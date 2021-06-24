<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  MQ Deadline i/o scheduler - adaptation of the legacy deadline scheduler,
 *  क्रम the blk-mq scheduling framework
 *
 *  Copyright (C) 2016 Jens Axboe <axboe@kernel.dk>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/elevator.h>
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/compiler.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sbiपंचांगap.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-mq-sched.h"

/*
 * See Documentation/block/deadline-iosched.rst
 */
अटल स्थिर पूर्णांक पढ़ो_expire = HZ / 2;  /* max समय beक्रमe a पढ़ो is submitted. */
अटल स्थिर पूर्णांक ग_लिखो_expire = 5 * HZ; /* ditto क्रम ग_लिखोs, these limits are SOFT! */
अटल स्थिर पूर्णांक ग_लिखोs_starved = 2;    /* max बार पढ़ोs can starve a ग_लिखो */
अटल स्थिर पूर्णांक fअगरo_batch = 16;       /* # of sequential requests treated as one
				     by the above parameters. For throughput. */

काष्ठा deadline_data अणु
	/*
	 * run समय data
	 */

	/*
	 * requests (deadline_rq s) are present on both sort_list and fअगरo_list
	 */
	काष्ठा rb_root sort_list[2];
	काष्ठा list_head fअगरo_list[2];

	/*
	 * next in sort order. पढ़ो, ग_लिखो or both are शून्य
	 */
	काष्ठा request *next_rq[2];
	अचिन्हित पूर्णांक batching;		/* number of sequential requests made */
	अचिन्हित पूर्णांक starved;		/* बार पढ़ोs have starved ग_लिखोs */

	/*
	 * settings that change how the i/o scheduler behaves
	 */
	पूर्णांक fअगरo_expire[2];
	पूर्णांक fअगरo_batch;
	पूर्णांक ग_लिखोs_starved;
	पूर्णांक front_merges;

	spinlock_t lock;
	spinlock_t zone_lock;
	काष्ठा list_head dispatch;
पूर्ण;

अटल अंतरभूत काष्ठा rb_root *
deadline_rb_root(काष्ठा deadline_data *dd, काष्ठा request *rq)
अणु
	वापस &dd->sort_list[rq_data_dir(rq)];
पूर्ण

/*
 * get the request after `rq' in sector-sorted order
 */
अटल अंतरभूत काष्ठा request *
deadline_latter_request(काष्ठा request *rq)
अणु
	काष्ठा rb_node *node = rb_next(&rq->rb_node);

	अगर (node)
		वापस rb_entry_rq(node);

	वापस शून्य;
पूर्ण

अटल व्योम
deadline_add_rq_rb(काष्ठा deadline_data *dd, काष्ठा request *rq)
अणु
	काष्ठा rb_root *root = deadline_rb_root(dd, rq);

	elv_rb_add(root, rq);
पूर्ण

अटल अंतरभूत व्योम
deadline_del_rq_rb(काष्ठा deadline_data *dd, काष्ठा request *rq)
अणु
	स्थिर पूर्णांक data_dir = rq_data_dir(rq);

	अगर (dd->next_rq[data_dir] == rq)
		dd->next_rq[data_dir] = deadline_latter_request(rq);

	elv_rb_del(deadline_rb_root(dd, rq), rq);
पूर्ण

/*
 * हटाओ rq from rbtree and fअगरo.
 */
अटल व्योम deadline_हटाओ_request(काष्ठा request_queue *q, काष्ठा request *rq)
अणु
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	list_del_init(&rq->queuelist);

	/*
	 * We might not be on the rbtree, अगर we are करोing an insert merge
	 */
	अगर (!RB_EMPTY_NODE(&rq->rb_node))
		deadline_del_rq_rb(dd, rq);

	elv_rqhash_del(q, rq);
	अगर (q->last_merge == rq)
		q->last_merge = शून्य;
पूर्ण

अटल व्योम dd_request_merged(काष्ठा request_queue *q, काष्ठा request *req,
			      क्रमागत elv_merge type)
अणु
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	/*
	 * अगर the merge was a front merge, we need to reposition request
	 */
	अगर (type == ELEVATOR_FRONT_MERGE) अणु
		elv_rb_del(deadline_rb_root(dd, req), req);
		deadline_add_rq_rb(dd, req);
	पूर्ण
