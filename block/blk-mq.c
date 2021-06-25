<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Block multiqueue core code
 *
 * Copyright (C) 2013-2014 Jens Axboe
 * Copyright (C) 2013-2014 Christoph Hellwig
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/smp.h>
#समावेश <linux/llist.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cache.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/delay.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/blk-crypto.h>

#समावेश <trace/events/block.h>

#समावेश <linux/blk-mq.h>
#समावेश <linux/t10-pi.h>
#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-pm.h"
#समावेश "blk-stat.h"
#समावेश "blk-mq-sched.h"
#समावेश "blk-rq-qos.h"

अटल DEFINE_PER_CPU(काष्ठा llist_head, blk_cpu_करोne);

अटल व्योम blk_mq_poll_stats_start(काष्ठा request_queue *q);
अटल व्योम blk_mq_poll_stats_fn(काष्ठा blk_stat_callback *cb);

अटल पूर्णांक blk_mq_poll_stats_bkt(स्थिर काष्ठा request *rq)
अणु
	पूर्णांक ddir, sectors, bucket;

	ddir = rq_data_dir(rq);
	sectors = blk_rq_stats_sectors(rq);

	bucket = ddir + 2 * ilog2(sectors);

	अगर (bucket < 0)
		वापस -1;
	अन्यथा अगर (bucket >= BLK_MQ_POLL_STATS_BKTS)
		वापस ddir + BLK_MQ_POLL_STATS_BKTS - 2;

	वापस bucket;
पूर्ण

/*
 * Check अगर any of the ctx, dispatch list or elevator
 * have pending work in this hardware queue.
 */
अटल bool blk_mq_hctx_has_pending(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	वापस !list_empty_careful(&hctx->dispatch) ||
		sbiपंचांगap_any_bit_set(&hctx->ctx_map) ||
			blk_mq_sched_has_work(hctx);
पूर्ण

/*
 * Mark this ctx as having pending work in this hardware queue
 */
अटल व्योम blk_mq_hctx_mark_pending(काष्ठा blk_mq_hw_ctx *hctx,
				     काष्ठा blk_mq_ctx *ctx)
अणु
	स्थिर पूर्णांक bit = ctx->index_hw[hctx->type];

	अगर (!sbiपंचांगap_test_bit(&hctx->ctx_map, bit))
		sbiपंचांगap_set_bit(&hctx->ctx_map, bit);
पूर्ण

अटल व्योम blk_mq_hctx_clear_pending(काष्ठा blk_mq_hw_ctx *hctx,
				      काष्ठा blk_mq_ctx *ctx)
अणु
	स्थिर पूर्णांक bit = ctx->index_hw[hctx->type];

	sbiपंचांगap_clear_bit(&hctx->ctx_map, bit);
पूर्ण

काष्ठा mq_inflight अणु
	काष्ठा block_device *part;
	अचिन्हित पूर्णांक inflight[2];
पूर्ण;

अटल bool blk_mq_check_inflight(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा request *rq, व्योम *priv,
				  bool reserved)
अणु
	काष्ठा mq_inflight *mi = priv;

	अगर ((!mi->part->bd_partno || rq->part == mi->part) &&
	    blk_mq_rq_state(rq) == MQ_RQ_IN_FLIGHT)
		mi->inflight[rq_data_dir(rq)]++;

	वापस true;
पूर्ण

अचिन्हित पूर्णांक blk_mq_in_flight(काष्ठा request_queue *q,
		काष्ठा block_device *part)
अणु
	काष्ठा mq_inflight mi = अणु .part = part पूर्ण;

	blk_mq_queue_tag_busy_iter(q, blk_mq_check_inflight, &mi);

	वापस mi.inflight[0] + mi.inflight[1];
पूर्ण

व्योम blk_mq_in_flight_rw(काष्ठा request_queue *q, काष्ठा block_device *part,
		अचिन्हित पूर्णांक inflight[2])
अणु
	काष्ठा mq_inflight mi = अणु .part = part पूर्ण;

	blk_mq_queue_tag_busy_iter(q, blk_mq_check_inflight, &mi);
	inflight[0] = mi.inflight[0];
	inflight[1] = mi.inflight[1];
पूर्ण

व्योम blk_मुक्तze_queue_start(काष्ठा request_queue *q)
अणु
	mutex_lock(&q->mq_मुक्तze_lock);
	अगर (++q->mq_मुक्तze_depth == 1) अणु
		percpu_ref_समाप्त(&q->q_usage_counter);
		mutex_unlock(&q->mq_मुक्तze_lock);
		अगर (queue_is_mq(q))
			blk_mq_run_hw_queues(q, false);
	पूर्ण अन्यथा अणु
		mutex_unlock(&q->mq_मुक्तze_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_मुक्तze_queue_start);

व्योम blk_mq_मुक्तze_queue_रुको(काष्ठा request_queue *q)
अणु
	रुको_event(q->mq_मुक्तze_wq, percpu_ref_is_zero(&q->q_usage_counter));
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_मुक्तze_queue_रुको);

पूर्णांक blk_mq_मुक्तze_queue_रुको_समयout(काष्ठा request_queue *q,
				     अचिन्हित दीर्घ समयout)
अणु
	वापस रुको_event_समयout(q->mq_मुक्तze_wq,
					percpu_ref_is_zero(&q->q_usage_counter),
					समयout);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_मुक्तze_queue_रुको_समयout);

/*
 * Guarantee no request is in use, so we can change any data काष्ठाure of
 * the queue afterward.
 */
व्योम blk_मुक्तze_queue(काष्ठा request_queue *q)
अणु
	/*
	 * In the !blk_mq हाल we are only calling this to समाप्त the
	 * q_usage_counter, otherwise this increases the मुक्तze depth
	 * and रुकोs क्रम it to वापस to zero.  For this reason there is
	 * no blk_unमुक्तze_queue(), and blk_मुक्तze_queue() is not
	 * exported to drivers as the only user क्रम unमुक्तze is blk_mq.
	 */
	blk_मुक्तze_queue_start(q);
	blk_mq_मुक्तze_queue_रुको(q);
पूर्ण

व्योम blk_mq_मुक्तze_queue(काष्ठा request_queue *q)
अणु
	/*
	 * ...just an alias to keep मुक्तze and unमुक्तze actions balanced
	 * in the blk_mq_* namespace
	 */
	blk_मुक्तze_queue(q);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_मुक्तze_queue);

व्योम blk_mq_unमुक्तze_queue(काष्ठा request_queue *q)
अणु
	mutex_lock(&q->mq_मुक्तze_lock);
	q->mq_मुक्तze_depth--;
	WARN_ON_ONCE(q->mq_मुक्तze_depth < 0);
	अगर (!q->mq_मुक्तze_depth) अणु
		percpu_ref_resurrect(&q->q_usage_counter);
		wake_up_all(&q->mq_मुक्तze_wq);
	पूर्ण
	mutex_unlock(&q->mq_मुक्तze_lock);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_unमुक्तze_queue);

/*
 * FIXME: replace the scsi_पूर्णांकernal_device_*block_noरुको() calls in the
 * mpt3sas driver such that this function can be हटाओd.
 */
व्योम blk_mq_quiesce_queue_noरुको(काष्ठा request_queue *q)
अणु
	blk_queue_flag_set(QUEUE_FLAG_QUIESCED, q);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_quiesce_queue_noरुको);

/**
 * blk_mq_quiesce_queue() - रुको until all ongoing dispatches have finished
 * @q: request queue.
 *
 * Note: this function करोes not prevent that the काष्ठा request end_io()
 * callback function is invoked. Once this function is वापसed, we make
 * sure no dispatch can happen until the queue is unquiesced via
 * blk_mq_unquiesce_queue().
 */
व्योम blk_mq_quiesce_queue(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	अचिन्हित पूर्णांक i;
	bool rcu = false;

	blk_mq_quiesce_queue_noरुको(q);

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (hctx->flags & BLK_MQ_F_BLOCKING)
			synchronize_srcu(hctx->srcu);
		अन्यथा
			rcu = true;
	पूर्ण
	अगर (rcu)
		synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_quiesce_queue);

/*
 * blk_mq_unquiesce_queue() - counterpart of blk_mq_quiesce_queue()
 * @q: request queue.
 *
 * This function recovers queue पूर्णांकo the state beक्रमe quiescing
 * which is करोne by blk_mq_quiesce_queue.
 */
व्योम blk_mq_unquiesce_queue(काष्ठा request_queue *q)
अणु
	blk_queue_flag_clear(QUEUE_FLAG_QUIESCED, q);

	/* dispatch requests which are inserted during quiescing */
	blk_mq_run_hw_queues(q, true);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_unquiesce_queue);

