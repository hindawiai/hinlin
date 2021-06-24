<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/sched/sch_hhf.c		Heavy-Hitter Filter (HHF)
 *
 * Copyright (C) 2013 Terry Lam <vtlam@google.com>
 * Copyright (C) 2013 Nandita Dukkipati <nanditad@google.com>
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/siphash.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sock.h>

/*	Heavy-Hitter Filter (HHF)
 *
 * Principles :
 * Flows are classअगरied पूर्णांकo two buckets: non-heavy-hitter and heavy-hitter
 * buckets. Initially, a new flow starts as non-heavy-hitter. Once classअगरied
 * as heavy-hitter, it is immediately चयनed to the heavy-hitter bucket.
 * The buckets are dequeued by a Weighted Deficit Round Robin (WDRR) scheduler,
 * in which the heavy-hitter bucket is served with less weight.
 * In other words, non-heavy-hitters (e.g., लघु bursts of critical traffic)
 * are isolated from heavy-hitters (e.g., persistent bulk traffic) and also have
 * higher share of bandwidth.
 *
 * To capture heavy-hitters, we use the "multi-stage filter" algorithm in the
 * following paper:
 * [EV02] C. Estan and G. Varghese, "New Directions in Traffic Measurement and
 * Accounting", in ACM SIGCOMM, 2002.
 *
 * Conceptually, a multi-stage filter comprises k independent hash functions
 * and k counter arrays. Packets are indexed पूर्णांकo k counter arrays by k hash
 * functions, respectively. The counters are then increased by the packet sizes.
 * Thereक्रमe,
 *    - For a heavy-hitter flow: *all* of its k array counters must be large.
 *    - For a non-heavy-hitter flow: some of its k array counters can be large
 *      due to hash collision with other small flows; however, with high
 *      probability, not *all* k counters are large.
 *
 * By the design of the multi-stage filter algorithm, the false negative rate
 * (heavy-hitters getting away uncaptured) is zero. However, the algorithm is
 * susceptible to false positives (non-heavy-hitters mistakenly classअगरied as
 * heavy-hitters).
 * Thereक्रमe, we also implement the following optimizations to reduce false
 * positives by aव्योमing unnecessary increment of the counter values:
 *    - Optimization O1: once a heavy-hitter is identअगरied, its bytes are not
 *        accounted in the array counters. This technique is called "shielding"
 *        in Section 3.3.1 of [EV02].
 *    - Optimization O2: conservative update of counters
 *                       (Section 3.3.2 of [EV02]),
 *        New counter value = max अणुold counter value,
 *                                 smallest counter value + packet bytesपूर्ण
 *
 * Finally, we refresh the counters periodically since otherwise the counter
 * values will keep accumulating.
 *
 * Once a flow is classअगरied as heavy-hitter, we also save its per-flow state
 * in an exact-matching flow table so that its subsequent packets can be
 * dispatched to the heavy-hitter bucket accordingly.
 *
 *
 * At a high level, this qdisc works as follows:
 * Given a packet p:
 *   - If the flow-id of p (e.g., TCP 5-tuple) is alपढ़ोy in the exact-matching
 *     heavy-hitter flow table, denoted table T, then send p to the heavy-hitter
 *     bucket.
 *   - Otherwise, क्रमward p to the multi-stage filter, denoted filter F
 *        + If F decides that p beदीर्घs to a non-heavy-hitter flow, then send p
 *          to the non-heavy-hitter bucket.
 *        + Otherwise, अगर F decides that p beदीर्घs to a new heavy-hitter flow,
 *          then set up a new flow entry क्रम the flow-id of p in the table T and
 *          send p to the heavy-hitter bucket.
 *
 * In this implementation:
 *   - T is a fixed-size hash-table with 1024 entries. Hash collision is
 *     resolved by linked-list chaining.
 *   - F has four counter arrays, each array containing 1024 32-bit counters.
 *     That means 4 * 1024 * 32 bits = 16KB of memory.
 *   - Since each array in F contains 1024 counters, 10 bits are sufficient to
 *     index पूर्णांकo each array.
 *     Hence, instead of having four hash functions, we chop the 32-bit
 *     skb-hash पूर्णांकo three 10-bit chunks, and the reमुख्यing 10-bit chunk is
 *     computed as XOR sum of those three chunks.
 *   - We need to clear the counter arrays periodically; however, directly
 *     स_रखोting 16KB of memory can lead to cache eviction and unwanted delay.
 *     So by representing each counter by a valid bit, we only need to reset
 *     4K of 1 bit (i.e. 512 bytes) instead of 16KB of memory.
 *   - The Deficit Round Robin engine is taken from fq_codel implementation
 *     (net/sched/sch_fq_codel.c). Note that wdrr_bucket corresponds to
 *     fq_codel_flow in fq_codel implementation.
 *
 */

