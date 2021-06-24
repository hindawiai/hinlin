<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1991, 1992 Linus Torvalds
 * Copyright (C) 1994,      Karl Keyte: Added support क्रम disk statistics
 * Elevator latency, (C) 2000  Andrea Arcangeli <andrea@suse.de> SuSE
 * Queue request tables / lock, selectable elevator, Jens Axboe <axboe@suse.de>
 * kernel-करोc करोcumentation started by NeilBrown <neilb@cse.unsw.edu.au>
 *	-  July2000
 * bio reग_लिखो, highmem i/o, etc, Jens Axboe <axboe@suse.de> - may 2001
 */

/*
 * This handles all पढ़ो/ग_लिखो requests to block devices
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-pm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/delay.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/t10-pi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/bpf.h>
#समावेश <linux/psi.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/blk-crypto.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-sched.h"
#समावेश "blk-pm.h"
#समावेश "blk-rq-qos.h"

काष्ठा dentry *blk_debugfs_root;

EXPORT_TRACEPOINT_SYMBOL_GPL(block_bio_remap);
EXPORT_TRACEPOINT_SYMBOL_GPL(block_rq_remap);
EXPORT_TRACEPOINT_SYMBOL_GPL(block_bio_complete);
EXPORT_TRACEPOINT_SYMBOL_GPL(block_split);
EXPORT_TRACEPOINT_SYMBOL_GPL(block_unplug);
EXPORT_TRACEPOINT_SYMBOL_GPL(block_rq_insert);

DEFINE_IDA(blk_queue_ida);

/*
 * For queue allocation
 */
काष्ठा kmem_cache *blk_requestq_cachep;

/*
 * Controlling काष्ठाure to kblockd
 */
अटल काष्ठा workqueue_काष्ठा *kblockd_workqueue;

/**
 * blk_queue_flag_set - atomically set a queue flag
 * @flag: flag to be set
 * @q: request queue
 */
व्योम blk_queue_flag_set(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q)
अणु
	set_bit(flag, &q->queue_flags);
पूर्ण
EXPORT_SYMBOL(blk_queue_flag_set);

/**
 * blk_queue_flag_clear - atomically clear a queue flag
 * @flag: flag to be cleared
 * @q: request queue
 */
व्योम blk_queue_flag_clear(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q)
अणु
	clear_bit(flag, &q->queue_flags);
पूर्ण
EXPORT_SYMBOL(blk_queue_flag_clear);

/**
 * blk_queue_flag_test_and_set - atomically test and set a queue flag
 * @flag: flag to be set
 * @q: request queue
 *
 * Returns the previous value of @flag - 0 अगर the flag was not set and 1 अगर
 * the flag was alपढ़ोy set.
 */
bool blk_queue_flag_test_and_set(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q)
अणु
	वापस test_and_set_bit(flag, &q->queue_flags);
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_flag_test_and_set);

व्योम blk_rq_init(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	स_रखो(rq, 0, माप(*rq));

	INIT_LIST_HEAD(&rq->queuelist);
	rq->q = q;
	rq->__sector = (sector_t) -1;
	INIT_HLIST_NODE(&rq->hash);
	RB_CLEAR_NODE(&rq->rb_node);
	rq->tag = BLK_MQ_NO_TAG;
	rq->पूर्णांकernal_tag = BLK_MQ_NO_TAG;
	rq->start_समय_ns = kसमय_get_ns();
	rq->part = शून्य;
	refcount_set(&rq->ref, 1);
	blk_crypto_rq_set_शेषs(rq);
पूर्ण
EXPORT_SYMBOL(blk_rq_init);

#घोषणा REQ_OP_NAME(name) [REQ_OP_##name] = #name
अटल स्थिर अक्षर *स्थिर blk_op_name[] = अणु
	REQ_OP_NAME(READ),
	REQ_OP_NAME(WRITE),
	REQ_OP_NAME(FLUSH),
	REQ_OP_NAME(DISCARD),
	REQ_OP_NAME(SECURE_ERASE),
	REQ_OP_NAME(ZONE_RESET),
	REQ_OP_NAME(ZONE_RESET_ALL),
	REQ_OP_NAME(ZONE_OPEN),
	REQ_OP_NAME(ZONE_CLOSE),
	REQ_OP_NAME(ZONE_FINISH),
	REQ_OP_NAME(ZONE_APPEND),
	REQ_OP_NAME(WRITE_SAME),
	REQ_OP_NAME(WRITE_ZEROES),
	REQ_OP_NAME(SCSI_IN),
	REQ_OP_NAME(SCSI_OUT),
	REQ_OP_NAME(DRV_IN),
	REQ_OP_NAME(DRV_OUT),
पूर्ण;
#अघोषित REQ_OP_NAME

/**
 * blk_op_str - Return string XXX in the REQ_OP_XXX.
 * @op: REQ_OP_XXX.
 *
 * Description: Centralize block layer function to convert REQ_OP_XXX पूर्णांकo
 * string क्रमmat. Useful in the debugging and tracing bio or request. For
 * invalid REQ_OP_XXX it वापसs string "UNKNOWN".
 */
अंतरभूत स्थिर अक्षर *blk_op_str(अचिन्हित पूर्णांक op)
अणु
	स्थिर अक्षर *op_str = "UNKNOWN";

	अगर (op < ARRAY_SIZE(blk_op_name) && blk_op_name[op])
		op_str = blk_op_name[op];

	वापस op_str;
पूर्ण
EXPORT_SYMBOL_GPL(blk_op_str);

अटल स्थिर काष्ठा अणु
	पूर्णांक		त्रुटि_सं;
	स्थिर अक्षर	*name;
पूर्ण blk_errors[] = अणु
	[BLK_STS_OK]		= अणु 0,		"" पूर्ण,
	[BLK_STS_NOTSUPP]	= अणु -EOPNOTSUPP, "operation not supported" पूर्ण,
	[BLK_STS_TIMEOUT]	= अणु -ETIMEDOUT,	"timeout" पूर्ण,
	[BLK_STS_NOSPC]		= अणु -ENOSPC,	"critical space allocation" पूर्ण,
	[BLK_STS_TRANSPORT]	= अणु -ENOLINK,	"recoverable transport" पूर्ण,
	[BLK_STS_TARGET]	= अणु -EREMOTEIO,	"critical target" पूर्ण,
	[BLK_STS_NEXUS]		= अणु -EBADE,	"critical nexus" पूर्ण,
	[BLK_STS_MEDIUM]	= अणु -ENODATA,	"critical medium" पूर्ण,
	[BLK_STS_PROTECTION]	= अणु -EILSEQ,	"protection" पूर्ण,
	[BLK_STS_RESOURCE]	= अणु -ENOMEM,	"kernel resource" पूर्ण,
	[BLK_STS_DEV_RESOURCE]	= अणु -EBUSY,	"device resource" पूर्ण,
	[BLK_STS_AGAIN]		= अणु -EAGAIN,	"nonblocking retry" पूर्ण,

	/* device mapper special हाल, should not leak out: */
	[BLK_STS_DM_REQUEUE]	= अणु -EREMCHG, "dm internal retry" पूर्ण,

	/* zone device specअगरic errors */
	[BLK_STS_ZONE_OPEN_RESOURCE]	= अणु -ETOOMANYREFS, "open zones exceeded" पूर्ण,
	[BLK_STS_ZONE_ACTIVE_RESOURCE]	= अणु -EOVERFLOW, "active zones exceeded" पूर्ण,

	/* everything अन्यथा not covered above: */
	[BLK_STS_IOERR]		= अणु -EIO,	"I/O" पूर्ण,
पूर्ण;

blk_status_t त्रुटि_सं_to_blk_status(पूर्णांक त्रुटि_सं)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(blk_errors); i++) अणु
		अगर (blk_errors[i].त्रुटि_सं == त्रुटि_सं)
			वापस (__क्रमce blk_status_t)i;
	पूर्ण

	वापस BLK_STS_IOERR;
पूर्ण
EXPORT_SYMBOL_GPL(त्रुटि_सं_to_blk_status);

पूर्णांक blk_status_to_त्रुटि_सं(blk_status_t status)
अणु
	पूर्णांक idx = (__क्रमce पूर्णांक)status;

	अगर (WARN_ON_ONCE(idx >= ARRAY_SIZE(blk_errors)))
		वापस -EIO;
	वापस blk_errors[idx].त्रुटि_सं;
