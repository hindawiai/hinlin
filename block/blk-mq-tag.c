<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tag allocation using scalable biपंचांगaps. Uses active queue tracking to support
 * fairer distribution of tags between multiple submitters when a shared tag map
 * is used.
 *
 * Copyright (C) 2013-2014 Jens Axboe
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/blk-mq.h>
#समावेश <linux/delay.h>
#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"

/*
 * If a previously inactive queue goes active, bump the active user count.
 * We need to करो this beक्रमe try to allocate driver tag, then even अगर fail
 * to get tag when first समय, the other shared-tag users could reserve
 * budget क्रम it.
 */
bool __blk_mq_tag_busy(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags)) अणु
		काष्ठा request_queue *q = hctx->queue;
		काष्ठा blk_mq_tag_set *set = q->tag_set;

		अगर (!test_bit(QUEUE_FLAG_HCTX_ACTIVE, &q->queue_flags) &&
		    !test_and_set_bit(QUEUE_FLAG_HCTX_ACTIVE, &q->queue_flags))
			atomic_inc(&set->active_queues_shared_sbiपंचांगap);
	पूर्ण अन्यथा अणु
		अगर (!test_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state) &&
		    !test_and_set_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
			atomic_inc(&hctx->tags->active_queues);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Wakeup all potentially sleeping on tags
 */
व्योम blk_mq_tag_wakeup_all(काष्ठा blk_mq_tags *tags, bool include_reserve)
अणु
	sbiपंचांगap_queue_wake_all(tags->biपंचांगap_tags);
	अगर (include_reserve)
		sbiपंचांगap_queue_wake_all(tags->breserved_tags);
पूर्ण

/*
 * If a previously busy queue goes inactive, potential रुकोers could now
 * be allowed to queue. Wake them up and check.
 */
