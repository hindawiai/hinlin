<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* net/sched/sch_etf.c  Earliest TxTime First queueing discipline.
 *
 * Authors:	Jesus Sanchez-Palencia <jesus.sanchez-palencia@पूर्णांकel.com>
 *		Vinicius Costa Gomes <vinicius.gomes@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sock.h>

#घोषणा DEADLINE_MODE_IS_ON(x) ((x)->flags & TC_ETF_DEADLINE_MODE_ON)
#घोषणा OFFLOAD_IS_ON(x) ((x)->flags & TC_ETF_OFFLOAD_ON)
#घोषणा SKIP_SOCK_CHECK_IS_SET(x) ((x)->flags & TC_ETF_SKIP_SOCK_CHECK)

काष्ठा etf_sched_data अणु
	bool offload;
	bool deadline_mode;
	bool skip_sock_check;
	पूर्णांक घड़ीid;
	पूर्णांक queue;
	s32 delta; /* in ns */
	kसमय_प्रकार last; /* The txसमय of the last skb sent to the netdevice. */
	काष्ठा rb_root_cached head;
	काष्ठा qdisc_watchकरोg watchकरोg;
	kसमय_प्रकार (*get_समय)(व्योम);
पूर्ण;

अटल स्थिर काष्ठा nla_policy etf_policy[TCA_ETF_MAX + 1] = अणु
	[TCA_ETF_PARMS]	= अणु .len = माप(काष्ठा tc_etf_qopt) पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक validate_input_params(काष्ठा tc_etf_qopt *qopt,
					काष्ठा netlink_ext_ack *extack)
अणु
	/* Check अगर params comply to the following rules:
	 *	* Clockid and delta must be valid.
	 *
	 *	* Dynamic घड़ीids are not supported.
	 *
	 *	* Delta must be a positive पूर्णांकeger.
	 *
	 * Also note that क्रम the HW offload हाल, we must
	 * expect that प्रणाली घड़ीs have been synchronized to PHC.
	 */
	अगर (qopt->घड़ीid < 0) अणु
		NL_SET_ERR_MSG(extack, "Dynamic clockids are not supported");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (qopt->घड़ीid != CLOCK_TAI) अणु
		NL_SET_ERR_MSG(extack, "Invalid clockid. CLOCK_TAI must be used");
		वापस -EINVAL;
	पूर्ण

	अगर (qopt->delta < 0) अणु
		NL_SET_ERR_MSG(extack, "Delta must be positive");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_packet_valid(काष्ठा Qdisc *sch, काष्ठा sk_buff *nskb)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	kसमय_प्रकार txसमय = nskb->tstamp;
	काष्ठा sock *sk = nskb->sk;
	kसमय_प्रकार now;

	अगर (q->skip_sock_check)
		जाओ skip;

	अगर (!sk || !sk_fullsock(sk))
		वापस false;

	अगर (!sock_flag(sk, SOCK_TXTIME))
		वापस false;

	/* We करोn't perक्रमm crossबारtamping.
	 * Drop अगर packet's clockid differs from qdisc's.
	 */
	अगर (sk->sk_घड़ीid != q->घड़ीid)
		वापस false;

	अगर (sk->sk_txसमय_deadline_mode != q->deadline_mode)
		वापस false;

