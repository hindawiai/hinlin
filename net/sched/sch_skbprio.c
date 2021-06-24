<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_skbprio.c  SKB Priority Queue.
 *
 * Authors:	Nishanth Devarajan, <ndev2021@gmail.com>
 *		Cody Doucette, <करोucette@bu.edu>
 *	        original idea by Michel Machaकरो, Cody Doucette, and Qiaobin Fu
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sch_generic.h>
#समावेश <net/inet_ecn.h>

/*		SKB Priority Queue
 *	=================================
 *
 * Skbprio (SKB Priority Queue) is a queueing discipline that prioritizes
 * packets according to their skb->priority field. Under congestion,
 * Skbprio drops alपढ़ोy-enqueued lower priority packets to make space
 * available क्रम higher priority packets; it was conceived as a solution
 * क्रम denial-of-service defenses that need to route packets with dअगरferent
 * priorities as a mean to overcome DoS attacks.
 */

काष्ठा skbprio_sched_data अणु
	/* Queue state. */
	काष्ठा sk_buff_head qdiscs[SKBPRIO_MAX_PRIORITY];
	काष्ठा gnet_stats_queue qstats[SKBPRIO_MAX_PRIORITY];
	u16 highest_prio;
	u16 lowest_prio;
पूर्ण;

अटल u16 calc_new_high_prio(स्थिर काष्ठा skbprio_sched_data *q)
अणु
	पूर्णांक prio;

	क्रम (prio = q->highest_prio - 1; prio >= q->lowest_prio; prio--) अणु
		अगर (!skb_queue_empty(&q->qdiscs[prio]))
			वापस prio;
	पूर्ण

	/* SKB queue is empty, वापस 0 (शेष highest priority setting). */
	वापस 0;
पूर्ण

अटल u16 calc_new_low_prio(स्थिर काष्ठा skbprio_sched_data *q)
अणु
	पूर्णांक prio;

	क्रम (prio = q->lowest_prio + 1; prio <= q->highest_prio; prio++) अणु
		अगर (!skb_queue_empty(&q->qdiscs[prio]))
			वापस prio;
	पूर्ण

	/* SKB queue is empty, वापस SKBPRIO_MAX_PRIORITY - 1
	 * (शेष lowest priority setting).
	 */
	वापस SKBPRIO_MAX_PRIORITY - 1;
पूर्ण

अटल पूर्णांक skbprio_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			  काष्ठा sk_buff **to_मुक्त)
अणु
	स्थिर अचिन्हित पूर्णांक max_priority = SKBPRIO_MAX_PRIORITY - 1;
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff_head *qdisc;
	काष्ठा sk_buff_head *lp_qdisc;
	काष्ठा sk_buff *to_drop;
	u16 prio, lp;

	/* Obtain the priority of @skb. */
	prio = min(skb->priority, max_priority);

	qdisc = &q->qdiscs[prio];
	अगर (sch->q.qlen < sch->limit) अणु
		__skb_queue_tail(qdisc, skb);
		qdisc_qstats_backlog_inc(sch, skb);
		q->qstats[prio].backlog += qdisc_pkt_len(skb);

		/* Check to update highest and lowest priorities. */
		अगर (prio > q->highest_prio)
			q->highest_prio = prio;

		अगर (prio < q->lowest_prio)
			q->lowest_prio = prio;

		sch->q.qlen++;
		वापस NET_XMIT_SUCCESS;
	पूर्ण

	/* If this packet has the lowest priority, drop it. */
	lp = q->lowest_prio;
	अगर (prio <= lp) अणु
		q->qstats[prio].drops++;
		q->qstats[prio].overlimits++;
		वापस qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण

	__skb_queue_tail(qdisc, skb);
	qdisc_qstats_backlog_inc(sch, skb);
	q->qstats[prio].backlog += qdisc_pkt_len(skb);

	/* Drop the packet at the tail of the lowest priority qdisc. */
	lp_qdisc = &q->qdiscs[lp];
	to_drop = __skb_dequeue_tail(lp_qdisc);
	BUG_ON(!to_drop);
	qdisc_qstats_backlog_dec(sch, to_drop);
	qdisc_drop(to_drop, sch, to_मुक्त);

	q->qstats[lp].backlog -= qdisc_pkt_len(to_drop);
	q->qstats[lp].drops++;
	q->qstats[lp].overlimits++;

	/* Check to update highest and lowest priorities. */
	अगर (skb_queue_empty(lp_qdisc)) अणु
		अगर (q->lowest_prio == q->highest_prio) अणु
			/* The incoming packet is the only packet in queue. */
			BUG_ON(sch->q.qlen != 1);
			q->lowest_prio = prio;
			q->highest_prio = prio;
		पूर्ण अन्यथा अणु
			q->lowest_prio = calc_new_low_prio(q);
		पूर्ण
	पूर्ण

	अगर (prio > q->highest_prio)
		q->highest_prio = prio;

	वापस NET_XMIT_CN;
