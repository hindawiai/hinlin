<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_tbf.c	Token Bucket Filter queue.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *		Dmitry Torokhov <dtor@mail.ru> - allow attaching inner qdiscs -
 *						 original idea by Martin Devera
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>


/*	Simple Token Bucket Filter.
	=======================================

	SOURCE.
	-------

	None.

	Description.
	------------

	A data flow obeys TBF with rate R and depth B, अगर क्रम any
	समय पूर्णांकerval t_i...t_f the number of transmitted bits
	करोes not exceed B + R*(t_f-t_i).

	Packetized version of this definition:
	The sequence of packets of sizes s_i served at moments t_i
	obeys TBF, अगर क्रम any i<=k:

	s_i+....+s_k <= B + R*(t_k - t_i)

	Algorithm.
	----------

	Let N(t_i) be B/R initially and N(t) grow continuously with समय as:

	N(t+delta) = minअणुB/R, N(t) + deltaपूर्ण

	If the first packet in queue has length S, it may be
	transmitted only at the समय t_* when S/R <= N(t_*),
	and in this हाल N(t) jumps:

	N(t_* + 0) = N(t_* - 0) - S/R.



	Actually, QoS requires two TBF to be applied to a data stream.
	One of them controls steady state burst size, another
	one with rate P (peak rate) and depth M (equal to link MTU)
	limits bursts at a smaller समय scale.

	It is easy to see that P>R, and B>M. If P is infinity, this द्विगुन
	TBF is equivalent to a single one.

	When TBF works in reshaping mode, latency is estimated as:

	lat = max ((L-B)/R, (L-M)/P)


	NOTES.
	------

	If TBF throttles, it starts a watchकरोg समयr, which will wake it up
	when it is पढ़ोy to transmit.
	Note that the minimal समयr resolution is 1/HZ.
	If no new packets arrive during this period,
	or अगर the device is not awaken by EOI क्रम some previous packet,
	TBF can stop its activity क्रम 1/HZ.


	This means, that with depth B, the maximal rate is

	R_crit = B*HZ

	F.e. क्रम 10Mbit ethernet and HZ=100 the minimal allowed B is ~10Kbytes.

	Note that the peak rate TBF is much more tough: with MTU 1500
	P_crit = 150Kbytes/sec. So, अगर you need greater peak
	rates, use alpha with HZ=1000 :-)

	With classful TBF, limit is just kept क्रम backwards compatibility.
	It is passed to the शेष bfअगरo qdisc - अगर the inner qdisc is
	changed the limit is not effective anymore.
*/

काष्ठा tbf_sched_data अणु
/* Parameters */
	u32		limit;		/* Maximal length of backlog: bytes */
	u32		max_size;
	s64		buffer;		/* Token bucket depth/rate: MUST BE >= MTU/B */
	s64		mtu;
	काष्ठा psched_ratecfg rate;
	काष्ठा psched_ratecfg peak;

/* Variables */
	s64	tokens;			/* Current number of B tokens */
	s64	ptokens;		/* Current number of P tokens */
	s64	t_c;			/* Time check-poपूर्णांक */
	काष्ठा Qdisc	*qdisc;		/* Inner qdisc, शेष - bfअगरo queue */
	काष्ठा qdisc_watchकरोg watchकरोg;	/* Watchकरोg समयr */
पूर्ण;


/* Time to Length, convert समय in ns to length in bytes
 * to determinate how many bytes can be sent in given समय.
 */
अटल u64 psched_ns_t2l(स्थिर काष्ठा psched_ratecfg *r,
			 u64 समय_in_ns)
अणु
	/* The क्रमmula is :
	 * len = (समय_in_ns * r->rate_bytes_ps) / NSEC_PER_SEC
	 */
	u64 len = समय_in_ns * r->rate_bytes_ps;

	करो_भाग(len, NSEC_PER_SEC);

	अगर (unlikely(r->linklayer == TC_LINKLAYER_ATM)) अणु
		करो_भाग(len, 53);
		len = len * 48;
	पूर्ण

	अगर (len > r->overhead)
		len -= r->overhead;
	अन्यथा
		len = 0;

	वापस len;
पूर्ण

अटल व्योम tbf_offload_change(काष्ठा Qdisc *sch)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_tbf_qopt_offload qopt;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_TBF_REPLACE;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.replace_params.rate = q->rate;
	qopt.replace_params.max_size = q->max_size;
	qopt.replace_params.qstats = &sch->qstats;

	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_TBF, &qopt);
पूर्ण

