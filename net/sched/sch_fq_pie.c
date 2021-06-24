<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Flow Queue PIE discipline
 *
 * Copyright (C) 2019 Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 * Copyright (C) 2019 Sachin D. Patil <sdp.sachin@gmail.com>
 * Copyright (C) 2019 V. Saiअक्षरan <vsaiअक्षरan1998@gmail.com>
 * Copyright (C) 2019 Mohit Bhasi <mohitbhasi1998@gmail.com>
 * Copyright (C) 2019 Leslie Monis <lesliemonis@gmail.com>
 * Copyright (C) 2019 Gautam Ramakrishnan <gautamramk@gmail.com>
 */

#समावेश <linux/jhash.h>
#समावेश <linux/sizes.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pie.h>

/* Flow Queue PIE
 *
 * Principles:
 *   - Packets are classअगरied on flows.
 *   - This is a Stochastic model (as we use a hash, several flows might
 *                                 be hashed to the same slot)
 *   - Each flow has a PIE managed queue.
 *   - Flows are linked onto two (Round Robin) lists,
 *     so that new flows have priority on old ones.
 *   - For a given flow, packets are not reordered.
 *   - Drops during enqueue only.
 *   - ECN capability is off by शेष.
 *   - ECN threshold (अगर ECN is enabled) is at 10% by शेष.
 *   - Uses बारtamps to calculate queue delay by शेष.
 */

/**
 * काष्ठा fq_pie_flow - contains data क्रम each flow
 * @vars:	pie vars associated with the flow
 * @deficit:	number of reमुख्यing byte credits
 * @backlog:	size of data in the flow
 * @qlen:	number of packets in the flow
 * @flowchain:	flowchain क्रम the flow
 * @head:	first packet in the flow
 * @tail:	last packet in the flow
 */
काष्ठा fq_pie_flow अणु
	काष्ठा pie_vars vars;
	s32 deficit;
	u32 backlog;
	u32 qlen;
	काष्ठा list_head flowchain;
	काष्ठा sk_buff *head;
	काष्ठा sk_buff *tail;
पूर्ण;

काष्ठा fq_pie_sched_data अणु
	काष्ठा tcf_proto __rcu *filter_list; /* optional बाह्यal classअगरier */
	काष्ठा tcf_block *block;
	काष्ठा fq_pie_flow *flows;
	काष्ठा Qdisc *sch;
	काष्ठा list_head old_flows;
	काष्ठा list_head new_flows;
	काष्ठा pie_params p_params;
	u32 ecn_prob;
	u32 flows_cnt;
	u32 quantum;
	u32 memory_limit;
	u32 new_flow_count;
	u32 memory_usage;
	u32 overmemory;
	काष्ठा pie_stats stats;
	काष्ठा समयr_list adapt_समयr;
पूर्ण;

अटल अचिन्हित पूर्णांक fq_pie_hash(स्थिर काष्ठा fq_pie_sched_data *q,
				काष्ठा sk_buff *skb)
अणु
	वापस reciprocal_scale(skb_get_hash(skb), q->flows_cnt);
पूर्ण

अटल अचिन्हित पूर्णांक fq_pie_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				    पूर्णांक *qerr)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा tcf_proto *filter;
	काष्ठा tcf_result res;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority) == sch->handle &&
	    TC_H_MIN(skb->priority) > 0 &&
	    TC_H_MIN(skb->priority) <= q->flows_cnt)
		वापस TC_H_MIN(skb->priority);

	filter = rcu_dereference_bh(q->filter_list);
	अगर (!filter)
		वापस fq_pie_hash(q, skb) + 1;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	result = tcf_classअगरy(skb, filter, &res, false);
	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस 0;
		पूर्ण
#पूर्ण_अगर
		अगर (TC_H_MIN(res.classid) <= q->flows_cnt)
			वापस TC_H_MIN(res.classid);
	पूर्ण
	वापस 0;
पूर्ण

