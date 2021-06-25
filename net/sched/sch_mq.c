<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_mq.c		Classful multiqueue dummy scheduler
 *
 * Copyright (c) 2009 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sch_generic.h>

काष्ठा mq_sched अणु
	काष्ठा Qdisc		**qdiscs;
पूर्ण;

अटल पूर्णांक mq_offload(काष्ठा Qdisc *sch, क्रमागत tc_mq_command cmd)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_mq_qopt_offload opt = अणु
		.command = cmd,
		.handle = sch->handle,
	पूर्ण;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस -EOPNOTSUPP;

	वापस dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_MQ, &opt);
पूर्ण

अटल पूर्णांक mq_offload_stats(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_mq_qopt_offload opt = अणु
		.command = TC_MQ_STATS,
		.handle = sch->handle,
		.stats = अणु
			.bstats = &sch->bstats,
			.qstats = &sch->qstats,
		पूर्ण,
	पूर्ण;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_MQ, &opt);
पूर्ण

अटल व्योम mq_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mq_sched *priv = qdisc_priv(sch);
	अचिन्हित पूर्णांक ntx;

	mq_offload(sch, TC_MQ_DESTROY);

	अगर (!priv->qdiscs)
		वापस;
	क्रम (ntx = 0; ntx < dev->num_tx_queues && priv->qdiscs[ntx]; ntx++)
		qdisc_put(priv->qdiscs[ntx]);
	kमुक्त(priv->qdiscs);
पूर्ण

अटल पूर्णांक mq_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mq_sched *priv = qdisc_priv(sch);
	काष्ठा netdev_queue *dev_queue;
	काष्ठा Qdisc *qdisc;
	अचिन्हित पूर्णांक ntx;

	अगर (sch->parent != TC_H_ROOT)
		वापस -EOPNOTSUPP;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -EOPNOTSUPP;

	/* pre-allocate qdiscs, attachment can't fail */
	priv->qdiscs = kसुस्मृति(dev->num_tx_queues, माप(priv->qdiscs[0]),
			       GFP_KERNEL);
	अगर (!priv->qdiscs)
		वापस -ENOMEM;

	क्रम (ntx = 0; ntx < dev->num_tx_queues; ntx++) अणु
		dev_queue = netdev_get_tx_queue(dev, ntx);
		qdisc = qdisc_create_dflt(dev_queue, get_शेष_qdisc_ops(dev, ntx),
					  TC_H_MAKE(TC_H_MAJ(sch->handle),
						    TC_H_MIN(ntx + 1)),
					  extack);
		अगर (!qdisc)
			वापस -ENOMEM;
		priv->qdiscs[ntx] = qdisc;
		qdisc->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	पूर्ण

	sch->flags |= TCQ_F_MQROOT;

	mq_offload(sch, TC_MQ_CREATE);
	वापस 0;
पूर्ण