अटल व्योम tbf_offload_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_tbf_qopt_offload qopt;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_TBF_DESTROY;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_TBF, &qopt);
पूर्ण

अटल पूर्णांक tbf_offload_dump(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_tbf_qopt_offload qopt;

	qopt.command = TC_TBF_STATS;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.stats.bstats = &sch->bstats;
	qopt.stats.qstats = &sch->qstats;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_TBF, &qopt);
पूर्ण

/* GSO packet is too big, segment it so that tbf can transmit
 * each segment in समय
 */
अटल पूर्णांक tbf_segment(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *segs, *nskb;
	netdev_features_t features = netअगर_skb_features(skb);
	अचिन्हित पूर्णांक len = 0, prev_len = qdisc_pkt_len(skb);
	पूर्णांक ret, nb;

	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);

	अगर (IS_ERR_OR_शून्य(segs))
		वापस qdisc_drop(skb, sch, to_मुक्त);

	nb = 0;
	skb_list_walk_safe(segs, segs, nskb) अणु
		skb_mark_not_on_list(segs);
		qdisc_skb_cb(segs)->pkt_len = segs->len;
		len += segs->len;
		ret = qdisc_enqueue(segs, q->qdisc, to_मुक्त);
		अगर (ret != NET_XMIT_SUCCESS) अणु
			अगर (net_xmit_drop_count(ret))
				qdisc_qstats_drop(sch);
		पूर्ण अन्यथा अणु
			nb++;
		पूर्ण
	पूर्ण
	sch->q.qlen += nb;
	अगर (nb > 1)
		qdisc_tree_reduce_backlog(sch, 1 - nb, prev_len - len);
	consume_skb(skb);
	वापस nb > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DROP;
पूर्ण

अटल पूर्णांक tbf_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	पूर्णांक ret;

	अगर (qdisc_pkt_len(skb) > q->max_size) अणु
		अगर (skb_is_gso(skb) &&
		    skb_gso_validate_mac_len(skb, q->max_size))
			वापस tbf_segment(skb, sch, to_मुक्त);
		वापस qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण
	ret = qdisc_enqueue(skb, q->qdisc, to_मुक्त);
	अगर (ret != NET_XMIT_SUCCESS) अणु
		अगर (net_xmit_drop_count(ret))
			qdisc_qstats_drop(sch);
		वापस ret;
	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल bool tbf_peak_present(स्थिर काष्ठा tbf_sched_data *q)
अणु
	वापस q->peak.rate_bytes_ps;
पूर्ण

अटल काष्ठा sk_buff *tbf_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

	skb = q->qdisc->ops->peek(q->qdisc);

	अगर (skb) अणु
		s64 now;
		s64 toks;
		s64 ptoks = 0;
		अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);

		now = kसमय_get_ns();
		toks = min_t(s64, now - q->t_c, q->buffer);

		अगर (tbf_peak_present(q)) अणु
			ptoks = toks + q->ptokens;
			अगर (ptoks > q->mtu)
				ptoks = q->mtu;
			ptoks -= (s64) psched_l2t_ns(&q->peak, len);
		पूर्ण
		toks += q->tokens;
		अगर (toks > q->buffer)
			toks = q->buffer;
		toks -= (s64) psched_l2t_ns(&q->rate, len);

		अगर ((toks|ptoks) >= 0) अणु
			skb = qdisc_dequeue_peeked(q->qdisc);
			अगर (unlikely(!skb))
				वापस शून्य;

			q->t_c = now;
			q->tokens = toks;
			q->ptokens = ptoks;
			qdisc_qstats_backlog_dec(sch, skb);
			sch->q.qlen--;
			qdisc_bstats_update(sch, skb);
			वापस skb;
		पूर्ण

		qdisc_watchकरोg_schedule_ns(&q->watchकरोg,
					   now + max_t(दीर्घ, -toks, -ptoks));

		/* Maybe we have a लघुer packet in the queue,
		   which can be sent now. It sounds cool,
		   but, however, this is wrong in principle.
		   We MUST NOT reorder packets under these circumstances.

		   Really, अगर we split the flow पूर्णांकo independent
		   subflows, it would be a very good solution.
		   This is the मुख्य idea of all FQ algorithms
		   (cf. CSZ, HPFQ, HFSC)
		 */

		qdisc_qstats_overlimit(sch);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम tbf_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);

	qdisc_reset(q->qdisc);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
	q->t_c = kसमय_get_ns();
	q->tokens = q->buffer;
	q->ptokens = q->mtu;
	qdisc_watchकरोg_cancel(&q->watchकरोg);
