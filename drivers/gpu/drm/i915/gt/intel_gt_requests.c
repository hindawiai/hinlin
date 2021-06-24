<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/workqueue.h>

#समावेश "i915_drv.h" /* क्रम_each_engine() */
#समावेश "i915_request.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_execlists_submission.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_timeline.h"

अटल bool retire_requests(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा i915_request *rq, *rn;

	list_क्रम_each_entry_safe(rq, rn, &tl->requests, link)
		अगर (!i915_request_retire(rq))
			वापस false;

	/* And check nothing new was submitted */
	वापस !i915_active_fence_isset(&tl->last_request);
पूर्ण

अटल bool engine_active(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस !list_empty(&engine->kernel_context->समयline->requests);
पूर्ण

अटल bool flush_submission(काष्ठा पूर्णांकel_gt *gt, दीर्घ समयout)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	bool active = false;

	अगर (!समयout)
		वापस false;

	अगर (!पूर्णांकel_gt_pm_is_awake(gt))
		वापस false;

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांकel_engine_flush_submission(engine);

		/* Flush the background retirement and idle barriers */
		flush_work(&engine->retire_work);
		flush_delayed_work(&engine->wakeref.work);

		/* Is the idle barrier still outstanding? */
		active |= engine_active(engine);
	पूर्ण

	वापस active;
पूर्ण

अटल व्योम engine_retire(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(work, typeof(*engine), retire_work);
	काष्ठा पूर्णांकel_समयline *tl = xchg(&engine->retire, शून्य);

	करो अणु
		काष्ठा पूर्णांकel_समयline *next = xchg(&tl->retire, शून्य);

		/*
		 * Our goal here is to retire _idle_ समयlines as soon as
		 * possible (as they are idle, we करो not expect userspace
		 * to be cleaning up anyसमय soon).
		 *
		 * If the समयline is currently locked, either it is being
		 * retired अन्यथाwhere or about to be!
		 */
		अगर (mutex_trylock(&tl->mutex)) अणु
			retire_requests(tl);
			mutex_unlock(&tl->mutex);
		पूर्ण
		पूर्णांकel_समयline_put(tl);

		GEM_BUG_ON(!next);
		tl = ptr_mask_bits(next, 1);
	पूर्ण जबतक (tl);
पूर्ण

अटल bool add_retire(काष्ठा पूर्णांकel_engine_cs *engine,
		       काष्ठा पूर्णांकel_समयline *tl)
अणु
#घोषणा STUB ((काष्ठा पूर्णांकel_समयline *)1)
	काष्ठा पूर्णांकel_समयline *first;

	/*
	 * We खोलो-code a llist here to include the additional tag [BIT(0)]
	 * so that we know when the समयline is alपढ़ोy on a
	 * retirement queue: either this engine or another.
	 */

	अगर (cmpxchg(&tl->retire, शून्य, STUB)) /* alपढ़ोy queued */
		वापस false;

	पूर्णांकel_समयline_get(tl);
	first = READ_ONCE(engine->retire);
	करो
		tl->retire = ptr_pack_bits(first, 1, 1);
	जबतक (!try_cmpxchg(&engine->retire, &first, tl));

	वापस !first;
पूर्ण

व्योम पूर्णांकel_engine_add_retire(काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा पूर्णांकel_समयline *tl)
अणु
	/* We करोn't deal well with the engine disappearing beneath us */
	GEM_BUG_ON(पूर्णांकel_engine_is_भव(engine));

	अगर (add_retire(engine, tl))
		schedule_work(&engine->retire_work);
पूर्ण

व्योम पूर्णांकel_engine_init_retire(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	INIT_WORK(&engine->retire_work, engine_retire);
पूर्ण

व्योम पूर्णांकel_engine_fini_retire(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	flush_work(&engine->retire_work);
	GEM_BUG_ON(engine->retire);
पूर्ण

दीर्घ पूर्णांकel_gt_retire_requests_समयout(काष्ठा पूर्णांकel_gt *gt, दीर्घ समयout)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &gt->समयlines;
	काष्ठा पूर्णांकel_समयline *tl, *tn;
	अचिन्हित दीर्घ active_count = 0;
	LIST_HEAD(मुक्त);

	flush_submission(gt, समयout); /* kick the ksoftirqd tasklets */
	spin_lock(&समयlines->lock);
	list_क्रम_each_entry_safe(tl, tn, &समयlines->active_list, link) अणु
		अगर (!mutex_trylock(&tl->mutex)) अणु
			active_count++; /* report busy to caller, try again? */
			जारी;
		पूर्ण

		पूर्णांकel_समयline_get(tl);
		GEM_BUG_ON(!atomic_पढ़ो(&tl->active_count));
		atomic_inc(&tl->active_count); /* pin the list element */
		spin_unlock(&समयlines->lock);

		अगर (समयout > 0) अणु
			काष्ठा dma_fence *fence;

			fence = i915_active_fence_get(&tl->last_request);
			अगर (fence) अणु
				mutex_unlock(&tl->mutex);

				समयout = dma_fence_रुको_समयout(fence,
								 true,
								 समयout);
				dma_fence_put(fence);

				/* Retirement is best efक्रमt */
				अगर (!mutex_trylock(&tl->mutex)) अणु
					active_count++;
					जाओ out_active;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!retire_requests(tl))
			active_count++;
		mutex_unlock(&tl->mutex);

out_active:	spin_lock(&समयlines->lock);

		/* Resume list iteration after reacquiring spinlock */
		list_safe_reset_next(tl, tn, link);
		अगर (atomic_dec_and_test(&tl->active_count))
			list_del(&tl->link);

		/* Defer the final release to after the spinlock */
		अगर (refcount_dec_and_test(&tl->kref.refcount)) अणु
			GEM_BUG_ON(atomic_पढ़ो(&tl->active_count));
			list_add(&tl->link, &मुक्त);
		पूर्ण
	पूर्ण
	spin_unlock(&समयlines->lock);

	list_क्रम_each_entry_safe(tl, tn, &मुक्त, link)
		__पूर्णांकel_समयline_मुक्त(&tl->kref);

	अगर (flush_submission(gt, समयout)) /* Wait, there's more! */
		active_count++;

	वापस active_count ? समयout : 0;
पूर्ण

पूर्णांक पूर्णांकel_gt_रुको_क्रम_idle(काष्ठा पूर्णांकel_gt *gt, दीर्घ समयout)
अणु
	/* If the device is asleep, we have no requests outstanding */
	अगर (!पूर्णांकel_gt_pm_is_awake(gt))
		वापस 0;

	जबतक ((समयout = पूर्णांकel_gt_retire_requests_समयout(gt, समयout)) > 0) अणु
		cond_resched();
		अगर (संकेत_pending(current))
			वापस -EINTR;
	पूर्ण

	वापस समयout;
पूर्ण

अटल व्योम retire_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_gt *gt =
		container_of(work, typeof(*gt), requests.retire_work.work);

	schedule_delayed_work(&gt->requests.retire_work,
			      round_jअगरfies_up_relative(HZ));
	पूर्णांकel_gt_retire_requests(gt);
पूर्ण

व्योम पूर्णांकel_gt_init_requests(काष्ठा पूर्णांकel_gt *gt)
अणु
	INIT_DELAYED_WORK(&gt->requests.retire_work, retire_work_handler);
पूर्ण

व्योम पूर्णांकel_gt_park_requests(काष्ठा पूर्णांकel_gt *gt)
अणु
	cancel_delayed_work(&gt->requests.retire_work);
पूर्ण

व्योम पूर्णांकel_gt_unpark_requests(काष्ठा पूर्णांकel_gt *gt)
अणु
	schedule_delayed_work(&gt->requests.retire_work,
			      round_jअगरfies_up_relative(HZ));
पूर्ण

व्योम पूर्णांकel_gt_fini_requests(काष्ठा पूर्णांकel_gt *gt)
अणु
	/* Wait until the work is marked as finished beक्रमe unloading! */
	cancel_delayed_work_sync(&gt->requests.retire_work);

	flush_work(&gt->watchकरोg.work);
पूर्ण

व्योम पूर्णांकel_gt_watchकरोg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_gt *gt =
		container_of(work, typeof(*gt), watchकरोg.work);
	काष्ठा i915_request *rq, *rn;
	काष्ठा llist_node *first;

	first = llist_del_all(&gt->watchकरोg.list);
	अगर (!first)
		वापस;

	llist_क्रम_each_entry_safe(rq, rn, first, watchकरोg.link) अणु
		अगर (!i915_request_completed(rq)) अणु
			काष्ठा dma_fence *f = &rq->fence;

			pr_notice("Fence expiration time out i915-%s:%s:%llx!\n",
				  f->ops->get_driver_name(f),
				  f->ops->get_समयline_name(f),
				  f->seqno);
			i915_request_cancel(rq, -EINTR);
		पूर्ण
		i915_request_put(rq);
	पूर्ण
पूर्ण
