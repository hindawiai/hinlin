<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_cbs.c	Credit Based Shaper
 *
 * Authors:	Vinicius Costa Gomes <vinicius.gomes@पूर्णांकel.com>
 */

/* Credit Based Shaper (CBS)
 * =========================
 *
 * This is a simple rate-limiting shaper aimed at TSN applications on
 * प्रणालीs with known traffic workloads.
 *
 * Its algorithm is defined by the IEEE 802.1Q-2014 Specअगरication,
 * Section 8.6.8.2, and explained in more detail in the Annex L of the
 * same specअगरication.
 *
 * There are four tunables to be considered:
 *
 *	'idleslope': Idleslope is the rate of credits that is
 *	accumulated (in kilobits per second) when there is at least
 *	one packet रुकोing क्रम transmission. Packets are transmitted
 *	when the current value of credits is equal or greater than
 *	zero. When there is no packet to be transmitted the amount of
 *	credits is set to zero. This is the मुख्य tunable of the CBS
 *	algorithm.
 *
 *	'sendslope':
 *	Sendslope is the rate of credits that is depleted (it should be a
 *	negative number of kilobits per second) when a transmission is
 *	ocurring. It can be calculated as follows, (IEEE 802.1Q-2014 Section
 *	8.6.8.2 item g):
 *
 *	sendslope = idleslope - port_transmit_rate
 *
 *	'hicredit': Hicredit defines the maximum amount of credits (in
 *	bytes) that can be accumulated. Hicredit depends on the
 *	अक्षरacteristics of पूर्णांकerfering traffic,
 *	'max_interference_size' is the maximum size of any burst of
 *	traffic that can delay the transmission of a frame that is
 *	available क्रम transmission क्रम this traffic class, (IEEE
 *	802.1Q-2014 Annex L, Equation L-3):
 *
 *	hicredit = max_पूर्णांकerference_size * (idleslope / port_transmit_rate)
 *
 *	'locredit': Locredit is the minimum amount of credits that can
 *	be reached. It is a function of the traffic flowing through
 *	this qdisc (IEEE 802.1Q-2014 Annex L, Equation L-2):
 *
 *	locredit = max_frame_size * (sendslope / port_transmit_rate)
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netevent.h>
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>

अटल LIST_HEAD(cbs_list);
अटल DEFINE_SPINLOCK(cbs_list_lock);

#घोषणा BYTES_PER_KBIT (1000LL / 8)

काष्ठा cbs_sched_data अणु
	bool offload;
	पूर्णांक queue;
	atomic64_t port_rate; /* in bytes/s */
	s64 last; /* बारtamp in ns */
	s64 credits; /* in bytes */
	s32 locredit; /* in bytes */
	s32 hicredit; /* in bytes */
	s64 sendslope; /* in bytes/s */
	s64 idleslope; /* in bytes/s */
	काष्ठा qdisc_watchकरोg watchकरोg;
	पूर्णांक (*enqueue)(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त);
	काष्ठा sk_buff *(*dequeue)(काष्ठा Qdisc *sch);
	काष्ठा Qdisc *qdisc;
	काष्ठा list_head cbs_list;
पूर्ण;

