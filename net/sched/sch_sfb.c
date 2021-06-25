<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_sfb.c	  Stochastic Fair Blue
 *
 * Copyright (c) 2008-2011 Juliusz Chroboczek <jch@pps.jussieu.fr>
 * Copyright (c) 2011 Eric Dumazet <eric.dumazet@gmail.com>
 *
 * W. Feng, D. Kandlur, D. Saha, K. Shin. Blue:
 * A New Class of Active Queue Management Algorithms.
 * U. Michigan CSE-TR-387-99, April 1999.
 *
 * http://www.thefengs.com/wuchang/blue/CSE-TR-387-99.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/siphash.h>
#समावेश <net/ip.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/inet_ecn.h>

/*
 * SFB uses two B[l][n] : L x N arrays of bins (L levels, N bins per level)
 * This implementation uses L = 8 and N = 16
 * This permits us to split one 32bit hash (provided per packet by rxhash or
 * बाह्यal classअगरier) पूर्णांकo 8 subhashes of 4 bits.
 */
#घोषणा SFB_BUCKET_SHIFT 4
#घोषणा SFB_NUMBUCKETS	(1 << SFB_BUCKET_SHIFT) /* N bins per Level */
#घोषणा SFB_BUCKET_MASK (SFB_NUMBUCKETS - 1)
#घोषणा SFB_LEVELS	(32 / SFB_BUCKET_SHIFT) /* L */

/* SFB algo uses a भव queue, named "bin" */
काष्ठा sfb_bucket अणु
	u16		qlen; /* length of भव queue */
	u16		p_mark; /* marking probability */
पूर्ण;

/* We use a द्विगुन buffering right beक्रमe hash change
 * (Section 4.4 of SFB reference : moving hash functions)
 */
काष्ठा sfb_bins अणु
	siphash_key_t	  perturbation; /* siphash key */
	काष्ठा sfb_bucket bins[SFB_LEVELS][SFB_NUMBUCKETS];
पूर्ण;

काष्ठा sfb_sched_data अणु
	काष्ठा Qdisc	*qdisc;
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block *block;
	अचिन्हित दीर्घ	rehash_पूर्णांकerval;
	अचिन्हित दीर्घ	warmup_समय;	/* द्विगुन buffering warmup समय in jअगरfies */
	u32		max;
	u32		bin_size;	/* maximum queue length per bin */
	u32		increment;	/* d1 */
	u32		decrement;	/* d2 */
	u32		limit;		/* HARD maximal queue length */
	u32		penalty_rate;
	u32		penalty_burst;
	u32		tokens_avail;
	अचिन्हित दीर्घ	rehash_समय;
	अचिन्हित दीर्घ	token_समय;

	u8		slot;		/* current active bins (0 or 1) */
	bool		द्विगुन_buffering;
	काष्ठा sfb_bins bins[2];

	काष्ठा अणु
		u32	earlydrop;
		u32	penaltydrop;
		u32	bucketdrop;
		u32	queuedrop;
		u32	childdrop;	/* drops in child qdisc */
		u32	marked;		/* ECN mark */
	पूर्ण stats;
पूर्ण;

/*
 * Each queued skb might be hashed on one or two bins
 * We store in skb_cb the two hash values.
 * (A zero value means द्विगुन buffering was not used)
 */
काष्ठा sfb_skb_cb अणु
	u32 hashes[2];
पूर्ण;

