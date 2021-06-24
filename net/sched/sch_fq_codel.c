<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fair Queue CoDel discipline
 *
 *  Copyright (C) 2012,2015 Eric Dumazet <edumazet@google.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/codel.h>
#समावेश <net/codel_impl.h>
#समावेश <net/codel_qdisc.h>

/*	Fair Queue CoDel.
 *
 * Principles :
 * Packets are classअगरied (पूर्णांकernal classअगरier or बाह्यal) on flows.
 * This is a Stochastic model (as we use a hash, several flows
 *			       might be hashed on same slot)
 * Each flow has a CoDel managed queue.
 * Flows are linked onto two (Round Robin) lists,
 * so that new flows have priority on old ones.
 *
 * For a given flow, packets are not reordered (CoDel uses a FIFO)
 * head drops only.
 * ECN capability is on by शेष.
 * Low memory footprपूर्णांक (64 bytes per flow)
 */

काष्ठा fq_codel_flow अणु
	काष्ठा sk_buff	  *head;
	काष्ठा sk_buff	  *tail;
	काष्ठा list_head  flowchain;
	पूर्णांक		  deficit;
	काष्ठा codel_vars cvars;
पूर्ण; /* please try to keep this काष्ठाure <= 64 bytes */

काष्ठा fq_codel_sched_data अणु
	काष्ठा tcf_proto __rcu *filter_list; /* optional बाह्यal classअगरier */
	काष्ठा tcf_block *block;
	काष्ठा fq_codel_flow *flows;	/* Flows table [flows_cnt] */
	u32		*backlogs;	/* backlog table [flows_cnt] */
	u32		flows_cnt;	/* number of flows */
	u32		quantum;	/* psched_mtu(qdisc_dev(sch)); */
	u32		drop_batch_size;
	u32		memory_limit;
	काष्ठा codel_params cparams;
	काष्ठा codel_stats cstats;
	u32		memory_usage;
	u32		drop_overmemory;
	u32		drop_overlimit;
	u32		new_flow_count;

	काष्ठा list_head new_flows;	/* list of new flows */
	काष्ठा list_head old_flows;	/* list of old flows */
पूर्ण;

अटल अचिन्हित पूर्णांक fq_codel_hash(स्थिर काष्ठा fq_codel_sched_data *q,
				  काष्ठा sk_buff *skb)
अणु
	वापस reciprocal_scale(skb_get_hash(skb), q->flows_cnt);
पूर्ण

अटल अचिन्हित पूर्णांक fq_codel_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				      पूर्णांक *qerr)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा tcf_proto *filter;
	काष्ठा tcf_result res;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority) == sch->handle &&
	    TC_H_MIN(skb->priority) > 0 &&
	    TC_H_MIN(skb->priority) <= q->flows_cnt)
		वापस TC_H_MIN(skb->priority);

	filter = rcu_dereference_bh(q->filter_list);
	अगर (!filter)
		वापस fq_codel_hash(q, skb) + 1;

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

/* helper functions : might be changed when/अगर skb use a standard list_head */

/* हटाओ one skb from head of slot queue */
अटल अंतरभूत काष्ठा sk_buff *dequeue_head(काष्ठा fq_codel_flow *flow)
अणु
	काष्ठा sk_buff *skb = flow->head;

	flow->head = skb->next;
	skb_mark_not_on_list(skb);
	वापस skb;
पूर्ण

/* add skb to flow queue (tail add) */
अटल अंतरभूत व्योम flow_queue_add(काष्ठा fq_codel_flow *flow,
				  काष्ठा sk_buff *skb)
