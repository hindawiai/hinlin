<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित INT_BLK_MQ_H
#घोषणा INT_BLK_MQ_H

#समावेश "blk-stat.h"
#समावेश "blk-mq-tag.h"

काष्ठा blk_mq_tag_set;

काष्ठा blk_mq_ctxs अणु
	काष्ठा kobject kobj;
	काष्ठा blk_mq_ctx __percpu	*queue_ctx;
पूर्ण;

/**
 * काष्ठा blk_mq_ctx - State क्रम a software queue facing the submitting CPUs
 */
काष्ठा blk_mq_ctx अणु
	काष्ठा अणु
		spinlock_t		lock;
		काष्ठा list_head	rq_lists[HCTX_MAX_TYPES];
	पूर्ण ____cacheline_aligned_in_smp;

	अचिन्हित पूर्णांक		cpu;
	अचिन्हित लघु		index_hw[HCTX_MAX_TYPES];
	काष्ठा blk_mq_hw_ctx 	*hctxs[HCTX_MAX_TYPES];

	/* incremented at dispatch समय */
	अचिन्हित दीर्घ		rq_dispatched[2];
	अचिन्हित दीर्घ		rq_merged;

	/* incremented at completion समय */
	अचिन्हित दीर्घ		____cacheline_aligned_in_smp rq_completed[2];

	काष्ठा request_queue	*queue;
	काष्ठा blk_mq_ctxs      *ctxs;
	काष्ठा kobject		kobj;
पूर्ण ____cacheline_aligned_in_smp;

व्योम blk_mq_निकास_queue(काष्ठा request_queue *q);
पूर्णांक blk_mq_update_nr_requests(काष्ठा request_queue *q, अचिन्हित पूर्णांक nr);
व्योम blk_mq_wake_रुकोers(काष्ठा request_queue *q);
bool blk_mq_dispatch_rq_list(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा list_head *,
			     अचिन्हित पूर्णांक);
व्योम blk_mq_add_to_requeue_list(काष्ठा request *rq, bool at_head,
				bool kick_requeue_list);
व्योम blk_mq_flush_busy_ctxs(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा list_head *list);
काष्ठा request *blk_mq_dequeue_from_ctx(काष्ठा blk_mq_hw_ctx *hctx,
					काष्ठा blk_mq_ctx *start);

/*
 * Internal helpers क्रम allocating/मुक्तing the request map
 */
व्योम blk_mq_मुक्त_rqs(काष्ठा blk_mq_tag_set *set, काष्ठा blk_mq_tags *tags,
		     अचिन्हित पूर्णांक hctx_idx);
व्योम blk_mq_मुक्त_rq_map(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक flags);
काष्ठा blk_mq_tags *blk_mq_alloc_rq_map(काष्ठा blk_mq_tag_set *set,
					अचिन्हित पूर्णांक hctx_idx,
					अचिन्हित पूर्णांक nr_tags,
					अचिन्हित पूर्णांक reserved_tags,
					अचिन्हित पूर्णांक flags);
पूर्णांक blk_mq_alloc_rqs(काष्ठा blk_mq_tag_set *set, काष्ठा blk_mq_tags *tags,
		     अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक depth);

/*
 * Internal helpers क्रम request insertion पूर्णांकo sw queues
 */
व्योम __blk_mq_insert_request(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा request *rq,
				bool at_head);
व्योम blk_mq_request_bypass_insert(काष्ठा request *rq, bool at_head,
				  bool run_queue);
व्योम blk_mq_insert_requests(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा blk_mq_ctx *ctx,
				काष्ठा list_head *list);

/* Used by blk_insert_cloned_request() to issue request directly */
blk_status_t blk_mq_request_issue_directly(काष्ठा request *rq, bool last);
व्योम blk_mq_try_issue_list_directly(काष्ठा blk_mq_hw_ctx *hctx,
				    काष्ठा list_head *list);

/*
 * CPU -> queue mappings
 */
बाह्य पूर्णांक blk_mq_hw_queue_to_node(काष्ठा blk_mq_queue_map *qmap, अचिन्हित पूर्णांक);

/*
 * blk_mq_map_queue_type() - map (hctx_type,cpu) to hardware queue
 * @q: request queue
 * @type: the hctx type index
 * @cpu: CPU
 */
अटल अंतरभूत काष्ठा blk_mq_hw_ctx *blk_mq_map_queue_type(काष्ठा request_queue *q,
							  क्रमागत hctx_type type,
							  अचिन्हित पूर्णांक cpu)
अणु
	वापस q->queue_hw_ctx[q->tag_set->map[type].mq_map[cpu]];
पूर्ण

/*
 * blk_mq_map_queue() - map (cmd_flags,type) to hardware queue
 * @q: request queue
 * @flags: request command flags
 * @ctx: software queue cpu ctx
 */