/* add skb to flow queue (tail add) */
अटल अंतरभूत व्योम flow_queue_add(काष्ठा fq_pie_flow *flow,
				  काष्ठा sk_buff *skb)
अणु
	अगर (!flow->head)
		flow->head = skb;
	अन्यथा
		flow->tail->next = skb;
	flow->tail = skb;
	skb->next = शून्य;
पूर्ण

अटल पूर्णांक fq_pie_qdisc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा fq_pie_flow *sel_flow;
	पूर्णांक ret;
	u8 memory_limited = false;
	u8 enqueue = false;
	u32 pkt_len;
	u32 idx;

	/* Classअगरies packet पूर्णांकo corresponding flow */
	idx = fq_pie_classअगरy(skb, sch, &ret);
	अगर (idx == 0) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण
	idx--;

	sel_flow = &q->flows[idx];
	/* Checks whether adding a new packet would exceed memory limit */
	get_pie_cb(skb)->mem_usage = skb->truesize;
	memory_limited = q->memory_usage > q->memory_limit + skb->truesize;

	/* Checks अगर the qdisc is full */
	अगर (unlikely(qdisc_qlen(sch) >= sch->limit)) अणु
		q->stats.overlimit++;
		जाओ out;
	पूर्ण अन्यथा अगर (unlikely(memory_limited)) अणु
		q->overmemory++;
	पूर्ण

	अगर (!pie_drop_early(sch, &q->p_params, &sel_flow->vars,
			    sel_flow->backlog, skb->len)) अणु
		enqueue = true;
	पूर्ण अन्यथा अगर (q->p_params.ecn &&
		   sel_flow->vars.prob <= (MAX_PROB / 100) * q->ecn_prob &&
		   INET_ECN_set_ce(skb)) अणु
		/* If packet is ecn capable, mark it अगर drop probability
		 * is lower than the parameter ecn_prob, अन्यथा drop it.
		 */
		q->stats.ecn_mark++;
		enqueue = true;
	पूर्ण
	अगर (enqueue) अणु
		/* Set enqueue समय only when dq_rate_estimator is disabled. */
		अगर (!q->p_params.dq_rate_estimator)
			pie_set_enqueue_समय(skb);

		pkt_len = qdisc_pkt_len(skb);
		q->stats.packets_in++;
		q->memory_usage += skb->truesize;
		sch->qstats.backlog += pkt_len;
		sch->q.qlen++;
		flow_queue_add(sel_flow, skb);
		अगर (list_empty(&sel_flow->flowchain)) अणु
			list_add_tail(&sel_flow->flowchain, &q->new_flows);
			q->new_flow_count++;
			sel_flow->deficit = q->quantum;
			sel_flow->qlen = 0;
			sel_flow->backlog = 0;
		पूर्ण
		sel_flow->qlen++;
		sel_flow->backlog += pkt_len;
		वापस NET_XMIT_SUCCESS;
	पूर्ण
out:
	q->stats.dropped++;
	sel_flow->vars.accu_prob = 0;
	__qdisc_drop(skb, to_मुक्त);
	qdisc_qstats_drop(sch);
	वापस NET_XMIT_CN;
पूर्ण

अटल स्थिर काष्ठा nla_policy fq_pie_policy[TCA_FQ_PIE_MAX + 1] = अणु
	[TCA_FQ_PIE_LIMIT]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_FLOWS]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_TARGET]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_TUPDATE]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_ALPHA]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_BETA]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_QUANTUM]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_MEMORY_LIMIT]	= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_ECN_PROB]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_ECN]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_BYTEMODE]		= अणु.type = NLA_U32पूर्ण,
	[TCA_FQ_PIE_DQ_RATE_ESTIMATOR]	= अणु.type = NLA_U32पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा sk_buff *dequeue_head(काष्ठा fq_pie_flow *flow)
अणु
	काष्ठा sk_buff *skb = flow->head;

	flow->head = skb->next;
	skb->next = शून्य;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *fq_pie_qdisc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा fq_pie_flow *flow;
	काष्ठा list_head *head;
	u32 pkt_len;