पूर्ण
EXPORT_SYMBOL_GPL(blk_status_to_त्रुटि_सं);

अटल व्योम prपूर्णांक_req_error(काष्ठा request *req, blk_status_t status,
		स्थिर अक्षर *caller)
अणु
	पूर्णांक idx = (__क्रमce पूर्णांक)status;

	अगर (WARN_ON_ONCE(idx >= ARRAY_SIZE(blk_errors)))
		वापस;

	prपूर्णांकk_ratelimited(KERN_ERR
		"%s: %s error, dev %s, sector %llu op 0x%x:(%s) flags 0x%x "
		"phys_seg %u prio class %u\n",
		caller, blk_errors[idx].name,
		req->rq_disk ? req->rq_disk->disk_name : "?",
		blk_rq_pos(req), req_op(req), blk_op_str(req_op(req)),
		req->cmd_flags & ~REQ_OP_MASK,
		req->nr_phys_segments,
		IOPRIO_PRIO_CLASS(req->ioprio));
पूर्ण

अटल व्योम req_bio_endio(काष्ठा request *rq, काष्ठा bio *bio,
			  अचिन्हित पूर्णांक nbytes, blk_status_t error)
अणु
	अगर (error)
		bio->bi_status = error;

	अगर (unlikely(rq->rq_flags & RQF_QUIET))
		bio_set_flag(bio, BIO_QUIET);

	bio_advance(bio, nbytes);

	अगर (req_op(rq) == REQ_OP_ZONE_APPEND && error == BLK_STS_OK) अणु
		/*
		 * Partial zone append completions cannot be supported as the
		 * BIO fragments may end up not being written sequentially.
		 */
		अगर (bio->bi_iter.bi_size)
			bio->bi_status = BLK_STS_IOERR;
		अन्यथा
			bio->bi_iter.bi_sector = rq->__sector;
	पूर्ण

	/* करोn't actually finish bio if it's part of flush sequence */
	अगर (bio->bi_iter.bi_size == 0 && !(rq->rq_flags & RQF_FLUSH_SEQ))
		bio_endio(bio);
पूर्ण

व्योम blk_dump_rq_flags(काष्ठा request *rq, अक्षर *msg)
अणु
	prपूर्णांकk(KERN_INFO "%s: dev %s: flags=%llx\n", msg,
		rq->rq_disk ? rq->rq_disk->disk_name : "?",
		(अचिन्हित दीर्घ दीर्घ) rq->cmd_flags);

	prपूर्णांकk(KERN_INFO "  sector %llu, nr/cnr %u/%u\n",
	       (अचिन्हित दीर्घ दीर्घ)blk_rq_pos(rq),
	       blk_rq_sectors(rq), blk_rq_cur_sectors(rq));
	prपूर्णांकk(KERN_INFO "  bio %p, biotail %p, len %u\n",
	       rq->bio, rq->biotail, blk_rq_bytes(rq));
पूर्ण
EXPORT_SYMBOL(blk_dump_rq_flags);

/**
 * blk_sync_queue - cancel any pending callbacks on a queue
 * @q: the queue
 *
 * Description:
 *     The block layer may perक्रमm asynchronous callback activity
 *     on a queue, such as calling the unplug function after a समयout.
 *     A block device may call blk_sync_queue to ensure that any
 *     such activity is cancelled, thus allowing it to release resources
 *     that the callbacks might use. The caller must alपढ़ोy have made sure
 *     that its ->submit_bio will not re-add plugging prior to calling
 *     this function.
 *
 *     This function करोes not cancel any asynchronous activity arising
 *     out of elevator or throttling code. That would require elevator_निकास()
 *     and blkcg_निकास_queue() to be called with queue lock initialized.
 *
 */
व्योम blk_sync_queue(काष्ठा request_queue *q)
अणु
	del_समयr_sync(&q->समयout);
	cancel_work_sync(&q->समयout_work);
पूर्ण
EXPORT_SYMBOL(blk_sync_queue);

/**
 * blk_set_pm_only - increment pm_only counter
 * @q: request queue poपूर्णांकer
 */
व्योम blk_set_pm_only(काष्ठा request_queue *q)
अणु
	atomic_inc(&q->pm_only);
पूर्ण
EXPORT_SYMBOL_GPL(blk_set_pm_only);

व्योम blk_clear_pm_only(काष्ठा request_queue *q)
अणु
	पूर्णांक pm_only;

	pm_only = atomic_dec_वापस(&q->pm_only);
	WARN_ON_ONCE(pm_only < 0);
	अगर (pm_only == 0)
		wake_up_all(&q->mq_मुक्तze_wq);
पूर्ण
EXPORT_SYMBOL_GPL(blk_clear_pm_only);

/**
 * blk_put_queue - decrement the request_queue refcount
 * @q: the request_queue काष्ठाure to decrement the refcount क्रम
 *
 * Decrements the refcount of the request_queue kobject. When this reaches 0
 * we'll have blk_release_queue() called.
 *
 * Context: Any context, but the last reference must not be dropped from
 *          atomic context.
 */
व्योम blk_put_queue(काष्ठा request_queue *q)
अणु
	kobject_put(&q->kobj);
पूर्ण
EXPORT_SYMBOL(blk_put_queue);

व्योम blk_set_queue_dying(काष्ठा request_queue *q)
अणु
	blk_queue_flag_set(QUEUE_FLAG_DYING, q);

	/*
	 * When queue DYING flag is set, we need to block new req
	 * entering queue, so we call blk_मुक्तze_queue_start() to
	 * prevent I/O from crossing blk_queue_enter().
	 */
	blk_मुक्तze_queue_start(q);

	अगर (queue_is_mq(q))
		blk_mq_wake_रुकोers(q);

	/* Make blk_queue_enter() reexamine the DYING flag. */
	wake_up_all(&q->mq_मुक्तze_wq);
पूर्ण
EXPORT_SYMBOL_GPL(blk_set_queue_dying);

/**
 * blk_cleanup_queue - shutकरोwn a request queue
 * @q: request queue to shutकरोwn
 *
 * Mark @q DYING, drain all pending requests, mark @q DEAD, destroy and
 * put it.  All future requests will be failed immediately with -ENODEV.
 *
 * Context: can sleep
 */
व्योम blk_cleanup_queue(काष्ठा request_queue *q)
अणु
	/* cannot be called from atomic context */
	might_sleep();

	WARN_ON_ONCE(blk_queue_रेजिस्टरed(q));

	/* mark @q DYING, no new request or merges will be allowed afterwards */
	blk_set_queue_dying(q);

	blk_queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	blk_queue_flag_set(QUEUE_FLAG_NOXMERGES, q);

	/*
	 * Drain all requests queued beक्रमe DYING marking. Set DEAD flag to
	 * prevent that blk_mq_run_hw_queues() accesses the hardware queues
	 * after draining finished.
	 */
	blk_मुक्तze_queue(q);

	rq_qos_निकास(q);

	blk_queue_flag_set(QUEUE_FLAG_DEAD, q);

	/* क्रम synchronous bio-based driver finish in-flight पूर्णांकegrity i/o */
	blk_flush_पूर्णांकegrity();

	/* @q won't process any more request, flush async actions */
	del_समयr_sync(&q->backing_dev_info->laptop_mode_wb_समयr);
	blk_sync_queue(q);

	अगर (queue_is_mq(q))
		blk_mq_निकास_queue(q);

	/*
	 * In theory, request pool of sched_tags beदीर्घs to request queue.
	 * However, the current implementation requires tag_set क्रम मुक्तing
	 * requests, so मुक्त the pool now.
	 *
	 * Queue has become frozen, there can't be any in-queue requests, so
	 * it is safe to मुक्त requests now.
	 */
	mutex_lock(&q->sysfs_lock);
	अगर (q->elevator)
		blk_mq_sched_मुक्त_requests(q);
	mutex_unlock(&q->sysfs_lock);

	percpu_ref_निकास(&q->q_usage_counter);

	/* @q is and will stay empty, shutकरोwn and put */
	blk_put_queue(q);
पूर्ण
EXPORT_SYMBOL(blk_cleanup_queue);

/**
 * blk_queue_enter() - try to increase q->q_usage_counter
 * @q: request queue poपूर्णांकer
 * @flags: BLK_MQ_REQ_NOWAIT and/or BLK_MQ_REQ_PM
 */