पूर्ण

अटल व्योम dd_merged_requests(काष्ठा request_queue *q, काष्ठा request *req,
			       काष्ठा request *next)
अणु
	/*
	 * अगर next expires beक्रमe rq, assign its expire समय to rq
	 * and move पूर्णांकo next position (next will be deleted) in fअगरo
	 */
	अगर (!list_empty(&req->queuelist) && !list_empty(&next->queuelist)) अणु
		अगर (समय_beक्रमe((अचिन्हित दीर्घ)next->fअगरo_समय,
				(अचिन्हित दीर्घ)req->fअगरo_समय)) अणु
			list_move(&req->queuelist, &next->queuelist);
			req->fअगरo_समय = next->fअगरo_समय;
		पूर्ण
	पूर्ण

	/*
	 * समाप्त knowledge of next, this one is a goner
	 */
	deadline_हटाओ_request(q, next);
पूर्ण

/*
 * move an entry to dispatch queue
 */
अटल व्योम
deadline_move_request(काष्ठा deadline_data *dd, काष्ठा request *rq)
अणु
	स्थिर पूर्णांक data_dir = rq_data_dir(rq);

	dd->next_rq[READ] = शून्य;
	dd->next_rq[WRITE] = शून्य;
	dd->next_rq[data_dir] = deadline_latter_request(rq);

	/*
	 * take it off the sort and fअगरo list
	 */
	deadline_हटाओ_request(rq->q, rq);
पूर्ण

/*
 * deadline_check_fअगरo वापसs 0 अगर there are no expired requests on the fअगरo,
 * 1 otherwise. Requires !list_empty(&dd->fअगरo_list[data_dir])
 */
अटल अंतरभूत पूर्णांक deadline_check_fअगरo(काष्ठा deadline_data *dd, पूर्णांक ddir)
अणु
	काष्ठा request *rq = rq_entry_fअगरo(dd->fअगरo_list[ddir].next);

	/*
	 * rq is expired!
	 */
	अगर (समय_after_eq(jअगरfies, (अचिन्हित दीर्घ)rq->fअगरo_समय))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * For the specअगरied data direction, वापस the next request to
 * dispatch using arrival ordered lists.
 */
अटल काष्ठा request *
deadline_fअगरo_request(काष्ठा deadline_data *dd, पूर्णांक data_dir)
अणु
	काष्ठा request *rq;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(data_dir != READ && data_dir != WRITE))
		वापस शून्य;

	अगर (list_empty(&dd->fअगरo_list[data_dir]))
		वापस शून्य;

	rq = rq_entry_fअगरo(dd->fअगरo_list[data_dir].next);
	अगर (data_dir == READ || !blk_queue_is_zoned(rq->q))
		वापस rq;

	/*
	 * Look क्रम a ग_लिखो request that can be dispatched, that is one with
	 * an unlocked target zone.
	 */
	spin_lock_irqsave(&dd->zone_lock, flags);
	list_क्रम_each_entry(rq, &dd->fअगरo_list[WRITE], queuelist) अणु
		अगर (blk_req_can_dispatch_to_zone(rq))
			जाओ out;
	पूर्ण
	rq = शून्य;
out:
	spin_unlock_irqrestore(&dd->zone_lock, flags);

	वापस rq;
पूर्ण

/*
 * For the specअगरied data direction, वापस the next request to
 * dispatch using sector position sorted lists.
 */
अटल काष्ठा request *
deadline_next_request(काष्ठा deadline_data *dd, पूर्णांक data_dir)
अणु
	काष्ठा request *rq;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(data_dir != READ && data_dir != WRITE))
		वापस शून्य;

	rq = dd->next_rq[data_dir];
	अगर (!rq)
		वापस शून्य;

	अगर (data_dir == READ || !blk_queue_is_zoned(rq->q))
		वापस rq;

	/*
	 * Look क्रम a ग_लिखो request that can be dispatched, that is one with
	 * an unlocked target zone.
	 */
	spin_lock_irqsave(&dd->zone_lock, flags);
	जबतक (rq) अणु
		अगर (blk_req_can_dispatch_to_zone(rq))
			अवरोध;
		rq = deadline_latter_request(rq);
	पूर्ण
	spin_unlock_irqrestore(&dd->zone_lock, flags);

	वापस rq;