पूर्ण

अटल स्थिर काष्ठा nla_policy tbf_policy[TCA_TBF_MAX + 1] = अणु
	[TCA_TBF_PARMS]	= अणु .len = माप(काष्ठा tc_tbf_qopt) पूर्ण,
	[TCA_TBF_RTAB]	= अणु .type = NLA_BINARY, .len = TC_RTAB_SIZE पूर्ण,
	[TCA_TBF_PTAB]	= अणु .type = NLA_BINARY, .len = TC_RTAB_SIZE पूर्ण,
	[TCA_TBF_RATE64]	= अणु .type = NLA_U64 पूर्ण,
	[TCA_TBF_PRATE64]	= अणु .type = NLA_U64 पूर्ण,
	[TCA_TBF_BURST] = अणु .type = NLA_U32 पूर्ण,
	[TCA_TBF_PBURST] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक tbf_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_TBF_MAX + 1];
	काष्ठा tc_tbf_qopt *qopt;
	काष्ठा Qdisc *child = शून्य;
	काष्ठा psched_ratecfg rate;
	काष्ठा psched_ratecfg peak;
	u64 max_size;
	s64 buffer, mtu;
	u64 rate64 = 0, prate64 = 0;

	err = nla_parse_nested_deprecated(tb, TCA_TBF_MAX, opt, tbf_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	err = -EINVAL;
	अगर (tb[TCA_TBF_PARMS] == शून्य)
		जाओ करोne;

	qopt = nla_data(tb[TCA_TBF_PARMS]);
	अगर (qopt->rate.linklayer == TC_LINKLAYER_UNAWARE)
		qdisc_put_rtab(qdisc_get_rtab(&qopt->rate,
					      tb[TCA_TBF_RTAB],
					      शून्य));

	अगर (qopt->peakrate.linklayer == TC_LINKLAYER_UNAWARE)
			qdisc_put_rtab(qdisc_get_rtab(&qopt->peakrate,
						      tb[TCA_TBF_PTAB],
						      शून्य));

	buffer = min_t(u64, PSCHED_TICKS2NS(qopt->buffer), ~0U);
	mtu = min_t(u64, PSCHED_TICKS2NS(qopt->mtu), ~0U);

	अगर (tb[TCA_TBF_RATE64])
		rate64 = nla_get_u64(tb[TCA_TBF_RATE64]);
	psched_ratecfg_precompute(&rate, &qopt->rate, rate64);

	अगर (tb[TCA_TBF_BURST]) अणु
		max_size = nla_get_u32(tb[TCA_TBF_BURST]);
		buffer = psched_l2t_ns(&rate, max_size);
	पूर्ण अन्यथा अणु
		max_size = min_t(u64, psched_ns_t2l(&rate, buffer), ~0U);
	पूर्ण

	अगर (qopt->peakrate.rate) अणु
		अगर (tb[TCA_TBF_PRATE64])
			prate64 = nla_get_u64(tb[TCA_TBF_PRATE64]);
		psched_ratecfg_precompute(&peak, &qopt->peakrate, prate64);
		अगर (peak.rate_bytes_ps <= rate.rate_bytes_ps) अणु
			pr_warn_ratelimited("sch_tbf: peakrate %llu is lower than or equals to rate %llu !\n",
					peak.rate_bytes_ps, rate.rate_bytes_ps);
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (tb[TCA_TBF_PBURST]) अणु
			u32 pburst = nla_get_u32(tb[TCA_TBF_PBURST]);
			max_size = min_t(u32, max_size, pburst);
			mtu = psched_l2t_ns(&peak, pburst);
		पूर्ण अन्यथा अणु
			max_size = min_t(u64, max_size, psched_ns_t2l(&peak, mtu));
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(&peak, 0, माप(peak));
	पूर्ण

	अगर (max_size < psched_mtu(qdisc_dev(sch)))
		pr_warn_ratelimited("sch_tbf: burst %llu is lower than device %s mtu (%u) !\n",
				    max_size, qdisc_dev(sch)->name,
				    psched_mtu(qdisc_dev(sch)));

	अगर (!max_size) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (q->qdisc != &noop_qdisc) अणु
		err = fअगरo_set_limit(q->qdisc, qopt->limit);
		अगर (err)
			जाओ करोne;
	पूर्ण अन्यथा अगर (qopt->limit > 0) अणु
		child = fअगरo_create_dflt(sch, &bfअगरo_qdisc_ops, qopt->limit,
					 extack);
		अगर (IS_ERR(child)) अणु
			err = PTR_ERR(child);
			जाओ करोne;
		पूर्ण

		/* child is fअगरo, no need to check क्रम noop_qdisc */
		qdisc_hash_add(child, true);
	पूर्ण

	sch_tree_lock(sch);
	अगर (child) अणु
		qdisc_tree_flush_backlog(q->qdisc);
		qdisc_put(q->qdisc);
		q->qdisc = child;
	पूर्ण
	q->limit = qopt->limit;
	अगर (tb[TCA_TBF_PBURST])
		q->mtu = mtu;
	अन्यथा
		q->mtu = PSCHED_TICKS2NS(qopt->mtu);
	q->max_size = max_size;
	अगर (tb[TCA_TBF_BURST])
		q->buffer = buffer;
	अन्यथा
		q->buffer = PSCHED_TICKS2NS(qopt->buffer);
	q->tokens = q->buffer;
	q->ptokens = q->mtu;

	स_नकल(&q->rate, &rate, माप(काष्ठा psched_ratecfg));
	स_नकल(&q->peak, &peak, माप(काष्ठा psched_ratecfg));

	sch_tree_unlock(sch);
	err = 0;

	tbf_offload_change(sch);
करोne:
	वापस err;
पूर्ण

अटल पूर्णांक tbf_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);

	qdisc_watchकरोg_init(&q->watchकरोg, sch);
	q->qdisc = &noop_qdisc;

	अगर (!opt)
		वापस -EINVAL;

	q->t_c = kसमय_get_ns();

	वापस tbf_change(sch, opt, extack);