अणु
	अगर (flow->head == शून्य)
		flow->head = skb;
	अन्यथा
		flow->tail->next = skb;
	flow->tail = skb;
	skb->next = शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक fq_codel_drop(काष्ठा Qdisc *sch, अचिन्हित पूर्णांक max_packets,
				  काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक maxbacklog = 0, idx = 0, i, len;
	काष्ठा fq_codel_flow *flow;
	अचिन्हित पूर्णांक threshold;
	अचिन्हित पूर्णांक mem = 0;

	/* Queue is full! Find the fat flow and drop packet(s) from it.
	 * This might sound expensive, but with 1024 flows, we scan
	 * 4KB of memory, and we करोnt need to handle a complex tree
	 * in fast path (packet queue/enqueue) with many cache misses.
	 * In stress mode, we'll try to drop 64 packets from the flow,
	 * amortizing this linear lookup to one cache line per drop.
	 */
	क्रम (i = 0; i < q->flows_cnt; i++) अणु
		अगर (q->backlogs[i] > maxbacklog) अणु
			maxbacklog = q->backlogs[i];
			idx = i;
		पूर्ण
	पूर्ण

	/* Our goal is to drop half of this fat flow backlog */
	threshold = maxbacklog >> 1;

	flow = &q->flows[idx];
	len = 0;
	i = 0;
	करो अणु
		skb = dequeue_head(flow);
		len += qdisc_pkt_len(skb);
		mem += get_codel_cb(skb)->mem_usage;
		__qdisc_drop(skb, to_मुक्त);
	पूर्ण जबतक (++i < max_packets && len < threshold);

	/* Tell codel to increase its संकेत strength also */
	flow->cvars.count += i;
	q->backlogs[idx] -= len;
	q->memory_usage -= mem;
	sch->qstats.drops += i;
	sch->qstats.backlog -= len;
	sch->q.qlen -= i;
	वापस idx;
पूर्ण

अटल पूर्णांक fq_codel_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			    काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक idx, prev_backlog, prev_qlen;
	काष्ठा fq_codel_flow *flow;
	पूर्णांक ret;
	अचिन्हित पूर्णांक pkt_len;
	bool memory_limited;

	idx = fq_codel_classअगरy(skb, sch, &ret);
	अगर (idx == 0) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण
	idx--;

	codel_set_enqueue_समय(skb);
	flow = &q->flows[idx];
	flow_queue_add(flow, skb);
	q->backlogs[idx] += qdisc_pkt_len(skb);
	qdisc_qstats_backlog_inc(sch, skb);

	अगर (list_empty(&flow->flowchain)) अणु
		list_add_tail(&flow->flowchain, &q->new_flows);
		q->new_flow_count++;
		flow->deficit = q->quantum;
	पूर्ण
	get_codel_cb(skb)->mem_usage = skb->truesize;
	q->memory_usage += get_codel_cb(skb)->mem_usage;
	memory_limited = q->memory_usage > q->memory_limit;
	अगर (++sch->q.qlen <= sch->limit && !memory_limited)
		वापस NET_XMIT_SUCCESS;

	prev_backlog = sch->qstats.backlog;
	prev_qlen = sch->q.qlen;

	/* save this packet length as it might be dropped by fq_codel_drop() */
	pkt_len = qdisc_pkt_len(skb);
	/* fq_codel_drop() is quite expensive, as it perक्रमms a linear search
	 * in q->backlogs[] to find a fat flow.
	 * So instead of dropping a single packet, drop half of its backlog
	 * with a 64 packets limit to not add a too big cpu spike here.
	 */
	ret = fq_codel_drop(sch, q->drop_batch_size, to_मुक्त);

	prev_qlen -= sch->q.qlen;
	prev_backlog -= sch->qstats.backlog;
	q->drop_overlimit += prev_qlen;
	अगर (memory_limited)
		q->drop_overmemory += prev_qlen;

	/* As we dropped packet(s), better let upper stack know this.
	 * If we dropped a packet क्रम this flow, वापस NET_XMIT_CN,
	 * but in this हाल, our parents wont increase their backlogs.
	 */
	अगर (ret == idx) अणु
		qdisc_tree_reduce_backlog(sch, prev_qlen - 1,
					  prev_backlog - pkt_len);
		वापस NET_XMIT_CN;
	पूर्ण
	qdisc_tree_reduce_backlog(sch, prev_qlen, prev_backlog);
	वापस NET_XMIT_SUCCESS;
पूर्ण

/* This is the specअगरic function called from codel_dequeue()
 * to dequeue a packet from queue. Note: backlog is handled in
 * codel, we करोnt need to reduce it here.
 */
अटल काष्ठा sk_buff *dequeue_func(काष्ठा codel_vars *vars, व्योम *ctx)
अणु
	काष्ठा Qdisc *sch = ctx;
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा fq_codel_flow *flow;
	काष्ठा sk_buff *skb = शून्य;

	flow = container_of(vars, काष्ठा fq_codel_flow, cvars);
	अगर (flow->head) अणु
		skb = dequeue_head(flow);
		q->backlogs[flow - q->flows] -= qdisc_pkt_len(skb);
		q->memory_usage -= get_codel_cb(skb)->mem_usage;
		sch->q.qlen--;
		sch->qstats.backlog -= qdisc_pkt_len(skb);
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम drop_func(काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा Qdisc *sch = ctx;

	kमुक्त_skb(skb);
	qdisc_qstats_drop(sch);
पूर्ण

अटल काष्ठा sk_buff *fq_codel_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	काष्ठा fq_codel_flow *flow;
	काष्ठा list_head *head;

begin:
	head = &q->new_flows;
	अगर (list_empty(head)) अणु
		head = &q->old_flows;
		अगर (list_empty(head))
			वापस शून्य;
	पूर्ण
	flow = list_first_entry(head, काष्ठा fq_codel_flow, flowchain);

	अगर (flow->deficit <= 0) अणु
		flow->deficit += q->quantum;
		list_move_tail(&flow->flowchain, &q->old_flows);
		जाओ begin;
	पूर्ण

	skb = codel_dequeue(sch, &sch->qstats.backlog, &q->cparams,
			    &flow->cvars, &q->cstats, qdisc_pkt_len,
			    codel_get_enqueue_समय, drop_func, dequeue_func);

	अगर (!skb) अणु
		/* क्रमce a pass through old_flows to prevent starvation */
		अगर ((head == &q->new_flows) && !list_empty(&q->old_flows))
			list_move_tail(&flow->flowchain, &q->old_flows);
		अन्यथा
			list_del_init(&flow->flowchain);
		जाओ begin;
	पूर्ण
	qdisc_bstats_update(sch, skb);
	flow->deficit -= qdisc_pkt_len(skb);
	/* We cant call qdisc_tree_reduce_backlog() अगर our qlen is 0,
	 * or HTB crashes. Defer it क्रम next round.
	 */
	अगर (q->cstats.drop_count && sch->q.qlen) अणु
		qdisc_tree_reduce_backlog(sch, q->cstats.drop_count,
					  q->cstats.drop_len);
		q->cstats.drop_count = 0;
		q->cstats.drop_len = 0;
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम fq_codel_flow_purge(काष्ठा fq_codel_flow *flow)
अणु
	rtnl_kमुक्त_skbs(flow->head, flow->tail);
	flow->head = शून्य;
पूर्ण

अटल व्योम fq_codel_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	पूर्णांक i;

	INIT_LIST_HEAD(&q->new_flows);
	INIT_LIST_HEAD(&q->old_flows);
	क्रम (i = 0; i < q->flows_cnt; i++) अणु
		काष्ठा fq_codel_flow *flow = q->flows + i;

		fq_codel_flow_purge(flow);
		INIT_LIST_HEAD(&flow->flowchain);
		codel_vars_init(&flow->cvars);
	पूर्ण
	स_रखो(q->backlogs, 0, q->flows_cnt * माप(u32));
	sch->q.qlen = 0;
	sch->qstats.backlog = 0;
	q->memory_usage = 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy fq_codel_policy[TCA_FQ_CODEL_MAX + 1] = अणु
	[TCA_FQ_CODEL_TARGET]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_LIMIT]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_ECN]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_FLOWS]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_QUANTUM]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_CE_THRESHOLD] = अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_DROP_BATCH_SIZE] = अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CODEL_MEMORY_LIMIT] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक fq_codel_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_FQ_CODEL_MAX + 1];
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_FQ_CODEL_MAX, opt,
					  fq_codel_policy, शून्य);
	अगर (err < 0)
		वापस err;
	अगर (tb[TCA_FQ_CODEL_FLOWS]) अणु
		अगर (q->flows)
			वापस -EINVAL;
		q->flows_cnt = nla_get_u32(tb[TCA_FQ_CODEL_FLOWS]);
		अगर (!q->flows_cnt ||
		    q->flows_cnt > 65536)
			वापस -EINVAL;
	पूर्ण
	sch_tree_lock(sch);

	अगर (tb[TCA_FQ_CODEL_TARGET]) अणु
		u64 target = nla_get_u32(tb[TCA_FQ_CODEL_TARGET]);

		q->cparams.target = (target * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_FQ_CODEL_CE_THRESHOLD]) अणु
		u64 val = nla_get_u32(tb[TCA_FQ_CODEL_CE_THRESHOLD]);

		q->cparams.ce_threshold = (val * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_FQ_CODEL_INTERVAL]) अणु
		u64 पूर्णांकerval = nla_get_u32(tb[TCA_FQ_CODEL_INTERVAL]);

		q->cparams.पूर्णांकerval = (पूर्णांकerval * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_FQ_CODEL_LIMIT])
		sch->limit = nla_get_u32(tb[TCA_FQ_CODEL_LIMIT]);

	अगर (tb[TCA_FQ_CODEL_ECN])
		q->cparams.ecn = !!nla_get_u32(tb[TCA_FQ_CODEL_ECN]);

	अगर (tb[TCA_FQ_CODEL_QUANTUM])
		q->quantum = max(256U, nla_get_u32(tb[TCA_FQ_CODEL_QUANTUM]));

	अगर (tb[TCA_FQ_CODEL_DROP_BATCH_SIZE])
		q->drop_batch_size = max(1U, nla_get_u32(tb[TCA_FQ_CODEL_DROP_BATCH_SIZE]));

	अगर (tb[TCA_FQ_CODEL_MEMORY_LIMIT])
		q->memory_limit = min(1U << 31, nla_get_u32(tb[TCA_FQ_CODEL_MEMORY_LIMIT]));

	जबतक (sch->q.qlen > sch->limit ||
	       q->memory_usage > q->memory_limit) अणु
		काष्ठा sk_buff *skb = fq_codel_dequeue(sch);

		q->cstats.drop_len += qdisc_pkt_len(skb);
		rtnl_kमुक्त_skbs(skb, skb);
		q->cstats.drop_count++;
	पूर्ण
	qdisc_tree_reduce_backlog(sch, q->cstats.drop_count, q->cstats.drop_len);
	q->cstats.drop_count = 0;
	q->cstats.drop_len = 0;

	sch_tree_unlock(sch);
	वापस 0;
