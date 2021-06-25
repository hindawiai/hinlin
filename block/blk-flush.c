<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions to sequence PREFLUSH and FUA ग_लिखोs.
 *
 * Copyright (C) 2011		Max Planck Institute क्रम Gravitational Physics
 * Copyright (C) 2011		Tejun Heo <tj@kernel.org>
 *
 * REQ_अणुPREFLUSH|FUAपूर्ण requests are decomposed to sequences consisted of three
 * optional steps - PREFLUSH, DATA and POSTFLUSH - according to the request
 * properties and hardware capability.
 *
 * If a request करोesn't have data, only REQ_PREFLUSH makes sense, which
 * indicates a simple flush request.  If there is data, REQ_PREFLUSH indicates
 * that the device cache should be flushed beक्रमe the data is executed, and
 * REQ_FUA means that the data must be on non-अस्थिर media on request
 * completion.
 *
 * If the device करोesn't have writeback cache, PREFLUSH and FUA don't make any
 * dअगरference.  The requests are either completed immediately अगर there's no data
 * or executed as normal requests otherwise.
 *
 * If the device has ग_लिखोback cache and supports FUA, REQ_PREFLUSH is
 * translated to PREFLUSH but REQ_FUA is passed करोwn directly with DATA.
 *
 * If the device has ग_लिखोback cache and करोesn't support FUA, REQ_PREFLUSH
 * is translated to PREFLUSH and REQ_FUA to POSTFLUSH.
 *
 * The actual execution of flush is द्विगुन buffered.  Whenever a request
 * needs to execute PRE or POSTFLUSH, it queues at
 * fq->flush_queue[fq->flush_pending_idx].  Once certain criteria are met, a
 * REQ_OP_FLUSH is issued and the pending_idx is toggled.  When the flush
 * completes, all the requests which were pending are proceeded to the next
 * step.  This allows arbitrary merging of dअगरferent types of PREFLUSH/FUA
 * requests.
 *
 * Currently, the following conditions are used to determine when to issue
 * flush.
 *
 * C1. At any given समय, only one flush shall be in progress.  This makes
 *     द्विगुन buffering sufficient.
 *
 * C2. Flush is deferred अगर any request is executing DATA of its sequence.
 *     This aव्योमs issuing separate POSTFLUSHes क्रम requests which shared
 *     PREFLUSH.
 *
 * C3. The second condition is ignored अगर there is a request which has
 *     रुकोed दीर्घer than FLUSH_PENDING_TIMEOUT.  This is to aव्योम
 *     starvation in the unlikely हाल where there are continuous stream of
 *     FUA (without PREFLUSH) requests.
 *
 * For devices which support FUA, it isn't clear whether C2 (and thus C3)
 * is beneficial.
 *
 * Note that a sequenced PREFLUSH/FUA request with DATA is completed twice.
 * Once जबतक executing DATA and again after the whole sequence is
 * complete.  The first completion updates the contained bio but करोesn't
 * finish it so that the bio submitter is notअगरied only after the whole
 * sequence is complete.  This is implemented by testing RQF_FLUSH_SEQ in
 * req_bio_endio().
 *
 * The above peculiarity requires that each PREFLUSH/FUA request has only one
 * bio attached to it, which is guaranteed as they aren't allowed to be
 * merged in the usual way.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/gfp.h>
#समावेश <linux/blk-mq.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-mq-sched.h"

/* PREFLUSH/FUA sequences */
क्रमागत अणु
	REQ_FSEQ_PREFLUSH	= (1 << 0), /* pre-flushing in progress */
	REQ_FSEQ_DATA		= (1 << 1), /* data ग_लिखो in progress */
	REQ_FSEQ_POSTFLUSH	= (1 << 2), /* post-flushing in progress */
	REQ_FSEQ_DONE		= (1 << 3),

	REQ_FSEQ_ACTIONS	= REQ_FSEQ_PREFLUSH | REQ_FSEQ_DATA |
				  REQ_FSEQ_POSTFLUSH,

	/*
	 * If flush has been pending दीर्घer than the following समयout,
	 * it's issued even अगर flush_data requests are still in flight.
	 */
	FLUSH_PENDING_TIMEOUT	= 5 * HZ,