अटल अंतरभूत काष्ठा sfb_skb_cb *sfb_skb_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	qdisc_cb_निजी_validate(skb, माप(काष्ठा sfb_skb_cb));
	वापस (काष्ठा sfb_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

/*
 * If using 'internal' SFB flow classअगरier, hash comes from skb rxhash
 * If using बाह्यal classअगरier, hash comes from the classid.
 */
अटल u32 sfb_hash(स्थिर काष्ठा sk_buff *skb, u32 slot)
अणु
	वापस sfb_skb_cb(skb)->hashes[slot];
पूर्ण

/* Probabilities are coded as Q0.16 fixed-poपूर्णांक values,
 * with 0xFFFF representing 65535/65536 (almost 1.0)
 * Addition and subtraction are saturating in [0, 65535]
 */
अटल u32 prob_plus(u32 p1, u32 p2)
अणु
	u32 res = p1 + p2;

	वापस min_t(u32, res, SFB_MAX_PROB);
पूर्ण

अटल u32 prob_minus(u32 p1, u32 p2)
अणु
	वापस p1 > p2 ? p1 - p2 : 0;
पूर्ण

अटल व्योम increment_one_qlen(u32 sfbhash, u32 slot, काष्ठा sfb_sched_data *q)
अणु
	पूर्णांक i;
	काष्ठा sfb_bucket *b = &q->bins[slot].bins[0][0];

	क्रम (i = 0; i < SFB_LEVELS; i++) अणु
		u32 hash = sfbhash & SFB_BUCKET_MASK;

		sfbhash >>= SFB_BUCKET_SHIFT;
		अगर (b[hash].qlen < 0xFFFF)
			b[hash].qlen++;
		b += SFB_NUMBUCKETS; /* next level */
	पूर्ण
पूर्ण

अटल व्योम increment_qlen(स्थिर काष्ठा sk_buff *skb, काष्ठा sfb_sched_data *q)
अणु
	u32 sfbhash;

	sfbhash = sfb_hash(skb, 0);
	अगर (sfbhash)
		increment_one_qlen(sfbhash, 0, q);

	sfbhash = sfb_hash(skb, 1);
	अगर (sfbhash)
		increment_one_qlen(sfbhash, 1, q);
पूर्ण

अटल व्योम decrement_one_qlen(u32 sfbhash, u32 slot,
			       काष्ठा sfb_sched_data *q)
अणु
	पूर्णांक i;
	काष्ठा sfb_bucket *b = &q->bins[slot].bins[0][0];

	क्रम (i = 0; i < SFB_LEVELS; i++) अणु
		u32 hash = sfbhash & SFB_BUCKET_MASK;

		sfbhash >>= SFB_BUCKET_SHIFT;
		अगर (b[hash].qlen > 0)
			b[hash].qlen--;
		b += SFB_NUMBUCKETS; /* next level */
	पूर्ण
पूर्ण

अटल व्योम decrement_qlen(स्थिर काष्ठा sk_buff *skb, काष्ठा sfb_sched_data *q)
अणु
	u32 sfbhash;

	sfbhash = sfb_hash(skb, 0);
	अगर (sfbhash)
		decrement_one_qlen(sfbhash, 0, q);

	sfbhash = sfb_hash(skb, 1);
	अगर (sfbhash)
		decrement_one_qlen(sfbhash, 1, q);
पूर्ण

अटल व्योम decrement_prob(काष्ठा sfb_bucket *b, काष्ठा sfb_sched_data *q)
अणु
	b->p_mark = prob_minus(b->p_mark, q->decrement);
पूर्ण

अटल व्योम increment_prob(काष्ठा sfb_bucket *b, काष्ठा sfb_sched_data *q)
अणु
	b->p_mark = prob_plus(b->p_mark, q->increment);
पूर्ण

अटल व्योम sfb_zero_all_buckets(काष्ठा sfb_sched_data *q)
अणु
	स_रखो(&q->bins, 0, माप(q->bins));
पूर्ण

/*
 * compute max qlen, max p_mark, and avg p_mark
 */
अटल u32 sfb_compute_qlen(u32 *prob_r, u32 *avgpm_r, स्थिर काष्ठा sfb_sched_data *q)
अणु
	पूर्णांक i;
	u32 qlen = 0, prob = 0, totalpm = 0;
	स्थिर काष्ठा sfb_bucket *b = &q->bins[q->slot].bins[0][0];

	क्रम (i = 0; i < SFB_LEVELS * SFB_NUMBUCKETS; i++) अणु
		अगर (qlen < b->qlen)
			qlen = b->qlen;
		totalpm += b->p_mark;
		अगर (prob < b->p_mark)
			prob = b->p_mark;
		b++;
	पूर्ण
	*prob_r = prob;
	*avgpm_r = totalpm / (SFB_LEVELS * SFB_NUMBUCKETS);
	वापस qlen;
पूर्ण


अटल व्योम sfb_init_perturbation(u32 slot, काष्ठा sfb_sched_data *q)
अणु
	get_अक्रमom_bytes(&q->bins[slot].perturbation,
			 माप(q->bins[slot].perturbation));
पूर्ण

अटल व्योम sfb_swap_slot(काष्ठा sfb_sched_data *q)
अणु
	sfb_init_perturbation(q->slot, q);
	q->slot ^= 1;
	q->द्विगुन_buffering = false;
पूर्ण

/* Non elastic flows are allowed to use part of the bandwidth, expressed
 * in "penalty_rate" packets per second, with "penalty_burst" burst
 */
अटल bool sfb_rate_limit(काष्ठा sk_buff *skb, काष्ठा sfb_sched_data *q)
अणु
	अगर (q->penalty_rate == 0 || q->penalty_burst == 0)
		वापस true;

	अगर (q->tokens_avail < 1) अणु
		अचिन्हित दीर्घ age = min(10UL * HZ, jअगरfies - q->token_समय);

		q->tokens_avail = (age * q->penalty_rate) / HZ;
		अगर (q->tokens_avail > q->penalty_burst)
			q->tokens_avail = q->penalty_burst;
		q->token_समय = jअगरfies;
		अगर (q->tokens_avail < 1)
			वापस true;
	पूर्ण

	q->tokens_avail--;
	वापस false;
पूर्ण

अटल bool sfb_classअगरy(काष्ठा sk_buff *skb, काष्ठा tcf_proto *fl,
			 पूर्णांक *qerr, u32 *salt)
अणु
	काष्ठा tcf_result res;
	पूर्णांक result;

	result = tcf_classअगरy(skb, fl, &res, false);
	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस false;
		पूर्ण
#पूर्ण_अगर
		*salt = TC_H_MIN(res.classid);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक sfb_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु

	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;
	काष्ठा tcf_proto *fl;
	पूर्णांक i;
	u32 p_min = ~0;
	u32 minqlen = ~0;
	u32 r, sfbhash;
	u32 slot = q->slot;
	पूर्णांक ret = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;

	अगर (unlikely(sch->q.qlen >= q->limit)) अणु
		qdisc_qstats_overlimit(sch);
		q->stats.queuedrop++;
		जाओ drop;
	पूर्ण

	अगर (q->rehash_पूर्णांकerval > 0) अणु
		अचिन्हित दीर्घ limit = q->rehash_समय + q->rehash_पूर्णांकerval;

		अगर (unlikely(समय_after(jअगरfies, limit))) अणु
			sfb_swap_slot(q);
			q->rehash_समय = jअगरfies;
		पूर्ण अन्यथा अगर (unlikely(!q->द्विगुन_buffering && q->warmup_समय > 0 &&
				    समय_after(jअगरfies, limit - q->warmup_समय))) अणु
			q->द्विगुन_buffering = true;
		पूर्ण
	पूर्ण

	fl = rcu_dereference_bh(q->filter_list);
	अगर (fl) अणु
		u32 salt;

		/* If using बाह्यal classअगरiers, get result and record it. */
		अगर (!sfb_classअगरy(skb, fl, &ret, &salt))
			जाओ other_drop;
		sfbhash = siphash_1u32(salt, &q->bins[slot].perturbation);
	पूर्ण अन्यथा अणु
		sfbhash = skb_get_hash_perturb(skb, &q->bins[slot].perturbation);
	पूर्ण


	अगर (!sfbhash)
		sfbhash = 1;
	sfb_skb_cb(skb)->hashes[slot] = sfbhash;

	क्रम (i = 0; i < SFB_LEVELS; i++) अणु
		u32 hash = sfbhash & SFB_BUCKET_MASK;
		काष्ठा sfb_bucket *b = &q->bins[slot].bins[i][hash];

		sfbhash >>= SFB_BUCKET_SHIFT;
		अगर (b->qlen == 0)
			decrement_prob(b, q);
		अन्यथा अगर (b->qlen >= q->bin_size)
			increment_prob(b, q);
		अगर (minqlen > b->qlen)
			minqlen = b->qlen;
		अगर (p_min > b->p_mark)
			p_min = b->p_mark;
	पूर्ण

	slot ^= 1;
	sfb_skb_cb(skb)->hashes[slot] = 0;

	अगर (unlikely(minqlen >= q->max)) अणु
		qdisc_qstats_overlimit(sch);
		q->stats.bucketdrop++;
		जाओ drop;
	पूर्ण

	अगर (unlikely(p_min >= SFB_MAX_PROB)) अणु
		/* Inelastic flow */
		अगर (q->द्विगुन_buffering) अणु
			sfbhash = skb_get_hash_perturb(skb,
			    &q->bins[slot].perturbation);
			अगर (!sfbhash)
				sfbhash = 1;
			sfb_skb_cb(skb)->hashes[slot] = sfbhash;

			क्रम (i = 0; i < SFB_LEVELS; i++) अणु
				u32 hash = sfbhash & SFB_BUCKET_MASK;
				काष्ठा sfb_bucket *b = &q->bins[slot].bins[i][hash];

				sfbhash >>= SFB_BUCKET_SHIFT;
				अगर (b->qlen == 0)
					decrement_prob(b, q);
				अन्यथा अगर (b->qlen >= q->bin_size)
					increment_prob(b, q);
			पूर्ण
		पूर्ण
		अगर (sfb_rate_limit(skb, q)) अणु
			qdisc_qstats_overlimit(sch);
			q->stats.penaltydrop++;
			जाओ drop;
		पूर्ण
		जाओ enqueue;
	पूर्ण

	r = pअक्रमom_u32() & SFB_MAX_PROB;

	अगर (unlikely(r < p_min)) अणु
		अगर (unlikely(p_min > SFB_MAX_PROB / 2)) अणु
			/* If we're marking that many packets, then either
			 * this flow is unresponsive, or we're badly congested.
			 * In either हाल, we want to start dropping packets.
			 */
			अगर (r < (p_min - SFB_MAX_PROB / 2) * 2) अणु
				q->stats.earlydrop++;
				जाओ drop;
			पूर्ण
		पूर्ण
		अगर (INET_ECN_set_ce(skb)) अणु
			q->stats.marked++;
		पूर्ण अन्यथा अणु
			q->stats.earlydrop++;
			जाओ drop;
		पूर्ण
	पूर्ण

enqueue:
	ret = qdisc_enqueue(skb, child, to_मुक्त);
	अगर (likely(ret == NET_XMIT_SUCCESS)) अणु
		qdisc_qstats_backlog_inc(sch, skb);
		sch->q.qlen++;
		increment_qlen(skb, q);
	पूर्ण अन्यथा अगर (net_xmit_drop_count(ret)) अणु
		q->stats.childdrop++;
		qdisc_qstats_drop(sch);
	पूर्ण
	वापस ret;

drop:
	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_CN;
other_drop:
	अगर (ret & __NET_XMIT_BYPASS)
		qdisc_qstats_drop(sch);
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *sfb_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;
	काष्ठा sk_buff *skb;

	skb = child->dequeue(q->qdisc);

	अगर (skb) अणु
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;
		decrement_qlen(skb, q);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *sfb_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;

	वापस child->ops->peek(child);
पूर्ण

/* No sfb_drop -- impossible since the child करोesn't वापस the dropped skb. */

अटल व्योम sfb_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);

	qdisc_reset(q->qdisc);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
	q->slot = 0;
	q->द्विगुन_buffering = false;
	sfb_zero_all_buckets(q);
	sfb_init_perturbation(0, q);
