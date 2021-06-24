<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_fअगरo.c	The simplest FIFO queue.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

/* 1 band FIFO pseuकरो-"scheduler" */

अटल पूर्णांक bfअगरo_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			 काष्ठा sk_buff **to_मुक्त)
अणु
	अगर (likely(sch->qstats.backlog + qdisc_pkt_len(skb) <= sch->limit))
		वापस qdisc_enqueue_tail(skb, sch);

	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल पूर्णांक pfअगरo_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			 काष्ठा sk_buff **to_मुक्त)
अणु
	अगर (likely(sch->q.qlen < sch->limit))
		वापस qdisc_enqueue_tail(skb, sch);

	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल पूर्णांक pfअगरo_tail_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			      काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक prev_backlog;

	अगर (likely(sch->q.qlen < sch->limit))
		वापस qdisc_enqueue_tail(skb, sch);

	prev_backlog = sch->qstats.backlog;
	/* queue full, हटाओ one skb to fulfill the limit */
	__qdisc_queue_drop_head(sch, &sch->q, to_मुक्त);
	qdisc_qstats_drop(sch);
	qdisc_enqueue_tail(skb, sch);

	qdisc_tree_reduce_backlog(sch, 0, prev_backlog - sch->qstats.backlog);
	वापस NET_XMIT_CN;
पूर्ण

अटल व्योम fअगरo_offload_init(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_fअगरo_qopt_offload qopt;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_FIFO_REPLACE;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_FIFO, &qopt);
पूर्ण

अटल व्योम fअगरo_offload_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_fअगरo_qopt_offload qopt;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_FIFO_DESTROY;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_FIFO, &qopt);
पूर्ण

अटल पूर्णांक fअगरo_offload_dump(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_fअगरo_qopt_offload qopt;

	qopt.command = TC_FIFO_STATS;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.stats.bstats = &sch->bstats;
	qopt.stats.qstats = &sch->qstats;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_FIFO, &qopt);
पूर्ण

अटल पूर्णांक __fअगरo_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	bool bypass;
	bool is_bfअगरo = sch->ops == &bfअगरo_qdisc_ops;

	अगर (opt == शून्य) अणु
		u32 limit = qdisc_dev(sch)->tx_queue_len;

		अगर (is_bfअगरo)
			limit *= psched_mtu(qdisc_dev(sch));

		sch->limit = limit;
	पूर्ण अन्यथा अणु
		काष्ठा tc_fअगरo_qopt *ctl = nla_data(opt);

		अगर (nla_len(opt) < माप(*ctl))
			वापस -EINVAL;

		sch->limit = ctl->limit;
	पूर्ण

	अगर (is_bfअगरo)
		bypass = sch->limit >= psched_mtu(qdisc_dev(sch));
	अन्यथा
		bypass = sch->limit >= 1;

	अगर (bypass)
		sch->flags |= TCQ_F_CAN_BYPASS;
	अन्यथा
		sch->flags &= ~TCQ_F_CAN_BYPASS;

	वापस 0;
पूर्ण

अटल पूर्णांक fअगरo_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = __fअगरo_init(sch, opt, extack);
	अगर (err)
		वापस err;

	fअगरo_offload_init(sch);
	वापस 0;
पूर्ण

अटल पूर्णांक fअगरo_hd_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	वापस __fअगरo_init(sch, opt, extack);
पूर्ण

अटल व्योम fअगरo_destroy(काष्ठा Qdisc *sch)
अणु
	fअगरo_offload_destroy(sch);
पूर्ण

अटल पूर्णांक __fअगरo_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा tc_fअगरo_qopt opt = अणु .limit = sch->limit पूर्ण;

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक fअगरo_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = fअगरo_offload_dump(sch);
	अगर (err)
		वापस err;

	वापस __fअगरo_dump(sch, skb);
पूर्ण

अटल पूर्णांक fअगरo_hd_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	वापस __fअगरo_dump(sch, skb);
पूर्ण

काष्ठा Qdisc_ops pfअगरo_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"pfifo",
	.priv_size	=	0,
	.enqueue	=	pfअगरo_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fअगरo_init,
	.destroy	=	fअगरo_destroy,
	.reset		=	qdisc_reset_queue,
	.change		=	fअगरo_init,
	.dump		=	fअगरo_dump,
	.owner		=	THIS_MODULE,
पूर्ण;
EXPORT_SYMBOL(pfअगरo_qdisc_ops);

काष्ठा Qdisc_ops bfअगरo_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"bfifo",
	.priv_size	=	0,
	.enqueue	=	bfअगरo_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fअगरo_init,
	.destroy	=	fअगरo_destroy,
	.reset		=	qdisc_reset_queue,
	.change		=	fअगरo_init,
	.dump		=	fअगरo_dump,
	.owner		=	THIS_MODULE,
पूर्ण;
EXPORT_SYMBOL(bfअगरo_qdisc_ops);

काष्ठा Qdisc_ops pfअगरo_head_drop_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"pfifo_head_drop",
	.priv_size	=	0,
	.enqueue	=	pfअगरo_tail_enqueue,
	.dequeue	=	qdisc_dequeue_head,
	.peek		=	qdisc_peek_head,
	.init		=	fअगरo_hd_init,
	.reset		=	qdisc_reset_queue,
	.change		=	fअगरo_hd_init,
	.dump		=	fअगरo_hd_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

/* Pass size change message करोwn to embedded FIFO */
पूर्णांक fअगरo_set_limit(काष्ठा Qdisc *q, अचिन्हित पूर्णांक limit)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक ret = -ENOMEM;

	/* Hack to aव्योम sending change message to non-FIFO */
	अगर (म_भेदन(q->ops->id + 1, "fifo", 4) != 0)
		वापस 0;

	nla = kदो_स्मृति(nla_attr_size(माप(काष्ठा tc_fअगरo_qopt)), GFP_KERNEL);
	अगर (nla) अणु
		nla->nla_type = RTM_NEWQDISC;
		nla->nla_len = nla_attr_size(माप(काष्ठा tc_fअगरo_qopt));
		((काष्ठा tc_fअगरo_qopt *)nla_data(nla))->limit = limit;

		ret = q->ops->change(q, nla, शून्य);
		kमुक्त(nla);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fअगरo_set_limit);

काष्ठा Qdisc *fअगरo_create_dflt(काष्ठा Qdisc *sch, काष्ठा Qdisc_ops *ops,
			       अचिन्हित पूर्णांक limit,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा Qdisc *q;
	पूर्णांक err = -ENOMEM;

	q = qdisc_create_dflt(sch->dev_queue, ops, TC_H_MAKE(sch->handle, 1),
			      extack);
	अगर (q) अणु
		err = fअगरo_set_limit(q, limit);
		अगर (err < 0) अणु
			qdisc_put(q);
			q = शून्य;
		पूर्ण
	पूर्ण

	वापस q ? : ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(fअगरo_create_dflt);