/* Non-configurable parameters */
#घोषणा HH_FLOWS_CNT	 1024  /* number of entries in exact-matching table T */
#घोषणा HHF_ARRAYS_CNT	 4     /* number of arrays in multi-stage filter F */
#घोषणा HHF_ARRAYS_LEN	 1024  /* number of counters in each array of F */
#घोषणा HHF_BIT_MASK_LEN 10    /* masking 10 bits */
#घोषणा HHF_BIT_MASK	 0x3FF /* biपंचांगask of 10 bits */

#घोषणा WDRR_BUCKET_CNT  2     /* two buckets क्रम Weighted DRR */
क्रमागत wdrr_bucket_idx अणु
	WDRR_BUCKET_FOR_HH	= 0, /* bucket id क्रम heavy-hitters */
	WDRR_BUCKET_FOR_NON_HH	= 1  /* bucket id क्रम non-heavy-hitters */
पूर्ण;

#घोषणा hhf_समय_beक्रमe(a, b)	\
	(typecheck(u32, a) && typecheck(u32, b) && ((s32)((a) - (b)) < 0))

/* Heavy-hitter per-flow state */
काष्ठा hh_flow_state अणु
	u32		 hash_id;	/* hash of flow-id (e.g. TCP 5-tuple) */
	u32		 hit_बारtamp;	/* last समय heavy-hitter was seen */
	काष्ठा list_head flowchain;	/* chaining under hash collision */
पूर्ण;

/* Weighted Deficit Round Robin (WDRR) scheduler */
काष्ठा wdrr_bucket अणु
	काष्ठा sk_buff	  *head;
	काष्ठा sk_buff	  *tail;
	काष्ठा list_head  bucketchain;
	पूर्णांक		  deficit;
पूर्ण;

काष्ठा hhf_sched_data अणु
	काष्ठा wdrr_bucket buckets[WDRR_BUCKET_CNT];
	siphash_key_t	   perturbation;   /* hash perturbation */
	u32		   quantum;        /* psched_mtu(qdisc_dev(sch)); */
	u32		   drop_overlimit; /* number of बार max qdisc packet
					    * limit was hit
					    */
	काष्ठा list_head   *hh_flows;       /* table T (currently active HHs) */
	u32		   hh_flows_limit;            /* max active HH allocs */
	u32		   hh_flows_overlimit; /* num of disallowed HH allocs */
	u32		   hh_flows_total_cnt;          /* total admitted HHs */
	u32		   hh_flows_current_cnt;        /* total current HHs  */
	u32		   *hhf_arrays[HHF_ARRAYS_CNT]; /* HH filter F */
	u32		   hhf_arrays_reset_बारtamp;  /* last समय hhf_arrays
							 * was reset
							 */
	अचिन्हित दीर्घ	   *hhf_valid_bits[HHF_ARRAYS_CNT]; /* shaकरोw valid bits
							     * of hhf_arrays
							     */
	/* Similar to the "new_flows" vs. "old_flows" concept in fq_codel DRR */
	काष्ठा list_head   new_buckets; /* list of new buckets */
	काष्ठा list_head   old_buckets; /* list of old buckets */

	/* Configurable HHF parameters */
	u32		   hhf_reset_समयout; /* पूर्णांकerval to reset counter
					       * arrays in filter F
					       * (शेष 40ms)
					       */
	u32		   hhf_admit_bytes;   /* counter thresh to classअगरy as
					       * HH (शेष 128KB).
					       * With these शेष values,
					       * 128KB / 40ms = 25 Mbps
					       * i.e., we expect to capture HHs
					       * sending > 25 Mbps.
					       */
	u32		   hhf_evict_समयout; /* aging threshold to evict idle
					       * HHs out of table T. This should
					       * be large enough to aव्योम
					       * reordering during HH eviction.
					       * (शेष 1s)
					       */
	u32		   hhf_non_hh_weight; /* WDRR weight क्रम non-HHs
					       * (शेष 2,
					       *  i.e., non-HH : HH = 2 : 1)
					       */
