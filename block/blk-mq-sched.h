<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BLK_MQ_SCHED_H
#घोषणा BLK_MQ_SCHED_H

#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"

व्योम blk_mq_sched_assign_ioc(काष्ठा request *rq);

bool blk_mq_sched_try_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs, काष्ठा request **merged_request);
bool __blk_mq_sched_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs);
bool blk_mq_sched_try_insert_merge(काष्ठा request_queue *q, काष्ठा request *rq);
व्योम blk_mq_sched_mark_restart_hctx(काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_sched_restart(काष्ठा blk_mq_hw_ctx *hctx);

व्योम blk_mq_sched_insert_request(काष्ठा request *rq, bool at_head,
				 bool run_queue, bool async);
व्योम blk_mq_sched_insert_requests(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा blk_mq_ctx *ctx,
				  काष्ठा list_head *list, bool run_queue_async);

व्योम blk_mq_sched_dispatch_requests(काष्ठा blk_mq_hw_ctx *hctx);

पूर्णांक blk_mq_init_sched(काष्ठा request_queue *q, काष्ठा elevator_type *e);
व्योम blk_mq_निकास_sched(काष्ठा request_queue *q, काष्ठा elevator_queue *e);
व्योम blk_mq_sched_मुक्त_requests(काष्ठा request_queue *q);

अटल अंतरभूत bool
blk_mq_sched_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	अगर (blk_queue_nomerges(q) || !bio_mergeable(bio))
		वापस false;

	वापस __blk_mq_sched_bio_merge(q, bio, nr_segs);
पूर्ण

अटल अंतरभूत bool
blk_mq_sched_allow_merge(काष्ठा request_queue *q, काष्ठा request *rq,
			 काष्ठा bio *bio)
अणु
	काष्ठा elevator_queue *e = q->elevator;

	अगर (e && e->type->ops.allow_merge)
		वापस e->type->ops.allow_merge(q, rq, bio);

	वापस true;
पूर्ण

अटल अंतरभूत व्योम blk_mq_sched_completed_request(काष्ठा request *rq, u64 now)
अणु
	काष्ठा elevator_queue *e = rq->q->elevator;

	अगर (e && e->type->ops.completed_request)
		e->type->ops.completed_request(rq, now);
पूर्ण

अटल अंतरभूत व्योम blk_mq_sched_requeue_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा elevator_queue *e = q->elevator;

	अगर ((rq->rq_flags & RQF_ELVPRIV) && e && e->type->ops.requeue_request)
		e->type->ops.requeue_request(rq);
पूर्ण

अटल अंतरभूत bool blk_mq_sched_has_work(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा elevator_queue *e = hctx->queue->elevator;

	अगर (e && e->type->ops.has_work)
		वापस e->type->ops.has_work(hctx);

	वापस false;
पूर्ण

अटल अंतरभूत bool blk_mq_sched_needs_restart(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	वापस test_bit(BLK_MQ_S_SCHED_RESTART, &hctx->state);
पूर्ण

#पूर्ण_अगर
