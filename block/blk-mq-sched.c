<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * blk-mq scheduling framework
 *
 * Copyright (C) 2016 Jens Axboe
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/list_sort.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-mq-sched.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-wbt.h"

व्योम blk_mq_sched_assign_ioc(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा io_context *ioc;
	काष्ठा io_cq *icq;

	/*
	 * May not have an IO context अगर it's a passthrough request
	 */
	ioc = current->io_context;
	अगर (!ioc)
		वापस;

	spin_lock_irq(&q->queue_lock);
	icq = ioc_lookup_icq(ioc, q);
	spin_unlock_irq(&q->queue_lock);

	अगर (!icq) अणु
		icq = ioc_create_icq(ioc, q, GFP_ATOMIC);
		अगर (!icq)
			वापस;
	पूर्ण
	get_io_context(icq->ioc);
	rq->elv.icq = icq;
पूर्ण

/*
 * Mark a hardware queue as needing a restart. For shared queues, मुख्यtain
 * a count of how many hardware queues are marked क्रम restart.
 */
व्योम blk_mq_sched_mark_restart_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (test_bit(BLK_MQ_S_SCHED_RESTART, &hctx->state))
		वापस;

	set_bit(BLK_MQ_S_SCHED_RESTART, &hctx->state);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_sched_mark_restart_hctx);

व्योम blk_mq_sched_restart(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (!test_bit(BLK_MQ_S_SCHED_RESTART, &hctx->state))
		वापस;
	clear_bit(BLK_MQ_S_SCHED_RESTART, &hctx->state);

	/*
	 * Order clearing SCHED_RESTART and list_empty_careful(&hctx->dispatch)
	 * in blk_mq_run_hw_queue(). Its pair is the barrier in
	 * blk_mq_dispatch_rq_list(). So dispatch code won't see SCHED_RESTART,
	 * meanसमय new request added to hctx->dispatch is missed to check in
	 * blk_mq_run_hw_queue().
	 */
	smp_mb();

	blk_mq_run_hw_queue(hctx, true);
पूर्ण

अटल पूर्णांक sched_rq_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			स्थिर काष्ठा list_head *b)
अणु
	काष्ठा request *rqa = container_of(a, काष्ठा request, queuelist);
	काष्ठा request *rqb = container_of(b, काष्ठा request, queuelist);

	वापस rqa->mq_hctx > rqb->mq_hctx;
पूर्ण

अटल bool blk_mq_dispatch_hctx_list(काष्ठा list_head *rq_list)
अणु
	काष्ठा blk_mq_hw_ctx *hctx =
		list_first_entry(rq_list, काष्ठा request, queuelist)->mq_hctx;
	काष्ठा request *rq;
	LIST_HEAD(hctx_list);
	अचिन्हित पूर्णांक count = 0;

	list_क्रम_each_entry(rq, rq_list, queuelist) अणु
		अगर (rq->mq_hctx != hctx) अणु
			list_cut_beक्रमe(&hctx_list, rq_list, &rq->queuelist);
			जाओ dispatch;
		पूर्ण
		count++;
	पूर्ण
	list_splice_tail_init(rq_list, &hctx_list);

dispatch:
	वापस blk_mq_dispatch_rq_list(hctx, &hctx_list, count);
पूर्ण

#घोषणा BLK_MQ_BUDGET_DELAY	3		/* ms units */

/*
 * Only SCSI implements .get_budget and .put_budget, and SCSI restarts
 * its queue by itself in its completion handler, so we करोn't need to
 * restart queue अगर .get_budget() वापसs BLK_STS_NO_RESOURCE.
 *
 * Returns -EAGAIN अगर hctx->dispatch was found non-empty and run_work has to
 * be run again.  This is necessary to aव्योम starving flushes.
 */
