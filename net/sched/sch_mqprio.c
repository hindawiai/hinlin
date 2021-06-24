<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_mqprio.c
 *
 * Copyright (c) 2010 John Fastabend <john.r.fastabend@पूर्णांकel.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>

काष्ठा mqprio_sched अणु
	काष्ठा Qdisc		**qdiscs;
	u16 mode;
	u16 shaper;
	पूर्णांक hw_offload;
	u32 flags;
	u64 min_rate[TC_QOPT_MAX_QUEUE];
	u64 max_rate[TC_QOPT_MAX_QUEUE];
पूर्ण;

अटल व्योम mqprio_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mqprio_sched *priv = qdisc_priv(sch);
	अचिन्हित पूर्णांक ntx;

	अगर (priv->qdiscs) अणु
		क्रम (ntx = 0;
		     ntx < dev->num_tx_queues && priv->qdiscs[ntx];
		     ntx++)
			qdisc_put(priv->qdiscs[ntx]);
		kमुक्त(priv->qdiscs);
	पूर्ण

	अगर (priv->hw_offload && dev->netdev_ops->nकरो_setup_tc) अणु
		काष्ठा tc_mqprio_qopt_offload mqprio = अणु अणु 0 पूर्ण पूर्ण;

		चयन (priv->mode) अणु
		हाल TC_MQPRIO_MODE_DCB:
		हाल TC_MQPRIO_MODE_CHANNEL:
			dev->netdev_ops->nकरो_setup_tc(dev,
						      TC_SETUP_QDISC_MQPRIO,
						      &mqprio);
			अवरोध;
		शेष:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_set_num_tc(dev, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक mqprio_parse_opt(काष्ठा net_device *dev, काष्ठा tc_mqprio_qopt *qopt)
अणु
	पूर्णांक i, j;

	/* Verअगरy num_tc is not out of max range */
	अगर (qopt->num_tc > TC_MAX_QUEUE)
		वापस -EINVAL;

	/* Verअगरy priority mapping uses valid tcs */
	क्रम (i = 0; i < TC_BITMASK + 1; i++) अणु
		अगर (qopt->prio_tc_map[i] >= qopt->num_tc)
			वापस -EINVAL;
	पूर्ण

	/* Limit qopt->hw to maximum supported offload value.  Drivers have
	 * the option of overriding this later अगर they करोn't support the a
	 * given offload type.
	 */
	अगर (qopt->hw > TC_MQPRIO_HW_OFFLOAD_MAX)
		qopt->hw = TC_MQPRIO_HW_OFFLOAD_MAX;

	/* If hardware offload is requested we will leave it to the device
	 * to either populate the queue counts itself or to validate the
	 * provided queue counts.  If nकरो_setup_tc is not present then
	 * hardware करोesn't support offload and we should वापस an error.
	 */
	अगर (qopt->hw)
		वापस dev->netdev_ops->nकरो_setup_tc ? 0 : -EINVAL;

	क्रम (i = 0; i < qopt->num_tc; i++) अणु
		अचिन्हित पूर्णांक last = qopt->offset[i] + qopt->count[i];

		/* Verअगरy the queue count is in tx range being equal to the
		 * real_num_tx_queues indicates the last queue is in use.
		 */
		अगर (qopt->offset[i] >= dev->real_num_tx_queues ||
		    !qopt->count[i] ||
		    last > dev->real_num_tx_queues)
			वापस -EINVAL;

		/* Verअगरy that the offset and counts करो not overlap */
		क्रम (j = i + 1; j < qopt->num_tc; j++) अणु
			अगर (last > qopt->offset[j])
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy mqprio_policy[TCA_MQPRIO_MAX + 1] = अणु
	[TCA_MQPRIO_MODE]	= अणु .len = माप(u16) पूर्ण,
	[TCA_MQPRIO_SHAPER]	= अणु .len = माप(u16) पूर्ण,
	[TCA_MQPRIO_MIN_RATE64]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_MQPRIO_MAX_RATE64]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक parse_attr(काष्ठा nlattr *tb[], पूर्णांक maxtype, काष्ठा nlattr *nla,
		      स्थिर काष्ठा nla_policy *policy, पूर्णांक len)
अणु
	पूर्णांक nested_len = nla_len(nla) - NLA_ALIGN(len);

	अगर (nested_len >= nla_attr_size(0))
		वापस nla_parse_deprecated(tb, maxtype,
					    nla_data(nla) + NLA_ALIGN(len),
					    nested_len, policy, शून्य);

	स_रखो(tb, 0, माप(काष्ठा nlattr *) * (maxtype + 1));
	वापस 0;