पूर्ण;

अटल u32 hhf_समय_stamp(व्योम)
अणु
	वापस jअगरfies;
पूर्ण

/* Looks up a heavy-hitter flow in a chaining list of table T. */
अटल काष्ठा hh_flow_state *seek_list(स्थिर u32 hash,
				       काष्ठा list_head *head,
				       काष्ठा hhf_sched_data *q)
अणु
	काष्ठा hh_flow_state *flow, *next;
	u32 now = hhf_समय_stamp();

	अगर (list_empty(head))
		वापस शून्य;

	list_क्रम_each_entry_safe(flow, next, head, flowchain) अणु
		u32 prev = flow->hit_बारtamp + q->hhf_evict_समयout;

		अगर (hhf_समय_beक्रमe(prev, now)) अणु
			/* Delete expired heavy-hitters, but preserve one entry
			 * to aव्योम kzalloc() when next समय this slot is hit.
			 */
			अगर (list_is_last(&flow->flowchain, head))
				वापस शून्य;
			list_del(&flow->flowchain);
			kमुक्त(flow);
			q->hh_flows_current_cnt--;
		पूर्ण अन्यथा अगर (flow->hash_id == hash) अणु
			वापस flow;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Returns a flow state entry क्रम a new heavy-hitter.  Either reuses an expired
 * entry or dynamically alloc a new entry.
 */
अटल काष्ठा hh_flow_state *alloc_new_hh(काष्ठा list_head *head,
					  काष्ठा hhf_sched_data *q)
अणु
	काष्ठा hh_flow_state *flow;
	u32 now = hhf_समय_stamp();

	अगर (!list_empty(head)) अणु
		/* Find an expired heavy-hitter flow entry. */
		list_क्रम_each_entry(flow, head, flowchain) अणु
			u32 prev = flow->hit_बारtamp + q->hhf_evict_समयout;

			अगर (hhf_समय_beक्रमe(prev, now))
				वापस flow;
		पूर्ण
	पूर्ण

	अगर (q->hh_flows_current_cnt >= q->hh_flows_limit) अणु
		q->hh_flows_overlimit++;
		वापस शून्य;
	पूर्ण
	/* Create new entry. */
	flow = kzalloc(माप(काष्ठा hh_flow_state), GFP_ATOMIC);
	अगर (!flow)
		वापस शून्य;

	q->hh_flows_current_cnt++;
	INIT_LIST_HEAD(&flow->flowchain);
	list_add_tail(&flow->flowchain, head);

	वापस flow;
पूर्ण

/* Assigns packets to WDRR buckets.  Implements a multi-stage filter to
 * classअगरy heavy-hitters.
 */