skip:
	now = q->get_समय();
	अगर (kसमय_beक्रमe(txसमय, now) || kसमय_beक्रमe(txसमय, q->last))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *etf_peek_बारortedlist(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_node *p;

	p = rb_first_cached(&q->head);
	अगर (!p)
		वापस शून्य;

	वापस rb_to_skb(p);
पूर्ण

अटल व्योम reset_watchकरोg(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb = etf_peek_बारortedlist(sch);
	kसमय_प्रकार next;

	अगर (!skb) अणु
		qdisc_watchकरोg_cancel(&q->watchकरोg);
		वापस;
	पूर्ण

	next = kसमय_sub_ns(skb->tstamp, q->delta);
	qdisc_watchकरोg_schedule_ns(&q->watchकरोg, kसमय_प्रकारo_ns(next));
पूर्ण

अटल व्योम report_sock_error(काष्ठा sk_buff *skb, u32 err, u8 code)
अणु
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sk_buff *clone;
	kसमय_प्रकार txसमय = skb->tstamp;
	काष्ठा sock *sk = skb->sk;

	अगर (!sk || !sk_fullsock(sk) || !(sk->sk_txसमय_report_errors))
		वापस;

	clone = skb_clone(skb, GFP_ATOMIC);
	अगर (!clone)
		वापस;

	serr = SKB_EXT_ERR(clone);
	serr->ee.ee_त्रुटि_सं = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXTIME;
	serr->ee.ee_type = 0;
	serr->ee.ee_code = code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_data = (txसमय >> 32); /* high part of tstamp */
	serr->ee.ee_info = txसमय; /* low part of tstamp */

	अगर (sock_queue_err_skb(sk, clone))
		kमुक्त_skb(clone);
पूर्ण

अटल पूर्णांक etf_enqueue_बारortedlist(काष्ठा sk_buff *nskb, काष्ठा Qdisc *sch,
				      काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_node **p = &q->head.rb_root.rb_node, *parent = शून्य;
	kसमय_प्रकार txसमय = nskb->tstamp;
	bool lefपंचांगost = true;

	अगर (!is_packet_valid(sch, nskb)) अणु
		report_sock_error(nskb, EINVAL,
				  SO_EE_CODE_TXTIME_INVALID_PARAM);
		वापस qdisc_drop(nskb, sch, to_मुक्त);
	पूर्ण

	जबतक (*p) अणु
		काष्ठा sk_buff *skb;

		parent = *p;
		skb = rb_to_skb(parent);
		अगर (kसमय_compare(txसमय, skb->tstamp) >= 0) अणु
			p = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			p = &parent->rb_left;
		पूर्ण
	पूर्ण
	rb_link_node(&nskb->rbnode, parent, p);
	rb_insert_color_cached(&nskb->rbnode, &q->head, lefपंचांगost);

	qdisc_qstats_backlog_inc(sch, nskb);
	sch->q.qlen++;

	/* Now we may need to re-arm the qdisc watchकरोg क्रम the next packet. */
	reset_watchकरोg(sch);

	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल व्योम बारortedlist_drop(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb,
				kसमय_प्रकार now)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *to_मुक्त = शून्य;
	काष्ठा sk_buff *पंचांगp = शून्य;

	skb_rbtree_walk_from_safe(skb, पंचांगp) अणु
		अगर (kसमय_after(skb->tstamp, now))
			अवरोध;

		rb_erase_cached(&skb->rbnode, &q->head);

		/* The rbnode field in the skb re-uses these fields, now that
		 * we are करोne with the rbnode, reset them.
		 */
		skb->next = शून्य;
		skb->prev = शून्य;
		skb->dev = qdisc_dev(sch);

		report_sock_error(skb, ECANCELED, SO_EE_CODE_TXTIME_MISSED);

		qdisc_qstats_backlog_dec(sch, skb);
		qdisc_drop(skb, sch, &to_मुक्त);
		qdisc_qstats_overlimit(sch);
		sch->q.qlen--;
	पूर्ण

	kमुक्त_skb_list(to_मुक्त);
पूर्ण

अटल व्योम बारortedlist_हटाओ(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);

	rb_erase_cached(&skb->rbnode, &q->head);

	/* The rbnode field in the skb re-uses these fields, now that
	 * we are करोne with the rbnode, reset them.
	 */
	skb->next = शून्य;
	skb->prev = शून्य;
	skb->dev = qdisc_dev(sch);

	qdisc_qstats_backlog_dec(sch, skb);

	qdisc_bstats_update(sch, skb);

	q->last = skb->tstamp;

	sch->q.qlen--;
पूर्ण

अटल काष्ठा sk_buff *etf_dequeue_बारortedlist(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	kसमय_प्रकार now, next;

	skb = etf_peek_बारortedlist(sch);
	अगर (!skb)
		वापस शून्य;

	now = q->get_समय();

	/* Drop अगर packet has expired जबतक in queue. */
	अगर (kसमय_beक्रमe(skb->tstamp, now)) अणु
		बारortedlist_drop(sch, skb, now);
		skb = शून्य;
		जाओ out;
	पूर्ण

	/* When in deadline mode, dequeue as soon as possible and change the
	 * txसमय from deadline to (now + delta).
	 */
	अगर (q->deadline_mode) अणु
		बारortedlist_हटाओ(sch, skb);
		skb->tstamp = now;
		जाओ out;
	पूर्ण

	next = kसमय_sub_ns(skb->tstamp, q->delta);

	/* Dequeue only अगर now is within the [txसमय - delta, txसमय] range. */
	अगर (kसमय_after(now, next))
		बारortedlist_हटाओ(sch, skb);
	अन्यथा
		skb = शून्य;

out:
	/* Now we may need to re-arm the qdisc watchकरोg क्रम the next packet. */
	reset_watchकरोg(sch);

	वापस skb;
पूर्ण

अटल व्योम etf_disable_offload(काष्ठा net_device *dev,
				काष्ठा etf_sched_data *q)
अणु
	काष्ठा tc_etf_qopt_offload etf = अणु पूर्ण;
	स्थिर काष्ठा net_device_ops *ops;
	पूर्णांक err;

	अगर (!q->offload)
		वापस;

	ops = dev->netdev_ops;
	अगर (!ops->nकरो_setup_tc)
		वापस;

	etf.queue = q->queue;
	etf.enable = 0;

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_ETF, &etf);
	अगर (err < 0)
		pr_warn("Couldn't disable ETF offload for queue %d\n",
			etf.queue);
पूर्ण

अटल पूर्णांक etf_enable_offload(काष्ठा net_device *dev, काष्ठा etf_sched_data *q,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा tc_etf_qopt_offload etf = अणु पूर्ण;
	पूर्णांक err;

	अगर (q->offload)
		वापस 0;

	अगर (!ops->nकरो_setup_tc) अणु
		NL_SET_ERR_MSG(extack, "Specified device does not support ETF offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	etf.queue = q->queue;
	etf.enable = 1;

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_ETF, &etf);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Specified device failed to setup ETF hardware offload");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक etf_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा nlattr *tb[TCA_ETF_MAX + 1];
	काष्ठा tc_etf_qopt *qopt;
	पूर्णांक err;

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack,
			       "Missing ETF qdisc options which are mandatory");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_ETF_MAX, opt, etf_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_ETF_PARMS]) अणु
		NL_SET_ERR_MSG(extack, "Missing mandatory ETF parameters");
		वापस -EINVAL;
	पूर्ण

	qopt = nla_data(tb[TCA_ETF_PARMS]);

	pr_debug("delta %d clockid %d offload %s deadline %s\n",
		 qopt->delta, qopt->घड़ीid,
		 OFFLOAD_IS_ON(qopt) ? "on" : "off",
		 DEADLINE_MODE_IS_ON(qopt) ? "on" : "off");

	err = validate_input_params(qopt, extack);
	अगर (err < 0)
		वापस err;

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	अगर (OFFLOAD_IS_ON(qopt)) अणु
		err = etf_enable_offload(dev, q, extack);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Everything went OK, save the parameters used. */
	q->delta = qopt->delta;
	q->घड़ीid = qopt->घड़ीid;
	q->offload = OFFLOAD_IS_ON(qopt);
	q->deadline_mode = DEADLINE_MODE_IS_ON(qopt);
	q->skip_sock_check = SKIP_SOCK_CHECK_IS_SET(qopt);

	चयन (q->घड़ीid) अणु
	हाल CLOCK_REALTIME:
		q->get_समय = kसमय_get_real;
		अवरोध;
	हाल CLOCK_MONOTONIC:
		q->get_समय = kसमय_get;
		अवरोध;
	हाल CLOCK_BOOTTIME:
		q->get_समय = kसमय_get_bootसमय;
		अवरोध;
	हाल CLOCK_TAI:
		q->get_समय = kसमय_get_घड़ीtai;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG(extack, "Clockid is not supported");
		वापस -ENOTSUPP;
	पूर्ण

	qdisc_watchकरोg_init_घड़ीid(&q->watchकरोg, sch, q->घड़ीid);

	वापस 0;
पूर्ण

अटल व्योम बारortedlist_clear(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_node *p = rb_first_cached(&q->head);

	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);

		rb_erase_cached(&skb->rbnode, &q->head);
		rtnl_kमुक्त_skbs(skb, skb);
		sch->q.qlen--;
	पूर्ण
पूर्ण

अटल व्योम etf_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);

	/* Only cancel watchकरोg अगर it's been initialized. */
	अगर (q->watchकरोg.qdisc == sch)
		qdisc_watchकरोg_cancel(&q->watchकरोg);

	/* No matter which mode we are on, it's safe to clear both lists. */
	बारortedlist_clear(sch);
	__qdisc_reset_queue(&sch->q);

	sch->qstats.backlog = 0;
	sch->q.qlen = 0;

	q->last = 0;