पूर्ण

अटल पूर्णांक mqprio_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mqprio_sched *priv = qdisc_priv(sch);
	काष्ठा netdev_queue *dev_queue;
	काष्ठा Qdisc *qdisc;
	पूर्णांक i, err = -EOPNOTSUPP;
	काष्ठा tc_mqprio_qopt *qopt = शून्य;
	काष्ठा nlattr *tb[TCA_MQPRIO_MAX + 1];
	काष्ठा nlattr *attr;
	पूर्णांक rem;
	पूर्णांक len;

	BUILD_BUG_ON(TC_MAX_QUEUE != TC_QOPT_MAX_QUEUE);
	BUILD_BUG_ON(TC_BITMASK != TC_QOPT_BITMASK);

	अगर (sch->parent != TC_H_ROOT)
		वापस -EOPNOTSUPP;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -EOPNOTSUPP;

	/* make certain can allocate enough classids to handle queues */
	अगर (dev->num_tx_queues >= TC_H_MIN_PRIORITY)
		वापस -ENOMEM;

	अगर (!opt || nla_len(opt) < माप(*qopt))
		वापस -EINVAL;

	qopt = nla_data(opt);
	अगर (mqprio_parse_opt(dev, qopt))
		वापस -EINVAL;

	len = nla_len(opt) - NLA_ALIGN(माप(*qopt));
	अगर (len > 0) अणु
		err = parse_attr(tb, TCA_MQPRIO_MAX, opt, mqprio_policy,
				 माप(*qopt));
		अगर (err < 0)
			वापस err;

		अगर (!qopt->hw)
			वापस -EINVAL;

		अगर (tb[TCA_MQPRIO_MODE]) अणु
			priv->flags |= TC_MQPRIO_F_MODE;
			priv->mode = *(u16 *)nla_data(tb[TCA_MQPRIO_MODE]);
		पूर्ण

		अगर (tb[TCA_MQPRIO_SHAPER]) अणु
			priv->flags |= TC_MQPRIO_F_SHAPER;
			priv->shaper = *(u16 *)nla_data(tb[TCA_MQPRIO_SHAPER]);
		पूर्ण

		अगर (tb[TCA_MQPRIO_MIN_RATE64]) अणु
			अगर (priv->shaper != TC_MQPRIO_SHAPER_BW_RATE)
				वापस -EINVAL;
			i = 0;
			nla_क्रम_each_nested(attr, tb[TCA_MQPRIO_MIN_RATE64],
					    rem) अणु
				अगर (nla_type(attr) != TCA_MQPRIO_MIN_RATE64)
					वापस -EINVAL;
				अगर (i >= qopt->num_tc)
					अवरोध;
				priv->min_rate[i] = *(u64 *)nla_data(attr);
				i++;
			पूर्ण
			priv->flags |= TC_MQPRIO_F_MIN_RATE;
		पूर्ण

		अगर (tb[TCA_MQPRIO_MAX_RATE64]) अणु
			अगर (priv->shaper != TC_MQPRIO_SHAPER_BW_RATE)
				वापस -EINVAL;
			i = 0;
			nla_क्रम_each_nested(attr, tb[TCA_MQPRIO_MAX_RATE64],
					    rem) अणु
				अगर (nla_type(attr) != TCA_MQPRIO_MAX_RATE64)
					वापस -EINVAL;
				अगर (i >= qopt->num_tc)
					अवरोध;
				priv->max_rate[i] = *(u64 *)nla_data(attr);
				i++;
			पूर्ण
			priv->flags |= TC_MQPRIO_F_MAX_RATE;
		पूर्ण
	पूर्ण

	/* pre-allocate qdisc, attachment can't fail */
	priv->qdiscs = kसुस्मृति(dev->num_tx_queues, माप(priv->qdiscs[0]),
			       GFP_KERNEL);
	अगर (!priv->qdiscs)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		dev_queue = netdev_get_tx_queue(dev, i);
		qdisc = qdisc_create_dflt(dev_queue,
					  get_शेष_qdisc_ops(dev, i),
					  TC_H_MAKE(TC_H_MAJ(sch->handle),
						    TC_H_MIN(i + 1)), extack);
		अगर (!qdisc)
			वापस -ENOMEM;

		priv->qdiscs[i] = qdisc;
		qdisc->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	पूर्ण

	/* If the mqprio options indicate that hardware should own
	 * the queue mapping then run nकरो_setup_tc otherwise use the
	 * supplied and verअगरied mapping
	 */
	अगर (qopt->hw) अणु
		काष्ठा tc_mqprio_qopt_offload mqprio = अणु.qopt = *qoptपूर्ण;

		चयन (priv->mode) अणु
		हाल TC_MQPRIO_MODE_DCB:
			अगर (priv->shaper != TC_MQPRIO_SHAPER_DCB)
				वापस -EINVAL;
			अवरोध;
		हाल TC_MQPRIO_MODE_CHANNEL:
			mqprio.flags = priv->flags;
			अगर (priv->flags & TC_MQPRIO_F_MODE)
				mqprio.mode = priv->mode;
			अगर (priv->flags & TC_MQPRIO_F_SHAPER)
				mqprio.shaper = priv->shaper;
			अगर (priv->flags & TC_MQPRIO_F_MIN_RATE)
				क्रम (i = 0; i < mqprio.qopt.num_tc; i++)
					mqprio.min_rate[i] = priv->min_rate[i];
			अगर (priv->flags & TC_MQPRIO_F_MAX_RATE)
				क्रम (i = 0; i < mqprio.qopt.num_tc; i++)
					mqprio.max_rate[i] = priv->max_rate[i];
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		err = dev->netdev_ops->nकरो_setup_tc(dev,
						    TC_SETUP_QDISC_MQPRIO,
						    &mqprio);
		अगर (err)
			वापस err;

		priv->hw_offload = mqprio.qopt.hw;
	पूर्ण अन्यथा अणु
		netdev_set_num_tc(dev, qopt->num_tc);
		क्रम (i = 0; i < qopt->num_tc; i++)
			netdev_set_tc_queue(dev, i,
					    qopt->count[i], qopt->offset[i]);
	पूर्ण

	/* Always use supplied priority mappings */
	क्रम (i = 0; i < TC_BITMASK + 1; i++)
		netdev_set_prio_tc_map(dev, i, qopt->prio_tc_map[i]);

	sch->flags |= TCQ_F_MQROOT;
	वापस 0;
