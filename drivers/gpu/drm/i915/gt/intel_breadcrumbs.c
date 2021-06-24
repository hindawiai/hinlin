<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2015-2021 Intel Corporation
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <trace/events/dma_fence.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"

अटल bool irq_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!engine->irq_enable)
		वापस false;

	/* Caller disables पूर्णांकerrupts */
	spin_lock(&engine->gt->irq_lock);
	engine->irq_enable(engine);
	spin_unlock(&engine->gt->irq_lock);

	वापस true;
पूर्ण

अटल व्योम irq_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!engine->irq_disable)
		वापस;

	/* Caller disables पूर्णांकerrupts */
	spin_lock(&engine->gt->irq_lock);
	engine->irq_disable(engine);
	spin_unlock(&engine->gt->irq_lock);
पूर्ण

अटल व्योम __पूर्णांकel_bपढ़ोcrumbs_arm_irq(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	/*
	 * Since we are रुकोing on a request, the GPU should be busy
	 * and should have its own rpm reference.
	 */
	अगर (GEM_WARN_ON(!पूर्णांकel_gt_pm_get_अगर_awake(b->irq_engine->gt)))
		वापस;

	/*
	 * The bपढ़ोcrumb irq will be disarmed on the पूर्णांकerrupt after the
	 * रुकोers are संकेतed. This gives us a single पूर्णांकerrupt winकरोw in
	 * which we can add a new रुकोer and aव्योम the cost of re-enabling
	 * the irq.
	 */
	WRITE_ONCE(b->irq_armed, true);

	/* Requests may have completed beक्रमe we could enable the पूर्णांकerrupt. */
	अगर (!b->irq_enabled++ && irq_enable(b->irq_engine))
		irq_work_queue(&b->irq_work);
पूर्ण

अटल व्योम पूर्णांकel_bपढ़ोcrumbs_arm_irq(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	अगर (!b->irq_engine)
		वापस;

	spin_lock(&b->irq_lock);
	अगर (!b->irq_armed)
		__पूर्णांकel_bपढ़ोcrumbs_arm_irq(b);
	spin_unlock(&b->irq_lock);
पूर्ण

अटल व्योम __पूर्णांकel_bपढ़ोcrumbs_disarm_irq(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	GEM_BUG_ON(!b->irq_enabled);
	अगर (!--b->irq_enabled)
		irq_disable(b->irq_engine);

	WRITE_ONCE(b->irq_armed, false);
	पूर्णांकel_gt_pm_put_async(b->irq_engine->gt);
पूर्ण

अटल व्योम पूर्णांकel_bपढ़ोcrumbs_disarm_irq(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	spin_lock(&b->irq_lock);
	अगर (b->irq_armed)
		__पूर्णांकel_bपढ़ोcrumbs_disarm_irq(b);
	spin_unlock(&b->irq_lock);
पूर्ण

अटल व्योम add_संकेतing_context(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b,
				  काष्ठा पूर्णांकel_context *ce)
अणु
	lockdep_निश्चित_held(&ce->संकेत_lock);

	spin_lock(&b->संकेतers_lock);
	list_add_rcu(&ce->संकेत_link, &b->संकेतers);
	spin_unlock(&b->संकेतers_lock);
पूर्ण

अटल bool हटाओ_संकेतing_context(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b,
				     काष्ठा पूर्णांकel_context *ce)
अणु
	lockdep_निश्चित_held(&ce->संकेत_lock);

	अगर (!list_empty(&ce->संकेतs))
		वापस false;

	spin_lock(&b->संकेतers_lock);
	list_del_rcu(&ce->संकेत_link);
	spin_unlock(&b->संकेतers_lock);

	वापस true;
पूर्ण

__maybe_unused अटल bool
check_संकेत_order(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_request *rq)
अणु
	अगर (rq->context != ce)
		वापस false;

	अगर (!list_is_last(&rq->संकेत_link, &ce->संकेतs) &&
	    i915_seqno_passed(rq->fence.seqno,
			      list_next_entry(rq, संकेत_link)->fence.seqno))
		वापस false;

	अगर (!list_is_first(&rq->संकेत_link, &ce->संकेतs) &&
	    i915_seqno_passed(list_prev_entry(rq, संकेत_link)->fence.seqno,
			      rq->fence.seqno))
		वापस false;

	वापस true;
पूर्ण

अटल bool
__dma_fence_संकेत(काष्ठा dma_fence *fence)
अणु
	वापस !test_and_set_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags);
पूर्ण

अटल व्योम
__dma_fence_संकेत__बारtamp(काष्ठा dma_fence *fence, kसमय_प्रकार बारtamp)
अणु
	fence->बारtamp = बारtamp;
	set_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags);
	trace_dma_fence_संकेतed(fence);
पूर्ण

अटल व्योम
__dma_fence_संकेत__notअगरy(काष्ठा dma_fence *fence,
			   स्थिर काष्ठा list_head *list)
अणु
	काष्ठा dma_fence_cb *cur, *पंचांगp;

	lockdep_निश्चित_held(fence->lock);

	list_क्रम_each_entry_safe(cur, पंचांगp, list, node) अणु
		INIT_LIST_HEAD(&cur->node);
		cur->func(fence, cur);
	पूर्ण
पूर्ण

अटल व्योम add_retire(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b, काष्ठा पूर्णांकel_समयline *tl)
अणु
	अगर (b->irq_engine)
		पूर्णांकel_engine_add_retire(b->irq_engine, tl);
पूर्ण

अटल काष्ठा llist_node *
slist_add(काष्ठा llist_node *node, काष्ठा llist_node *head)
अणु
	node->next = head;
	वापस node;
पूर्ण

अटल व्योम संकेत_irq_work(काष्ठा irq_work *work)
अणु
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *b = container_of(work, typeof(*b), irq_work);
	स्थिर kसमय_प्रकार बारtamp = kसमय_get();
	काष्ठा llist_node *संकेत, *sn;
	काष्ठा पूर्णांकel_context *ce;

	संकेत = शून्य;
	अगर (unlikely(!llist_empty(&b->संकेतed_requests)))
		संकेत = llist_del_all(&b->संकेतed_requests);

	/*
	 * Keep the irq armed until the पूर्णांकerrupt after all listeners are gone.
	 *
	 * Enabling/disabling the पूर्णांकerrupt is rather costly, roughly a couple
	 * of hundred microseconds. If we are proactive and enable/disable
	 * the पूर्णांकerrupt around every request that wants a bपढ़ोcrumb, we
	 * quickly drown in the extra orders of magnitude of latency imposed
	 * on request submission.
	 *
	 * So we try to be lazy, and keep the पूर्णांकerrupts enabled until no
	 * more listeners appear within a bपढ़ोcrumb पूर्णांकerrupt पूर्णांकerval (that
	 * is until a request completes that no one cares about). The
	 * observation is that listeners come in batches, and will often
	 * listen to a bunch of requests in succession. Though note on icl+,
	 * पूर्णांकerrupts are always enabled due to concerns with rc6 being
	 * dysfunctional with per-engine पूर्णांकerrupt masking.
	 *
	 * We also try to aव्योम raising too many पूर्णांकerrupts, as they may
	 * be generated by userspace batches and it is unक्रमtunately rather
	 * too easy to drown the CPU under a flood of GPU पूर्णांकerrupts. Thus
	 * whenever no one appears to be listening, we turn off the पूर्णांकerrupts.
	 * Fewer पूर्णांकerrupts should conserve घातer -- at the very least, fewer
	 * पूर्णांकerrupt draw less ire from other users of the प्रणाली and tools
	 * like घातertop.
	 */
	अगर (!संकेत && READ_ONCE(b->irq_armed) && list_empty(&b->संकेतers))
		पूर्णांकel_bपढ़ोcrumbs_disarm_irq(b);

	rcu_पढ़ो_lock();
	atomic_inc(&b->संकेतer_active);
	list_क्रम_each_entry_rcu(ce, &b->संकेतers, संकेत_link) अणु
		काष्ठा i915_request *rq;

		list_क्रम_each_entry_rcu(rq, &ce->संकेतs, संकेत_link) अणु
			bool release;

			अगर (!__i915_request_is_complete(rq))
				अवरोध;

			अगर (!test_and_clear_bit(I915_FENCE_FLAG_SIGNAL,
						&rq->fence.flags))
				अवरोध;

			/*
			 * Queue क्रम execution after dropping the संकेतing
			 * spinlock as the callback chain may end up adding
			 * more संकेतers to the same context or engine.
			 */
			spin_lock(&ce->संकेत_lock);
			list_del_rcu(&rq->संकेत_link);
			release = हटाओ_संकेतing_context(b, ce);
			spin_unlock(&ce->संकेत_lock);
			अगर (release) अणु
				अगर (पूर्णांकel_समयline_is_last(ce->समयline, rq))
					add_retire(b, ce->समयline);
				पूर्णांकel_context_put(ce);
			पूर्ण

			अगर (__dma_fence_संकेत(&rq->fence))
				/* We own संकेत_node now, xfer to local list */
				संकेत = slist_add(&rq->संकेत_node, संकेत);
			अन्यथा
				i915_request_put(rq);
		पूर्ण
	पूर्ण
	atomic_dec(&b->संकेतer_active);
	rcu_पढ़ो_unlock();

	llist_क्रम_each_safe(संकेत, sn, संकेत) अणु
		काष्ठा i915_request *rq =
			llist_entry(संकेत, typeof(*rq), संकेत_node);
		काष्ठा list_head cb_list;

		spin_lock(&rq->lock);
		list_replace(&rq->fence.cb_list, &cb_list);
		__dma_fence_संकेत__बारtamp(&rq->fence, बारtamp);
		__dma_fence_संकेत__notअगरy(&rq->fence, &cb_list);
		spin_unlock(&rq->lock);

		i915_request_put(rq);
	पूर्ण

	अगर (!READ_ONCE(b->irq_armed) && !list_empty(&b->संकेतers))
		पूर्णांकel_bपढ़ोcrumbs_arm_irq(b);
पूर्ण

काष्ठा पूर्णांकel_bपढ़ोcrumbs *
पूर्णांकel_bपढ़ोcrumbs_create(काष्ठा पूर्णांकel_engine_cs *irq_engine)
अणु
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *b;

	b = kzalloc(माप(*b), GFP_KERNEL);
	अगर (!b)
		वापस शून्य;

	b->irq_engine = irq_engine;

	spin_lock_init(&b->संकेतers_lock);
	INIT_LIST_HEAD(&b->संकेतers);
	init_llist_head(&b->संकेतed_requests);

	spin_lock_init(&b->irq_lock);
	init_irq_work(&b->irq_work, संकेत_irq_work);

	वापस b;
पूर्ण

व्योम पूर्णांकel_bपढ़ोcrumbs_reset(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!b->irq_engine)
		वापस;

	spin_lock_irqsave(&b->irq_lock, flags);

	अगर (b->irq_enabled)
		irq_enable(b->irq_engine);
	अन्यथा
		irq_disable(b->irq_engine);

	spin_unlock_irqrestore(&b->irq_lock, flags);
पूर्ण

व्योम __पूर्णांकel_bपढ़ोcrumbs_park(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	अगर (!READ_ONCE(b->irq_armed))
		वापस;

	/* Kick the work once more to drain the संकेतers, and disarm the irq */
	irq_work_sync(&b->irq_work);
	जबतक (READ_ONCE(b->irq_armed) && !atomic_पढ़ो(&b->active)) अणु
		local_irq_disable();
		संकेत_irq_work(&b->irq_work);
		local_irq_enable();
		cond_resched();
	पूर्ण
पूर्ण

व्योम पूर्णांकel_bपढ़ोcrumbs_मुक्त(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	irq_work_sync(&b->irq_work);
	GEM_BUG_ON(!list_empty(&b->संकेतers));
	GEM_BUG_ON(b->irq_armed);
	kमुक्त(b);
पूर्ण

अटल व्योम irq_संकेत_request(काष्ठा i915_request *rq,
			       काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	अगर (!__dma_fence_संकेत(&rq->fence))
		वापस;

	i915_request_get(rq);
	अगर (llist_add(&rq->संकेत_node, &b->संकेतed_requests))
		irq_work_queue(&b->irq_work);
पूर्ण

अटल व्योम insert_bपढ़ोcrumb(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *b = READ_ONCE(rq->engine)->bपढ़ोcrumbs;
	काष्ठा पूर्णांकel_context *ce = rq->context;
	काष्ठा list_head *pos;

	अगर (test_bit(I915_FENCE_FLAG_SIGNAL, &rq->fence.flags))
		वापस;

	/*
	 * If the request is alपढ़ोy completed, we can transfer it
	 * straight onto a संकेतed list, and queue the irq worker क्रम
	 * its संकेत completion.
	 */
	अगर (__i915_request_is_complete(rq)) अणु
		irq_संकेत_request(rq, b);
		वापस;
	पूर्ण

	अगर (list_empty(&ce->संकेतs)) अणु
		पूर्णांकel_context_get(ce);
		add_संकेतing_context(b, ce);
		pos = &ce->संकेतs;
	पूर्ण अन्यथा अणु
		/*
		 * We keep the seqno in retirement order, so we can अवरोध
		 * inside पूर्णांकel_engine_संकेत_bपढ़ोcrumbs as soon as we've
		 * passed the last completed request (or seen a request that
		 * hasn't event started). We could walk the समयline->requests,
		 * but keeping a separate संकेतers_list has the advantage of
		 * hopefully being much smaller than the full list and so
		 * provides faster iteration and detection when there are no
		 * more पूर्णांकerrupts required क्रम this context.
		 *
		 * We typically expect to add new संकेतers in order, so we
		 * start looking क्रम our insertion poपूर्णांक from the tail of
		 * the list.
		 */
		list_क्रम_each_prev(pos, &ce->संकेतs) अणु
			काष्ठा i915_request *it =
				list_entry(pos, typeof(*it), संकेत_link);

			अगर (i915_seqno_passed(rq->fence.seqno, it->fence.seqno))
				अवरोध;
		पूर्ण
	पूर्ण

	i915_request_get(rq);
	list_add_rcu(&rq->संकेत_link, pos);
	GEM_BUG_ON(!check_संकेत_order(ce, rq));
	GEM_BUG_ON(test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags));
	set_bit(I915_FENCE_FLAG_SIGNAL, &rq->fence.flags);

	/*
	 * Defer enabling the पूर्णांकerrupt to after HW submission and recheck
	 * the request as it may have completed and उठाओd the पूर्णांकerrupt as
	 * we were attaching it पूर्णांकo the lists.
	 */
	irq_work_queue(&b->irq_work);
पूर्ण

bool i915_request_enable_bपढ़ोcrumb(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_context *ce = rq->context;

	/* Serialises with i915_request_retire() using rq->lock */
	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags))
		वापस true;

	/*
	 * Peek at i915_request_submit()/i915_request_unsubmit() status.
	 *
	 * If the request is not yet active (and not संकेतed), we will
	 * attach the bपढ़ोcrumb later.
	 */
	अगर (!test_bit(I915_FENCE_FLAG_ACTIVE, &rq->fence.flags))
		वापस true;

	spin_lock(&ce->संकेत_lock);
	अगर (test_bit(I915_FENCE_FLAG_ACTIVE, &rq->fence.flags))
		insert_bपढ़ोcrumb(rq);
	spin_unlock(&ce->संकेत_lock);

	वापस true;
पूर्ण

व्योम i915_request_cancel_bपढ़ोcrumb(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *b = READ_ONCE(rq->engine)->bपढ़ोcrumbs;
	काष्ठा पूर्णांकel_context *ce = rq->context;
	bool release;

	spin_lock(&ce->संकेत_lock);
	अगर (!test_and_clear_bit(I915_FENCE_FLAG_SIGNAL, &rq->fence.flags)) अणु
		spin_unlock(&ce->संकेत_lock);
		वापस;
	पूर्ण

	list_del_rcu(&rq->संकेत_link);
	release = हटाओ_संकेतing_context(b, ce);
	spin_unlock(&ce->संकेत_lock);
	अगर (release)
		पूर्णांकel_context_put(ce);

	अगर (__i915_request_is_complete(rq))
		irq_संकेत_request(rq, b);

	i915_request_put(rq);
पूर्ण

व्योम पूर्णांकel_context_हटाओ_bपढ़ोcrumbs(काष्ठा पूर्णांकel_context *ce,
				      काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	काष्ठा i915_request *rq, *rn;
	bool release = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ce->संकेत_lock, flags);

	अगर (list_empty(&ce->संकेतs))
		जाओ unlock;

	list_क्रम_each_entry_safe(rq, rn, &ce->संकेतs, संकेत_link) अणु
		GEM_BUG_ON(!__i915_request_is_complete(rq));
		अगर (!test_and_clear_bit(I915_FENCE_FLAG_SIGNAL,
					&rq->fence.flags))
			जारी;

		list_del_rcu(&rq->संकेत_link);
		irq_संकेत_request(rq, b);
		i915_request_put(rq);
	पूर्ण
	release = हटाओ_संकेतing_context(b, ce);

unlock:
	spin_unlock_irqrestore(&ce->संकेत_lock, flags);
	अगर (release)
		पूर्णांकel_context_put(ce);

	जबतक (atomic_पढ़ो(&b->संकेतer_active))
		cpu_relax();
पूर्ण

अटल व्योम prपूर्णांक_संकेतs(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b, काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;

	drm_म_लिखो(p, "Signals:\n");

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ce, &b->संकेतers, संकेत_link) अणु
		list_क्रम_each_entry_rcu(rq, &ce->संकेतs, संकेत_link)
			drm_म_लिखो(p, "\t[%llx:%llx%s] @ %dms\n",
				   rq->fence.context, rq->fence.seqno,
				   __i915_request_is_complete(rq) ? "!" :
				   __i915_request_has_started(rq) ? "*" :
				   "",
				   jअगरfies_to_msecs(jअगरfies - rq->emitted_jअगरfies));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम पूर्णांकel_engine_prपूर्णांक_bपढ़ोcrumbs(काष्ठा पूर्णांकel_engine_cs *engine,
				    काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *b;

	b = engine->bपढ़ोcrumbs;
	अगर (!b)
		वापस;

	drm_म_लिखो(p, "IRQ: %s\n", enableddisabled(b->irq_armed));
	अगर (!list_empty(&b->संकेतers))
		prपूर्णांक_संकेतs(b, p);
पूर्ण