अटल पूर्णांक cbs_child_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			     काष्ठा Qdisc *child,
			     काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	पूर्णांक err;

	err = child->ops->enqueue(skb, child, to_मुक्त);
	अगर (err != NET_XMIT_SUCCESS)
		वापस err;

	sch->qstats.backlog += len;
	sch->q.qlen++;

	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल पूर्णांक cbs_enqueue_offload(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc = q->qdisc;

	वापस cbs_child_enqueue(skb, sch, qdisc, to_मुक्त);
पूर्ण

अटल पूर्णांक cbs_enqueue_soft(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			    काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc = q->qdisc;

	अगर (sch->q.qlen == 0 && q->credits > 0) अणु
		/* We need to stop accumulating credits when there's
		 * no enqueued packets and q->credits is positive.
		 */
		q->credits = 0;
		q->last = kसमय_get_ns();
	पूर्ण

	वापस cbs_child_enqueue(skb, sch, qdisc, to_मुक्त);
पूर्ण

अटल पूर्णांक cbs_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);

	वापस q->enqueue(skb, sch, to_मुक्त);
पूर्ण

/* समयdअगरf is in ns, slope is in bytes/s */
अटल s64 समयdअगरf_to_credits(s64 समयdअगरf, s64 slope)
अणु
	वापस भाग64_s64(समयdअगरf * slope, NSEC_PER_SEC);
पूर्ण

अटल s64 delay_from_credits(s64 credits, s64 slope)
अणु
	अगर (unlikely(slope == 0))
		वापस S64_MAX;

	वापस भाग64_s64(-credits * NSEC_PER_SEC, slope);
पूर्ण

अटल s64 credits_from_len(अचिन्हित पूर्णांक len, s64 slope, s64 port_rate)
अणु
	अगर (unlikely(port_rate == 0))
		वापस S64_MAX;

	वापस भाग64_s64(len * slope, port_rate);
पूर्ण

अटल काष्ठा sk_buff *cbs_child_dequeue(काष्ठा Qdisc *sch, काष्ठा Qdisc *child)
अणु
	काष्ठा sk_buff *skb;

	skb = child->ops->dequeue(child);
	अगर (!skb)
		वापस शून्य;

	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);
	sch->q.qlen--;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *cbs_dequeue_soft(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc = q->qdisc;
	s64 now = kसमय_get_ns();
	काष्ठा sk_buff *skb;
	s64 credits;
	पूर्णांक len;

	/* The previous packet is still being sent */
	अगर (now < q->last) अणु
		qdisc_watchकरोg_schedule_ns(&q->watchकरोg, q->last);
		वापस शून्य;
	पूर्ण
	अगर (q->credits < 0) अणु
		credits = समयdअगरf_to_credits(now - q->last, q->idleslope);

		credits = q->credits + credits;
		q->credits = min_t(s64, credits, q->hicredit);

		अगर (q->credits < 0) अणु
			s64 delay;

			delay = delay_from_credits(q->credits, q->idleslope);
			qdisc_watchकरोg_schedule_ns(&q->watchकरोg, now + delay);

			q->last = now;

			वापस शून्य;
		पूर्ण
	पूर्ण
	skb = cbs_child_dequeue(sch, qdisc);
	अगर (!skb)
		वापस शून्य;

	len = qdisc_pkt_len(skb);

	/* As sendslope is a negative number, this will decrease the
	 * amount of q->credits.
	 */
	credits = credits_from_len(len, q->sendslope,
				   atomic64_पढ़ो(&q->port_rate));
	credits += q->credits;

	q->credits = max_t(s64, credits, q->locredit);
	/* Estimate of the transmission of the last byte of the packet in ns */
	अगर (unlikely(atomic64_पढ़ो(&q->port_rate) == 0))
		q->last = now;
	अन्यथा
		q->last = now + भाग64_s64(len * NSEC_PER_SEC,
					  atomic64_पढ़ो(&q->port_rate));

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *cbs_dequeue_offload(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc = q->qdisc;

	वापस cbs_child_dequeue(sch, qdisc);
पूर्ण

अटल काष्ठा sk_buff *cbs_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);

	वापस q->dequeue(sch);
पूर्ण

अटल स्थिर काष्ठा nla_policy cbs_policy[TCA_CBS_MAX + 1] = अणु
	[TCA_CBS_PARMS]	= अणु .len = माप(काष्ठा tc_cbs_qopt) पूर्ण,
पूर्ण;

अटल व्योम cbs_disable_offload(काष्ठा net_device *dev,
				काष्ठा cbs_sched_data *q)
अणु
	काष्ठा tc_cbs_qopt_offload cbs = अणु पूर्ण;
	स्थिर काष्ठा net_device_ops *ops;
	पूर्णांक err;

	अगर (!q->offload)
		वापस;

	q->enqueue = cbs_enqueue_soft;
	q->dequeue = cbs_dequeue_soft;

	ops = dev->netdev_ops;
	अगर (!ops->nकरो_setup_tc)
		वापस;

	cbs.queue = q->queue;
	cbs.enable = 0;

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_CBS, &cbs);
	अगर (err < 0)
		pr_warn("Couldn't disable CBS offload for queue %d\n",
			cbs.queue);
