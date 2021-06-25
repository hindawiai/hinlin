<शैली गुरु>
/*
 * Copyright (C) 2016 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"
#समावेश "dm-rq.h"

#समावेश <linux/elevator.h> /* क्रम rq_end_sector() */
#समावेश <linux/blk-mq.h>

#घोषणा DM_MSG_PREFIX "core-rq"

/*
 * One of these is allocated per request.
 */
काष्ठा dm_rq_target_io अणु
	काष्ठा mapped_device *md;
	काष्ठा dm_target *ti;
	काष्ठा request *orig, *clone;
	काष्ठा kthपढ़ो_work work;
	blk_status_t error;
	जोड़ map_info info;
	काष्ठा dm_stats_aux stats_aux;
	अचिन्हित दीर्घ duration_jअगरfies;
	अचिन्हित n_sectors;
	अचिन्हित completed;
पूर्ण;

#घोषणा DM_MQ_NR_HW_QUEUES 1
#घोषणा DM_MQ_QUEUE_DEPTH 2048
अटल अचिन्हित dm_mq_nr_hw_queues = DM_MQ_NR_HW_QUEUES;
अटल अचिन्हित dm_mq_queue_depth = DM_MQ_QUEUE_DEPTH;

/*
 * Request-based DM's mempools' reserved IOs set by the user.
 */
#घोषणा RESERVED_REQUEST_BASED_IOS	256
अटल अचिन्हित reserved_rq_based_ios = RESERVED_REQUEST_BASED_IOS;

अचिन्हित dm_get_reserved_rq_based_ios(व्योम)
अणु
	वापस __dm_get_module_param(&reserved_rq_based_ios,
				     RESERVED_REQUEST_BASED_IOS, DM_RESERVED_MAX_IOS);
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_reserved_rq_based_ios);

अटल अचिन्हित dm_get_blk_mq_nr_hw_queues(व्योम)
अणु
	वापस __dm_get_module_param(&dm_mq_nr_hw_queues, 1, 32);
पूर्ण

अटल अचिन्हित dm_get_blk_mq_queue_depth(व्योम)
अणु
	वापस __dm_get_module_param(&dm_mq_queue_depth,
				     DM_MQ_QUEUE_DEPTH, BLK_MQ_MAX_DEPTH);
पूर्ण

पूर्णांक dm_request_based(काष्ठा mapped_device *md)
अणु
	वापस queue_is_mq(md->queue);
पूर्ण

व्योम dm_start_queue(काष्ठा request_queue *q)
अणु
	blk_mq_unquiesce_queue(q);
	blk_mq_kick_requeue_list(q);
पूर्ण

व्योम dm_stop_queue(काष्ठा request_queue *q)
अणु
	blk_mq_quiesce_queue(q);
पूर्ण

/*
 * Partial completion handling क्रम request-based dm
 */
अटल व्योम end_clone_bio(काष्ठा bio *clone)
अणु
	काष्ठा dm_rq_clone_bio_info *info =
		container_of(clone, काष्ठा dm_rq_clone_bio_info, clone);
	काष्ठा dm_rq_target_io *tio = info->tio;
	अचिन्हित पूर्णांक nr_bytes = info->orig->bi_iter.bi_size;
	blk_status_t error = clone->bi_status;
	bool is_last = !clone->bi_next;

	bio_put(clone);

	अगर (tio->error)
		/*
		 * An error has alपढ़ोy been detected on the request.
		 * Once error occurred, just let clone->end_io() handle
		 * the reमुख्यder.
		 */
		वापस;
	अन्यथा अगर (error) अणु
		/*
		 * Don't notice the error to the upper layer yet.
		 * The error handling decision is made by the target driver,
		 * when the request is completed.
		 */
		tio->error = error;
		जाओ निकास;
	पूर्ण

	/*
	 * I/O क्रम the bio successfully completed.
	 * Notice the data completion to the upper layer.
	 */
	tio->completed += nr_bytes;

	/*
	 * Update the original request.
	 * Do not use blk_mq_end_request() here, because it may complete
	 * the original request beक्रमe the clone, and अवरोध the ordering.
	 */
	अगर (is_last)
 निकास:
		blk_update_request(tio->orig, BLK_STS_OK, tio->completed);
पूर्ण

