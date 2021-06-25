<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Kyber I/O scheduler. Controls latency by throttling queue depths using
 * scalable techniques.
 *
 * Copyright (C) 2017 Facebook
 */

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/elevator.h>
#समावेश <linux/module.h>
#समावेश <linux/sbiपंचांगap.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-mq-sched.h"
#समावेश "blk-mq-tag.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/kyber.h>

/*
 * Scheduling करोमुख्यs: the device is भागided पूर्णांकo multiple करोमुख्यs based on the
 * request type.
 */
क्रमागत अणु
	KYBER_READ,
	KYBER_WRITE,
	KYBER_DISCARD,
	KYBER_OTHER,
	KYBER_NUM_DOMAINS,
पूर्ण;

अटल स्थिर अक्षर *kyber_करोमुख्य_names[] = अणु
	[KYBER_READ] = "READ",
	[KYBER_WRITE] = "WRITE",
	[KYBER_DISCARD] = "DISCARD",
	[KYBER_OTHER] = "OTHER",
पूर्ण;

क्रमागत अणु
	/*
	 * In order to prevent starvation of synchronous requests by a flood of
	 * asynchronous requests, we reserve 25% of requests क्रम synchronous
	 * operations.
	 */
	KYBER_ASYNC_PERCENT = 75,
पूर्ण;

/*
 * Maximum device-wide depth क्रम each scheduling करोमुख्य.
 *
 * Even क्रम fast devices with lots of tags like NVMe, you can saturate the
 * device with only a fraction of the maximum possible queue depth. So, we cap
 * these to a reasonable value.
 */
अटल स्थिर अचिन्हित पूर्णांक kyber_depth[] = अणु
	[KYBER_READ] = 256,
	[KYBER_WRITE] = 128,
	[KYBER_DISCARD] = 64,
	[KYBER_OTHER] = 16,
पूर्ण;

/*
 * Default latency tarमाला_लो क्रम each scheduling करोमुख्य.
 */
अटल स्थिर u64 kyber_latency_tarमाला_लो[] = अणु
	[KYBER_READ] = 2ULL * NSEC_PER_MSEC,
	[KYBER_WRITE] = 10ULL * NSEC_PER_MSEC,
	[KYBER_DISCARD] = 5ULL * NSEC_PER_SEC,
पूर्ण;

/*
 * Batch size (number of requests we'll dispatch in a row) क्रम each scheduling
 * करोमुख्य.
 */
अटल स्थिर अचिन्हित पूर्णांक kyber_batch_size[] = अणु
	[KYBER_READ] = 16,
	[KYBER_WRITE] = 8,
	[KYBER_DISCARD] = 1,
	[KYBER_OTHER] = 1,
पूर्ण;

/*
 * Requests latencies are recorded in a histogram with buckets defined relative
 * to the target latency:
 *
 * <= 1/4 * target latency
 * <= 1/2 * target latency
 * <= 3/4 * target latency
 * <= target latency
 * <= 1 1/4 * target latency
 * <= 1 1/2 * target latency
 * <= 1 3/4 * target latency
 * > 1 3/4 * target latency
 */
क्रमागत अणु
	/*
	 * The width of the latency histogram buckets is
	 * 1 / (1 << KYBER_LATENCY_SHIFT) * target latency.
	 */
	KYBER_LATENCY_SHIFT = 2,
	/*
	 * The first (1 << KYBER_LATENCY_SHIFT) buckets are <= target latency,
	 * thus, "good".
	 */
	KYBER_GOOD_BUCKETS = 1 << KYBER_LATENCY_SHIFT,
	/* There are also (1 << KYBER_LATENCY_SHIFT) "bad" buckets. */
	KYBER_LATENCY_BUCKETS = 2 << KYBER_LATENCY_SHIFT,
पूर्ण;

/*
 * We measure both the total latency and the I/O latency (i.e., latency after
 * submitting to the device).
 */
क्रमागत अणु
	KYBER_TOTAL_LATENCY,
	KYBER_IO_LATENCY,
पूर्ण;

अटल स्थिर अक्षर *kyber_latency_type_names[] = अणु
	[KYBER_TOTAL_LATENCY] = "total",
	[KYBER_IO_LATENCY] = "I/O",
पूर्ण;

/*
 * Per-cpu latency histograms: total latency and I/O latency क्रम each scheduling
 * करोमुख्य except क्रम KYBER_OTHER.
 */
काष्ठा kyber_cpu_latency अणु
	atomic_t buckets[KYBER_OTHER][2][KYBER_LATENCY_BUCKETS];
पूर्ण;

/*
 * There is a same mapping between ctx & hctx and kcq & khd,
 * we use request->mq_ctx->index_hw to index the kcq in khd.
 */