पूर्ण

अटल व्योम fq_codel_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	kvमुक्त(q->backlogs);
	kvमुक्त(q->flows);
पूर्ण

अटल पूर्णांक fq_codel_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	पूर्णांक i;
	पूर्णांक err;

	sch->limit = 10*1024;
	q->flows_cnt = 1024;
	q->memory_limit = 32 << 20; /* 32 MBytes */
	q->drop_batch_size = 64;
	q->quantum = psched_mtu(qdisc_dev(sch));
	INIT_LIST_HEAD(&q->new_flows);
	INIT_LIST_HEAD(&q->old_flows);
	codel_params_init(&q->cparams);
	codel_stats_init(&q->cstats);
	q->cparams.ecn = true;
	q->cparams.mtu = psched_mtu(qdisc_dev(sch));

	अगर (opt) अणु
		err = fq_codel_change(sch, opt, extack);
		अगर (err)
			जाओ init_failure;
	पूर्ण

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		जाओ init_failure;

	अगर (!q->flows) अणु
		q->flows = kvसुस्मृति(q->flows_cnt,
				    माप(काष्ठा fq_codel_flow),
				    GFP_KERNEL);
		अगर (!q->flows) अणु
			err = -ENOMEM;
			जाओ init_failure;
		पूर्ण
		q->backlogs = kvसुस्मृति(q->flows_cnt, माप(u32), GFP_KERNEL);
		अगर (!q->backlogs) अणु
			err = -ENOMEM;
			जाओ alloc_failure;
		पूर्ण
		क्रम (i = 0; i < q->flows_cnt; i++) अणु
			काष्ठा fq_codel_flow *flow = q->flows + i;

			INIT_LIST_HEAD(&flow->flowchain);
			codel_vars_init(&flow->cvars);
		पूर्ण
	पूर्ण
	अगर (sch->limit >= 1)
		sch->flags |= TCQ_F_CAN_BYPASS;
	अन्यथा
		sch->flags &= ~TCQ_F_CAN_BYPASS;
	वापस 0;