अटल काष्ठा dm_rq_target_io *tio_from_request(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_to_pdu(rq);
पूर्ण

अटल व्योम rq_end_stats(काष्ठा mapped_device *md, काष्ठा request *orig)
अणु
	अगर (unlikely(dm_stats_used(&md->stats))) अणु
		काष्ठा dm_rq_target_io *tio = tio_from_request(orig);
		tio->duration_jअगरfies = jअगरfies - tio->duration_jअगरfies;
		dm_stats_account_io(&md->stats, rq_data_dir(orig),
				    blk_rq_pos(orig), tio->n_sectors, true,
				    tio->duration_jअगरfies, &tio->stats_aux);
	पूर्ण
पूर्ण

/*
 * Don't touch any member of the md after calling this function because
 * the md may be मुक्तd in dm_put() at the end of this function.
 * Or करो dm_get() beक्रमe calling this function and dm_put() later.
 */
अटल व्योम rq_completed(काष्ठा mapped_device *md)
अणु
	/*
	 * dm_put() must be at the end of this function. See the comment above
	 */
	dm_put(md);
पूर्ण

/*
 * Complete the clone and the original request.
 * Must be called without clone's queue lock held,
 * see end_clone_request() क्रम more details.
 */
अटल व्योम dm_end_request(काष्ठा request *clone, blk_status_t error)
अणु
	काष्ठा dm_rq_target_io *tio = clone->end_io_data;
	काष्ठा mapped_device *md = tio->md;
	काष्ठा request *rq = tio->orig;

	blk_rq_unprep_clone(clone);
	tio->ti->type->release_clone_rq(clone, शून्य);

	rq_end_stats(md, rq);
	blk_mq_end_request(rq, error);
	rq_completed(md);
पूर्ण

अटल व्योम __dm_mq_kick_requeue_list(काष्ठा request_queue *q, अचिन्हित दीर्घ msecs)
अणु
	blk_mq_delay_kick_requeue_list(q, msecs);
पूर्ण

व्योम dm_mq_kick_requeue_list(काष्ठा mapped_device *md)
अणु
	__dm_mq_kick_requeue_list(md->queue, 0);
पूर्ण
EXPORT_SYMBOL(dm_mq_kick_requeue_list);

अटल व्योम dm_mq_delay_requeue_request(काष्ठा request *rq, अचिन्हित दीर्घ msecs)
अणु
	blk_mq_requeue_request(rq, false);
	__dm_mq_kick_requeue_list(rq->q, msecs);
पूर्ण

अटल व्योम dm_requeue_original_request(काष्ठा dm_rq_target_io *tio, bool delay_requeue)
अणु
	काष्ठा mapped_device *md = tio->md;
	काष्ठा request *rq = tio->orig;
	अचिन्हित दीर्घ delay_ms = delay_requeue ? 100 : 0;

	rq_end_stats(md, rq);
	अगर (tio->clone) अणु
		blk_rq_unprep_clone(tio->clone);
		tio->ti->type->release_clone_rq(tio->clone, शून्य);
	पूर्ण

	dm_mq_delay_requeue_request(rq, delay_ms);
	rq_completed(md);
पूर्ण

अटल व्योम dm_करोne(काष्ठा request *clone, blk_status_t error, bool mapped)
अणु
	पूर्णांक r = DM_ENDIO_DONE;
	काष्ठा dm_rq_target_io *tio = clone->end_io_data;
	dm_request_endio_fn rq_end_io = शून्य;

	अगर (tio->ti) अणु
		rq_end_io = tio->ti->type->rq_end_io;

		अगर (mapped && rq_end_io)
			r = rq_end_io(tio->ti, clone, error, &tio->info);
	पूर्ण

	अगर (unlikely(error == BLK_STS_TARGET)) अणु
		अगर (req_op(clone) == REQ_OP_DISCARD &&
		    !clone->q->limits.max_discard_sectors)
			disable_discard(tio->md);
		अन्यथा अगर (req_op(clone) == REQ_OP_WRITE_SAME &&
			 !clone->q->limits.max_ग_लिखो_same_sectors)
			disable_ग_लिखो_same(tio->md);
		अन्यथा अगर (req_op(clone) == REQ_OP_WRITE_ZEROES &&
			 !clone->q->limits.max_ग_लिखो_zeroes_sectors)
			disable_ग_लिखो_zeroes(tio->md);
	पूर्ण

	चयन (r) अणु
	हाल DM_ENDIO_DONE:
		/* The target wants to complete the I/O */
		dm_end_request(clone, error);
		अवरोध;
	हाल DM_ENDIO_INCOMPLETE:
		/* The target will handle the I/O */
		वापस;
	हाल DM_ENDIO_REQUEUE:
		/* The target wants to requeue the I/O */
		dm_requeue_original_request(tio, false);
		अवरोध;
	हाल DM_ENDIO_DELAY_REQUEUE:
		/* The target wants to requeue the I/O after a delay */
		dm_requeue_original_request(tio, true);
		अवरोध;
	शेष:
		DMWARN("unimplemented target endio return value: %d", r);
		BUG();
	पूर्ण
पूर्ण

/*
 * Request completion handler क्रम request-based dm
 */
अटल व्योम dm_softirq_करोne(काष्ठा request *rq)
अणु
	bool mapped = true;
	काष्ठा dm_rq_target_io *tio = tio_from_request(rq);
	काष्ठा request *clone = tio->clone;

	अगर (!clone) अणु
		काष्ठा mapped_device *md = tio->md;

		rq_end_stats(md, rq);
		blk_mq_end_request(rq, tio->error);
		rq_completed(md);
		वापस;
	पूर्ण

	अगर (rq->rq_flags & RQF_FAILED)
		mapped = false;

	dm_करोne(clone, tio->error, mapped);
पूर्ण

/*
 * Complete the clone and the original request with the error status
 * through softirq context.
 */
अटल व्योम dm_complete_request(काष्ठा request *rq, blk_status_t error)
अणु
	काष्ठा dm_rq_target_io *tio = tio_from_request(rq);

	tio->error = error;
	अगर (likely(!blk_should_fake_समयout(rq->q)))
		blk_mq_complete_request(rq);
पूर्ण

/*
 * Complete the not-mapped clone and the original request with the error status
 * through softirq context.
 * Target's rq_end_io() function isn't called.
 * This may be used when the target's clone_and_map_rq() function fails.
 */
अटल व्योम dm_समाप्त_unmapped_request(काष्ठा request *rq, blk_status_t error)
अणु
	rq->rq_flags |= RQF_FAILED;
	dm_complete_request(rq, error);
पूर्ण

अटल व्योम end_clone_request(काष्ठा request *clone, blk_status_t error)
अणु
	काष्ठा dm_rq_target_io *tio = clone->end_io_data;

	dm_complete_request(tio->orig, error);
पूर्ण

अटल blk_status_t dm_dispatch_clone_request(काष्ठा request *clone, काष्ठा request *rq)
अणु
	blk_status_t r;

	अगर (blk_queue_io_stat(clone->q))
		clone->rq_flags |= RQF_IO_STAT;

	clone->start_समय_ns = kसमय_get_ns();
	r = blk_insert_cloned_request(clone->q, clone);
	अगर (r != BLK_STS_OK && r != BLK_STS_RESOURCE && r != BLK_STS_DEV_RESOURCE)
		/* must complete clone in terms of original request */
		dm_complete_request(rq, r);
	वापस r;
पूर्ण

अटल पूर्णांक dm_rq_bio_स्थिरructor(काष्ठा bio *bio, काष्ठा bio *bio_orig,
				 व्योम *data)
अणु
	काष्ठा dm_rq_target_io *tio = data;
	काष्ठा dm_rq_clone_bio_info *info =
		container_of(bio, काष्ठा dm_rq_clone_bio_info, clone);

	info->orig = bio_orig;
	info->tio = tio;
	bio->bi_end_io = end_clone_bio;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_clone(काष्ठा request *clone, काष्ठा request *rq,
		       काष्ठा dm_rq_target_io *tio, gfp_t gfp_mask)
अणु
	पूर्णांक r;

	r = blk_rq_prep_clone(clone, rq, &tio->md->bs, gfp_mask,
			      dm_rq_bio_स्थिरructor, tio);
	अगर (r)
		वापस r;

	clone->end_io = end_clone_request;
	clone->end_io_data = tio;

	tio->clone = clone;

	वापस 0;
पूर्ण

अटल व्योम init_tio(काष्ठा dm_rq_target_io *tio, काष्ठा request *rq,
		     काष्ठा mapped_device *md)
अणु
	tio->md = md;
	tio->ti = शून्य;
	tio->clone = शून्य;
	tio->orig = rq;
	tio->error = 0;
	tio->completed = 0;
	/*
	 * Aव्योम initializing info क्रम blk-mq; it passes
	 * target-specअगरic data through info.ptr
	 * (see: dm_mq_init_request)
	 */
	अगर (!md->init_tio_pdu)
		स_रखो(&tio->info, 0, माप(tio->info));
पूर्ण

/*
 * Returns:
 * DM_MAPIO_*       : the request has been processed as indicated
 * DM_MAPIO_REQUEUE : the original request needs to be immediately requeued
 * < 0              : the request was completed due to failure
 */
अटल पूर्णांक map_request(काष्ठा dm_rq_target_io *tio)
अणु
	पूर्णांक r;
	काष्ठा dm_target *ti = tio->ti;
	काष्ठा mapped_device *md = tio->md;
	काष्ठा request *rq = tio->orig;
	काष्ठा request *clone = शून्य;
	blk_status_t ret;

	r = ti->type->clone_and_map_rq(ti, rq, &tio->info, &clone);
	चयन (r) अणु
	हाल DM_MAPIO_SUBMITTED:
		/* The target has taken the I/O to submit by itself later */
		अवरोध;
	हाल DM_MAPIO_REMAPPED:
		अगर (setup_clone(clone, rq, tio, GFP_ATOMIC)) अणु
			/* -ENOMEM */
			ti->type->release_clone_rq(clone, &tio->info);
			वापस DM_MAPIO_REQUEUE;
		पूर्ण

		/* The target has remapped the I/O so dispatch it */
		trace_block_rq_remap(clone, disk_devt(dm_disk(md)),
				     blk_rq_pos(rq));
		ret = dm_dispatch_clone_request(clone, rq);
		अगर (ret == BLK_STS_RESOURCE || ret == BLK_STS_DEV_RESOURCE) अणु
			blk_rq_unprep_clone(clone);
			blk_mq_cleanup_rq(clone);
			tio->ti->type->release_clone_rq(clone, &tio->info);
			tio->clone = शून्य;
			वापस DM_MAPIO_REQUEUE;
		पूर्ण
		अवरोध;
	हाल DM_MAPIO_REQUEUE:
		/* The target wants to requeue the I/O */
		अवरोध;
	हाल DM_MAPIO_DELAY_REQUEUE:
		/* The target wants to requeue the I/O after a delay */
		dm_requeue_original_request(tio, true);
		अवरोध;
	हाल DM_MAPIO_KILL:
		/* The target wants to complete the I/O */
		dm_समाप्त_unmapped_request(rq, BLK_STS_IOERR);
		अवरोध;
	शेष:
		DMWARN("unimplemented target map return value: %d", r);
		BUG();
	पूर्ण

	वापस r;
पूर्ण

/* DEPRECATED: previously used क्रम request-based merge heuristic in dm_request_fn() */
sमाप_प्रकार dm_attr_rq_based_seq_io_merge_deadline_show(काष्ठा mapped_device *md, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", 0);
पूर्ण

sमाप_प्रकार dm_attr_rq_based_seq_io_merge_deadline_store(काष्ठा mapped_device *md,
						     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस count;
पूर्ण

अटल व्योम dm_start_request(काष्ठा mapped_device *md, काष्ठा request *orig)
अणु
	blk_mq_start_request(orig);

	अगर (unlikely(dm_stats_used(&md->stats))) अणु
		काष्ठा dm_rq_target_io *tio = tio_from_request(orig);
		tio->duration_jअगरfies = jअगरfies;
		tio->n_sectors = blk_rq_sectors(orig);
		dm_stats_account_io(&md->stats, rq_data_dir(orig),
				    blk_rq_pos(orig), tio->n_sectors, false, 0,
				    &tio->stats_aux);
	पूर्ण

	/*
	 * Hold the md reference here क्रम the in-flight I/O.
	 * We can't rely on the reference count by device खोलोer,
	 * because the device may be बंदd during the request completion
	 * when all bios are completed.
	 * See the comment in rq_completed() too.
	 */
	dm_get(md);
पूर्ण

अटल पूर्णांक dm_mq_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
			      अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा mapped_device *md = set->driver_data;
	काष्ठा dm_rq_target_io *tio = blk_mq_rq_to_pdu(rq);

	/*
	 * Must initialize md member of tio, otherwise it won't
	 * be available in dm_mq_queue_rq.
	 */
	tio->md = md;

	अगर (md->init_tio_pdu) अणु
		/* target-specअगरic per-io data is immediately after the tio */
		tio->info.ptr = tio + 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल blk_status_t dm_mq_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			  स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *rq = bd->rq;
	काष्ठा dm_rq_target_io *tio = blk_mq_rq_to_pdu(rq);
	काष्ठा mapped_device *md = tio->md;
	काष्ठा dm_target *ti = md->immutable_target;

	अगर (unlikely(!ti)) अणु
		पूर्णांक srcu_idx;
		काष्ठा dm_table *map = dm_get_live_table(md, &srcu_idx);

		ti = dm_table_find_target(map, 0);
		dm_put_live_table(md, srcu_idx);
	पूर्ण

	अगर (ti->type->busy && ti->type->busy(ti))
		वापस BLK_STS_RESOURCE;

	dm_start_request(md, rq);

	/* Init tio using md established in .init_request */
	init_tio(tio, rq, md);

	/*
	 * Establish tio->ti beक्रमe calling map_request().
	 */
	tio->ti = ti;

	/* Direct call is fine since .queue_rq allows allocations */
	अगर (map_request(tio) == DM_MAPIO_REQUEUE) अणु
		/* Unकरो dm_start_request() beक्रमe requeuing */
		rq_end_stats(md, rq);
		rq_completed(md);
		वापस BLK_STS_RESOURCE;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops dm_mq_ops = अणु
	.queue_rq = dm_mq_queue_rq,
	.complete = dm_softirq_करोne,
	.init_request = dm_mq_init_request,
पूर्ण;

पूर्णांक dm_mq_init_request_queue(काष्ठा mapped_device *md, काष्ठा dm_table *t)
अणु
	काष्ठा request_queue *q;
	काष्ठा dm_target *immutable_tgt;
	पूर्णांक err;

	md->tag_set = kzalloc_node(माप(काष्ठा blk_mq_tag_set), GFP_KERNEL, md->numa_node_id);
	अगर (!md->tag_set)
		वापस -ENOMEM;

	md->tag_set->ops = &dm_mq_ops;
	md->tag_set->queue_depth = dm_get_blk_mq_queue_depth();
	md->tag_set->numa_node = md->numa_node_id;
	md->tag_set->flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_STACKING;
	md->tag_set->nr_hw_queues = dm_get_blk_mq_nr_hw_queues();
	md->tag_set->driver_data = md;

	md->tag_set->cmd_size = माप(काष्ठा dm_rq_target_io);
	immutable_tgt = dm_table_get_immutable_target(t);
	अगर (immutable_tgt && immutable_tgt->per_io_data_size) अणु
		/* any target-specअगरic per-io data is immediately after the tio */
		md->tag_set->cmd_size += immutable_tgt->per_io_data_size;
		md->init_tio_pdu = true;
	पूर्ण

	err = blk_mq_alloc_tag_set(md->tag_set);
	अगर (err)
		जाओ out_kमुक्त_tag_set;

	q = blk_mq_init_allocated_queue(md->tag_set, md->queue, true);
	अगर (IS_ERR(q)) अणु
		err = PTR_ERR(q);
		जाओ out_tag_set;
	पूर्ण

	वापस 0;

out_tag_set:
	blk_mq_मुक्त_tag_set(md->tag_set);
out_kमुक्त_tag_set:
	kमुक्त(md->tag_set);
	md->tag_set = शून्य;

	वापस err;
पूर्ण

व्योम dm_mq_cleanup_mapped_device(काष्ठा mapped_device *md)
अणु
	अगर (md->tag_set) अणु
		blk_mq_मुक्त_tag_set(md->tag_set);
		kमुक्त(md->tag_set);
		md->tag_set = शून्य;
	पूर्ण
पूर्ण

module_param(reserved_rq_based_ios, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(reserved_rq_based_ios, "Reserved IOs in request-based mempools");

/* Unused, but preserved क्रम userspace compatibility */
अटल bool use_blk_mq = true;
module_param(use_blk_mq, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(use_blk_mq, "Use block multiqueue for request-based DM devices");

module_param(dm_mq_nr_hw_queues, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dm_mq_nr_hw_queues, "Number of hardware queues for request-based dm-mq devices");

module_param(dm_mq_queue_depth, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dm_mq_queue_depth, "Queue depth for request-based dm-mq devices");