अटल व्योम mq_attach(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mq_sched *priv = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc, *old;
	अचिन्हित पूर्णांक ntx;

	क्रम (ntx = 0; ntx < dev->num_tx_queues; ntx++) अणु
		qdisc = priv->qdiscs[ntx];
		old = dev_graft_qdisc(qdisc->dev_queue, qdisc);
		अगर (old)
			qdisc_put(old);
#अगर_घोषित CONFIG_NET_SCHED
		अगर (ntx < dev->real_num_tx_queues)
			qdisc_hash_add(qdisc, false);
#पूर्ण_अगर

	पूर्ण
	kमुक्त(priv->qdiscs);
	priv->qdiscs = शून्य;
पूर्ण

अटल पूर्णांक mq_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा Qdisc *qdisc;
	अचिन्हित पूर्णांक ntx;
	__u32 qlen = 0;

	sch->q.qlen = 0;
	स_रखो(&sch->bstats, 0, माप(sch->bstats));
	स_रखो(&sch->qstats, 0, माप(sch->qstats));

	/* MQ supports lockless qdiscs. However, statistics accounting needs
	 * to account क्रम all, none, or a mix of locked and unlocked child
	 * qdiscs. Percpu stats are added to counters in-band and locking
	 * qdisc totals are added at end.
	 */
	क्रम (ntx = 0; ntx < dev->num_tx_queues; ntx++) अणु
		qdisc = netdev_get_tx_queue(dev, ntx)->qdisc_sleeping;
		spin_lock_bh(qdisc_lock(qdisc));

		अगर (qdisc_is_percpu_stats(qdisc)) अणु
			qlen = qdisc_qlen_sum(qdisc);
			__gnet_stats_copy_basic(शून्य, &sch->bstats,
						qdisc->cpu_bstats,
						&qdisc->bstats);
			__gnet_stats_copy_queue(&sch->qstats,
						qdisc->cpu_qstats,
						&qdisc->qstats, qlen);
			sch->q.qlen		+= qlen;
		पूर्ण अन्यथा अणु
			sch->q.qlen		+= qdisc->q.qlen;
			sch->bstats.bytes	+= qdisc->bstats.bytes;
			sch->bstats.packets	+= qdisc->bstats.packets;
			sch->qstats.qlen	+= qdisc->qstats.qlen;
			sch->qstats.backlog	+= qdisc->qstats.backlog;
			sch->qstats.drops	+= qdisc->qstats.drops;
			sch->qstats.requeues	+= qdisc->qstats.requeues;
			sch->qstats.overlimits	+= qdisc->qstats.overlimits;
		पूर्ण

		spin_unlock_bh(qdisc_lock(qdisc));
	पूर्ण

	वापस mq_offload_stats(sch);
पूर्ण

अटल काष्ठा netdev_queue *mq_queue_get(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित दीर्घ ntx = cl - 1;

	अगर (ntx >= dev->num_tx_queues)
		वापस शून्य;
	वापस netdev_get_tx_queue(dev, ntx);
पूर्ण

अटल काष्ठा netdev_queue *mq_select_queue(काष्ठा Qdisc *sch,
					    काष्ठा tcmsg *tcm)
अणु
	वापस mq_queue_get(sch, TC_H_MIN(tcm->tcm_parent));
पूर्ण

अटल पूर्णांक mq_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl, काष्ठा Qdisc *new,
		    काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_queue *dev_queue = mq_queue_get(sch, cl);
	काष्ठा tc_mq_qopt_offload graft_offload;
	काष्ठा net_device *dev = qdisc_dev(sch);

	अगर (dev->flags & IFF_UP)
		dev_deactivate(dev);

	*old = dev_graft_qdisc(dev_queue, new);
	अगर (new)
		new->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	अगर (dev->flags & IFF_UP)
		dev_activate(dev);

	graft_offload.handle = sch->handle;
	graft_offload.graft_params.queue = cl - 1;
	graft_offload.graft_params.child_handle = new ? new->handle : 0;
	graft_offload.command = TC_MQ_GRAFT;

	qdisc_offload_graft_helper(qdisc_dev(sch), sch, new, *old,
				   TC_SETUP_QDISC_MQ, &graft_offload, extack);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *mq_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा netdev_queue *dev_queue = mq_queue_get(sch, cl);

	वापस dev_queue->qdisc_sleeping;
पूर्ण

अटल अचिन्हित दीर्घ mq_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	अचिन्हित पूर्णांक ntx = TC_H_MIN(classid);

	अगर (!mq_queue_get(sch, ntx))
		वापस 0;
	वापस ntx;
पूर्ण

अटल पूर्णांक mq_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			 काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा netdev_queue *dev_queue = mq_queue_get(sch, cl);

	tcm->tcm_parent = TC_H_ROOT;
	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = dev_queue->qdisc_sleeping->handle;
	वापस 0;
पूर्ण

अटल पूर्णांक mq_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			       काष्ठा gnet_dump *d)
अणु
	काष्ठा netdev_queue *dev_queue = mq_queue_get(sch, cl);

	sch = dev_queue->qdisc_sleeping;
	अगर (gnet_stats_copy_basic(&sch->running, d, sch->cpu_bstats,
				  &sch->bstats) < 0 ||
	    qdisc_qstats_copy(d, sch) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम mq_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित पूर्णांक ntx;

	अगर (arg->stop)
		वापस;

	arg->count = arg->skip;
	क्रम (ntx = arg->skip; ntx < dev->num_tx_queues; ntx++) अणु
		अगर (arg->fn(sch, ntx + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops mq_class_ops = अणु
	.select_queue	= mq_select_queue,
	.graft		= mq_graft,
	.leaf		= mq_leaf,
	.find		= mq_find,
	.walk		= mq_walk,
	.dump		= mq_dump_class,
	.dump_stats	= mq_dump_class_stats,
पूर्ण;

काष्ठा Qdisc_ops mq_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &mq_class_ops,
	.id		= "mq",
	.priv_size	= माप(काष्ठा mq_sched),
	.init		= mq_init,
	.destroy	= mq_destroy,
	.attach		= mq_attach,
	.dump		= mq_dump,
	.owner		= THIS_MODULE,
पूर्ण;
