<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2006-2007 Pierre Ossman
 */
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/backing-dev.h>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>

#समावेश "queue.h"
#समावेश "block.h"
#समावेश "core.h"
#समावेश "card.h"
#समावेश "crypto.h"
#समावेश "host.h"

#घोषणा MMC_DMA_MAP_MERGE_SEGMENTS	512

अटल अंतरभूत bool mmc_cqe_dcmd_busy(काष्ठा mmc_queue *mq)
अणु
	/* Allow only 1 DCMD at a समय */
	वापस mq->in_flight[MMC_ISSUE_DCMD];
पूर्ण

व्योम mmc_cqe_check_busy(काष्ठा mmc_queue *mq)
अणु
	अगर ((mq->cqe_busy & MMC_CQE_DCMD_BUSY) && !mmc_cqe_dcmd_busy(mq))
		mq->cqe_busy &= ~MMC_CQE_DCMD_BUSY;
पूर्ण

अटल अंतरभूत bool mmc_cqe_can_dcmd(काष्ठा mmc_host *host)
अणु
	वापस host->caps2 & MMC_CAP2_CQE_DCMD;
पूर्ण

अटल क्रमागत mmc_issue_type mmc_cqe_issue_type(काष्ठा mmc_host *host,
					      काष्ठा request *req)
अणु
	चयन (req_op(req)) अणु
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
		वापस MMC_ISSUE_SYNC;
	हाल REQ_OP_FLUSH:
		वापस mmc_cqe_can_dcmd(host) ? MMC_ISSUE_DCMD : MMC_ISSUE_SYNC;
	शेष:
		वापस MMC_ISSUE_ASYNC;
	पूर्ण
पूर्ण

क्रमागत mmc_issue_type mmc_issue_type(काष्ठा mmc_queue *mq, काष्ठा request *req)
अणु
	काष्ठा mmc_host *host = mq->card->host;

	अगर (host->cqe_enabled && !host->hsq_enabled)
		वापस mmc_cqe_issue_type(host, req);

	अगर (req_op(req) == REQ_OP_READ || req_op(req) == REQ_OP_WRITE)
		वापस MMC_ISSUE_ASYNC;

	वापस MMC_ISSUE_SYNC;
पूर्ण

अटल व्योम __mmc_cqe_recovery_notअगरier(काष्ठा mmc_queue *mq)
अणु
	अगर (!mq->recovery_needed) अणु
		mq->recovery_needed = true;
		schedule_work(&mq->recovery_work);
	पूर्ण
पूर्ण