अटल अंतरभूत काष्ठा blk_mq_hw_ctx *blk_mq_map_queue(काष्ठा request_queue *q,
						     अचिन्हित पूर्णांक flags,
						     काष्ठा blk_mq_ctx *ctx)
अणु
	क्रमागत hctx_type type = HCTX_TYPE_DEFAULT;

	/*
	 * The caller ensure that अगर REQ_HIPRI, poll must be enabled.
	 */
	अगर (flags & REQ_HIPRI)
		type = HCTX_TYPE_POLL;
	अन्यथा अगर ((flags & REQ_OP_MASK) == REQ_OP_READ)
		type = HCTX_TYPE_READ;
	
	वापस ctx->hctxs[type];
पूर्ण

/*
 * sysfs helpers
 */
बाह्य व्योम blk_mq_sysfs_init(काष्ठा request_queue *q);
बाह्य व्योम blk_mq_sysfs_deinit(काष्ठा request_queue *q);
बाह्य पूर्णांक __blk_mq_रेजिस्टर_dev(काष्ठा device *dev, काष्ठा request_queue *q);
बाह्य पूर्णांक blk_mq_sysfs_रेजिस्टर(काष्ठा request_queue *q);
बाह्य व्योम blk_mq_sysfs_unरेजिस्टर(काष्ठा request_queue *q);
बाह्य व्योम blk_mq_hctx_kobj_init(काष्ठा blk_mq_hw_ctx *hctx);

व्योम blk_mq_release(काष्ठा request_queue *q);

अटल अंतरभूत काष्ठा blk_mq_ctx *__blk_mq_get_ctx(काष्ठा request_queue *q,
					   अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu_ptr(q->queue_ctx, cpu);
पूर्ण

/*
 * This assumes per-cpu software queueing queues. They could be per-node
 * as well, क्रम instance. For now this is hardcoded as-is. Note that we करोn't
 * care about preemption, since we know the ctx's are persistent. This करोes
 * mean that we can't rely on ctx always matching the currently running CPU.
 */
अटल अंतरभूत काष्ठा blk_mq_ctx *blk_mq_get_ctx(काष्ठा request_queue *q)
अणु
	वापस __blk_mq_get_ctx(q, raw_smp_processor_id());
पूर्ण

काष्ठा blk_mq_alloc_data अणु
	/* input parameter */
	काष्ठा request_queue *q;
	blk_mq_req_flags_t flags;
	अचिन्हित पूर्णांक shallow_depth;
	अचिन्हित पूर्णांक cmd_flags;

	/* input & output parameter */
	काष्ठा blk_mq_ctx *ctx;
	काष्ठा blk_mq_hw_ctx *hctx;
पूर्ण;

अटल अंतरभूत bool blk_mq_is_sbiपंचांगap_shared(अचिन्हित पूर्णांक flags)
अणु
	वापस flags & BLK_MQ_F_TAG_HCTX_SHARED;
पूर्ण

अटल अंतरभूत काष्ठा blk_mq_tags *blk_mq_tags_from_data(काष्ठा blk_mq_alloc_data *data)
अणु
	अगर (data->q->elevator)
		वापस data->hctx->sched_tags;

	वापस data->hctx->tags;
पूर्ण

अटल अंतरभूत bool blk_mq_hctx_stopped(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	वापस test_bit(BLK_MQ_S_STOPPED, &hctx->state);
पूर्ण

अटल अंतरभूत bool blk_mq_hw_queue_mapped(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	वापस hctx->nr_ctx && hctx->tags;
पूर्ण

अचिन्हित पूर्णांक blk_mq_in_flight(काष्ठा request_queue *q,
		काष्ठा block_device *part);
व्योम blk_mq_in_flight_rw(काष्ठा request_queue *q, काष्ठा block_device *part,
		अचिन्हित पूर्णांक inflight[2]);

अटल अंतरभूत व्योम blk_mq_put_dispatch_budget(काष्ठा request_queue *q,
					      पूर्णांक budget_token)
अणु
	अगर (q->mq_ops->put_budget)
		q->mq_ops->put_budget(q, budget_token);
पूर्ण

अटल अंतरभूत पूर्णांक blk_mq_get_dispatch_budget(काष्ठा request_queue *q)
अणु
	अगर (q->mq_ops->get_budget)
		वापस q->mq_ops->get_budget(q);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम blk_mq_set_rq_budget_token(काष्ठा request *rq, पूर्णांक token)
अणु
	अगर (token < 0)
		वापस;

	अगर (rq->q->mq_ops->set_rq_budget_token)
		rq->q->mq_ops->set_rq_budget_token(rq, token);
पूर्ण

अटल अंतरभूत पूर्णांक blk_mq_get_rq_budget_token(काष्ठा request *rq)
अणु
	अगर (rq->q->mq_ops->get_rq_budget_token)
		वापस rq->q->mq_ops->get_rq_budget_token(rq);
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम __blk_mq_inc_active_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags))
		atomic_inc(&hctx->queue->nr_active_requests_shared_sbiपंचांगap);
	अन्यथा
		atomic_inc(&hctx->nr_active);
पूर्ण

अटल अंतरभूत व्योम __blk_mq_dec_active_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags))
		atomic_dec(&hctx->queue->nr_active_requests_shared_sbiपंचांगap);
	अन्यथा
		atomic_dec(&hctx->nr_active);