पूर्ण

अटल पूर्णांक cbs_enable_offload(काष्ठा net_device *dev, काष्ठा cbs_sched_data *q,
			      स्थिर काष्ठा tc_cbs_qopt *opt,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा tc_cbs_qopt_offload cbs = अणु पूर्ण;
	पूर्णांक err;

	अगर (!ops->nकरो_setup_tc) अणु
		NL_SET_ERR_MSG(extack, "Specified device does not support cbs offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	cbs.queue = q->queue;

	cbs.enable = 1;
	cbs.hicredit = opt->hicredit;
	cbs.locredit = opt->locredit;
	cbs.idleslope = opt->idleslope;
	cbs.sendslope = opt->sendslope;

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_CBS, &cbs);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Specified device failed to setup cbs hardware offload");
		वापस err;
	पूर्ण

	q->enqueue = cbs_enqueue_offload;
	q->dequeue = cbs_dequeue_offload;

	वापस 0;
पूर्ण

अटल व्योम cbs_set_port_rate(काष्ठा net_device *dev, काष्ठा cbs_sched_data *q)
अणु
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक speed = SPEED_10;
	पूर्णांक port_rate;
	पूर्णांक err;

	err = __ethtool_get_link_ksettings(dev, &ecmd);
	अगर (err < 0)
		जाओ skip;

	अगर (ecmd.base.speed && ecmd.base.speed != SPEED_UNKNOWN)
		speed = ecmd.base.speed;

skip:
	port_rate = speed * 1000 * BYTES_PER_KBIT;

	atomic64_set(&q->port_rate, port_rate);
	netdev_dbg(dev, "cbs: set %s's port_rate to: %lld, linkspeed: %d\n",
		   dev->name, (दीर्घ दीर्घ)atomic64_पढ़ो(&q->port_rate),
		   ecmd.base.speed);
पूर्ण

अटल पूर्णांक cbs_dev_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा cbs_sched_data *q;
	काष्ठा net_device *qdev;
	bool found = false;

	ASSERT_RTNL();

	अगर (event != NETDEV_UP && event != NETDEV_CHANGE)
		वापस NOTIFY_DONE;

	spin_lock(&cbs_list_lock);
	list_क्रम_each_entry(q, &cbs_list, cbs_list) अणु
		qdev = qdisc_dev(q->qdisc);
		अगर (qdev == dev) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cbs_list_lock);

	अगर (found)
		cbs_set_port_rate(dev, q);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक cbs_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा nlattr *tb[TCA_CBS_MAX + 1];
	काष्ठा tc_cbs_qopt *qopt;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, TCA_CBS_MAX, opt, cbs_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_CBS_PARMS]) अणु
		NL_SET_ERR_MSG(extack, "Missing CBS parameter which are mandatory");
		वापस -EINVAL;
	पूर्ण

	qopt = nla_data(tb[TCA_CBS_PARMS]);

	अगर (!qopt->offload) अणु
		cbs_set_port_rate(dev, q);
		cbs_disable_offload(dev, q);
	पूर्ण अन्यथा अणु
		err = cbs_enable_offload(dev, q, qopt, extack);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Everything went OK, save the parameters used. */
	q->hicredit = qopt->hicredit;
	q->locredit = qopt->locredit;
	q->idleslope = qopt->idleslope * BYTES_PER_KBIT;
	q->sendslope = qopt->sendslope * BYTES_PER_KBIT;
	q->offload = qopt->offload;

	वापस 0;