alloc_failure:
	kvमुक्त(q->flows);
	q->flows = शून्य;
init_failure:
	q->flows_cnt = 0;
	वापस err;
पूर्ण

अटल पूर्णांक fq_codel_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_FQ_CODEL_TARGET,
			codel_समय_प्रकारo_us(q->cparams.target)) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_LIMIT,
			sch->limit) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_INTERVAL,
			codel_समय_प्रकारo_us(q->cparams.पूर्णांकerval)) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_ECN,
			q->cparams.ecn) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_QUANTUM,
			q->quantum) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_DROP_BATCH_SIZE,
			q->drop_batch_size) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_MEMORY_LIMIT,
			q->memory_limit) ||
	    nla_put_u32(skb, TCA_FQ_CODEL_FLOWS,
			q->flows_cnt))
		जाओ nla_put_failure;

	अगर (q->cparams.ce_threshold != CODEL_DISABLED_THRESHOLD &&
	    nla_put_u32(skb, TCA_FQ_CODEL_CE_THRESHOLD,
			codel_समय_प्रकारo_us(q->cparams.ce_threshold)))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक fq_codel_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_fq_codel_xstats st = अणु
		.type				= TCA_FQ_CODEL_XSTATS_QDISC,
	पूर्ण;
	काष्ठा list_head *pos;

	st.qdisc_stats.maxpacket = q->cstats.maxpacket;
	st.qdisc_stats.drop_overlimit = q->drop_overlimit;
	st.qdisc_stats.ecn_mark = q->cstats.ecn_mark;
	st.qdisc_stats.new_flow_count = q->new_flow_count;
	st.qdisc_stats.ce_mark = q->cstats.ce_mark;
	st.qdisc_stats.memory_usage  = q->memory_usage;
	st.qdisc_stats.drop_overmemory = q->drop_overmemory;

	sch_tree_lock(sch);
	list_क्रम_each(pos, &q->new_flows)
		st.qdisc_stats.new_flows_len++;

	list_क्रम_each(pos, &q->old_flows)
		st.qdisc_stats.old_flows_len++;
	sch_tree_unlock(sch);

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल काष्ठा Qdisc *fq_codel_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ fq_codel_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ fq_codel_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
			      u32 classid)
