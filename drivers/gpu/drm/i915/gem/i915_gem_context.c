<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2011-2012 Intel Corporation
 */

/*
 * This file implements HW context support. On gen5+ a HW context consists of an
 * opaque GPU object which is referenced at बार of context saves and restores.
 * With RC6 enabled, the context is also referenced as the GPU enters and exists
 * from RC6 (GPU has it's own पूर्णांकernal घातer context, except on gen5). Though
 * something like a context करोes exist क्रम the media ring, the code only
 * supports contexts क्रम the render ring.
 *
 * In software, there is a distinction between contexts created by the user,
 * and the शेष HW context. The शेष HW context is used by GPU clients
 * that करो not request setup of their own hardware context. The शेष
 * context's state is never restored to help prevent programming errors. This
 * would happen अगर a client ran and piggy-backed off another clients GPU state.
 * The शेष context only exists to give the GPU some offset to load as the
 * current to invoke a save of the context we actually care about. In fact, the
 * code could likely be स्थिरructed, albeit in a more complicated fashion, to
 * never use the शेष context, though that limits the driver's ability to
 * swap out, and/or destroy other contexts.
 *
 * All other contexts are created as a request by the GPU client. These contexts
 * store GPU state, and thus allow GPU clients to not re-emit state (and
 * potentially query certain state) at any समय. The kernel driver makes
 * certain that the appropriate commands are inserted.
 *
 * The context lअगरe cycle is semi-complicated in that context BOs may live
 * दीर्घer than the context itself because of the way the hardware, and object
 * tracking works. Below is a very crude representation of the state machine
 * describing the context lअगरe.
 *                                         refcount     pincount     active
 * S0: initial state                          0            0           0
 * S1: context created                        1            0           0
 * S2: context is currently running           2            1           X
 * S3: GPU referenced, but not current        2            0           1
 * S4: context is current, but destroyed      1            1           0
 * S5: like S3, but destroyed                 1            0           1
 *
 * The most common (but not all) transitions:
 * S0->S1: client creates a context
 * S1->S2: client submits execbuf with context
 * S2->S3: other clients submits execbuf with context
 * S3->S1: context object was retired
 * S3->S2: clients submits another execbuf
 * S2->S4: context destroy called with current context
 * S3->S5->S0: destroy path
 * S4->S5->S0: destroy path on current context
 *
 * There are two confusing terms used above:
 *  The "current context" means the context which is currently running on the
 *  GPU. The GPU has loaded its state alपढ़ोy and has stored away the gtt
 *  offset of the BO. The GPU is not actively referencing the data at this
 *  offset, but it will on the next context चयन. The only way to aव्योम this
 *  is to करो a GPU reset.
 *
 *  An "active context' is one which was previously the "current context" and is
 *  on the active list रुकोing क्रम the next context चयन to occur. Until this
 *  happens, the object must reमुख्य at the same gtt offset. It is thereक्रमe
 *  possible to destroy a context, but it is still active.
 *
 */

#समावेश <linux/log2.h>
#समावेश <linux/nospec.h>

#समावेश "gt/gen6_ppgtt.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_context_param.h"
#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_execlists_submission.h" /* भव_engine */
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_gem_context.h"
#समावेश "i915_globals.h"
#समावेश "i915_trace.h"
#समावेश "i915_user_extensions.h"

#घोषणा ALL_L3_SLICES(dev) (1 << NUM_L3_SLICES(dev)) - 1

अटल काष्ठा i915_global_gem_context अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_luts;
पूर्ण global;

काष्ठा i915_lut_handle *i915_lut_handle_alloc(व्योम)
अणु
	वापस kmem_cache_alloc(global.slab_luts, GFP_KERNEL);
पूर्ण

व्योम i915_lut_handle_मुक्त(काष्ठा i915_lut_handle *lut)
अणु
	वापस kmem_cache_मुक्त(global.slab_luts, lut);
पूर्ण

अटल व्योम lut_बंद(काष्ठा i915_gem_context *ctx)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	mutex_lock(&ctx->lut_mutex);
	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &ctx->handles_vma, &iter, 0) अणु
		काष्ठा i915_vma *vma = rcu_dereference_raw(*slot);
		काष्ठा drm_i915_gem_object *obj = vma->obj;
		काष्ठा i915_lut_handle *lut;

		अगर (!kref_get_unless_zero(&obj->base.refcount))
			जारी;

		spin_lock(&obj->lut_lock);
		list_क्रम_each_entry(lut, &obj->lut_list, obj_link) अणु
			अगर (lut->ctx != ctx)
				जारी;

			अगर (lut->handle != iter.index)
				जारी;

			list_del(&lut->obj_link);
			अवरोध;
		पूर्ण
		spin_unlock(&obj->lut_lock);

		अगर (&lut->obj_link != &obj->lut_list) अणु
			i915_lut_handle_मुक्त(lut);
			radix_tree_iter_delete(&ctx->handles_vma, &iter, slot);
			i915_vma_बंद(vma);
			i915_gem_object_put(obj);
		पूर्ण

		i915_gem_object_put(obj);
	पूर्ण
	rcu_पढ़ो_unlock();
	mutex_unlock(&ctx->lut_mutex);
पूर्ण

अटल काष्ठा पूर्णांकel_context *
lookup_user_engine(काष्ठा i915_gem_context *ctx,
		   अचिन्हित दीर्घ flags,
		   स्थिर काष्ठा i915_engine_class_instance *ci)
#घोषणा LOOKUP_USER_INDEX BIT(0)
अणु
	पूर्णांक idx;

	अगर (!!(flags & LOOKUP_USER_INDEX) != i915_gem_context_user_engines(ctx))
		वापस ERR_PTR(-EINVAL);

	अगर (!i915_gem_context_user_engines(ctx)) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;

		engine = पूर्णांकel_engine_lookup_user(ctx->i915,
						  ci->engine_class,
						  ci->engine_instance);
		अगर (!engine)
			वापस ERR_PTR(-EINVAL);

		idx = engine->legacy_idx;
	पूर्ण अन्यथा अणु
		idx = ci->engine_instance;
	पूर्ण

	वापस i915_gem_context_get_engine(ctx, idx);
पूर्ण

अटल काष्ठा i915_address_space *
context_get_vm_rcu(काष्ठा i915_gem_context *ctx)
अणु
	GEM_BUG_ON(!rcu_access_poपूर्णांकer(ctx->vm));

	करो अणु
		काष्ठा i915_address_space *vm;

		/*
		 * We करो not allow करोwngrading from full-ppgtt [to a shared
		 * global gtt], so ctx->vm cannot become शून्य.
		 */
		vm = rcu_dereference(ctx->vm);
		अगर (!kref_get_unless_zero(&vm->ref))
			जारी;

		/*
		 * This ppgtt may have be पुनः_स्मृतिated between
		 * the पढ़ो and the kref, and reasचिन्हित to a third
		 * context. In order to aव्योम inadvertent sharing
		 * of this ppgtt with that third context (and not
		 * src), we have to confirm that we have the same
		 * ppgtt after passing through the strong memory
		 * barrier implied by a successful
		 * kref_get_unless_zero().
		 *
		 * Once we have acquired the current ppgtt of ctx,
		 * we no दीर्घer care अगर it is released from ctx, as
		 * it cannot be पुनः_स्मृतिated अन्यथाwhere.
		 */

		अगर (vm == rcu_access_poपूर्णांकer(ctx->vm))
			वापस rcu_poपूर्णांकer_hanकरोff(vm);

		i915_vm_put(vm);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम पूर्णांकel_context_set_gem(काष्ठा पूर्णांकel_context *ce,
				  काष्ठा i915_gem_context *ctx)
अणु
	GEM_BUG_ON(rcu_access_poपूर्णांकer(ce->gem_context));
	RCU_INIT_POINTER(ce->gem_context, ctx);

	अगर (!test_bit(CONTEXT_ALLOC_BIT, &ce->flags))
		ce->ring = __पूर्णांकel_context_ring_size(SZ_16K);

	अगर (rcu_access_poपूर्णांकer(ctx->vm)) अणु
		काष्ठा i915_address_space *vm;

		rcu_पढ़ो_lock();
		vm = context_get_vm_rcu(ctx); /* hmm */
		rcu_पढ़ो_unlock();

		i915_vm_put(ce->vm);
		ce->vm = vm;
	पूर्ण

	GEM_BUG_ON(ce->समयline);
	अगर (ctx->समयline)
		ce->समयline = पूर्णांकel_समयline_get(ctx->समयline);

	अगर (ctx->sched.priority >= I915_PRIORITY_NORMAL &&
	    पूर्णांकel_engine_has_बारlices(ce->engine))
		__set_bit(CONTEXT_USE_SEMAPHORES, &ce->flags);

	पूर्णांकel_context_set_watchकरोg_us(ce, ctx->watchकरोg.समयout_us);
पूर्ण

अटल व्योम __मुक्त_engines(काष्ठा i915_gem_engines *e, अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (!e->engines[count])
			जारी;

		पूर्णांकel_context_put(e->engines[count]);
	पूर्ण
	kमुक्त(e);
पूर्ण

अटल व्योम मुक्त_engines(काष्ठा i915_gem_engines *e)
अणु
	__मुक्त_engines(e, e->num_engines);
पूर्ण

अटल व्योम मुक्त_engines_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा i915_gem_engines *engines =
		container_of(rcu, काष्ठा i915_gem_engines, rcu);

	i915_sw_fence_fini(&engines->fence);
	मुक्त_engines(engines);
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
engines_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा i915_gem_engines *engines =
		container_of(fence, typeof(*engines), fence);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		अगर (!list_empty(&engines->link)) अणु
			काष्ठा i915_gem_context *ctx = engines->ctx;
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&ctx->stale.lock, flags);
			list_del(&engines->link);
			spin_unlock_irqrestore(&ctx->stale.lock, flags);
		पूर्ण
		i915_gem_context_put(engines->ctx);
		अवरोध;

	हाल FENCE_FREE:
		init_rcu_head(&engines->rcu);
		call_rcu(&engines->rcu, मुक्त_engines_rcu);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा i915_gem_engines *alloc_engines(अचिन्हित पूर्णांक count)