पूर्ण

अटल व्योम sfb_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	qdisc_put(q->qdisc);
पूर्ण

अटल स्थिर काष्ठा nla_policy sfb_policy[TCA_SFB_MAX + 1] = अणु
	[TCA_SFB_PARMS]	= अणु .len = माप(काष्ठा tc_sfb_qopt) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tc_sfb_qopt sfb_शेष_ops = अणु
	.rehash_पूर्णांकerval = 600 * MSEC_PER_SEC,
	.warmup_समय = 60 * MSEC_PER_SEC,
	.limit = 0,
	.max = 25,
	.bin_size = 20,
	.increment = (SFB_MAX_PROB + 500) / 1000, /* 0.1 % */
	.decrement = (SFB_MAX_PROB + 3000) / 6000,
	.penalty_rate = 10,
	.penalty_burst = 20,
पूर्ण;

अटल पूर्णांक sfb_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child, *old;
	काष्ठा nlattr *tb[TCA_SFB_MAX + 1];
	स्थिर काष्ठा tc_sfb_qopt *ctl = &sfb_शेष_ops;
	u32 limit;
	पूर्णांक err;

	अगर (opt) अणु
		err = nla_parse_nested_deprecated(tb, TCA_SFB_MAX, opt,
						  sfb_policy, शून्य);
		अगर (err < 0)
			वापस -EINVAL;

		अगर (tb[TCA_SFB_PARMS] == शून्य)
			वापस -EINVAL;

		ctl = nla_data(tb[TCA_SFB_PARMS]);
	पूर्ण

	limit = ctl->limit;
	अगर (limit == 0)
		limit = qdisc_dev(sch)->tx_queue_len;

	child = fअगरo_create_dflt(sch, &pfअगरo_qdisc_ops, limit, extack);
	अगर (IS_ERR(child))
		वापस PTR_ERR(child);

	अगर (child != &noop_qdisc)
		qdisc_hash_add(child, true);
	sch_tree_lock(sch);

	qdisc_purge_queue(q->qdisc);
	old = q->qdisc;
	q->qdisc = child;

	q->rehash_पूर्णांकerval = msecs_to_jअगरfies(ctl->rehash_पूर्णांकerval);
	q->warmup_समय = msecs_to_jअगरfies(ctl->warmup_समय);
	q->rehash_समय = jअगरfies;
	q->limit = limit;
	q->increment = ctl->increment;
	q->decrement = ctl->decrement;
	q->max = ctl->max;
	q->bin_size = ctl->bin_size;
	q->penalty_rate = ctl->penalty_rate;
	q->penalty_burst = ctl->penalty_burst;
	q->tokens_avail = ctl->penalty_burst;
	q->token_समय = jअगरfies;

	q->slot = 0;
	q->द्विगुन_buffering = false;
	sfb_zero_all_buckets(q);
	sfb_init_perturbation(0, q);
	sfb_init_perturbation(1, q);

	sch_tree_unlock(sch);
	qdisc_put(old);

	वापस 0;