पूर्ण

/*
 * deadline_dispatch_requests selects the best request according to
 * पढ़ो/ग_लिखो expire, fअगरo_batch, etc
 */
अटल काष्ठा request *__dd_dispatch_request(काष्ठा deadline_data *dd)
अणु
	काष्ठा request *rq, *next_rq;
	bool पढ़ोs, ग_लिखोs;
	पूर्णांक data_dir;

	अगर (!list_empty(&dd->dispatch)) अणु
		rq = list_first_entry(&dd->dispatch, काष्ठा request, queuelist);
		list_del_init(&rq->queuelist);
		जाओ करोne;
	पूर्ण

	पढ़ोs = !list_empty(&dd->fअगरo_list[READ]);
	ग_लिखोs = !list_empty(&dd->fअगरo_list[WRITE]);

	/*
	 * batches are currently पढ़ोs XOR ग_लिखोs
	 */
	rq = deadline_next_request(dd, WRITE);
	अगर (!rq)
		rq = deadline_next_request(dd, READ);

	अगर (rq && dd->batching < dd->fअगरo_batch)
		/* we have a next request are still entitled to batch */
		जाओ dispatch_request;

	/*
	 * at this poपूर्णांक we are not running a batch. select the appropriate
	 * data direction (पढ़ो / ग_लिखो)
	 */

	अगर (पढ़ोs) अणु
		BUG_ON(RB_EMPTY_ROOT(&dd->sort_list[READ]));

		अगर (deadline_fअगरo_request(dd, WRITE) &&
		    (dd->starved++ >= dd->ग_लिखोs_starved))
			जाओ dispatch_ग_लिखोs;

		data_dir = READ;

		जाओ dispatch_find_request;
	पूर्ण

	/*
	 * there are either no पढ़ोs or ग_लिखोs have been starved
	 */

	अगर (ग_लिखोs) अणु
dispatch_ग_लिखोs:
		BUG_ON(RB_EMPTY_ROOT(&dd->sort_list[WRITE]));

		dd->starved = 0;

		data_dir = WRITE;

		जाओ dispatch_find_request;
	पूर्ण

	वापस शून्य;

dispatch_find_request:
	/*
	 * we are not running a batch, find best request क्रम selected data_dir
	 */
	next_rq = deadline_next_request(dd, data_dir);
	अगर (deadline_check_fअगरo(dd, data_dir) || !next_rq) अणु
		/*
		 * A deadline has expired, the last request was in the other
		 * direction, or we have run out of higher-sectored requests.
		 * Start again from the request with the earliest expiry समय.
		 */
		rq = deadline_fअगरo_request(dd, data_dir);
	पूर्ण अन्यथा अणु
		/*
		 * The last req was the same dir and we have a next request in
		 * sort order. No expired requests so जारी on from here.
		 */
		rq = next_rq;
	पूर्ण

	/*
	 * For a zoned block device, अगर we only have ग_लिखोs queued and none of
	 * them can be dispatched, rq will be शून्य.
	 */
	अगर (!rq)
		वापस शून्य;

	dd->batching = 0;

dispatch_request:
	/*
	 * rq is the selected appropriate request.
	 */
	dd->batching++;
	deadline_move_request(dd, rq);
करोne:
	/*
	 * If the request needs its target zone locked, करो it.
	 */
	blk_req_zone_ग_लिखो_lock(rq);
	rq->rq_flags |= RQF_STARTED;
	वापस rq;
पूर्ण

/*
 * One confusing aspect here is that we get called क्रम a specअगरic
 * hardware queue, but we may वापस a request that is क्रम a
 * dअगरferent hardware queue. This is because mq-deadline has shared
 * state क्रम all hardware queues, in terms of sorting, FIFOs, etc.
 */