काष्ठा kyber_ctx_queue अणु
	/*
	 * Used to ensure operations on rq_list and kcq_map to be an aपंचांगoic one.
	 * Also protect the rqs on rq_list when merge.
	 */
	spinlock_t lock;
	काष्ठा list_head rq_list[KYBER_NUM_DOMAINS];
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा kyber_queue_data अणु
	काष्ठा request_queue *q;

	/*
	 * Each scheduling करोमुख्य has a limited number of in-flight requests
	 * device-wide, limited by these tokens.
	 */
	काष्ठा sbiपंचांगap_queue करोमुख्य_tokens[KYBER_NUM_DOMAINS];

	/*
	 * Async request percentage, converted to per-word depth क्रम
	 * sbiपंचांगap_get_shallow().
	 */
	अचिन्हित पूर्णांक async_depth;

	काष्ठा kyber_cpu_latency __percpu *cpu_latency;

	/* Timer क्रम stats aggregation and adjusting करोमुख्य tokens. */
	काष्ठा समयr_list समयr;

	अचिन्हित पूर्णांक latency_buckets[KYBER_OTHER][2][KYBER_LATENCY_BUCKETS];

	अचिन्हित दीर्घ latency_समयout[KYBER_OTHER];

	पूर्णांक करोमुख्य_p99[KYBER_OTHER];

	/* Target latencies in nanoseconds. */
	u64 latency_tarमाला_लो[KYBER_OTHER];
पूर्ण;

काष्ठा kyber_hctx_data अणु
	spinlock_t lock;
	काष्ठा list_head rqs[KYBER_NUM_DOMAINS];
	अचिन्हित पूर्णांक cur_करोमुख्य;
	अचिन्हित पूर्णांक batching;
	काष्ठा kyber_ctx_queue *kcqs;
	काष्ठा sbiपंचांगap kcq_map[KYBER_NUM_DOMAINS];
	काष्ठा sbq_रुको करोमुख्य_रुको[KYBER_NUM_DOMAINS];
	काष्ठा sbq_रुको_state *करोमुख्य_ws[KYBER_NUM_DOMAINS];
	atomic_t रुको_index[KYBER_NUM_DOMAINS];
पूर्ण;

अटल पूर्णांक kyber_करोमुख्य_wake(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक flags,
			     व्योम *key);

अटल अचिन्हित पूर्णांक kyber_sched_करोमुख्य(अचिन्हित पूर्णांक op)
अणु
	चयन (op & REQ_OP_MASK) अणु
	हाल REQ_OP_READ:
		वापस KYBER_READ;
	हाल REQ_OP_WRITE:
		वापस KYBER_WRITE;
	हाल REQ_OP_DISCARD:
		वापस KYBER_DISCARD;
	शेष:
		वापस KYBER_OTHER;
	पूर्ण
पूर्ण