begin:
	head = &q->new_flows;
	अगर (list_empty(head)) अणु
		head = &q->old_flows;
		अगर (list_empty(head))
			वापस शून्य;
	पूर्ण

	flow = list_first_entry(head, काष्ठा fq_pie_flow, flowchain);
	/* Flow has exhausted all its credits */
	अगर (flow->deficit <= 0) अणु
		flow->deficit += q->quantum;
		list_move_tail(&flow->flowchain, &q->old_flows);
		जाओ begin;
	पूर्ण

	अगर (flow->head) अणु
		skb = dequeue_head(flow);
		pkt_len = qdisc_pkt_len(skb);
		sch->qstats.backlog -= pkt_len;
		sch->q.qlen--;
		qdisc_bstats_update(sch, skb);
	पूर्ण

	अगर (!skb) अणु
		/* क्रमce a pass through old_flows to prevent starvation */
		अगर (head == &q->new_flows && !list_empty(&q->old_flows))
			list_move_tail(&flow->flowchain, &q->old_flows);
		अन्यथा
			list_del_init(&flow->flowchain);
		जाओ begin;
	पूर्ण

	flow->qlen--;
	flow->deficit -= pkt_len;
	flow->backlog -= pkt_len;
	q->memory_usage -= get_pie_cb(skb)->mem_usage;
	pie_process_dequeue(skb, &q->p_params, &flow->vars, flow->backlog);
	वापस skb;
पूर्ण

अटल पूर्णांक fq_pie_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_FQ_PIE_MAX + 1];
	अचिन्हित पूर्णांक len_dropped = 0;
	अचिन्हित पूर्णांक num_dropped = 0;
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested(tb, TCA_FQ_PIE_MAX, opt, fq_pie_policy, extack);
	अगर (err < 0)
		वापस err;

	sch_tree_lock(sch);
	अगर (tb[TCA_FQ_PIE_LIMIT]) अणु
		u32 limit = nla_get_u32(tb[TCA_FQ_PIE_LIMIT]);

		q->p_params.limit = limit;
		sch->limit = limit;
	पूर्ण
	अगर (tb[TCA_FQ_PIE_FLOWS]) अणु
		अगर (q->flows) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Number of flows cannot be changed");
			जाओ flow_error;
		पूर्ण
		q->flows_cnt = nla_get_u32(tb[TCA_FQ_PIE_FLOWS]);
		अगर (!q->flows_cnt || q->flows_cnt > 65536) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Number of flows must range in [1..65536]");
			जाओ flow_error;
		पूर्ण
	पूर्ण

	/* convert from microseconds to pschedसमय */
	अगर (tb[TCA_FQ_PIE_TARGET]) अणु
		/* target is in us */
		u32 target = nla_get_u32(tb[TCA_FQ_PIE_TARGET]);

		/* convert to pschedसमय */
		q->p_params.target =
			PSCHED_NS2TICKS((u64)target * NSEC_PER_USEC);
	पूर्ण

	/* tupdate is in jअगरfies */
	अगर (tb[TCA_FQ_PIE_TUPDATE])
		q->p_params.tupdate =
			usecs_to_jअगरfies(nla_get_u32(tb[TCA_FQ_PIE_TUPDATE]));

	अगर (tb[TCA_FQ_PIE_ALPHA])
		q->p_params.alpha = nla_get_u32(tb[TCA_FQ_PIE_ALPHA]);

	अगर (tb[TCA_FQ_PIE_BETA])
		q->p_params.beta = nla_get_u32(tb[TCA_FQ_PIE_BETA]);

	अगर (tb[TCA_FQ_PIE_QUANTUM])
		q->quantum = nla_get_u32(tb[TCA_FQ_PIE_QUANTUM]);

	अगर (tb[TCA_FQ_PIE_MEMORY_LIMIT])
		q->memory_limit = nla_get_u32(tb[TCA_FQ_PIE_MEMORY_LIMIT]);

	अगर (tb[TCA_FQ_PIE_ECN_PROB])
		q->ecn_prob = nla_get_u32(tb[TCA_FQ_PIE_ECN_PROB]);

	अगर (tb[TCA_FQ_PIE_ECN])
		q->p_params.ecn = nla_get_u32(tb[TCA_FQ_PIE_ECN]);

	अगर (tb[TCA_FQ_PIE_BYTEMODE])
		q->p_params.bytemode = nla_get_u32(tb[TCA_FQ_PIE_BYTEMODE]);

	अगर (tb[TCA_FQ_PIE_DQ_RATE_ESTIMATOR])
		q->p_params.dq_rate_estimator =
			nla_get_u32(tb[TCA_FQ_PIE_DQ_RATE_ESTIMATOR]);

	/* Drop excess packets अगर new limit is lower */
	जबतक (sch->q.qlen > sch->limit) अणु
		काष्ठा sk_buff *skb = fq_pie_qdisc_dequeue(sch);

		len_dropped += qdisc_pkt_len(skb);
		num_dropped += 1;
		rtnl_kमुक्त_skbs(skb, skb);
	पूर्ण
	qdisc_tree_reduce_backlog(sch, num_dropped, len_dropped);

	sch_tree_unlock(sch);
	वापस 0;