पूर्ण

अटल अंतरभूत पूर्णांक __blk_mq_active_requests(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags))
		वापस atomic_पढ़ो(&hctx->queue->nr_active_requests_shared_sbiपंचांगap);
	वापस atomic_पढ़ो(&hctx->nr_active);
पूर्ण
अटल अंतरभूत व्योम __blk_mq_put_driver_tag(काष्ठा blk_mq_hw_ctx *hctx,
					   काष्ठा request *rq)
अणु
	blk_mq_put_tag(hctx->tags, rq->mq_ctx, rq->tag);
	rq->tag = BLK_MQ_NO_TAG;

	अगर (rq->rq_flags & RQF_MQ_INFLIGHT) अणु
		rq->rq_flags &= ~RQF_MQ_INFLIGHT;
		__blk_mq_dec_active_requests(hctx);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम blk_mq_put_driver_tag(काष्ठा request *rq)
अणु
	अगर (rq->tag == BLK_MQ_NO_TAG || rq->पूर्णांकernal_tag == BLK_MQ_NO_TAG)
		वापस;

	__blk_mq_put_driver_tag(rq->mq_hctx, rq);
पूर्ण

अटल अंतरभूत व्योम blk_mq_clear_mq_map(काष्ठा blk_mq_queue_map *qmap)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		qmap->mq_map[cpu] = 0;
पूर्ण

/*
 * blk_mq_plug() - Get caller context plug
 * @q: request queue
 * @bio : the bio being submitted by the caller context
 *
 * Plugging, by design, may delay the insertion of BIOs पूर्णांकo the elevator in
 * order to increase BIO merging opportunities. This however can cause BIO
 * insertion order to change from the order in which submit_bio() is being
 * executed in the हाल of multiple contexts concurrently issuing BIOs to a
 * device, even अगर these context are synchronized to tightly control BIO issuing
 * order. While this is not a problem with regular block devices, this ordering
 * change can cause ग_लिखो BIO failures with zoned block devices as these
 * require sequential ग_लिखो patterns to zones. Prevent this from happening by
 * ignoring the plug state of a BIO issuing context अगर the target request queue
 * is क्रम a zoned block device and the BIO to plug is a ग_लिखो operation.
 *
 * Return current->plug अगर the bio can be plugged and शून्य otherwise
 */
अटल अंतरभूत काष्ठा blk_plug *blk_mq_plug(काष्ठा request_queue *q,
					   काष्ठा bio *bio)
अणु
	/*
	 * For regular block devices or पढ़ो operations, use the context plug
	 * which may be शून्य अगर blk_start_plug() was not executed.
	 */
	अगर (!blk_queue_is_zoned(q) || !op_is_ग_लिखो(bio_op(bio)))
		वापस current->plug;

	/* Zoned block device ग_लिखो operation हाल: करो not plug the BIO */
	वापस शून्य;
पूर्ण

/*
 * For shared tag users, we track the number of currently active users
 * and attempt to provide a fair share of the tag depth क्रम each of them.
 */
अटल अंतरभूत bool hctx_may_queue(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा sbiपंचांगap_queue *bt)
अणु
	अचिन्हित पूर्णांक depth, users;

	अगर (!hctx || !(hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED))
		वापस true;

	/*
	 * Don't try भागiding an ant
	 */
	अगर (bt->sb.depth == 1)
		वापस true;

	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags)) अणु
		काष्ठा request_queue *q = hctx->queue;
		काष्ठा blk_mq_tag_set *set = q->tag_set;

		अगर (!test_bit(QUEUE_FLAG_HCTX_ACTIVE, &q->queue_flags))
			वापस true;
		users = atomic_पढ़ो(&set->active_queues_shared_sbiपंचांगap);
	पूर्ण अन्यथा अणु
		अगर (!test_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
			वापस true;
		users = atomic_पढ़ो(&hctx->tags->active_queues);
	पूर्ण

	अगर (!users)
		वापस true;

	/*
	 * Allow at least some tags
	 */
	depth = max((bt->sb.depth + users - 1) / users, 4U);
	वापस __blk_mq_active_requests(hctx) < depth;
पूर्ण


#पूर्ण_अगर
