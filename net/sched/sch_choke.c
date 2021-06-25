<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_choke.c	CHOKE scheduler
 *
 * Copyright (c) 2011 Stephen Hemminger <shemminger@vyatta.com>
 * Copyright (c) 2011 Eric Dumazet <eric.dumazet@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/red.h>
#समावेश <net/flow_dissector.h>

/*
   CHOKe stateless AQM क्रम fair bandwidth allocation
   =================================================

   CHOKe (CHOose and Keep क्रम responsive flows, CHOose and Kill क्रम
   unresponsive flows) is a variant of RED that penalizes misbehaving flows but
   मुख्यtains no flow state. The dअगरference from RED is an additional step
   during the enqueuing process. If average queue size is over the
   low threshold (qmin), a packet is chosen at अक्रमom from the queue.
   If both the new and chosen packet are from the same flow, both
   are dropped. Unlike RED, CHOKe is not really a "classful" qdisc because it
   needs to access packets in queue अक्रमomly. It has a minimal class
   पूर्णांकerface to allow overriding the builtin flow classअगरier with
   filters.

   Source:
   R. Pan, B. Prabhakar, and K. Psounis, "CHOKe, A Stateless
   Active Queue Management Scheme क्रम Approximating Fair Bandwidth Allocation",
   IEEE INFOCOM, 2000.

   A. Tang, J. Wang, S. Low, "Understanding CHOKe: Throughput and Spatial
   Characteristics", IEEE/ACM Transactions on Networking, 2004

 */

/* Upper bound on size of sk_buff table (packets) */
#घोषणा CHOKE_MAX_QUEUE	(128*1024 - 1)

काष्ठा choke_sched_data अणु
/* Parameters */
	u32		 limit;
	अचिन्हित अक्षर	 flags;

	काष्ठा red_parms parms;

/* Variables */
	काष्ठा red_vars  vars;
	काष्ठा अणु
		u32	prob_drop;	/* Early probability drops */
		u32	prob_mark;	/* Early probability marks */
		u32	क्रमced_drop;	/* Forced drops, qavg > max_thresh */
		u32	क्रमced_mark;	/* Forced marks, qavg > max_thresh */
		u32	pdrop;          /* Drops due to queue limits */
		u32	other;          /* Drops due to drop() calls */
		u32	matched;	/* Drops to flow match */
	पूर्ण stats;

	अचिन्हित पूर्णांक	 head;
	अचिन्हित पूर्णांक	 tail;

	अचिन्हित पूर्णांक	 tab_mask; /* size - 1 */

	काष्ठा sk_buff **tab;
पूर्ण;

/* number of elements in queue including holes */
अटल अचिन्हित पूर्णांक choke_len(स्थिर काष्ठा choke_sched_data *q)
अणु
	वापस (q->tail - q->head) & q->tab_mask;
पूर्ण

/* Is ECN parameter configured */
अटल पूर्णांक use_ecn(स्थिर काष्ठा choke_sched_data *q)
अणु
	वापस q->flags & TC_RED_ECN;
पूर्ण

/* Should packets over max just be dropped (versus marked) */
अटल पूर्णांक use_harddrop(स्थिर काष्ठा choke_sched_data *q)
अणु
	वापस q->flags & TC_RED_HARDDROP;
पूर्ण

/* Move head poपूर्णांकer क्रमward to skip over holes */
अटल व्योम choke_zap_head_holes(काष्ठा choke_sched_data *q)
अणु
	करो अणु
		q->head = (q->head + 1) & q->tab_mask;
		अगर (q->head == q->tail)
			अवरोध;
	पूर्ण जबतक (q->tab[q->head] == शून्य);
पूर्ण

/* Move tail poपूर्णांकer backwards to reuse holes */
अटल व्योम choke_zap_tail_holes(काष्ठा choke_sched_data *q)
अणु
	करो अणु
		q->tail = (q->tail - 1) & q->tab_mask;
		अगर (q->head == q->tail)
			अवरोध;
	पूर्ण जबतक (q->tab[q->tail] == शून्य);
पूर्ण