पूर्ण

अटल पूर्णांक sfb_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	पूर्णांक err;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	q->qdisc = &noop_qdisc;
	वापस sfb_change(sch, opt, extack);
पूर्ण

अटल पूर्णांक sfb_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;
	काष्ठा tc_sfb_qopt opt = अणु
		.rehash_पूर्णांकerval = jअगरfies_to_msecs(q->rehash_पूर्णांकerval),
		.warmup_समय = jअगरfies_to_msecs(q->warmup_समय),
		.limit = q->limit,
		.max = q->max,
		.bin_size = q->bin_size,
		.increment = q->increment,
		.decrement = q->decrement,
		.penalty_rate = q->penalty_rate,
		.penalty_burst = q->penalty_burst,
	पूर्ण;

	sch->qstats.backlog = q->qdisc->qstats.backlog;
	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put(skb, TCA_SFB_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक sfb_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_sfb_xstats st = अणु
		.earlydrop = q->stats.earlydrop,
		.penaltydrop = q->stats.penaltydrop,
		.bucketdrop = q->stats.bucketdrop,
		.queuedrop = q->stats.queuedrop,
		.childdrop = q->stats.childdrop,
		.marked = q->stats.marked,
	पूर्ण;

	st.maxqlen = sfb_compute_qlen(&st.maxprob, &st.avgprob, q);

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल पूर्णांक sfb_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक sfb_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);

	अगर (new == शून्य)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *sfb_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);

	वापस q->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ sfb_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 1;