अटल क्रमागत wdrr_bucket_idx hhf_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	u32 पंचांगp_hash, hash;
	u32 xorsum, filter_pos[HHF_ARRAYS_CNT], flow_pos;
	काष्ठा hh_flow_state *flow;
	u32 pkt_len, min_hhf_val;
	पूर्णांक i;
	u32 prev;
	u32 now = hhf_समय_stamp();

	/* Reset the HHF counter arrays अगर this is the right समय. */
	prev = q->hhf_arrays_reset_बारtamp + q->hhf_reset_समयout;
	अगर (hhf_समय_beक्रमe(prev, now)) अणु
		क्रम (i = 0; i < HHF_ARRAYS_CNT; i++)
			biपंचांगap_zero(q->hhf_valid_bits[i], HHF_ARRAYS_LEN);
		q->hhf_arrays_reset_बारtamp = now;
	पूर्ण

	/* Get hashed flow-id of the skb. */
	hash = skb_get_hash_perturb(skb, &q->perturbation);

	/* Check अगर this packet beदीर्घs to an alपढ़ोy established HH flow. */
	flow_pos = hash & HHF_BIT_MASK;
	flow = seek_list(hash, &q->hh_flows[flow_pos], q);
	अगर (flow) अणु /* found its HH flow */
		flow->hit_बारtamp = now;
		वापस WDRR_BUCKET_FOR_HH;
	पूर्ण

	/* Now pass the packet through the multi-stage filter. */
	पंचांगp_hash = hash;
	xorsum = 0;
	क्रम (i = 0; i < HHF_ARRAYS_CNT - 1; i++) अणु
		/* Split the skb_hash पूर्णांकo three 10-bit chunks. */
		filter_pos[i] = पंचांगp_hash & HHF_BIT_MASK;
		xorsum ^= filter_pos[i];
		पंचांगp_hash >>= HHF_BIT_MASK_LEN;
	पूर्ण
	/* The last chunk is computed as XOR sum of other chunks. */
	filter_pos[HHF_ARRAYS_CNT - 1] = xorsum ^ पंचांगp_hash;

	pkt_len = qdisc_pkt_len(skb);
	min_hhf_val = ~0U;
	क्रम (i = 0; i < HHF_ARRAYS_CNT; i++) अणु
		u32 val;

		अगर (!test_bit(filter_pos[i], q->hhf_valid_bits[i])) अणु
			q->hhf_arrays[i][filter_pos[i]] = 0;
			__set_bit(filter_pos[i], q->hhf_valid_bits[i]);
		पूर्ण

		val = q->hhf_arrays[i][filter_pos[i]] + pkt_len;
		अगर (min_hhf_val > val)
			min_hhf_val = val;
	पूर्ण

	/* Found a new HH अगरf all counter values > HH admit threshold. */
	अगर (min_hhf_val > q->hhf_admit_bytes) अणु
		/* Just captured a new heavy-hitter. */
		flow = alloc_new_hh(&q->hh_flows[flow_pos], q);
		अगर (!flow) /* memory alloc problem */
			वापस WDRR_BUCKET_FOR_NON_HH;
		flow->hash_id = hash;
		flow->hit_बारtamp = now;
		q->hh_flows_total_cnt++;

		/* By वापसing without updating counters in q->hhf_arrays,
		 * we implicitly implement "shielding" (see Optimization O1).
		 */
		वापस WDRR_BUCKET_FOR_HH;
	पूर्ण

	/* Conservative update of HHF arrays (see Optimization O2). */
	क्रम (i = 0; i < HHF_ARRAYS_CNT; i++) अणु
		अगर (q->hhf_arrays[i][filter_pos[i]] < min_hhf_val)
			q->hhf_arrays[i][filter_pos[i]] = min_hhf_val;
	पूर्ण
	वापस WDRR_BUCKET_FOR_NON_HH;
पूर्ण

/* Removes one skb from head of bucket. */
अटल काष्ठा sk_buff *dequeue_head(काष्ठा wdrr_bucket *bucket)
अणु
	काष्ठा sk_buff *skb = bucket->head;

	bucket->head = skb->next;
	skb_mark_not_on_list(skb);
	वापस skb;
पूर्ण