पूर्ण

अटल पूर्णांक cbs_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack, "Missing CBS qdisc options  which are mandatory");
		वापस -EINVAL;
	पूर्ण

	q->qdisc = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
				     sch->handle, extack);
	अगर (!q->qdisc)
		वापस -ENOMEM;

	spin_lock(&cbs_list_lock);
	list_add(&q->cbs_list, &cbs_list);
	spin_unlock(&cbs_list_lock);

	qdisc_hash_add(q->qdisc, false);

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	q->enqueue = cbs_enqueue_soft;
	q->dequeue = cbs_dequeue_soft;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);

	वापस cbs_change(sch, opt, extack);
पूर्ण

अटल व्योम cbs_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);

	/* Nothing to करो अगर we couldn't create the underlying qdisc */
	अगर (!q->qdisc)
		वापस;

	qdisc_watchकरोg_cancel(&q->watchकरोg);
	cbs_disable_offload(dev, q);

	spin_lock(&cbs_list_lock);
	list_del(&q->cbs_list);
	spin_unlock(&cbs_list_lock);

	qdisc_put(q->qdisc);
पूर्ण

अटल पूर्णांक cbs_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_cbs_qopt opt = अणु पूर्ण;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	opt.hicredit = q->hicredit;
	opt.locredit = q->locredit;
	opt.sendslope = भाग64_s64(q->sendslope, BYTES_PER_KBIT);
	opt.idleslope = भाग64_s64(q->idleslope, BYTES_PER_KBIT);
	opt.offload = q->offload;

	अगर (nla_put(skb, TCA_CBS_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक cbs_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);

	अगर (cl != 1 || !q->qdisc)	/* only one class */
		वापस -ENOENT;

	tcm->tcm_handle |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handle;

	वापस 0;
पूर्ण

अटल पूर्णांक cbs_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);

	अगर (!new) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					sch->handle, शून्य);
		अगर (!new)
			new = &noop_qdisc;
	पूर्ण

	*old = qdisc_replace(sch, new, &q->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *cbs_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cbs_sched_data *q = qdisc_priv(sch);

	वापस q->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ cbs_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 1;
पूर्ण

अटल व्योम cbs_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	अगर (!walker->stop) अणु
		अगर (walker->count >= walker->skip) अणु
			अगर (walker->fn(sch, 1, walker) < 0) अणु
				walker->stop = 1;
				वापस;
			पूर्ण
		पूर्ण
		walker->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops cbs_class_ops = अणु
	.graft		=	cbs_graft,
	.leaf		=	cbs_leaf,
	.find		=	cbs_find,
	.walk		=	cbs_walk,
	.dump		=	cbs_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops cbs_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"cbs",
	.cl_ops		=	&cbs_class_ops,
	.priv_size	=	माप(काष्ठा cbs_sched_data),
	.enqueue	=	cbs_enqueue,
	.dequeue	=	cbs_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	cbs_init,
	.reset		=	qdisc_reset_queue,
	.destroy	=	cbs_destroy,
	.change		=	cbs_change,
	.dump		=	cbs_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल काष्ठा notअगरier_block cbs_device_notअगरier = अणु
	.notअगरier_call = cbs_dev_notअगरier,
पूर्ण;

अटल पूर्णांक __init cbs_module_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_netdevice_notअगरier(&cbs_device_notअगरier);
	अगर (err)
		वापस err;

	err = रेजिस्टर_qdisc(&cbs_qdisc_ops);
	अगर (err)
		unरेजिस्टर_netdevice_notअगरier(&cbs_device_notअगरier);

	वापस err;
पूर्ण

अटल व्योम __निकास cbs_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&cbs_qdisc_ops);
	unरेजिस्टर_netdevice_notअगरier(&cbs_device_notअगरier);
पूर्ण
module_init(cbs_module_init)
module_निकास(cbs_module_निकास)
MODULE_LICENSE("GPL");