व्योम blk_mq_wake_रुकोers(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	अचिन्हित पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		अगर (blk_mq_hw_queue_mapped(hctx))
			blk_mq_tag_wakeup_all(hctx->tags, true);
पूर्ण

/*
 * Only need start/end समय stamping अगर we have iostat or
 * blk stats enabled, or using an IO scheduler.
 */
अटल अंतरभूत bool blk_mq_need_समय_stamp(काष्ठा request *rq)
अणु
	वापस (rq->rq_flags & (RQF_IO_STAT | RQF_STATS)) || rq->q->elevator;
पूर्ण

अटल काष्ठा request *blk_mq_rq_ctx_init(काष्ठा blk_mq_alloc_data *data,
		अचिन्हित पूर्णांक tag, u64 alloc_समय_ns)
अणु
	काष्ठा blk_mq_tags *tags = blk_mq_tags_from_data(data);
	काष्ठा request *rq = tags->अटल_rqs[tag];

	अगर (data->q->elevator) अणु
		rq->tag = BLK_MQ_NO_TAG;
		rq->पूर्णांकernal_tag = tag;
	पूर्ण अन्यथा अणु
		rq->tag = tag;
		rq->पूर्णांकernal_tag = BLK_MQ_NO_TAG;
	पूर्ण

	/* csd/requeue_work/fअगरo_समय is initialized beक्रमe use */
	rq->q = data->q;
	rq->mq_ctx = data->ctx;
	rq->mq_hctx = data->hctx;
	rq->rq_flags = 0;
	rq->cmd_flags = data->cmd_flags;
	अगर (data->flags & BLK_MQ_REQ_PM)
		rq->rq_flags |= RQF_PM;
	अगर (blk_queue_io_stat(data->q))
		rq->rq_flags |= RQF_IO_STAT;
	INIT_LIST_HEAD(&rq->queuelist);
	INIT_HLIST_NODE(&rq->hash);
	RB_CLEAR_NODE(&rq->rb_node);
	rq->rq_disk = शून्य;
	rq->part = शून्य;
#अगर_घोषित CONFIG_BLK_RQ_ALLOC_TIME
	rq->alloc_समय_ns = alloc_समय_ns;
#पूर्ण_अगर
	अगर (blk_mq_need_समय_stamp(rq))
		rq->start_समय_ns = kसमय_get_ns();
	अन्यथा
		rq->start_समय_ns = 0;
	rq->io_start_समय_ns = 0;
	rq->stats_sectors = 0;
	rq->nr_phys_segments = 0;
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	rq->nr_पूर्णांकegrity_segments = 0;
#पूर्ण_अगर
	blk_crypto_rq_set_शेषs(rq);
	/* tag was alपढ़ोy set */
	WRITE_ONCE(rq->deadline, 0);

	rq->समयout = 0;

	rq->end_io = शून्य;
	rq->end_io_data = शून्य;

	data->ctx->rq_dispatched[op_is_sync(data->cmd_flags)]++;
	refcount_set(&rq->ref, 1);

	अगर (!op_is_flush(data->cmd_flags)) अणु
		काष्ठा elevator_queue *e = data->q->elevator;

		rq->elv.icq = शून्य;
		अगर (e && e->type->ops.prepare_request) अणु
			अगर (e->type->icq_cache)
				blk_mq_sched_assign_ioc(rq);

			e->type->ops.prepare_request(rq);
			rq->rq_flags |= RQF_ELVPRIV;
		पूर्ण
	पूर्ण

	data->hctx->queued++;
	वापस rq;
पूर्ण

अटल काष्ठा request *__blk_mq_alloc_request(काष्ठा blk_mq_alloc_data *data)
अणु
	काष्ठा request_queue *q = data->q;
	काष्ठा elevator_queue *e = q->elevator;
	u64 alloc_समय_ns = 0;
	अचिन्हित पूर्णांक tag;

	/* alloc_समय includes depth and tag रुकोs */
	अगर (blk_queue_rq_alloc_समय(q))
		alloc_समय_ns = kसमय_get_ns();

	अगर (data->cmd_flags & REQ_NOWAIT)
		data->flags |= BLK_MQ_REQ_NOWAIT;

	अगर (e) अणु
		/*
		 * Flush/passthrough requests are special and go directly to the
		 * dispatch list. Don't include reserved tags in the
		 * limiting, as it isn't useful.
		 */
		अगर (!op_is_flush(data->cmd_flags) &&
		    !blk_op_is_passthrough(data->cmd_flags) &&
		    e->type->ops.limit_depth &&
		    !(data->flags & BLK_MQ_REQ_RESERVED))
			e->type->ops.limit_depth(data->cmd_flags, data);
	पूर्ण

retry:
	data->ctx = blk_mq_get_ctx(q);
	data->hctx = blk_mq_map_queue(q, data->cmd_flags, data->ctx);
	अगर (!e)
		blk_mq_tag_busy(data->hctx);

	/*
	 * Waiting allocations only fail because of an inactive hctx.  In that
	 * हाल just retry the hctx assignment and tag allocation as CPU hotplug
	 * should have migrated us to an online CPU by now.
	 */
	tag = blk_mq_get_tag(data);
	अगर (tag == BLK_MQ_NO_TAG) अणु
		अगर (data->flags & BLK_MQ_REQ_NOWAIT)
			वापस शून्य;

		/*
		 * Give up the CPU and sleep क्रम a अक्रमom लघु समय to ensure
		 * that thपढ़ो using a realसमय scheduling class are migrated
		 * off the CPU, and thus off the hctx that is going away.
		 */
		msleep(3);
		जाओ retry;
	पूर्ण
	वापस blk_mq_rq_ctx_init(data, tag, alloc_समय_ns);
पूर्ण

काष्ठा request *blk_mq_alloc_request(काष्ठा request_queue *q, अचिन्हित पूर्णांक op,
		blk_mq_req_flags_t flags)
अणु
	काष्ठा blk_mq_alloc_data data = अणु
		.q		= q,
		.flags		= flags,
		.cmd_flags	= op,
	पूर्ण;
	काष्ठा request *rq;
	पूर्णांक ret;

	ret = blk_queue_enter(q, flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	rq = __blk_mq_alloc_request(&data);
	अगर (!rq)
		जाओ out_queue_निकास;
	rq->__data_len = 0;
	rq->__sector = (sector_t) -1;
	rq->bio = rq->biotail = शून्य;
	वापस rq;
out_queue_निकास:
	blk_queue_निकास(q);
	वापस ERR_PTR(-EWOULDBLOCK);
पूर्ण
EXPORT_SYMBOL(blk_mq_alloc_request);

काष्ठा request *blk_mq_alloc_request_hctx(काष्ठा request_queue *q,
	अचिन्हित पूर्णांक op, blk_mq_req_flags_t flags, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा blk_mq_alloc_data data = अणु
		.q		= q,
		.flags		= flags,
		.cmd_flags	= op,
	पूर्ण;
	u64 alloc_समय_ns = 0;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक tag;
	पूर्णांक ret;

	/* alloc_समय includes depth and tag रुकोs */
	अगर (blk_queue_rq_alloc_समय(q))
		alloc_समय_ns = kसमय_get_ns();

	/*
	 * If the tag allocator sleeps we could get an allocation क्रम a
	 * dअगरferent hardware context.  No need to complicate the low level
	 * allocator क्रम this क्रम the rare use हाल of a command tied to
	 * a specअगरic queue.
	 */
	अगर (WARN_ON_ONCE(!(flags & (BLK_MQ_REQ_NOWAIT | BLK_MQ_REQ_RESERVED))))
		वापस ERR_PTR(-EINVAL);

	अगर (hctx_idx >= q->nr_hw_queues)
		वापस ERR_PTR(-EIO);

	ret = blk_queue_enter(q, flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	/*
	 * Check अगर the hardware context is actually mapped to anything.
	 * If not tell the caller that it should skip this queue.
	 */
	ret = -EXDEV;
	data.hctx = q->queue_hw_ctx[hctx_idx];
	अगर (!blk_mq_hw_queue_mapped(data.hctx))
		जाओ out_queue_निकास;
	cpu = cpumask_first_and(data.hctx->cpumask, cpu_online_mask);
	data.ctx = __blk_mq_get_ctx(q, cpu);

	अगर (!q->elevator)
		blk_mq_tag_busy(data.hctx);

	ret = -EWOULDBLOCK;
	tag = blk_mq_get_tag(&data);
	अगर (tag == BLK_MQ_NO_TAG)
		जाओ out_queue_निकास;
	वापस blk_mq_rq_ctx_init(&data, tag, alloc_समय_ns);

out_queue_निकास:
	blk_queue_निकास(q);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_alloc_request_hctx);

अटल व्योम __blk_mq_मुक्त_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;
	स्थिर पूर्णांक sched_tag = rq->पूर्णांकernal_tag;

	blk_crypto_मुक्त_request(rq);
	blk_pm_mark_last_busy(rq);
	rq->mq_hctx = शून्य;
	अगर (rq->tag != BLK_MQ_NO_TAG)
		blk_mq_put_tag(hctx->tags, ctx, rq->tag);
	अगर (sched_tag != BLK_MQ_NO_TAG)
		blk_mq_put_tag(hctx->sched_tags, ctx, sched_tag);
	blk_mq_sched_restart(hctx);
	blk_queue_निकास(q);
पूर्ण

व्योम blk_mq_मुक्त_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा elevator_queue *e = q->elevator;
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;

	अगर (rq->rq_flags & RQF_ELVPRIV) अणु
		अगर (e && e->type->ops.finish_request)
			e->type->ops.finish_request(rq);
		अगर (rq->elv.icq) अणु
			put_io_context(rq->elv.icq->ioc);
			rq->elv.icq = शून्य;
		पूर्ण
	पूर्ण

	ctx->rq_completed[rq_is_sync(rq)]++;
	अगर (rq->rq_flags & RQF_MQ_INFLIGHT)
		__blk_mq_dec_active_requests(hctx);

	अगर (unlikely(laptop_mode && !blk_rq_is_passthrough(rq)))
		laptop_io_completion(q->backing_dev_info);

	rq_qos_करोne(q, rq);

	WRITE_ONCE(rq->state, MQ_RQ_IDLE);
	अगर (refcount_dec_and_test(&rq->ref))
		__blk_mq_मुक्त_request(rq);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_मुक्त_request);

अंतरभूत व्योम __blk_mq_end_request(काष्ठा request *rq, blk_status_t error)
अणु
	u64 now = 0;

	अगर (blk_mq_need_समय_stamp(rq))
		now = kसमय_get_ns();

	अगर (rq->rq_flags & RQF_STATS) अणु
		blk_mq_poll_stats_start(rq->q);
		blk_stat_add(rq, now);
	पूर्ण

	blk_mq_sched_completed_request(rq, now);

	blk_account_io_करोne(rq, now);

	अगर (rq->end_io) अणु
		rq_qos_करोne(rq->q, rq);
		rq->end_io(rq, error);
	पूर्ण अन्यथा अणु
		blk_mq_मुक्त_request(rq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__blk_mq_end_request);

व्योम blk_mq_end_request(काष्ठा request *rq, blk_status_t error)
अणु
	अगर (blk_update_request(rq, error, blk_rq_bytes(rq)))
		BUG();
	__blk_mq_end_request(rq, error);
पूर्ण
EXPORT_SYMBOL(blk_mq_end_request);

अटल व्योम blk_complete_reqs(काष्ठा llist_head *list)
अणु
	काष्ठा llist_node *entry = llist_reverse_order(llist_del_all(list));
	काष्ठा request *rq, *next;

	llist_क्रम_each_entry_safe(rq, next, entry, ipi_list)
		rq->q->mq_ops->complete(rq);
पूर्ण

अटल __latent_entropy व्योम blk_करोne_softirq(काष्ठा softirq_action *h)
अणु
	blk_complete_reqs(this_cpu_ptr(&blk_cpu_करोne));
पूर्ण

अटल पूर्णांक blk_softirq_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	blk_complete_reqs(&per_cpu(blk_cpu_करोne, cpu));
	वापस 0;
पूर्ण

अटल व्योम __blk_mq_complete_request_remote(व्योम *data)
अणु
	__उठाओ_softirq_irqoff(BLOCK_SOFTIRQ);
पूर्ण

अटल अंतरभूत bool blk_mq_complete_need_ipi(काष्ठा request *rq)
अणु
	पूर्णांक cpu = raw_smp_processor_id();

	अगर (!IS_ENABLED(CONFIG_SMP) ||
	    !test_bit(QUEUE_FLAG_SAME_COMP, &rq->q->queue_flags))
		वापस false;
	/*
	 * With क्रमce thपढ़ोed पूर्णांकerrupts enabled, raising softirq from an SMP
	 * function call will always result in waking the ksoftirqd thपढ़ो.
	 * This is probably worse than completing the request on a dअगरferent
	 * cache करोमुख्य.
	 */
	अगर (क्रमce_irqthपढ़ोs)
		वापस false;

	/* same CPU or cache करोमुख्य?  Complete locally */
	अगर (cpu == rq->mq_ctx->cpu ||
	    (!test_bit(QUEUE_FLAG_SAME_FORCE, &rq->q->queue_flags) &&
	     cpus_share_cache(cpu, rq->mq_ctx->cpu)))
		वापस false;

	/* करोn't try to IPI to an offline CPU */
	वापस cpu_online(rq->mq_ctx->cpu);
पूर्ण

अटल व्योम blk_mq_complete_send_ipi(काष्ठा request *rq)
अणु
	काष्ठा llist_head *list;
	अचिन्हित पूर्णांक cpu;

	cpu = rq->mq_ctx->cpu;
	list = &per_cpu(blk_cpu_करोne, cpu);
	अगर (llist_add(&rq->ipi_list, list)) अणु
		INIT_CSD(&rq->csd, __blk_mq_complete_request_remote, rq);
		smp_call_function_single_async(cpu, &rq->csd);
	पूर्ण
पूर्ण

अटल व्योम blk_mq_उठाओ_softirq(काष्ठा request *rq)
अणु
	काष्ठा llist_head *list;

	preempt_disable();
	list = this_cpu_ptr(&blk_cpu_करोne);
	अगर (llist_add(&rq->ipi_list, list))
		उठाओ_softirq(BLOCK_SOFTIRQ);
	preempt_enable();
पूर्ण

bool blk_mq_complete_request_remote(काष्ठा request *rq)
अणु
	WRITE_ONCE(rq->state, MQ_RQ_COMPLETE);

	/*
	 * For a polled request, always complete locallly, it's poपूर्णांकless
	 * to redirect the completion.
	 */
	अगर (rq->cmd_flags & REQ_HIPRI)
		वापस false;

	अगर (blk_mq_complete_need_ipi(rq)) अणु
		blk_mq_complete_send_ipi(rq);
		वापस true;
	पूर्ण

	अगर (rq->q->nr_hw_queues == 1) अणु
		blk_mq_उठाओ_softirq(rq);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_complete_request_remote);

/**
 * blk_mq_complete_request - end I/O on a request
 * @rq:		the request being processed
 *
 * Description:
 *	Complete a request by scheduling the ->complete_rq operation.
 **/
व्योम blk_mq_complete_request(काष्ठा request *rq)
अणु
	अगर (!blk_mq_complete_request_remote(rq))
		rq->q->mq_ops->complete(rq);
पूर्ण
EXPORT_SYMBOL(blk_mq_complete_request);

अटल व्योम hctx_unlock(काष्ठा blk_mq_hw_ctx *hctx, पूर्णांक srcu_idx)
	__releases(hctx->srcu)
अणु
	अगर (!(hctx->flags & BLK_MQ_F_BLOCKING))
		rcu_पढ़ो_unlock();
	अन्यथा
		srcu_पढ़ो_unlock(hctx->srcu, srcu_idx);
पूर्ण

अटल व्योम hctx_lock(काष्ठा blk_mq_hw_ctx *hctx, पूर्णांक *srcu_idx)
	__acquires(hctx->srcu)
अणु
	अगर (!(hctx->flags & BLK_MQ_F_BLOCKING)) अणु
		/* shut up gcc false positive */
		*srcu_idx = 0;
		rcu_पढ़ो_lock();
	पूर्ण अन्यथा
		*srcu_idx = srcu_पढ़ो_lock(hctx->srcu);
पूर्ण

/**
 * blk_mq_start_request - Start processing a request
 * @rq: Poपूर्णांकer to request to be started
 *
 * Function used by device drivers to notअगरy the block layer that a request
 * is going to be processed now, so blk layer can करो proper initializations
 * such as starting the समयout समयr.
 */
व्योम blk_mq_start_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;

	trace_block_rq_issue(rq);

	अगर (test_bit(QUEUE_FLAG_STATS, &q->queue_flags)) अणु
		rq->io_start_समय_ns = kसमय_get_ns();
		rq->stats_sectors = blk_rq_sectors(rq);
		rq->rq_flags |= RQF_STATS;
		rq_qos_issue(q, rq);
	पूर्ण

	WARN_ON_ONCE(blk_mq_rq_state(rq) != MQ_RQ_IDLE);

	blk_add_समयr(rq);
	WRITE_ONCE(rq->state, MQ_RQ_IN_FLIGHT);

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	अगर (blk_पूर्णांकegrity_rq(rq) && req_op(rq) == REQ_OP_WRITE)
		q->पूर्णांकegrity.profile->prepare_fn(rq);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(blk_mq_start_request);

अटल व्योम __blk_mq_requeue_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;

	blk_mq_put_driver_tag(rq);

	trace_block_rq_requeue(rq);
	rq_qos_requeue(q, rq);

	अगर (blk_mq_request_started(rq)) अणु
		WRITE_ONCE(rq->state, MQ_RQ_IDLE);
		rq->rq_flags &= ~RQF_TIMED_OUT;
	पूर्ण
पूर्ण

व्योम blk_mq_requeue_request(काष्ठा request *rq, bool kick_requeue_list)
अणु
	__blk_mq_requeue_request(rq);

	/* this request will be re-inserted to io scheduler queue */
	blk_mq_sched_requeue_request(rq);

	BUG_ON(!list_empty(&rq->queuelist));
	blk_mq_add_to_requeue_list(rq, true, kick_requeue_list);
पूर्ण
EXPORT_SYMBOL(blk_mq_requeue_request);

अटल व्योम blk_mq_requeue_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा request_queue *q =
		container_of(work, काष्ठा request_queue, requeue_work.work);
	LIST_HEAD(rq_list);
	काष्ठा request *rq, *next;

	spin_lock_irq(&q->requeue_lock);
	list_splice_init(&q->requeue_list, &rq_list);
	spin_unlock_irq(&q->requeue_lock);

	list_क्रम_each_entry_safe(rq, next, &rq_list, queuelist) अणु
		अगर (!(rq->rq_flags & (RQF_SOFTBARRIER | RQF_DONTPREP)))
			जारी;

		rq->rq_flags &= ~RQF_SOFTBARRIER;
		list_del_init(&rq->queuelist);
		/*
		 * If RQF_DONTPREP, rq has contained some driver specअगरic
		 * data, so insert it to hctx dispatch list to aव्योम any
		 * merge.
		 */
		अगर (rq->rq_flags & RQF_DONTPREP)
			blk_mq_request_bypass_insert(rq, false, false);
		अन्यथा
			blk_mq_sched_insert_request(rq, true, false, false);
	पूर्ण

	जबतक (!list_empty(&rq_list)) अणु
		rq = list_entry(rq_list.next, काष्ठा request, queuelist);
		list_del_init(&rq->queuelist);
		blk_mq_sched_insert_request(rq, false, false, false);
	पूर्ण

	blk_mq_run_hw_queues(q, false);
पूर्ण

व्योम blk_mq_add_to_requeue_list(काष्ठा request *rq, bool at_head,
				bool kick_requeue_list)
अणु
	काष्ठा request_queue *q = rq->q;
	अचिन्हित दीर्घ flags;

	/*
	 * We abuse this flag that is otherwise used by the I/O scheduler to
	 * request head insertion from the workqueue.
	 */
	BUG_ON(rq->rq_flags & RQF_SOFTBARRIER);

	spin_lock_irqsave(&q->requeue_lock, flags);
	अगर (at_head) अणु
		rq->rq_flags |= RQF_SOFTBARRIER;
		list_add(&rq->queuelist, &q->requeue_list);
	पूर्ण अन्यथा अणु
		list_add_tail(&rq->queuelist, &q->requeue_list);
	पूर्ण
	spin_unlock_irqrestore(&q->requeue_lock, flags);

	अगर (kick_requeue_list)
		blk_mq_kick_requeue_list(q);
पूर्ण

व्योम blk_mq_kick_requeue_list(काष्ठा request_queue *q)
अणु
	kblockd_mod_delayed_work_on(WORK_CPU_UNBOUND, &q->requeue_work, 0);
पूर्ण
EXPORT_SYMBOL(blk_mq_kick_requeue_list);

व्योम blk_mq_delay_kick_requeue_list(काष्ठा request_queue *q,
				    अचिन्हित दीर्घ msecs)
अणु
	kblockd_mod_delayed_work_on(WORK_CPU_UNBOUND, &q->requeue_work,
				    msecs_to_jअगरfies(msecs));
पूर्ण
EXPORT_SYMBOL(blk_mq_delay_kick_requeue_list);

काष्ठा request *blk_mq_tag_to_rq(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक tag)
अणु
	अगर (tag < tags->nr_tags) अणु
		prefetch(tags->rqs[tag]);
		वापस tags->rqs[tag];
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(blk_mq_tag_to_rq);

अटल bool blk_mq_rq_inflight(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा request *rq,
			       व्योम *priv, bool reserved)
अणु
	/*
	 * If we find a request that isn't idle and the queue matches,
	 * we know the queue is busy. Return false to stop the iteration.
	 */
	अगर (blk_mq_request_started(rq) && rq->q == hctx->queue) अणु
		bool *busy = priv;

		*busy = true;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool blk_mq_queue_inflight(काष्ठा request_queue *q)
अणु
	bool busy = false;

	blk_mq_queue_tag_busy_iter(q, blk_mq_rq_inflight, &busy);
	वापस busy;
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_queue_inflight);

अटल व्योम blk_mq_rq_समयd_out(काष्ठा request *req, bool reserved)
अणु
	req->rq_flags |= RQF_TIMED_OUT;
	अगर (req->q->mq_ops->समयout) अणु
		क्रमागत blk_eh_समयr_वापस ret;

		ret = req->q->mq_ops->समयout(req, reserved);
		अगर (ret == BLK_EH_DONE)
			वापस;
		WARN_ON_ONCE(ret != BLK_EH_RESET_TIMER);
	पूर्ण

	blk_add_समयr(req);
पूर्ण

अटल bool blk_mq_req_expired(काष्ठा request *rq, अचिन्हित दीर्घ *next)
अणु
	अचिन्हित दीर्घ deadline;

	अगर (blk_mq_rq_state(rq) != MQ_RQ_IN_FLIGHT)
		वापस false;
	अगर (rq->rq_flags & RQF_TIMED_OUT)
		वापस false;

	deadline = READ_ONCE(rq->deadline);
	अगर (समय_after_eq(jअगरfies, deadline))
		वापस true;

	अगर (*next == 0)
		*next = deadline;
	अन्यथा अगर (समय_after(*next, deadline))
		*next = deadline;
	वापस false;
पूर्ण

अटल bool blk_mq_check_expired(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा request *rq, व्योम *priv, bool reserved)
अणु
	अचिन्हित दीर्घ *next = priv;

	/*
	 * Just करो a quick check अगर it is expired beक्रमe locking the request in
	 * so we're not unnecessarilly synchronizing across CPUs.
	 */
	अगर (!blk_mq_req_expired(rq, next))
		वापस true;

	/*
	 * We have reason to believe the request may be expired. Take a
	 * reference on the request to lock this request lअगरeसमय पूर्णांकo its
	 * currently allocated context to prevent it from being पुनः_स्मृतिated in
	 * the event the completion by-passes this समयout handler.
	 *
	 * If the reference was alपढ़ोy released, then the driver beat the
	 * समयout handler to posting a natural completion.
	 */
	अगर (!refcount_inc_not_zero(&rq->ref))
		वापस true;

	/*
	 * The request is now locked and cannot be पुनः_स्मृतिated underneath the
	 * समयout handler's processing. Re-verअगरy this exact request is truly
	 * expired; अगर it is not expired, then the request was completed and
	 * पुनः_स्मृतिated as a new request.
	 */
	अगर (blk_mq_req_expired(rq, next))
		blk_mq_rq_समयd_out(rq, reserved);

	अगर (is_flush_rq(rq, hctx))
		rq->end_io(rq, 0);
	अन्यथा अगर (refcount_dec_and_test(&rq->ref))
		__blk_mq_मुक्त_request(rq);

	वापस true;
पूर्ण

अटल व्योम blk_mq_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा request_queue *q =
		container_of(work, काष्ठा request_queue, समयout_work);
	अचिन्हित दीर्घ next = 0;
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	/* A deadlock might occur अगर a request is stuck requiring a
	 * समयout at the same समय a queue मुक्तze is रुकोing
	 * completion, since the समयout code would not be able to
	 * acquire the queue reference here.
	 *
	 * That's why we don't use blk_queue_enter here; instead, we use
	 * percpu_ref_tryget directly, because we need to be able to
	 * obtain a reference even in the लघु winकरोw between the queue
	 * starting to मुक्तze, by dropping the first reference in
	 * blk_मुक्तze_queue_start, and the moment the last request is
	 * consumed, marked by the instant q_usage_counter reaches
	 * zero.
	 */
	अगर (!percpu_ref_tryget(&q->q_usage_counter))
		वापस;

	blk_mq_queue_tag_busy_iter(q, blk_mq_check_expired, &next);

	अगर (next != 0) अणु
		mod_समयr(&q->समयout, next);
	पूर्ण अन्यथा अणु
		/*
		 * Request समयouts are handled as a क्रमward rolling समयr. If
		 * we end up here it means that no requests are pending and
		 * also that no request has been pending क्रम a जबतक. Mark
		 * each hctx as idle.
		 */
		queue_क्रम_each_hw_ctx(q, hctx, i) अणु
			/* the hctx may be unmapped, so check it here */
			अगर (blk_mq_hw_queue_mapped(hctx))
				blk_mq_tag_idle(hctx);
		पूर्ण
	पूर्ण
	blk_queue_निकास(q);