अटल व्योम flush_latency_buckets(काष्ठा kyber_queue_data *kqd,
				  काष्ठा kyber_cpu_latency *cpu_latency,
				  अचिन्हित पूर्णांक sched_करोमुख्य, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक *buckets = kqd->latency_buckets[sched_करोमुख्य][type];
	atomic_t *cpu_buckets = cpu_latency->buckets[sched_करोमुख्य][type];
	अचिन्हित पूर्णांक bucket;

	क्रम (bucket = 0; bucket < KYBER_LATENCY_BUCKETS; bucket++)
		buckets[bucket] += atomic_xchg(&cpu_buckets[bucket], 0);
पूर्ण

/*
 * Calculate the histogram bucket with the given percentile rank, or -1 अगर there
 * aren't enough samples yet.
 */
अटल पूर्णांक calculate_percentile(काष्ठा kyber_queue_data *kqd,
				अचिन्हित पूर्णांक sched_करोमुख्य, अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक percentile)
अणु
	अचिन्हित पूर्णांक *buckets = kqd->latency_buckets[sched_करोमुख्य][type];
	अचिन्हित पूर्णांक bucket, samples = 0, percentile_samples;

	क्रम (bucket = 0; bucket < KYBER_LATENCY_BUCKETS; bucket++)
		samples += buckets[bucket];

	अगर (!samples)
		वापस -1;

	/*
	 * We करो the calculation once we have 500 samples or one second passes
	 * since the first sample was recorded, whichever comes first.
	 */
	अगर (!kqd->latency_समयout[sched_करोमुख्य])
		kqd->latency_समयout[sched_करोमुख्य] = max(jअगरfies + HZ, 1UL);
	अगर (samples < 500 &&
	    समय_is_after_jअगरfies(kqd->latency_समयout[sched_करोमुख्य])) अणु
		वापस -1;
	पूर्ण
	kqd->latency_समयout[sched_करोमुख्य] = 0;

	percentile_samples = DIV_ROUND_UP(samples * percentile, 100);
	क्रम (bucket = 0; bucket < KYBER_LATENCY_BUCKETS - 1; bucket++) अणु
		अगर (buckets[bucket] >= percentile_samples)
			अवरोध;
		percentile_samples -= buckets[bucket];
	पूर्ण
	स_रखो(buckets, 0, माप(kqd->latency_buckets[sched_करोमुख्य][type]));

	trace_kyber_latency(kqd->q, kyber_करोमुख्य_names[sched_करोमुख्य],
			    kyber_latency_type_names[type], percentile,
			    bucket + 1, 1 << KYBER_LATENCY_SHIFT, samples);

	वापस bucket;
पूर्ण

अटल व्योम kyber_resize_करोमुख्य(काष्ठा kyber_queue_data *kqd,
				अचिन्हित पूर्णांक sched_करोमुख्य, अचिन्हित पूर्णांक depth)
अणु
	depth = clamp(depth, 1U, kyber_depth[sched_करोमुख्य]);
	अगर (depth != kqd->करोमुख्य_tokens[sched_करोमुख्य].sb.depth) अणु
		sbiपंचांगap_queue_resize(&kqd->करोमुख्य_tokens[sched_करोमुख्य], depth);
		trace_kyber_adjust(kqd->q, kyber_करोमुख्य_names[sched_करोमुख्य],
				   depth);
	पूर्ण
पूर्ण

अटल व्योम kyber_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा kyber_queue_data *kqd = from_समयr(kqd, t, समयr);
	अचिन्हित पूर्णांक sched_करोमुख्य;
	पूर्णांक cpu;
	bool bad = false;

	/* Sum all of the per-cpu latency histograms. */
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा kyber_cpu_latency *cpu_latency;

		cpu_latency = per_cpu_ptr(kqd->cpu_latency, cpu);
		क्रम (sched_करोमुख्य = 0; sched_करोमुख्य < KYBER_OTHER; sched_करोमुख्य++) अणु
			flush_latency_buckets(kqd, cpu_latency, sched_करोमुख्य,
					      KYBER_TOTAL_LATENCY);
			flush_latency_buckets(kqd, cpu_latency, sched_करोमुख्य,
					      KYBER_IO_LATENCY);
		पूर्ण
	पूर्ण

	/*
	 * Check अगर any करोमुख्यs have a high I/O latency, which might indicate
	 * congestion in the device. Note that we use the p90; we करोn't want to
	 * be too sensitive to outliers here.
	 */
	क्रम (sched_करोमुख्य = 0; sched_करोमुख्य < KYBER_OTHER; sched_करोमुख्य++) अणु
		पूर्णांक p90;

		p90 = calculate_percentile(kqd, sched_करोमुख्य, KYBER_IO_LATENCY,
					   90);
		अगर (p90 >= KYBER_GOOD_BUCKETS)
			bad = true;
	पूर्ण

	/*
	 * Adjust the scheduling करोमुख्य depths. If we determined that there was
	 * congestion, we throttle all करोमुख्यs with good latencies. Either way,
	 * we ease up on throttling करोमुख्यs with bad latencies.
	 */
	क्रम (sched_करोमुख्य = 0; sched_करोमुख्य < KYBER_OTHER; sched_करोमुख्य++) अणु
		अचिन्हित पूर्णांक orig_depth, depth;
		पूर्णांक p99;

		p99 = calculate_percentile(kqd, sched_करोमुख्य,
					   KYBER_TOTAL_LATENCY, 99);
		/*
		 * This is kind of subtle: dअगरferent करोमुख्यs will not
		 * necessarily have enough samples to calculate the latency
		 * percentiles during the same winकरोw, so we have to remember
		 * the p99 क्रम the next समय we observe congestion; once we करो,
		 * we करोn't want to throttle again until we get more data, so we
		 * reset it to -1.
		 */
		अगर (bad) अणु
			अगर (p99 < 0)
				p99 = kqd->करोमुख्य_p99[sched_करोमुख्य];
			kqd->करोमुख्य_p99[sched_करोमुख्य] = -1;
		पूर्ण अन्यथा अगर (p99 >= 0) अणु
			kqd->करोमुख्य_p99[sched_करोमुख्य] = p99;
		पूर्ण
		अगर (p99 < 0)
			जारी;

		/*
		 * If this करोमुख्य has bad latency, throttle less. Otherwise,
		 * throttle more अगरf we determined that there is congestion.
		 *
		 * The new depth is scaled linearly with the p99 latency vs the
		 * latency target. E.g., अगर the p99 is 3/4 of the target, then
		 * we throttle करोwn to 3/4 of the current depth, and अगर the p99
		 * is 2x the target, then we द्विगुन the depth.
		 */
		अगर (bad || p99 >= KYBER_GOOD_BUCKETS) अणु
			orig_depth = kqd->करोमुख्य_tokens[sched_करोमुख्य].sb.depth;
			depth = (orig_depth * (p99 + 1)) >> KYBER_LATENCY_SHIFT;
			kyber_resize_करोमुख्य(kqd, sched_करोमुख्य, depth);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा kyber_queue_data *kyber_queue_data_alloc(काष्ठा request_queue *q)
अणु
	काष्ठा kyber_queue_data *kqd;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	kqd = kzalloc_node(माप(*kqd), GFP_KERNEL, q->node);
	अगर (!kqd)
		जाओ err;

	kqd->q = q;

	kqd->cpu_latency = alloc_percpu_gfp(काष्ठा kyber_cpu_latency,
					    GFP_KERNEL | __GFP_ZERO);
	अगर (!kqd->cpu_latency)
		जाओ err_kqd;

	समयr_setup(&kqd->समयr, kyber_समयr_fn, 0);

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++) अणु
		WARN_ON(!kyber_depth[i]);
		WARN_ON(!kyber_batch_size[i]);
		ret = sbiपंचांगap_queue_init_node(&kqd->करोमुख्य_tokens[i],
					      kyber_depth[i], -1, false,
					      GFP_KERNEL, q->node);
		अगर (ret) अणु
			जबतक (--i >= 0)
				sbiपंचांगap_queue_मुक्त(&kqd->करोमुख्य_tokens[i]);
			जाओ err_buckets;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < KYBER_OTHER; i++) अणु
		kqd->करोमुख्य_p99[i] = -1;
		kqd->latency_tarमाला_लो[i] = kyber_latency_tarमाला_लो[i];
	पूर्ण

	वापस kqd;

err_buckets:
	मुक्त_percpu(kqd->cpu_latency);
err_kqd:
	kमुक्त(kqd);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक kyber_init_sched(काष्ठा request_queue *q, काष्ठा elevator_type *e)