अटल काष्ठा request *dd_dispatch_request(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा deadline_data *dd = hctx->queue->elevator->elevator_data;
	काष्ठा request *rq;

	spin_lock(&dd->lock);
	rq = __dd_dispatch_request(dd);
	spin_unlock(&dd->lock);

	वापस rq;
पूर्ण

अटल व्योम dd_निकास_queue(काष्ठा elevator_queue *e)
अणु
	काष्ठा deadline_data *dd = e->elevator_data;

	BUG_ON(!list_empty(&dd->fअगरo_list[READ]));
	BUG_ON(!list_empty(&dd->fअगरo_list[WRITE]));

	kमुक्त(dd);
पूर्ण

/*
 * initialize elevator निजी data (deadline_data).
 */
अटल पूर्णांक dd_init_queue(काष्ठा request_queue *q, काष्ठा elevator_type *e)
अणु
	काष्ठा deadline_data *dd;
	काष्ठा elevator_queue *eq;

	eq = elevator_alloc(q, e);
	अगर (!eq)
		वापस -ENOMEM;

	dd = kzalloc_node(माप(*dd), GFP_KERNEL, q->node);
	अगर (!dd) अणु
		kobject_put(&eq->kobj);
		वापस -ENOMEM;
	पूर्ण
	eq->elevator_data = dd;

	INIT_LIST_HEAD(&dd->fअगरo_list[READ]);
	INIT_LIST_HEAD(&dd->fअगरo_list[WRITE]);
	dd->sort_list[READ] = RB_ROOT;
	dd->sort_list[WRITE] = RB_ROOT;
	dd->fअगरo_expire[READ] = पढ़ो_expire;
	dd->fअगरo_expire[WRITE] = ग_लिखो_expire;
	dd->ग_लिखोs_starved = ग_लिखोs_starved;
	dd->front_merges = 1;
	dd->fअगरo_batch = fअगरo_batch;
	spin_lock_init(&dd->lock);
	spin_lock_init(&dd->zone_lock);
	INIT_LIST_HEAD(&dd->dispatch);

	q->elevator = eq;
	वापस 0;
पूर्ण

अटल पूर्णांक dd_request_merge(काष्ठा request_queue *q, काष्ठा request **rq,
			    काष्ठा bio *bio)
अणु
	काष्ठा deadline_data *dd = q->elevator->elevator_data;
	sector_t sector = bio_end_sector(bio);
	काष्ठा request *__rq;

	अगर (!dd->front_merges)
		वापस ELEVATOR_NO_MERGE;

	__rq = elv_rb_find(&dd->sort_list[bio_data_dir(bio)], sector);
	अगर (__rq) अणु
		BUG_ON(sector != blk_rq_pos(__rq));

		अगर (elv_bio_merge_ok(__rq, bio)) अणु
			*rq = __rq;
			वापस ELEVATOR_FRONT_MERGE;
		पूर्ण
	पूर्ण

	वापस ELEVATOR_NO_MERGE;
पूर्ण

अटल bool dd_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा deadline_data *dd = q->elevator->elevator_data;
	काष्ठा request *मुक्त = शून्य;
	bool ret;

	spin_lock(&dd->lock);
	ret = blk_mq_sched_try_merge(q, bio, nr_segs, &मुक्त);
	spin_unlock(&dd->lock);

	अगर (मुक्त)
		blk_mq_मुक्त_request(मुक्त);

	वापस ret;
पूर्ण

/*
 * add rq to rbtree and fअगरo
 */
अटल व्योम dd_insert_request(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा request *rq,
			      bool at_head)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;
	स्थिर पूर्णांक data_dir = rq_data_dir(rq);

	/*
	 * This may be a requeue of a ग_लिखो request that has locked its
	 * target zone. If it is the हाल, this releases the zone lock.
	 */
	blk_req_zone_ग_लिखो_unlock(rq);

	अगर (blk_mq_sched_try_insert_merge(q, rq))
		वापस;

	trace_block_rq_insert(rq);

	अगर (at_head) अणु
		list_add(&rq->queuelist, &dd->dispatch);
	पूर्ण अन्यथा अणु
		deadline_add_rq_rb(dd, rq);

		अगर (rq_mergeable(rq)) अणु
			elv_rqhash_add(q, rq);
			अगर (!q->last_merge)
				q->last_merge = rq;
		पूर्ण

		/*
		 * set expire समय and add to fअगरo list
		 */
		rq->fअगरo_समय = jअगरfies + dd->fअगरo_expire[data_dir];
		list_add_tail(&rq->queuelist, &dd->fअगरo_list[data_dir]);
	पूर्ण
पूर्ण

अटल व्योम dd_insert_requests(काष्ठा blk_mq_hw_ctx *hctx,
			       काष्ठा list_head *list, bool at_head)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	spin_lock(&dd->lock);
	जबतक (!list_empty(list)) अणु
		काष्ठा request *rq;

		rq = list_first_entry(list, काष्ठा request, queuelist);
		list_del_init(&rq->queuelist);
		dd_insert_request(hctx, rq, at_head);
	पूर्ण
	spin_unlock(&dd->lock);
पूर्ण

/*
 * Nothing to करो here. This is defined only to ensure that .finish_request
 * method is called upon request completion.
 */
अटल व्योम dd_prepare_request(काष्ठा request *rq)
अणु
पूर्ण

/*
 * For zoned block devices, ग_लिखो unlock the target zone of
 * completed ग_लिखो requests. Do this जबतक holding the zone lock
 * spinlock so that the zone is never unlocked जबतक deadline_fअगरo_request()
 * or deadline_next_request() are executing. This function is called क्रम
 * all requests, whether or not these requests complete successfully.
 *
 * For a zoned block device, __dd_dispatch_request() may have stopped
 * dispatching requests अगर all the queued requests are ग_लिखो requests directed
 * at zones that are alपढ़ोy locked due to on-going ग_लिखो requests. To ensure
 * ग_लिखो request dispatch progress in this हाल, mark the queue as needing a
 * restart to ensure that the queue is run again after completion of the
 * request and zones being unlocked.
 */
अटल व्योम dd_finish_request(काष्ठा request *rq)
अणु
	काष्ठा request_queue *q = rq->q;

	अगर (blk_queue_is_zoned(q)) अणु
		काष्ठा deadline_data *dd = q->elevator->elevator_data;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dd->zone_lock, flags);
		blk_req_zone_ग_लिखो_unlock(rq);
		अगर (!list_empty(&dd->fअगरo_list[WRITE]))
			blk_mq_sched_mark_restart_hctx(rq->mq_hctx);
		spin_unlock_irqrestore(&dd->zone_lock, flags);
	पूर्ण