/* Drop packet from queue array by creating a "hole" */
अटल व्योम choke_drop_by_idx(काष्ठा Qdisc *sch, अचिन्हित पूर्णांक idx,
			      काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb = q->tab[idx];

	q->tab[idx] = शून्य;

	अगर (idx == q->head)
		choke_zap_head_holes(q);
	अगर (idx == q->tail)
		choke_zap_tail_holes(q);

	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_tree_reduce_backlog(sch, 1, qdisc_pkt_len(skb));
	qdisc_drop(skb, sch, to_मुक्त);
	--sch->q.qlen;
पूर्ण

काष्ठा choke_skb_cb अणु
	u8			keys_valid;
	काष्ठा			flow_keys_digest keys;
पूर्ण;

अटल अंतरभूत काष्ठा choke_skb_cb *choke_skb_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	qdisc_cb_निजी_validate(skb, माप(काष्ठा choke_skb_cb));
	वापस (काष्ठा choke_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

/*
 * Compare flow of two packets
 *  Returns true only अगर source and destination address and port match.
 *          false क्रम special हालs
 */
अटल bool choke_match_flow(काष्ठा sk_buff *skb1,
			     काष्ठा sk_buff *skb2)
अणु
	काष्ठा flow_keys temp;

	अगर (skb1->protocol != skb2->protocol)
		वापस false;

	अगर (!choke_skb_cb(skb1)->keys_valid) अणु
		choke_skb_cb(skb1)->keys_valid = 1;
		skb_flow_dissect_flow_keys(skb1, &temp, 0);
		make_flow_keys_digest(&choke_skb_cb(skb1)->keys, &temp);
	पूर्ण

	अगर (!choke_skb_cb(skb2)->keys_valid) अणु
		choke_skb_cb(skb2)->keys_valid = 1;
		skb_flow_dissect_flow_keys(skb2, &temp, 0);
		make_flow_keys_digest(&choke_skb_cb(skb2)->keys, &temp);
	पूर्ण

	वापस !स_भेद(&choke_skb_cb(skb1)->keys,
		       &choke_skb_cb(skb2)->keys,
		       माप(choke_skb_cb(skb1)->keys));
पूर्ण

/*
 * Select a packet at अक्रमom from queue
 * HACK: since queue can have holes from previous deletion; retry several
 *   बार to find a अक्रमom skb but then just give up and वापस the head
 * Will वापस शून्य अगर queue is empty (q->head == q->tail)
 */
अटल काष्ठा sk_buff *choke_peek_अक्रमom(स्थिर काष्ठा choke_sched_data *q,
					 अचिन्हित पूर्णांक *pidx)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक retrys = 3;

	करो अणु
		*pidx = (q->head + pअक्रमom_u32_max(choke_len(q))) & q->tab_mask;
		skb = q->tab[*pidx];
		अगर (skb)
			वापस skb;
	पूर्ण जबतक (--retrys > 0);

	वापस q->tab[*pidx = q->head];
पूर्ण

/*
 * Compare new packet with अक्रमom packet in queue
 * वापसs true अगर matched and sets *pidx
 */
अटल bool choke_match_अक्रमom(स्थिर काष्ठा choke_sched_data *q,
			       काष्ठा sk_buff *nskb,
			       अचिन्हित पूर्णांक *pidx)
अणु
	काष्ठा sk_buff *oskb;

	अगर (q->head == q->tail)
		वापस false;

	oskb = choke_peek_अक्रमom(q, pidx);
	वापस choke_match_flow(oskb, nskb);
पूर्ण

अटल पूर्णांक choke_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			 काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	स्थिर काष्ठा red_parms *p = &q->parms;

	choke_skb_cb(skb)->keys_valid = 0;
	/* Compute average queue usage (see RED) */
	q->vars.qavg = red_calc_qavg(p, &q->vars, sch->q.qlen);
	अगर (red_is_idling(&q->vars))
		red_end_of_idle_period(&q->vars);

	/* Is queue small? */
	अगर (q->vars.qavg <= p->qth_min)
		q->vars.qcount = -1;
	अन्यथा अणु
		अचिन्हित पूर्णांक idx;

		/* Draw a packet at अक्रमom from queue and compare flow */
		अगर (choke_match_अक्रमom(q, skb, &idx)) अणु
			q->stats.matched++;
			choke_drop_by_idx(sch, idx, to_मुक्त);
			जाओ congestion_drop;
		पूर्ण

		/* Queue is large, always mark/drop */
		अगर (q->vars.qavg > p->qth_max) अणु
			q->vars.qcount = -1;

			qdisc_qstats_overlimit(sch);
			अगर (use_harddrop(q) || !use_ecn(q) ||
			    !INET_ECN_set_ce(skb)) अणु
				q->stats.क्रमced_drop++;
				जाओ congestion_drop;
			पूर्ण

			q->stats.क्रमced_mark++;
		पूर्ण अन्यथा अगर (++q->vars.qcount) अणु
			अगर (red_mark_probability(p, &q->vars, q->vars.qavg)) अणु
				q->vars.qcount = 0;
				q->vars.qR = red_अक्रमom(p);

				qdisc_qstats_overlimit(sch);
				अगर (!use_ecn(q) || !INET_ECN_set_ce(skb)) अणु
					q->stats.prob_drop++;
					जाओ congestion_drop;
				पूर्ण

				q->stats.prob_mark++;
			पूर्ण
		पूर्ण अन्यथा
			q->vars.qR = red_अक्रमom(p);
	पूर्ण

	/* Admit new packet */
	अगर (sch->q.qlen < q->limit) अणु
		q->tab[q->tail] = skb;
		q->tail = (q->tail + 1) & q->tab_mask;
		++sch->q.qlen;
		qdisc_qstats_backlog_inc(sch, skb);
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	q->stats.pdrop++;
	वापस qdisc_drop(skb, sch, to_मुक्त);

congestion_drop:
	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_CN;
पूर्ण

अटल काष्ठा sk_buff *choke_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

	अगर (q->head == q->tail) अणु
		अगर (!red_is_idling(&q->vars))
			red_start_of_idle_period(&q->vars);
		वापस शून्य;
	पूर्ण

	skb = q->tab[q->head];
	q->tab[q->head] = शून्य;
	choke_zap_head_holes(q);
	--sch->q.qlen;
	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);

	वापस skb;
पूर्ण

अटल व्योम choke_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);

	जबतक (q->head != q->tail) अणु
		काष्ठा sk_buff *skb = q->tab[q->head];

		q->head = (q->head + 1) & q->tab_mask;
		अगर (!skb)
			जारी;
		rtnl_qdisc_drop(skb, sch);
	पूर्ण

	sch->q.qlen = 0;
	sch->qstats.backlog = 0;
	अगर (q->tab)
		स_रखो(q->tab, 0, (q->tab_mask + 1) * माप(काष्ठा sk_buff *));
	q->head = q->tail = 0;
	red_restart(&q->vars);