पूर्ण

काष्ठा flush_busy_ctx_data अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा list_head *list;
पूर्ण;

अटल bool flush_busy_ctx(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr, व्योम *data)
अणु
	काष्ठा flush_busy_ctx_data *flush_data = data;
	काष्ठा blk_mq_hw_ctx *hctx = flush_data->hctx;
	काष्ठा blk_mq_ctx *ctx = hctx->ctxs[bitnr];
	क्रमागत hctx_type type = hctx->type;

	spin_lock(&ctx->lock);
	list_splice_tail_init(&ctx->rq_lists[type], flush_data->list);
	sbiपंचांगap_clear_bit(sb, bitnr);
	spin_unlock(&ctx->lock);
	वापस true;
पूर्ण

/*
 * Process software queues that have been marked busy, splicing them
 * to the क्रम-dispatch
 */
व्योम blk_mq_flush_busy_ctxs(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा list_head *list)
अणु
	काष्ठा flush_busy_ctx_data data = अणु
		.hctx = hctx,
		.list = list,
	पूर्ण;

	sbiपंचांगap_क्रम_each_set(&hctx->ctx_map, flush_busy_ctx, &data);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_flush_busy_ctxs);

काष्ठा dispatch_rq_data अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा request *rq;
पूर्ण;

अटल bool dispatch_rq_from_ctx(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr,
		व्योम *data)
अणु
	काष्ठा dispatch_rq_data *dispatch_data = data;
	काष्ठा blk_mq_hw_ctx *hctx = dispatch_data->hctx;
	काष्ठा blk_mq_ctx *ctx = hctx->ctxs[bitnr];
	क्रमागत hctx_type type = hctx->type;

	spin_lock(&ctx->lock);
	अगर (!list_empty(&ctx->rq_lists[type])) अणु
		dispatch_data->rq = list_entry_rq(ctx->rq_lists[type].next);
		list_del_init(&dispatch_data->rq->queuelist);
		अगर (list_empty(&ctx->rq_lists[type]))
			sbiपंचांगap_clear_bit(sb, bitnr);
	पूर्ण
	spin_unlock(&ctx->lock);

	वापस !dispatch_data->rq;
पूर्ण

काष्ठा request *blk_mq_dequeue_from_ctx(काष्ठा blk_mq_hw_ctx *hctx,
					काष्ठा blk_mq_ctx *start)
अणु
	अचिन्हित off = start ? start->index_hw[hctx->type] : 0;
	काष्ठा dispatch_rq_data data = अणु
		.hctx = hctx,
		.rq   = शून्य,
	पूर्ण;

	__sbiपंचांगap_क्रम_each_set(&hctx->ctx_map, off,
			       dispatch_rq_from_ctx, &data);

	वापस data.rq;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queued_to_index(अचिन्हित पूर्णांक queued)
अणु
	अगर (!queued)
		वापस 0;

	वापस min(BLK_MQ_MAX_DISPATCH_ORDER - 1, ilog2(queued) + 1);
पूर्ण

अटल bool __blk_mq_get_driver_tag(काष्ठा request *rq)
अणु
	काष्ठा sbiपंचांगap_queue *bt = rq->mq_hctx->tags->biपंचांगap_tags;
	अचिन्हित पूर्णांक tag_offset = rq->mq_hctx->tags->nr_reserved_tags;
	पूर्णांक tag;

	blk_mq_tag_busy(rq->mq_hctx);

	अगर (blk_mq_tag_is_reserved(rq->mq_hctx->sched_tags, rq->पूर्णांकernal_tag)) अणु
		bt = rq->mq_hctx->tags->breserved_tags;
		tag_offset = 0;
	पूर्ण अन्यथा अणु
		अगर (!hctx_may_queue(rq->mq_hctx, bt))
			वापस false;
	पूर्ण

	tag = __sbiपंचांगap_queue_get(bt);
	अगर (tag == BLK_MQ_NO_TAG)
		वापस false;

	rq->tag = tag + tag_offset;
	वापस true;
पूर्ण

अटल bool blk_mq_get_driver_tag(काष्ठा request *rq)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;

	अगर (rq->tag == BLK_MQ_NO_TAG && !__blk_mq_get_driver_tag(rq))
		वापस false;

	अगर ((hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED) &&
			!(rq->rq_flags & RQF_MQ_INFLIGHT)) अणु
		rq->rq_flags |= RQF_MQ_INFLIGHT;
		__blk_mq_inc_active_requests(hctx);
	पूर्ण
	hctx->tags->rqs[rq->tag] = rq;
	वापस true;
पूर्ण

अटल पूर्णांक blk_mq_dispatch_wake(रुको_queue_entry_t *रुको, अचिन्हित mode,
				पूर्णांक flags, व्योम *key)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;

	hctx = container_of(रुको, काष्ठा blk_mq_hw_ctx, dispatch_रुको);

	spin_lock(&hctx->dispatch_रुको_lock);
	अगर (!list_empty(&रुको->entry)) अणु
		काष्ठा sbiपंचांगap_queue *sbq;

		list_del_init(&रुको->entry);
		sbq = hctx->tags->biपंचांगap_tags;
		atomic_dec(&sbq->ws_active);
	पूर्ण
	spin_unlock(&hctx->dispatch_रुको_lock);

	blk_mq_run_hw_queue(hctx, true);
	वापस 1;
पूर्ण

/*
 * Mark us रुकोing क्रम a tag. For shared tags, this involves hooking us पूर्णांकo
 * the tag wakeups. For non-shared tags, we can simply mark us needing a
 * restart. For both हालs, take care to check the condition again after
 * marking us as रुकोing.
 */
अटल bool blk_mq_mark_tag_रुको(काष्ठा blk_mq_hw_ctx *hctx,
				 काष्ठा request *rq)
अणु
	काष्ठा sbiपंचांगap_queue *sbq = hctx->tags->biपंचांगap_tags;
	काष्ठा रुको_queue_head *wq;
	रुको_queue_entry_t *रुको;
	bool ret;

	अगर (!(hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED)) अणु
		blk_mq_sched_mark_restart_hctx(hctx);

		/*
		 * It's possible that a tag was मुक्तd in the winकरोw between the
		 * allocation failure and adding the hardware queue to the रुको
		 * queue.
		 *
		 * Don't clear RESTART here, someone अन्यथा could have set it.
		 * At most this will cost an extra queue run.
		 */
		वापस blk_mq_get_driver_tag(rq);
	पूर्ण

	रुको = &hctx->dispatch_रुको;
	अगर (!list_empty_careful(&रुको->entry))
		वापस false;

	wq = &bt_रुको_ptr(sbq, hctx)->रुको;

	spin_lock_irq(&wq->lock);
	spin_lock(&hctx->dispatch_रुको_lock);
	अगर (!list_empty(&रुको->entry)) अणु
		spin_unlock(&hctx->dispatch_रुको_lock);
		spin_unlock_irq(&wq->lock);
		वापस false;
	पूर्ण

	atomic_inc(&sbq->ws_active);
	रुको->flags &= ~WQ_FLAG_EXCLUSIVE;
	__add_रुको_queue(wq, रुको);

	/*
	 * It's possible that a tag was मुक्तd in the winकरोw between the
	 * allocation failure and adding the hardware queue to the रुको
	 * queue.
	 */
	ret = blk_mq_get_driver_tag(rq);
	अगर (!ret) अणु
		spin_unlock(&hctx->dispatch_रुको_lock);
		spin_unlock_irq(&wq->lock);
		वापस false;
	पूर्ण

	/*
	 * We got a tag, हटाओ ourselves from the रुको queue to ensure
	 * someone अन्यथा माला_लो the wakeup.
	 */
	list_del_init(&रुको->entry);
	atomic_dec(&sbq->ws_active);
	spin_unlock(&hctx->dispatch_रुको_lock);
	spin_unlock_irq(&wq->lock);

	वापस true;
पूर्ण

#घोषणा BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT  8
#घोषणा BLK_MQ_DISPATCH_BUSY_EWMA_FACTOR  4
/*
 * Update dispatch busy with the Exponential Weighted Moving Average(EWMA):
 * - EWMA is one simple way to compute running average value
 * - weight(7/8 and 1/8) is applied so that it can decrease exponentially
 * - take 4 as factor क्रम aव्योमing to get too small(0) result, and this
 *   factor करोesn't matter because EWMA decreases exponentially
 */
अटल व्योम blk_mq_update_dispatch_busy(काष्ठा blk_mq_hw_ctx *hctx, bool busy)
अणु
	अचिन्हित पूर्णांक ewma;

	अगर (hctx->queue->elevator)
		वापस;

	ewma = hctx->dispatch_busy;

	अगर (!ewma && !busy)
		वापस;

	ewma *= BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT - 1;
	अगर (busy)
		ewma += 1 << BLK_MQ_DISPATCH_BUSY_EWMA_FACTOR;
	ewma /= BLK_MQ_DISPATCH_BUSY_EWMA_WEIGHT;

	hctx->dispatch_busy = ewma;
पूर्ण

#घोषणा BLK_MQ_RESOURCE_DELAY	3		/* ms units */

अटल व्योम blk_mq_handle_dev_resource(काष्ठा request *rq,
				       काष्ठा list_head *list)
अणु
	काष्ठा request *next =
		list_first_entry_or_null(list, काष्ठा request, queuelist);

	/*
	 * If an I/O scheduler has been configured and we got a driver tag क्रम
	 * the next request alपढ़ोy, मुक्त it.
	 */
	अगर (next)
		blk_mq_put_driver_tag(next);

	list_add(&rq->queuelist, list);
	__blk_mq_requeue_request(rq);
पूर्ण

अटल व्योम blk_mq_handle_zone_resource(काष्ठा request *rq,
					काष्ठा list_head *zone_list)
अणु
	/*
	 * If we end up here it is because we cannot dispatch a request to a
	 * specअगरic zone due to LLD level zone-ग_लिखो locking or other zone
	 * related resource not being available. In this हाल, set the request
	 * aside in zone_list क्रम retrying it later.
	 */
	list_add(&rq->queuelist, zone_list);
	__blk_mq_requeue_request(rq);
पूर्ण

क्रमागत prep_dispatch अणु
	PREP_DISPATCH_OK,
	PREP_DISPATCH_NO_TAG,
	PREP_DISPATCH_NO_BUDGET,
पूर्ण;

अटल क्रमागत prep_dispatch blk_mq_prep_dispatch_rq(काष्ठा request *rq,
						  bool need_budget)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;
	पूर्णांक budget_token = -1;

	अगर (need_budget) अणु
		budget_token = blk_mq_get_dispatch_budget(rq->q);
		अगर (budget_token < 0) अणु
			blk_mq_put_driver_tag(rq);
			वापस PREP_DISPATCH_NO_BUDGET;
		पूर्ण
		blk_mq_set_rq_budget_token(rq, budget_token);
	पूर्ण

	अगर (!blk_mq_get_driver_tag(rq)) अणु
		/*
		 * The initial allocation attempt failed, so we need to
		 * rerun the hardware queue when a tag is मुक्तd. The
		 * रुकोqueue takes care of that. If the queue is run
		 * beक्रमe we add this entry back on the dispatch list,
		 * we'll re-run it below.
		 */
		अगर (!blk_mq_mark_tag_रुको(hctx, rq)) अणु
			/*
			 * All budमाला_लो not got from this function will be put
			 * together during handling partial dispatch
			 */
			अगर (need_budget)
				blk_mq_put_dispatch_budget(rq->q, budget_token);
			वापस PREP_DISPATCH_NO_TAG;
		पूर्ण
	पूर्ण

	वापस PREP_DISPATCH_OK;
पूर्ण

/* release all allocated budमाला_लो beक्रमe calling to blk_mq_dispatch_rq_list */
अटल व्योम blk_mq_release_budमाला_लो(काष्ठा request_queue *q,
		काष्ठा list_head *list)
अणु
	काष्ठा request *rq;

	list_क्रम_each_entry(rq, list, queuelist) अणु
		पूर्णांक budget_token = blk_mq_get_rq_budget_token(rq);

		अगर (budget_token >= 0)
			blk_mq_put_dispatch_budget(q, budget_token);
	पूर्ण
पूर्ण

/*
 * Returns true अगर we did some work AND can potentially करो more.
 */
bool blk_mq_dispatch_rq_list(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा list_head *list,
			     अचिन्हित पूर्णांक nr_budमाला_लो)
अणु
	क्रमागत prep_dispatch prep;
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा request *rq, *nxt;
	पूर्णांक errors, queued;
	blk_status_t ret = BLK_STS_OK;
	LIST_HEAD(zone_list);

	अगर (list_empty(list))
		वापस false;

	/*
	 * Now process all the entries, sending them to the driver.
	 */
	errors = queued = 0;
	करो अणु
		काष्ठा blk_mq_queue_data bd;

		rq = list_first_entry(list, काष्ठा request, queuelist);

		WARN_ON_ONCE(hctx != rq->mq_hctx);
		prep = blk_mq_prep_dispatch_rq(rq, !nr_budमाला_लो);
		अगर (prep != PREP_DISPATCH_OK)
			अवरोध;

		list_del_init(&rq->queuelist);

		bd.rq = rq;

		/*
		 * Flag last अगर we have no more requests, or अगर we have more
		 * but can't assign a driver tag to it.
		 */
		अगर (list_empty(list))
			bd.last = true;
		अन्यथा अणु
			nxt = list_first_entry(list, काष्ठा request, queuelist);
			bd.last = !blk_mq_get_driver_tag(nxt);
		पूर्ण

		/*
		 * once the request is queued to lld, no need to cover the
		 * budget any more
		 */
		अगर (nr_budमाला_लो)
			nr_budमाला_लो--;
		ret = q->mq_ops->queue_rq(hctx, &bd);
		चयन (ret) अणु
		हाल BLK_STS_OK:
			queued++;
			अवरोध;
		हाल BLK_STS_RESOURCE:
		हाल BLK_STS_DEV_RESOURCE:
			blk_mq_handle_dev_resource(rq, list);
			जाओ out;
		हाल BLK_STS_ZONE_RESOURCE:
			/*
			 * Move the request to zone_list and keep going through
			 * the dispatch list to find more requests the drive can
			 * accept.
			 */
			blk_mq_handle_zone_resource(rq, &zone_list);
			अवरोध;
		शेष:
			errors++;
			blk_mq_end_request(rq, ret);
		पूर्ण
	पूर्ण जबतक (!list_empty(list));
out:
	अगर (!list_empty(&zone_list))
		list_splice_tail_init(&zone_list, list);

	hctx->dispatched[queued_to_index(queued)]++;

	/* If we didn't flush the entire list, we could have told the driver
	 * there was more coming, but that turned out to be a lie.
	 */
	अगर ((!list_empty(list) || errors) && q->mq_ops->commit_rqs && queued)
		q->mq_ops->commit_rqs(hctx);
	/*
	 * Any items that need requeuing? Stuff them पूर्णांकo hctx->dispatch,
	 * that is where we will जारी on next queue run.
	 */
	अगर (!list_empty(list)) अणु
		bool needs_restart;
		/* For non-shared tags, the RESTART check will suffice */
		bool no_tag = prep == PREP_DISPATCH_NO_TAG &&
			(hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED);
		bool no_budget_avail = prep == PREP_DISPATCH_NO_BUDGET;

		अगर (nr_budमाला_लो)
			blk_mq_release_budमाला_लो(q, list);

		spin_lock(&hctx->lock);
		list_splice_tail_init(list, &hctx->dispatch);
		spin_unlock(&hctx->lock);

		/*
		 * Order adding requests to hctx->dispatch and checking
		 * SCHED_RESTART flag. The pair of this smp_mb() is the one
		 * in blk_mq_sched_restart(). Aव्योम restart code path to
		 * miss the new added requests to hctx->dispatch, meanसमय
		 * SCHED_RESTART is observed here.
		 */
		smp_mb();

		/*
		 * If SCHED_RESTART was set by the caller of this function and
		 * it is no दीर्घer set that means that it was cleared by another
		 * thपढ़ो and hence that a queue rerun is needed.
		 *
		 * If 'no_tag' is set, that means that we failed getting
		 * a driver tag with an I/O scheduler attached. If our dispatch
		 * रुकोqueue is no दीर्घer active, ensure that we run the queue
		 * AFTER adding our entries back to the list.
		 *
		 * If no I/O scheduler has been configured it is possible that
		 * the hardware queue got stopped and restarted beक्रमe requests
		 * were pushed back onto the dispatch list. Rerun the queue to
		 * aव्योम starvation. Notes:
		 * - blk_mq_run_hw_queue() checks whether or not a queue has
		 *   been stopped beक्रमe rerunning a queue.
		 * - Some but not all block drivers stop a queue beक्रमe
		 *   वापसing BLK_STS_RESOURCE. Two exceptions are scsi-mq
		 *   and dm-rq.
		 *
		 * If driver वापसs BLK_STS_RESOURCE and SCHED_RESTART
		 * bit is set, run queue after a delay to aव्योम IO stalls
		 * that could otherwise occur अगर the queue is idle.  We'll करो
		 * similar अगर we couldn't get budget and SCHED_RESTART is set.
		 */
		needs_restart = blk_mq_sched_needs_restart(hctx);
		अगर (!needs_restart ||
		    (no_tag && list_empty_careful(&hctx->dispatch_रुको.entry)))
			blk_mq_run_hw_queue(hctx, true);
		अन्यथा अगर (needs_restart && (ret == BLK_STS_RESOURCE ||
					   no_budget_avail))
			blk_mq_delay_run_hw_queue(hctx, BLK_MQ_RESOURCE_DELAY);

		blk_mq_update_dispatch_busy(hctx, true);
		वापस false;
	पूर्ण अन्यथा
		blk_mq_update_dispatch_busy(hctx, false);

	वापस (queued + errors) != 0;