flow_error:
	sch_tree_unlock(sch);
	वापस -EINVAL;
पूर्ण

अटल व्योम fq_pie_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fq_pie_sched_data *q = from_समयr(q, t, adapt_समयr);
	काष्ठा Qdisc *sch = q->sch;
	spinlock_t *root_lock; /* to lock qdisc क्रम probability calculations */
	u32 idx;

	root_lock = qdisc_lock(qdisc_root_sleeping(sch));
	spin_lock(root_lock);

	क्रम (idx = 0; idx < q->flows_cnt; idx++)
		pie_calculate_probability(&q->p_params, &q->flows[idx].vars,
					  q->flows[idx].backlog);

	/* reset the समयr to fire after 'tupdate' jअगरfies. */
	अगर (q->p_params.tupdate)
		mod_समयr(&q->adapt_समयr, jअगरfies + q->p_params.tupdate);

	spin_unlock(root_lock);
पूर्ण

अटल पूर्णांक fq_pie_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	पूर्णांक err;
	u32 idx;

	pie_params_init(&q->p_params);
	sch->limit = 10 * 1024;
	q->p_params.limit = sch->limit;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->sch = sch;
	q->ecn_prob = 10;
	q->flows_cnt = 1024;
	q->memory_limit = SZ_32M;

	INIT_LIST_HEAD(&q->new_flows);
	INIT_LIST_HEAD(&q->old_flows);
	समयr_setup(&q->adapt_समयr, fq_pie_समयr, 0);

	अगर (opt) अणु
		err = fq_pie_change(sch, opt, extack);

		अगर (err)
			वापस err;
	पूर्ण

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		जाओ init_failure;

	q->flows = kvसुस्मृति(q->flows_cnt, माप(काष्ठा fq_pie_flow),
			    GFP_KERNEL);
	अगर (!q->flows) अणु
		err = -ENOMEM;
		जाओ init_failure;
	पूर्ण
	क्रम (idx = 0; idx < q->flows_cnt; idx++) अणु
		काष्ठा fq_pie_flow *flow = q->flows + idx;

		INIT_LIST_HEAD(&flow->flowchain);
		pie_vars_init(&flow->vars);
	पूर्ण

	mod_समयr(&q->adapt_समयr, jअगरfies + HZ / 2);

	वापस 0;

init_failure:
	q->flows_cnt = 0;

	वापस err;
पूर्ण

