<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Block stat tracking code
 *
 * Copyright (C) 2016 Jens Axboe
 */
#समावेश <linux/kernel.h>
#समावेश <linux/rculist.h>
#समावेश <linux/blk-mq.h>

#समावेश "blk-stat.h"
#समावेश "blk-mq.h"
#समावेश "blk.h"

काष्ठा blk_queue_stats अणु
	काष्ठा list_head callbacks;
	spinlock_t lock;
	bool enable_accounting;
पूर्ण;

व्योम blk_rq_stat_init(काष्ठा blk_rq_stat *stat)
अणु
	stat->min = -1ULL;
	stat->max = stat->nr_samples = stat->mean = 0;
	stat->batch = 0;
पूर्ण

/* src is a per-cpu stat, mean isn't initialized */
व्योम blk_rq_stat_sum(काष्ठा blk_rq_stat *dst, काष्ठा blk_rq_stat *src)
अणु
	अगर (!src->nr_samples)
		वापस;

	dst->min = min(dst->min, src->min);
	dst->max = max(dst->max, src->max);

	dst->mean = भाग_u64(src->batch + dst->mean * dst->nr_samples,
				dst->nr_samples + src->nr_samples);

	dst->nr_samples += src->nr_samples;
पूर्ण

व्योम blk_rq_stat_add(काष्ठा blk_rq_stat *stat, u64 value)
अणु
	stat->min = min(stat->min, value);
	stat->max = max(stat->max, value);
	stat->batch += value;
	stat->nr_samples++;
पूर्ण

व्योम blk_stat_add(काष्ठा request *rq, u64 now)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा blk_stat_callback *cb;
	काष्ठा blk_rq_stat *stat;
	पूर्णांक bucket, cpu;
	u64 value;

	value = (now >= rq->io_start_समय_ns) ? now - rq->io_start_समय_ns : 0;

	blk_throtl_stat_add(rq, value);

	rcu_पढ़ो_lock();
	cpu = get_cpu();
	list_क्रम_each_entry_rcu(cb, &q->stats->callbacks, list) अणु
		अगर (!blk_stat_is_active(cb))
			जारी;

		bucket = cb->bucket_fn(rq);
		अगर (bucket < 0)
			जारी;

		stat = &per_cpu_ptr(cb->cpu_stat, cpu)[bucket];
		blk_rq_stat_add(stat, value);
	पूर्ण
	put_cpu();
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम blk_stat_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा blk_stat_callback *cb = from_समयr(cb, t, समयr);
	अचिन्हित पूर्णांक bucket;
	पूर्णांक cpu;

	क्रम (bucket = 0; bucket < cb->buckets; bucket++)
		blk_rq_stat_init(&cb->stat[bucket]);

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा blk_rq_stat *cpu_stat;

		cpu_stat = per_cpu_ptr(cb->cpu_stat, cpu);
		क्रम (bucket = 0; bucket < cb->buckets; bucket++) अणु
			blk_rq_stat_sum(&cb->stat[bucket], &cpu_stat[bucket]);
			blk_rq_stat_init(&cpu_stat[bucket]);
		पूर्ण
	पूर्ण

	cb->समयr_fn(cb);
पूर्ण

काष्ठा blk_stat_callback *
blk_stat_alloc_callback(व्योम (*समयr_fn)(काष्ठा blk_stat_callback *),
			पूर्णांक (*bucket_fn)(स्थिर काष्ठा request *),
			अचिन्हित पूर्णांक buckets, व्योम *data)
अणु
	काष्ठा blk_stat_callback *cb;

	cb = kदो_स्मृति(माप(*cb), GFP_KERNEL);
	अगर (!cb)
		वापस शून्य;

	cb->stat = kदो_स्मृति_array(buckets, माप(काष्ठा blk_rq_stat),
				 GFP_KERNEL);
	अगर (!cb->stat) अणु
		kमुक्त(cb);
		वापस शून्य;
	पूर्ण
	cb->cpu_stat = __alloc_percpu(buckets * माप(काष्ठा blk_rq_stat),
				      __alignof__(काष्ठा blk_rq_stat));
	अगर (!cb->cpu_stat) अणु
		kमुक्त(cb->stat);
		kमुक्त(cb);
		वापस शून्य;
	पूर्ण

	cb->समयr_fn = समयr_fn;
	cb->bucket_fn = bucket_fn;
	cb->data = data;
	cb->buckets = buckets;
	समयr_setup(&cb->समयr, blk_stat_समयr_fn, 0);

	वापस cb;
पूर्ण

व्योम blk_stat_add_callback(काष्ठा request_queue *q,
			   काष्ठा blk_stat_callback *cb)
अणु
	अचिन्हित पूर्णांक bucket;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा blk_rq_stat *cpu_stat;

		cpu_stat = per_cpu_ptr(cb->cpu_stat, cpu);
		क्रम (bucket = 0; bucket < cb->buckets; bucket++)
			blk_rq_stat_init(&cpu_stat[bucket]);
	पूर्ण

	spin_lock_irqsave(&q->stats->lock, flags);
	list_add_tail_rcu(&cb->list, &q->stats->callbacks);
	blk_queue_flag_set(QUEUE_FLAG_STATS, q);
	spin_unlock_irqrestore(&q->stats->lock, flags);
पूर्ण

व्योम blk_stat_हटाओ_callback(काष्ठा request_queue *q,
			      काष्ठा blk_stat_callback *cb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->stats->lock, flags);
	list_del_rcu(&cb->list);
	अगर (list_empty(&q->stats->callbacks) && !q->stats->enable_accounting)
		blk_queue_flag_clear(QUEUE_FLAG_STATS, q);
	spin_unlock_irqrestore(&q->stats->lock, flags);

	del_समयr_sync(&cb->समयr);
पूर्ण

अटल व्योम blk_stat_मुक्त_callback_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा blk_stat_callback *cb;

	cb = container_of(head, काष्ठा blk_stat_callback, rcu);
	मुक्त_percpu(cb->cpu_stat);
	kमुक्त(cb->stat);
	kमुक्त(cb);
पूर्ण

व्योम blk_stat_मुक्त_callback(काष्ठा blk_stat_callback *cb)
अणु
	अगर (cb)
		call_rcu(&cb->rcu, blk_stat_मुक्त_callback_rcu);
पूर्ण

व्योम blk_stat_enable_accounting(काष्ठा request_queue *q)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->stats->lock, flags);
	q->stats->enable_accounting = true;
	blk_queue_flag_set(QUEUE_FLAG_STATS, q);
	spin_unlock_irqrestore(&q->stats->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(blk_stat_enable_accounting);

काष्ठा blk_queue_stats *blk_alloc_queue_stats(व्योम)
अणु
	काष्ठा blk_queue_stats *stats;

	stats = kदो_स्मृति(माप(*stats), GFP_KERNEL);
	अगर (!stats)
		वापस शून्य;

	INIT_LIST_HEAD(&stats->callbacks);
	spin_lock_init(&stats->lock);
	stats->enable_accounting = false;

	वापस stats;
पूर्ण

व्योम blk_मुक्त_queue_stats(काष्ठा blk_queue_stats *stats)
अणु
	अगर (!stats)
		वापस;

	WARN_ON(!list_empty(&stats->callbacks));

	kमुक्त(stats);
पूर्ण