पूर्ण

/**
 * __blk_mq_run_hw_queue - Run a hardware queue.
 * @hctx: Poपूर्णांकer to the hardware queue to run.
 *
 * Send pending requests to the hardware.
 */
अटल व्योम __blk_mq_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	पूर्णांक srcu_idx;

	/*
	 * We can't run the queue अंतरभूत with पूर्णांकs disabled. Ensure that
	 * we catch bad users of this early.
	 */
	WARN_ON_ONCE(in_पूर्णांकerrupt());

	might_sleep_अगर(hctx->flags & BLK_MQ_F_BLOCKING);

	hctx_lock(hctx, &srcu_idx);
	blk_mq_sched_dispatch_requests(hctx);
	hctx_unlock(hctx, srcu_idx);
पूर्ण

अटल अंतरभूत पूर्णांक blk_mq_first_mapped_cpu(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	पूर्णांक cpu = cpumask_first_and(hctx->cpumask, cpu_online_mask);

	अगर (cpu >= nr_cpu_ids)
		cpu = cpumask_first(hctx->cpumask);
	वापस cpu;
पूर्ण

/*
 * It'd be great अगर the workqueue API had a way to pass
 * in a mask and had some smarts क्रम more clever placement.
 * For now we just round-robin here, चयनing क्रम every
 * BLK_MQ_CPU_WORK_BATCH queued items.
 */
अटल पूर्णांक blk_mq_hctx_next_cpu(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	bool tried = false;
	पूर्णांक next_cpu = hctx->next_cpu;

	अगर (hctx->queue->nr_hw_queues == 1)
		वापस WORK_CPU_UNBOUND;

	अगर (--hctx->next_cpu_batch <= 0) अणु
select_cpu:
		next_cpu = cpumask_next_and(next_cpu, hctx->cpumask,
				cpu_online_mask);
		अगर (next_cpu >= nr_cpu_ids)
			next_cpu = blk_mq_first_mapped_cpu(hctx);
		hctx->next_cpu_batch = BLK_MQ_CPU_WORK_BATCH;
	पूर्ण

	/*
	 * Do unbound schedule अगर we can't find a online CPU क्रम this hctx,
	 * and it should only happen in the path of handling CPU DEAD.
	 */
	अगर (!cpu_online(next_cpu)) अणु
		अगर (!tried) अणु
			tried = true;
			जाओ select_cpu;
		पूर्ण

		/*
		 * Make sure to re-select CPU next समय once after CPUs
		 * in hctx->cpumask become online again.
		 */
		hctx->next_cpu = next_cpu;
		hctx->next_cpu_batch = 1;
		वापस WORK_CPU_UNBOUND;
	पूर्ण

	hctx->next_cpu = next_cpu;
	वापस next_cpu;
पूर्ण

/**
 * __blk_mq_delay_run_hw_queue - Run (or schedule to run) a hardware queue.
 * @hctx: Poपूर्णांकer to the hardware queue to run.
 * @async: If we want to run the queue asynchronously.
 * @msecs: Milliseconds of delay to रुको beक्रमe running the queue.
 *
 * If !@async, try to run the queue now. Else, run the queue asynchronously and
 * with a delay of @msecs.
 */
अटल व्योम __blk_mq_delay_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, bool async,
					अचिन्हित दीर्घ msecs)
अणु
	अगर (unlikely(blk_mq_hctx_stopped(hctx)))
		वापस;

	अगर (!async && !(hctx->flags & BLK_MQ_F_BLOCKING)) अणु
		पूर्णांक cpu = get_cpu();
		अगर (cpumask_test_cpu(cpu, hctx->cpumask)) अणु
			__blk_mq_run_hw_queue(hctx);
			put_cpu();
			वापस;
		पूर्ण

		put_cpu();
	पूर्ण

	kblockd_mod_delayed_work_on(blk_mq_hctx_next_cpu(hctx), &hctx->run_work,
				    msecs_to_jअगरfies(msecs));
पूर्ण

/**
 * blk_mq_delay_run_hw_queue - Run a hardware queue asynchronously.
 * @hctx: Poपूर्णांकer to the hardware queue to run.
 * @msecs: Milliseconds of delay to रुको beक्रमe running the queue.
 *
 * Run a hardware queue asynchronously with a delay of @msecs.
 */
व्योम blk_mq_delay_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित दीर्घ msecs)
अणु
	__blk_mq_delay_run_hw_queue(hctx, true, msecs);
पूर्ण
EXPORT_SYMBOL(blk_mq_delay_run_hw_queue);

/**
 * blk_mq_run_hw_queue - Start to run a hardware queue.
 * @hctx: Poपूर्णांकer to the hardware queue to run.
 * @async: If we want to run the queue asynchronously.
 *
 * Check अगर the request queue is not in a quiesced state and अगर there are
 * pending requests to be sent. If this is true, run the queue to send requests
 * to hardware.
 */
व्योम blk_mq_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, bool async)
अणु
	पूर्णांक srcu_idx;
	bool need_run;

	/*
	 * When queue is quiesced, we may be चयनing io scheduler, or
	 * updating nr_hw_queues, or other things, and we can't run queue
	 * any more, even __blk_mq_hctx_has_pending() can't be called safely.
	 *
	 * And queue will be rerun in blk_mq_unquiesce_queue() अगर it is
	 * quiesced.
	 */
	hctx_lock(hctx, &srcu_idx);
	need_run = !blk_queue_quiesced(hctx->queue) &&
		blk_mq_hctx_has_pending(hctx);
	hctx_unlock(hctx, srcu_idx);

	अगर (need_run)
		__blk_mq_delay_run_hw_queue(hctx, async, 0);
पूर्ण
EXPORT_SYMBOL(blk_mq_run_hw_queue);

/*
 * Is the request queue handled by an IO scheduler that करोes not respect
 * hardware queues when dispatching?
 */
अटल bool blk_mq_has_sqsched(काष्ठा request_queue *q)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e && e->type->ops.dispatch_request &&
	    !(e->type->elevator_features & ELEVATOR_F_MQ_AWARE))
		वापस true;
	वापस false;
पूर्ण

/*
 * Return prefered queue to dispatch from (अगर any) क्रम non-mq aware IO
 * scheduler.
 */