/* Tail-adds skb to bucket. */
अटल व्योम bucket_add(काष्ठा wdrr_bucket *bucket, काष्ठा sk_buff *skb)
अणु
	अगर (bucket->head == शून्य)
		bucket->head = skb;
	अन्यथा
		bucket->tail->next = skb;
	bucket->tail = skb;
	skb->next = शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक hhf_drop(काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	काष्ठा wdrr_bucket *bucket;

	/* Always try to drop from heavy-hitters first. */
	bucket = &q->buckets[WDRR_BUCKET_FOR_HH];
	अगर (!bucket->head)
		bucket = &q->buckets[WDRR_BUCKET_FOR_NON_HH];

	अगर (bucket->head) अणु
		काष्ठा sk_buff *skb = dequeue_head(bucket);

		sch->q.qlen--;
		qdisc_qstats_backlog_dec(sch, skb);
		qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण

	/* Return id of the bucket from which the packet was dropped. */
	वापस bucket - q->buckets;
पूर्ण

अटल पूर्णांक hhf_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	क्रमागत wdrr_bucket_idx idx;
	काष्ठा wdrr_bucket *bucket;
	अचिन्हित पूर्णांक prev_backlog;

	idx = hhf_classअगरy(skb, sch);

	bucket = &q->buckets[idx];
	bucket_add(bucket, skb);
	qdisc_qstats_backlog_inc(sch, skb);

	अगर (list_empty(&bucket->bucketchain)) अणु
		अचिन्हित पूर्णांक weight;

		/* The logic of new_buckets vs. old_buckets is the same as
		 * new_flows vs. old_flows in the implementation of fq_codel,
		 * i.e., लघु bursts of non-HHs should have strict priority.
		 */
		अगर (idx == WDRR_BUCKET_FOR_HH) अणु
			/* Always move heavy-hitters to old bucket. */
			weight = 1;
			list_add_tail(&bucket->bucketchain, &q->old_buckets);
		पूर्ण अन्यथा अणु
			weight = q->hhf_non_hh_weight;
			list_add_tail(&bucket->bucketchain, &q->new_buckets);
		पूर्ण
		bucket->deficit = weight * q->quantum;
	पूर्ण
	अगर (++sch->q.qlen <= sch->limit)
		वापस NET_XMIT_SUCCESS;

	prev_backlog = sch->qstats.backlog;
	q->drop_overlimit++;
	/* Return Congestion Notअगरication only अगर we dropped a packet from this
	 * bucket.
	 */
	अगर (hhf_drop(sch, to_मुक्त) == idx)
		वापस NET_XMIT_CN;

	/* As we dropped a packet, better let upper stack know this. */
	qdisc_tree_reduce_backlog(sch, 1, prev_backlog - sch->qstats.backlog);
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल काष्ठा sk_buff *hhf_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा wdrr_bucket *bucket;
	काष्ठा list_head *head;

begin:
	head = &q->new_buckets;
	अगर (list_empty(head)) अणु
		head = &q->old_buckets;
		अगर (list_empty(head))
			वापस शून्य;
	पूर्ण
	bucket = list_first_entry(head, काष्ठा wdrr_bucket, bucketchain);

	अगर (bucket->deficit <= 0) अणु
		पूर्णांक weight = (bucket - q->buckets == WDRR_BUCKET_FOR_HH) ?
			      1 : q->hhf_non_hh_weight;

		bucket->deficit += weight * q->quantum;
		list_move_tail(&bucket->bucketchain, &q->old_buckets);
		जाओ begin;
	पूर्ण

	अगर (bucket->head) अणु
		skb = dequeue_head(bucket);
		sch->q.qlen--;
		qdisc_qstats_backlog_dec(sch, skb);
	पूर्ण

	अगर (!skb) अणु
		/* Force a pass through old_buckets to prevent starvation. */
		अगर ((head == &q->new_buckets) && !list_empty(&q->old_buckets))
			list_move_tail(&bucket->bucketchain, &q->old_buckets);
		अन्यथा
			list_del_init(&bucket->bucketchain);
		जाओ begin;
	पूर्ण
	qdisc_bstats_update(sch, skb);
	bucket->deficit -= qdisc_pkt_len(skb);

	वापस skb;
पूर्ण

अटल व्योम hhf_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = hhf_dequeue(sch)) != शून्य)
		rtnl_kमुक्त_skbs(skb, skb);
पूर्ण

अटल व्योम hhf_destroy(काष्ठा Qdisc *sch)
अणु
	पूर्णांक i;
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);

	क्रम (i = 0; i < HHF_ARRAYS_CNT; i++) अणु
		kvमुक्त(q->hhf_arrays[i]);
		kvमुक्त(q->hhf_valid_bits[i]);
	पूर्ण

	अगर (!q->hh_flows)
		वापस;

	क्रम (i = 0; i < HH_FLOWS_CNT; i++) अणु
		काष्ठा hh_flow_state *flow, *next;
		काष्ठा list_head *head = &q->hh_flows[i];

		अगर (list_empty(head))
			जारी;
		list_क्रम_each_entry_safe(flow, next, head, flowchain) अणु
			list_del(&flow->flowchain);
			kमुक्त(flow);
		पूर्ण
	पूर्ण
	kvमुक्त(q->hh_flows);