व्योम __blk_mq_tag_idle(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा blk_mq_tags *tags = hctx->tags;
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा blk_mq_tag_set *set = q->tag_set;

	अगर (blk_mq_is_sbiपंचांगap_shared(hctx->flags)) अणु
		अगर (!test_and_clear_bit(QUEUE_FLAG_HCTX_ACTIVE,
					&q->queue_flags))
			वापस;
		atomic_dec(&set->active_queues_shared_sbiपंचांगap);
	पूर्ण अन्यथा अणु
		अगर (!test_and_clear_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
			वापस;
		atomic_dec(&tags->active_queues);
	पूर्ण

	blk_mq_tag_wakeup_all(tags, false);
पूर्ण

अटल पूर्णांक __blk_mq_get_tag(काष्ठा blk_mq_alloc_data *data,
			    काष्ठा sbiपंचांगap_queue *bt)
अणु
	अगर (!data->q->elevator && !(data->flags & BLK_MQ_REQ_RESERVED) &&
			!hctx_may_queue(data->hctx, bt))
		वापस BLK_MQ_NO_TAG;

	अगर (data->shallow_depth)
		वापस __sbiपंचांगap_queue_get_shallow(bt, data->shallow_depth);
	अन्यथा
		वापस __sbiपंचांगap_queue_get(bt);
पूर्ण

अचिन्हित पूर्णांक blk_mq_get_tag(काष्ठा blk_mq_alloc_data *data)
अणु
	काष्ठा blk_mq_tags *tags = blk_mq_tags_from_data(data);
	काष्ठा sbiपंचांगap_queue *bt;
	काष्ठा sbq_रुको_state *ws;
	DEFINE_SBQ_WAIT(रुको);
	अचिन्हित पूर्णांक tag_offset;
	पूर्णांक tag;

	अगर (data->flags & BLK_MQ_REQ_RESERVED) अणु
		अगर (unlikely(!tags->nr_reserved_tags)) अणु
			WARN_ON_ONCE(1);
			वापस BLK_MQ_NO_TAG;
		पूर्ण
		bt = tags->breserved_tags;
		tag_offset = 0;
	पूर्ण अन्यथा अणु
		bt = tags->biपंचांगap_tags;
		tag_offset = tags->nr_reserved_tags;
	पूर्ण

	tag = __blk_mq_get_tag(data, bt);
	अगर (tag != BLK_MQ_NO_TAG)
		जाओ found_tag;

	अगर (data->flags & BLK_MQ_REQ_NOWAIT)
		वापस BLK_MQ_NO_TAG;

	ws = bt_रुको_ptr(bt, data->hctx);
	करो अणु
		काष्ठा sbiपंचांगap_queue *bt_prev;

		/*
		 * We're out of tags on this hardware queue, kick any
		 * pending IO submits beक्रमe going to sleep रुकोing क्रम
		 * some to complete.
		 */
		blk_mq_run_hw_queue(data->hctx, false);

		/*
		 * Retry tag allocation after running the hardware queue,
		 * as running the queue may also have found completions.
		 */
		tag = __blk_mq_get_tag(data, bt);
		अगर (tag != BLK_MQ_NO_TAG)
			अवरोध;

		sbiपंचांगap_prepare_to_रुको(bt, ws, &रुको, TASK_UNINTERRUPTIBLE);

		tag = __blk_mq_get_tag(data, bt);
		अगर (tag != BLK_MQ_NO_TAG)
			अवरोध;

		bt_prev = bt;
		io_schedule();

		sbiपंचांगap_finish_रुको(bt, ws, &रुको);

		data->ctx = blk_mq_get_ctx(data->q);
		data->hctx = blk_mq_map_queue(data->q, data->cmd_flags,
						data->ctx);
		tags = blk_mq_tags_from_data(data);
		अगर (data->flags & BLK_MQ_REQ_RESERVED)
			bt = tags->breserved_tags;
		अन्यथा
			bt = tags->biपंचांगap_tags;

		/*
		 * If destination hw queue is changed, fake wake up on
		 * previous queue क्रम compensating the wake up miss, so
		 * other allocations on previous queue won't be starved.
		 */
		अगर (bt != bt_prev)
			sbiपंचांगap_queue_wake_up(bt_prev);

		ws = bt_रुको_ptr(bt, data->hctx);
	पूर्ण जबतक (1);

	sbiपंचांगap_finish_रुको(bt, ws, &रुको);

found_tag:
	/*
	 * Give up this allocation अगर the hctx is inactive.  The caller will
	 * retry on an active hctx.
	 */
	अगर (unlikely(test_bit(BLK_MQ_S_INACTIVE, &data->hctx->state))) अणु
		blk_mq_put_tag(tags, data->ctx, tag + tag_offset);
		वापस BLK_MQ_NO_TAG;
	पूर्ण
	वापस tag + tag_offset;
पूर्ण

व्योम blk_mq_put_tag(काष्ठा blk_mq_tags *tags, काष्ठा blk_mq_ctx *ctx,
		    अचिन्हित पूर्णांक tag)
अणु
	अगर (!blk_mq_tag_is_reserved(tags, tag)) अणु
		स्थिर पूर्णांक real_tag = tag - tags->nr_reserved_tags;

		BUG_ON(real_tag >= tags->nr_tags);
		sbiपंचांगap_queue_clear(tags->biपंचांगap_tags, real_tag, ctx->cpu);
	पूर्ण अन्यथा अणु
		BUG_ON(tag >= tags->nr_reserved_tags);
		sbiपंचांगap_queue_clear(tags->breserved_tags, tag, ctx->cpu);
	पूर्ण
पूर्ण

काष्ठा bt_iter_data अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	busy_iter_fn *fn;
	व्योम *data;
	bool reserved;
पूर्ण;

अटल bool bt_iter(काष्ठा sbiपंचांगap *biपंचांगap, अचिन्हित पूर्णांक bitnr, व्योम *data)
अणु
	काष्ठा bt_iter_data *iter_data = data;
	काष्ठा blk_mq_hw_ctx *hctx = iter_data->hctx;
	काष्ठा blk_mq_tags *tags = hctx->tags;
	bool reserved = iter_data->reserved;
	काष्ठा request *rq;

	अगर (!reserved)
		bitnr += tags->nr_reserved_tags;
	rq = tags->rqs[bitnr];

	/*
	 * We can hit rq == शून्य here, because the tagging functions
	 * test and set the bit beक्रमe assigning ->rqs[].
	 */
	अगर (rq && rq->q == hctx->queue && rq->mq_hctx == hctx)
		वापस iter_data->fn(hctx, rq, iter_data->data, reserved);
	वापस true;
पूर्ण

/**
 * bt_क्रम_each - iterate over the requests associated with a hardware queue
 * @hctx:	Hardware queue to examine.
 * @bt:		sbiपंचांगap to examine. This is either the breserved_tags member
 *		or the biपंचांगap_tags member of काष्ठा blk_mq_tags.
 * @fn:		Poपूर्णांकer to the function that will be called क्रम each request
 *		associated with @hctx that has been asचिन्हित a driver tag.
 *		@fn will be called as follows: @fn(@hctx, rq, @data, @reserved)
 *		where rq is a poपूर्णांकer to a request. Return true to जारी
 *		iterating tags, false to stop.
 * @data:	Will be passed as third argument to @fn.
 * @reserved:	Indicates whether @bt is the breserved_tags member or the
 *		biपंचांगap_tags member of काष्ठा blk_mq_tags.
 */
अटल व्योम bt_क्रम_each(काष्ठा blk_mq_hw_ctx *hctx, काष्ठा sbiपंचांगap_queue *bt,
			busy_iter_fn *fn, व्योम *data, bool reserved)
अणु
	काष्ठा bt_iter_data iter_data = अणु
		.hctx = hctx,
		.fn = fn,
		.data = data,
		.reserved = reserved,
	पूर्ण;

	sbiपंचांगap_क्रम_each_set(&bt->sb, bt_iter, &iter_data);
पूर्ण

काष्ठा bt_tags_iter_data अणु
	काष्ठा blk_mq_tags *tags;
	busy_tag_iter_fn *fn;
	व्योम *data;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा BT_TAG_ITER_RESERVED		(1 << 0)
#घोषणा BT_TAG_ITER_STARTED		(1 << 1)
#घोषणा BT_TAG_ITER_STATIC_RQS		(1 << 2)

अटल bool bt_tags_iter(काष्ठा sbiपंचांगap *biपंचांगap, अचिन्हित पूर्णांक bitnr, व्योम *data)
अणु
	काष्ठा bt_tags_iter_data *iter_data = data;
	काष्ठा blk_mq_tags *tags = iter_data->tags;
	bool reserved = iter_data->flags & BT_TAG_ITER_RESERVED;
	काष्ठा request *rq;

	अगर (!reserved)
		bitnr += tags->nr_reserved_tags;

	/*
	 * We can hit rq == शून्य here, because the tagging functions
	 * test and set the bit beक्रमe assigning ->rqs[].
	 */
	अगर (iter_data->flags & BT_TAG_ITER_STATIC_RQS)
		rq = tags->अटल_rqs[bitnr];
	अन्यथा
		rq = tags->rqs[bitnr];
	अगर (!rq)
		वापस true;
	अगर ((iter_data->flags & BT_TAG_ITER_STARTED) &&
	    !blk_mq_request_started(rq))
		वापस true;
	वापस iter_data->fn(rq, iter_data->data, reserved);
पूर्ण

/**
 * bt_tags_क्रम_each - iterate over the requests in a tag map
 * @tags:	Tag map to iterate over.
 * @bt:		sbiपंचांगap to examine. This is either the breserved_tags member
 *		or the biपंचांगap_tags member of काष्ठा blk_mq_tags.
 * @fn:		Poपूर्णांकer to the function that will be called क्रम each started
 *		request. @fn will be called as follows: @fn(rq, @data,
 *		@reserved) where rq is a poपूर्णांकer to a request. Return true
 *		to जारी iterating tags, false to stop.
 * @data:	Will be passed as second argument to @fn.
 * @flags:	BT_TAG_ITER_*
 */
अटल व्योम bt_tags_क्रम_each(काष्ठा blk_mq_tags *tags, काष्ठा sbiपंचांगap_queue *bt,
			     busy_tag_iter_fn *fn, व्योम *data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा bt_tags_iter_data iter_data = अणु
		.tags = tags,
		.fn = fn,
		.data = data,
		.flags = flags,
	पूर्ण;

	अगर (tags->rqs)
		sbiपंचांगap_क्रम_each_set(&bt->sb, bt_tags_iter, &iter_data);
पूर्ण

अटल व्योम __blk_mq_all_tag_iter(काष्ठा blk_mq_tags *tags,
		busy_tag_iter_fn *fn, व्योम *priv, अचिन्हित पूर्णांक flags)
अणु
	WARN_ON_ONCE(flags & BT_TAG_ITER_RESERVED);

	अगर (tags->nr_reserved_tags)
		bt_tags_क्रम_each(tags, tags->breserved_tags, fn, priv,
				 flags | BT_TAG_ITER_RESERVED);
	bt_tags_क्रम_each(tags, tags->biपंचांगap_tags, fn, priv, flags);
पूर्ण

/**
 * blk_mq_all_tag_iter - iterate over all requests in a tag map
 * @tags:	Tag map to iterate over.
 * @fn:		Poपूर्णांकer to the function that will be called क्रम each
 *		request. @fn will be called as follows: @fn(rq, @priv,
 *		reserved) where rq is a poपूर्णांकer to a request. 'reserved'
 *		indicates whether or not @rq is a reserved request. Return
 *		true to जारी iterating tags, false to stop.
 * @priv:	Will be passed as second argument to @fn.
 *
 * Caller has to pass the tag map from which requests are allocated.
 */
व्योम blk_mq_all_tag_iter(काष्ठा blk_mq_tags *tags, busy_tag_iter_fn *fn,
		व्योम *priv)
अणु
	__blk_mq_all_tag_iter(tags, fn, priv, BT_TAG_ITER_STATIC_RQS);
पूर्ण

/**
 * blk_mq_tagset_busy_iter - iterate over all started requests in a tag set
 * @tagset:	Tag set to iterate over.
 * @fn:		Poपूर्णांकer to the function that will be called क्रम each started
 *		request. @fn will be called as follows: @fn(rq, @priv,
 *		reserved) where rq is a poपूर्णांकer to a request. 'reserved'
 *		indicates whether or not @rq is a reserved request. Return
 *		true to जारी iterating tags, false to stop.
 * @priv:	Will be passed as second argument to @fn.
 */
व्योम blk_mq_tagset_busy_iter(काष्ठा blk_mq_tag_set *tagset,
		busy_tag_iter_fn *fn, व्योम *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tagset->nr_hw_queues; i++) अणु
		अगर (tagset->tags && tagset->tags[i])
			__blk_mq_all_tag_iter(tagset->tags[i], fn, priv,
					      BT_TAG_ITER_STARTED);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(blk_mq_tagset_busy_iter);

अटल bool blk_mq_tagset_count_completed_rqs(काष्ठा request *rq,
		व्योम *data, bool reserved)
अणु
	अचिन्हित *count = data;

	अगर (blk_mq_request_completed(rq))
		(*count)++;
	वापस true;
पूर्ण

/**
 * blk_mq_tagset_रुको_completed_request - Wait until all scheduled request
 * completions have finished.
 * @tagset:	Tag set to drain completed request
 *
 * Note: This function has to be run after all IO queues are shutकरोwn
 */
व्योम blk_mq_tagset_रुको_completed_request(काष्ठा blk_mq_tag_set *tagset)
अणु
	जबतक (true) अणु
		अचिन्हित count = 0;

		blk_mq_tagset_busy_iter(tagset,
				blk_mq_tagset_count_completed_rqs, &count);
		अगर (!count)
			अवरोध;
		msleep(5);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(blk_mq_tagset_रुको_completed_request);

/**
 * blk_mq_queue_tag_busy_iter - iterate over all requests with a driver tag
 * @q:		Request queue to examine.
 * @fn:		Poपूर्णांकer to the function that will be called क्रम each request
 *		on @q. @fn will be called as follows: @fn(hctx, rq, @priv,
 *		reserved) where rq is a poपूर्णांकer to a request and hctx poपूर्णांकs
 *		to the hardware queue associated with the request. 'reserved'
 *		indicates whether or not @rq is a reserved request.
 * @priv:	Will be passed as third argument to @fn.
 *
 * Note: अगर @q->tag_set is shared with other request queues then @fn will be
 * called क्रम all requests on all queues that share that tag set and not only
 * क्रम requests associated with @q.
 */
व्योम blk_mq_queue_tag_busy_iter(काष्ठा request_queue *q, busy_iter_fn *fn,
		व्योम *priv)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	/*
	 * __blk_mq_update_nr_hw_queues() updates nr_hw_queues and queue_hw_ctx
	 * जबतक the queue is frozen. So we can use q_usage_counter to aव्योम
	 * racing with it.
	 */
	अगर (!percpu_ref_tryget(&q->q_usage_counter))
		वापस;

	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		काष्ठा blk_mq_tags *tags = hctx->tags;

		/*
		 * If no software queues are currently mapped to this
		 * hardware queue, there's nothing to check
		 */
		अगर (!blk_mq_hw_queue_mapped(hctx))
			जारी;

		अगर (tags->nr_reserved_tags)
			bt_क्रम_each(hctx, tags->breserved_tags, fn, priv, true);
		bt_क्रम_each(hctx, tags->biपंचांगap_tags, fn, priv, false);
	पूर्ण
	blk_queue_निकास(q);
पूर्ण

अटल पूर्णांक bt_alloc(काष्ठा sbiपंचांगap_queue *bt, अचिन्हित पूर्णांक depth,
		    bool round_robin, पूर्णांक node)
अणु
	वापस sbiपंचांगap_queue_init_node(bt, depth, -1, round_robin, GFP_KERNEL,
				       node);
पूर्ण

अटल पूर्णांक blk_mq_init_biपंचांगap_tags(काष्ठा blk_mq_tags *tags,
				   पूर्णांक node, पूर्णांक alloc_policy)
अणु
	अचिन्हित पूर्णांक depth = tags->nr_tags - tags->nr_reserved_tags;
	bool round_robin = alloc_policy == BLK_TAG_ALLOC_RR;

	अगर (bt_alloc(&tags->__biपंचांगap_tags, depth, round_robin, node))
		वापस -ENOMEM;
	अगर (bt_alloc(&tags->__breserved_tags, tags->nr_reserved_tags,
		     round_robin, node))
		जाओ मुक्त_biपंचांगap_tags;

	tags->biपंचांगap_tags = &tags->__biपंचांगap_tags;
	tags->breserved_tags = &tags->__breserved_tags;

	वापस 0;
मुक्त_biपंचांगap_tags:
	sbiपंचांगap_queue_मुक्त(&tags->__biपंचांगap_tags);
	वापस -ENOMEM;
पूर्ण

पूर्णांक blk_mq_init_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक depth = set->queue_depth - set->reserved_tags;
	पूर्णांक alloc_policy = BLK_MQ_FLAG_TO_ALLOC_POLICY(set->flags);
	bool round_robin = alloc_policy == BLK_TAG_ALLOC_RR;
	पूर्णांक i, node = set->numa_node;

	अगर (bt_alloc(&set->__biपंचांगap_tags, depth, round_robin, node))
		वापस -ENOMEM;
	अगर (bt_alloc(&set->__breserved_tags, set->reserved_tags,
		     round_robin, node))
		जाओ मुक्त_biपंचांगap_tags;

	क्रम (i = 0; i < set->nr_hw_queues; i++) अणु
		काष्ठा blk_mq_tags *tags = set->tags[i];

		tags->biपंचांगap_tags = &set->__biपंचांगap_tags;
		tags->breserved_tags = &set->__breserved_tags;
	पूर्ण

	वापस 0;
मुक्त_biपंचांगap_tags:
	sbiपंचांगap_queue_मुक्त(&set->__biपंचांगap_tags);
	वापस -ENOMEM;
पूर्ण

व्योम blk_mq_निकास_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set)
अणु
	sbiपंचांगap_queue_मुक्त(&set->__biपंचांगap_tags);
	sbiपंचांगap_queue_मुक्त(&set->__breserved_tags);
पूर्ण

काष्ठा blk_mq_tags *blk_mq_init_tags(अचिन्हित पूर्णांक total_tags,
				     अचिन्हित पूर्णांक reserved_tags,
				     पूर्णांक node, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक alloc_policy = BLK_MQ_FLAG_TO_ALLOC_POLICY(flags);
	काष्ठा blk_mq_tags *tags;

	अगर (total_tags > BLK_MQ_TAG_MAX) अणु
		pr_err("blk-mq: tag depth too large\n");
		वापस शून्य;
	पूर्ण

	tags = kzalloc_node(माप(*tags), GFP_KERNEL, node);
	अगर (!tags)
		वापस शून्य;

	tags->nr_tags = total_tags;
	tags->nr_reserved_tags = reserved_tags;

	अगर (blk_mq_is_sbiपंचांगap_shared(flags))
		वापस tags;

	अगर (blk_mq_init_biपंचांगap_tags(tags, node, alloc_policy) < 0) अणु
		kमुक्त(tags);
		वापस शून्य;
	पूर्ण
	वापस tags;
पूर्ण

व्योम blk_mq_मुक्त_tags(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक flags)
अणु
	अगर (!blk_mq_is_sbiपंचांगap_shared(flags)) अणु
		sbiपंचांगap_queue_मुक्त(tags->biपंचांगap_tags);
		sbiपंचांगap_queue_मुक्त(tags->breserved_tags);
	पूर्ण
	kमुक्त(tags);
पूर्ण

पूर्णांक blk_mq_tag_update_depth(काष्ठा blk_mq_hw_ctx *hctx,
			    काष्ठा blk_mq_tags **tagsptr, अचिन्हित पूर्णांक tdepth,
			    bool can_grow)
अणु
	काष्ठा blk_mq_tags *tags = *tagsptr;

	अगर (tdepth <= tags->nr_reserved_tags)
		वापस -EINVAL;

	/*
	 * If we are allowed to grow beyond the original size, allocate
	 * a new set of tags beक्रमe मुक्तing the old one.
	 */
	अगर (tdepth > tags->nr_tags) अणु
		काष्ठा blk_mq_tag_set *set = hctx->queue->tag_set;
		/* Only sched tags can grow, so clear HCTX_SHARED flag  */
		अचिन्हित पूर्णांक flags = set->flags & ~BLK_MQ_F_TAG_HCTX_SHARED;
		काष्ठा blk_mq_tags *new;
		bool ret;

		अगर (!can_grow)
			वापस -EINVAL;

		/*
		 * We need some sort of upper limit, set it high enough that
		 * no valid use हालs should require more.
		 */
		अगर (tdepth > 16 * BLKDEV_MAX_RQ)
			वापस -EINVAL;

		new = blk_mq_alloc_rq_map(set, hctx->queue_num, tdepth,
				tags->nr_reserved_tags, flags);
		अगर (!new)
			वापस -ENOMEM;
		ret = blk_mq_alloc_rqs(set, new, hctx->queue_num, tdepth);
		अगर (ret) अणु
			blk_mq_मुक्त_rq_map(new, flags);
			वापस -ENOMEM;
		पूर्ण

		blk_mq_मुक्त_rqs(set, *tagsptr, hctx->queue_num);
		blk_mq_मुक्त_rq_map(*tagsptr, flags);
		*tagsptr = new;
	पूर्ण अन्यथा अणु
		/*
		 * Don't need (or can't) update reserved tags here, they
		 * reमुख्य अटल and should never need resizing.
		 */
		sbiपंचांगap_queue_resize(tags->biपंचांगap_tags,
				tdepth - tags->nr_reserved_tags);
	पूर्ण

	वापस 0;
पूर्ण

व्योम blk_mq_tag_resize_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set, अचिन्हित पूर्णांक size)
अणु
	sbiपंचांगap_queue_resize(&set->__biपंचांगap_tags, size - set->reserved_tags);
पूर्ण

/**
 * blk_mq_unique_tag() - वापस a tag that is unique queue-wide
 * @rq: request क्रम which to compute a unique tag
 *
 * The tag field in काष्ठा request is unique per hardware queue but not over
 * all hardware queues. Hence this function that वापसs a tag with the
 * hardware context index in the upper bits and the per hardware queue tag in
 * the lower bits.
 *
 * Note: When called क्रम a request that is queued on a non-multiqueue request
 * queue, the hardware context index is set to zero.
 */
u32 blk_mq_unique_tag(काष्ठा request *rq)
अणु
	वापस (rq->mq_hctx->queue_num << BLK_MQ_UNIQUE_TAG_BITS) |
		(rq->tag & BLK_MQ_UNIQUE_TAG_MASK);
पूर्ण
EXPORT_SYMBOL(blk_mq_unique_tag);