अटल पूर्णांक __blk_mq_करो_dispatch_sched(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा elevator_queue *e = q->elevator;
	bool multi_hctxs = false, run_queue = false;
	bool dispatched = false, busy = false;
	अचिन्हित पूर्णांक max_dispatch;
	LIST_HEAD(rq_list);
	पूर्णांक count = 0;

	अगर (hctx->dispatch_busy)
		max_dispatch = 1;
	अन्यथा
		max_dispatch = hctx->queue->nr_requests;

	करो अणु
		काष्ठा request *rq;
		पूर्णांक budget_token;

		अगर (e->type->ops.has_work && !e->type->ops.has_work(hctx))
			अवरोध;

		अगर (!list_empty_careful(&hctx->dispatch)) अणु
			busy = true;
			अवरोध;
		पूर्ण

		budget_token = blk_mq_get_dispatch_budget(q);
		अगर (budget_token < 0)
			अवरोध;

		rq = e->type->ops.dispatch_request(hctx);
		अगर (!rq) अणु
			blk_mq_put_dispatch_budget(q, budget_token);
			/*
			 * We're releasing without dispatching. Holding the
			 * budget could have blocked any "hctx"s with the
			 * same queue and अगर we didn't dispatch then there's
			 * no guarantee anyone will kick the queue.  Kick it
			 * ourselves.
			 */
			run_queue = true;
			अवरोध;
		पूर्ण

		blk_mq_set_rq_budget_token(rq, budget_token);

		/*
		 * Now this rq owns the budget which has to be released
		 * अगर this rq won't be queued to driver via .queue_rq()
		 * in blk_mq_dispatch_rq_list().
		 */
		list_add_tail(&rq->queuelist, &rq_list);
		अगर (rq->mq_hctx != hctx)
			multi_hctxs = true;
	पूर्ण जबतक (++count < max_dispatch);

	अगर (!count) अणु
		अगर (run_queue)
			blk_mq_delay_run_hw_queues(q, BLK_MQ_BUDGET_DELAY);
	पूर्ण अन्यथा अगर (multi_hctxs) अणु
		/*
		 * Requests from dअगरferent hctx may be dequeued from some
		 * schedulers, such as bfq and deadline.
		 *
		 * Sort the requests in the list according to their hctx,
		 * dispatch batching requests from same hctx at a समय.
		 */
		list_sort(शून्य, &rq_list, sched_rq_cmp);
		करो अणु
			dispatched |= blk_mq_dispatch_hctx_list(&rq_list);
		पूर्ण जबतक (!list_empty(&rq_list));
	पूर्ण अन्यथा अणु
		dispatched = blk_mq_dispatch_rq_list(hctx, &rq_list, count);
	पूर्ण

	अगर (busy)
		वापस -EAGAIN;
	वापस !!dispatched;
पूर्ण

अटल पूर्णांक blk_mq_करो_dispatch_sched(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	पूर्णांक ret;

	करो अणु
		ret = __blk_mq_करो_dispatch_sched(hctx);
	पूर्ण जबतक (ret == 1);

	वापस ret;
पूर्ण

अटल काष्ठा blk_mq_ctx *blk_mq_next_ctx(काष्ठा blk_mq_hw_ctx *hctx,
					  काष्ठा blk_mq_ctx *ctx)
अणु
	अचिन्हित लघु idx = ctx->index_hw[hctx->type];

	अगर (++idx == hctx->nr_ctx)
		idx = 0;

	वापस hctx->ctxs[idx];
पूर्ण

/*
 * Only SCSI implements .get_budget and .put_budget, and SCSI restarts
 * its queue by itself in its completion handler, so we करोn't need to
 * restart queue अगर .get_budget() वापसs BLK_STS_NO_RESOURCE.
 *
 * Returns -EAGAIN अगर hctx->dispatch was found non-empty and run_work has to
 * be run again.  This is necessary to aव्योम starving flushes.
 */
अटल पूर्णांक blk_mq_करो_dispatch_ctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा request_queue *q = hctx->queue;
	LIST_HEAD(rq_list);
	काष्ठा blk_mq_ctx *ctx = READ_ONCE(hctx->dispatch_from);
	पूर्णांक ret = 0;
	काष्ठा request *rq;

	करो अणु
		पूर्णांक budget_token;

		अगर (!list_empty_careful(&hctx->dispatch)) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (!sbiपंचांगap_any_bit_set(&hctx->ctx_map))
			अवरोध;

		budget_token = blk_mq_get_dispatch_budget(q);
		अगर (budget_token < 0)
			अवरोध;

		rq = blk_mq_dequeue_from_ctx(hctx, ctx);
		अगर (!rq) अणु
			blk_mq_put_dispatch_budget(q, budget_token);
			/*
			 * We're releasing without dispatching. Holding the
			 * budget could have blocked any "hctx"s with the
			 * same queue and अगर we didn't dispatch then there's
			 * no guarantee anyone will kick the queue.  Kick it
			 * ourselves.
			 */
			blk_mq_delay_run_hw_queues(q, BLK_MQ_BUDGET_DELAY);
			अवरोध;
		पूर्ण

		blk_mq_set_rq_budget_token(rq, budget_token);

		/*
		 * Now this rq owns the budget which has to be released
		 * अगर this rq won't be queued to driver via .queue_rq()
		 * in blk_mq_dispatch_rq_list().
		 */
		list_add(&rq->queuelist, &rq_list);

		/* round robin क्रम fair dispatch */
		ctx = blk_mq_next_ctx(hctx, rq->mq_ctx);

	पूर्ण जबतक (blk_mq_dispatch_rq_list(rq->mq_hctx, &rq_list, 1));

	WRITE_ONCE(hctx->dispatch_from, ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक __blk_mq_sched_dispatch_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा elevator_queue *e = q->elevator;
	स्थिर bool has_sched_dispatch = e && e->type->ops.dispatch_request;
	पूर्णांक ret = 0;
	LIST_HEAD(rq_list);

	/*
	 * If we have previous entries on our dispatch list, grab them first क्रम
	 * more fair dispatch.
	 */
	अगर (!list_empty_careful(&hctx->dispatch)) अणु
		spin_lock(&hctx->lock);
		अगर (!list_empty(&hctx->dispatch))
			list_splice_init(&hctx->dispatch, &rq_list);
		spin_unlock(&hctx->lock);
	पूर्ण

	/*
	 * Only ask the scheduler क्रम requests, अगर we didn't have residual
	 * requests from the dispatch list. This is to aव्योम the हाल where
	 * we only ever dispatch a fraction of the requests available because
	 * of low device queue depth. Once we pull requests out of the IO
	 * scheduler, we can no दीर्घer merge or sort them. So it's best to
	 * leave them there क्रम as दीर्घ as we can. Mark the hw queue as
	 * needing a restart in that हाल.
	 *
	 * We want to dispatch from the scheduler अगर there was nothing
	 * on the dispatch list or we were able to dispatch from the
	 * dispatch list.
	 */
	अगर (!list_empty(&rq_list)) अणु
		blk_mq_sched_mark_restart_hctx(hctx);
		अगर (blk_mq_dispatch_rq_list(hctx, &rq_list, 0)) अणु
			अगर (has_sched_dispatch)
				ret = blk_mq_करो_dispatch_sched(hctx);
			अन्यथा
				ret = blk_mq_करो_dispatch_ctx(hctx);
		पूर्ण
	पूर्ण अन्यथा अगर (has_sched_dispatch) अणु
		ret = blk_mq_करो_dispatch_sched(hctx);
	पूर्ण अन्यथा अगर (hctx->dispatch_busy) अणु
		/* dequeue request one by one from sw queue अगर queue is busy */
		ret = blk_mq_करो_dispatch_ctx(hctx);
	पूर्ण अन्यथा अणु
		blk_mq_flush_busy_ctxs(hctx, &rq_list);
		blk_mq_dispatch_rq_list(hctx, &rq_list, 0);
	पूर्ण

	वापस ret;
पूर्ण

व्योम blk_mq_sched_dispatch_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा request_queue *q = hctx->queue;

	/* RCU or SRCU पढ़ो lock is needed beक्रमe checking quiesced flag */
	अगर (unlikely(blk_mq_hctx_stopped(hctx) || blk_queue_quiesced(q)))
		वापस;

	hctx->run++;

	/*
	 * A वापस of -EAGAIN is an indication that hctx->dispatch is not
	 * empty and we must run again in order to aव्योम starving flushes.
	 */
	अगर (__blk_mq_sched_dispatch_requests(hctx) == -EAGAIN) अणु
		अगर (__blk_mq_sched_dispatch_requests(hctx) == -EAGAIN)
			blk_mq_run_hw_queue(hctx, true);
	पूर्ण
पूर्ण

bool __blk_mq_sched_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा blk_mq_ctx *ctx;
	काष्ठा blk_mq_hw_ctx *hctx;
	bool ret = false;
	क्रमागत hctx_type type;

	अगर (e && e->type->ops.bio_merge)
		वापस e->type->ops.bio_merge(q, bio, nr_segs);

	ctx = blk_mq_get_ctx(q);
	hctx = blk_mq_map_queue(q, bio->bi_opf, ctx);
	type = hctx->type;
	अगर (!(hctx->flags & BLK_MQ_F_SHOULD_MERGE) ||
	    list_empty_careful(&ctx->rq_lists[type]))
		वापस false;

	/* शेष per sw-queue merge */
	spin_lock(&ctx->lock);
	/*
	 * Reverse check our software queue क्रम entries that we could
	 * potentially merge with. Currently includes a hand-wavy stop
	 * count of 8, to not spend too much समय checking क्रम merges.
	 */
	अगर (blk_bio_list_merge(q, &ctx->rq_lists[type], bio, nr_segs)) अणु
		ctx->rq_merged++;
		ret = true;
	पूर्ण

	spin_unlock(&ctx->lock);

	वापस ret;
पूर्ण

bool blk_mq_sched_try_insert_merge(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	वापस rq_mergeable(rq) && elv_attempt_insert_merge(q, rq);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_sched_try_insert_merge);

अटल bool blk_mq_sched_bypass_insert(काष्ठा blk_mq_hw_ctx *hctx,
				       काष्ठा request *rq)
अणु
	/*
	 * dispatch flush and passthrough rq directly
	 *
	 * passthrough request has to be added to hctx->dispatch directly.
	 * For some reason, device may be in one situation which can't
	 * handle FS request, so STS_RESOURCE is always वापसed and the
	 * FS request will be added to hctx->dispatch. However passthrough
	 * request may be required at that समय क्रम fixing the problem. If
	 * passthrough request is added to scheduler queue, there isn't any
	 * chance to dispatch it given we prioritize requests in hctx->dispatch.
	 */
	अगर ((rq->rq_flags & RQF_FLUSH_SEQ) || blk_rq_is_passthrough(rq))
		वापस true;

	वापस false;
पूर्ण

व्योम blk_mq_sched_insert_request(काष्ठा request *rq, bool at_head,
				 bool run_queue, bool async)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;

	WARN_ON(e && (rq->tag != BLK_MQ_NO_TAG));

	अगर (blk_mq_sched_bypass_insert(hctx, rq)) अणु
		/*
		 * Firstly normal IO request is inserted to scheduler queue or
		 * sw queue, meanसमय we add flush request to dispatch queue(
		 * hctx->dispatch) directly and there is at most one in-flight
		 * flush request क्रम each hw queue, so it करोesn't matter to add
		 * flush request to tail or front of the dispatch queue.
		 *
		 * Secondly in हाल of NCQ, flush request beदीर्घs to non-NCQ
		 * command, and queueing it will fail when there is any
		 * in-flight normal IO request(NCQ command). When adding flush
		 * rq to the front of hctx->dispatch, it is easier to पूर्णांकroduce
		 * extra समय to flush rq's latency because of S_SCHED_RESTART
		 * compared with adding to the tail of dispatch queue, then
		 * chance of flush merge is increased, and less flush requests
		 * will be issued to controller. It is observed that ~10% समय
		 * is saved in blktests block/004 on disk attached to AHCI/NCQ
		 * drive when adding flush rq to the front of hctx->dispatch.
		 *
		 * Simply queue flush rq to the front of hctx->dispatch so that
		 * पूर्णांकensive flush workloads can benefit in हाल of NCQ HW.
		 */
		at_head = (rq->rq_flags & RQF_FLUSH_SEQ) ? true : at_head;
		blk_mq_request_bypass_insert(rq, at_head, false);
		जाओ run;
	पूर्ण

	अगर (e && e->type->ops.insert_requests) अणु
		LIST_HEAD(list);

		list_add(&rq->queuelist, &list);
		e->type->ops.insert_requests(hctx, &list, at_head);
	पूर्ण अन्यथा अणु
		spin_lock(&ctx->lock);
		__blk_mq_insert_request(hctx, rq, at_head);
		spin_unlock(&ctx->lock);
	पूर्ण

run:
	अगर (run_queue)
		blk_mq_run_hw_queue(hctx, async);
पूर्ण

व्योम blk_mq_sched_insert_requests(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा blk_mq_ctx *ctx,
				  काष्ठा list_head *list, bool run_queue_async)
अणु
	काष्ठा elevator_queue *e;
	काष्ठा request_queue *q = hctx->queue;

	/*
	 * blk_mq_sched_insert_requests() is called from flush plug
	 * context only, and hold one usage counter to prevent queue
	 * from being released.
	 */
	percpu_ref_get(&q->q_usage_counter);

	e = hctx->queue->elevator;
	अगर (e && e->type->ops.insert_requests)
		e->type->ops.insert_requests(hctx, list, false);
	अन्यथा अणु
		/*
		 * try to issue requests directly अगर the hw queue isn't
		 * busy in हाल of 'none' scheduler, and this way may save
		 * us one extra enqueue & dequeue to sw queue.
		 */
		अगर (!hctx->dispatch_busy && !e && !run_queue_async) अणु
			blk_mq_try_issue_list_directly(hctx, list);
			अगर (list_empty(list))
				जाओ out;
		पूर्ण
		blk_mq_insert_requests(hctx, ctx, list);
	पूर्ण

	blk_mq_run_hw_queue(hctx, run_queue_async);
 out:
	percpu_ref_put(&q->q_usage_counter);
पूर्ण

अटल व्योम blk_mq_sched_मुक्त_tags(काष्ठा blk_mq_tag_set *set,
				   काष्ठा blk_mq_hw_ctx *hctx,
				   अचिन्हित पूर्णांक hctx_idx)
अणु
	अचिन्हित पूर्णांक flags = set->flags & ~BLK_MQ_F_TAG_HCTX_SHARED;

	अगर (hctx->sched_tags) अणु
		blk_mq_मुक्त_rqs(set, hctx->sched_tags, hctx_idx);
		blk_mq_मुक्त_rq_map(hctx->sched_tags, flags);
		hctx->sched_tags = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक blk_mq_sched_alloc_tags(काष्ठा request_queue *q,
				   काष्ठा blk_mq_hw_ctx *hctx,
				   अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा blk_mq_tag_set *set = q->tag_set;
	/* Clear HCTX_SHARED so tags are init'ed */
	अचिन्हित पूर्णांक flags = set->flags & ~BLK_MQ_F_TAG_HCTX_SHARED;
	पूर्णांक ret;

	hctx->sched_tags = blk_mq_alloc_rq_map(set, hctx_idx, q->nr_requests,
					       set->reserved_tags, flags);
	अगर (!hctx->sched_tags)
		वापस -ENOMEM;

	ret = blk_mq_alloc_rqs(set, hctx->sched_tags, hctx_idx, q->nr_requests);
	अगर (ret)
		blk_mq_sched_मुक्त_tags(set, hctx, hctx_idx);

	वापस ret;
पूर्ण

/* called in queue's release handler, tagset has gone away */
अटल व्योम blk_mq_sched_tags_tearकरोwn(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		/* Clear HCTX_SHARED so tags are मुक्तd */
		अचिन्हित पूर्णांक flags = hctx->flags & ~BLK_MQ_F_TAG_HCTX_SHARED;

		अगर (hctx->sched_tags) अणु
			blk_mq_मुक्त_rq_map(hctx->sched_tags, flags);
			hctx->sched_tags = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक blk_mq_init_sched(काष्ठा request_queue *q, काष्ठा elevator_type *e)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा elevator_queue *eq;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!e) अणु
		q->elevator = शून्य;
		q->nr_requests = q->tag_set->queue_depth;
		वापस 0;
	पूर्ण

	/*
	 * Default to द्विगुन of smaller one between hw queue_depth and 128,
	 * since we करोn't split पूर्णांकo sync/async like the old code did.
	 * Additionally, this is a per-hw queue depth.
	 */
	q->nr_requests = 2 * min_t(अचिन्हित पूर्णांक, q->tag_set->queue_depth,
				   BLKDEV_MAX_RQ);

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		ret = blk_mq_sched_alloc_tags(q, hctx, i);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = e->ops.init_sched(q, e);
	अगर (ret)
		जाओ err;

	blk_mq_debugfs_रेजिस्टर_sched(q);

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (e->ops.init_hctx) अणु
			ret = e->ops.init_hctx(hctx, i);
			अगर (ret) अणु
				eq = q->elevator;
				blk_mq_sched_मुक्त_requests(q);
				blk_mq_निकास_sched(q, eq);
				kobject_put(&eq->kobj);
				वापस ret;
			पूर्ण
		पूर्ण
		blk_mq_debugfs_रेजिस्टर_sched_hctx(q, hctx);
	पूर्ण

	वापस 0;

err:
	blk_mq_sched_मुक्त_requests(q);
	blk_mq_sched_tags_tearकरोwn(q);
	q->elevator = शून्य;
	वापस ret;
पूर्ण

/*
 * called in either blk_queue_cleanup or elevator_चयन, tagset
 * is required क्रम मुक्तing requests
 */
व्योम blk_mq_sched_मुक्त_requests(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (hctx->sched_tags)
			blk_mq_मुक्त_rqs(q->tag_set, hctx->sched_tags, i);
	पूर्ण
पूर्ण

व्योम blk_mq_निकास_sched(काष्ठा request_queue *q, काष्ठा elevator_queue *e)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	अचिन्हित पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		blk_mq_debugfs_unरेजिस्टर_sched_hctx(hctx);
		अगर (e->type->ops.निकास_hctx && hctx->sched_data) अणु
			e->type->ops.निकास_hctx(hctx, i);
			hctx->sched_data = शून्य;
		पूर्ण
	पूर्ण
	blk_mq_debugfs_unरेजिस्टर_sched(q);
	अगर (e->type->ops.निकास_sched)
		e->type->ops.निकास_sched(e);
	blk_mq_sched_tags_tearकरोwn(q);
	q->elevator = शून्य;
पूर्ण