अटल काष्ठा blk_mq_hw_ctx *blk_mq_get_sq_hctx(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;

	/*
	 * If the IO scheduler करोes not respect hardware queues when
	 * dispatching, we just करोn't bother with multiple HW queues and
	 * dispatch from hctx क्रम the current CPU since running multiple queues
	 * just causes lock contention inside the scheduler and poपूर्णांकless cache
	 * bouncing.
	 */
	hctx = blk_mq_map_queue_type(q, HCTX_TYPE_DEFAULT,
				     raw_smp_processor_id());
	अगर (!blk_mq_hctx_stopped(hctx))
		वापस hctx;
	वापस शून्य;
पूर्ण

/**
 * blk_mq_run_hw_queues - Run all hardware queues in a request queue.
 * @q: Poपूर्णांकer to the request queue to run.
 * @async: If we want to run the queue asynchronously.
 */
व्योम blk_mq_run_hw_queues(काष्ठा request_queue *q, bool async)
अणु
	काष्ठा blk_mq_hw_ctx *hctx, *sq_hctx;
	पूर्णांक i;

	sq_hctx = शून्य;
	अगर (blk_mq_has_sqsched(q))
		sq_hctx = blk_mq_get_sq_hctx(q);
	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (blk_mq_hctx_stopped(hctx))
			जारी;
		/*
		 * Dispatch from this hctx either अगर there's no hctx preferred
		 * by IO scheduler or अगर it has requests that bypass the
		 * scheduler.
		 */
		अगर (!sq_hctx || sq_hctx == hctx ||
		    !list_empty_careful(&hctx->dispatch))
			blk_mq_run_hw_queue(hctx, async);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(blk_mq_run_hw_queues);

/**
 * blk_mq_delay_run_hw_queues - Run all hardware queues asynchronously.
 * @q: Poपूर्णांकer to the request queue to run.
 * @msecs: Milliseconds of delay to रुको beक्रमe running the queues.
 */
व्योम blk_mq_delay_run_hw_queues(काष्ठा request_queue *q, अचिन्हित दीर्घ msecs)
अणु
	काष्ठा blk_mq_hw_ctx *hctx, *sq_hctx;
	पूर्णांक i;

	sq_hctx = शून्य;
	अगर (blk_mq_has_sqsched(q))
		sq_hctx = blk_mq_get_sq_hctx(q);
	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (blk_mq_hctx_stopped(hctx))
			जारी;
		/*
		 * Dispatch from this hctx either अगर there's no hctx preferred
		 * by IO scheduler or अगर it has requests that bypass the
		 * scheduler.
		 */
		अगर (!sq_hctx || sq_hctx == hctx ||
		    !list_empty_careful(&hctx->dispatch))
			blk_mq_delay_run_hw_queue(hctx, msecs);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(blk_mq_delay_run_hw_queues);

/**
 * blk_mq_queue_stopped() - check whether one or more hctxs have been stopped
 * @q: request queue.
 *
 * The caller is responsible क्रम serializing this function against
 * blk_mq_अणुstart,stopपूर्ण_hw_queue().
 */
bool blk_mq_queue_stopped(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		अगर (blk_mq_hctx_stopped(hctx))
			वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(blk_mq_queue_stopped);

/*
 * This function is often used क्रम pausing .queue_rq() by driver when
 * there isn't enough resource or some conditions aren't satisfied, and
 * BLK_STS_RESOURCE is usually वापसed.
 *
 * We करो not guarantee that dispatch can be drained or blocked
 * after blk_mq_stop_hw_queue() वापसs. Please use
 * blk_mq_quiesce_queue() क्रम that requirement.
 */
व्योम blk_mq_stop_hw_queue(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	cancel_delayed_work(&hctx->run_work);

	set_bit(BLK_MQ_S_STOPPED, &hctx->state);
पूर्ण
EXPORT_SYMBOL(blk_mq_stop_hw_queue);

/*
 * This function is often used क्रम pausing .queue_rq() by driver when
 * there isn't enough resource or some conditions aren't satisfied, and
 * BLK_STS_RESOURCE is usually वापसed.
 *
 * We करो not guarantee that dispatch can be drained or blocked
 * after blk_mq_stop_hw_queues() वापसs. Please use
 * blk_mq_quiesce_queue() क्रम that requirement.
 */
व्योम blk_mq_stop_hw_queues(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_stop_hw_queue(hctx);
पूर्ण
EXPORT_SYMBOL(blk_mq_stop_hw_queues);

व्योम blk_mq_start_hw_queue(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	clear_bit(BLK_MQ_S_STOPPED, &hctx->state);

	blk_mq_run_hw_queue(hctx, false);
पूर्ण
EXPORT_SYMBOL(blk_mq_start_hw_queue);

व्योम blk_mq_start_hw_queues(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_start_hw_queue(hctx);
पूर्ण
EXPORT_SYMBOL(blk_mq_start_hw_queues);

व्योम blk_mq_start_stopped_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, bool async)
अणु
	अगर (!blk_mq_hctx_stopped(hctx))
		वापस;

	clear_bit(BLK_MQ_S_STOPPED, &hctx->state);
	blk_mq_run_hw_queue(hctx, async);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_start_stopped_hw_queue);

व्योम blk_mq_start_stopped_hw_queues(काष्ठा request_queue *q, bool async)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_start_stopped_hw_queue(hctx, async);
पूर्ण
EXPORT_SYMBOL(blk_mq_start_stopped_hw_queues);

अटल व्योम blk_mq_run_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;

	hctx = container_of(work, काष्ठा blk_mq_hw_ctx, run_work.work);

	/*
	 * If we are stopped, करोn't run the queue.
	 */
	अगर (blk_mq_hctx_stopped(hctx))
		वापस;

	__blk_mq_run_hw_queue(hctx);
पूर्ण

अटल अंतरभूत व्योम __blk_mq_insert_req_list(काष्ठा blk_mq_hw_ctx *hctx,
					    काष्ठा request *rq,
					    bool at_head)
अणु
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;
	क्रमागत hctx_type type = hctx->type;

	lockdep_निश्चित_held(&ctx->lock);

	trace_block_rq_insert(rq);

	अगर (at_head)
		list_add(&rq->queuelist, &ctx->rq_lists[type]);
	अन्यथा
		list_add_tail(&rq->queuelist, &ctx->rq_lists[type]);
पूर्ण

व्योम __blk_mq_insert_request(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा request *rq,
			     bool at_head)
अणु
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;

	lockdep_निश्चित_held(&ctx->lock);

	__blk_mq_insert_req_list(hctx, rq, at_head);
	blk_mq_hctx_mark_pending(hctx, ctx);
पूर्ण

/**
 * blk_mq_request_bypass_insert - Insert a request at dispatch list.
 * @rq: Poपूर्णांकer to request to be inserted.
 * @at_head: true अगर the request should be inserted at the head of the list.
 * @run_queue: If we should run the hardware queue after inserting the request.
 *
 * Should only be used carefully, when the caller knows we want to
 * bypass a potential IO scheduler on the target device.
 */
व्योम blk_mq_request_bypass_insert(काष्ठा request *rq, bool at_head,
				  bool run_queue)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;

	spin_lock(&hctx->lock);
	अगर (at_head)
		list_add(&rq->queuelist, &hctx->dispatch);
	अन्यथा
		list_add_tail(&rq->queuelist, &hctx->dispatch);
	spin_unlock(&hctx->lock);

	अगर (run_queue)
		blk_mq_run_hw_queue(hctx, false);
पूर्ण

व्योम blk_mq_insert_requests(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा blk_mq_ctx *ctx,
			    काष्ठा list_head *list)

अणु
	काष्ठा request *rq;
	क्रमागत hctx_type type = hctx->type;

	/*
	 * preemption करोesn't flush plug list, so it's possible ctx->cpu is
	 * offline now
	 */
	list_क्रम_each_entry(rq, list, queuelist) अणु
		BUG_ON(rq->mq_ctx != ctx);
		trace_block_rq_insert(rq);
	पूर्ण

	spin_lock(&ctx->lock);
	list_splice_tail_init(list, &ctx->rq_lists[type]);
	blk_mq_hctx_mark_pending(hctx, ctx);
	spin_unlock(&ctx->lock);
पूर्ण

अटल पूर्णांक plug_rq_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		       स्थिर काष्ठा list_head *b)
अणु
	काष्ठा request *rqa = container_of(a, काष्ठा request, queuelist);
	काष्ठा request *rqb = container_of(b, काष्ठा request, queuelist);

	अगर (rqa->mq_ctx != rqb->mq_ctx)
		वापस rqa->mq_ctx > rqb->mq_ctx;
	अगर (rqa->mq_hctx != rqb->mq_hctx)
		वापस rqa->mq_hctx > rqb->mq_hctx;

	वापस blk_rq_pos(rqa) > blk_rq_pos(rqb);
पूर्ण

व्योम blk_mq_flush_plug_list(काष्ठा blk_plug *plug, bool from_schedule)
अणु
	LIST_HEAD(list);

	अगर (list_empty(&plug->mq_list))
		वापस;
	list_splice_init(&plug->mq_list, &list);

	अगर (plug->rq_count > 2 && plug->multiple_queues)
		list_sort(शून्य, &list, plug_rq_cmp);

	plug->rq_count = 0;

	करो अणु
		काष्ठा list_head rq_list;
		काष्ठा request *rq, *head_rq = list_entry_rq(list.next);
		काष्ठा list_head *pos = &head_rq->queuelist; /* skip first */
		काष्ठा blk_mq_hw_ctx *this_hctx = head_rq->mq_hctx;
		काष्ठा blk_mq_ctx *this_ctx = head_rq->mq_ctx;
		अचिन्हित पूर्णांक depth = 1;

		list_क्रम_each_जारी(pos, &list) अणु
			rq = list_entry_rq(pos);
			BUG_ON(!rq->q);
			अगर (rq->mq_hctx != this_hctx || rq->mq_ctx != this_ctx)
				अवरोध;
			depth++;
		पूर्ण

		list_cut_beक्रमe(&rq_list, &list, pos);
		trace_block_unplug(head_rq->q, depth, !from_schedule);
		blk_mq_sched_insert_requests(this_hctx, this_ctx, &rq_list,
						from_schedule);
	पूर्ण जबतक(!list_empty(&list));
पूर्ण

अटल व्योम blk_mq_bio_to_request(काष्ठा request *rq, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	पूर्णांक err;

	अगर (bio->bi_opf & REQ_RAHEAD)
		rq->cmd_flags |= REQ_FAILFAST_MASK;

	rq->__sector = bio->bi_iter.bi_sector;
	rq->ग_लिखो_hपूर्णांक = bio->bi_ग_लिखो_hपूर्णांक;
	blk_rq_bio_prep(rq, bio, nr_segs);

	/* This can't fail, since GFP_NOIO includes __GFP_सूचीECT_RECLAIM. */
	err = blk_crypto_rq_bio_prep(rq, bio, GFP_NOIO);
	WARN_ON_ONCE(err);

	blk_account_io_start(rq);
पूर्ण

अटल blk_status_t __blk_mq_issue_directly(काष्ठा blk_mq_hw_ctx *hctx,
					    काष्ठा request *rq,
					    blk_qc_t *cookie, bool last)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा blk_mq_queue_data bd = अणु
		.rq = rq,
		.last = last,
	पूर्ण;
	blk_qc_t new_cookie;
	blk_status_t ret;

	new_cookie = request_to_qc_t(hctx, rq);

	/*
	 * For OK queue, we are करोne. For error, caller may समाप्त it.
	 * Any other error (busy), just add it to our list as we
	 * previously would have करोne.
	 */
	ret = q->mq_ops->queue_rq(hctx, &bd);
	चयन (ret) अणु
	हाल BLK_STS_OK:
		blk_mq_update_dispatch_busy(hctx, false);
		*cookie = new_cookie;
		अवरोध;
	हाल BLK_STS_RESOURCE:
	हाल BLK_STS_DEV_RESOURCE:
		blk_mq_update_dispatch_busy(hctx, true);
		__blk_mq_requeue_request(rq);
		अवरोध;
	शेष:
		blk_mq_update_dispatch_busy(hctx, false);
		*cookie = BLK_QC_T_NONE;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल blk_status_t __blk_mq_try_issue_directly(काष्ठा blk_mq_hw_ctx *hctx,
						काष्ठा request *rq,
						blk_qc_t *cookie,
						bool bypass_insert, bool last)
अणु
	काष्ठा request_queue *q = rq->q;
	bool run_queue = true;
	पूर्णांक budget_token;

	/*
	 * RCU or SRCU पढ़ो lock is needed beक्रमe checking quiesced flag.
	 *
	 * When queue is stopped or quiesced, ignore 'bypass_insert' from
	 * blk_mq_request_issue_directly(), and वापस BLK_STS_OK to caller,
	 * and aव्योम driver to try to dispatch again.
	 */
	अगर (blk_mq_hctx_stopped(hctx) || blk_queue_quiesced(q)) अणु
		run_queue = false;
		bypass_insert = false;
		जाओ insert;
	पूर्ण

	अगर (q->elevator && !bypass_insert)
		जाओ insert;

	budget_token = blk_mq_get_dispatch_budget(q);
	अगर (budget_token < 0)
		जाओ insert;

	blk_mq_set_rq_budget_token(rq, budget_token);

	अगर (!blk_mq_get_driver_tag(rq)) अणु
		blk_mq_put_dispatch_budget(q, budget_token);
		जाओ insert;
	पूर्ण

	वापस __blk_mq_issue_directly(hctx, rq, cookie, last);
insert:
	अगर (bypass_insert)
		वापस BLK_STS_RESOURCE;

	blk_mq_sched_insert_request(rq, false, run_queue, false);

	वापस BLK_STS_OK;
पूर्ण

/**
 * blk_mq_try_issue_directly - Try to send a request directly to device driver.
 * @hctx: Poपूर्णांकer of the associated hardware queue.
 * @rq: Poपूर्णांकer to request to be sent.
 * @cookie: Request queue cookie.
 *
 * If the device has enough resources to accept a new request now, send the
 * request directly to device driver. Else, insert at hctx->dispatch queue, so
 * we can try send it another समय in the future. Requests inserted at this
 * queue have higher priority.
 */
अटल व्योम blk_mq_try_issue_directly(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा request *rq, blk_qc_t *cookie)
अणु
	blk_status_t ret;
	पूर्णांक srcu_idx;

	might_sleep_अगर(hctx->flags & BLK_MQ_F_BLOCKING);

	hctx_lock(hctx, &srcu_idx);

	ret = __blk_mq_try_issue_directly(hctx, rq, cookie, false, true);
	अगर (ret == BLK_STS_RESOURCE || ret == BLK_STS_DEV_RESOURCE)
		blk_mq_request_bypass_insert(rq, false, true);
	अन्यथा अगर (ret != BLK_STS_OK)
		blk_mq_end_request(rq, ret);

	hctx_unlock(hctx, srcu_idx);
पूर्ण

blk_status_t blk_mq_request_issue_directly(काष्ठा request *rq, bool last)
अणु
	blk_status_t ret;
	पूर्णांक srcu_idx;
	blk_qc_t unused_cookie;
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;

	hctx_lock(hctx, &srcu_idx);
	ret = __blk_mq_try_issue_directly(hctx, rq, &unused_cookie, true, last);
	hctx_unlock(hctx, srcu_idx);

	वापस ret;
पूर्ण

व्योम blk_mq_try_issue_list_directly(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा list_head *list)
अणु
	पूर्णांक queued = 0;
	पूर्णांक errors = 0;

	जबतक (!list_empty(list)) अणु
		blk_status_t ret;
		काष्ठा request *rq = list_first_entry(list, काष्ठा request,
				queuelist);

		list_del_init(&rq->queuelist);
		ret = blk_mq_request_issue_directly(rq, list_empty(list));
		अगर (ret != BLK_STS_OK) अणु
			अगर (ret == BLK_STS_RESOURCE ||
					ret == BLK_STS_DEV_RESOURCE) अणु
				blk_mq_request_bypass_insert(rq, false,
							list_empty(list));
				अवरोध;
			पूर्ण
			blk_mq_end_request(rq, ret);
			errors++;
		पूर्ण अन्यथा
			queued++;
	पूर्ण

	/*
	 * If we didn't flush the entire list, we could have told
	 * the driver there was more coming, but that turned out to
	 * be a lie.
	 */
	अगर ((!list_empty(list) || errors) &&
	     hctx->queue->mq_ops->commit_rqs && queued)
		hctx->queue->mq_ops->commit_rqs(hctx);
पूर्ण

अटल व्योम blk_add_rq_to_plug(काष्ठा blk_plug *plug, काष्ठा request *rq)
अणु
	list_add_tail(&rq->queuelist, &plug->mq_list);
	plug->rq_count++;
	अगर (!plug->multiple_queues && !list_is_singular(&plug->mq_list)) अणु
		काष्ठा request *पंचांगp;

		पंचांगp = list_first_entry(&plug->mq_list, काष्ठा request,
						queuelist);
		अगर (पंचांगp->q != rq->q)
			plug->multiple_queues = true;
	पूर्ण
पूर्ण

/**
 * blk_mq_submit_bio - Create and send a request to block device.
 * @bio: Bio poपूर्णांकer.
 *
 * Builds up a request काष्ठाure from @q and @bio and send to the device. The
 * request may not be queued directly to hardware अगर:
 * * This request can be merged with another one
 * * We want to place request at plug queue क्रम possible future merging
 * * There is an IO scheduler active at this queue
 *
 * It will not queue the request अगर there is an error with the bio, or at the
 * request creation.
 *
 * Returns: Request queue cookie.
 */
blk_qc_t blk_mq_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	स्थिर पूर्णांक is_sync = op_is_sync(bio->bi_opf);
	स्थिर पूर्णांक is_flush_fua = op_is_flush(bio->bi_opf);
	काष्ठा blk_mq_alloc_data data = अणु
		.q		= q,
	पूर्ण;
	काष्ठा request *rq;
	काष्ठा blk_plug *plug;
	काष्ठा request *same_queue_rq = शून्य;
	अचिन्हित पूर्णांक nr_segs;
	blk_qc_t cookie;
	blk_status_t ret;
	bool hipri;

	blk_queue_bounce(q, &bio);
	__blk_queue_split(&bio, &nr_segs);

	अगर (!bio_पूर्णांकegrity_prep(bio))
		जाओ queue_निकास;

	अगर (!is_flush_fua && !blk_queue_nomerges(q) &&
	    blk_attempt_plug_merge(q, bio, nr_segs, &same_queue_rq))
		जाओ queue_निकास;

	अगर (blk_mq_sched_bio_merge(q, bio, nr_segs))
		जाओ queue_निकास;

	rq_qos_throttle(q, bio);

	hipri = bio->bi_opf & REQ_HIPRI;

	data.cmd_flags = bio->bi_opf;
	rq = __blk_mq_alloc_request(&data);
	अगर (unlikely(!rq)) अणु
		rq_qos_cleanup(q, bio);
		अगर (bio->bi_opf & REQ_NOWAIT)
			bio_wouldblock_error(bio);
		जाओ queue_निकास;
	पूर्ण

	trace_block_getrq(bio);

	rq_qos_track(q, rq, bio);

	cookie = request_to_qc_t(data.hctx, rq);

	blk_mq_bio_to_request(rq, bio, nr_segs);

	ret = blk_crypto_init_request(rq);
	अगर (ret != BLK_STS_OK) अणु
		bio->bi_status = ret;
		bio_endio(bio);
		blk_mq_मुक्त_request(rq);
		वापस BLK_QC_T_NONE;
	पूर्ण

	plug = blk_mq_plug(q, bio);
	अगर (unlikely(is_flush_fua)) अणु
		/* Bypass scheduler क्रम flush requests */
		blk_insert_flush(rq);
		blk_mq_run_hw_queue(data.hctx, true);
	पूर्ण अन्यथा अगर (plug && (q->nr_hw_queues == 1 ||
		   blk_mq_is_sbiपंचांगap_shared(rq->mq_hctx->flags) ||
		   q->mq_ops->commit_rqs || !blk_queue_nonrot(q))) अणु
		/*
		 * Use plugging अगर we have a ->commit_rqs() hook as well, as
		 * we know the driver uses bd->last in a smart fashion.
		 *
		 * Use normal plugging अगर this disk is slow HDD, as sequential
		 * IO may benefit a lot from plug merging.
		 */
		अचिन्हित पूर्णांक request_count = plug->rq_count;
		काष्ठा request *last = शून्य;

		अगर (!request_count)
			trace_block_plug(q);
		अन्यथा
			last = list_entry_rq(plug->mq_list.prev);

		अगर (request_count >= BLK_MAX_REQUEST_COUNT || (last &&
		    blk_rq_bytes(last) >= BLK_PLUG_FLUSH_SIZE)) अणु
			blk_flush_plug_list(plug, false);
			trace_block_plug(q);
		पूर्ण

		blk_add_rq_to_plug(plug, rq);
	पूर्ण अन्यथा अगर (q->elevator) अणु
		/* Insert the request at the IO scheduler queue */
		blk_mq_sched_insert_request(rq, false, true, true);
	पूर्ण अन्यथा अगर (plug && !blk_queue_nomerges(q)) अणु
		/*
		 * We करो limited plugging. If the bio can be merged, करो that.
		 * Otherwise the existing request in the plug list will be
		 * issued. So the plug list will have one request at most
		 * The plug list might get flushed beक्रमe this. If that happens,
		 * the plug list is empty, and same_queue_rq is invalid.
		 */
		अगर (list_empty(&plug->mq_list))
			same_queue_rq = शून्य;
		अगर (same_queue_rq) अणु
			list_del_init(&same_queue_rq->queuelist);
			plug->rq_count--;
		पूर्ण
		blk_add_rq_to_plug(plug, rq);
		trace_block_plug(q);

		अगर (same_queue_rq) अणु
			data.hctx = same_queue_rq->mq_hctx;
			trace_block_unplug(q, 1, true);
			blk_mq_try_issue_directly(data.hctx, same_queue_rq,
					&cookie);
		पूर्ण
	पूर्ण अन्यथा अगर ((q->nr_hw_queues > 1 && is_sync) ||
			!data.hctx->dispatch_busy) अणु
		/*
		 * There is no scheduler and we can try to send directly
		 * to the hardware.
		 */
		blk_mq_try_issue_directly(data.hctx, rq, &cookie);
	पूर्ण अन्यथा अणु
		/* Default हाल. */
		blk_mq_sched_insert_request(rq, false, true, true);
	पूर्ण

	अगर (!hipri)
		वापस BLK_QC_T_NONE;
	वापस cookie;
queue_निकास:
	blk_queue_निकास(q);
	वापस BLK_QC_T_NONE;
पूर्ण

व्योम blk_mq_मुक्त_rqs(काष्ठा blk_mq_tag_set *set, काष्ठा blk_mq_tags *tags,
		     अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा page *page;

	अगर (tags->rqs && set->ops->निकास_request) अणु
		पूर्णांक i;

		क्रम (i = 0; i < tags->nr_tags; i++) अणु
			काष्ठा request *rq = tags->अटल_rqs[i];

			अगर (!rq)
				जारी;
			set->ops->निकास_request(set, rq, hctx_idx);
			tags->अटल_rqs[i] = शून्य;
		पूर्ण
	पूर्ण

	जबतक (!list_empty(&tags->page_list)) अणु
		page = list_first_entry(&tags->page_list, काष्ठा page, lru);
		list_del_init(&page->lru);
		/*
		 * Remove kmemleak object previously allocated in
		 * blk_mq_alloc_rqs().
		 */
		kmemleak_मुक्त(page_address(page));
		__मुक्त_pages(page, page->निजी);
	पूर्ण
पूर्ण

व्योम blk_mq_मुक्त_rq_map(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक flags)
अणु
	kमुक्त(tags->rqs);
	tags->rqs = शून्य;
	kमुक्त(tags->अटल_rqs);
	tags->अटल_rqs = शून्य;

	blk_mq_मुक्त_tags(tags, flags);
पूर्ण

काष्ठा blk_mq_tags *blk_mq_alloc_rq_map(काष्ठा blk_mq_tag_set *set,
					अचिन्हित पूर्णांक hctx_idx,
					अचिन्हित पूर्णांक nr_tags,
					अचिन्हित पूर्णांक reserved_tags,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा blk_mq_tags *tags;
	पूर्णांक node;

	node = blk_mq_hw_queue_to_node(&set->map[HCTX_TYPE_DEFAULT], hctx_idx);
	अगर (node == NUMA_NO_NODE)
		node = set->numa_node;

	tags = blk_mq_init_tags(nr_tags, reserved_tags, node, flags);
	अगर (!tags)
		वापस शून्य;

	tags->rqs = kसुस्मृति_node(nr_tags, माप(काष्ठा request *),
				 GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY,
				 node);
	अगर (!tags->rqs) अणु
		blk_mq_मुक्त_tags(tags, flags);
		वापस शून्य;
	पूर्ण

	tags->अटल_rqs = kसुस्मृति_node(nr_tags, माप(काष्ठा request *),
					GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY,
					node);
	अगर (!tags->अटल_rqs) अणु
		kमुक्त(tags->rqs);
		blk_mq_मुक्त_tags(tags, flags);
		वापस शून्य;
	पूर्ण

	वापस tags;
पूर्ण

अटल माप_प्रकार order_to_size(अचिन्हित पूर्णांक order)
अणु
	वापस (माप_प्रकार)PAGE_SIZE << order;
पूर्ण

अटल पूर्णांक blk_mq_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
			       अचिन्हित पूर्णांक hctx_idx, पूर्णांक node)
अणु
	पूर्णांक ret;

	अगर (set->ops->init_request) अणु
		ret = set->ops->init_request(set, rq, hctx_idx, node);
		अगर (ret)
			वापस ret;
	पूर्ण

	WRITE_ONCE(rq->state, MQ_RQ_IDLE);
	वापस 0;
पूर्ण

पूर्णांक blk_mq_alloc_rqs(काष्ठा blk_mq_tag_set *set, काष्ठा blk_mq_tags *tags,
		     अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक i, j, entries_per_page, max_order = 4;
	माप_प्रकार rq_size, left;
	पूर्णांक node;

	node = blk_mq_hw_queue_to_node(&set->map[HCTX_TYPE_DEFAULT], hctx_idx);
	अगर (node == NUMA_NO_NODE)
		node = set->numa_node;

	INIT_LIST_HEAD(&tags->page_list);

	/*
	 * rq_size is the size of the request plus driver payload, rounded
	 * to the cacheline size
	 */
	rq_size = round_up(माप(काष्ठा request) + set->cmd_size,
				cache_line_size());
	left = rq_size * depth;

	क्रम (i = 0; i < depth; ) अणु
		पूर्णांक this_order = max_order;
		काष्ठा page *page;
		पूर्णांक to_करो;
		व्योम *p;

		जबतक (this_order && left < order_to_size(this_order - 1))
			this_order--;

		करो अणु
			page = alloc_pages_node(node,
				GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY | __GFP_ZERO,
				this_order);
			अगर (page)
				अवरोध;
			अगर (!this_order--)
				अवरोध;
			अगर (order_to_size(this_order) < rq_size)
				अवरोध;
		पूर्ण जबतक (1);

		अगर (!page)
			जाओ fail;

		page->निजी = this_order;
		list_add_tail(&page->lru, &tags->page_list);

		p = page_address(page);
		/*
		 * Allow kmemleak to scan these pages as they contain poपूर्णांकers
		 * to additional allocations like via ops->init_request().
		 */
		kmemleak_alloc(p, order_to_size(this_order), 1, GFP_NOIO);
		entries_per_page = order_to_size(this_order) / rq_size;
		to_करो = min(entries_per_page, depth - i);
		left -= to_करो * rq_size;
		क्रम (j = 0; j < to_करो; j++) अणु
			काष्ठा request *rq = p;

			tags->अटल_rqs[i] = rq;
			अगर (blk_mq_init_request(set, rq, hctx_idx, node)) अणु
				tags->अटल_rqs[i] = शून्य;
				जाओ fail;
			पूर्ण

			p += rq_size;
			i++;
		पूर्ण
	पूर्ण
	वापस 0;

fail:
	blk_mq_मुक्त_rqs(set, tags, hctx_idx);
	वापस -ENOMEM;
पूर्ण

काष्ठा rq_iter_data अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	bool has_rq;
पूर्ण;

अटल bool blk_mq_has_request(काष्ठा request *rq, व्योम *data, bool reserved)
अणु
	काष्ठा rq_iter_data *iter_data = data;

	अगर (rq->mq_hctx != iter_data->hctx)
		वापस true;
	iter_data->has_rq = true;
	वापस false;
पूर्ण

अटल bool blk_mq_hctx_has_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा blk_mq_tags *tags = hctx->sched_tags ?
			hctx->sched_tags : hctx->tags;
	काष्ठा rq_iter_data data = अणु
		.hctx	= hctx,
	पूर्ण;

	blk_mq_all_tag_iter(tags, blk_mq_has_request, &data);
	वापस data.has_rq;
पूर्ण

अटल अंतरभूत bool blk_mq_last_cpu_in_hctx(अचिन्हित पूर्णांक cpu,
		काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (cpumask_next_and(-1, hctx->cpumask, cpu_online_mask) != cpu)
		वापस false;
	अगर (cpumask_next_and(cpu, hctx->cpumask, cpu_online_mask) < nr_cpu_ids)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक blk_mq_hctx_notअगरy_offline(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = hlist_entry_safe(node,
			काष्ठा blk_mq_hw_ctx, cpuhp_online);

	अगर (!cpumask_test_cpu(cpu, hctx->cpumask) ||
	    !blk_mq_last_cpu_in_hctx(cpu, hctx))
		वापस 0;

	/*
	 * Prevent new request from being allocated on the current hctx.
	 *
	 * The smp_mb__after_atomic() Pairs with the implied barrier in
	 * test_and_set_bit_lock in sbiपंचांगap_get().  Ensures the inactive flag is
	 * seen once we वापस from the tag allocator.
	 */
	set_bit(BLK_MQ_S_INACTIVE, &hctx->state);
	smp_mb__after_atomic();

	/*
	 * Try to grab a reference to the queue and रुको क्रम any outstanding
	 * requests.  If we could not grab a reference the queue has been
	 * frozen and there are no requests.
	 */
	अगर (percpu_ref_tryget(&hctx->queue->q_usage_counter)) अणु
		जबतक (blk_mq_hctx_has_requests(hctx))
			msleep(5);
		percpu_ref_put(&hctx->queue->q_usage_counter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक blk_mq_hctx_notअगरy_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = hlist_entry_safe(node,
			काष्ठा blk_mq_hw_ctx, cpuhp_online);

	अगर (cpumask_test_cpu(cpu, hctx->cpumask))
		clear_bit(BLK_MQ_S_INACTIVE, &hctx->state);
	वापस 0;
पूर्ण

/*
 * 'cpu' is going away. splice any existing rq_list entries from this
 * software queue to the hw queue dispatch list, and ensure that it
 * माला_लो run.
 */
अटल पूर्णांक blk_mq_hctx_notअगरy_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा blk_mq_ctx *ctx;
	LIST_HEAD(पंचांगp);
	क्रमागत hctx_type type;

	hctx = hlist_entry_safe(node, काष्ठा blk_mq_hw_ctx, cpuhp_dead);
	अगर (!cpumask_test_cpu(cpu, hctx->cpumask))
		वापस 0;

	ctx = __blk_mq_get_ctx(hctx->queue, cpu);
	type = hctx->type;

	spin_lock(&ctx->lock);
	अगर (!list_empty(&ctx->rq_lists[type])) अणु
		list_splice_init(&ctx->rq_lists[type], &पंचांगp);
		blk_mq_hctx_clear_pending(hctx, ctx);
	पूर्ण
	spin_unlock(&ctx->lock);

	अगर (list_empty(&पंचांगp))
		वापस 0;

	spin_lock(&hctx->lock);
	list_splice_tail_init(&पंचांगp, &hctx->dispatch);
	spin_unlock(&hctx->lock);

	blk_mq_run_hw_queue(hctx, true);
	वापस 0;
पूर्ण

अटल व्योम blk_mq_हटाओ_cpuhp(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (!(hctx->flags & BLK_MQ_F_STACKING))
		cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_BLK_MQ_ONLINE,
						    &hctx->cpuhp_online);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_BLK_MQ_DEAD,
					    &hctx->cpuhp_dead);
पूर्ण

/* hctx->ctxs will be मुक्तd in queue's release handler */
अटल व्योम blk_mq_निकास_hctx(काष्ठा request_queue *q,
		काष्ठा blk_mq_tag_set *set,
		काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक hctx_idx)
अणु
	अगर (blk_mq_hw_queue_mapped(hctx))
		blk_mq_tag_idle(hctx);

	अगर (set->ops->निकास_request)
		set->ops->निकास_request(set, hctx->fq->flush_rq, hctx_idx);

	अगर (set->ops->निकास_hctx)
		set->ops->निकास_hctx(hctx, hctx_idx);

	blk_mq_हटाओ_cpuhp(hctx);

	spin_lock(&q->unused_hctx_lock);
	list_add(&hctx->hctx_list, &q->unused_hctx_list);
	spin_unlock(&q->unused_hctx_lock);
पूर्ण

अटल व्योम blk_mq_निकास_hw_queues(काष्ठा request_queue *q,
		काष्ठा blk_mq_tag_set *set, पूर्णांक nr_queue)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	अचिन्हित पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (i == nr_queue)
			अवरोध;
		blk_mq_debugfs_unरेजिस्टर_hctx(hctx);
		blk_mq_निकास_hctx(q, set, hctx, i);
	पूर्ण
पूर्ण

अटल पूर्णांक blk_mq_hw_ctx_size(काष्ठा blk_mq_tag_set *tag_set)
अणु
	पूर्णांक hw_ctx_size = माप(काष्ठा blk_mq_hw_ctx);

	BUILD_BUG_ON(ALIGN(दुरत्व(काष्ठा blk_mq_hw_ctx, srcu),
			   __alignof__(काष्ठा blk_mq_hw_ctx)) !=
		     माप(काष्ठा blk_mq_hw_ctx));

	अगर (tag_set->flags & BLK_MQ_F_BLOCKING)
		hw_ctx_size += माप(काष्ठा srcu_काष्ठा);

	वापस hw_ctx_size;
पूर्ण

अटल पूर्णांक blk_mq_init_hctx(काष्ठा request_queue *q,
		काष्ठा blk_mq_tag_set *set,
		काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित hctx_idx)
अणु
	hctx->queue_num = hctx_idx;

	अगर (!(hctx->flags & BLK_MQ_F_STACKING))
		cpuhp_state_add_instance_nocalls(CPUHP_AP_BLK_MQ_ONLINE,
				&hctx->cpuhp_online);
	cpuhp_state_add_instance_nocalls(CPUHP_BLK_MQ_DEAD, &hctx->cpuhp_dead);

	hctx->tags = set->tags[hctx_idx];

	अगर (set->ops->init_hctx &&
	    set->ops->init_hctx(hctx, set->driver_data, hctx_idx))
		जाओ unरेजिस्टर_cpu_notअगरier;

	अगर (blk_mq_init_request(set, hctx->fq->flush_rq, hctx_idx,
				hctx->numa_node))
		जाओ निकास_hctx;
	वापस 0;

 निकास_hctx:
	अगर (set->ops->निकास_hctx)
		set->ops->निकास_hctx(hctx, hctx_idx);
 unरेजिस्टर_cpu_notअगरier:
	blk_mq_हटाओ_cpuhp(hctx);
	वापस -1;
पूर्ण

अटल काष्ठा blk_mq_hw_ctx *
blk_mq_alloc_hctx(काष्ठा request_queue *q, काष्ठा blk_mq_tag_set *set,
		पूर्णांक node)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	gfp_t gfp = GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY;

	hctx = kzalloc_node(blk_mq_hw_ctx_size(set), gfp, node);
	अगर (!hctx)
		जाओ fail_alloc_hctx;

	अगर (!zalloc_cpumask_var_node(&hctx->cpumask, gfp, node))
		जाओ मुक्त_hctx;

	atomic_set(&hctx->nr_active, 0);
	अगर (node == NUMA_NO_NODE)
		node = set->numa_node;
	hctx->numa_node = node;

	INIT_DELAYED_WORK(&hctx->run_work, blk_mq_run_work_fn);
	spin_lock_init(&hctx->lock);
	INIT_LIST_HEAD(&hctx->dispatch);
	hctx->queue = q;
	hctx->flags = set->flags & ~BLK_MQ_F_TAG_QUEUE_SHARED;

	INIT_LIST_HEAD(&hctx->hctx_list);

	/*
	 * Allocate space क्रम all possible cpus to aव्योम allocation at
	 * runसमय
	 */
	hctx->ctxs = kदो_स्मृति_array_node(nr_cpu_ids, माप(व्योम *),
			gfp, node);
	अगर (!hctx->ctxs)
		जाओ मुक्त_cpumask;

	अगर (sbiपंचांगap_init_node(&hctx->ctx_map, nr_cpu_ids, ilog2(8),
				gfp, node, false, false))
		जाओ मुक्त_ctxs;
	hctx->nr_ctx = 0;

	spin_lock_init(&hctx->dispatch_रुको_lock);
	init_रुकोqueue_func_entry(&hctx->dispatch_रुको, blk_mq_dispatch_wake);
	INIT_LIST_HEAD(&hctx->dispatch_रुको.entry);

	hctx->fq = blk_alloc_flush_queue(hctx->numa_node, set->cmd_size, gfp);
	अगर (!hctx->fq)
		जाओ मुक्त_biपंचांगap;

	अगर (hctx->flags & BLK_MQ_F_BLOCKING)
		init_srcu_काष्ठा(hctx->srcu);
	blk_mq_hctx_kobj_init(hctx);

	वापस hctx;

 मुक्त_biपंचांगap:
	sbiपंचांगap_मुक्त(&hctx->ctx_map);
 मुक्त_ctxs:
	kमुक्त(hctx->ctxs);
 मुक्त_cpumask:
	मुक्त_cpumask_var(hctx->cpumask);
 मुक्त_hctx:
	kमुक्त(hctx);
 fail_alloc_hctx:
	वापस शून्य;
पूर्ण

अटल व्योम blk_mq_init_cpu_queues(काष्ठा request_queue *q,
				   अचिन्हित पूर्णांक nr_hw_queues)
अणु
	काष्ठा blk_mq_tag_set *set = q->tag_set;
	अचिन्हित पूर्णांक i, j;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा blk_mq_ctx *__ctx = per_cpu_ptr(q->queue_ctx, i);
		काष्ठा blk_mq_hw_ctx *hctx;
		पूर्णांक k;

		__ctx->cpu = i;
		spin_lock_init(&__ctx->lock);
		क्रम (k = HCTX_TYPE_DEFAULT; k < HCTX_MAX_TYPES; k++)
			INIT_LIST_HEAD(&__ctx->rq_lists[k]);

		__ctx->queue = q;

		/*
		 * Set local node, IFF we have more than one hw queue. If
		 * not, we reमुख्य on the home node of the device
		 */
		क्रम (j = 0; j < set->nr_maps; j++) अणु
			hctx = blk_mq_map_queue_type(q, j, i);
			अगर (nr_hw_queues > 1 && hctx->numa_node == NUMA_NO_NODE)
				hctx->numa_node = cpu_to_node(i);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool __blk_mq_alloc_map_and_request(काष्ठा blk_mq_tag_set *set,
					पूर्णांक hctx_idx)
अणु
	अचिन्हित पूर्णांक flags = set->flags;
	पूर्णांक ret = 0;

	set->tags[hctx_idx] = blk_mq_alloc_rq_map(set, hctx_idx,
					set->queue_depth, set->reserved_tags, flags);
	अगर (!set->tags[hctx_idx])
		वापस false;

	ret = blk_mq_alloc_rqs(set, set->tags[hctx_idx], hctx_idx,
				set->queue_depth);
	अगर (!ret)
		वापस true;

	blk_mq_मुक्त_rq_map(set->tags[hctx_idx], flags);
	set->tags[hctx_idx] = शून्य;
	वापस false;
पूर्ण

अटल व्योम blk_mq_मुक्त_map_and_requests(काष्ठा blk_mq_tag_set *set,
					 अचिन्हित पूर्णांक hctx_idx)
अणु
	अचिन्हित पूर्णांक flags = set->flags;

	अगर (set->tags && set->tags[hctx_idx]) अणु
		blk_mq_मुक्त_rqs(set, set->tags[hctx_idx], hctx_idx);
		blk_mq_मुक्त_rq_map(set->tags[hctx_idx], flags);
		set->tags[hctx_idx] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम blk_mq_map_swqueue(काष्ठा request_queue *q)
अणु
	अचिन्हित पूर्णांक i, j, hctx_idx;
	काष्ठा blk_mq_hw_ctx *hctx;
	काष्ठा blk_mq_ctx *ctx;
	काष्ठा blk_mq_tag_set *set = q->tag_set;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		cpumask_clear(hctx->cpumask);
		hctx->nr_ctx = 0;
		hctx->dispatch_from = शून्य;
	पूर्ण

	/*
	 * Map software to hardware queues.
	 *
	 * If the cpu isn't present, the cpu is mapped to first hctx.
	 */
	क्रम_each_possible_cpu(i) अणु

		ctx = per_cpu_ptr(q->queue_ctx, i);
		क्रम (j = 0; j < set->nr_maps; j++) अणु
			अगर (!set->map[j].nr_queues) अणु
				ctx->hctxs[j] = blk_mq_map_queue_type(q,
						HCTX_TYPE_DEFAULT, i);
				जारी;
			पूर्ण
			hctx_idx = set->map[j].mq_map[i];
			/* unmapped hw queue can be remapped after CPU topo changed */
			अगर (!set->tags[hctx_idx] &&
			    !__blk_mq_alloc_map_and_request(set, hctx_idx)) अणु
				/*
				 * If tags initialization fail क्रम some hctx,
				 * that hctx won't be brought online.  In this
				 * हाल, remap the current ctx to hctx[0] which
				 * is guaranteed to always have tags allocated
				 */
				set->map[j].mq_map[i] = 0;
			पूर्ण

			hctx = blk_mq_map_queue_type(q, j, i);
			ctx->hctxs[j] = hctx;
			/*
			 * If the CPU is alपढ़ोy set in the mask, then we've
			 * mapped this one alपढ़ोy. This can happen अगर
			 * devices share queues across queue maps.
			 */
			अगर (cpumask_test_cpu(i, hctx->cpumask))
				जारी;

			cpumask_set_cpu(i, hctx->cpumask);
			hctx->type = j;
			ctx->index_hw[hctx->type] = hctx->nr_ctx;
			hctx->ctxs[hctx->nr_ctx++] = ctx;

			/*
			 * If the nr_ctx type overflows, we have exceeded the
			 * amount of sw queues we can support.
			 */
			BUG_ON(!hctx->nr_ctx);
		पूर्ण

		क्रम (; j < HCTX_MAX_TYPES; j++)
			ctx->hctxs[j] = blk_mq_map_queue_type(q,
					HCTX_TYPE_DEFAULT, i);
	पूर्ण

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		/*
		 * If no software queues are mapped to this hardware queue,
		 * disable it and मुक्त the request entries.
		 */
		अगर (!hctx->nr_ctx) अणु
			/* Never unmap queue 0.  We need it as a
			 * fallback in हाल of a new remap fails
			 * allocation
			 */
			अगर (i && set->tags[i])
				blk_mq_मुक्त_map_and_requests(set, i);

			hctx->tags = शून्य;
			जारी;
		पूर्ण

		hctx->tags = set->tags[i];
		WARN_ON(!hctx->tags);

		/*
		 * Set the map size to the number of mapped software queues.
		 * This is more accurate and more efficient than looping
		 * over all possibly mapped software queues.
		 */
		sbiपंचांगap_resize(&hctx->ctx_map, hctx->nr_ctx);

		/*
		 * Initialize batch roundrobin counts
		 */
		hctx->next_cpu = blk_mq_first_mapped_cpu(hctx);
		hctx->next_cpu_batch = BLK_MQ_CPU_WORK_BATCH;
	पूर्ण
पूर्ण

/*
 * Caller needs to ensure that we're either frozen/quiesced, or that
 * the queue isn't live yet.
 */
अटल व्योम queue_set_hctx_shared(काष्ठा request_queue *q, bool shared)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (shared)
			hctx->flags |= BLK_MQ_F_TAG_QUEUE_SHARED;
		अन्यथा
			hctx->flags &= ~BLK_MQ_F_TAG_QUEUE_SHARED;
	पूर्ण
पूर्ण

अटल व्योम blk_mq_update_tag_set_shared(काष्ठा blk_mq_tag_set *set,
					 bool shared)
अणु
	काष्ठा request_queue *q;

	lockdep_निश्चित_held(&set->tag_list_lock);

	list_क्रम_each_entry(q, &set->tag_list, tag_set_list) अणु
		blk_mq_मुक्तze_queue(q);
		queue_set_hctx_shared(q, shared);
		blk_mq_unमुक्तze_queue(q);
	पूर्ण
पूर्ण

अटल व्योम blk_mq_del_queue_tag_set(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_tag_set *set = q->tag_set;

	mutex_lock(&set->tag_list_lock);
	list_del(&q->tag_set_list);
	अगर (list_is_singular(&set->tag_list)) अणु
		/* just transitioned to unshared */
		set->flags &= ~BLK_MQ_F_TAG_QUEUE_SHARED;
		/* update existing queue */
		blk_mq_update_tag_set_shared(set, false);
	पूर्ण
	mutex_unlock(&set->tag_list_lock);
	INIT_LIST_HEAD(&q->tag_set_list);
पूर्ण

अटल व्योम blk_mq_add_queue_tag_set(काष्ठा blk_mq_tag_set *set,
				     काष्ठा request_queue *q)
अणु
	mutex_lock(&set->tag_list_lock);

	/*
	 * Check to see अगर we're transitioning to shared (from 1 to 2 queues).
	 */
	अगर (!list_empty(&set->tag_list) &&
	    !(set->flags & BLK_MQ_F_TAG_QUEUE_SHARED)) अणु
		set->flags |= BLK_MQ_F_TAG_QUEUE_SHARED;
		/* update existing queue */
		blk_mq_update_tag_set_shared(set, true);
	पूर्ण
	अगर (set->flags & BLK_MQ_F_TAG_QUEUE_SHARED)
		queue_set_hctx_shared(q, true);
	list_add_tail(&q->tag_set_list, &set->tag_list);

	mutex_unlock(&set->tag_list_lock);
पूर्ण

/* All allocations will be मुक्तd in release handler of q->mq_kobj */
अटल पूर्णांक blk_mq_alloc_ctxs(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_ctxs *ctxs;
	पूर्णांक cpu;

	ctxs = kzalloc(माप(*ctxs), GFP_KERNEL);
	अगर (!ctxs)
		वापस -ENOMEM;

	ctxs->queue_ctx = alloc_percpu(काष्ठा blk_mq_ctx);
	अगर (!ctxs->queue_ctx)
		जाओ fail;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा blk_mq_ctx *ctx = per_cpu_ptr(ctxs->queue_ctx, cpu);
		ctx->ctxs = ctxs;
	पूर्ण

	q->mq_kobj = &ctxs->kobj;
	q->queue_ctx = ctxs->queue_ctx;

	वापस 0;
 fail:
	kमुक्त(ctxs);
	वापस -ENOMEM;
पूर्ण

/*
 * It is the actual release handler क्रम mq, but we करो it from
 * request queue's release handler क्रम aव्योमing use-after-मुक्त
 * and headache because q->mq_kobj shouldn't have been पूर्णांकroduced,
 * but we can't group ctx/kctx kobj without it.
 */
व्योम blk_mq_release(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx, *next;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		WARN_ON_ONCE(hctx && list_empty(&hctx->hctx_list));

	/* all hctx are in .unused_hctx_list now */
	list_क्रम_each_entry_safe(hctx, next, &q->unused_hctx_list, hctx_list) अणु
		list_del_init(&hctx->hctx_list);
		kobject_put(&hctx->kobj);
	पूर्ण

	kमुक्त(q->queue_hw_ctx);

	/*
	 * release .mq_kobj and sw queue's kobject now because
	 * both share lअगरeसमय with request queue.
	 */
	blk_mq_sysfs_deinit(q);
पूर्ण

काष्ठा request_queue *blk_mq_init_queue_data(काष्ठा blk_mq_tag_set *set,
		व्योम *queuedata)
अणु
	काष्ठा request_queue *uninit_q, *q;

	uninit_q = blk_alloc_queue(set->numa_node);
	अगर (!uninit_q)
		वापस ERR_PTR(-ENOMEM);
	uninit_q->queuedata = queuedata;

	/*
	 * Initialize the queue without an elevator. device_add_disk() will करो
	 * the initialization.
	 */
	q = blk_mq_init_allocated_queue(set, uninit_q, false);
	अगर (IS_ERR(q))
		blk_cleanup_queue(uninit_q);

	वापस q;
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_init_queue_data);

काष्ठा request_queue *blk_mq_init_queue(काष्ठा blk_mq_tag_set *set)
अणु
	वापस blk_mq_init_queue_data(set, शून्य);
पूर्ण
EXPORT_SYMBOL(blk_mq_init_queue);

/*
 * Helper क्रम setting up a queue with mq ops, given queue depth, and
 * the passed in mq ops flags.
 */
काष्ठा request_queue *blk_mq_init_sq_queue(काष्ठा blk_mq_tag_set *set,
					   स्थिर काष्ठा blk_mq_ops *ops,
					   अचिन्हित पूर्णांक queue_depth,
					   अचिन्हित पूर्णांक set_flags)
अणु
	काष्ठा request_queue *q;
	पूर्णांक ret;

	स_रखो(set, 0, माप(*set));
	set->ops = ops;
	set->nr_hw_queues = 1;
	set->nr_maps = 1;
	set->queue_depth = queue_depth;
	set->numa_node = NUMA_NO_NODE;
	set->flags = set_flags;

	ret = blk_mq_alloc_tag_set(set);
	अगर (ret)
		वापस ERR_PTR(ret);

	q = blk_mq_init_queue(set);
	अगर (IS_ERR(q)) अणु
		blk_mq_मुक्त_tag_set(set);
		वापस q;
	पूर्ण

	वापस q;
पूर्ण
EXPORT_SYMBOL(blk_mq_init_sq_queue);

अटल काष्ठा blk_mq_hw_ctx *blk_mq_alloc_and_init_hctx(
		काष्ठा blk_mq_tag_set *set, काष्ठा request_queue *q,
		पूर्णांक hctx_idx, पूर्णांक node)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = शून्य, *पंचांगp;

	/* reuse dead hctx first */
	spin_lock(&q->unused_hctx_lock);
	list_क्रम_each_entry(पंचांगp, &q->unused_hctx_list, hctx_list) अणु
		अगर (पंचांगp->numa_node == node) अणु
			hctx = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (hctx)
		list_del_init(&hctx->hctx_list);
	spin_unlock(&q->unused_hctx_lock);

	अगर (!hctx)
		hctx = blk_mq_alloc_hctx(q, set, node);
	अगर (!hctx)
		जाओ fail;

	अगर (blk_mq_init_hctx(q, set, hctx, hctx_idx))
		जाओ मुक्त_hctx;

	वापस hctx;

 मुक्त_hctx:
	kobject_put(&hctx->kobj);
 fail:
	वापस शून्य;
पूर्ण

अटल व्योम blk_mq_पुनः_स्मृति_hw_ctxs(काष्ठा blk_mq_tag_set *set,
						काष्ठा request_queue *q)
अणु
	पूर्णांक i, j, end;
	काष्ठा blk_mq_hw_ctx **hctxs = q->queue_hw_ctx;

	अगर (q->nr_hw_queues < set->nr_hw_queues) अणु
		काष्ठा blk_mq_hw_ctx **new_hctxs;

		new_hctxs = kसुस्मृति_node(set->nr_hw_queues,
				       माप(*new_hctxs), GFP_KERNEL,
				       set->numa_node);
		अगर (!new_hctxs)
			वापस;
		अगर (hctxs)
			स_नकल(new_hctxs, hctxs, q->nr_hw_queues *
			       माप(*hctxs));
		q->queue_hw_ctx = new_hctxs;
		kमुक्त(hctxs);
		hctxs = new_hctxs;
	पूर्ण

	/* protect against चयनing io scheduler  */
	mutex_lock(&q->sysfs_lock);
	क्रम (i = 0; i < set->nr_hw_queues; i++) अणु
		पूर्णांक node;
		काष्ठा blk_mq_hw_ctx *hctx;

		node = blk_mq_hw_queue_to_node(&set->map[HCTX_TYPE_DEFAULT], i);
		/*
		 * If the hw queue has been mapped to another numa node,
		 * we need to पुनः_स्मृति the hctx. If allocation fails, fallback
		 * to use the previous one.
		 */
		अगर (hctxs[i] && (hctxs[i]->numa_node == node))
			जारी;

		hctx = blk_mq_alloc_and_init_hctx(set, q, i, node);
		अगर (hctx) अणु
			अगर (hctxs[i])
				blk_mq_निकास_hctx(q, set, hctxs[i], i);
			hctxs[i] = hctx;
		पूर्ण अन्यथा अणु
			अगर (hctxs[i])
				pr_warn("Allocate new hctx on node %d fails,\
						fallback to previous one on node %d\न",
						node, hctxs[i]->numa_node);
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * Increasing nr_hw_queues fails. Free the newly allocated
	 * hctxs and keep the previous q->nr_hw_queues.
	 */
	अगर (i != set->nr_hw_queues) अणु
		j = q->nr_hw_queues;
		end = i;
	पूर्ण अन्यथा अणु
		j = i;
		end = q->nr_hw_queues;
		q->nr_hw_queues = set->nr_hw_queues;
	पूर्ण

	क्रम (; j < end; j++) अणु
		काष्ठा blk_mq_hw_ctx *hctx = hctxs[j];

		अगर (hctx) अणु
			अगर (hctx->tags)
				blk_mq_मुक्त_map_and_requests(set, j);
			blk_mq_निकास_hctx(q, set, hctx, j);
			hctxs[j] = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&q->sysfs_lock);
पूर्ण

काष्ठा request_queue *blk_mq_init_allocated_queue(काष्ठा blk_mq_tag_set *set,
						  काष्ठा request_queue *q,
						  bool elevator_init)
अणु
	/* mark the queue as mq asap */
	q->mq_ops = set->ops;

	q->poll_cb = blk_stat_alloc_callback(blk_mq_poll_stats_fn,
					     blk_mq_poll_stats_bkt,
					     BLK_MQ_POLL_STATS_BKTS, q);
	अगर (!q->poll_cb)
		जाओ err_निकास;

	अगर (blk_mq_alloc_ctxs(q))
		जाओ err_poll;

	/* init q->mq_kobj and sw queues' kobjects */
	blk_mq_sysfs_init(q);

	INIT_LIST_HEAD(&q->unused_hctx_list);
	spin_lock_init(&q->unused_hctx_lock);

	blk_mq_पुनः_स्मृति_hw_ctxs(set, q);
	अगर (!q->nr_hw_queues)
		जाओ err_hctxs;

	INIT_WORK(&q->समयout_work, blk_mq_समयout_work);
	blk_queue_rq_समयout(q, set->समयout ? set->समयout : 30 * HZ);

	q->tag_set = set;

	q->queue_flags |= QUEUE_FLAG_MQ_DEFAULT;
	अगर (set->nr_maps > HCTX_TYPE_POLL &&
	    set->map[HCTX_TYPE_POLL].nr_queues)
		blk_queue_flag_set(QUEUE_FLAG_POLL, q);

	q->sg_reserved_size = पूर्णांक_उच्च;

	INIT_DELAYED_WORK(&q->requeue_work, blk_mq_requeue_work);
	INIT_LIST_HEAD(&q->requeue_list);
	spin_lock_init(&q->requeue_lock);

	q->nr_requests = set->queue_depth;

	/*
	 * Default to classic polling
	 */
	q->poll_nsec = BLK_MQ_POLL_CLASSIC;

	blk_mq_init_cpu_queues(q, set->nr_hw_queues);
	blk_mq_add_queue_tag_set(set, q);
	blk_mq_map_swqueue(q);

	अगर (elevator_init)
		elevator_init_mq(q);

	वापस q;

err_hctxs:
	kमुक्त(q->queue_hw_ctx);
	q->nr_hw_queues = 0;
	blk_mq_sysfs_deinit(q);
err_poll:
	blk_stat_मुक्त_callback(q->poll_cb);
	q->poll_cb = शून्य;
err_निकास:
	q->mq_ops = शून्य;
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL(blk_mq_init_allocated_queue);

/* tags can _not_ be used after वापसing from blk_mq_निकास_queue */
व्योम blk_mq_निकास_queue(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_tag_set *set = q->tag_set;

	/* Checks hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED. */
	blk_mq_निकास_hw_queues(q, set, set->nr_hw_queues);
	/* May clear BLK_MQ_F_TAG_QUEUE_SHARED in hctx->flags. */
	blk_mq_del_queue_tag_set(q);
पूर्ण

अटल पूर्णांक __blk_mq_alloc_rq_maps(काष्ठा blk_mq_tag_set *set)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < set->nr_hw_queues; i++) अणु
		अगर (!__blk_mq_alloc_map_and_request(set, i))
			जाओ out_unwind;
		cond_resched();
	पूर्ण

	वापस 0;

out_unwind:
	जबतक (--i >= 0)
		blk_mq_मुक्त_map_and_requests(set, i);

	वापस -ENOMEM;
पूर्ण

/*
 * Allocate the request maps associated with this tag_set. Note that this
 * may reduce the depth asked क्रम, अगर memory is tight. set->queue_depth
 * will be updated to reflect the allocated depth.
 */
अटल पूर्णांक blk_mq_alloc_map_and_requests(काष्ठा blk_mq_tag_set *set)
अणु
	अचिन्हित पूर्णांक depth;
	पूर्णांक err;

	depth = set->queue_depth;
	करो अणु
		err = __blk_mq_alloc_rq_maps(set);
		अगर (!err)
			अवरोध;

		set->queue_depth >>= 1;
		अगर (set->queue_depth < set->reserved_tags + BLK_MQ_TAG_MIN) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (set->queue_depth);

	अगर (!set->queue_depth || err) अणु
		pr_err("blk-mq: failed to allocate request map\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (depth != set->queue_depth)
		pr_info("blk-mq: reduced tag depth (%u -> %u)\n",
						depth, set->queue_depth);

	वापस 0;
पूर्ण

अटल पूर्णांक blk_mq_update_queue_map(काष्ठा blk_mq_tag_set *set)
अणु
	/*
	 * blk_mq_map_queues() and multiple .map_queues() implementations
	 * expect that set->map[HCTX_TYPE_DEFAULT].nr_queues is set to the
	 * number of hardware queues.
	 */
	अगर (set->nr_maps == 1)
		set->map[HCTX_TYPE_DEFAULT].nr_queues = set->nr_hw_queues;

	अगर (set->ops->map_queues && !is_kdump_kernel()) अणु
		पूर्णांक i;

		/*
		 * transport .map_queues is usually करोne in the following
		 * way:
		 *
		 * क्रम (queue = 0; queue < set->nr_hw_queues; queue++) अणु
		 * 	mask = get_cpu_mask(queue)
		 * 	क्रम_each_cpu(cpu, mask)
		 * 		set->map[x].mq_map[cpu] = queue;
		 * पूर्ण
		 *
		 * When we need to remap, the table has to be cleared क्रम
		 * समाप्तing stale mapping since one CPU may not be mapped
		 * to any hw queue.
		 */
		क्रम (i = 0; i < set->nr_maps; i++)
			blk_mq_clear_mq_map(&set->map[i]);

		वापस set->ops->map_queues(set);
	पूर्ण अन्यथा अणु
		BUG_ON(set->nr_maps > 1);
		वापस blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
	पूर्ण
पूर्ण

अटल पूर्णांक blk_mq_पुनः_स्मृति_tag_set_tags(काष्ठा blk_mq_tag_set *set,
				  पूर्णांक cur_nr_hw_queues, पूर्णांक new_nr_hw_queues)
अणु
	काष्ठा blk_mq_tags **new_tags;

	अगर (cur_nr_hw_queues >= new_nr_hw_queues)
		वापस 0;

	new_tags = kसुस्मृति_node(new_nr_hw_queues, माप(काष्ठा blk_mq_tags *),
				GFP_KERNEL, set->numa_node);
	अगर (!new_tags)
		वापस -ENOMEM;

	अगर (set->tags)
		स_नकल(new_tags, set->tags, cur_nr_hw_queues *
		       माप(*set->tags));
	kमुक्त(set->tags);
	set->tags = new_tags;
	set->nr_hw_queues = new_nr_hw_queues;

	वापस 0;
पूर्ण

अटल पूर्णांक blk_mq_alloc_tag_set_tags(काष्ठा blk_mq_tag_set *set,
				पूर्णांक new_nr_hw_queues)
अणु
	वापस blk_mq_पुनः_स्मृति_tag_set_tags(set, 0, new_nr_hw_queues);
पूर्ण

/*
 * Alloc a tag set to be associated with one or more request queues.
 * May fail with EINVAL क्रम various error conditions. May adjust the
 * requested depth करोwn, अगर it's too large. In that हाल, the set
 * value will be stored in set->queue_depth.
 */
पूर्णांक blk_mq_alloc_tag_set(काष्ठा blk_mq_tag_set *set)
अणु
	पूर्णांक i, ret;

	BUILD_BUG_ON(BLK_MQ_MAX_DEPTH > 1 << BLK_MQ_UNIQUE_TAG_BITS);

	अगर (!set->nr_hw_queues)
		वापस -EINVAL;
	अगर (!set->queue_depth)
		वापस -EINVAL;
	अगर (set->queue_depth < set->reserved_tags + BLK_MQ_TAG_MIN)
		वापस -EINVAL;

	अगर (!set->ops->queue_rq)
		वापस -EINVAL;

	अगर (!set->ops->get_budget ^ !set->ops->put_budget)
		वापस -EINVAL;

	अगर (set->queue_depth > BLK_MQ_MAX_DEPTH) अणु
		pr_info("blk-mq: reduced tag depth to %u\n",
			BLK_MQ_MAX_DEPTH);
		set->queue_depth = BLK_MQ_MAX_DEPTH;
	पूर्ण

	अगर (!set->nr_maps)
		set->nr_maps = 1;
	अन्यथा अगर (set->nr_maps > HCTX_MAX_TYPES)
		वापस -EINVAL;

	/*
	 * If a crashdump is active, then we are potentially in a very
	 * memory स्थिरrained environment. Limit us to 1 queue and
	 * 64 tags to prevent using too much memory.
	 */
	अगर (is_kdump_kernel()) अणु
		set->nr_hw_queues = 1;
		set->nr_maps = 1;
		set->queue_depth = min(64U, set->queue_depth);
	पूर्ण
	/*
	 * There is no use क्रम more h/w queues than cpus अगर we just have
	 * a single map
	 */
	अगर (set->nr_maps == 1 && set->nr_hw_queues > nr_cpu_ids)
		set->nr_hw_queues = nr_cpu_ids;

	अगर (blk_mq_alloc_tag_set_tags(set, set->nr_hw_queues) < 0)
		वापस -ENOMEM;

	ret = -ENOMEM;
	क्रम (i = 0; i < set->nr_maps; i++) अणु
		set->map[i].mq_map = kसुस्मृति_node(nr_cpu_ids,
						  माप(set->map[i].mq_map[0]),
						  GFP_KERNEL, set->numa_node);
		अगर (!set->map[i].mq_map)
			जाओ out_मुक्त_mq_map;
		set->map[i].nr_queues = is_kdump_kernel() ? 1 : set->nr_hw_queues;
	पूर्ण

	ret = blk_mq_update_queue_map(set);
	अगर (ret)
		जाओ out_मुक्त_mq_map;

	ret = blk_mq_alloc_map_and_requests(set);
	अगर (ret)
		जाओ out_मुक्त_mq_map;

	अगर (blk_mq_is_sbiपंचांगap_shared(set->flags)) अणु
		atomic_set(&set->active_queues_shared_sbiपंचांगap, 0);

		अगर (blk_mq_init_shared_sbiपंचांगap(set, set->flags)) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_mq_rq_maps;
		पूर्ण
	पूर्ण

	mutex_init(&set->tag_list_lock);
	INIT_LIST_HEAD(&set->tag_list);

	वापस 0;

out_मुक्त_mq_rq_maps:
	क्रम (i = 0; i < set->nr_hw_queues; i++)
		blk_mq_मुक्त_map_and_requests(set, i);
out_मुक्त_mq_map:
	क्रम (i = 0; i < set->nr_maps; i++) अणु
		kमुक्त(set->map[i].mq_map);
		set->map[i].mq_map = शून्य;
	पूर्ण
	kमुक्त(set->tags);
	set->tags = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_mq_alloc_tag_set);

व्योम blk_mq_मुक्त_tag_set(काष्ठा blk_mq_tag_set *set)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < set->nr_hw_queues; i++)
		blk_mq_मुक्त_map_and_requests(set, i);

	अगर (blk_mq_is_sbiपंचांगap_shared(set->flags))
		blk_mq_निकास_shared_sbiपंचांगap(set);

	क्रम (j = 0; j < set->nr_maps; j++) अणु
		kमुक्त(set->map[j].mq_map);
		set->map[j].mq_map = शून्य;
	पूर्ण

	kमुक्त(set->tags);
	set->tags = शून्य;
पूर्ण
EXPORT_SYMBOL(blk_mq_मुक्त_tag_set);

पूर्णांक blk_mq_update_nr_requests(काष्ठा request_queue *q, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा blk_mq_tag_set *set = q->tag_set;
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i, ret;

	अगर (!set)
		वापस -EINVAL;

	अगर (q->nr_requests == nr)
		वापस 0;

	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	ret = 0;
	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (!hctx->tags)
			जारी;
		/*
		 * If we're using an MQ scheduler, just update the scheduler
		 * queue depth. This is similar to what the old code would करो.
		 */
		अगर (!hctx->sched_tags) अणु
			ret = blk_mq_tag_update_depth(hctx, &hctx->tags, nr,
							false);
			अगर (!ret && blk_mq_is_sbiपंचांगap_shared(set->flags))
				blk_mq_tag_resize_shared_sbiपंचांगap(set, nr);
		पूर्ण अन्यथा अणु
			ret = blk_mq_tag_update_depth(hctx, &hctx->sched_tags,
							nr, true);
		पूर्ण
		अगर (ret)
			अवरोध;
		अगर (q->elevator && q->elevator->type->ops.depth_updated)
			q->elevator->type->ops.depth_updated(hctx);
	पूर्ण

	अगर (!ret)
		q->nr_requests = nr;

	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);

	वापस ret;
पूर्ण

/*
 * request_queue and elevator_type pair.
 * It is just used by __blk_mq_update_nr_hw_queues to cache
 * the elevator_type associated with a request_queue.
 */
काष्ठा blk_mq_qe_pair अणु
	काष्ठा list_head node;
	काष्ठा request_queue *q;
	काष्ठा elevator_type *type;
पूर्ण;

/*
 * Cache the elevator_type in qe pair list and चयन the
 * io scheduler to 'none'
 */
अटल bool blk_mq_elv_चयन_none(काष्ठा list_head *head,
		काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_qe_pair *qe;

	अगर (!q->elevator)
		वापस true;

	qe = kदो_स्मृति(माप(*qe), GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY);
	अगर (!qe)
		वापस false;

	INIT_LIST_HEAD(&qe->node);
	qe->q = q;
	qe->type = q->elevator->type;
	list_add(&qe->node, head);

	mutex_lock(&q->sysfs_lock);
	/*
	 * After elevator_चयन_mq, the previous elevator_queue will be
	 * released by elevator_release. The reference of the io scheduler
	 * module get by elevator_get will also be put. So we need to get
	 * a reference of the io scheduler module here to prevent it to be
	 * हटाओd.
	 */
	__module_get(qe->type->elevator_owner);
	elevator_चयन_mq(q, शून्य);
	mutex_unlock(&q->sysfs_lock);

	वापस true;
पूर्ण

अटल व्योम blk_mq_elv_चयन_back(काष्ठा list_head *head,
		काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_qe_pair *qe;
	काष्ठा elevator_type *t = शून्य;

	list_क्रम_each_entry(qe, head, node)
		अगर (qe->q == q) अणु
			t = qe->type;
			अवरोध;
		पूर्ण

	अगर (!t)
		वापस;

	list_del(&qe->node);
	kमुक्त(qe);

	mutex_lock(&q->sysfs_lock);
	elevator_चयन_mq(q, t);
	mutex_unlock(&q->sysfs_lock);
पूर्ण

अटल व्योम __blk_mq_update_nr_hw_queues(काष्ठा blk_mq_tag_set *set,
							पूर्णांक nr_hw_queues)
अणु
	काष्ठा request_queue *q;
	LIST_HEAD(head);
	पूर्णांक prev_nr_hw_queues;

	lockdep_निश्चित_held(&set->tag_list_lock);

	अगर (set->nr_maps == 1 && nr_hw_queues > nr_cpu_ids)
		nr_hw_queues = nr_cpu_ids;
	अगर (nr_hw_queues < 1)
		वापस;
	अगर (set->nr_maps == 1 && nr_hw_queues == set->nr_hw_queues)
		वापस;

	list_क्रम_each_entry(q, &set->tag_list, tag_set_list)
		blk_mq_मुक्तze_queue(q);
	/*
	 * Switch IO scheduler to 'none', cleaning up the data associated
	 * with the previous scheduler. We will चयन back once we are करोne
	 * updating the new sw to hw queue mappings.
	 */
	list_क्रम_each_entry(q, &set->tag_list, tag_set_list)
		अगर (!blk_mq_elv_चयन_none(&head, q))
			जाओ चयन_back;

	list_क्रम_each_entry(q, &set->tag_list, tag_set_list) अणु
		blk_mq_debugfs_unरेजिस्टर_hctxs(q);
		blk_mq_sysfs_unरेजिस्टर(q);
	पूर्ण

	prev_nr_hw_queues = set->nr_hw_queues;
	अगर (blk_mq_पुनः_स्मृति_tag_set_tags(set, set->nr_hw_queues, nr_hw_queues) <
	    0)
		जाओ reरेजिस्टर;

	set->nr_hw_queues = nr_hw_queues;
fallback:
	blk_mq_update_queue_map(set);
	list_क्रम_each_entry(q, &set->tag_list, tag_set_list) अणु
		blk_mq_पुनः_स्मृति_hw_ctxs(set, q);
		अगर (q->nr_hw_queues != set->nr_hw_queues) अणु
			pr_warn("Increasing nr_hw_queues to %d fails, fallback to %d\n",
					nr_hw_queues, prev_nr_hw_queues);
			set->nr_hw_queues = prev_nr_hw_queues;
			blk_mq_map_queues(&set->map[HCTX_TYPE_DEFAULT]);
			जाओ fallback;
		पूर्ण
		blk_mq_map_swqueue(q);
	पूर्ण

reरेजिस्टर:
	list_क्रम_each_entry(q, &set->tag_list, tag_set_list) अणु
		blk_mq_sysfs_रेजिस्टर(q);
		blk_mq_debugfs_रेजिस्टर_hctxs(q);
	पूर्ण

चयन_back:
	list_क्रम_each_entry(q, &set->tag_list, tag_set_list)
		blk_mq_elv_चयन_back(&head, q);

	list_क्रम_each_entry(q, &set->tag_list, tag_set_list)
		blk_mq_unमुक्तze_queue(q);
पूर्ण

व्योम blk_mq_update_nr_hw_queues(काष्ठा blk_mq_tag_set *set, पूर्णांक nr_hw_queues)
अणु
	mutex_lock(&set->tag_list_lock);
	__blk_mq_update_nr_hw_queues(set, nr_hw_queues);
	mutex_unlock(&set->tag_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_update_nr_hw_queues);

/* Enable polling stats and वापस whether they were alपढ़ोy enabled. */
अटल bool blk_poll_stats_enable(काष्ठा request_queue *q)
अणु
	अगर (test_bit(QUEUE_FLAG_POLL_STATS, &q->queue_flags) ||
	    blk_queue_flag_test_and_set(QUEUE_FLAG_POLL_STATS, q))
		वापस true;
	blk_stat_add_callback(q, q->poll_cb);
	वापस false;
पूर्ण

अटल व्योम blk_mq_poll_stats_start(काष्ठा request_queue *q)
अणु
	/*
	 * We करोn't arm the callback अगर polling stats are not enabled or the
	 * callback is alपढ़ोy active.
	 */
	अगर (!test_bit(QUEUE_FLAG_POLL_STATS, &q->queue_flags) ||
	    blk_stat_is_active(q->poll_cb))
		वापस;

	blk_stat_activate_msecs(q->poll_cb, 100);
पूर्ण

अटल व्योम blk_mq_poll_stats_fn(काष्ठा blk_stat_callback *cb)
अणु
	काष्ठा request_queue *q = cb->data;
	पूर्णांक bucket;

	क्रम (bucket = 0; bucket < BLK_MQ_POLL_STATS_BKTS; bucket++) अणु
		अगर (cb->stat[bucket].nr_samples)
			q->poll_stat[bucket] = cb->stat[bucket];
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ blk_mq_poll_nsecs(काष्ठा request_queue *q,
				       काष्ठा request *rq)
अणु
	अचिन्हित दीर्घ ret = 0;
	पूर्णांक bucket;

	/*
	 * If stats collection isn't on, don't sleep but turn it on क्रम
	 * future users
	 */
	अगर (!blk_poll_stats_enable(q))
		वापस 0;

	/*
	 * As an optimistic guess, use half of the mean service समय
	 * क्रम this type of request. We can (and should) make this smarter.
	 * For instance, अगर the completion latencies are tight, we can
	 * get बंदr than just half the mean. This is especially
	 * important on devices where the completion latencies are दीर्घer
	 * than ~10 usec. We करो use the stats क्रम the relevant IO size
	 * अगर available which करोes lead to better estimates.
	 */
	bucket = blk_mq_poll_stats_bkt(rq);
	अगर (bucket < 0)
		वापस ret;

	अगर (q->poll_stat[bucket].nr_samples)
		ret = (q->poll_stat[bucket].mean + 1) / 2;

	वापस ret;
पूर्ण

अटल bool blk_mq_poll_hybrid_sleep(काष्ठा request_queue *q,
				     काष्ठा request *rq)
अणु
	काष्ठा hrसमयr_sleeper hs;
	क्रमागत hrसमयr_mode mode;
	अचिन्हित पूर्णांक nsecs;
	kसमय_प्रकार kt;

	अगर (rq->rq_flags & RQF_MQ_POLL_SLEPT)
		वापस false;

	/*
	 * If we get here, hybrid polling is enabled. Hence poll_nsec can be:
	 *
	 *  0:	use half of prev avg
	 * >0:	use this specअगरic value
	 */
	अगर (q->poll_nsec > 0)
		nsecs = q->poll_nsec;
	अन्यथा
		nsecs = blk_mq_poll_nsecs(q, rq);

	अगर (!nsecs)
		वापस false;

	rq->rq_flags |= RQF_MQ_POLL_SLEPT;

	/*
	 * This will be replaced with the stats tracking code, using
	 * 'avg_completion_time / 2' as the pre-sleep target.
	 */
	kt = nsecs;

	mode = HRTIMER_MODE_REL;
	hrसमयr_init_sleeper_on_stack(&hs, CLOCK_MONOTONIC, mode);
	hrसमयr_set_expires(&hs.समयr, kt);

	करो अणु
		अगर (blk_mq_rq_state(rq) == MQ_RQ_COMPLETE)
			अवरोध;
		set_current_state(TASK_UNINTERRUPTIBLE);
		hrसमयr_sleeper_start_expires(&hs, mode);
		अगर (hs.task)
			io_schedule();
		hrसमयr_cancel(&hs.समयr);
		mode = HRTIMER_MODE_ABS;
	पूर्ण जबतक (hs.task && !संकेत_pending(current));

	__set_current_state(TASK_RUNNING);
	destroy_hrसमयr_on_stack(&hs.समयr);
	वापस true;
पूर्ण

अटल bool blk_mq_poll_hybrid(काष्ठा request_queue *q,
			       काष्ठा blk_mq_hw_ctx *hctx, blk_qc_t cookie)
अणु
	काष्ठा request *rq;

	अगर (q->poll_nsec == BLK_MQ_POLL_CLASSIC)
		वापस false;

	अगर (!blk_qc_t_is_पूर्णांकernal(cookie))
		rq = blk_mq_tag_to_rq(hctx->tags, blk_qc_t_to_tag(cookie));
	अन्यथा अणु
		rq = blk_mq_tag_to_rq(hctx->sched_tags, blk_qc_t_to_tag(cookie));
		/*
		 * With scheduling, अगर the request has completed, we'll
		 * get a शून्य वापस here, as we clear the sched tag when
		 * that happens. The request still reमुख्यs valid, like always,
		 * so we should be safe with just the शून्य check.
		 */
		अगर (!rq)
			वापस false;
	पूर्ण

	वापस blk_mq_poll_hybrid_sleep(q, rq);
पूर्ण

/**
 * blk_poll - poll क्रम IO completions
 * @q:  the queue
 * @cookie: cookie passed back at IO submission समय
 * @spin: whether to spin क्रम completions
 *
 * Description:
 *    Poll क्रम completions on the passed in queue. Returns number of
 *    completed entries found. If @spin is true, then blk_poll will जारी
 *    looping until at least one completion is found, unless the task is
 *    otherwise marked running (or we need to reschedule).
 */
पूर्णांक blk_poll(काष्ठा request_queue *q, blk_qc_t cookie, bool spin)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	दीर्घ state;

	अगर (!blk_qc_t_valid(cookie) ||
	    !test_bit(QUEUE_FLAG_POLL, &q->queue_flags))
		वापस 0;

	अगर (current->plug)
		blk_flush_plug_list(current->plug, false);

	hctx = q->queue_hw_ctx[blk_qc_t_to_queue_num(cookie)];

	/*
	 * If we sleep, have the caller restart the poll loop to reset
	 * the state. Like क्रम the other success वापस हालs, the
	 * caller is responsible क्रम checking अगर the IO completed. If
	 * the IO isn't complete, we'll get called again and will go
	 * straight to the busy poll loop. If specअगरied not to spin,
	 * we also should not sleep.
	 */
	अगर (spin && blk_mq_poll_hybrid(q, hctx, cookie))
		वापस 1;

	hctx->poll_considered++;

	state = current->state;
	करो अणु
		पूर्णांक ret;

		hctx->poll_invoked++;

		ret = q->mq_ops->poll(hctx);
		अगर (ret > 0) अणु
			hctx->poll_success++;
			__set_current_state(TASK_RUNNING);
			वापस ret;
		पूर्ण

		अगर (संकेत_pending_state(state, current))
			__set_current_state(TASK_RUNNING);

		अगर (current->state == TASK_RUNNING)
			वापस 1;
		अगर (ret < 0 || !spin)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (!need_resched());

	__set_current_state(TASK_RUNNING);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(blk_poll);

अचिन्हित पूर्णांक blk_mq_rq_cpu(काष्ठा request *rq)
अणु
	वापस rq->mq_ctx->cpu;
पूर्ण
EXPORT_SYMBOL(blk_mq_rq_cpu);

अटल पूर्णांक __init blk_mq_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		init_llist_head(&per_cpu(blk_cpu_करोne, i));
	खोलो_softirq(BLOCK_SOFTIRQ, blk_करोne_softirq);

	cpuhp_setup_state_nocalls(CPUHP_BLOCK_SOFTIRQ_DEAD,
				  "block/softirq:dead", शून्य,
				  blk_softirq_cpu_dead);
	cpuhp_setup_state_multi(CPUHP_BLK_MQ_DEAD, "block/mq:dead", शून्य,
				blk_mq_hctx_notअगरy_dead);
	cpuhp_setup_state_multi(CPUHP_AP_BLK_MQ_ONLINE, "block/mq:online",
				blk_mq_hctx_notअगरy_online,
				blk_mq_hctx_notअगरy_offline);
	वापस 0;
पूर्ण
subsys_initcall(blk_mq_init);