पूर्ण

अटल स्थिर काष्ठा nla_policy hhf_policy[TCA_HHF_MAX + 1] = अणु
	[TCA_HHF_BACKLOG_LIMIT]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_QUANTUM]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_HH_FLOWS_LIMIT] = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_RESET_TIMEOUT]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_ADMIT_BYTES]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_EVICT_TIMEOUT]	 = अणु .type = NLA_U32 पूर्ण,
	[TCA_HHF_NON_HH_WEIGHT]	 = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक hhf_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_HHF_MAX + 1];
	अचिन्हित पूर्णांक qlen, prev_backlog;
	पूर्णांक err;
	u64 non_hh_quantum;
	u32 new_quantum = q->quantum;
	u32 new_hhf_non_hh_weight = q->hhf_non_hh_weight;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_HHF_MAX, opt, hhf_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_HHF_QUANTUM])
		new_quantum = nla_get_u32(tb[TCA_HHF_QUANTUM]);

	अगर (tb[TCA_HHF_NON_HH_WEIGHT])
		new_hhf_non_hh_weight = nla_get_u32(tb[TCA_HHF_NON_HH_WEIGHT]);

	non_hh_quantum = (u64)new_quantum * new_hhf_non_hh_weight;
	अगर (non_hh_quantum == 0 || non_hh_quantum > पूर्णांक_उच्च)
		वापस -EINVAL;

	sch_tree_lock(sch);

	अगर (tb[TCA_HHF_BACKLOG_LIMIT])
		sch->limit = nla_get_u32(tb[TCA_HHF_BACKLOG_LIMIT]);

	q->quantum = new_quantum;
	q->hhf_non_hh_weight = new_hhf_non_hh_weight;

	अगर (tb[TCA_HHF_HH_FLOWS_LIMIT])
		q->hh_flows_limit = nla_get_u32(tb[TCA_HHF_HH_FLOWS_LIMIT]);

	अगर (tb[TCA_HHF_RESET_TIMEOUT]) अणु
		u32 us = nla_get_u32(tb[TCA_HHF_RESET_TIMEOUT]);

		q->hhf_reset_समयout = usecs_to_jअगरfies(us);
	पूर्ण

	अगर (tb[TCA_HHF_ADMIT_BYTES])
		q->hhf_admit_bytes = nla_get_u32(tb[TCA_HHF_ADMIT_BYTES]);

	अगर (tb[TCA_HHF_EVICT_TIMEOUT]) अणु
		u32 us = nla_get_u32(tb[TCA_HHF_EVICT_TIMEOUT]);

		q->hhf_evict_समयout = usecs_to_jअगरfies(us);
	पूर्ण

	qlen = sch->q.qlen;
	prev_backlog = sch->qstats.backlog;
	जबतक (sch->q.qlen > sch->limit) अणु
		काष्ठा sk_buff *skb = hhf_dequeue(sch);

		rtnl_kमुक्त_skbs(skb, skb);
	पूर्ण
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen,
				  prev_backlog - sch->qstats.backlog);

	sch_tree_unlock(sch);
	वापस 0;
पूर्ण