पूर्ण

अटल bool dd_has_work(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा deadline_data *dd = hctx->queue->elevator->elevator_data;

	वापस !list_empty_careful(&dd->dispatch) ||
		!list_empty_careful(&dd->fअगरo_list[0]) ||
		!list_empty_careful(&dd->fअगरo_list[1]);
पूर्ण

/*
 * sysfs parts below
 */
अटल sमाप_प्रकार
deadline_var_show(पूर्णांक var, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", var);
पूर्ण

अटल व्योम
deadline_var_store(पूर्णांक *var, स्थिर अक्षर *page)
अणु
	अक्षर *p = (अक्षर *) page;

	*var = simple_म_से_दीर्घ(p, &p, 10);
पूर्ण

#घोषणा SHOW_FUNCTION(__FUNC, __VAR, __CONV)				\
अटल sमाप_प्रकार __FUNC(काष्ठा elevator_queue *e, अक्षर *page)		\
अणु									\
	काष्ठा deadline_data *dd = e->elevator_data;			\
	पूर्णांक __data = __VAR;						\
	अगर (__CONV)							\
		__data = jअगरfies_to_msecs(__data);			\
	वापस deadline_var_show(__data, (page));			\
पूर्ण
SHOW_FUNCTION(deadline_पढ़ो_expire_show, dd->fअगरo_expire[READ], 1);
SHOW_FUNCTION(deadline_ग_लिखो_expire_show, dd->fअगरo_expire[WRITE], 1);
SHOW_FUNCTION(deadline_ग_लिखोs_starved_show, dd->ग_लिखोs_starved, 0);
SHOW_FUNCTION(deadline_front_merges_show, dd->front_merges, 0);
SHOW_FUNCTION(deadline_fअगरo_batch_show, dd->fअगरo_batch, 0);
#अघोषित SHOW_FUNCTION

#घोषणा STORE_FUNCTION(__FUNC, __PTR, MIN, MAX, __CONV)			\
अटल sमाप_प्रकार __FUNC(काष्ठा elevator_queue *e, स्थिर अक्षर *page, माप_प्रकार count)	\
अणु									\
	काष्ठा deadline_data *dd = e->elevator_data;			\
	पूर्णांक __data;							\
	deadline_var_store(&__data, (page));				\
	अगर (__data < (MIN))						\
		__data = (MIN);						\
	अन्यथा अगर (__data > (MAX))					\
		__data = (MAX);						\
	अगर (__CONV)							\
		*(__PTR) = msecs_to_jअगरfies(__data);			\
	अन्यथा								\
		*(__PTR) = __data;					\
	वापस count;							\
पूर्ण
STORE_FUNCTION(deadline_पढ़ो_expire_store, &dd->fअगरo_expire[READ], 0, पूर्णांक_उच्च, 1);
STORE_FUNCTION(deadline_ग_लिखो_expire_store, &dd->fअगरo_expire[WRITE], 0, पूर्णांक_उच्च, 1);
STORE_FUNCTION(deadline_ग_लिखोs_starved_store, &dd->ग_लिखोs_starved, पूर्णांक_न्यून, पूर्णांक_उच्च, 0);
STORE_FUNCTION(deadline_front_merges_store, &dd->front_merges, 0, 1, 0);
STORE_FUNCTION(deadline_fअगरo_batch_store, &dd->fअगरo_batch, 0, पूर्णांक_उच्च, 0);
#अघोषित STORE_FUNCTION

#घोषणा DD_ATTR(name) \
	__ATTR(name, 0644, deadline_##name##_show, deadline_##name##_store)

अटल काष्ठा elv_fs_entry deadline_attrs[] = अणु
	DD_ATTR(पढ़ो_expire),
	DD_ATTR(ग_लिखो_expire),
	DD_ATTR(ग_लिखोs_starved),
	DD_ATTR(front_merges),
	DD_ATTR(fअगरo_batch),
	__ATTR_शून्य
पूर्ण;

#अगर_घोषित CONFIG_BLK_DEBUG_FS
#घोषणा DEADLINE_DEBUGFS_Dसूची_ATTRS(ddir, name)				\
अटल व्योम *deadline_##name##_fअगरo_start(काष्ठा seq_file *m,		\
					  loff_t *pos)			\
	__acquires(&dd->lock)						\
अणु									\
	काष्ठा request_queue *q = m->निजी;				\
	काष्ठा deadline_data *dd = q->elevator->elevator_data;		\
									\
	spin_lock(&dd->lock);						\
	वापस seq_list_start(&dd->fअगरo_list[ddir], *pos);		\
पूर्ण									\
									\
अटल व्योम *deadline_##name##_fअगरo_next(काष्ठा seq_file *m, व्योम *v,	\
					 loff_t *pos)			\
अणु									\
	काष्ठा request_queue *q = m->निजी;				\
	काष्ठा deadline_data *dd = q->elevator->elevator_data;		\
									\
	वापस seq_list_next(v, &dd->fअगरo_list[ddir], pos);		\
पूर्ण									\
									\
अटल व्योम deadline_##name##_fअगरo_stop(काष्ठा seq_file *m, व्योम *v)	\
	__releases(&dd->lock)						\
अणु									\
	काष्ठा request_queue *q = m->निजी;				\
	काष्ठा deadline_data *dd = q->elevator->elevator_data;		\
									\
	spin_unlock(&dd->lock);						\
पूर्ण									\
									\
अटल स्थिर काष्ठा seq_operations deadline_##name##_fअगरo_seq_ops = अणु	\
	.start	= deadline_##name##_fअगरo_start,				\
	.next	= deadline_##name##_fअगरo_next,				\
	.stop	= deadline_##name##_fअगरo_stop,				\
	.show	= blk_mq_debugfs_rq_show,				\
पूर्ण;									\
									\
अटल पूर्णांक deadline_##name##_next_rq_show(व्योम *data,			\
					  काष्ठा seq_file *m)		\