पूर्ण

अटल व्योम tbf_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);

	qdisc_watchकरोg_cancel(&q->watchकरोg);
	tbf_offload_destroy(sch);
	qdisc_put(q->qdisc);
पूर्ण

अटल पूर्णांक tbf_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *nest;
	काष्ठा tc_tbf_qopt opt;
	पूर्णांक err;

	err = tbf_offload_dump(sch);
	अगर (err)
		वापस err;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	opt.limit = q->limit;
	psched_ratecfg_getrate(&opt.rate, &q->rate);
	अगर (tbf_peak_present(q))
		psched_ratecfg_getrate(&opt.peakrate, &q->peak);
	अन्यथा
		स_रखो(&opt.peakrate, 0, माप(opt.peakrate));
	opt.mtu = PSCHED_NS2TICKS(q->mtu);
	opt.buffer = PSCHED_NS2TICKS(q->buffer);
	अगर (nla_put(skb, TCA_TBF_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
	अगर (q->rate.rate_bytes_ps >= (1ULL << 32) &&
	    nla_put_u64_64bit(skb, TCA_TBF_RATE64, q->rate.rate_bytes_ps,
			      TCA_TBF_PAD))
		जाओ nla_put_failure;
	अगर (tbf_peak_present(q) &&
	    q->peak.rate_bytes_ps >= (1ULL << 32) &&
	    nla_put_u64_64bit(skb, TCA_TBF_PRATE64, q->peak.rate_bytes_ps,
			      TCA_TBF_PAD))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक tbf_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);

	tcm->tcm_handle |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handle;

	वापस 0;
पूर्ण

अटल पूर्णांक tbf_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);

	अगर (new == शून्य)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *tbf_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tbf_sched_data *q = qdisc_priv(sch);
	वापस q->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ tbf_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 1;
पूर्ण

अटल व्योम tbf_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
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

अटल स्थिर काष्ठा Qdisc_class_ops tbf_class_ops = अणु
	.graft		=	tbf_graft,
	.leaf		=	tbf_leaf,
	.find		=	tbf_find,
	.walk		=	tbf_walk,
	.dump		=	tbf_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops tbf_qdisc_ops __पढ़ो_mostly = अणु
	.next		=	शून्य,
	.cl_ops		=	&tbf_class_ops,
	.id		=	"tbf",
	.priv_size	=	माप(काष्ठा tbf_sched_data),
	.enqueue	=	tbf_enqueue,
	.dequeue	=	tbf_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	tbf_init,
	.reset		=	tbf_reset,
	.destroy	=	tbf_destroy,
	.change		=	tbf_change,
	.dump		=	tbf_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init tbf_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&tbf_qdisc_ops);
पूर्ण

अटल व्योम __निकास tbf_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&tbf_qdisc_ops);
पूर्ण
module_init(tbf_module_init)
module_निकास(tbf_module_निकास)
MODULE_LICENSE("GPL");