अणु
	वापस 0;
पूर्ण

अटल व्योम fq_codel_unbind(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल काष्ठा tcf_block *fq_codel_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल पूर्णांक fq_codel_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	tcm->tcm_handle |= TC_H_MIN(cl);
	वापस 0;
पूर्ण

अटल पूर्णांक fq_codel_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				     काष्ठा gnet_dump *d)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	u32 idx = cl - 1;
	काष्ठा gnet_stats_queue qs = अणु 0 पूर्ण;
	काष्ठा tc_fq_codel_xstats xstats;

	अगर (idx < q->flows_cnt) अणु
		स्थिर काष्ठा fq_codel_flow *flow = &q->flows[idx];
		स्थिर काष्ठा sk_buff *skb;

		स_रखो(&xstats, 0, माप(xstats));
		xstats.type = TCA_FQ_CODEL_XSTATS_CLASS;
		xstats.class_stats.deficit = flow->deficit;
		xstats.class_stats.ldelay =
			codel_समय_प्रकारo_us(flow->cvars.ldelay);
		xstats.class_stats.count = flow->cvars.count;
		xstats.class_stats.lastcount = flow->cvars.lastcount;
		xstats.class_stats.dropping = flow->cvars.dropping;
		अगर (flow->cvars.dropping) अणु
			codel_tdअगरf_t delta = flow->cvars.drop_next -
					      codel_get_समय();

			xstats.class_stats.drop_next = (delta >= 0) ?
				codel_समय_प्रकारo_us(delta) :
				-codel_समय_प्रकारo_us(-delta);
		पूर्ण
		अगर (flow->head) अणु
			sch_tree_lock(sch);
			skb = flow->head;
			जबतक (skb) अणु
				qs.qlen++;
				skb = skb->next;
			पूर्ण
			sch_tree_unlock(sch);
		पूर्ण
		qs.backlog = q->backlogs[idx];
		qs.drops = 0;
	पूर्ण
	अगर (gnet_stats_copy_queue(d, शून्य, &qs, qs.qlen) < 0)
		वापस -1;
	अगर (idx < q->flows_cnt)
		वापस gnet_stats_copy_app(d, &xstats, माप(xstats));
	वापस 0;
पूर्ण

अटल व्योम fq_codel_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा fq_codel_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->flows_cnt; i++) अणु
		अगर (list_empty(&q->flows[i].flowchain) ||
		    arg->count < arg->skip) अणु
			arg->count++;
			जारी;
		पूर्ण
		अगर (arg->fn(sch, i + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops fq_codel_class_ops = अणु
	.leaf		=	fq_codel_leaf,
	.find		=	fq_codel_find,
	.tcf_block	=	fq_codel_tcf_block,
	.bind_tcf	=	fq_codel_bind,
	.unbind_tcf	=	fq_codel_unbind,
	.dump		=	fq_codel_dump_class,
	.dump_stats	=	fq_codel_dump_class_stats,
	.walk		=	fq_codel_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops fq_codel_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		=	&fq_codel_class_ops,
	.id		=	"fq_codel",
	.priv_size	=	माप(काष्ठा fq_codel_sched_data),
	.enqueue	=	fq_codel_enqueue,
	.dequeue	=	fq_codel_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	fq_codel_init,
	.reset		=	fq_codel_reset,
	.destroy	=	fq_codel_destroy,
	.change		=	fq_codel_change,
	.dump		=	fq_codel_dump,
	.dump_stats =	fq_codel_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init fq_codel_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&fq_codel_qdisc_ops);
पूर्ण

अटल व्योम __निकास fq_codel_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&fq_codel_qdisc_ops);
पूर्ण

module_init(fq_codel_module_init)
module_निकास(fq_codel_module_निकास)
MODULE_AUTHOR("Eric Dumazet");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fair Queue CoDel discipline");