पूर्ण

अटल व्योम etf_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);

	/* Only cancel watchकरोg अगर it's been initialized. */
	अगर (q->watchकरोg.qdisc == sch)
		qdisc_watchकरोg_cancel(&q->watchकरोg);

	etf_disable_offload(dev, q);
पूर्ण

अटल पूर्णांक etf_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा etf_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_etf_qopt opt = अणु पूर्ण;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	opt.delta = q->delta;
	opt.घड़ीid = q->घड़ीid;
	अगर (q->offload)
		opt.flags |= TC_ETF_OFFLOAD_ON;

	अगर (q->deadline_mode)
		opt.flags |= TC_ETF_DEADLINE_MODE_ON;

	अगर (q->skip_sock_check)
		opt.flags |= TC_ETF_SKIP_SOCK_CHECK;

	अगर (nla_put(skb, TCA_ETF_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल काष्ठा Qdisc_ops etf_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"etf",
	.priv_size	=	माप(काष्ठा etf_sched_data),
	.enqueue	=	etf_enqueue_बारortedlist,
	.dequeue	=	etf_dequeue_बारortedlist,
	.peek		=	etf_peek_बारortedlist,
	.init		=	etf_init,
	.reset		=	etf_reset,
	.destroy	=	etf_destroy,
	.dump		=	etf_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init etf_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&etf_qdisc_ops);
पूर्ण

अटल व्योम __निकास etf_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&etf_qdisc_ops);
पूर्ण
module_init(etf_module_init)
module_निकास(etf_module_निकास)
MODULE_LICENSE("GPL");