पूर्ण

अटल काष्ठा sk_buff *skbprio_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff_head *hpq = &q->qdiscs[q->highest_prio];
	काष्ठा sk_buff *skb = __skb_dequeue(hpq);

	अगर (unlikely(!skb))
		वापस शून्य;

	sch->q.qlen--;
	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);

	q->qstats[q->highest_prio].backlog -= qdisc_pkt_len(skb);

	/* Update highest priority field. */
	अगर (skb_queue_empty(hpq)) अणु
		अगर (q->lowest_prio == q->highest_prio) अणु
			BUG_ON(sch->q.qlen);
			q->highest_prio = 0;
			q->lowest_prio = SKBPRIO_MAX_PRIORITY - 1;
		पूर्ण अन्यथा अणु
			q->highest_prio = calc_new_high_prio(q);
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक skbprio_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_skbprio_qopt *ctl = nla_data(opt);

	अगर (opt->nla_len != nla_attr_size(माप(*ctl)))
		वापस -EINVAL;

	sch->limit = ctl->limit;
	वापस 0;
पूर्ण

अटल पूर्णांक skbprio_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	/* Initialise all queues, one क्रम each possible priority. */
	क्रम (prio = 0; prio < SKBPRIO_MAX_PRIORITY; prio++)
		__skb_queue_head_init(&q->qdiscs[prio]);

	स_रखो(&q->qstats, 0, माप(q->qstats));
	q->highest_prio = 0;
	q->lowest_prio = SKBPRIO_MAX_PRIORITY - 1;
	sch->limit = 64;
	अगर (!opt)
		वापस 0;

	वापस skbprio_change(sch, opt, extack);
पूर्ण

अटल पूर्णांक skbprio_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा tc_skbprio_qopt opt;

	opt.limit = sch->limit;

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		वापस -1;

	वापस skb->len;
पूर्ण

अटल व्योम skbprio_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	sch->qstats.backlog = 0;
	sch->q.qlen = 0;

	क्रम (prio = 0; prio < SKBPRIO_MAX_PRIORITY; prio++)
		__skb_queue_purge(&q->qdiscs[prio]);

	स_रखो(&q->qstats, 0, माप(q->qstats));
	q->highest_prio = 0;
	q->lowest_prio = SKBPRIO_MAX_PRIORITY - 1;
पूर्ण

अटल व्योम skbprio_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	क्रम (prio = 0; prio < SKBPRIO_MAX_PRIORITY; prio++)
		__skb_queue_purge(&q->qdiscs[prio]);
पूर्ण

अटल काष्ठा Qdisc *skbprio_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ skbprio_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक skbprio_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			     काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	tcm->tcm_handle |= TC_H_MIN(cl);
	वापस 0;
पूर्ण

अटल पूर्णांक skbprio_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				   काष्ठा gnet_dump *d)
अणु
	काष्ठा skbprio_sched_data *q = qdisc_priv(sch);
	अगर (gnet_stats_copy_queue(d, शून्य, &q->qstats[cl - 1],
		q->qstats[cl - 1].qlen) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम skbprio_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < SKBPRIO_MAX_PRIORITY; i++) अणु
		अगर (arg->count < arg->skip) अणु
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

अटल स्थिर काष्ठा Qdisc_class_ops skbprio_class_ops = अणु
	.leaf		=	skbprio_leaf,
	.find		=	skbprio_find,
	.dump		=	skbprio_dump_class,
	.dump_stats	=	skbprio_dump_class_stats,
	.walk		=	skbprio_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops skbprio_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		=	&skbprio_class_ops,
	.id		=	"skbprio",
	.priv_size	=	माप(काष्ठा skbprio_sched_data),
	.enqueue	=	skbprio_enqueue,
	.dequeue	=	skbprio_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	skbprio_init,
	.reset		=	skbprio_reset,
	.change		=	skbprio_change,
	.dump		=	skbprio_dump,
	.destroy	=	skbprio_destroy,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init skbprio_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&skbprio_qdisc_ops);
पूर्ण

अटल व्योम __निकास skbprio_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&skbprio_qdisc_ops);
पूर्ण

module_init(skbprio_module_init)
module_निकास(skbprio_module_निकास)

MODULE_LICENSE("GPL");