पूर्ण

अटल स्थिर काष्ठा nla_policy choke_policy[TCA_CHOKE_MAX + 1] = अणु
	[TCA_CHOKE_PARMS]	= अणु .len = माप(काष्ठा tc_red_qopt) पूर्ण,
	[TCA_CHOKE_STAB]	= अणु .len = RED_STAB_SIZE पूर्ण,
	[TCA_CHOKE_MAX_P]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;


अटल व्योम choke_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

अटल पूर्णांक choke_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_CHOKE_MAX + 1];
	स्थिर काष्ठा tc_red_qopt *ctl;
	पूर्णांक err;
	काष्ठा sk_buff **old = शून्य;
	अचिन्हित पूर्णांक mask;
	u32 max_P;
	u8 *stab;

	अगर (opt == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_CHOKE_MAX, opt,
					  choke_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_CHOKE_PARMS] == शून्य ||
	    tb[TCA_CHOKE_STAB] == शून्य)
		वापस -EINVAL;

	max_P = tb[TCA_CHOKE_MAX_P] ? nla_get_u32(tb[TCA_CHOKE_MAX_P]) : 0;

	ctl = nla_data(tb[TCA_CHOKE_PARMS]);
	stab = nla_data(tb[TCA_CHOKE_STAB]);
	अगर (!red_check_params(ctl->qth_min, ctl->qth_max, ctl->Wlog, ctl->Scell_log, stab))
		वापस -EINVAL;

	अगर (ctl->limit > CHOKE_MAX_QUEUE)
		वापस -EINVAL;

	mask = roundup_घात_of_two(ctl->limit + 1) - 1;
	अगर (mask != q->tab_mask) अणु
		काष्ठा sk_buff **ntab;

		ntab = kvसुस्मृति(mask + 1, माप(काष्ठा sk_buff *), GFP_KERNEL);
		अगर (!ntab)
			वापस -ENOMEM;

		sch_tree_lock(sch);
		old = q->tab;
		अगर (old) अणु
			अचिन्हित पूर्णांक oqlen = sch->q.qlen, tail = 0;
			अचिन्हित dropped = 0;

			जबतक (q->head != q->tail) अणु
				काष्ठा sk_buff *skb = q->tab[q->head];

				q->head = (q->head + 1) & q->tab_mask;
				अगर (!skb)
					जारी;
				अगर (tail < mask) अणु
					ntab[tail++] = skb;
					जारी;
				पूर्ण
				dropped += qdisc_pkt_len(skb);
				qdisc_qstats_backlog_dec(sch, skb);
				--sch->q.qlen;
				rtnl_qdisc_drop(skb, sch);
			पूर्ण
			qdisc_tree_reduce_backlog(sch, oqlen - sch->q.qlen, dropped);
			q->head = 0;
			q->tail = tail;
		पूर्ण

		q->tab_mask = mask;
		q->tab = ntab;
	पूर्ण अन्यथा
		sch_tree_lock(sch);

	q->flags = ctl->flags;
	q->limit = ctl->limit;

	red_set_parms(&q->parms, ctl->qth_min, ctl->qth_max, ctl->Wlog,
		      ctl->Plog, ctl->Scell_log,
		      stab,
		      max_P);
	red_set_vars(&q->vars);

	अगर (q->head == q->tail)
		red_end_of_idle_period(&q->vars);

	sch_tree_unlock(sch);
	choke_मुक्त(old);
	वापस 0;