पूर्णांक blk_queue_enter(काष्ठा request_queue *q, blk_mq_req_flags_t flags)
अणु
	स्थिर bool pm = flags & BLK_MQ_REQ_PM;

	जबतक (true) अणु
		bool success = false;

		rcu_पढ़ो_lock();
		अगर (percpu_ref_tryget_live(&q->q_usage_counter)) अणु
			/*
			 * The code that increments the pm_only counter is
			 * responsible क्रम ensuring that that counter is
			 * globally visible beक्रमe the queue is unfrozen.
			 */
			अगर ((pm && queue_rpm_status(q) != RPM_SUSPENDED) ||
			    !blk_queue_pm_only(q)) अणु
				success = true;
			पूर्ण अन्यथा अणु
				percpu_ref_put(&q->q_usage_counter);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (success)
			वापस 0;

		अगर (flags & BLK_MQ_REQ_NOWAIT)
			वापस -EBUSY;

		/*
		 * पढ़ो pair of barrier in blk_मुक्तze_queue_start(),
		 * we need to order पढ़ोing __PERCPU_REF_DEAD flag of
		 * .q_usage_counter and पढ़ोing .mq_मुक्तze_depth or
		 * queue dying flag, otherwise the following रुको may
		 * never वापस अगर the two पढ़ोs are reordered.
		 */
		smp_rmb();

		रुको_event(q->mq_मुक्तze_wq,
			   (!q->mq_मुक्तze_depth &&
			    blk_pm_resume_queue(pm, q)) ||
			   blk_queue_dying(q));
		अगर (blk_queue_dying(q))
			वापस -ENODEV;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक bio_queue_enter(काष्ठा bio *bio)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	bool noरुको = bio->bi_opf & REQ_NOWAIT;
	पूर्णांक ret;

	ret = blk_queue_enter(q, noरुको ? BLK_MQ_REQ_NOWAIT : 0);
	अगर (unlikely(ret)) अणु
		अगर (noरुको && !blk_queue_dying(q))
			bio_wouldblock_error(bio);
		अन्यथा
			bio_io_error(bio);
	पूर्ण

	वापस ret;
पूर्ण

व्योम blk_queue_निकास(काष्ठा request_queue *q)
अणु
	percpu_ref_put(&q->q_usage_counter);
पूर्ण

अटल व्योम blk_queue_usage_counter_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा request_queue *q =
		container_of(ref, काष्ठा request_queue, q_usage_counter);

	wake_up_all(&q->mq_मुक्तze_wq);
पूर्ण

अटल व्योम blk_rq_समयd_out_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा request_queue *q = from_समयr(q, t, समयout);

	kblockd_schedule_work(&q->समयout_work);
पूर्ण