अणु
	काष्ठा i915_gem_engines *e;

	e = kzalloc(काष्ठा_size(e, engines, count), GFP_KERNEL);
	अगर (!e)
		वापस शून्य;

	i915_sw_fence_init(&e->fence, engines_notअगरy);
	वापस e;
पूर्ण

अटल काष्ठा i915_gem_engines *शेष_engines(काष्ठा i915_gem_context *ctx)
अणु
	स्थिर काष्ठा पूर्णांकel_gt *gt = &ctx->i915->gt;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_gem_engines *e;
	क्रमागत पूर्णांकel_engine_id id;

	e = alloc_engines(I915_NUM_ENGINES);
	अगर (!e)
		वापस ERR_PTR(-ENOMEM);

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;

		अगर (engine->legacy_idx == INVALID_ENGINE)
			जारी;

		GEM_BUG_ON(engine->legacy_idx >= I915_NUM_ENGINES);
		GEM_BUG_ON(e->engines[engine->legacy_idx]);

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			__मुक्त_engines(e, e->num_engines + 1);
			वापस ERR_CAST(ce);
		पूर्ण

		पूर्णांकel_context_set_gem(ce, ctx);

		e->engines[engine->legacy_idx] = ce;
		e->num_engines = max(e->num_engines, engine->legacy_idx);
	पूर्ण
	e->num_engines++;

	वापस e;
पूर्ण