पूर्ण

अटल पूर्णांक choke_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	वापस choke_change(sch, opt, extack);
पूर्ण

अटल पूर्णांक choke_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts = शून्य;
	काष्ठा tc_red_qopt opt = अणु
		.limit		= q->limit,
		.flags		= q->flags,
		.qth_min	= q->parms.qth_min >> q->parms.Wlog,
		.qth_max	= q->parms.qth_max >> q->parms.Wlog,
		.Wlog		= q->parms.Wlog,
		.Plog		= q->parms.Plog,
		.Scell_log	= q->parms.Scell_log,
	पूर्ण;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_CHOKE_PARMS, माप(opt), &opt) ||
	    nla_put_u32(skb, TCA_CHOKE_MAX_P, q->parms.max_P))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक choke_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_choke_xstats st = अणु
		.early	= q->stats.prob_drop + q->stats.क्रमced_drop,
		.marked	= q->stats.prob_mark + q->stats.क्रमced_mark,
		.pdrop	= q->stats.pdrop,
		.other	= q->stats.other,
		.matched = q->stats.matched,
	पूर्ण;

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल व्योम choke_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);

	choke_मुक्त(q->tab);
पूर्ण

अटल काष्ठा sk_buff *choke_peek_head(काष्ठा Qdisc *sch)
अणु
	काष्ठा choke_sched_data *q = qdisc_priv(sch);

	वापस (q->head != q->tail) ? q->tab[q->head] : शून्य;
पूर्ण

अटल काष्ठा Qdisc_ops choke_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"choke",
	.priv_size	=	माप(काष्ठा choke_sched_data),

	.enqueue	=	choke_enqueue,
	.dequeue	=	choke_dequeue,
	.peek		=	choke_peek_head,
	.init		=	choke_init,
	.destroy	=	choke_destroy,
	.reset		=	choke_reset,
	.change		=	choke_change,
	.dump		=	choke_dump,
	.dump_stats	=	choke_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init choke_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&choke_qdisc_ops);
पूर्ण

अटल व्योम __निकास choke_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&choke_qdisc_ops);
पूर्ण

module_init(choke_module_init)
module_निकास(choke_module_निकास)

MODULE_LICENSE("GPL");