अणु									\
	काष्ठा request_queue *q = data;					\
	काष्ठा deadline_data *dd = q->elevator->elevator_data;		\
	काष्ठा request *rq = dd->next_rq[ddir];				\
									\
	अगर (rq)								\
		__blk_mq_debugfs_rq_show(m, rq);			\
	वापस 0;							\
पूर्ण
DEADLINE_DEBUGFS_Dसूची_ATTRS(READ, पढ़ो)
DEADLINE_DEBUGFS_Dसूची_ATTRS(WRITE, ग_लिखो)
#अघोषित DEADLINE_DEBUGFS_Dसूची_ATTRS

अटल पूर्णांक deadline_batching_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	seq_म_लिखो(m, "%u\n", dd->batching);
	वापस 0;
पूर्ण

अटल पूर्णांक deadline_starved_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	seq_म_लिखो(m, "%u\n", dd->starved);
	वापस 0;
पूर्ण

अटल व्योम *deadline_dispatch_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(&dd->lock)
अणु
	काष्ठा request_queue *q = m->निजी;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	spin_lock(&dd->lock);
	वापस seq_list_start(&dd->dispatch, *pos);
पूर्ण

अटल व्योम *deadline_dispatch_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा request_queue *q = m->निजी;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	वापस seq_list_next(v, &dd->dispatch, pos);
पूर्ण