अटल पूर्णांक fq_pie_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start(skb, TCA_OPTIONS);
	अगर (!opts)
		वापस -EMSGSIZE;

	/* convert target from pschedसमय to us */
	अगर (nla_put_u32(skb, TCA_FQ_PIE_LIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_FQ_PIE_FLOWS, q->flows_cnt) ||
	    nla_put_u32(skb, TCA_FQ_PIE_TARGET,
			((u32)PSCHED_TICKS2NS(q->p_params.target)) /
			NSEC_PER_USEC) ||
	    nla_put_u32(skb, TCA_FQ_PIE_TUPDATE,
			jअगरfies_to_usecs(q->p_params.tupdate)) ||
	    nla_put_u32(skb, TCA_FQ_PIE_ALPHA, q->p_params.alpha) ||
	    nla_put_u32(skb, TCA_FQ_PIE_BETA, q->p_params.beta) ||
	    nla_put_u32(skb, TCA_FQ_PIE_QUANTUM, q->quantum) ||
	    nla_put_u32(skb, TCA_FQ_PIE_MEMORY_LIMIT, q->memory_limit) ||
	    nla_put_u32(skb, TCA_FQ_PIE_ECN_PROB, q->ecn_prob) ||
	    nla_put_u32(skb, TCA_FQ_PIE_ECN, q->p_params.ecn) ||
	    nla_put_u32(skb, TCA_FQ_PIE_BYTEMODE, q->p_params.bytemode) ||
	    nla_put_u32(skb, TCA_FQ_PIE_DQ_RATE_ESTIMATOR,
			q->p_params.dq_rate_estimator))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fq_pie_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_fq_pie_xstats st = अणु
		.packets_in	= q->stats.packets_in,
		.overlimit	= q->stats.overlimit,
		.overmemory	= q->overmemory,
		.dropped	= q->stats.dropped,
		.ecn_mark	= q->stats.ecn_mark,
		.new_flow_count = q->new_flow_count,
		.memory_usage   = q->memory_usage,
	पूर्ण;
	काष्ठा list_head *pos;

	sch_tree_lock(sch);
	list_क्रम_each(pos, &q->new_flows)
		st.new_flows_len++;

	list_क्रम_each(pos, &q->old_flows)
		st.old_flows_len++;
	sch_tree_unlock(sch);

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल व्योम fq_pie_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);
	u32 idx;

	INIT_LIST_HEAD(&q->new_flows);
	INIT_LIST_HEAD(&q->old_flows);
	क्रम (idx = 0; idx < q->flows_cnt; idx++) अणु
		काष्ठा fq_pie_flow *flow = q->flows + idx;

		/* Removes all packets from flow */
		rtnl_kमुक्त_skbs(flow->head, flow->tail);
		flow->head = शून्य;

		INIT_LIST_HEAD(&flow->flowchain);
		pie_vars_init(&flow->vars);
	पूर्ण

	sch->q.qlen = 0;
	sch->qstats.backlog = 0;
पूर्ण

अटल व्योम fq_pie_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_pie_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	del_समयr_sync(&q->adapt_समयr);
	kvमुक्त(q->flows);
पूर्ण

अटल काष्ठा Qdisc_ops fq_pie_qdisc_ops __पढ़ो_mostly = अणु
	.id		= "fq_pie",
	.priv_size	= माप(काष्ठा fq_pie_sched_data),
	.enqueue	= fq_pie_qdisc_enqueue,
	.dequeue	= fq_pie_qdisc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= fq_pie_init,
	.destroy	= fq_pie_destroy,
	.reset		= fq_pie_reset,
	.change		= fq_pie_change,
	.dump		= fq_pie_dump,
	.dump_stats	= fq_pie_dump_stats,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init fq_pie_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&fq_pie_qdisc_ops);
पूर्ण

अटल व्योम __निकास fq_pie_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&fq_pie_qdisc_ops);
पूर्ण

module_init(fq_pie_module_init);
module_निकास(fq_pie_module_निकास);

MODULE_DESCRIPTION("Flow Queue Proportional Integral controller Enhanced (FQ-PIE)");
MODULE_AUTHOR("Mohit P. Tahiliani");
MODULE_LICENSE("GPL");