अणु
	काष्ठा kyber_queue_data *kqd;
	काष्ठा elevator_queue *eq;

	eq = elevator_alloc(q, e);
	अगर (!eq)
		वापस -ENOMEM;

	kqd = kyber_queue_data_alloc(q);
	अगर (IS_ERR(kqd)) अणु
		kobject_put(&eq->kobj);
		वापस PTR_ERR(kqd);
	पूर्ण

	blk_stat_enable_accounting(q);

	eq->elevator_data = kqd;
	q->elevator = eq;

	वापस 0;
पूर्ण

अटल व्योम kyber_निकास_sched(काष्ठा elevator_queue *e)
अणु
	काष्ठा kyber_queue_data *kqd = e->elevator_data;
	पूर्णांक i;

	del_समयr_sync(&kqd->समयr);

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++)
		sbiपंचांगap_queue_मुक्त(&kqd->करोमुख्य_tokens[i]);
	मुक्त_percpu(kqd->cpu_latency);
	kमुक्त(kqd);
पूर्ण

अटल व्योम kyber_ctx_queue_init(काष्ठा kyber_ctx_queue *kcq)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_init(&kcq->lock);
	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++)
		INIT_LIST_HEAD(&kcq->rq_list[i]);
पूर्ण

अटल व्योम kyber_depth_updated(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा kyber_queue_data *kqd = hctx->queue->elevator->elevator_data;
	काष्ठा blk_mq_tags *tags = hctx->sched_tags;
	अचिन्हित पूर्णांक shअगरt = tags->biपंचांगap_tags->sb.shअगरt;

	kqd->async_depth = (1U << shअगरt) * KYBER_ASYNC_PERCENT / 100U;

	sbiपंचांगap_queue_min_shallow_depth(tags->biपंचांगap_tags, kqd->async_depth);
पूर्ण

अटल पूर्णांक kyber_init_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा kyber_hctx_data *khd;
	पूर्णांक i;

	khd = kदो_स्मृति_node(माप(*khd), GFP_KERNEL, hctx->numa_node);
	अगर (!khd)
		वापस -ENOMEM;

	khd->kcqs = kदो_स्मृति_array_node(hctx->nr_ctx,
				       माप(काष्ठा kyber_ctx_queue),
				       GFP_KERNEL, hctx->numa_node);
	अगर (!khd->kcqs)
		जाओ err_khd;

	क्रम (i = 0; i < hctx->nr_ctx; i++)
		kyber_ctx_queue_init(&khd->kcqs[i]);

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++) अणु
		अगर (sbiपंचांगap_init_node(&khd->kcq_map[i], hctx->nr_ctx,
				      ilog2(8), GFP_KERNEL, hctx->numa_node,
				      false, false)) अणु
			जबतक (--i >= 0)
				sbiपंचांगap_मुक्त(&khd->kcq_map[i]);
			जाओ err_kcqs;
		पूर्ण
	पूर्ण

	spin_lock_init(&khd->lock);

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++) अणु
		INIT_LIST_HEAD(&khd->rqs[i]);
		khd->करोमुख्य_रुको[i].sbq = शून्य;
		init_रुकोqueue_func_entry(&khd->करोमुख्य_रुको[i].रुको,
					  kyber_करोमुख्य_wake);
		khd->करोमुख्य_रुको[i].रुको.निजी = hctx;
		INIT_LIST_HEAD(&khd->करोमुख्य_रुको[i].रुको.entry);
		atomic_set(&khd->रुको_index[i], 0);
	पूर्ण

	khd->cur_करोमुख्य = 0;
	khd->batching = 0;

	hctx->sched_data = khd;
	kyber_depth_updated(hctx);

	वापस 0;

err_kcqs:
	kमुक्त(khd->kcqs);
err_khd:
	kमुक्त(khd);
	वापस -ENOMEM;
पूर्ण

अटल व्योम kyber_निकास_hctx(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित पूर्णांक hctx_idx)
अणु
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;
	पूर्णांक i;

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++)
		sbiपंचांगap_मुक्त(&khd->kcq_map[i]);
	kमुक्त(khd->kcqs);
	kमुक्त(hctx->sched_data);
पूर्ण

अटल पूर्णांक rq_get_करोमुख्य_token(काष्ठा request *rq)
अणु
	वापस (दीर्घ)rq->elv.priv[0];
पूर्ण

अटल व्योम rq_set_करोमुख्य_token(काष्ठा request *rq, पूर्णांक token)
अणु
	rq->elv.priv[0] = (व्योम *)(दीर्घ)token;
पूर्ण