पूर्ण;

अटल व्योम blk_kick_flush(काष्ठा request_queue *q,
			   काष्ठा blk_flush_queue *fq, अचिन्हित पूर्णांक flags);

अटल अचिन्हित पूर्णांक blk_flush_policy(अचिन्हित दीर्घ fflags, काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक policy = 0;

	अगर (blk_rq_sectors(rq))
		policy |= REQ_FSEQ_DATA;

	अगर (fflags & (1UL << QUEUE_FLAG_WC)) अणु
		अगर (rq->cmd_flags & REQ_PREFLUSH)
			policy |= REQ_FSEQ_PREFLUSH;
		अगर (!(fflags & (1UL << QUEUE_FLAG_FUA)) &&
		    (rq->cmd_flags & REQ_FUA))
			policy |= REQ_FSEQ_POSTFLUSH;
	पूर्ण
	वापस policy;
पूर्ण

अटल अचिन्हित पूर्णांक blk_flush_cur_seq(काष्ठा request *rq)
अणु
	वापस 1 << ffz(rq->flush.seq);
पूर्ण

अटल व्योम blk_flush_restore_request(काष्ठा request *rq)
अणु
	/*
	 * After flush data completion, @rq->bio is %शून्य but we need to
	 * complete the bio again.  @rq->biotail is guaranteed to equal the
	 * original @rq->bio.  Restore it.
	 */
	rq->bio = rq->biotail;

	/* make @rq a normal request */
	rq->rq_flags &= ~RQF_FLUSH_SEQ;
	rq->end_io = rq->flush.saved_end_io;
पूर्ण

अटल व्योम blk_flush_queue_rq(काष्ठा request *rq, bool add_front)
अणु
	blk_mq_add_to_requeue_list(rq, add_front, true);
पूर्ण

अटल व्योम blk_account_io_flush(काष्ठा request *rq)
अणु
	काष्ठा block_device *part = rq->rq_disk->part0;

	part_stat_lock();
	part_stat_inc(part, ios[STAT_FLUSH]);
	part_stat_add(part, nsecs[STAT_FLUSH],
		      kसमय_get_ns() - rq->start_समय_ns);
	part_stat_unlock();
पूर्ण

/**
 * blk_flush_complete_seq - complete flush sequence
 * @rq: PREFLUSH/FUA request being sequenced
 * @fq: flush queue
 * @seq: sequences to complete (mask of %REQ_FSEQ_*, can be zero)
 * @error: whether an error occurred
 *
 * @rq just completed @seq part of its flush sequence, record the
 * completion and trigger the next step.
 *
 * CONTEXT:
 * spin_lock_irq(fq->mq_flush_lock)
 */
अटल व्योम blk_flush_complete_seq(काष्ठा request *rq,
				   काष्ठा blk_flush_queue *fq,
				   अचिन्हित पूर्णांक seq, blk_status_t error)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा list_head *pending = &fq->flush_queue[fq->flush_pending_idx];
	अचिन्हित पूर्णांक cmd_flags;

	BUG_ON(rq->flush.seq & seq);
	rq->flush.seq |= seq;
	cmd_flags = rq->cmd_flags;

	अगर (likely(!error))
		seq = blk_flush_cur_seq(rq);
	अन्यथा
		seq = REQ_FSEQ_DONE;

	चयन (seq) अणु
	हाल REQ_FSEQ_PREFLUSH:
	हाल REQ_FSEQ_POSTFLUSH:
		/* queue क्रम flush */
		अगर (list_empty(pending))
			fq->flush_pending_since = jअगरfies;
		list_move_tail(&rq->flush.list, pending);
		अवरोध;

	हाल REQ_FSEQ_DATA:
		list_move_tail(&rq->flush.list, &fq->flush_data_in_flight);
		blk_flush_queue_rq(rq, true);
		अवरोध;

	हाल REQ_FSEQ_DONE:
		/*
		 * @rq was previously adjusted by blk_insert_flush() क्रम
		 * flush sequencing and may alपढ़ोy have gone through the
		 * flush data request completion path.  Restore @rq क्रम
		 * normal completion and end it.
		 */
		BUG_ON(!list_empty(&rq->queuelist));
		list_del_init(&rq->flush.list);
		blk_flush_restore_request(rq);
		blk_mq_end_request(rq, error);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	blk_kick_flush(q, fq, cmd_flags);
पूर्ण

अटल व्योम flush_end_io(काष्ठा request *flush_rq, blk_status_t error)
अणु
	काष्ठा request_queue *q = flush_rq->q;
	काष्ठा list_head *running;
	काष्ठा request *rq, *n;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा blk_flush_queue *fq = blk_get_flush_queue(q, flush_rq->mq_ctx);

	blk_account_io_flush(flush_rq);

	/* release the tag's ownership to the req cloned from */
	spin_lock_irqsave(&fq->mq_flush_lock, flags);

	अगर (!refcount_dec_and_test(&flush_rq->ref)) अणु
		fq->rq_status = error;
		spin_unlock_irqrestore(&fq->mq_flush_lock, flags);
		वापस;
	पूर्ण

	/*
	 * Flush request has to be marked as IDLE when it is really ended
	 * because its .end_io() is called from समयout code path too क्रम
	 * aव्योमing use-after-मुक्त.
	 */
	WRITE_ONCE(flush_rq->state, MQ_RQ_IDLE);
	अगर (fq->rq_status != BLK_STS_OK)
		error = fq->rq_status;

	अगर (!q->elevator) अणु
		flush_rq->tag = BLK_MQ_NO_TAG;
	पूर्ण अन्यथा अणु
		blk_mq_put_driver_tag(flush_rq);
		flush_rq->पूर्णांकernal_tag = BLK_MQ_NO_TAG;
	पूर्ण

	running = &fq->flush_queue[fq->flush_running_idx];
	BUG_ON(fq->flush_pending_idx == fq->flush_running_idx);

	/* account completion of the flush request */
	fq->flush_running_idx ^= 1;

	/* and push the रुकोing requests to the next stage */
	list_क्रम_each_entry_safe(rq, n, running, flush.list) अणु
		अचिन्हित पूर्णांक seq = blk_flush_cur_seq(rq);

		BUG_ON(seq != REQ_FSEQ_PREFLUSH && seq != REQ_FSEQ_POSTFLUSH);
		blk_flush_complete_seq(rq, fq, seq, error);
	पूर्ण

	spin_unlock_irqrestore(&fq->mq_flush_lock, flags);
पूर्ण

/**
 * blk_kick_flush - consider issuing flush request
 * @q: request_queue being kicked
 * @fq: flush queue
 * @flags: cmd_flags of the original request
 *
 * Flush related states of @q have changed, consider issuing flush request.
 * Please पढ़ो the comment at the top of this file क्रम more info.
 *
 * CONTEXT:
 * spin_lock_irq(fq->mq_flush_lock)
 *
 */
अटल व्योम blk_kick_flush(काष्ठा request_queue *q, काष्ठा blk_flush_queue *fq,
			   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा list_head *pending = &fq->flush_queue[fq->flush_pending_idx];
	काष्ठा request *first_rq =
		list_first_entry(pending, काष्ठा request, flush.list);
	काष्ठा request *flush_rq = fq->flush_rq;

	/* C1 described at the top of this file */
	अगर (fq->flush_pending_idx != fq->flush_running_idx || list_empty(pending))
		वापस;

	/* C2 and C3 */
	अगर (!list_empty(&fq->flush_data_in_flight) &&
	    समय_beक्रमe(jअगरfies,
			fq->flush_pending_since + FLUSH_PENDING_TIMEOUT))
		वापस;

	/*
	 * Issue flush and toggle pending_idx.  This makes pending_idx
	 * dअगरferent from running_idx, which means flush is in flight.
	 */
	fq->flush_pending_idx ^= 1;

	blk_rq_init(q, flush_rq);

	/*
	 * In हाल of none scheduler, borrow tag from the first request
	 * since they can't be in flight at the same समय. And acquire
	 * the tag's ownership क्रम flush req.
	 *
	 * In हाल of IO scheduler, flush rq need to borrow scheduler tag
	 * just क्रम cheating put/get driver tag.
	 */
	flush_rq->mq_ctx = first_rq->mq_ctx;
	flush_rq->mq_hctx = first_rq->mq_hctx;

	अगर (!q->elevator) अणु
		flush_rq->tag = first_rq->tag;

		/*
		 * We borrow data request's driver tag, so have to mark
		 * this flush request as INFLIGHT क्रम aव्योमing द्विगुन
		 * account of this driver tag
		 */
		flush_rq->rq_flags |= RQF_MQ_INFLIGHT;
	पूर्ण अन्यथा
		flush_rq->पूर्णांकernal_tag = first_rq->पूर्णांकernal_tag;

	flush_rq->cmd_flags = REQ_OP_FLUSH | REQ_PREFLUSH;
	flush_rq->cmd_flags |= (flags & REQ_DRV) | (flags & REQ_FAILFAST_MASK);
	flush_rq->rq_flags |= RQF_FLUSH_SEQ;
	flush_rq->rq_disk = first_rq->rq_disk;
	flush_rq->end_io = flush_end_io;

	blk_flush_queue_rq(flush_rq, false);
पूर्ण

अटल व्योम mq_flush_data_end_io(काष्ठा request *rq, blk_status_t error)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा blk_mq_hw_ctx *hctx = rq->mq_hctx;
	काष्ठा blk_mq_ctx *ctx = rq->mq_ctx;
	अचिन्हित दीर्घ flags;
	काष्ठा blk_flush_queue *fq = blk_get_flush_queue(q, ctx);

	अगर (q->elevator) अणु
		WARN_ON(rq->tag < 0);
		blk_mq_put_driver_tag(rq);
	पूर्ण

	/*
	 * After populating an empty queue, kick it to aव्योम stall.  Read
	 * the comment in flush_end_io().
	 */
	spin_lock_irqsave(&fq->mq_flush_lock, flags);
	blk_flush_complete_seq(rq, fq, REQ_FSEQ_DATA, error);
	spin_unlock_irqrestore(&fq->mq_flush_lock, flags);

	blk_mq_sched_restart(hctx);
पूर्ण

/**
 * blk_insert_flush - insert a new PREFLUSH/FUA request
 * @rq: request to insert
 *
 * To be called from __elv_add_request() क्रम %ELEVATOR_INSERT_FLUSH insertions.
 * or __blk_mq_run_hw_queue() to dispatch request.
 * @rq is being submitted.  Analyze what needs to be करोne and put it on the
 * right queue.
 */
व्योम blk_insert_flush(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	अचिन्हित दीर्घ fflags = q->queue_flags;	/* may change, cache */
	अचिन्हित पूर्णांक policy = blk_flush_policy(fflags, rq);
	काष्ठा blk_flush_queue *fq = blk_get_flush_queue(q, rq->mq_ctx);

	/*
	 * @policy now records what operations need to be करोne.  Adjust
	 * REQ_PREFLUSH and FUA क्रम the driver.
	 */
	rq->cmd_flags &= ~REQ_PREFLUSH;
	अगर (!(fflags & (1UL << QUEUE_FLAG_FUA)))
		rq->cmd_flags &= ~REQ_FUA;

	/*
	 * REQ_PREFLUSH|REQ_FUA implies REQ_SYNC, so अगर we clear any
	 * of those flags, we have to set REQ_SYNC to aव्योम skewing
	 * the request accounting.
	 */
	rq->cmd_flags |= REQ_SYNC;

	/*
	 * An empty flush handed करोwn from a stacking driver may
	 * translate पूर्णांकo nothing अगर the underlying device करोes not
	 * advertise a ग_लिखो-back cache.  In this हाल, simply
	 * complete the request.
	 */
	अगर (!policy) अणु
		blk_mq_end_request(rq, 0);
		वापस;
	पूर्ण

	BUG_ON(rq->bio != rq->biotail); /*assumes zero or single bio rq */

	/*
	 * If there's data but flush is not necessary, the request can be
	 * processed directly without going through flush machinery.  Queue
	 * क्रम normal execution.
	 */
	अगर ((policy & REQ_FSEQ_DATA) &&
	    !(policy & (REQ_FSEQ_PREFLUSH | REQ_FSEQ_POSTFLUSH))) अणु
		blk_mq_request_bypass_insert(rq, false, false);
		वापस;
	पूर्ण

	/*
	 * @rq should go through flush machinery.  Mark it part of flush
	 * sequence and submit क्रम further processing.
	 */
	स_रखो(&rq->flush, 0, माप(rq->flush));
	INIT_LIST_HEAD(&rq->flush.list);
	rq->rq_flags |= RQF_FLUSH_SEQ;
	rq->flush.saved_end_io = rq->end_io; /* Usually शून्य */

	rq->end_io = mq_flush_data_end_io;

	spin_lock_irq(&fq->mq_flush_lock);
	blk_flush_complete_seq(rq, fq, REQ_FSEQ_ACTIONS & ~policy, 0);
	spin_unlock_irq(&fq->mq_flush_lock);
पूर्ण

/**
 * blkdev_issue_flush - queue a flush
 * @bdev:	blockdev to issue flush क्रम
 *
 * Description:
 *    Issue a flush क्रम the block device in question.
 */
पूर्णांक blkdev_issue_flush(काष्ठा block_device *bdev)
अणु
	काष्ठा bio bio;

	bio_init(&bio, शून्य, 0);
	bio_set_dev(&bio, bdev);
	bio.bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
	वापस submit_bio_रुको(&bio);
पूर्ण
EXPORT_SYMBOL(blkdev_issue_flush);

काष्ठा blk_flush_queue *blk_alloc_flush_queue(पूर्णांक node, पूर्णांक cmd_size,
					      gfp_t flags)
अणु
	काष्ठा blk_flush_queue *fq;
	पूर्णांक rq_sz = माप(काष्ठा request);

	fq = kzalloc_node(माप(*fq), flags, node);
	अगर (!fq)
		जाओ fail;

	spin_lock_init(&fq->mq_flush_lock);

	rq_sz = round_up(rq_sz + cmd_size, cache_line_size());
	fq->flush_rq = kzalloc_node(rq_sz, flags, node);
	अगर (!fq->flush_rq)
		जाओ fail_rq;

	INIT_LIST_HEAD(&fq->flush_queue[0]);
	INIT_LIST_HEAD(&fq->flush_queue[1]);
	INIT_LIST_HEAD(&fq->flush_data_in_flight);

	वापस fq;

 fail_rq:
	kमुक्त(fq);
 fail:
	वापस शून्य;
पूर्ण

व्योम blk_मुक्त_flush_queue(काष्ठा blk_flush_queue *fq)
अणु
	/* bio based request queue hasn't flush queue */
	अगर (!fq)
		वापस;

	kमुक्त(fq->flush_rq);
	kमुक्त(fq);
पूर्ण

/*
 * Allow driver to set its own lock class to fq->mq_flush_lock क्रम
 * aव्योमing lockdep complaपूर्णांक.
 *
 * flush_end_io() may be called recursively from some driver, such as
 * nvme-loop, so lockdep may complain 'possible recursive locking' because
 * all 'struct blk_flush_queue' instance share same mq_flush_lock lock class
 * key. We need to assign dअगरferent lock class क्रम these driver's
 * fq->mq_flush_lock क्रम aव्योमing the lockdep warning.
 *
 * Use dynamically allocated lock class key क्रम each 'blk_flush_queue'
 * instance is over-समाप्त, and more worse it पूर्णांकroduces horrible boot delay
 * issue because synchronize_rcu() is implied in lockdep_unरेजिस्टर_key which
 * is called क्रम each hctx release. SCSI probing may synchronously create and
 * destroy lots of MQ request_queues क्रम non-existent devices, and some robot
 * test kernel always enable lockdep option. It is observed that more than half
 * an hour is taken during SCSI MQ probe with per-fq lock class.
 */
व्योम blk_mq_hctx_set_fq_lock_class(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा lock_class_key *key)
अणु
	lockdep_set_class(&hctx->fq->mq_flush_lock, key);
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_hctx_set_fq_lock_class);