व्योम mmc_cqe_recovery_notअगरier(काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_queue_req *mqrq = container_of(mrq, काष्ठा mmc_queue_req,
						  brq.mrq);
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mq->lock, flags);
	__mmc_cqe_recovery_notअगरier(mq);
	spin_unlock_irqrestore(&mq->lock, flags);
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस mmc_cqe_समयd_out(काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mqrq = req_to_mmc_queue_req(req);
	काष्ठा mmc_request *mrq = &mqrq->brq.mrq;
	काष्ठा mmc_queue *mq = req->q->queuedata;
	काष्ठा mmc_host *host = mq->card->host;
	क्रमागत mmc_issue_type issue_type = mmc_issue_type(mq, req);
	bool recovery_needed = false;

	चयन (issue_type) अणु
	हाल MMC_ISSUE_ASYNC:
	हाल MMC_ISSUE_DCMD:
		अगर (host->cqe_ops->cqe_समयout(host, mrq, &recovery_needed)) अणु
			अगर (recovery_needed)
				mmc_cqe_recovery_notअगरier(mrq);
			वापस BLK_EH_RESET_TIMER;
		पूर्ण
		/* The request has gone alपढ़ोy */
		वापस BLK_EH_DONE;
	शेष:
		/* Timeout is handled by mmc core */
		वापस BLK_EH_RESET_TIMER;
	पूर्ण
पूर्ण

अटल क्रमागत blk_eh_समयr_वापस mmc_mq_समयd_out(काष्ठा request *req,
						 bool reserved)
अणु
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_host *host = card->host;
	अचिन्हित दीर्घ flags;
	bool ignore_tout;

	spin_lock_irqsave(&mq->lock, flags);
	ignore_tout = mq->recovery_needed || !host->cqe_enabled || host->hsq_enabled;
	spin_unlock_irqrestore(&mq->lock, flags);

	वापस ignore_tout ? BLK_EH_RESET_TIMER : mmc_cqe_समयd_out(req);
पूर्ण

अटल व्योम mmc_mq_recovery_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_queue *mq = container_of(work, काष्ठा mmc_queue,
					    recovery_work);
	काष्ठा request_queue *q = mq->queue;
	काष्ठा mmc_host *host = mq->card->host;

	mmc_get_card(mq->card, &mq->ctx);

	mq->in_recovery = true;

	अगर (host->cqe_enabled && !host->hsq_enabled)
		mmc_blk_cqe_recovery(mq);
	अन्यथा
		mmc_blk_mq_recovery(mq);

	mq->in_recovery = false;

	spin_lock_irq(&mq->lock);
	mq->recovery_needed = false;
	spin_unlock_irq(&mq->lock);

	अगर (host->hsq_enabled)
		host->cqe_ops->cqe_recovery_finish(host);

	mmc_put_card(mq->card, &mq->ctx);

	blk_mq_run_hw_queues(q, true);
पूर्ण

अटल काष्ठा scatterlist *mmc_alloc_sg(पूर्णांक sg_len, gfp_t gfp)
अणु
	काष्ठा scatterlist *sg;

	sg = kदो_स्मृति_array(sg_len, माप(*sg), gfp);
	अगर (sg)
		sg_init_table(sg, sg_len);

	वापस sg;
पूर्ण

अटल व्योम mmc_queue_setup_discard(काष्ठा request_queue *q,
				    काष्ठा mmc_card *card)
अणु
	अचिन्हित max_discard;

	max_discard = mmc_calc_max_discard(card);
	अगर (!max_discard)
		वापस;

	blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
	blk_queue_max_discard_sectors(q, max_discard);
	q->limits.discard_granularity = card->pref_erase << 9;
	/* granularity must not be greater than max. discard */
	अगर (card->pref_erase > max_discard)
		q->limits.discard_granularity = SECTOR_SIZE;
	अगर (mmc_can_secure_erase_trim(card))
		blk_queue_flag_set(QUEUE_FLAG_SECERASE, q);
पूर्ण

अटल अचिन्हित पूर्णांक mmc_get_max_segments(काष्ठा mmc_host *host)
अणु
	वापस host->can_dma_map_merge ? MMC_DMA_MAP_MERGE_SEGMENTS :
					 host->max_segs;
पूर्ण

/**
 * mmc_init_request() - initialize the MMC-specअगरic per-request data
 * @mq: the request queue
 * @req: the request
 * @gfp: memory allocation policy
 */
अटल पूर्णांक __mmc_init_request(काष्ठा mmc_queue *mq, काष्ठा request *req,
			      gfp_t gfp)
अणु
	काष्ठा mmc_queue_req *mq_rq = req_to_mmc_queue_req(req);
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_host *host = card->host;

	mq_rq->sg = mmc_alloc_sg(mmc_get_max_segments(host), gfp);
	अगर (!mq_rq->sg)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mmc_निकास_request(काष्ठा request_queue *q, काष्ठा request *req)
अणु
	काष्ठा mmc_queue_req *mq_rq = req_to_mmc_queue_req(req);

	kमुक्त(mq_rq->sg);
	mq_rq->sg = शून्य;
पूर्ण

अटल पूर्णांक mmc_mq_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *req,
			       अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	वापस __mmc_init_request(set->driver_data, req, GFP_KERNEL);
पूर्ण

अटल व्योम mmc_mq_निकास_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *req,
				अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा mmc_queue *mq = set->driver_data;

	mmc_निकास_request(mq->queue, req);
पूर्ण

अटल blk_status_t mmc_mq_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				    स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *req = bd->rq;
	काष्ठा request_queue *q = req->q;
	काष्ठा mmc_queue *mq = q->queuedata;
	काष्ठा mmc_card *card = mq->card;
	काष्ठा mmc_host *host = card->host;
	क्रमागत mmc_issue_type issue_type;
	क्रमागत mmc_issued issued;
	bool get_card, cqe_retune_ok;
	पूर्णांक ret;

	अगर (mmc_card_हटाओd(mq->card)) अणु
		req->rq_flags |= RQF_QUIET;
		वापस BLK_STS_IOERR;
	पूर्ण

	issue_type = mmc_issue_type(mq, req);

	spin_lock_irq(&mq->lock);

	अगर (mq->recovery_needed || mq->busy) अणु
		spin_unlock_irq(&mq->lock);
		वापस BLK_STS_RESOURCE;
	पूर्ण

	चयन (issue_type) अणु
	हाल MMC_ISSUE_DCMD:
		अगर (mmc_cqe_dcmd_busy(mq)) अणु
			mq->cqe_busy |= MMC_CQE_DCMD_BUSY;
			spin_unlock_irq(&mq->lock);
			वापस BLK_STS_RESOURCE;
		पूर्ण
		अवरोध;
	हाल MMC_ISSUE_ASYNC:
		/*
		 * For MMC host software queue, we only allow 2 requests in
		 * flight to aव्योम a दीर्घ latency.
		 */
		अगर (host->hsq_enabled && mq->in_flight[issue_type] > 2) अणु
			spin_unlock_irq(&mq->lock);
			वापस BLK_STS_RESOURCE;
		पूर्ण
		अवरोध;
	शेष:
		/*
		 * Timeouts are handled by mmc core, and we करोn't have a host
		 * API to पात requests, so we can't handle the समयout anyway.
		 * However, when the समयout happens, blk_mq_complete_request()
		 * no दीर्घer works (to stop the request disappearing under us).
		 * To aव्योम racing with that, set a large समयout.
		 */
		req->समयout = 600 * HZ;
		अवरोध;
	पूर्ण

	/* Parallel dispatch of requests is not supported at the moment */
	mq->busy = true;

	mq->in_flight[issue_type] += 1;
	get_card = (mmc_tot_in_flight(mq) == 1);
	cqe_retune_ok = (mmc_cqe_qcnt(mq) == 1);

	spin_unlock_irq(&mq->lock);

	अगर (!(req->rq_flags & RQF_DONTPREP)) अणु
		req_to_mmc_queue_req(req)->retries = 0;
		req->rq_flags |= RQF_DONTPREP;
	पूर्ण

	अगर (get_card)
		mmc_get_card(card, &mq->ctx);

	अगर (host->cqe_enabled) अणु
		host->retune_now = host->need_retune && cqe_retune_ok &&
				   !host->hold_retune;
	पूर्ण

	blk_mq_start_request(req);

	issued = mmc_blk_mq_issue_rq(mq, req);

	चयन (issued) अणु
	हाल MMC_REQ_BUSY:
		ret = BLK_STS_RESOURCE;
		अवरोध;
	हाल MMC_REQ_FAILED_TO_START:
		ret = BLK_STS_IOERR;
		अवरोध;
	शेष:
		ret = BLK_STS_OK;
		अवरोध;
	पूर्ण

	अगर (issued != MMC_REQ_STARTED) अणु
		bool put_card = false;

		spin_lock_irq(&mq->lock);
		mq->in_flight[issue_type] -= 1;
		अगर (mmc_tot_in_flight(mq) == 0)
			put_card = true;
		mq->busy = false;
		spin_unlock_irq(&mq->lock);
		अगर (put_card)
			mmc_put_card(card, &mq->ctx);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(mq->busy, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops mmc_mq_ops = अणु
	.queue_rq	= mmc_mq_queue_rq,
	.init_request	= mmc_mq_init_request,
	.निकास_request	= mmc_mq_निकास_request,
	.complete	= mmc_blk_mq_complete,
	.समयout	= mmc_mq_समयd_out,
पूर्ण;

अटल व्योम mmc_setup_queue(काष्ठा mmc_queue *mq, काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित block_size = 512;

	blk_queue_flag_set(QUEUE_FLAG_NONROT, mq->queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, mq->queue);
	अगर (mmc_can_erase(card))
		mmc_queue_setup_discard(mq->queue, card);

	अगर (!mmc_dev(host)->dma_mask || !*mmc_dev(host)->dma_mask)
		blk_queue_bounce_limit(mq->queue, BLK_BOUNCE_HIGH);
	blk_queue_max_hw_sectors(mq->queue,
		min(host->max_blk_count, host->max_req_size / 512));
	अगर (host->can_dma_map_merge)
		WARN(!blk_queue_can_use_dma_map_merging(mq->queue,
							mmc_dev(host)),
		     "merging was advertised but not possible");
	blk_queue_max_segments(mq->queue, mmc_get_max_segments(host));

	अगर (mmc_card_mmc(card) && card->ext_csd.data_sector_size) अणु
		block_size = card->ext_csd.data_sector_size;
		WARN_ON(block_size != 512 && block_size != 4096);
	पूर्ण

	blk_queue_logical_block_size(mq->queue, block_size);
	/*
	 * After blk_queue_can_use_dma_map_merging() was called with succeed,
	 * since it calls blk_queue_virt_boundary(), the mmc should not call
	 * both blk_queue_max_segment_size().
	 */
	अगर (!host->can_dma_map_merge)
		blk_queue_max_segment_size(mq->queue,
			round_करोwn(host->max_seg_size, block_size));

	dma_set_max_seg_size(mmc_dev(host), queue_max_segment_size(mq->queue));

	INIT_WORK(&mq->recovery_work, mmc_mq_recovery_handler);
	INIT_WORK(&mq->complete_work, mmc_blk_mq_complete_work);

	mutex_init(&mq->complete_lock);

	init_रुकोqueue_head(&mq->रुको);

	mmc_crypto_setup_queue(mq->queue, host);
पूर्ण

अटल अंतरभूत bool mmc_merge_capable(काष्ठा mmc_host *host)
अणु
	वापस host->caps2 & MMC_CAP2_MERGE_CAPABLE;
पूर्ण

/* Set queue depth to get a reasonable value क्रम q->nr_requests */
#घोषणा MMC_QUEUE_DEPTH 64

/**
 * mmc_init_queue - initialise a queue काष्ठाure.
 * @mq: mmc queue
 * @card: mmc card to attach this queue
 *
 * Initialise a MMC card request queue.
 */
पूर्णांक mmc_init_queue(काष्ठा mmc_queue *mq, काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक ret;

	mq->card = card;
	
	spin_lock_init(&mq->lock);

	स_रखो(&mq->tag_set, 0, माप(mq->tag_set));
	mq->tag_set.ops = &mmc_mq_ops;
	/*
	 * The queue depth क्रम CQE must match the hardware because the request
	 * tag is used to index the hardware queue.
	 */
	अगर (host->cqe_enabled && !host->hsq_enabled)
		mq->tag_set.queue_depth =
			min_t(पूर्णांक, card->ext_csd.cmdq_depth, host->cqe_qdepth);
	अन्यथा
		mq->tag_set.queue_depth = MMC_QUEUE_DEPTH;
	mq->tag_set.numa_node = NUMA_NO_NODE;
	mq->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;
	mq->tag_set.nr_hw_queues = 1;
	mq->tag_set.cmd_size = माप(काष्ठा mmc_queue_req);
	mq->tag_set.driver_data = mq;

	/*
	 * Since blk_mq_alloc_tag_set() calls .init_request() of mmc_mq_ops,
	 * the host->can_dma_map_merge should be set beक्रमe to get max_segs
	 * from mmc_get_max_segments().
	 */
	अगर (mmc_merge_capable(host) &&
	    host->max_segs < MMC_DMA_MAP_MERGE_SEGMENTS &&
	    dma_get_merge_boundary(mmc_dev(host)))
		host->can_dma_map_merge = 1;
	अन्यथा
		host->can_dma_map_merge = 0;

	ret = blk_mq_alloc_tag_set(&mq->tag_set);
	अगर (ret)
		वापस ret;

	mq->queue = blk_mq_init_queue(&mq->tag_set);
	अगर (IS_ERR(mq->queue)) अणु
		ret = PTR_ERR(mq->queue);
		जाओ मुक्त_tag_set;
	पूर्ण

	अगर (mmc_host_is_spi(host) && host->use_spi_crc)
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, mq->queue);

	mq->queue->queuedata = mq;
	blk_queue_rq_समयout(mq->queue, 60 * HZ);

	mmc_setup_queue(mq, card);
	वापस 0;

मुक्त_tag_set:
	blk_mq_मुक्त_tag_set(&mq->tag_set);
	वापस ret;
पूर्ण

व्योम mmc_queue_suspend(काष्ठा mmc_queue *mq)
अणु
	blk_mq_quiesce_queue(mq->queue);

	/*
	 * The host reमुख्यs claimed जबतक there are outstanding requests, so
	 * simply claiming and releasing here ensures there are none.
	 */
	mmc_claim_host(mq->card->host);
	mmc_release_host(mq->card->host);
पूर्ण

व्योम mmc_queue_resume(काष्ठा mmc_queue *mq)
अणु
	blk_mq_unquiesce_queue(mq->queue);
पूर्ण

व्योम mmc_cleanup_queue(काष्ठा mmc_queue *mq)
अणु
	काष्ठा request_queue *q = mq->queue;

	/*
	 * The legacy code handled the possibility of being suspended,
	 * so करो that here too.
	 */
	अगर (blk_queue_quiesced(q))
		blk_mq_unquiesce_queue(q);

	blk_cleanup_queue(q);
	blk_mq_मुक्त_tag_set(&mq->tag_set);

	/*
	 * A request can be completed beक्रमe the next request, potentially
	 * leaving a complete_work with nothing to करो. Such a work item might
	 * still be queued at this poपूर्णांक. Flush it.
	 */
	flush_work(&mq->complete_work);

	mq->card = शून्य;
पूर्ण

/*
 * Prepare the sg list(s) to be handed of to the host driver
 */
अचिन्हित पूर्णांक mmc_queue_map_sg(काष्ठा mmc_queue *mq, काष्ठा mmc_queue_req *mqrq)
अणु
	काष्ठा request *req = mmc_queue_req_to_req(mqrq);

	वापस blk_rq_map_sg(mq->queue, req, mqrq->sg);
पूर्ण