अटल व्योम blk_समयout_work(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

काष्ठा request_queue *blk_alloc_queue(पूर्णांक node_id)
अणु
	काष्ठा request_queue *q;
	पूर्णांक ret;

	q = kmem_cache_alloc_node(blk_requestq_cachep,
				GFP_KERNEL | __GFP_ZERO, node_id);
	अगर (!q)
		वापस शून्य;

	q->last_merge = शून्य;

	q->id = ida_simple_get(&blk_queue_ida, 0, 0, GFP_KERNEL);
	अगर (q->id < 0)
		जाओ fail_q;

	ret = bioset_init(&q->bio_split, BIO_POOL_SIZE, 0, 0);
	अगर (ret)
		जाओ fail_id;

	q->backing_dev_info = bdi_alloc(node_id);
	अगर (!q->backing_dev_info)
		जाओ fail_split;

	q->stats = blk_alloc_queue_stats();
	अगर (!q->stats)
		जाओ fail_stats;

	q->node = node_id;

	atomic_set(&q->nr_active_requests_shared_sbiपंचांगap, 0);

	समयr_setup(&q->backing_dev_info->laptop_mode_wb_समयr,
		    laptop_mode_समयr_fn, 0);
	समयr_setup(&q->समयout, blk_rq_समयd_out_समयr, 0);
	INIT_WORK(&q->समयout_work, blk_समयout_work);
	INIT_LIST_HEAD(&q->icq_list);
#अगर_घोषित CONFIG_BLK_CGROUP
	INIT_LIST_HEAD(&q->blkg_list);
#पूर्ण_अगर

	kobject_init(&q->kobj, &blk_queue_ktype);

	mutex_init(&q->debugfs_mutex);
	mutex_init(&q->sysfs_lock);
	mutex_init(&q->sysfs_dir_lock);
	spin_lock_init(&q->queue_lock);

	init_रुकोqueue_head(&q->mq_मुक्तze_wq);
	mutex_init(&q->mq_मुक्तze_lock);

	/*
	 * Init percpu_ref in atomic mode so that it's faster to shutकरोwn.
	 * See blk_रेजिस्टर_queue() क्रम details.
	 */
	अगर (percpu_ref_init(&q->q_usage_counter,
				blk_queue_usage_counter_release,
				PERCPU_REF_INIT_ATOMIC, GFP_KERNEL))
		जाओ fail_bdi;

	अगर (blkcg_init_queue(q))
		जाओ fail_ref;

	blk_queue_dma_alignment(q, 511);
	blk_set_शेष_limits(&q->limits);
	q->nr_requests = BLKDEV_MAX_RQ;

	वापस q;

fail_ref:
	percpu_ref_निकास(&q->q_usage_counter);
fail_bdi:
	blk_मुक्त_queue_stats(q->stats);
fail_stats:
	bdi_put(q->backing_dev_info);
fail_split:
	bioset_निकास(&q->bio_split);
fail_id:
	ida_simple_हटाओ(&blk_queue_ida, q->id);
fail_q:
	kmem_cache_मुक्त(blk_requestq_cachep, q);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(blk_alloc_queue);

/**
 * blk_get_queue - increment the request_queue refcount
 * @q: the request_queue काष्ठाure to increment the refcount क्रम
 *
 * Increment the refcount of the request_queue kobject.
 *
 * Context: Any context.
 */
bool blk_get_queue(काष्ठा request_queue *q)
अणु
	अगर (likely(!blk_queue_dying(q))) अणु
		__blk_get_queue(q);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(blk_get_queue);

/**
 * blk_get_request - allocate a request
 * @q: request queue to allocate a request क्रम
 * @op: operation (REQ_OP_*) and REQ_* flags, e.g. REQ_SYNC.
 * @flags: BLK_MQ_REQ_* flags, e.g. BLK_MQ_REQ_NOWAIT.
 */
काष्ठा request *blk_get_request(काष्ठा request_queue *q, अचिन्हित पूर्णांक op,
				blk_mq_req_flags_t flags)
अणु
	काष्ठा request *req;

	WARN_ON_ONCE(op & REQ_NOWAIT);
	WARN_ON_ONCE(flags & ~(BLK_MQ_REQ_NOWAIT | BLK_MQ_REQ_PM));

	req = blk_mq_alloc_request(q, op, flags);
	अगर (!IS_ERR(req) && q->mq_ops->initialize_rq_fn)
		q->mq_ops->initialize_rq_fn(req);

	वापस req;
पूर्ण
EXPORT_SYMBOL(blk_get_request);

व्योम blk_put_request(काष्ठा request *req)
अणु
	blk_mq_मुक्त_request(req);
पूर्ण
EXPORT_SYMBOL(blk_put_request);

अटल व्योम handle_bad_sector(काष्ठा bio *bio, sector_t maxsector)
अणु
	अक्षर b[BDEVNAME_SIZE];

	pr_info_ratelimited("attempt to access beyond end of device\n"
			    "%s: rw=%d, want=%llu, limit=%llu\n",
			    bio_devname(bio, b), bio->bi_opf,
			    bio_end_sector(bio), maxsector);
पूर्ण

#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST

अटल DECLARE_FAULT_ATTR(fail_make_request);

अटल पूर्णांक __init setup_fail_make_request(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_make_request, str);
पूर्ण
__setup("fail_make_request=", setup_fail_make_request);

अटल bool should_fail_request(काष्ठा block_device *part, अचिन्हित पूर्णांक bytes)
अणु
	वापस part->bd_make_it_fail && should_fail(&fail_make_request, bytes);
पूर्ण

अटल पूर्णांक __init fail_make_request_debugfs(व्योम)
अणु
	काष्ठा dentry *dir = fault_create_debugfs_attr("fail_make_request",
						शून्य, &fail_make_request);

	वापस PTR_ERR_OR_ZERO(dir);
पूर्ण

late_initcall(fail_make_request_debugfs);

#अन्यथा /* CONFIG_FAIL_MAKE_REQUEST */

अटल अंतरभूत bool should_fail_request(काष्ठा block_device *part,
					अचिन्हित पूर्णांक bytes)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_FAIL_MAKE_REQUEST */

अटल अंतरभूत bool bio_check_ro(काष्ठा bio *bio)
अणु
	अगर (op_is_ग_लिखो(bio_op(bio)) && bdev_पढ़ो_only(bio->bi_bdev)) अणु
		अक्षर b[BDEVNAME_SIZE];

		अगर (op_is_flush(bio->bi_opf) && !bio_sectors(bio))
			वापस false;

		WARN_ONCE(1,
		       "Trying to write to read-only block-device %s (partno %d)\n",
			bio_devname(bio, b), bio->bi_bdev->bd_partno);
		/* Older lvm-tools actually trigger this */
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल noअंतरभूत पूर्णांक should_fail_bio(काष्ठा bio *bio)
अणु
	अगर (should_fail_request(bdev_whole(bio->bi_bdev), bio->bi_iter.bi_size))
		वापस -EIO;
	वापस 0;
पूर्ण
ALLOW_ERROR_INJECTION(should_fail_bio, ERRNO);

/*
 * Check whether this bio extends beyond the end of the device or partition.
 * This may well happen - the kernel calls bपढ़ो() without checking the size of
 * the device, e.g., when mounting a file प्रणाली.
 */
अटल अंतरभूत पूर्णांक bio_check_eod(काष्ठा bio *bio)
अणु
	sector_t maxsector = bdev_nr_sectors(bio->bi_bdev);
	अचिन्हित पूर्णांक nr_sectors = bio_sectors(bio);

	अगर (nr_sectors && maxsector &&
	    (nr_sectors > maxsector ||
	     bio->bi_iter.bi_sector > maxsector - nr_sectors)) अणु
		handle_bad_sector(bio, maxsector);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remap block n of partition p to block n+start(p) of the disk.
 */
अटल पूर्णांक blk_partition_remap(काष्ठा bio *bio)
अणु
	काष्ठा block_device *p = bio->bi_bdev;

	अगर (unlikely(should_fail_request(p, bio->bi_iter.bi_size)))
		वापस -EIO;
	अगर (bio_sectors(bio)) अणु
		bio->bi_iter.bi_sector += p->bd_start_sect;
		trace_block_bio_remap(bio, p->bd_dev,
				      bio->bi_iter.bi_sector -
				      p->bd_start_sect);
	पूर्ण
	bio_set_flag(bio, BIO_REMAPPED);
	वापस 0;
पूर्ण

/*
 * Check ग_लिखो append to a zoned block device.
 */
अटल अंतरभूत blk_status_t blk_check_zone_append(काष्ठा request_queue *q,
						 काष्ठा bio *bio)
अणु
	sector_t pos = bio->bi_iter.bi_sector;
	पूर्णांक nr_sectors = bio_sectors(bio);

	/* Only applicable to zoned block devices */
	अगर (!blk_queue_is_zoned(q))
		वापस BLK_STS_NOTSUPP;

	/* The bio sector must poपूर्णांक to the start of a sequential zone */
	अगर (pos & (blk_queue_zone_sectors(q) - 1) ||
	    !blk_queue_zone_is_seq(q, pos))
		वापस BLK_STS_IOERR;

	/*
	 * Not allowed to cross zone boundaries. Otherwise, the BIO will be
	 * split and could result in non-contiguous sectors being written in
	 * dअगरferent zones.
	 */
	अगर (nr_sectors > q->limits.chunk_sectors)
		वापस BLK_STS_IOERR;

	/* Make sure the BIO is small enough and will not get split */
	अगर (nr_sectors > q->limits.max_zone_append_sectors)
		वापस BLK_STS_IOERR;

	bio->bi_opf |= REQ_NOMERGE;

	वापस BLK_STS_OK;
पूर्ण

अटल noअंतरभूत_क्रम_stack bool submit_bio_checks(काष्ठा bio *bio)
अणु
	काष्ठा block_device *bdev = bio->bi_bdev;
	काष्ठा request_queue *q = bdev->bd_disk->queue;
	blk_status_t status = BLK_STS_IOERR;
	काष्ठा blk_plug *plug;

	might_sleep();

	plug = blk_mq_plug(q, bio);
	अगर (plug && plug->noरुको)
		bio->bi_opf |= REQ_NOWAIT;

	/*
	 * For a REQ_NOWAIT based request, वापस -EOPNOTSUPP
	 * अगर queue करोes not support NOWAIT.
	 */
	अगर ((bio->bi_opf & REQ_NOWAIT) && !blk_queue_noरुको(q))
		जाओ not_supported;

	अगर (should_fail_bio(bio))
		जाओ end_io;
	अगर (unlikely(bio_check_ro(bio)))
		जाओ end_io;
	अगर (!bio_flagged(bio, BIO_REMAPPED)) अणु
		अगर (unlikely(bio_check_eod(bio)))
			जाओ end_io;
		अगर (bdev->bd_partno && unlikely(blk_partition_remap(bio)))
			जाओ end_io;
	पूर्ण

	/*
	 * Filter flush bio's early so that bio based drivers without flush
	 * support करोn't have to worry about them.
	 */
	अगर (op_is_flush(bio->bi_opf) &&
	    !test_bit(QUEUE_FLAG_WC, &q->queue_flags)) अणु
		bio->bi_opf &= ~(REQ_PREFLUSH | REQ_FUA);
		अगर (!bio_sectors(bio)) अणु
			status = BLK_STS_OK;
			जाओ end_io;
		पूर्ण
	पूर्ण

	अगर (!test_bit(QUEUE_FLAG_POLL, &q->queue_flags))
		bio->bi_opf &= ~REQ_HIPRI;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
		अगर (!blk_queue_discard(q))
			जाओ not_supported;
		अवरोध;
	हाल REQ_OP_SECURE_ERASE:
		अगर (!blk_queue_secure_erase(q))
			जाओ not_supported;
		अवरोध;
	हाल REQ_OP_WRITE_SAME:
		अगर (!q->limits.max_ग_लिखो_same_sectors)
			जाओ not_supported;
		अवरोध;
	हाल REQ_OP_ZONE_APPEND:
		status = blk_check_zone_append(q, bio);
		अगर (status != BLK_STS_OK)
			जाओ end_io;
		अवरोध;
	हाल REQ_OP_ZONE_RESET:
	हाल REQ_OP_ZONE_OPEN:
	हाल REQ_OP_ZONE_CLOSE:
	हाल REQ_OP_ZONE_FINISH:
		अगर (!blk_queue_is_zoned(q))
			जाओ not_supported;
		अवरोध;
	हाल REQ_OP_ZONE_RESET_ALL:
		अगर (!blk_queue_is_zoned(q) || !blk_queue_zone_resetall(q))
			जाओ not_supported;
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		अगर (!q->limits.max_ग_लिखो_zeroes_sectors)
			जाओ not_supported;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Various block parts want %current->io_context, so allocate it up
	 * front rather than dealing with lots of pain to allocate it only
	 * where needed. This may fail and the block layer knows how to live
	 * with it.
	 */
	अगर (unlikely(!current->io_context))
		create_task_io_context(current, GFP_ATOMIC, q->node);

	अगर (blk_throtl_bio(bio)) अणु
		blkcg_bio_issue_init(bio);
		वापस false;
	पूर्ण

	blk_cgroup_bio_start(bio);
	blkcg_bio_issue_init(bio);

	अगर (!bio_flagged(bio, BIO_TRACE_COMPLETION)) अणु
		trace_block_bio_queue(bio);
		/* Now that enqueuing has been traced, we need to trace
		 * completion as well.
		 */
		bio_set_flag(bio, BIO_TRACE_COMPLETION);
	पूर्ण
	वापस true;

not_supported:
	status = BLK_STS_NOTSUPP;
end_io:
	bio->bi_status = status;
	bio_endio(bio);
	वापस false;
पूर्ण

अटल blk_qc_t __submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा gendisk *disk = bio->bi_bdev->bd_disk;
	blk_qc_t ret = BLK_QC_T_NONE;

	अगर (blk_crypto_bio_prep(&bio)) अणु
		अगर (!disk->fops->submit_bio)
			वापस blk_mq_submit_bio(bio);
		ret = disk->fops->submit_bio(bio);
	पूर्ण
	blk_queue_निकास(disk->queue);
	वापस ret;
पूर्ण

/*
 * The loop in this function may be a bit non-obvious, and so deserves some
 * explanation:
 *
 *  - Beक्रमe entering the loop, bio->bi_next is शून्य (as all callers ensure
 *    that), so we have a list with a single bio.
 *  - We pretend that we have just taken it off a दीर्घer list, so we assign
 *    bio_list to a poपूर्णांकer to the bio_list_on_stack, thus initialising the
 *    bio_list of new bios to be added.  ->submit_bio() may indeed add some more
 *    bios through a recursive call to submit_bio_noacct.  If it did, we find a
 *    non-शून्य value in bio_list and re-enter the loop from the top.
 *  - In this हाल we really did just take the bio of the top of the list (no
 *    pretending) and so हटाओ it from bio_list, and call पूर्णांकo ->submit_bio()
 *    again.
 *
 * bio_list_on_stack[0] contains bios submitted by the current ->submit_bio.
 * bio_list_on_stack[1] contains bios that were submitted beक्रमe the current
 *	->submit_bio_bio, but that haven't been processed yet.
 */
अटल blk_qc_t __submit_bio_noacct(काष्ठा bio *bio)
अणु
	काष्ठा bio_list bio_list_on_stack[2];
	blk_qc_t ret = BLK_QC_T_NONE;

	BUG_ON(bio->bi_next);

	bio_list_init(&bio_list_on_stack[0]);
	current->bio_list = bio_list_on_stack;

	करो अणु
		काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
		काष्ठा bio_list lower, same;

		अगर (unlikely(bio_queue_enter(bio) != 0))
			जारी;

		/*
		 * Create a fresh bio_list क्रम all subordinate requests.
		 */
		bio_list_on_stack[1] = bio_list_on_stack[0];
		bio_list_init(&bio_list_on_stack[0]);

		ret = __submit_bio(bio);

		/*
		 * Sort new bios पूर्णांकo those क्रम a lower level and those क्रम the
		 * same level.
		 */
		bio_list_init(&lower);
		bio_list_init(&same);
		जबतक ((bio = bio_list_pop(&bio_list_on_stack[0])) != शून्य)
			अगर (q == bio->bi_bdev->bd_disk->queue)
				bio_list_add(&same, bio);
			अन्यथा
				bio_list_add(&lower, bio);

		/*
		 * Now assemble so we handle the lowest level first.
		 */
		bio_list_merge(&bio_list_on_stack[0], &lower);
		bio_list_merge(&bio_list_on_stack[0], &same);
		bio_list_merge(&bio_list_on_stack[0], &bio_list_on_stack[1]);
	पूर्ण जबतक ((bio = bio_list_pop(&bio_list_on_stack[0])));

	current->bio_list = शून्य;
	वापस ret;
पूर्ण

अटल blk_qc_t __submit_bio_noacct_mq(काष्ठा bio *bio)
अणु
	काष्ठा bio_list bio_list[2] = अणु पूर्ण;
	blk_qc_t ret = BLK_QC_T_NONE;

	current->bio_list = bio_list;

	करो अणु
		काष्ठा gendisk *disk = bio->bi_bdev->bd_disk;

		अगर (unlikely(bio_queue_enter(bio) != 0))
			जारी;

		अगर (!blk_crypto_bio_prep(&bio)) अणु
			blk_queue_निकास(disk->queue);
			ret = BLK_QC_T_NONE;
			जारी;
		पूर्ण

		ret = blk_mq_submit_bio(bio);
	पूर्ण जबतक ((bio = bio_list_pop(&bio_list[0])));

	current->bio_list = शून्य;
	वापस ret;
पूर्ण

/**
 * submit_bio_noacct - re-submit a bio to the block device layer क्रम I/O
 * @bio:  The bio describing the location in memory and on the device.
 *
 * This is a version of submit_bio() that shall only be used क्रम I/O that is
 * resubmitted to lower level drivers by stacking block drivers.  All file
 * प्रणालीs and other upper level users of the block layer should use
 * submit_bio() instead.
 */
blk_qc_t submit_bio_noacct(काष्ठा bio *bio)
अणु
	अगर (!submit_bio_checks(bio))
		वापस BLK_QC_T_NONE;

	/*
	 * We only want one ->submit_bio to be active at a समय, अन्यथा stack
	 * usage with stacked devices could be a problem.  Use current->bio_list
	 * to collect a list of requests submited by a ->submit_bio method जबतक
	 * it is active, and then process them after it वापसed.
	 */
	अगर (current->bio_list) अणु
		bio_list_add(&current->bio_list[0], bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (!bio->bi_bdev->bd_disk->fops->submit_bio)
		वापस __submit_bio_noacct_mq(bio);
	वापस __submit_bio_noacct(bio);
पूर्ण
EXPORT_SYMBOL(submit_bio_noacct);

/**
 * submit_bio - submit a bio to the block device layer क्रम I/O
 * @bio: The &काष्ठा bio which describes the I/O
 *
 * submit_bio() is used to submit I/O requests to block devices.  It is passed a
 * fully set up &काष्ठा bio that describes the I/O that needs to be करोne.  The
 * bio will be send to the device described by the bi_bdev field.
 *
 * The success/failure status of the request, aदीर्घ with notअगरication of
 * completion, is delivered asynchronously through the ->bi_end_io() callback
 * in @bio.  The bio must NOT be touched by thecaller until ->bi_end_io() has
 * been called.
 */
blk_qc_t submit_bio(काष्ठा bio *bio)
अणु
	अगर (blkcg_punt_bio_submit(bio))
		वापस BLK_QC_T_NONE;

	/*
	 * If it's a regular पढ़ो/ग_लिखो or a barrier with data attached,
	 * go through the normal accounting stuff beक्रमe submission.
	 */
	अगर (bio_has_data(bio)) अणु
		अचिन्हित पूर्णांक count;

		अगर (unlikely(bio_op(bio) == REQ_OP_WRITE_SAME))
			count = queue_logical_block_size(
					bio->bi_bdev->bd_disk->queue) >> 9;
		अन्यथा
			count = bio_sectors(bio);

		अगर (op_is_ग_लिखो(bio_op(bio))) अणु
			count_vm_events(PGPGOUT, count);
		पूर्ण अन्यथा अणु
			task_io_account_पढ़ो(bio->bi_iter.bi_size);
			count_vm_events(PGPGIN, count);
		पूर्ण

		अगर (unlikely(block_dump)) अणु
			अक्षर b[BDEVNAME_SIZE];
			prपूर्णांकk(KERN_DEBUG "%s(%d): %s block %Lu on %s (%u sectors)\n",
			current->comm, task_pid_nr(current),
				op_is_ग_लिखो(bio_op(bio)) ? "WRITE" : "READ",
				(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
				bio_devname(bio, b), count);
		पूर्ण
	पूर्ण

	/*
	 * If we're पढ़ोing data that is part of the userspace workingset, count
	 * submission समय as memory stall.  When the device is congested, or
	 * the submitting cgroup IO-throttled, submission can be a signअगरicant
	 * part of overall IO समय.
	 */
	अगर (unlikely(bio_op(bio) == REQ_OP_READ &&
	    bio_flagged(bio, BIO_WORKINGSET))) अणु
		अचिन्हित दीर्घ pflags;
		blk_qc_t ret;

		psi_memstall_enter(&pflags);
		ret = submit_bio_noacct(bio);
		psi_memstall_leave(&pflags);

		वापस ret;
	पूर्ण

	वापस submit_bio_noacct(bio);
पूर्ण
EXPORT_SYMBOL(submit_bio);

/**
 * blk_cloned_rq_check_limits - Helper function to check a cloned request
 *                              क्रम the new queue limits
 * @q:  the queue
 * @rq: the request being checked
 *
 * Description:
 *    @rq may have been made based on weaker limitations of upper-level queues
 *    in request stacking drivers, and it may violate the limitation of @q.
 *    Since the block layer and the underlying device driver trust @rq
 *    after it is inserted to @q, it should be checked against @q beक्रमe
 *    the insertion using this generic function.
 *
 *    Request stacking drivers like request-based dm may change the queue
 *    limits when retrying requests on other queues. Those requests need
 *    to be checked against the new queue limits again during dispatch.
 */
अटल blk_status_t blk_cloned_rq_check_limits(काष्ठा request_queue *q,
				      काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक max_sectors = blk_queue_get_max_sectors(q, req_op(rq));

	अगर (blk_rq_sectors(rq) > max_sectors) अणु
		/*
		 * SCSI device करोes not have a good way to वापस अगर
		 * Write Same/Zero is actually supported. If a device rejects
		 * a non-पढ़ो/ग_लिखो command (discard, ग_लिखो same,etc.) the
		 * low-level device driver will set the relevant queue limit to
		 * 0 to prevent blk-lib from issuing more of the offending
		 * operations. Commands queued prior to the queue limit being
		 * reset need to be completed with BLK_STS_NOTSUPP to aव्योम I/O
		 * errors being propagated to upper layers.
		 */
		अगर (max_sectors == 0)
			वापस BLK_STS_NOTSUPP;

		prपूर्णांकk(KERN_ERR "%s: over max size limit. (%u > %u)\n",
			__func__, blk_rq_sectors(rq), max_sectors);
		वापस BLK_STS_IOERR;
	पूर्ण

	/*
	 * The queue settings related to segment counting may dअगरfer from the
	 * original queue.
	 */
	rq->nr_phys_segments = blk_recalc_rq_segments(rq);
	अगर (rq->nr_phys_segments > queue_max_segments(q)) अणु
		prपूर्णांकk(KERN_ERR "%s: over max segments limit. (%hu > %hu)\n",
			__func__, rq->nr_phys_segments, queue_max_segments(q));
		वापस BLK_STS_IOERR;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

/**
 * blk_insert_cloned_request - Helper क्रम stacking drivers to submit a request
 * @q:  the queue to submit the request
 * @rq: the request being queued
 */
blk_status_t blk_insert_cloned_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	blk_status_t ret;

	ret = blk_cloned_rq_check_limits(q, rq);
	अगर (ret != BLK_STS_OK)
		वापस ret;

	अगर (rq->rq_disk &&
	    should_fail_request(rq->rq_disk->part0, blk_rq_bytes(rq)))
		वापस BLK_STS_IOERR;

	अगर (blk_crypto_insert_cloned_request(rq))
		वापस BLK_STS_IOERR;

	अगर (blk_queue_io_stat(q))
		blk_account_io_start(rq);

	/*
	 * Since we have a scheduler attached on the top device,
	 * bypass a potential scheduler on the bottom device क्रम
	 * insert.
	 */
	वापस blk_mq_request_issue_directly(rq, true);
पूर्ण
EXPORT_SYMBOL_GPL(blk_insert_cloned_request);

/**
 * blk_rq_err_bytes - determine number of bytes till the next failure boundary
 * @rq: request to examine
 *
 * Description:
 *     A request could be merge of IOs which require dअगरferent failure
 *     handling.  This function determines the number of bytes which
 *     can be failed from the beginning of the request without
 *     crossing पूर्णांकo area which need to be retried further.
 *
 * Return:
 *     The number of bytes to fail.
 */
अचिन्हित पूर्णांक blk_rq_err_bytes(स्थिर काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक ff = rq->cmd_flags & REQ_FAILFAST_MASK;
	अचिन्हित पूर्णांक bytes = 0;
	काष्ठा bio *bio;

	अगर (!(rq->rq_flags & RQF_MIXED_MERGE))
		वापस blk_rq_bytes(rq);

	/*
	 * Currently the only 'mixing' which can happen is between
	 * dअगरferent fastfail types.  We can safely fail portions
	 * which have all the failfast bits that the first one has -
	 * the ones which are at least as eager to fail as the first
	 * one.
	 */
	क्रम (bio = rq->bio; bio; bio = bio->bi_next) अणु
		अगर ((bio->bi_opf & ff) != ff)
			अवरोध;
		bytes += bio->bi_iter.bi_size;
	पूर्ण

	/* this could lead to infinite loop */
	BUG_ON(blk_rq_bytes(rq) && !bytes);
	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(blk_rq_err_bytes);

अटल व्योम update_io_ticks(काष्ठा block_device *part, अचिन्हित दीर्घ now,
		bool end)
अणु
	अचिन्हित दीर्घ stamp;
again:
	stamp = READ_ONCE(part->bd_stamp);
	अगर (unlikely(stamp != now)) अणु
		अगर (likely(cmpxchg(&part->bd_stamp, stamp, now) == stamp))
			__part_stat_add(part, io_ticks, end ? now - stamp : 1);
	पूर्ण
	अगर (part->bd_partno) अणु
		part = bdev_whole(part);
		जाओ again;
	पूर्ण
पूर्ण

अटल व्योम blk_account_io_completion(काष्ठा request *req, अचिन्हित पूर्णांक bytes)
अणु
	अगर (req->part && blk_करो_io_stat(req)) अणु
		स्थिर पूर्णांक sgrp = op_stat_group(req_op(req));

		part_stat_lock();
		part_stat_add(req->part, sectors[sgrp], bytes >> 9);
		part_stat_unlock();
	पूर्ण
पूर्ण

व्योम blk_account_io_करोne(काष्ठा request *req, u64 now)
अणु
	/*
	 * Account IO completion.  flush_rq isn't accounted as a
	 * normal IO on queueing nor completion.  Accounting the
	 * containing request is enough.
	 */
	अगर (req->part && blk_करो_io_stat(req) &&
	    !(req->rq_flags & RQF_FLUSH_SEQ)) अणु
		स्थिर पूर्णांक sgrp = op_stat_group(req_op(req));

		part_stat_lock();
		update_io_ticks(req->part, jअगरfies, true);
		part_stat_inc(req->part, ios[sgrp]);
		part_stat_add(req->part, nsecs[sgrp], now - req->start_समय_ns);
		part_stat_unlock();
	पूर्ण
पूर्ण

व्योम blk_account_io_start(काष्ठा request *rq)
अणु
	अगर (!blk_करो_io_stat(rq))
		वापस;

	/* passthrough requests can hold bios that करो not have ->bi_bdev set */
	अगर (rq->bio && rq->bio->bi_bdev)
		rq->part = rq->bio->bi_bdev;
	अन्यथा
		rq->part = rq->rq_disk->part0;

	part_stat_lock();
	update_io_ticks(rq->part, jअगरfies, false);
	part_stat_unlock();
पूर्ण

अटल अचिन्हित दीर्घ __part_start_io_acct(काष्ठा block_device *part,
					  अचिन्हित पूर्णांक sectors, अचिन्हित पूर्णांक op)
अणु
	स्थिर पूर्णांक sgrp = op_stat_group(op);
	अचिन्हित दीर्घ now = READ_ONCE(jअगरfies);

	part_stat_lock();
	update_io_ticks(part, now, false);
	part_stat_inc(part, ios[sgrp]);
	part_stat_add(part, sectors[sgrp], sectors);
	part_stat_local_inc(part, in_flight[op_is_ग_लिखो(op)]);
	part_stat_unlock();

	वापस now;
पूर्ण

/**
 * bio_start_io_acct - start I/O accounting क्रम bio based drivers
 * @bio:	bio to start account क्रम
 *
 * Returns the start समय that should be passed back to bio_end_io_acct().
 */
अचिन्हित दीर्घ bio_start_io_acct(काष्ठा bio *bio)
अणु
	वापस __part_start_io_acct(bio->bi_bdev, bio_sectors(bio), bio_op(bio));
पूर्ण
EXPORT_SYMBOL_GPL(bio_start_io_acct);

अचिन्हित दीर्घ disk_start_io_acct(काष्ठा gendisk *disk, अचिन्हित पूर्णांक sectors,
				 अचिन्हित पूर्णांक op)
अणु
	वापस __part_start_io_acct(disk->part0, sectors, op);
पूर्ण
EXPORT_SYMBOL(disk_start_io_acct);

अटल व्योम __part_end_io_acct(काष्ठा block_device *part, अचिन्हित पूर्णांक op,
			       अचिन्हित दीर्घ start_समय)
अणु
	स्थिर पूर्णांक sgrp = op_stat_group(op);
	अचिन्हित दीर्घ now = READ_ONCE(jअगरfies);
	अचिन्हित दीर्घ duration = now - start_समय;

	part_stat_lock();
	update_io_ticks(part, now, true);
	part_stat_add(part, nsecs[sgrp], jअगरfies_to_nsecs(duration));
	part_stat_local_dec(part, in_flight[op_is_ग_लिखो(op)]);
	part_stat_unlock();
पूर्ण

व्योम bio_end_io_acct_remapped(काष्ठा bio *bio, अचिन्हित दीर्घ start_समय,
		काष्ठा block_device *orig_bdev)
अणु
	__part_end_io_acct(orig_bdev, bio_op(bio), start_समय);
पूर्ण
EXPORT_SYMBOL_GPL(bio_end_io_acct_remapped);

व्योम disk_end_io_acct(काष्ठा gendisk *disk, अचिन्हित पूर्णांक op,
		      अचिन्हित दीर्घ start_समय)
अणु
	__part_end_io_acct(disk->part0, op, start_समय);
पूर्ण
EXPORT_SYMBOL(disk_end_io_acct);

/*
 * Steal bios from a request and add them to a bio list.
 * The request must not have been partially completed beक्रमe.
 */
व्योम blk_steal_bios(काष्ठा bio_list *list, काष्ठा request *rq)
अणु
	अगर (rq->bio) अणु
		अगर (list->tail)
			list->tail->bi_next = rq->bio;
		अन्यथा
			list->head = rq->bio;
		list->tail = rq->biotail;

		rq->bio = शून्य;
		rq->biotail = शून्य;
	पूर्ण

	rq->__data_len = 0;
पूर्ण
EXPORT_SYMBOL_GPL(blk_steal_bios);

/**
 * blk_update_request - Special helper function क्रम request stacking drivers
 * @req:      the request being processed
 * @error:    block status code
 * @nr_bytes: number of bytes to complete @req
 *
 * Description:
 *     Ends I/O on a number of bytes attached to @req, but करोesn't complete
 *     the request काष्ठाure even अगर @req करोesn't have leftover.
 *     If @req has leftover, sets it up क्रम the next range of segments.
 *
 *     This special helper function is only क्रम request stacking drivers
 *     (e.g. request-based dm) so that they can handle partial completion.
 *     Actual device drivers should use blk_mq_end_request instead.
 *
 *     Passing the result of blk_rq_bytes() as @nr_bytes guarantees
 *     %false वापस from this function.
 *
 * Note:
 *	The RQF_SPECIAL_PAYLOAD flag is ignored on purpose in both
 *	blk_rq_bytes() and in blk_update_request().
 *
 * Return:
 *     %false - this request करोesn't have any more data
 *     %true  - this request has more data
 **/
bool blk_update_request(काष्ठा request *req, blk_status_t error,
		अचिन्हित पूर्णांक nr_bytes)
अणु
	पूर्णांक total_bytes;

	trace_block_rq_complete(req, blk_status_to_त्रुटि_सं(error), nr_bytes);

	अगर (!req->bio)
		वापस false;

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
	अगर (blk_पूर्णांकegrity_rq(req) && req_op(req) == REQ_OP_READ &&
	    error == BLK_STS_OK)
		req->q->पूर्णांकegrity.profile->complete_fn(req, nr_bytes);
#पूर्ण_अगर

	अगर (unlikely(error && !blk_rq_is_passthrough(req) &&
		     !(req->rq_flags & RQF_QUIET)))
		prपूर्णांक_req_error(req, error, __func__);

	blk_account_io_completion(req, nr_bytes);

	total_bytes = 0;
	जबतक (req->bio) अणु
		काष्ठा bio *bio = req->bio;
		अचिन्हित bio_bytes = min(bio->bi_iter.bi_size, nr_bytes);

		अगर (bio_bytes == bio->bi_iter.bi_size)
			req->bio = bio->bi_next;

		/* Completion has alपढ़ोy been traced */
		bio_clear_flag(bio, BIO_TRACE_COMPLETION);
		req_bio_endio(req, bio, bio_bytes, error);

		total_bytes += bio_bytes;
		nr_bytes -= bio_bytes;

		अगर (!nr_bytes)
			अवरोध;
	पूर्ण

	/*
	 * completely करोne
	 */
	अगर (!req->bio) अणु
		/*
		 * Reset counters so that the request stacking driver
		 * can find how many bytes reमुख्य in the request
		 * later.
		 */
		req->__data_len = 0;
		वापस false;
	पूर्ण

	req->__data_len -= total_bytes;

	/* update sector only क्रम requests with clear definition of sector */
	अगर (!blk_rq_is_passthrough(req))
		req->__sector += total_bytes >> 9;

	/* mixed attributes always follow the first bio */
	अगर (req->rq_flags & RQF_MIXED_MERGE) अणु
		req->cmd_flags &= ~REQ_FAILFAST_MASK;
		req->cmd_flags |= req->bio->bi_opf & REQ_FAILFAST_MASK;
	पूर्ण

	अगर (!(req->rq_flags & RQF_SPECIAL_PAYLOAD)) अणु
		/*
		 * If total number of sectors is less than the first segment
		 * size, something has gone terribly wrong.
		 */
		अगर (blk_rq_bytes(req) < blk_rq_cur_bytes(req)) अणु
			blk_dump_rq_flags(req, "request botched");
			req->__data_len = blk_rq_cur_bytes(req);
		पूर्ण

		/* recalculate the number of segments */
		req->nr_phys_segments = blk_recalc_rq_segments(req);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(blk_update_request);

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
/**
 * rq_flush_dcache_pages - Helper function to flush all pages in a request
 * @rq: the request to be flushed
 *
 * Description:
 *     Flush all pages in @rq.
 */
व्योम rq_flush_dcache_pages(काष्ठा request *rq)
अणु
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bvec;

	rq_क्रम_each_segment(bvec, rq, iter)
		flush_dcache_page(bvec.bv_page);
पूर्ण
EXPORT_SYMBOL_GPL(rq_flush_dcache_pages);
#पूर्ण_अगर

/**
 * blk_lld_busy - Check अगर underlying low-level drivers of a device are busy
 * @q : the queue of the device being checked
 *
 * Description:
 *    Check अगर underlying low-level drivers of a device are busy.
 *    If the drivers want to export their busy state, they must set own
 *    exporting function using blk_queue_lld_busy() first.
 *
 *    Basically, this function is used only by request stacking drivers
 *    to stop dispatching requests to underlying devices when underlying
 *    devices are busy.  This behavior helps more I/O merging on the queue
 *    of the request stacking driver and prevents I/O throughput regression
 *    on burst I/O load.
 *
 * Return:
 *    0 - Not busy (The request stacking driver should dispatch request)
 *    1 - Busy (The request stacking driver should stop dispatching request)
 */
पूर्णांक blk_lld_busy(काष्ठा request_queue *q)
अणु
	अगर (queue_is_mq(q) && q->mq_ops->busy)
		वापस q->mq_ops->busy(q);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(blk_lld_busy);

/**
 * blk_rq_unprep_clone - Helper function to मुक्त all bios in a cloned request
 * @rq: the clone request to be cleaned up
 *
 * Description:
 *     Free all bios in @rq क्रम a cloned request.
 */
व्योम blk_rq_unprep_clone(काष्ठा request *rq)
अणु
	काष्ठा bio *bio;

	जबतक ((bio = rq->bio) != शून्य) अणु
		rq->bio = bio->bi_next;

		bio_put(bio);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_rq_unprep_clone);

/**
 * blk_rq_prep_clone - Helper function to setup clone request
 * @rq: the request to be setup
 * @rq_src: original request to be cloned
 * @bs: bio_set that bios क्रम clone are allocated from
 * @gfp_mask: memory allocation mask क्रम bio
 * @bio_ctr: setup function to be called क्रम each clone bio.
 *           Returns %0 क्रम success, non %0 क्रम failure.
 * @data: निजी data to be passed to @bio_ctr
 *
 * Description:
 *     Clones bios in @rq_src to @rq, and copies attributes of @rq_src to @rq.
 *     Also, pages which the original bios are poपूर्णांकing to are not copied
 *     and the cloned bios just poपूर्णांक same pages.
 *     So cloned bios must be completed beक्रमe original bios, which means
 *     the caller must complete @rq beक्रमe @rq_src.
 */
पूर्णांक blk_rq_prep_clone(काष्ठा request *rq, काष्ठा request *rq_src,
		      काष्ठा bio_set *bs, gfp_t gfp_mask,
		      पूर्णांक (*bio_ctr)(काष्ठा bio *, काष्ठा bio *, व्योम *),
		      व्योम *data)
अणु
	काष्ठा bio *bio, *bio_src;

	अगर (!bs)
		bs = &fs_bio_set;

	__rq_क्रम_each_bio(bio_src, rq_src) अणु
		bio = bio_clone_fast(bio_src, gfp_mask, bs);
		अगर (!bio)
			जाओ मुक्त_and_out;

		अगर (bio_ctr && bio_ctr(bio, bio_src, data))
			जाओ मुक्त_and_out;

		अगर (rq->bio) अणु
			rq->biotail->bi_next = bio;
			rq->biotail = bio;
		पूर्ण अन्यथा अणु
			rq->bio = rq->biotail = bio;
		पूर्ण
		bio = शून्य;
	पूर्ण

	/* Copy attributes of the original request to the clone request. */
	rq->__sector = blk_rq_pos(rq_src);
	rq->__data_len = blk_rq_bytes(rq_src);
	अगर (rq_src->rq_flags & RQF_SPECIAL_PAYLOAD) अणु
		rq->rq_flags |= RQF_SPECIAL_PAYLOAD;
		rq->special_vec = rq_src->special_vec;
	पूर्ण
	rq->nr_phys_segments = rq_src->nr_phys_segments;
	rq->ioprio = rq_src->ioprio;

	अगर (rq->bio && blk_crypto_rq_bio_prep(rq, rq->bio, gfp_mask) < 0)
		जाओ मुक्त_and_out;

	वापस 0;

मुक्त_and_out:
	अगर (bio)
		bio_put(bio);
	blk_rq_unprep_clone(rq);

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(blk_rq_prep_clone);

पूर्णांक kblockd_schedule_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(kblockd_workqueue, work);
पूर्ण
EXPORT_SYMBOL(kblockd_schedule_work);

पूर्णांक kblockd_mod_delayed_work_on(पूर्णांक cpu, काष्ठा delayed_work *dwork,
				अचिन्हित दीर्घ delay)
अणु
	वापस mod_delayed_work_on(cpu, kblockd_workqueue, dwork, delay);
पूर्ण
EXPORT_SYMBOL(kblockd_mod_delayed_work_on);

/**
 * blk_start_plug - initialize blk_plug and track it inside the task_काष्ठा
 * @plug:	The &काष्ठा blk_plug that needs to be initialized
 *
 * Description:
 *   blk_start_plug() indicates to the block layer an पूर्णांकent by the caller
 *   to submit multiple I/O requests in a batch.  The block layer may use
 *   this hपूर्णांक to defer submitting I/Os from the caller until blk_finish_plug()
 *   is called.  However, the block layer may choose to submit requests
 *   beक्रमe a call to blk_finish_plug() अगर the number of queued I/Os
 *   exceeds %BLK_MAX_REQUEST_COUNT, or अगर the size of the I/O is larger than
 *   %BLK_PLUG_FLUSH_SIZE.  The queued I/Os may also be submitted early अगर
 *   the task schedules (see below).
 *
 *   Tracking blk_plug inside the task_काष्ठा will help with स्वतः-flushing the
 *   pending I/O should the task end up blocking between blk_start_plug() and
 *   blk_finish_plug(). This is important from a perक्रमmance perspective, but
 *   also ensures that we करोn't deadlock. For instance, अगर the task is blocking
 *   क्रम a memory allocation, memory reclaim could end up wanting to मुक्त a
 *   page beदीर्घing to that request that is currently residing in our निजी
 *   plug. By flushing the pending I/O when the process goes to sleep, we aव्योम
 *   this kind of deadlock.
 */
व्योम blk_start_plug(काष्ठा blk_plug *plug)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	/*
	 * If this is a nested plug, करोn't actually assign it.
	 */
	अगर (tsk->plug)
		वापस;

	INIT_LIST_HEAD(&plug->mq_list);
	INIT_LIST_HEAD(&plug->cb_list);
	plug->rq_count = 0;
	plug->multiple_queues = false;
	plug->noरुको = false;

	/*
	 * Store ordering should not be needed here, since a potential
	 * preempt will imply a full memory barrier
	 */
	tsk->plug = plug;
पूर्ण
EXPORT_SYMBOL(blk_start_plug);

अटल व्योम flush_plug_callbacks(काष्ठा blk_plug *plug, bool from_schedule)
अणु
	LIST_HEAD(callbacks);

	जबतक (!list_empty(&plug->cb_list)) अणु
		list_splice_init(&plug->cb_list, &callbacks);

		जबतक (!list_empty(&callbacks)) अणु
			काष्ठा blk_plug_cb *cb = list_first_entry(&callbacks,
							  काष्ठा blk_plug_cb,
							  list);
			list_del(&cb->list);
			cb->callback(cb, from_schedule);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा blk_plug_cb *blk_check_plugged(blk_plug_cb_fn unplug, व्योम *data,
				      पूर्णांक size)
अणु
	काष्ठा blk_plug *plug = current->plug;
	काष्ठा blk_plug_cb *cb;

	अगर (!plug)
		वापस शून्य;

	list_क्रम_each_entry(cb, &plug->cb_list, list)
		अगर (cb->callback == unplug && cb->data == data)
			वापस cb;

	/* Not currently on the callback list */
	BUG_ON(size < माप(*cb));
	cb = kzalloc(size, GFP_ATOMIC);
	अगर (cb) अणु
		cb->data = data;
		cb->callback = unplug;
		list_add(&cb->list, &plug->cb_list);
	पूर्ण
	वापस cb;
पूर्ण
EXPORT_SYMBOL(blk_check_plugged);

व्योम blk_flush_plug_list(काष्ठा blk_plug *plug, bool from_schedule)
अणु
	flush_plug_callbacks(plug, from_schedule);

	अगर (!list_empty(&plug->mq_list))
		blk_mq_flush_plug_list(plug, from_schedule);
पूर्ण

/**
 * blk_finish_plug - mark the end of a batch of submitted I/O
 * @plug:	The &काष्ठा blk_plug passed to blk_start_plug()
 *
 * Description:
 * Indicate that a batch of I/O submissions is complete.  This function
 * must be paired with an initial call to blk_start_plug().  The पूर्णांकent
 * is to allow the block layer to optimize I/O submission.  See the
 * करोcumentation क्रम blk_start_plug() क्रम more inक्रमmation.
 */
व्योम blk_finish_plug(काष्ठा blk_plug *plug)
अणु
	अगर (plug != current->plug)
		वापस;
	blk_flush_plug_list(plug, false);

	current->plug = शून्य;
पूर्ण
EXPORT_SYMBOL(blk_finish_plug);

व्योम blk_io_schedule(व्योम)
अणु
	/* Prevent hang_check समयr from firing at us during very दीर्घ I/O */
	अचिन्हित दीर्घ समयout = sysctl_hung_task_समयout_secs * HZ / 2;

	अगर (समयout)
		io_schedule_समयout(समयout);
	अन्यथा
		io_schedule();
पूर्ण
EXPORT_SYMBOL_GPL(blk_io_schedule);

पूर्णांक __init blk_dev_init(व्योम)
अणु
	BUILD_BUG_ON(REQ_OP_LAST >= (1 << REQ_OP_BITS));
	BUILD_BUG_ON(REQ_OP_BITS + REQ_FLAG_BITS > 8 *
			माप_field(काष्ठा request, cmd_flags));
	BUILD_BUG_ON(REQ_OP_BITS + REQ_FLAG_BITS > 8 *
			माप_field(काष्ठा bio, bi_opf));

	/* used क्रम unplugging and affects IO latency/throughput - HIGHPRI */
	kblockd_workqueue = alloc_workqueue("kblockd",
					    WQ_MEM_RECLAIM | WQ_HIGHPRI, 0);
	अगर (!kblockd_workqueue)
		panic("Failed to create kblockd\n");

	blk_requestq_cachep = kmem_cache_create("request_queue",
			माप(काष्ठा request_queue), 0, SLAB_PANIC, शून्य);

	blk_debugfs_root = debugfs_create_dir("block", शून्य);

	वापस 0;
पूर्ण