पूर्ण

अटल व्योम sfb_unbind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
पूर्ण

अटल पूर्णांक sfb_change_class(काष्ठा Qdisc *sch, u32 classid, u32 parentid,
			    काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक sfb_delete(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
		      काष्ठा netlink_ext_ack *extack)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम sfb_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	अगर (!walker->stop) अणु
		अगर (walker->count >= walker->skip)
			अगर (walker->fn(sch, 1, walker) < 0) अणु
				walker->stop = 1;
				वापस;
			पूर्ण
		walker->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *sfb_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfb_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल अचिन्हित दीर्घ sfb_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
			      u32 classid)
अणु
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा Qdisc_class_ops sfb_class_ops = अणु
	.graft		=	sfb_graft,
	.leaf		=	sfb_leaf,
	.find		=	sfb_find,
	.change		=	sfb_change_class,
	.delete		=	sfb_delete,
	.walk		=	sfb_walk,
	.tcf_block	=	sfb_tcf_block,
	.bind_tcf	=	sfb_bind,
	.unbind_tcf	=	sfb_unbind,
	.dump		=	sfb_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops sfb_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"sfb",
	.priv_size	=	माप(काष्ठा sfb_sched_data),
	.cl_ops		=	&sfb_class_ops,
	.enqueue	=	sfb_enqueue,
	.dequeue	=	sfb_dequeue,
	.peek		=	sfb_peek,
	.init		=	sfb_init,
	.reset		=	sfb_reset,
	.destroy	=	sfb_destroy,
	.change		=	sfb_change,
	.dump		=	sfb_dump,
	.dump_stats	=	sfb_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init sfb_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&sfb_qdisc_ops);
पूर्ण

अटल व्योम __निकास sfb_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&sfb_qdisc_ops);
पूर्ण

module_init(sfb_module_init)
module_निकास(sfb_module_निकास)

MODULE_DESCRIPTION("Stochastic Fair Blue queue discipline");
MODULE_AUTHOR("Juliusz Chroboczek");
MODULE_AUTHOR("Eric Dumazet");
MODULE_LICENSE("GPL");