पूर्ण

अटल व्योम mqprio_attach(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mqprio_sched *priv = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc, *old;
	अचिन्हित पूर्णांक ntx;

	/* Attach underlying qdisc */
	क्रम (ntx = 0; ntx < dev->num_tx_queues; ntx++) अणु
		qdisc = priv->qdiscs[ntx];
		old = dev_graft_qdisc(qdisc->dev_queue, qdisc);
		अगर (old)
			qdisc_put(old);
		अगर (ntx < dev->real_num_tx_queues)
			qdisc_hash_add(qdisc, false);
	पूर्ण
	kमुक्त(priv->qdiscs);
	priv->qdiscs = शून्य;
पूर्ण

अटल काष्ठा netdev_queue *mqprio_queue_get(काष्ठा Qdisc *sch,
					     अचिन्हित दीर्घ cl)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित दीर्घ ntx = cl - 1;

	अगर (ntx >= dev->num_tx_queues)
		वापस शून्य;
	वापस netdev_get_tx_queue(dev, ntx);
पूर्ण

अटल पूर्णांक mqprio_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl, काष्ठा Qdisc *new,
			काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा netdev_queue *dev_queue = mqprio_queue_get(sch, cl);

	अगर (!dev_queue)
		वापस -EINVAL;

	अगर (dev->flags & IFF_UP)
		dev_deactivate(dev);

	*old = dev_graft_qdisc(dev_queue, new);

	अगर (new)
		new->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;

	अगर (dev->flags & IFF_UP)
		dev_activate(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_rates(काष्ठा mqprio_sched *priv,
		      काष्ठा tc_mqprio_qopt *opt, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक i;

	अगर (priv->flags & TC_MQPRIO_F_MIN_RATE) अणु
		nest = nla_nest_start_noflag(skb, TCA_MQPRIO_MIN_RATE64);
		अगर (!nest)
			जाओ nla_put_failure;

		क्रम (i = 0; i < opt->num_tc; i++) अणु
			अगर (nla_put(skb, TCA_MQPRIO_MIN_RATE64,
				    माप(priv->min_rate[i]),
				    &priv->min_rate[i]))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण

	अगर (priv->flags & TC_MQPRIO_F_MAX_RATE) अणु
		nest = nla_nest_start_noflag(skb, TCA_MQPRIO_MAX_RATE64);
		अगर (!nest)
			जाओ nla_put_failure;

		क्रम (i = 0; i < opt->num_tc; i++) अणु
			अगर (nla_put(skb, TCA_MQPRIO_MAX_RATE64,
				    माप(priv->max_rate[i]),
				    &priv->max_rate[i]))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक mqprio_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा mqprio_sched *priv = qdisc_priv(sch);
	काष्ठा nlattr *nla = (काष्ठा nlattr *)skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_mqprio_qopt opt = अणु 0 पूर्ण;
	काष्ठा Qdisc *qdisc;
	अचिन्हित पूर्णांक ntx, tc;

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
			__u32 qlen = qdisc_qlen_sum(qdisc);

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
			sch->qstats.backlog	+= qdisc->qstats.backlog;
			sch->qstats.drops	+= qdisc->qstats.drops;
			sch->qstats.requeues	+= qdisc->qstats.requeues;
			sch->qstats.overlimits	+= qdisc->qstats.overlimits;
		पूर्ण

		spin_unlock_bh(qdisc_lock(qdisc));
	पूर्ण

	opt.num_tc = netdev_get_num_tc(dev);
	स_नकल(opt.prio_tc_map, dev->prio_tc_map, माप(opt.prio_tc_map));
	opt.hw = priv->hw_offload;

	क्रम (tc = 0; tc < netdev_get_num_tc(dev); tc++) अणु
		opt.count[tc] = dev->tc_to_txq[tc].count;
		opt.offset[tc] = dev->tc_to_txq[tc].offset;
	पूर्ण

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर ((priv->flags & TC_MQPRIO_F_MODE) &&
	    nla_put_u16(skb, TCA_MQPRIO_MODE, priv->mode))
		जाओ nla_put_failure;

	अगर ((priv->flags & TC_MQPRIO_F_SHAPER) &&
	    nla_put_u16(skb, TCA_MQPRIO_SHAPER, priv->shaper))
		जाओ nla_put_failure;

	अगर ((priv->flags & TC_MQPRIO_F_MIN_RATE ||
	     priv->flags & TC_MQPRIO_F_MAX_RATE) &&
	    (dump_rates(priv, &opt, skb) != 0))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nla);
nla_put_failure:
	nlmsg_trim(skb, nla);
	वापस -1;
पूर्ण

अटल काष्ठा Qdisc *mqprio_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा netdev_queue *dev_queue = mqprio_queue_get(sch, cl);

	अगर (!dev_queue)
		वापस शून्य;

	वापस dev_queue->qdisc_sleeping;
पूर्ण

अटल अचिन्हित दीर्घ mqprio_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित पूर्णांक ntx = TC_H_MIN(classid);

	/* There are essentially two regions here that have valid classid
	 * values. The first region will have a classid value of 1 through
	 * num_tx_queues. All of these are backed by actual Qdiscs.
	 */
	अगर (ntx < TC_H_MIN_PRIORITY)
		वापस (ntx <= dev->num_tx_queues) ? ntx : 0;

	/* The second region represents the hardware traffic classes. These
	 * are represented by classid values of TC_H_MIN_PRIORITY through
	 * TC_H_MIN_PRIORITY + netdev_get_num_tc - 1
	 */
	वापस ((ntx - TC_H_MIN_PRIORITY) < netdev_get_num_tc(dev)) ? ntx : 0;
पूर्ण

अटल पूर्णांक mqprio_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			 काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	अगर (cl < TC_H_MIN_PRIORITY) अणु
		काष्ठा netdev_queue *dev_queue = mqprio_queue_get(sch, cl);
		काष्ठा net_device *dev = qdisc_dev(sch);
		पूर्णांक tc = netdev_txq_to_tc(dev, cl - 1);

		tcm->tcm_parent = (tc < 0) ? 0 :
			TC_H_MAKE(TC_H_MAJ(sch->handle),
				  TC_H_MIN(tc + TC_H_MIN_PRIORITY));
		tcm->tcm_info = dev_queue->qdisc_sleeping->handle;
	पूर्ण अन्यथा अणु
		tcm->tcm_parent = TC_H_ROOT;
		tcm->tcm_info = 0;
	पूर्ण
	tcm->tcm_handle |= TC_H_MIN(cl);
	वापस 0;
पूर्ण

अटल पूर्णांक mqprio_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				   काष्ठा gnet_dump *d)
	__releases(d->lock)
	__acquires(d->lock)
अणु
	अगर (cl >= TC_H_MIN_PRIORITY) अणु
		पूर्णांक i;
		__u32 qlen = 0;
		काष्ठा gnet_stats_queue qstats = अणु0पूर्ण;
		काष्ठा gnet_stats_basic_packed bstats = अणु0पूर्ण;
		काष्ठा net_device *dev = qdisc_dev(sch);
		काष्ठा netdev_tc_txq tc = dev->tc_to_txq[cl & TC_BITMASK];

		/* Drop lock here it will be reclaimed beक्रमe touching
		 * statistics this is required because the d->lock we
		 * hold here is the look on dev_queue->qdisc_sleeping
		 * also acquired below.
		 */
		अगर (d->lock)
			spin_unlock_bh(d->lock);

		क्रम (i = tc.offset; i < tc.offset + tc.count; i++) अणु
			काष्ठा netdev_queue *q = netdev_get_tx_queue(dev, i);
			काष्ठा Qdisc *qdisc = rtnl_dereference(q->qdisc);
			काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats = शून्य;
			काष्ठा gnet_stats_queue __percpu *cpu_qstats = शून्य;

			spin_lock_bh(qdisc_lock(qdisc));
			अगर (qdisc_is_percpu_stats(qdisc)) अणु
				cpu_bstats = qdisc->cpu_bstats;
				cpu_qstats = qdisc->cpu_qstats;
			पूर्ण

			qlen = qdisc_qlen_sum(qdisc);
			__gnet_stats_copy_basic(शून्य, &sch->bstats,
						cpu_bstats, &qdisc->bstats);
			__gnet_stats_copy_queue(&sch->qstats,
						cpu_qstats,
						&qdisc->qstats,
						qlen);
			spin_unlock_bh(qdisc_lock(qdisc));
		पूर्ण

		/* Reclaim root sleeping lock beक्रमe completing stats */
		अगर (d->lock)
			spin_lock_bh(d->lock);
		अगर (gnet_stats_copy_basic(शून्य, d, शून्य, &bstats) < 0 ||
		    gnet_stats_copy_queue(d, शून्य, &qstats, qlen) < 0)
			वापस -1;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_queue *dev_queue = mqprio_queue_get(sch, cl);

		sch = dev_queue->qdisc_sleeping;
		अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch), d,
					  sch->cpu_bstats, &sch->bstats) < 0 ||
		    qdisc_qstats_copy(d, sch) < 0)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mqprio_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित दीर्घ ntx;

	अगर (arg->stop)
		वापस;

	/* Walk hierarchy with a भव class per tc */
	arg->count = arg->skip;
	क्रम (ntx = arg->skip; ntx < netdev_get_num_tc(dev); ntx++) अणु
		अगर (arg->fn(sch, ntx + TC_H_MIN_PRIORITY, arg) < 0) अणु
			arg->stop = 1;
			वापस;
		पूर्ण
		arg->count++;
	पूर्ण

	/* Pad the values and skip over unused traffic classes */
	अगर (ntx < TC_MAX_QUEUE) अणु
		arg->count = TC_MAX_QUEUE;
		ntx = TC_MAX_QUEUE;
	पूर्ण

	/* Reset offset, sort out reमुख्यing per-queue qdiscs */
	क्रम (ntx -= TC_MAX_QUEUE; ntx < dev->num_tx_queues; ntx++) अणु
		अगर (arg->fn(sch, ntx + 1, arg) < 0) अणु
			arg->stop = 1;
			वापस;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा netdev_queue *mqprio_select_queue(काष्ठा Qdisc *sch,
						काष्ठा tcmsg *tcm)
अणु
	वापस mqprio_queue_get(sch, TC_H_MIN(tcm->tcm_parent));
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops mqprio_class_ops = अणु
	.graft		= mqprio_graft,
	.leaf		= mqprio_leaf,
	.find		= mqprio_find,
	.walk		= mqprio_walk,
	.dump		= mqprio_dump_class,
	.dump_stats	= mqprio_dump_class_stats,
	.select_queue	= mqprio_select_queue,
पूर्ण;

अटल काष्ठा Qdisc_ops mqprio_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &mqprio_class_ops,
	.id		= "mqprio",
	.priv_size	= माप(काष्ठा mqprio_sched),
	.init		= mqprio_init,
	.destroy	= mqprio_destroy,
	.attach		= mqprio_attach,
	.dump		= mqprio_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mqprio_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&mqprio_qdisc_ops);
पूर्ण

अटल व्योम __निकास mqprio_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&mqprio_qdisc_ops);
पूर्ण

module_init(mqprio_module_init);
module_निकास(mqprio_module_निकास);

MODULE_LICENSE("GPL");