अटल पूर्णांक hhf_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	पूर्णांक i;

	sch->limit = 1000;
	q->quantum = psched_mtu(qdisc_dev(sch));
	get_अक्रमom_bytes(&q->perturbation, माप(q->perturbation));
	INIT_LIST_HEAD(&q->new_buckets);
	INIT_LIST_HEAD(&q->old_buckets);

	/* Configurable HHF parameters */
	q->hhf_reset_समयout = HZ / 25; /* 40  ms */
	q->hhf_admit_bytes = 131072;    /* 128 KB */
	q->hhf_evict_समयout = HZ;      /* 1  sec */
	q->hhf_non_hh_weight = 2;

	अगर (opt) अणु
		पूर्णांक err = hhf_change(sch, opt, extack);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (!q->hh_flows) अणु
		/* Initialize heavy-hitter flow table. */
		q->hh_flows = kvसुस्मृति(HH_FLOWS_CNT, माप(काष्ठा list_head),
				       GFP_KERNEL);
		अगर (!q->hh_flows)
			वापस -ENOMEM;
		क्रम (i = 0; i < HH_FLOWS_CNT; i++)
			INIT_LIST_HEAD(&q->hh_flows[i]);

		/* Cap max active HHs at twice len of hh_flows table. */
		q->hh_flows_limit = 2 * HH_FLOWS_CNT;
		q->hh_flows_overlimit = 0;
		q->hh_flows_total_cnt = 0;
		q->hh_flows_current_cnt = 0;

		/* Initialize heavy-hitter filter arrays. */
		क्रम (i = 0; i < HHF_ARRAYS_CNT; i++) अणु
			q->hhf_arrays[i] = kvसुस्मृति(HHF_ARRAYS_LEN,
						    माप(u32),
						    GFP_KERNEL);
			अगर (!q->hhf_arrays[i]) अणु
				/* Note: hhf_destroy() will be called
				 * by our caller.
				 */
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		q->hhf_arrays_reset_बारtamp = hhf_समय_stamp();

		/* Initialize valid bits of heavy-hitter filter arrays. */
		क्रम (i = 0; i < HHF_ARRAYS_CNT; i++) अणु
			q->hhf_valid_bits[i] = kvzalloc(HHF_ARRAYS_LEN /
							  BITS_PER_BYTE, GFP_KERNEL);
			अगर (!q->hhf_valid_bits[i]) अणु
				/* Note: hhf_destroy() will be called
				 * by our caller.
				 */
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		/* Initialize Weighted DRR buckets. */
		क्रम (i = 0; i < WDRR_BUCKET_CNT; i++) अणु
			काष्ठा wdrr_bucket *bucket = q->buckets + i;

			INIT_LIST_HEAD(&bucket->bucketchain);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hhf_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_HHF_BACKLOG_LIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_HHF_QUANTUM, q->quantum) ||
	    nla_put_u32(skb, TCA_HHF_HH_FLOWS_LIMIT, q->hh_flows_limit) ||
	    nla_put_u32(skb, TCA_HHF_RESET_TIMEOUT,
			jअगरfies_to_usecs(q->hhf_reset_समयout)) ||
	    nla_put_u32(skb, TCA_HHF_ADMIT_BYTES, q->hhf_admit_bytes) ||
	    nla_put_u32(skb, TCA_HHF_EVICT_TIMEOUT,
			jअगरfies_to_usecs(q->hhf_evict_समयout)) ||
	    nla_put_u32(skb, TCA_HHF_NON_HH_WEIGHT, q->hhf_non_hh_weight))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक hhf_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा hhf_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_hhf_xstats st = अणु
		.drop_overlimit = q->drop_overlimit,
		.hh_overlimit	= q->hh_flows_overlimit,
		.hh_tot_count	= q->hh_flows_total_cnt,
		.hh_cur_count	= q->hh_flows_current_cnt,
	पूर्ण;

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल काष्ठा Qdisc_ops hhf_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"hhf",
	.priv_size	=	माप(काष्ठा hhf_sched_data),

	.enqueue	=	hhf_enqueue,
	.dequeue	=	hhf_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	hhf_init,
	.reset		=	hhf_reset,
	.destroy	=	hhf_destroy,
	.change		=	hhf_change,
	.dump		=	hhf_dump,
	.dump_stats	=	hhf_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init hhf_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&hhf_qdisc_ops);
पूर्ण

अटल व्योम __निकास hhf_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&hhf_qdisc_ops);
पूर्ण

module_init(hhf_module_init)
module_निकास(hhf_module_निकास)
MODULE_AUTHOR("Terry Lam");
MODULE_AUTHOR("Nandita Dukkipati");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Heavy-Hitter Filter (HHF)");