अटल व्योम deadline_dispatch_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&dd->lock)
अणु
	काष्ठा request_queue *q = m->निजी;
	काष्ठा deadline_data *dd = q->elevator->elevator_data;

	spin_unlock(&dd->lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations deadline_dispatch_seq_ops = अणु
	.start	= deadline_dispatch_start,
	.next	= deadline_dispatch_next,
	.stop	= deadline_dispatch_stop,
	.show	= blk_mq_debugfs_rq_show,
पूर्ण;

#घोषणा DEADLINE_QUEUE_Dसूची_ATTRS(name)						\
	अणु#name "_fifo_list", 0400, .seq_ops = &deadline_##name##_fअगरo_seq_opsपूर्ण,	\
	अणु#name "_next_rq", 0400, deadline_##name##_next_rq_showपूर्ण
अटल स्थिर काष्ठा blk_mq_debugfs_attr deadline_queue_debugfs_attrs[] = अणु
	DEADLINE_QUEUE_Dसूची_ATTRS(पढ़ो),
	DEADLINE_QUEUE_Dसूची_ATTRS(ग_लिखो),
	अणु"batching", 0400, deadline_batching_showपूर्ण,
	अणु"starved", 0400, deadline_starved_showपूर्ण,
	अणु"dispatch", 0400, .seq_ops = &deadline_dispatch_seq_opsपूर्ण,
	अणुपूर्ण,
पूर्ण;
#अघोषित DEADLINE_QUEUE_Dसूची_ATTRS
#पूर्ण_अगर

अटल काष्ठा elevator_type mq_deadline = अणु
	.ops = अणु
		.insert_requests	= dd_insert_requests,
		.dispatch_request	= dd_dispatch_request,
		.prepare_request	= dd_prepare_request,
		.finish_request		= dd_finish_request,
		.next_request		= elv_rb_latter_request,
		.क्रमmer_request		= elv_rb_क्रमmer_request,
		.bio_merge		= dd_bio_merge,
		.request_merge		= dd_request_merge,
		.requests_merged	= dd_merged_requests,
		.request_merged		= dd_request_merged,
		.has_work		= dd_has_work,
		.init_sched		= dd_init_queue,
		.निकास_sched		= dd_निकास_queue,
	पूर्ण,

#अगर_घोषित CONFIG_BLK_DEBUG_FS
	.queue_debugfs_attrs = deadline_queue_debugfs_attrs,
#पूर्ण_अगर
	.elevator_attrs = deadline_attrs,
	.elevator_name = "mq-deadline",
	.elevator_alias = "deadline",
	.elevator_features = ELEVATOR_F_ZBD_SEQ_WRITE,
	.elevator_owner = THIS_MODULE,
पूर्ण;
MODULE_ALIAS("mq-deadline-iosched");

अटल पूर्णांक __init deadline_init(व्योम)
अणु
	वापस elv_रेजिस्टर(&mq_deadline);
पूर्ण

अटल व्योम __निकास deadline_निकास(व्योम)
अणु
	elv_unरेजिस्टर(&mq_deadline);
पूर्ण

module_init(deadline_init);
module_निकास(deadline_निकास);

MODULE_AUTHOR("Jens Axboe");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MQ deadline IO scheduler");