अटल व्योम rq_clear_करोमुख्य_token(काष्ठा kyber_queue_data *kqd,
				  काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक sched_करोमुख्य;
	पूर्णांक nr;

	nr = rq_get_करोमुख्य_token(rq);
	अगर (nr != -1) अणु
		sched_करोमुख्य = kyber_sched_करोमुख्य(rq->cmd_flags);
		sbiपंचांगap_queue_clear(&kqd->करोमुख्य_tokens[sched_करोमुख्य], nr,
				    rq->mq_ctx->cpu);
	पूर्ण
पूर्ण

अटल व्योम kyber_limit_depth(अचिन्हित पूर्णांक op, काष्ठा blk_mq_alloc_data *data)
अणु
	/*
	 * We use the scheduler tags as per-hardware queue queueing tokens.
	 * Async requests can be limited at this stage.
	 */
	अगर (!op_is_sync(op)) अणु
		काष्ठा kyber_queue_data *kqd = data->q->elevator->elevator_data;

		data->shallow_depth = kqd->async_depth;
	पूर्ण
पूर्ण

अटल bool kyber_bio_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा blk_mq_ctx *ctx = blk_mq_get_ctx(q);
	काष्ठा blk_mq_hw_ctx *hctx = blk_mq_map_queue(q, bio->bi_opf, ctx);
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;
	काष्ठा kyber_ctx_queue *kcq = &khd->kcqs[ctx->index_hw[hctx->type]];
	अचिन्हित पूर्णांक sched_करोमुख्य = kyber_sched_करोमुख्य(bio->bi_opf);
	काष्ठा list_head *rq_list = &kcq->rq_list[sched_करोमुख्य];
	bool merged;

	spin_lock(&kcq->lock);
	merged = blk_bio_list_merge(hctx->queue, rq_list, bio, nr_segs);
	spin_unlock(&kcq->lock);

	वापस merged;
पूर्ण

अटल व्योम kyber_prepare_request(काष्ठा request *rq)
अणु
	rq_set_करोमुख्य_token(rq, -1);
पूर्ण

अटल व्योम kyber_insert_requests(काष्ठा blk_mq_hw_ctx *hctx,
				  काष्ठा list_head *rq_list, bool at_head)
अणु
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;
	काष्ठा request *rq, *next;

	list_क्रम_each_entry_safe(rq, next, rq_list, queuelist) अणु
		अचिन्हित पूर्णांक sched_करोमुख्य = kyber_sched_करोमुख्य(rq->cmd_flags);
		काष्ठा kyber_ctx_queue *kcq = &khd->kcqs[rq->mq_ctx->index_hw[hctx->type]];
		काष्ठा list_head *head = &kcq->rq_list[sched_करोमुख्य];

		spin_lock(&kcq->lock);
		अगर (at_head)
			list_move(&rq->queuelist, head);
		अन्यथा
			list_move_tail(&rq->queuelist, head);
		sbiपंचांगap_set_bit(&khd->kcq_map[sched_करोमुख्य],
				rq->mq_ctx->index_hw[hctx->type]);
		trace_block_rq_insert(rq);
		spin_unlock(&kcq->lock);
	पूर्ण
पूर्ण

अटल व्योम kyber_finish_request(काष्ठा request *rq)
अणु
	काष्ठा kyber_queue_data *kqd = rq->q->elevator->elevator_data;

	rq_clear_करोमुख्य_token(kqd, rq);
पूर्ण

अटल व्योम add_latency_sample(काष्ठा kyber_cpu_latency *cpu_latency,
			       अचिन्हित पूर्णांक sched_करोमुख्य, अचिन्हित पूर्णांक type,
			       u64 target, u64 latency)
अणु
	अचिन्हित पूर्णांक bucket;
	u64 भागisor;

	अगर (latency > 0) अणु
		भागisor = max_t(u64, target >> KYBER_LATENCY_SHIFT, 1);
		bucket = min_t(अचिन्हित पूर्णांक, भाग64_u64(latency - 1, भागisor),
			       KYBER_LATENCY_BUCKETS - 1);
	पूर्ण अन्यथा अणु
		bucket = 0;
	पूर्ण

	atomic_inc(&cpu_latency->buckets[sched_करोमुख्य][type][bucket]);
पूर्ण

अटल व्योम kyber_completed_request(काष्ठा request *rq, u64 now)
अणु
	काष्ठा kyber_queue_data *kqd = rq->q->elevator->elevator_data;
	काष्ठा kyber_cpu_latency *cpu_latency;
	अचिन्हित पूर्णांक sched_करोमुख्य;
	u64 target;

	sched_करोमुख्य = kyber_sched_करोमुख्य(rq->cmd_flags);
	अगर (sched_करोमुख्य == KYBER_OTHER)
		वापस;

	cpu_latency = get_cpu_ptr(kqd->cpu_latency);
	target = kqd->latency_tarमाला_लो[sched_करोमुख्य];
	add_latency_sample(cpu_latency, sched_करोमुख्य, KYBER_TOTAL_LATENCY,
			   target, now - rq->start_समय_ns);
	add_latency_sample(cpu_latency, sched_करोमुख्य, KYBER_IO_LATENCY, target,
			   now - rq->io_start_समय_ns);
	put_cpu_ptr(kqd->cpu_latency);

	समयr_reduce(&kqd->समयr, jअगरfies + HZ / 10);
पूर्ण

काष्ठा flush_kcq_data अणु
	काष्ठा kyber_hctx_data *khd;
	अचिन्हित पूर्णांक sched_करोमुख्य;
	काष्ठा list_head *list;
पूर्ण;

अटल bool flush_busy_kcq(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr, व्योम *data)
अणु
	काष्ठा flush_kcq_data *flush_data = data;
	काष्ठा kyber_ctx_queue *kcq = &flush_data->khd->kcqs[bitnr];

	spin_lock(&kcq->lock);
	list_splice_tail_init(&kcq->rq_list[flush_data->sched_करोमुख्य],
			      flush_data->list);
	sbiपंचांगap_clear_bit(sb, bitnr);
	spin_unlock(&kcq->lock);

	वापस true;
पूर्ण

अटल व्योम kyber_flush_busy_kcqs(काष्ठा kyber_hctx_data *khd,
				  अचिन्हित पूर्णांक sched_करोमुख्य,
				  काष्ठा list_head *list)
अणु
	काष्ठा flush_kcq_data data = अणु
		.khd = khd,
		.sched_करोमुख्य = sched_करोमुख्य,
		.list = list,
	पूर्ण;

	sbiपंचांगap_क्रम_each_set(&khd->kcq_map[sched_करोमुख्य],
			     flush_busy_kcq, &data);
पूर्ण

अटल पूर्णांक kyber_करोमुख्य_wake(रुको_queue_entry_t *wqe, अचिन्हित mode, पूर्णांक flags,
			     व्योम *key)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = READ_ONCE(wqe->निजी);
	काष्ठा sbq_रुको *रुको = container_of(wqe, काष्ठा sbq_रुको, रुको);

	sbiपंचांगap_del_रुको_queue(रुको);
	blk_mq_run_hw_queue(hctx, true);
	वापस 1;
पूर्ण

अटल पूर्णांक kyber_get_करोमुख्य_token(काष्ठा kyber_queue_data *kqd,
				  काष्ठा kyber_hctx_data *khd,
				  काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अचिन्हित पूर्णांक sched_करोमुख्य = khd->cur_करोमुख्य;
	काष्ठा sbiपंचांगap_queue *करोमुख्य_tokens = &kqd->करोमुख्य_tokens[sched_करोमुख्य];
	काष्ठा sbq_रुको *रुको = &khd->करोमुख्य_रुको[sched_करोमुख्य];
	काष्ठा sbq_रुको_state *ws;
	पूर्णांक nr;

	nr = __sbiपंचांगap_queue_get(करोमुख्य_tokens);

	/*
	 * If we failed to get a करोमुख्य token, make sure the hardware queue is
	 * run when one becomes available. Note that this is serialized on
	 * khd->lock, but we still need to be careful about the waker.
	 */
	अगर (nr < 0 && list_empty_careful(&रुको->रुको.entry)) अणु
		ws = sbq_रुको_ptr(करोमुख्य_tokens,
				  &khd->रुको_index[sched_करोमुख्य]);
		khd->करोमुख्य_ws[sched_करोमुख्य] = ws;
		sbiपंचांगap_add_रुको_queue(करोमुख्य_tokens, ws, रुको);

		/*
		 * Try again in हाल a token was मुक्तd beक्रमe we got on the रुको
		 * queue.
		 */
		nr = __sbiपंचांगap_queue_get(करोमुख्य_tokens);
	पूर्ण

	/*
	 * If we got a token जबतक we were on the रुको queue, हटाओ ourselves
	 * from the रुको queue to ensure that all wake ups make क्रमward
	 * progress. It's possible that the waker alपढ़ोy deleted the entry
	 * between the !list_empty_careful() check and us grabbing the lock, but
	 * list_del_init() is okay with that.
	 */
	अगर (nr >= 0 && !list_empty_careful(&रुको->रुको.entry)) अणु
		ws = khd->करोमुख्य_ws[sched_करोमुख्य];
		spin_lock_irq(&ws->रुको.lock);
		sbiपंचांगap_del_रुको_queue(रुको);
		spin_unlock_irq(&ws->रुको.lock);
	पूर्ण

	वापस nr;
पूर्ण

अटल काष्ठा request *
kyber_dispatch_cur_करोमुख्य(काष्ठा kyber_queue_data *kqd,
			  काष्ठा kyber_hctx_data *khd,
			  काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा list_head *rqs;
	काष्ठा request *rq;
	पूर्णांक nr;

	rqs = &khd->rqs[khd->cur_करोमुख्य];

	/*
	 * If we alपढ़ोy have a flushed request, then we just need to get a
	 * token क्रम it. Otherwise, अगर there are pending requests in the kcqs,
	 * flush the kcqs, but only अगर we can get a token. If not, we should
	 * leave the requests in the kcqs so that they can be merged. Note that
	 * khd->lock serializes the flushes, so अगर we observed any bit set in
	 * the kcq_map, we will always get a request.
	 */
	rq = list_first_entry_or_null(rqs, काष्ठा request, queuelist);
	अगर (rq) अणु
		nr = kyber_get_करोमुख्य_token(kqd, khd, hctx);
		अगर (nr >= 0) अणु
			khd->batching++;
			rq_set_करोमुख्य_token(rq, nr);
			list_del_init(&rq->queuelist);
			वापस rq;
		पूर्ण अन्यथा अणु
			trace_kyber_throttled(kqd->q,
					      kyber_करोमुख्य_names[khd->cur_करोमुख्य]);
		पूर्ण
	पूर्ण अन्यथा अगर (sbiपंचांगap_any_bit_set(&khd->kcq_map[khd->cur_करोमुख्य])) अणु
		nr = kyber_get_करोमुख्य_token(kqd, khd, hctx);
		अगर (nr >= 0) अणु
			kyber_flush_busy_kcqs(khd, khd->cur_करोमुख्य, rqs);
			rq = list_first_entry(rqs, काष्ठा request, queuelist);
			khd->batching++;
			rq_set_करोमुख्य_token(rq, nr);
			list_del_init(&rq->queuelist);
			वापस rq;
		पूर्ण अन्यथा अणु
			trace_kyber_throttled(kqd->q,
					      kyber_करोमुख्य_names[khd->cur_करोमुख्य]);
		पूर्ण
	पूर्ण

	/* There were either no pending requests or no tokens. */
	वापस शून्य;
पूर्ण

अटल काष्ठा request *kyber_dispatch_request(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा kyber_queue_data *kqd = hctx->queue->elevator->elevator_data;
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;
	काष्ठा request *rq;
	पूर्णांक i;

	spin_lock(&khd->lock);

	/*
	 * First, अगर we are still entitled to batch, try to dispatch a request
	 * from the batch.
	 */
	अगर (khd->batching < kyber_batch_size[khd->cur_करोमुख्य]) अणु
		rq = kyber_dispatch_cur_करोमुख्य(kqd, khd, hctx);
		अगर (rq)
			जाओ out;
	पूर्ण

	/*
	 * Either,
	 * 1. We were no दीर्घer entitled to a batch.
	 * 2. The करोमुख्य we were batching didn't have any requests.
	 * 3. The करोमुख्य we were batching was out of tokens.
	 *
	 * Start another batch. Note that this wraps back around to the original
	 * करोमुख्य अगर no other करोमुख्यs have requests or tokens.
	 */
	khd->batching = 0;
	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++) अणु
		अगर (khd->cur_करोमुख्य == KYBER_NUM_DOMAINS - 1)
			khd->cur_करोमुख्य = 0;
		अन्यथा
			khd->cur_करोमुख्य++;

		rq = kyber_dispatch_cur_करोमुख्य(kqd, khd, hctx);
		अगर (rq)
			जाओ out;
	पूर्ण

	rq = शून्य;
out:
	spin_unlock(&khd->lock);
	वापस rq;
पूर्ण

अटल bool kyber_has_work(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;
	पूर्णांक i;

	क्रम (i = 0; i < KYBER_NUM_DOMAINS; i++) अणु
		अगर (!list_empty_careful(&khd->rqs[i]) ||
		    sbiपंचांगap_any_bit_set(&khd->kcq_map[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा KYBER_LAT_SHOW_STORE(करोमुख्य, name)				\
अटल sमाप_प्रकार kyber_##name##_lat_show(काष्ठा elevator_queue *e,	\
				       अक्षर *page)			\
अणु									\
	काष्ठा kyber_queue_data *kqd = e->elevator_data;		\
									\
	वापस प्र_लिखो(page, "%llu\n", kqd->latency_tarमाला_लो[करोमुख्य]);	\
पूर्ण									\
									\
अटल sमाप_प्रकार kyber_##name##_lat_store(काष्ठा elevator_queue *e,	\
					स्थिर अक्षर *page, माप_प्रकार count)	\
अणु									\
	काष्ठा kyber_queue_data *kqd = e->elevator_data;		\
	अचिन्हित दीर्घ दीर्घ nsec;					\
	पूर्णांक ret;							\
									\
	ret = kम_से_अदीर्घl(page, 10, &nsec);				\
	अगर (ret)							\
		वापस ret;						\
									\
	kqd->latency_tarमाला_लो[करोमुख्य] = nsec;				\
									\
	वापस count;							\
पूर्ण
KYBER_LAT_SHOW_STORE(KYBER_READ, पढ़ो);
KYBER_LAT_SHOW_STORE(KYBER_WRITE, ग_लिखो);
#अघोषित KYBER_LAT_SHOW_STORE

#घोषणा KYBER_LAT_ATTR(op) __ATTR(op##_lat_nsec, 0644, kyber_##op##_lat_show, kyber_##op##_lat_store)
अटल काष्ठा elv_fs_entry kyber_sched_attrs[] = अणु
	KYBER_LAT_ATTR(पढ़ो),
	KYBER_LAT_ATTR(ग_लिखो),
	__ATTR_शून्य
पूर्ण;
#अघोषित KYBER_LAT_ATTR

#अगर_घोषित CONFIG_BLK_DEBUG_FS
#घोषणा KYBER_DEBUGFS_DOMAIN_ATTRS(करोमुख्य, name)			\
अटल पूर्णांक kyber_##name##_tokens_show(व्योम *data, काष्ठा seq_file *m)	\
अणु									\
	काष्ठा request_queue *q = data;					\
	काष्ठा kyber_queue_data *kqd = q->elevator->elevator_data;	\
									\
	sbiपंचांगap_queue_show(&kqd->करोमुख्य_tokens[करोमुख्य], m);		\
	वापस 0;							\
पूर्ण									\
									\
अटल व्योम *kyber_##name##_rqs_start(काष्ठा seq_file *m, loff_t *pos)	\
	__acquires(&khd->lock)						\
अणु									\
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;			\
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;			\
									\
	spin_lock(&khd->lock);						\
	वापस seq_list_start(&khd->rqs[करोमुख्य], *pos);			\
पूर्ण									\
									\
अटल व्योम *kyber_##name##_rqs_next(काष्ठा seq_file *m, व्योम *v,	\
				     loff_t *pos)			\
अणु									\
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;			\
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;			\
									\
	वापस seq_list_next(v, &khd->rqs[करोमुख्य], pos);		\
पूर्ण									\
									\
अटल व्योम kyber_##name##_rqs_stop(काष्ठा seq_file *m, व्योम *v)	\
	__releases(&khd->lock)						\
अणु									\
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;			\
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;			\
									\
	spin_unlock(&khd->lock);					\
पूर्ण									\
									\
अटल स्थिर काष्ठा seq_operations kyber_##name##_rqs_seq_ops = अणु	\
	.start	= kyber_##name##_rqs_start,				\
	.next	= kyber_##name##_rqs_next,				\
	.stop	= kyber_##name##_rqs_stop,				\
	.show	= blk_mq_debugfs_rq_show,				\
पूर्ण;									\
									\
अटल पूर्णांक kyber_##name##_रुकोing_show(व्योम *data, काष्ठा seq_file *m)	\
अणु									\
	काष्ठा blk_mq_hw_ctx *hctx = data;				\
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;			\
	रुको_queue_entry_t *रुको = &khd->करोमुख्य_रुको[करोमुख्य].रुको;	\
									\
	seq_म_लिखो(m, "%d\n", !list_empty_careful(&रुको->entry));	\
	वापस 0;							\
पूर्ण
KYBER_DEBUGFS_DOMAIN_ATTRS(KYBER_READ, पढ़ो)
KYBER_DEBUGFS_DOMAIN_ATTRS(KYBER_WRITE, ग_लिखो)
KYBER_DEBUGFS_DOMAIN_ATTRS(KYBER_DISCARD, discard)
KYBER_DEBUGFS_DOMAIN_ATTRS(KYBER_OTHER, other)
#अघोषित KYBER_DEBUGFS_DOMAIN_ATTRS

अटल पूर्णांक kyber_async_depth_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	काष्ठा kyber_queue_data *kqd = q->elevator->elevator_data;

	seq_म_लिखो(m, "%u\n", kqd->async_depth);
	वापस 0;
पूर्ण

अटल पूर्णांक kyber_cur_करोमुख्य_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;

	seq_म_लिखो(m, "%s\n", kyber_करोमुख्य_names[khd->cur_करोमुख्य]);
	वापस 0;
पूर्ण

अटल पूर्णांक kyber_batching_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा kyber_hctx_data *khd = hctx->sched_data;

	seq_म_लिखो(m, "%u\n", khd->batching);
	वापस 0;
पूर्ण

#घोषणा KYBER_QUEUE_DOMAIN_ATTRS(name)	\
	अणु#name "_tokens", 0400, kyber_##name##_tokens_showपूर्ण
अटल स्थिर काष्ठा blk_mq_debugfs_attr kyber_queue_debugfs_attrs[] = अणु
	KYBER_QUEUE_DOMAIN_ATTRS(पढ़ो),
	KYBER_QUEUE_DOMAIN_ATTRS(ग_लिखो),
	KYBER_QUEUE_DOMAIN_ATTRS(discard),
	KYBER_QUEUE_DOMAIN_ATTRS(other),
	अणु"async_depth", 0400, kyber_async_depth_showपूर्ण,
	अणुपूर्ण,
पूर्ण;
#अघोषित KYBER_QUEUE_DOMAIN_ATTRS

#घोषणा KYBER_HCTX_DOMAIN_ATTRS(name)					\
	अणु#name "_rqs", 0400, .seq_ops = &kyber_##name##_rqs_seq_opsपूर्ण,	\
	अणु#name "_waiting", 0400, kyber_##name##_रुकोing_showपूर्ण
अटल स्थिर काष्ठा blk_mq_debugfs_attr kyber_hctx_debugfs_attrs[] = अणु
	KYBER_HCTX_DOMAIN_ATTRS(पढ़ो),
	KYBER_HCTX_DOMAIN_ATTRS(ग_लिखो),
	KYBER_HCTX_DOMAIN_ATTRS(discard),
	KYBER_HCTX_DOMAIN_ATTRS(other),
	अणु"cur_domain", 0400, kyber_cur_करोमुख्य_showपूर्ण,
	अणु"batching", 0400, kyber_batching_showपूर्ण,
	अणुपूर्ण,
पूर्ण;
#अघोषित KYBER_HCTX_DOMAIN_ATTRS
#पूर्ण_अगर

अटल काष्ठा elevator_type kyber_sched = अणु
	.ops = अणु
		.init_sched = kyber_init_sched,
		.निकास_sched = kyber_निकास_sched,
		.init_hctx = kyber_init_hctx,
		.निकास_hctx = kyber_निकास_hctx,
		.limit_depth = kyber_limit_depth,
		.bio_merge = kyber_bio_merge,
		.prepare_request = kyber_prepare_request,
		.insert_requests = kyber_insert_requests,
		.finish_request = kyber_finish_request,
		.requeue_request = kyber_finish_request,
		.completed_request = kyber_completed_request,
		.dispatch_request = kyber_dispatch_request,
		.has_work = kyber_has_work,
		.depth_updated = kyber_depth_updated,
	पूर्ण,
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	.queue_debugfs_attrs = kyber_queue_debugfs_attrs,
	.hctx_debugfs_attrs = kyber_hctx_debugfs_attrs,
#पूर्ण_अगर
	.elevator_attrs = kyber_sched_attrs,
	.elevator_name = "kyber",
	.elevator_features = ELEVATOR_F_MQ_AWARE,
	.elevator_owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init kyber_init(व्योम)
अणु
	वापस elv_रेजिस्टर(&kyber_sched);
पूर्ण

अटल व्योम __निकास kyber_निकास(व्योम)
अणु
	elv_unरेजिस्टर(&kyber_sched);
पूर्ण

module_init(kyber_init);
module_निकास(kyber_निकास);

MODULE_AUTHOR("Omar Sandoval");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kyber I/O scheduler");