व्योम i915_gem_context_release(काष्ठा kref *ref)
अणु
	काष्ठा i915_gem_context *ctx = container_of(ref, typeof(*ctx), ref);

	trace_i915_context_मुक्त(ctx);
	GEM_BUG_ON(!i915_gem_context_is_बंदd(ctx));

	mutex_destroy(&ctx->engines_mutex);
	mutex_destroy(&ctx->lut_mutex);

	अगर (ctx->समयline)
		पूर्णांकel_समयline_put(ctx->समयline);

	put_pid(ctx->pid);
	mutex_destroy(&ctx->mutex);

	kमुक्त_rcu(ctx, rcu);
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_engines *
__context_engines_अटल(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस rcu_dereference_रक्षित(ctx->engines, true);
पूर्ण

अटल व्योम __reset_context(काष्ठा i915_gem_context *ctx,
			    काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_gt_handle_error(engine->gt, engine->mask, 0,
			      "context closure in %s", ctx->name);
पूर्ण

अटल bool __cancel_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/*
	 * Send a "high priority pulse" करोwn the engine to cause the
	 * current request to be momentarily preempted. (If it fails to
	 * be preempted, it will be reset). As we have marked our context
	 * as banned, any incomplete request, including any running, will
	 * be skipped following the preemption.
	 *
	 * If there is no hangchecking (one of the reasons why we try to
	 * cancel the context) and no क्रमced preemption, there may be no
	 * means by which we reset the GPU and evict the persistent hog.
	 * Ergo अगर we are unable to inject a preemptive pulse that can
	 * समाप्त the banned context, we fallback to करोing a local reset
	 * instead.
	 */
	वापस पूर्णांकel_engine_pulse(engine) == 0;
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs *active_engine(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = शून्य;
	काष्ठा i915_request *rq;

	अगर (पूर्णांकel_context_has_inflight(ce))
		वापस पूर्णांकel_context_inflight(ce);

	अगर (!ce->समयline)
		वापस शून्य;

	/*
	 * rq->link is only SLAB_TYPESAFE_BY_RCU, we need to hold a reference
	 * to the request to prevent it being transferred to a new समयline
	 * (and onto a new समयline->requests list).
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_reverse(rq, &ce->समयline->requests, link) अणु
		bool found;

		/* समयline is alपढ़ोy completed upto this poपूर्णांक? */
		अगर (!i915_request_get_rcu(rq))
			अवरोध;

		/* Check with the backend अगर the request is inflight */
		found = true;
		अगर (likely(rcu_access_poपूर्णांकer(rq->समयline) == ce->समयline))
			found = i915_request_active_engine(rq, &engine);

		i915_request_put(rq);
		अगर (found)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस engine;
पूर्ण

अटल व्योम समाप्त_engines(काष्ठा i915_gem_engines *engines, bool ban)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;

	/*
	 * Map the user's engine back to the actual engines; one भव
	 * engine will be mapped to multiple engines, and using ctx->engine[]
	 * the same engine may be have multiple instances in the user's map.
	 * However, we only care about pending requests, so only include
	 * engines on which there are incomplete requests.
	 */
	क्रम_each_gem_engine(ce, engines, it) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;

		अगर (ban && पूर्णांकel_context_set_banned(ce))
			जारी;

		/*
		 * Check the current active state of this context; अगर we
		 * are currently executing on the GPU we need to evict
		 * ourselves. On the other hand, अगर we haven't yet been
		 * submitted to the GPU or अगर everything is complete,
		 * we have nothing to करो.
		 */
		engine = active_engine(ce);

		/* First attempt to gracefully cancel the context */
		अगर (engine && !__cancel_engine(engine) && ban)
			/*
			 * If we are unable to send a preemptive pulse to bump
			 * the context from the GPU, we have to resort to a full
			 * reset. We hope the collateral damage is worth it.
			 */
			__reset_context(engines->ctx, engine);
	पूर्ण
पूर्ण

अटल व्योम समाप्त_context(काष्ठा i915_gem_context *ctx)
अणु
	bool ban = (!i915_gem_context_is_persistent(ctx) ||
		    !ctx->i915->params.enable_hangcheck);
	काष्ठा i915_gem_engines *pos, *next;

	spin_lock_irq(&ctx->stale.lock);
	GEM_BUG_ON(!i915_gem_context_is_बंदd(ctx));
	list_क्रम_each_entry_safe(pos, next, &ctx->stale.engines, link) अणु
		अगर (!i915_sw_fence_aरुको(&pos->fence)) अणु
			list_del_init(&pos->link);
			जारी;
		पूर्ण

		spin_unlock_irq(&ctx->stale.lock);

		समाप्त_engines(pos, ban);

		spin_lock_irq(&ctx->stale.lock);
		GEM_BUG_ON(i915_sw_fence_संकेतed(&pos->fence));
		list_safe_reset_next(pos, next, link);
		list_del_init(&pos->link); /* decouple from FENCE_COMPLETE */

		i915_sw_fence_complete(&pos->fence);
	पूर्ण
	spin_unlock_irq(&ctx->stale.lock);
पूर्ण

अटल व्योम engines_idle_release(काष्ठा i915_gem_context *ctx,
				 काष्ठा i915_gem_engines *engines)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;

	INIT_LIST_HEAD(&engines->link);

	engines->ctx = i915_gem_context_get(ctx);

	क्रम_each_gem_engine(ce, engines, it) अणु
		पूर्णांक err;

		/* serialises with execbuf */
		set_bit(CONTEXT_CLOSED_BIT, &ce->flags);
		अगर (!पूर्णांकel_context_pin_अगर_active(ce))
			जारी;

		/* Wait until context is finally scheduled out and retired */
		err = i915_sw_fence_aरुको_active(&engines->fence,
						 &ce->active,
						 I915_ACTIVE_AWAIT_BARRIER);
		पूर्णांकel_context_unpin(ce);
		अगर (err)
			जाओ समाप्त;
	पूर्ण

	spin_lock_irq(&ctx->stale.lock);
	अगर (!i915_gem_context_is_बंदd(ctx))
		list_add_tail(&engines->link, &ctx->stale.engines);
	spin_unlock_irq(&ctx->stale.lock);

समाप्त:
	अगर (list_empty(&engines->link)) /* raced, alपढ़ोy बंदd */
		समाप्त_engines(engines, true);

	i915_sw_fence_commit(&engines->fence);
पूर्ण

अटल व्योम set_बंदd_name(काष्ठा i915_gem_context *ctx)
अणु
	अक्षर *s;

	/* Replace '[]' with '<>' to indicate बंदd in debug prपूर्णांकs */

	s = म_खोजप(ctx->name, '[');
	अगर (!s)
		वापस;

	*s = '<';

	s = म_अक्षर(s + 1, ']');
	अगर (s)
		*s = '>';
पूर्ण

अटल व्योम context_बंद(काष्ठा i915_gem_context *ctx)
अणु
	काष्ठा i915_address_space *vm;

	/* Flush any concurrent set_engines() */
	mutex_lock(&ctx->engines_mutex);
	engines_idle_release(ctx, rcu_replace_poपूर्णांकer(ctx->engines, शून्य, 1));
	i915_gem_context_set_बंदd(ctx);
	mutex_unlock(&ctx->engines_mutex);

	mutex_lock(&ctx->mutex);

	set_बंदd_name(ctx);

	vm = i915_gem_context_vm(ctx);
	अगर (vm)
		i915_vm_बंद(vm);

	ctx->file_priv = ERR_PTR(-EBADF);

	/*
	 * The LUT uses the VMA as a backpoपूर्णांकer to unref the object,
	 * so we need to clear the LUT beक्रमe we बंद all the VMA (inside
	 * the ppgtt).
	 */
	lut_बंद(ctx);

	spin_lock(&ctx->i915->gem.contexts.lock);
	list_del(&ctx->link);
	spin_unlock(&ctx->i915->gem.contexts.lock);

	mutex_unlock(&ctx->mutex);

	/*
	 * If the user has disabled hangchecking, we can not be sure that
	 * the batches will ever complete after the context is बंदd,
	 * keeping the context and all resources pinned क्रमever. So in this
	 * हाल we opt to क्रमcibly समाप्त off all reमुख्यing requests on
	 * context बंद.
	 */
	समाप्त_context(ctx);

	i915_gem_context_put(ctx);
पूर्ण

अटल पूर्णांक __context_set_persistence(काष्ठा i915_gem_context *ctx, bool state)
अणु
	अगर (i915_gem_context_is_persistent(ctx) == state)
		वापस 0;

	अगर (state) अणु
		/*
		 * Only contexts that are लघु-lived [that will expire or be
		 * reset] are allowed to survive past termination. We require
		 * hangcheck to ensure that the persistent requests are healthy.
		 */
		अगर (!ctx->i915->params.enable_hangcheck)
			वापस -EINVAL;

		i915_gem_context_set_persistence(ctx);
	पूर्ण अन्यथा अणु
		/* To cancel a context we use "preempt-to-idle" */
		अगर (!(ctx->i915->caps.scheduler & I915_SCHEDULER_CAP_PREEMPTION))
			वापस -ENODEV;

		/*
		 * If the cancel fails, we then need to reset, cleanly!
		 *
		 * If the per-engine reset fails, all hope is lost! We resort
		 * to a full GPU reset in that unlikely हाल, but realistically
		 * अगर the engine could not reset, the full reset करोes not fare
		 * much better. The damage has been करोne.
		 *
		 * However, अगर we cannot reset an engine by itself, we cannot
		 * cleanup a hanging persistent context without causing
		 * colateral damage, and we should not pretend we can by
		 * exposing the पूर्णांकerface.
		 */
		अगर (!पूर्णांकel_has_reset_engine(&ctx->i915->gt))
			वापस -ENODEV;

		i915_gem_context_clear_persistence(ctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i915_gem_context *
__create_context(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_gem_context *ctx;
	काष्ठा i915_gem_engines *e;
	पूर्णांक err;
	पूर्णांक i;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&ctx->ref);
	ctx->i915 = i915;
	ctx->sched.priority = I915_PRIORITY_NORMAL;
	mutex_init(&ctx->mutex);
	INIT_LIST_HEAD(&ctx->link);

	spin_lock_init(&ctx->stale.lock);
	INIT_LIST_HEAD(&ctx->stale.engines);

	mutex_init(&ctx->engines_mutex);
	e = शेष_engines(ctx);
	अगर (IS_ERR(e)) अणु
		err = PTR_ERR(e);
		जाओ err_मुक्त;
	पूर्ण
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	mutex_init(&ctx->lut_mutex);

	/* NB: Mark all slices as needing a remap so that when the context first
	 * loads it will restore whatever remap state alपढ़ोy exists. If there
	 * is no remap info, it will be a NOP. */
	ctx->remap_slice = ALL_L3_SLICES(i915);

	i915_gem_context_set_bannable(ctx);
	i915_gem_context_set_recoverable(ctx);
	__context_set_persistence(ctx, true /* cgroup hook? */);

	क्रम (i = 0; i < ARRAY_SIZE(ctx->hang_बारtamp); i++)
		ctx->hang_बारtamp[i] = jअगरfies - CONTEXT_FAST_HANG_JIFFIES;

	वापस ctx;

err_मुक्त:
	kमुक्त(ctx);
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_engines *
__context_engines_aरुको(स्थिर काष्ठा i915_gem_context *ctx,
			bool *user_engines)
अणु
	काष्ठा i915_gem_engines *engines;

	rcu_पढ़ो_lock();
	करो अणु
		engines = rcu_dereference(ctx->engines);
		GEM_BUG_ON(!engines);

		अगर (user_engines)
			*user_engines = i915_gem_context_user_engines(ctx);

		/* successful aरुको => strong mb */
		अगर (unlikely(!i915_sw_fence_aरुको(&engines->fence)))
			जारी;

		अगर (likely(engines == rcu_access_poपूर्णांकer(ctx->engines)))
			अवरोध;

		i915_sw_fence_complete(&engines->fence);
	पूर्ण जबतक (1);
	rcu_पढ़ो_unlock();

	वापस engines;
पूर्ण

अटल पूर्णांक
context_apply_all(काष्ठा i915_gem_context *ctx,
		  पूर्णांक (*fn)(काष्ठा पूर्णांकel_context *ce, व्योम *data),
		  व्योम *data)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_gem_engines *e;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err = 0;

	e = __context_engines_aरुको(ctx, शून्य);
	क्रम_each_gem_engine(ce, e, it) अणु
		err = fn(ce, data);
		अगर (err)
			अवरोध;
	पूर्ण
	i915_sw_fence_complete(&e->fence);

	वापस err;
पूर्ण

अटल पूर्णांक __apply_ppgtt(काष्ठा पूर्णांकel_context *ce, व्योम *vm)
अणु
	i915_vm_put(ce->vm);
	ce->vm = i915_vm_get(vm);
	वापस 0;
पूर्ण

अटल काष्ठा i915_address_space *
__set_ppgtt(काष्ठा i915_gem_context *ctx, काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_address_space *old;

	old = rcu_replace_poपूर्णांकer(ctx->vm,
				  i915_vm_खोलो(vm),
				  lockdep_is_held(&ctx->mutex));
	GEM_BUG_ON(old && i915_vm_is_4lvl(vm) != i915_vm_is_4lvl(old));

	context_apply_all(ctx, __apply_ppgtt, vm);

	वापस old;
पूर्ण

अटल व्योम __assign_ppgtt(काष्ठा i915_gem_context *ctx,
			   काष्ठा i915_address_space *vm)
अणु
	अगर (vm == rcu_access_poपूर्णांकer(ctx->vm))
		वापस;

	vm = __set_ppgtt(ctx, vm);
	अगर (vm)
		i915_vm_बंद(vm);
पूर्ण

अटल व्योम __set_समयline(काष्ठा पूर्णांकel_समयline **dst,
			   काष्ठा पूर्णांकel_समयline *src)
अणु
	काष्ठा पूर्णांकel_समयline *old = *dst;

	*dst = src ? पूर्णांकel_समयline_get(src) : शून्य;

	अगर (old)
		पूर्णांकel_समयline_put(old);
पूर्ण

अटल पूर्णांक __apply_समयline(काष्ठा पूर्णांकel_context *ce, व्योम *समयline)
अणु
	__set_समयline(&ce->समयline, समयline);
	वापस 0;
पूर्ण

अटल व्योम __assign_समयline(काष्ठा i915_gem_context *ctx,
			      काष्ठा पूर्णांकel_समयline *समयline)
अणु
	__set_समयline(&ctx->समयline, समयline);
	context_apply_all(ctx, __apply_समयline, समयline);
पूर्ण

अटल पूर्णांक __apply_watchकरोg(काष्ठा पूर्णांकel_context *ce, व्योम *समयout_us)
अणु
	वापस पूर्णांकel_context_set_watchकरोg_us(ce, (uपूर्णांकptr_t)समयout_us);
पूर्ण

अटल पूर्णांक
__set_watchकरोg(काष्ठा i915_gem_context *ctx, अचिन्हित दीर्घ समयout_us)
अणु
	पूर्णांक ret;

	ret = context_apply_all(ctx, __apply_watchकरोg,
				(व्योम *)(uपूर्णांकptr_t)समयout_us);
	अगर (!ret)
		ctx->watchकरोg.समयout_us = समयout_us;

	वापस ret;
पूर्ण

अटल व्योम __set_शेष_fence_expiry(काष्ठा i915_gem_context *ctx)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	पूर्णांक ret;

	अगर (!IS_ACTIVE(CONFIG_DRM_I915_REQUEST_TIMEOUT) ||
	    !i915->params.request_समयout_ms)
		वापस;

	/* Default expiry क्रम user fences. */
	ret = __set_watchकरोg(ctx, i915->params.request_समयout_ms * 1000);
	अगर (ret)
		drm_notice(&i915->drm,
			   "Failed to configure default fence expiry! (%d)",
			   ret);
पूर्ण

अटल काष्ठा i915_gem_context *
i915_gem_create_context(काष्ठा drm_i915_निजी *i915, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_gem_context *ctx;

	अगर (flags & I915_CONTEXT_CREATE_FLAGS_SINGLE_TIMELINE &&
	    !HAS_EXECLISTS(i915))
		वापस ERR_PTR(-EINVAL);

	ctx = __create_context(i915);
	अगर (IS_ERR(ctx))
		वापस ctx;

	अगर (HAS_FULL_PPGTT(i915)) अणु
		काष्ठा i915_ppgtt *ppgtt;

		ppgtt = i915_ppgtt_create(&i915->gt);
		अगर (IS_ERR(ppgtt)) अणु
			drm_dbg(&i915->drm, "PPGTT setup failed (%ld)\n",
				PTR_ERR(ppgtt));
			context_बंद(ctx);
			वापस ERR_CAST(ppgtt);
		पूर्ण

		mutex_lock(&ctx->mutex);
		__assign_ppgtt(ctx, &ppgtt->vm);
		mutex_unlock(&ctx->mutex);

		i915_vm_put(&ppgtt->vm);
	पूर्ण

	अगर (flags & I915_CONTEXT_CREATE_FLAGS_SINGLE_TIMELINE) अणु
		काष्ठा पूर्णांकel_समयline *समयline;

		समयline = पूर्णांकel_समयline_create(&i915->gt);
		अगर (IS_ERR(समयline)) अणु
			context_बंद(ctx);
			वापस ERR_CAST(समयline);
		पूर्ण

		__assign_समयline(ctx, समयline);
		पूर्णांकel_समयline_put(समयline);
	पूर्ण

	__set_शेष_fence_expiry(ctx);

	trace_i915_context_create(ctx);

	वापस ctx;
पूर्ण

अटल व्योम init_contexts(काष्ठा i915_gem_contexts *gc)
अणु
	spin_lock_init(&gc->lock);
	INIT_LIST_HEAD(&gc->list);
पूर्ण

व्योम i915_gem_init__contexts(काष्ठा drm_i915_निजी *i915)
अणु
	init_contexts(&i915->gem.contexts);
पूर्ण

अटल पूर्णांक gem_context_रेजिस्टर(काष्ठा i915_gem_context *ctx,
				काष्ठा drm_i915_file_निजी *fpriv,
				u32 *id)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा i915_address_space *vm;
	पूर्णांक ret;

	ctx->file_priv = fpriv;

	mutex_lock(&ctx->mutex);
	vm = i915_gem_context_vm(ctx);
	अगर (vm)
		WRITE_ONCE(vm->file, fpriv); /* XXX */
	mutex_unlock(&ctx->mutex);

	ctx->pid = get_task_pid(current, PIDTYPE_PID);
	snम_लिखो(ctx->name, माप(ctx->name), "%s[%d]",
		 current->comm, pid_nr(ctx->pid));

	/* And finally expose ourselves to userspace via the idr */
	ret = xa_alloc(&fpriv->context_xa, id, ctx, xa_limit_32b, GFP_KERNEL);
	अगर (ret)
		जाओ err_pid;

	spin_lock(&i915->gem.contexts.lock);
	list_add_tail(&ctx->link, &i915->gem.contexts.list);
	spin_unlock(&i915->gem.contexts.lock);

	वापस 0;

err_pid:
	put_pid(fetch_and_zero(&ctx->pid));
	वापस ret;
पूर्ण

पूर्णांक i915_gem_context_खोलो(काष्ठा drm_i915_निजी *i915,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक err;
	u32 id;

	xa_init_flags(&file_priv->context_xa, XA_FLAGS_ALLOC);

	/* 0 reserved क्रम invalid/unasचिन्हित ppgtt */
	xa_init_flags(&file_priv->vm_xa, XA_FLAGS_ALLOC1);

	ctx = i915_gem_create_context(i915, 0);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ err;
	पूर्ण

	err = gem_context_रेजिस्टर(ctx, file_priv, &id);
	अगर (err < 0)
		जाओ err_ctx;

	GEM_BUG_ON(id);
	वापस 0;

err_ctx:
	context_बंद(ctx);
err:
	xa_destroy(&file_priv->vm_xa);
	xa_destroy(&file_priv->context_xa);
	वापस err;
पूर्ण

व्योम i915_gem_context_बंद(काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_gem_context *ctx;
	अचिन्हित दीर्घ idx;

	xa_क्रम_each(&file_priv->context_xa, idx, ctx)
		context_बंद(ctx);
	xa_destroy(&file_priv->context_xa);

	xa_क्रम_each(&file_priv->vm_xa, idx, vm)
		i915_vm_put(vm);
	xa_destroy(&file_priv->vm_xa);
पूर्ण

पूर्णांक i915_gem_vm_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_vm_control *args = data;
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा i915_ppgtt *ppgtt;
	u32 id;
	पूर्णांक err;

	अगर (!HAS_FULL_PPGTT(i915))
		वापस -ENODEV;

	अगर (args->flags)
		वापस -EINVAL;

	ppgtt = i915_ppgtt_create(&i915->gt);
	अगर (IS_ERR(ppgtt))
		वापस PTR_ERR(ppgtt);

	ppgtt->vm.file = file_priv;

	अगर (args->extensions) अणु
		err = i915_user_extensions(u64_to_user_ptr(args->extensions),
					   शून्य, 0,
					   ppgtt);
		अगर (err)
			जाओ err_put;
	पूर्ण

	err = xa_alloc(&file_priv->vm_xa, &id, &ppgtt->vm,
		       xa_limit_32b, GFP_KERNEL);
	अगर (err)
		जाओ err_put;

	GEM_BUG_ON(id == 0); /* reserved क्रम invalid/unasचिन्हित ppgtt */
	args->vm_id = id;
	वापस 0;

err_put:
	i915_vm_put(&ppgtt->vm);
	वापस err;
पूर्ण

पूर्णांक i915_gem_vm_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा drm_i915_gem_vm_control *args = data;
	काष्ठा i915_address_space *vm;

	अगर (args->flags)
		वापस -EINVAL;

	अगर (args->extensions)
		वापस -EINVAL;

	vm = xa_erase(&file_priv->vm_xa, args->vm_id);
	अगर (!vm)
		वापस -ENOENT;

	i915_vm_put(vm);
	वापस 0;
पूर्ण

काष्ठा context_barrier_task अणु
	काष्ठा i915_active base;
	व्योम (*task)(व्योम *data);
	व्योम *data;
पूर्ण;

__i915_active_call
अटल व्योम cb_retire(काष्ठा i915_active *base)
अणु
	काष्ठा context_barrier_task *cb = container_of(base, typeof(*cb), base);

	अगर (cb->task)
		cb->task(cb->data);

	i915_active_fini(&cb->base);
	kमुक्त(cb);
पूर्ण

I915_SELFTEST_DECLARE(अटल पूर्णांकel_engine_mask_t context_barrier_inject_fault);
अटल पूर्णांक context_barrier_task(काष्ठा i915_gem_context *ctx,
				पूर्णांकel_engine_mask_t engines,
				bool (*skip)(काष्ठा पूर्णांकel_context *ce, व्योम *data),
				पूर्णांक (*pin)(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_gem_ww_ctx *ww, व्योम *data),
				पूर्णांक (*emit)(काष्ठा i915_request *rq, व्योम *data),
				व्योम (*task)(व्योम *data),
				व्योम *data)
अणु
	काष्ठा context_barrier_task *cb;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_gem_engines *e;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err = 0;

	GEM_BUG_ON(!task);

	cb = kदो_स्मृति(माप(*cb), GFP_KERNEL);
	अगर (!cb)
		वापस -ENOMEM;

	i915_active_init(&cb->base, शून्य, cb_retire);
	err = i915_active_acquire(&cb->base);
	अगर (err) अणु
		kमुक्त(cb);
		वापस err;
	पूर्ण

	e = __context_engines_aरुको(ctx, शून्य);
	अगर (!e) अणु
		i915_active_release(&cb->base);
		वापस -ENOENT;
	पूर्ण

	क्रम_each_gem_engine(ce, e, it) अणु
		काष्ठा i915_request *rq;

		अगर (I915_SELFTEST_ONLY(context_barrier_inject_fault &
				       ce->engine->mask)) अणु
			err = -ENXIO;
			अवरोध;
		पूर्ण

		अगर (!(ce->engine->mask & engines))
			जारी;

		अगर (skip && skip(ce, data))
			जारी;

		i915_gem_ww_ctx_init(&ww, true);
retry:
		err = पूर्णांकel_context_pin_ww(ce, &ww);
		अगर (err)
			जाओ err;

		अगर (pin)
			err = pin(ce, &ww, data);
		अगर (err)
			जाओ err_unpin;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_unpin;
		पूर्ण

		err = 0;
		अगर (emit)
			err = emit(rq, data);
		अगर (err == 0)
			err = i915_active_add_request(&cb->base, rq);

		i915_request_add(rq);
err_unpin:
		पूर्णांकel_context_unpin(ce);
err:
		अगर (err == -EDEADLK) अणु
			err = i915_gem_ww_ctx_backoff(&ww);
			अगर (!err)
				जाओ retry;
		पूर्ण
		i915_gem_ww_ctx_fini(&ww);

		अगर (err)
			अवरोध;
	पूर्ण
	i915_sw_fence_complete(&e->fence);

	cb->task = err ? शून्य : task; /* caller needs to unwind instead */
	cb->data = data;

	i915_active_release(&cb->base);

	वापस err;
पूर्ण

अटल पूर्णांक get_ppgtt(काष्ठा drm_i915_file_निजी *file_priv,
		     काष्ठा i915_gem_context *ctx,
		     काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा i915_address_space *vm;
	पूर्णांक err;
	u32 id;

	अगर (!rcu_access_poपूर्णांकer(ctx->vm))
		वापस -ENODEV;

	rcu_पढ़ो_lock();
	vm = context_get_vm_rcu(ctx);
	rcu_पढ़ो_unlock();
	अगर (!vm)
		वापस -ENODEV;

	err = xa_alloc(&file_priv->vm_xa, &id, vm, xa_limit_32b, GFP_KERNEL);
	अगर (err)
		जाओ err_put;

	i915_vm_खोलो(vm);

	GEM_BUG_ON(id == 0); /* reserved क्रम invalid/unasचिन्हित ppgtt */
	args->value = id;
	args->size = 0;

err_put:
	i915_vm_put(vm);
	वापस err;
पूर्ण

अटल व्योम set_ppgtt_barrier(व्योम *data)
अणु
	काष्ठा i915_address_space *old = data;

	अगर (INTEL_GEN(old->i915) < 8)
		gen6_ppgtt_unpin_all(i915_vm_to_ppgtt(old));

	i915_vm_बंद(old);
पूर्ण

अटल पूर्णांक pin_ppgtt_update(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_gem_ww_ctx *ww, व्योम *data)
अणु
	काष्ठा i915_address_space *vm = ce->vm;

	अगर (!HAS_LOGICAL_RING_CONTEXTS(vm->i915))
		/* ppGTT is not part of the legacy context image */
		वापस gen6_ppgtt_pin(i915_vm_to_ppgtt(vm), ww);

	वापस 0;
पूर्ण

अटल पूर्णांक emit_ppgtt_update(काष्ठा i915_request *rq, व्योम *data)
अणु
	काष्ठा i915_address_space *vm = rq->context->vm;
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	u32 base = engine->mmio_base;
	u32 *cs;
	पूर्णांक i;

	अगर (i915_vm_is_4lvl(vm)) अणु
		काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);
		स्थिर dma_addr_t pd_daddr = px_dma(ppgtt->pd);

		cs = पूर्णांकel_ring_begin(rq, 6);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		*cs++ = MI_LOAD_REGISTER_IMM(2);

		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_UDW(base, 0));
		*cs++ = upper_32_bits(pd_daddr);
		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_LDW(base, 0));
		*cs++ = lower_32_bits(pd_daddr);

		*cs++ = MI_NOOP;
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण अन्यथा अगर (HAS_LOGICAL_RING_CONTEXTS(engine->i915)) अणु
		काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);
		पूर्णांक err;

		/* Magic required to prevent क्रमcewake errors! */
		err = engine->emit_flush(rq, EMIT_INVALIDATE);
		अगर (err)
			वापस err;

		cs = पूर्णांकel_ring_begin(rq, 4 * GEN8_3LVL_PDPES + 2);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		*cs++ = MI_LOAD_REGISTER_IMM(2 * GEN8_3LVL_PDPES) | MI_LRI_FORCE_POSTED;
		क्रम (i = GEN8_3LVL_PDPES; i--; ) अणु
			स्थिर dma_addr_t pd_daddr = i915_page_dir_dma_addr(ppgtt, i);

			*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_UDW(base, i));
			*cs++ = upper_32_bits(pd_daddr);
			*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_LDW(base, i));
			*cs++ = lower_32_bits(pd_daddr);
		पूर्ण
		*cs++ = MI_NOOP;
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool skip_ppgtt_update(काष्ठा पूर्णांकel_context *ce, व्योम *data)
अणु
	अगर (HAS_LOGICAL_RING_CONTEXTS(ce->engine->i915))
		वापस !ce->state;
	अन्यथा
		वापस !atomic_पढ़ो(&ce->pin_count);
पूर्ण

अटल पूर्णांक set_ppgtt(काष्ठा drm_i915_file_निजी *file_priv,
		     काष्ठा i915_gem_context *ctx,
		     काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा i915_address_space *vm, *old;
	पूर्णांक err;

	अगर (args->size)
		वापस -EINVAL;

	अगर (!rcu_access_poपूर्णांकer(ctx->vm))
		वापस -ENODEV;

	अगर (upper_32_bits(args->value))
		वापस -ENOENT;

	rcu_पढ़ो_lock();
	vm = xa_load(&file_priv->vm_xa, args->value);
	अगर (vm && !kref_get_unless_zero(&vm->ref))
		vm = शून्य;
	rcu_पढ़ो_unlock();
	अगर (!vm)
		वापस -ENOENT;

	err = mutex_lock_पूर्णांकerruptible(&ctx->mutex);
	अगर (err)
		जाओ out;

	अगर (i915_gem_context_is_बंदd(ctx)) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	अगर (vm == rcu_access_poपूर्णांकer(ctx->vm))
		जाओ unlock;

	old = __set_ppgtt(ctx, vm);

	/* Tearकरोwn the existing obj:vma cache, it will have to be rebuilt. */
	lut_बंद(ctx);

	/*
	 * We need to flush any requests using the current ppgtt beक्रमe
	 * we release it as the requests करो not hold a reference themselves,
	 * only indirectly through the context.
	 */
	err = context_barrier_task(ctx, ALL_ENGINES,
				   skip_ppgtt_update,
				   pin_ppgtt_update,
				   emit_ppgtt_update,
				   set_ppgtt_barrier,
				   old);
	अगर (err) अणु
		i915_vm_बंद(__set_ppgtt(ctx, old));
		i915_vm_बंद(old);
		lut_बंद(ctx); /* क्रमce a rebuild of the old obj:vma cache */
	पूर्ण

unlock:
	mutex_unlock(&ctx->mutex);
out:
	i915_vm_put(vm);
	वापस err;
पूर्ण

अटल पूर्णांक __apply_ringsize(काष्ठा पूर्णांकel_context *ce, व्योम *sz)
अणु
	वापस पूर्णांकel_context_set_ring_size(ce, (अचिन्हित दीर्घ)sz);
पूर्ण

अटल पूर्णांक set_ringsize(काष्ठा i915_gem_context *ctx,
			काष्ठा drm_i915_gem_context_param *args)
अणु
	अगर (!HAS_LOGICAL_RING_CONTEXTS(ctx->i915))
		वापस -ENODEV;

	अगर (args->size)
		वापस -EINVAL;

	अगर (!IS_ALIGNED(args->value, I915_GTT_PAGE_SIZE))
		वापस -EINVAL;

	अगर (args->value < I915_GTT_PAGE_SIZE)
		वापस -EINVAL;

	अगर (args->value > 128 * I915_GTT_PAGE_SIZE)
		वापस -EINVAL;

	वापस context_apply_all(ctx,
				 __apply_ringsize,
				 __पूर्णांकel_context_ring_size(args->value));
पूर्ण

अटल पूर्णांक __get_ringsize(काष्ठा पूर्णांकel_context *ce, व्योम *arg)
अणु
	दीर्घ sz;

	sz = पूर्णांकel_context_get_ring_size(ce);
	GEM_BUG_ON(sz > पूर्णांक_उच्च);

	वापस sz; /* stop on first engine */
पूर्ण

अटल पूर्णांक get_ringsize(काष्ठा i915_gem_context *ctx,
			काष्ठा drm_i915_gem_context_param *args)
अणु
	पूर्णांक sz;

	अगर (!HAS_LOGICAL_RING_CONTEXTS(ctx->i915))
		वापस -ENODEV;

	अगर (args->size)
		वापस -EINVAL;

	sz = context_apply_all(ctx, __get_ringsize, शून्य);
	अगर (sz < 0)
		वापस sz;

	args->value = sz;
	वापस 0;
पूर्ण

पूर्णांक
i915_gem_user_to_context_sseu(काष्ठा पूर्णांकel_gt *gt,
			      स्थिर काष्ठा drm_i915_gem_context_param_sseu *user,
			      काष्ठा पूर्णांकel_sseu *context)
अणु
	स्थिर काष्ठा sseu_dev_info *device = &gt->info.sseu;
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	/* No zeros in any field. */
	अगर (!user->slice_mask || !user->subslice_mask ||
	    !user->min_eus_per_subslice || !user->max_eus_per_subslice)
		वापस -EINVAL;

	/* Max > min. */
	अगर (user->max_eus_per_subslice < user->min_eus_per_subslice)
		वापस -EINVAL;

	/*
	 * Some future proofing on the types since the uAPI is wider than the
	 * current पूर्णांकernal implementation.
	 */
	अगर (overflows_type(user->slice_mask, context->slice_mask) ||
	    overflows_type(user->subslice_mask, context->subslice_mask) ||
	    overflows_type(user->min_eus_per_subslice,
			   context->min_eus_per_subslice) ||
	    overflows_type(user->max_eus_per_subslice,
			   context->max_eus_per_subslice))
		वापस -EINVAL;

	/* Check validity against hardware. */
	अगर (user->slice_mask & ~device->slice_mask)
		वापस -EINVAL;

	अगर (user->subslice_mask & ~device->subslice_mask[0])
		वापस -EINVAL;

	अगर (user->max_eus_per_subslice > device->max_eus_per_subslice)
		वापस -EINVAL;

	context->slice_mask = user->slice_mask;
	context->subslice_mask = user->subslice_mask;
	context->min_eus_per_subslice = user->min_eus_per_subslice;
	context->max_eus_per_subslice = user->max_eus_per_subslice;

	/* Part specअगरic restrictions. */
	अगर (IS_GEN(i915, 11)) अणु
		अचिन्हित पूर्णांक hw_s = hweight8(device->slice_mask);
		अचिन्हित पूर्णांक hw_ss_per_s = hweight8(device->subslice_mask[0]);
		अचिन्हित पूर्णांक req_s = hweight8(context->slice_mask);
		अचिन्हित पूर्णांक req_ss = hweight8(context->subslice_mask);

		/*
		 * Only full subslice enablement is possible अगर more than one
		 * slice is turned on.
		 */
		अगर (req_s > 1 && req_ss != hw_ss_per_s)
			वापस -EINVAL;

		/*
		 * If more than four (SScount bitfield limit) subslices are
		 * requested then the number has to be even.
		 */
		अगर (req_ss > 4 && (req_ss & 1))
			वापस -EINVAL;

		/*
		 * If only one slice is enabled and subslice count is below the
		 * device full enablement, it must be at most half of the all
		 * available subslices.
		 */
		अगर (req_s == 1 && req_ss < hw_ss_per_s &&
		    req_ss > (hw_ss_per_s / 2))
			वापस -EINVAL;

		/* ABI restriction - VME use हाल only. */

		/* All slices or one slice only. */
		अगर (req_s != 1 && req_s != hw_s)
			वापस -EINVAL;

		/*
		 * Half subslices or full enablement only when one slice is
		 * enabled.
		 */
		अगर (req_s == 1 &&
		    (req_ss != hw_ss_per_s && req_ss != (hw_ss_per_s / 2)))
			वापस -EINVAL;

		/* No EU configuration changes. */
		अगर ((user->min_eus_per_subslice !=
		     device->max_eus_per_subslice) ||
		    (user->max_eus_per_subslice !=
		     device->max_eus_per_subslice))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_sseu(काष्ठा i915_gem_context *ctx,
		    काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा drm_i915_gem_context_param_sseu user_sseu;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा पूर्णांकel_sseu sseu;
	अचिन्हित दीर्घ lookup;
	पूर्णांक ret;

	अगर (args->size < माप(user_sseu))
		वापस -EINVAL;

	अगर (!IS_GEN(i915, 11))
		वापस -ENODEV;

	अगर (copy_from_user(&user_sseu, u64_to_user_ptr(args->value),
			   माप(user_sseu)))
		वापस -EFAULT;

	अगर (user_sseu.rsvd)
		वापस -EINVAL;

	अगर (user_sseu.flags & ~(I915_CONTEXT_SSEU_FLAG_ENGINE_INDEX))
		वापस -EINVAL;

	lookup = 0;
	अगर (user_sseu.flags & I915_CONTEXT_SSEU_FLAG_ENGINE_INDEX)
		lookup |= LOOKUP_USER_INDEX;

	ce = lookup_user_engine(ctx, lookup, &user_sseu.engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	/* Only render engine supports RPCS configuration. */
	अगर (ce->engine->class != RENDER_CLASS) अणु
		ret = -ENODEV;
		जाओ out_ce;
	पूर्ण

	ret = i915_gem_user_to_context_sseu(ce->engine->gt, &user_sseu, &sseu);
	अगर (ret)
		जाओ out_ce;

	ret = पूर्णांकel_context_reconfigure_sseu(ce, sseu);
	अगर (ret)
		जाओ out_ce;

	args->size = माप(user_sseu);

out_ce:
	पूर्णांकel_context_put(ce);
	वापस ret;
पूर्ण

काष्ठा set_engines अणु
	काष्ठा i915_gem_context *ctx;
	काष्ठा i915_gem_engines *engines;
पूर्ण;

अटल पूर्णांक
set_engines__load_balance(काष्ठा i915_user_extension __user *base, व्योम *data)
अणु
	काष्ठा i915_context_engines_load_balance __user *ext =
		container_of_user(base, typeof(*ext), base);
	स्थिर काष्ठा set_engines *set = data;
	काष्ठा drm_i915_निजी *i915 = set->ctx->i915;
	काष्ठा पूर्णांकel_engine_cs *stack[16];
	काष्ठा पूर्णांकel_engine_cs **siblings;
	काष्ठा पूर्णांकel_context *ce;
	u16 num_siblings, idx;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	अगर (!HAS_EXECLISTS(i915))
		वापस -ENODEV;

	अगर (पूर्णांकel_uc_uses_guc_submission(&i915->gt.uc))
		वापस -ENODEV; /* not implement yet */

	अगर (get_user(idx, &ext->engine_index))
		वापस -EFAULT;

	अगर (idx >= set->engines->num_engines) अणु
		drm_dbg(&i915->drm, "Invalid placement value, %d >= %d\n",
			idx, set->engines->num_engines);
		वापस -EINVAL;
	पूर्ण

	idx = array_index_nospec(idx, set->engines->num_engines);
	अगर (set->engines->engines[idx]) अणु
		drm_dbg(&i915->drm,
			"Invalid placement[%d], already occupied\n", idx);
		वापस -EEXIST;
	पूर्ण

	अगर (get_user(num_siblings, &ext->num_siblings))
		वापस -EFAULT;

	err = check_user_mbz(&ext->flags);
	अगर (err)
		वापस err;

	err = check_user_mbz(&ext->mbz64);
	अगर (err)
		वापस err;

	siblings = stack;
	अगर (num_siblings > ARRAY_SIZE(stack)) अणु
		siblings = kदो_स्मृति_array(num_siblings,
					 माप(*siblings),
					 GFP_KERNEL);
		अगर (!siblings)
			वापस -ENOMEM;
	पूर्ण

	क्रम (n = 0; n < num_siblings; n++) अणु
		काष्ठा i915_engine_class_instance ci;

		अगर (copy_from_user(&ci, &ext->engines[n], माप(ci))) अणु
			err = -EFAULT;
			जाओ out_siblings;
		पूर्ण

		siblings[n] = पूर्णांकel_engine_lookup_user(i915,
						       ci.engine_class,
						       ci.engine_instance);
		अगर (!siblings[n]) अणु
			drm_dbg(&i915->drm,
				"Invalid sibling[%d]: { class:%d, inst:%d }\n",
				n, ci.engine_class, ci.engine_instance);
			err = -EINVAL;
			जाओ out_siblings;
		पूर्ण
	पूर्ण

	ce = पूर्णांकel_execlists_create_भव(siblings, n);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out_siblings;
	पूर्ण

	पूर्णांकel_context_set_gem(ce, set->ctx);

	अगर (cmpxchg(&set->engines->engines[idx], शून्य, ce)) अणु
		पूर्णांकel_context_put(ce);
		err = -EEXIST;
		जाओ out_siblings;
	पूर्ण

out_siblings:
	अगर (siblings != stack)
		kमुक्त(siblings);

	वापस err;
पूर्ण

अटल पूर्णांक
set_engines__bond(काष्ठा i915_user_extension __user *base, व्योम *data)
अणु
	काष्ठा i915_context_engines_bond __user *ext =
		container_of_user(base, typeof(*ext), base);
	स्थिर काष्ठा set_engines *set = data;
	काष्ठा drm_i915_निजी *i915 = set->ctx->i915;
	काष्ठा i915_engine_class_instance ci;
	काष्ठा पूर्णांकel_engine_cs *भव;
	काष्ठा पूर्णांकel_engine_cs *master;
	u16 idx, num_bonds;
	पूर्णांक err, n;

	अगर (get_user(idx, &ext->भव_index))
		वापस -EFAULT;

	अगर (idx >= set->engines->num_engines) अणु
		drm_dbg(&i915->drm,
			"Invalid index for virtual engine: %d >= %d\n",
			idx, set->engines->num_engines);
		वापस -EINVAL;
	पूर्ण

	idx = array_index_nospec(idx, set->engines->num_engines);
	अगर (!set->engines->engines[idx]) अणु
		drm_dbg(&i915->drm, "Invalid engine at %d\n", idx);
		वापस -EINVAL;
	पूर्ण
	भव = set->engines->engines[idx]->engine;

	err = check_user_mbz(&ext->flags);
	अगर (err)
		वापस err;

	क्रम (n = 0; n < ARRAY_SIZE(ext->mbz64); n++) अणु
		err = check_user_mbz(&ext->mbz64[n]);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (copy_from_user(&ci, &ext->master, माप(ci)))
		वापस -EFAULT;

	master = पूर्णांकel_engine_lookup_user(i915,
					  ci.engine_class, ci.engine_instance);
	अगर (!master) अणु
		drm_dbg(&i915->drm,
			"Unrecognised master engine: { class:%u, instance:%u }\n",
			ci.engine_class, ci.engine_instance);
		वापस -EINVAL;
	पूर्ण

	अगर (get_user(num_bonds, &ext->num_bonds))
		वापस -EFAULT;

	क्रम (n = 0; n < num_bonds; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *bond;

		अगर (copy_from_user(&ci, &ext->engines[n], माप(ci)))
			वापस -EFAULT;

		bond = पूर्णांकel_engine_lookup_user(i915,
						ci.engine_class,
						ci.engine_instance);
		अगर (!bond) अणु
			drm_dbg(&i915->drm,
				"Unrecognised engine[%d] for bonding: { class:%d, instance: %d }\n",
				n, ci.engine_class, ci.engine_instance);
			वापस -EINVAL;
		पूर्ण

		/*
		 * A non-भव engine has no siblings to choose between; and
		 * a submit fence will always be directed to the one engine.
		 */
		अगर (पूर्णांकel_engine_is_भव(भव)) अणु
			err = पूर्णांकel_भव_engine_attach_bond(भव,
							       master,
							       bond);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर i915_user_extension_fn set_engines__extensions[] = अणु
	[I915_CONTEXT_ENGINES_EXT_LOAD_BALANCE] = set_engines__load_balance,
	[I915_CONTEXT_ENGINES_EXT_BOND] = set_engines__bond,
पूर्ण;

अटल पूर्णांक
set_engines(काष्ठा i915_gem_context *ctx,
	    स्थिर काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा i915_context_param_engines __user *user =
		u64_to_user_ptr(args->value);
	काष्ठा set_engines set = अणु .ctx = ctx पूर्ण;
	अचिन्हित पूर्णांक num_engines, n;
	u64 extensions;
	पूर्णांक err;

	अगर (!args->size) अणु /* चयन back to legacy user_ring_map */
		अगर (!i915_gem_context_user_engines(ctx))
			वापस 0;

		set.engines = शेष_engines(ctx);
		अगर (IS_ERR(set.engines))
			वापस PTR_ERR(set.engines);

		जाओ replace;
	पूर्ण

	BUILD_BUG_ON(!IS_ALIGNED(माप(*user), माप(*user->engines)));
	अगर (args->size < माप(*user) ||
	    !IS_ALIGNED(args->size, माप(*user->engines))) अणु
		drm_dbg(&i915->drm, "Invalid size for engine array: %d\n",
			args->size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Note that I915_EXEC_RING_MASK limits execbuf to only using the
	 * first 64 engines defined here.
	 */
	num_engines = (args->size - माप(*user)) / माप(*user->engines);
	set.engines = alloc_engines(num_engines);
	अगर (!set.engines)
		वापस -ENOMEM;

	क्रम (n = 0; n < num_engines; n++) अणु
		काष्ठा i915_engine_class_instance ci;
		काष्ठा पूर्णांकel_engine_cs *engine;
		काष्ठा पूर्णांकel_context *ce;

		अगर (copy_from_user(&ci, &user->engines[n], माप(ci))) अणु
			__मुक्त_engines(set.engines, n);
			वापस -EFAULT;
		पूर्ण

		अगर (ci.engine_class == (u16)I915_ENGINE_CLASS_INVALID &&
		    ci.engine_instance == (u16)I915_ENGINE_CLASS_INVALID_NONE) अणु
			set.engines->engines[n] = शून्य;
			जारी;
		पूर्ण

		engine = पूर्णांकel_engine_lookup_user(ctx->i915,
						  ci.engine_class,
						  ci.engine_instance);
		अगर (!engine) अणु
			drm_dbg(&i915->drm,
				"Invalid engine[%d]: { class:%d, instance:%d }\n",
				n, ci.engine_class, ci.engine_instance);
			__मुक्त_engines(set.engines, n);
			वापस -ENOENT;
		पूर्ण

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			__मुक्त_engines(set.engines, n);
			वापस PTR_ERR(ce);
		पूर्ण

		पूर्णांकel_context_set_gem(ce, ctx);

		set.engines->engines[n] = ce;
	पूर्ण
	set.engines->num_engines = num_engines;

	err = -EFAULT;
	अगर (!get_user(extensions, &user->extensions))
		err = i915_user_extensions(u64_to_user_ptr(extensions),
					   set_engines__extensions,
					   ARRAY_SIZE(set_engines__extensions),
					   &set);
	अगर (err) अणु
		मुक्त_engines(set.engines);
		वापस err;
	पूर्ण

replace:
	mutex_lock(&ctx->engines_mutex);
	अगर (i915_gem_context_is_बंदd(ctx)) अणु
		mutex_unlock(&ctx->engines_mutex);
		मुक्त_engines(set.engines);
		वापस -ENOENT;
	पूर्ण
	अगर (args->size)
		i915_gem_context_set_user_engines(ctx);
	अन्यथा
		i915_gem_context_clear_user_engines(ctx);
	set.engines = rcu_replace_poपूर्णांकer(ctx->engines, set.engines, 1);
	mutex_unlock(&ctx->engines_mutex);

	/* Keep track of old engine sets क्रम समाप्त_context() */
	engines_idle_release(ctx, set.engines);

	वापस 0;
पूर्ण

अटल पूर्णांक
get_engines(काष्ठा i915_gem_context *ctx,
	    काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा i915_context_param_engines __user *user;
	काष्ठा i915_gem_engines *e;
	माप_प्रकार n, count, size;
	bool user_engines;
	पूर्णांक err = 0;

	e = __context_engines_aरुको(ctx, &user_engines);
	अगर (!e)
		वापस -ENOENT;

	अगर (!user_engines) अणु
		i915_sw_fence_complete(&e->fence);
		args->size = 0;
		वापस 0;
	पूर्ण

	count = e->num_engines;

	/* Be paranoid in हाल we have an impedance mismatch */
	अगर (!check_काष्ठा_size(user, engines, count, &size)) अणु
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण
	अगर (overflows_type(size, args->size)) अणु
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	अगर (!args->size) अणु
		args->size = size;
		जाओ err_मुक्त;
	पूर्ण

	अगर (args->size < size) अणु
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	user = u64_to_user_ptr(args->value);
	अगर (put_user(0, &user->extensions)) अणु
		err = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	क्रम (n = 0; n < count; n++) अणु
		काष्ठा i915_engine_class_instance ci = अणु
			.engine_class = I915_ENGINE_CLASS_INVALID,
			.engine_instance = I915_ENGINE_CLASS_INVALID_NONE,
		पूर्ण;

		अगर (e->engines[n]) अणु
			ci.engine_class = e->engines[n]->engine->uabi_class;
			ci.engine_instance = e->engines[n]->engine->uabi_instance;
		पूर्ण

		अगर (copy_to_user(&user->engines[n], &ci, माप(ci))) अणु
			err = -EFAULT;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	args->size = size;

err_मुक्त:
	i915_sw_fence_complete(&e->fence);
	वापस err;
पूर्ण

अटल पूर्णांक
set_persistence(काष्ठा i915_gem_context *ctx,
		स्थिर काष्ठा drm_i915_gem_context_param *args)
अणु
	अगर (args->size)
		वापस -EINVAL;

	वापस __context_set_persistence(ctx, args->value);
पूर्ण

अटल पूर्णांक __apply_priority(काष्ठा पूर्णांकel_context *ce, व्योम *arg)
अणु
	काष्ठा i915_gem_context *ctx = arg;

	अगर (!पूर्णांकel_engine_has_बारlices(ce->engine))
		वापस 0;

	अगर (ctx->sched.priority >= I915_PRIORITY_NORMAL)
		पूर्णांकel_context_set_use_semaphores(ce);
	अन्यथा
		पूर्णांकel_context_clear_use_semaphores(ce);

	वापस 0;
पूर्ण

अटल पूर्णांक set_priority(काष्ठा i915_gem_context *ctx,
			स्थिर काष्ठा drm_i915_gem_context_param *args)
अणु
	s64 priority = args->value;

	अगर (args->size)
		वापस -EINVAL;

	अगर (!(ctx->i915->caps.scheduler & I915_SCHEDULER_CAP_PRIORITY))
		वापस -ENODEV;

	अगर (priority > I915_CONTEXT_MAX_USER_PRIORITY ||
	    priority < I915_CONTEXT_MIN_USER_PRIORITY)
		वापस -EINVAL;

	अगर (priority > I915_CONTEXT_DEFAULT_PRIORITY &&
	    !capable(CAP_SYS_NICE))
		वापस -EPERM;

	ctx->sched.priority = priority;
	context_apply_all(ctx, __apply_priority, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक ctx_setparam(काष्ठा drm_i915_file_निजी *fpriv,
			काष्ठा i915_gem_context *ctx,
			काष्ठा drm_i915_gem_context_param *args)
अणु
	पूर्णांक ret = 0;

	चयन (args->param) अणु
	हाल I915_CONTEXT_PARAM_NO_ZEROMAP:
		अगर (args->size)
			ret = -EINVAL;
		अन्यथा अगर (args->value)
			set_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags);
		अन्यथा
			clear_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags);
		अवरोध;

	हाल I915_CONTEXT_PARAM_NO_ERROR_CAPTURE:
		अगर (args->size)
			ret = -EINVAL;
		अन्यथा अगर (args->value)
			i915_gem_context_set_no_error_capture(ctx);
		अन्यथा
			i915_gem_context_clear_no_error_capture(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_BANNABLE:
		अगर (args->size)
			ret = -EINVAL;
		अन्यथा अगर (!capable(CAP_SYS_ADMIN) && !args->value)
			ret = -EPERM;
		अन्यथा अगर (args->value)
			i915_gem_context_set_bannable(ctx);
		अन्यथा
			i915_gem_context_clear_bannable(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_RECOVERABLE:
		अगर (args->size)
			ret = -EINVAL;
		अन्यथा अगर (args->value)
			i915_gem_context_set_recoverable(ctx);
		अन्यथा
			i915_gem_context_clear_recoverable(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_PRIORITY:
		ret = set_priority(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_SSEU:
		ret = set_sseu(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_VM:
		ret = set_ppgtt(fpriv, ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_ENGINES:
		ret = set_engines(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_PERSISTENCE:
		ret = set_persistence(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_RINGSIZE:
		ret = set_ringsize(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_BAN_PERIOD:
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा create_ext अणु
	काष्ठा i915_gem_context *ctx;
	काष्ठा drm_i915_file_निजी *fpriv;
पूर्ण;

अटल पूर्णांक create_setparam(काष्ठा i915_user_extension __user *ext, व्योम *data)
अणु
	काष्ठा drm_i915_gem_context_create_ext_setparam local;
	स्थिर काष्ठा create_ext *arg = data;

	अगर (copy_from_user(&local, ext, माप(local)))
		वापस -EFAULT;

	अगर (local.param.ctx_id)
		वापस -EINVAL;

	वापस ctx_setparam(arg->fpriv, arg->ctx, &local.param);
पूर्ण

अटल पूर्णांक copy_ring_size(काष्ठा पूर्णांकel_context *dst,
			  काष्ठा पूर्णांकel_context *src)
अणु
	दीर्घ sz;

	sz = पूर्णांकel_context_get_ring_size(src);
	अगर (sz < 0)
		वापस sz;

	वापस पूर्णांकel_context_set_ring_size(dst, sz);
पूर्ण

अटल पूर्णांक clone_engines(काष्ठा i915_gem_context *dst,
			 काष्ठा i915_gem_context *src)
अणु
	काष्ठा i915_gem_engines *clone, *e;
	bool user_engines;
	अचिन्हित दीर्घ n;

	e = __context_engines_aरुको(src, &user_engines);
	अगर (!e)
		वापस -ENOENT;

	clone = alloc_engines(e->num_engines);
	अगर (!clone)
		जाओ err_unlock;

	क्रम (n = 0; n < e->num_engines; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;

		अगर (!e->engines[n]) अणु
			clone->engines[n] = शून्य;
			जारी;
		पूर्ण
		engine = e->engines[n]->engine;

		/*
		 * Virtual engines are singletons; they can only exist
		 * inside a single context, because they embed their
		 * HW context... As each भव context implies a single
		 * समयline (each engine can only dequeue a single request
		 * at any समय), it would be surprising क्रम two contexts
		 * to use the same engine. So let's create a copy of
		 * the भव engine instead.
		 */
		अगर (पूर्णांकel_engine_is_भव(engine))
			clone->engines[n] =
				पूर्णांकel_execlists_clone_भव(engine);
		अन्यथा
			clone->engines[n] = पूर्णांकel_context_create(engine);
		अगर (IS_ERR_OR_शून्य(clone->engines[n])) अणु
			__मुक्त_engines(clone, n);
			जाओ err_unlock;
		पूर्ण

		पूर्णांकel_context_set_gem(clone->engines[n], dst);

		/* Copy across the preferred ringsize */
		अगर (copy_ring_size(clone->engines[n], e->engines[n])) अणु
			__मुक्त_engines(clone, n + 1);
			जाओ err_unlock;
		पूर्ण
	पूर्ण
	clone->num_engines = n;
	i915_sw_fence_complete(&e->fence);

	/* Serialised by स्थिरructor */
	engines_idle_release(dst, rcu_replace_poपूर्णांकer(dst->engines, clone, 1));
	अगर (user_engines)
		i915_gem_context_set_user_engines(dst);
	अन्यथा
		i915_gem_context_clear_user_engines(dst);
	वापस 0;

err_unlock:
	i915_sw_fence_complete(&e->fence);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक clone_flags(काष्ठा i915_gem_context *dst,
		       काष्ठा i915_gem_context *src)
अणु
	dst->user_flags = src->user_flags;
	वापस 0;
पूर्ण

अटल पूर्णांक clone_schedattr(काष्ठा i915_gem_context *dst,
			   काष्ठा i915_gem_context *src)
अणु
	dst->sched = src->sched;
	वापस 0;
पूर्ण

अटल पूर्णांक clone_sseu(काष्ठा i915_gem_context *dst,
		      काष्ठा i915_gem_context *src)
अणु
	काष्ठा i915_gem_engines *e = i915_gem_context_lock_engines(src);
	काष्ठा i915_gem_engines *clone;
	अचिन्हित दीर्घ n;
	पूर्णांक err;

	/* no locking required; sole access under स्थिरructor*/
	clone = __context_engines_अटल(dst);
	अगर (e->num_engines != clone->num_engines) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	क्रम (n = 0; n < e->num_engines; n++) अणु
		काष्ठा पूर्णांकel_context *ce = e->engines[n];

		अगर (clone->engines[n]->engine->class != ce->engine->class) अणु
			/* Must have compatible engine maps! */
			err = -EINVAL;
			जाओ unlock;
		पूर्ण

		/* serialises with set_sseu */
		err = पूर्णांकel_context_lock_pinned(ce);
		अगर (err)
			जाओ unlock;

		clone->engines[n]->sseu = ce->sseu;
		पूर्णांकel_context_unlock_pinned(ce);
	पूर्ण

	err = 0;
unlock:
	i915_gem_context_unlock_engines(src);
	वापस err;
पूर्ण

अटल पूर्णांक clone_समयline(काष्ठा i915_gem_context *dst,
			  काष्ठा i915_gem_context *src)
अणु
	अगर (src->समयline)
		__assign_समयline(dst, src->समयline);

	वापस 0;
पूर्ण

अटल पूर्णांक clone_vm(काष्ठा i915_gem_context *dst,
		    काष्ठा i915_gem_context *src)
अणु
	काष्ठा i915_address_space *vm;
	पूर्णांक err = 0;

	अगर (!rcu_access_poपूर्णांकer(src->vm))
		वापस 0;

	rcu_पढ़ो_lock();
	vm = context_get_vm_rcu(src);
	rcu_पढ़ो_unlock();

	अगर (!mutex_lock_पूर्णांकerruptible(&dst->mutex)) अणु
		__assign_ppgtt(dst, vm);
		mutex_unlock(&dst->mutex);
	पूर्ण अन्यथा अणु
		err = -EINTR;
	पूर्ण

	i915_vm_put(vm);
	वापस err;
पूर्ण

अटल पूर्णांक create_clone(काष्ठा i915_user_extension __user *ext, व्योम *data)
अणु
	अटल पूर्णांक (* स्थिर fn[])(काष्ठा i915_gem_context *dst,
				  काष्ठा i915_gem_context *src) = अणु
#घोषणा MAP(x, y) [ilog2(I915_CONTEXT_CLONE_##x)] = y
		MAP(ENGINES, clone_engines),
		MAP(FLAGS, clone_flags),
		MAP(SCHEDATTR, clone_schedattr),
		MAP(SSEU, clone_sseu),
		MAP(TIMELINE, clone_समयline),
		MAP(VM, clone_vm),
#अघोषित MAP
	पूर्ण;
	काष्ठा drm_i915_gem_context_create_ext_clone local;
	स्थिर काष्ठा create_ext *arg = data;
	काष्ठा i915_gem_context *dst = arg->ctx;
	काष्ठा i915_gem_context *src;
	पूर्णांक err, bit;

	अगर (copy_from_user(&local, ext, माप(local)))
		वापस -EFAULT;

	BUILD_BUG_ON(GENMASK(BITS_PER_TYPE(local.flags) - 1, ARRAY_SIZE(fn)) !=
		     I915_CONTEXT_CLONE_UNKNOWN);

	अगर (local.flags & I915_CONTEXT_CLONE_UNKNOWN)
		वापस -EINVAL;

	अगर (local.rsvd)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	src = __i915_gem_context_lookup_rcu(arg->fpriv, local.clone_id);
	rcu_पढ़ो_unlock();
	अगर (!src)
		वापस -ENOENT;

	GEM_BUG_ON(src == dst);

	क्रम (bit = 0; bit < ARRAY_SIZE(fn); bit++) अणु
		अगर (!(local.flags & BIT(bit)))
			जारी;

		err = fn[bit](dst, src);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर i915_user_extension_fn create_extensions[] = अणु
	[I915_CONTEXT_CREATE_EXT_SETPARAM] = create_setparam,
	[I915_CONTEXT_CREATE_EXT_CLONE] = create_clone,
पूर्ण;

अटल bool client_is_banned(काष्ठा drm_i915_file_निजी *file_priv)
अणु
	वापस atomic_पढ़ो(&file_priv->ban_score) >= I915_CLIENT_SCORE_BANNED;
पूर्ण

पूर्णांक i915_gem_context_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_context_create_ext *args = data;
	काष्ठा create_ext ext_data;
	पूर्णांक ret;
	u32 id;

	अगर (!DRIVER_CAPS(i915)->has_logical_contexts)
		वापस -ENODEV;

	अगर (args->flags & I915_CONTEXT_CREATE_FLAGS_UNKNOWN)
		वापस -EINVAL;

	ret = पूर्णांकel_gt_terminally_wedged(&i915->gt);
	अगर (ret)
		वापस ret;

	ext_data.fpriv = file->driver_priv;
	अगर (client_is_banned(ext_data.fpriv)) अणु
		drm_dbg(&i915->drm,
			"client %s[%d] banned from creating ctx\n",
			current->comm, task_pid_nr(current));
		वापस -EIO;
	पूर्ण

	ext_data.ctx = i915_gem_create_context(i915, args->flags);
	अगर (IS_ERR(ext_data.ctx))
		वापस PTR_ERR(ext_data.ctx);

	अगर (args->flags & I915_CONTEXT_CREATE_FLAGS_USE_EXTENSIONS) अणु
		ret = i915_user_extensions(u64_to_user_ptr(args->extensions),
					   create_extensions,
					   ARRAY_SIZE(create_extensions),
					   &ext_data);
		अगर (ret)
			जाओ err_ctx;
	पूर्ण

	ret = gem_context_रेजिस्टर(ext_data.ctx, ext_data.fpriv, &id);
	अगर (ret < 0)
		जाओ err_ctx;

	args->ctx_id = id;
	drm_dbg(&i915->drm, "HW context %d created\n", args->ctx_id);

	वापस 0;

err_ctx:
	context_बंद(ext_data.ctx);
	वापस ret;
पूर्ण

पूर्णांक i915_gem_context_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_context_destroy *args = data;
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा i915_gem_context *ctx;

	अगर (args->pad != 0)
		वापस -EINVAL;

	अगर (!args->ctx_id)
		वापस -ENOENT;

	ctx = xa_erase(&file_priv->context_xa, args->ctx_id);
	अगर (!ctx)
		वापस -ENOENT;

	context_बंद(ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक get_sseu(काष्ठा i915_gem_context *ctx,
		    काष्ठा drm_i915_gem_context_param *args)
अणु
	काष्ठा drm_i915_gem_context_param_sseu user_sseu;
	काष्ठा पूर्णांकel_context *ce;
	अचिन्हित दीर्घ lookup;
	पूर्णांक err;

	अगर (args->size == 0)
		जाओ out;
	अन्यथा अगर (args->size < माप(user_sseu))
		वापस -EINVAL;

	अगर (copy_from_user(&user_sseu, u64_to_user_ptr(args->value),
			   माप(user_sseu)))
		वापस -EFAULT;

	अगर (user_sseu.rsvd)
		वापस -EINVAL;

	अगर (user_sseu.flags & ~(I915_CONTEXT_SSEU_FLAG_ENGINE_INDEX))
		वापस -EINVAL;

	lookup = 0;
	अगर (user_sseu.flags & I915_CONTEXT_SSEU_FLAG_ENGINE_INDEX)
		lookup |= LOOKUP_USER_INDEX;

	ce = lookup_user_engine(ctx, lookup, &user_sseu.engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = पूर्णांकel_context_lock_pinned(ce); /* serialises with set_sseu */
	अगर (err) अणु
		पूर्णांकel_context_put(ce);
		वापस err;
	पूर्ण

	user_sseu.slice_mask = ce->sseu.slice_mask;
	user_sseu.subslice_mask = ce->sseu.subslice_mask;
	user_sseu.min_eus_per_subslice = ce->sseu.min_eus_per_subslice;
	user_sseu.max_eus_per_subslice = ce->sseu.max_eus_per_subslice;

	पूर्णांकel_context_unlock_pinned(ce);
	पूर्णांकel_context_put(ce);

	अगर (copy_to_user(u64_to_user_ptr(args->value), &user_sseu,
			 माप(user_sseu)))
		वापस -EFAULT;

out:
	args->size = माप(user_sseu);

	वापस 0;
पूर्ण

पूर्णांक i915_gem_context_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा drm_i915_gem_context_param *args = data;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक ret = 0;

	ctx = i915_gem_context_lookup(file_priv, args->ctx_id);
	अगर (!ctx)
		वापस -ENOENT;

	चयन (args->param) अणु
	हाल I915_CONTEXT_PARAM_NO_ZEROMAP:
		args->size = 0;
		args->value = test_bit(UCONTEXT_NO_ZEROMAP, &ctx->user_flags);
		अवरोध;

	हाल I915_CONTEXT_PARAM_GTT_SIZE:
		args->size = 0;
		rcu_पढ़ो_lock();
		अगर (rcu_access_poपूर्णांकer(ctx->vm))
			args->value = rcu_dereference(ctx->vm)->total;
		अन्यथा
			args->value = to_i915(dev)->ggtt.vm.total;
		rcu_पढ़ो_unlock();
		अवरोध;

	हाल I915_CONTEXT_PARAM_NO_ERROR_CAPTURE:
		args->size = 0;
		args->value = i915_gem_context_no_error_capture(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_BANNABLE:
		args->size = 0;
		args->value = i915_gem_context_is_bannable(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_RECOVERABLE:
		args->size = 0;
		args->value = i915_gem_context_is_recoverable(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_PRIORITY:
		args->size = 0;
		args->value = ctx->sched.priority;
		अवरोध;

	हाल I915_CONTEXT_PARAM_SSEU:
		ret = get_sseu(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_VM:
		ret = get_ppgtt(file_priv, ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_ENGINES:
		ret = get_engines(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_PERSISTENCE:
		args->size = 0;
		args->value = i915_gem_context_is_persistent(ctx);
		अवरोध;

	हाल I915_CONTEXT_PARAM_RINGSIZE:
		ret = get_ringsize(ctx, args);
		अवरोध;

	हाल I915_CONTEXT_PARAM_BAN_PERIOD:
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	i915_gem_context_put(ctx);
	वापस ret;
पूर्ण

पूर्णांक i915_gem_context_setparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा drm_i915_gem_context_param *args = data;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक ret;

	ctx = i915_gem_context_lookup(file_priv, args->ctx_id);
	अगर (!ctx)
		वापस -ENOENT;

	ret = ctx_setparam(file_priv, ctx, args);

	i915_gem_context_put(ctx);
	वापस ret;
पूर्ण

पूर्णांक i915_gem_context_reset_stats_ioctl(काष्ठा drm_device *dev,
				       व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_reset_stats *args = data;
	काष्ठा i915_gem_context *ctx;
	पूर्णांक ret;

	अगर (args->flags || args->pad)
		वापस -EINVAL;

	ret = -ENOENT;
	rcu_पढ़ो_lock();
	ctx = __i915_gem_context_lookup_rcu(file->driver_priv, args->ctx_id);
	अगर (!ctx)
		जाओ out;

	/*
	 * We opt क्रम unserialised पढ़ोs here. This may result in tearing
	 * in the extremely unlikely event of a GPU hang on this context
	 * as we are querying them. If we need that extra layer of protection,
	 * we should wrap the hangstats with a seqlock.
	 */

	अगर (capable(CAP_SYS_ADMIN))
		args->reset_count = i915_reset_count(&i915->gpu_error);
	अन्यथा
		args->reset_count = 0;

	args->batch_active = atomic_पढ़ो(&ctx->guilty_count);
	args->batch_pending = atomic_पढ़ो(&ctx->active_count);

	ret = 0;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/* GEM context-engines iterator: क्रम_each_gem_engine() */
काष्ठा पूर्णांकel_context *
i915_gem_engines_iter_next(काष्ठा i915_gem_engines_iter *it)
अणु
	स्थिर काष्ठा i915_gem_engines *e = it->engines;
	काष्ठा पूर्णांकel_context *ctx;

	अगर (unlikely(!e))
		वापस शून्य;

	करो अणु
		अगर (it->idx >= e->num_engines)
			वापस शून्य;

		ctx = e->engines[it->idx++];
	पूर्ण जबतक (!ctx);

	वापस ctx;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_context.c"
#समावेश "selftests/i915_gem_context.c"
#पूर्ण_अगर

अटल व्योम i915_global_gem_context_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_luts);
पूर्ण

अटल व्योम i915_global_gem_context_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_luts);
पूर्ण

अटल काष्ठा i915_global_gem_context global = अणु अणु
	.shrink = i915_global_gem_context_shrink,
	.निकास = i915_global_gem_context_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_gem_context_init(व्योम)
अणु
	global.slab_luts = KMEM_CACHE(i915_lut_handle, 0);
	अगर (!global.slab_luts)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण
