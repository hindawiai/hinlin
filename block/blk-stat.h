<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BLK_STAT_H
#घोषणा BLK_STAT_H

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/rcupdate.h>
#समावेश <linux/समयr.h>

/**
 * काष्ठा blk_stat_callback - Block statistics callback.
 *
 * A &काष्ठा blk_stat_callback is associated with a &काष्ठा request_queue. While
 * @समयr is active, that queue's request completion latencies are sorted पूर्णांकo
 * buckets by @bucket_fn and added to a per-cpu buffer, @cpu_stat. When the
 * समयr fires, @cpu_stat is flushed to @stat and @समयr_fn is invoked.
 */
काष्ठा blk_stat_callback अणु
	/*
	 * @list: RCU list of callbacks क्रम a &काष्ठा request_queue.
	 */
	काष्ठा list_head list;

	/**
	 * @समयr: Timer क्रम the next callback invocation.
	 */
	काष्ठा समयr_list समयr;

	/**
	 * @cpu_stat: Per-cpu statistics buckets.
	 */
	काष्ठा blk_rq_stat __percpu *cpu_stat;

	/**
	 * @bucket_fn: Given a request, वापसs which statistics bucket it
	 * should be accounted under. Return -1 क्रम no bucket क्रम this
	 * request.
	 */
	पूर्णांक (*bucket_fn)(स्थिर काष्ठा request *);

	/**
	 * @buckets: Number of statistics buckets.
	 */
	अचिन्हित पूर्णांक buckets;

	/**
	 * @stat: Array of statistics buckets.
	 */
	काष्ठा blk_rq_stat *stat;

	/**
	 * @fn: Callback function.
	 */
	व्योम (*समयr_fn)(काष्ठा blk_stat_callback *);

	/**
	 * @data: Private poपूर्णांकer क्रम the user.
	 */
	व्योम *data;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा blk_queue_stats *blk_alloc_queue_stats(व्योम);
व्योम blk_मुक्त_queue_stats(काष्ठा blk_queue_stats *);

व्योम blk_stat_add(काष्ठा request *rq, u64 now);

/* record समय/size info in request but not add a callback */
व्योम blk_stat_enable_accounting(काष्ठा request_queue *q);

/**
 * blk_stat_alloc_callback() - Allocate a block statistics callback.
 * @समयr_fn: Timer callback function.
 * @bucket_fn: Bucket callback function.
 * @buckets: Number of statistics buckets.
 * @data: Value क्रम the @data field of the &काष्ठा blk_stat_callback.
 *
 * See &काष्ठा blk_stat_callback क्रम details on the callback functions.
 *
 * Return: &काष्ठा blk_stat_callback on success or शून्य on ENOMEM.
 */
काष्ठा blk_stat_callback *
blk_stat_alloc_callback(व्योम (*समयr_fn)(काष्ठा blk_stat_callback *),
			पूर्णांक (*bucket_fn)(स्थिर काष्ठा request *),
			अचिन्हित पूर्णांक buckets, व्योम *data);

/**
 * blk_stat_add_callback() - Add a block statistics callback to be run on a
 * request queue.
 * @q: The request queue.
 * @cb: The callback.
 *
 * Note that a single &काष्ठा blk_stat_callback can only be added to a single
 * &काष्ठा request_queue.
 */
व्योम blk_stat_add_callback(काष्ठा request_queue *q,
			   काष्ठा blk_stat_callback *cb);

/**
 * blk_stat_हटाओ_callback() - Remove a block statistics callback from a
 * request queue.
 * @q: The request queue.
 * @cb: The callback.
 *
 * When this वापसs, the callback is not running on any CPUs and will not be
 * called again unless पढ़ोded.
 */
व्योम blk_stat_हटाओ_callback(काष्ठा request_queue *q,
			      काष्ठा blk_stat_callback *cb);

/**
 * blk_stat_मुक्त_callback() - Free a block statistics callback.
 * @cb: The callback.
 *
 * @cb may be शून्य, in which हाल this करोes nothing. If it is not शून्य, @cb must
 * not be associated with a request queue. I.e., अगर it was previously added with
 * blk_stat_add_callback(), it must also have been हटाओd since then with
 * blk_stat_हटाओ_callback().
 */
व्योम blk_stat_मुक्त_callback(काष्ठा blk_stat_callback *cb);

/**
 * blk_stat_is_active() - Check अगर a block statistics callback is currently
 * gathering statistics.
 * @cb: The callback.
 */
अटल अंतरभूत bool blk_stat_is_active(काष्ठा blk_stat_callback *cb)
अणु
	वापस समयr_pending(&cb->समयr);
पूर्ण

/**
 * blk_stat_activate_nsecs() - Gather block statistics during a समय winकरोw in
 * nanoseconds.
 * @cb: The callback.
 * @nsecs: Number of nanoseconds to gather statistics क्रम.
 *
 * The समयr callback will be called when the winकरोw expires.
 */
अटल अंतरभूत व्योम blk_stat_activate_nsecs(काष्ठा blk_stat_callback *cb,
					   u64 nsecs)
अणु
	mod_समयr(&cb->समयr, jअगरfies + nsecs_to_jअगरfies(nsecs));
पूर्ण

अटल अंतरभूत व्योम blk_stat_deactivate(काष्ठा blk_stat_callback *cb)
अणु
	del_समयr_sync(&cb->समयr);
पूर्ण

/**
 * blk_stat_activate_msecs() - Gather block statistics during a समय winकरोw in
 * milliseconds.
 * @cb: The callback.
 * @msecs: Number of milliseconds to gather statistics क्रम.
 *
 * The समयr callback will be called when the winकरोw expires.
 */
अटल अंतरभूत व्योम blk_stat_activate_msecs(काष्ठा blk_stat_callback *cb,
					   अचिन्हित पूर्णांक msecs)
अणु
	mod_समयr(&cb->समयr, jअगरfies + msecs_to_jअगरfies(msecs));
पूर्ण

व्योम blk_rq_stat_add(काष्ठा blk_rq_stat *, u64);
व्योम blk_rq_stat_sum(काष्ठा blk_rq_stat *, काष्ठा blk_rq_stat *);
व्योम blk_rq_stat_init(काष्ठा blk_rq_stat *);

#पूर्ण_अगर
