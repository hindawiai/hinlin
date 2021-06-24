<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_police.c	Input police filter
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 * 		J Hadi Salim (action changes)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/act_api.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_police.h>

/* Each policer is serialized by its inभागidual spinlock */

अटल अचिन्हित पूर्णांक police_net_id;
अटल काष्ठा tc_action_ops act_police_ops;

अटल पूर्णांक tcf_police_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb, पूर्णांक type,
				 स्थिर काष्ठा tc_action_ops *ops,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, police_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल स्थिर काष्ठा nla_policy police_policy[TCA_POLICE_MAX + 1] = अणु
	[TCA_POLICE_RATE]	= अणु .len = TC_RTAB_SIZE पूर्ण,
	[TCA_POLICE_PEAKRATE]	= अणु .len = TC_RTAB_SIZE पूर्ण,
	[TCA_POLICE_AVRATE]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_POLICE_RESULT]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_POLICE_RATE64]     = अणु .type = NLA_U64 पूर्ण,
	[TCA_POLICE_PEAKRATE64] = अणु .type = NLA_U64 पूर्ण,
	[TCA_POLICE_PKTRATE64]  = अणु .type = NLA_U64, .min = 1 पूर्ण,
	[TCA_POLICE_PKTBURST64] = अणु .type = NLA_U64, .min = 1 पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_police_init(काष्ठा net *net, काष्ठा nlattr *nla,
			       काष्ठा nlattr *est, काष्ठा tc_action **a,
			       पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			       काष्ठा tcf_proto *tp, u32 flags,
			       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret = 0, tcfp_result = TC_ACT_OK, err, size;
	काष्ठा nlattr *tb[TCA_POLICE_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_police *parm;
	काष्ठा tcf_police *police;
	काष्ठा qdisc_rate_table *R_tab = शून्य, *P_tab = शून्य;
	काष्ठा tc_action_net *tn = net_generic(net, police_net_id);
	काष्ठा tcf_police_params *new;
	bool exists = false;
	u32 index;
	u64 rate64, prate64;
	u64 pps, ppsburst;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_POLICE_MAX, nla,
					  police_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_POLICE_TBF] == शून्य)
		वापस -EINVAL;
	size = nla_len(tb[TCA_POLICE_TBF]);
	अगर (size != माप(*parm) && size != माप(काष्ठा tc_police_compat))
		वापस -EINVAL;

	parm = nla_data(tb[TCA_POLICE_TBF]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, शून्य, a,
				     &act_police_ops, bind, true, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
		spin_lock_init(&(to_police(*a)->tcfp_lock));
	पूर्ण अन्यथा अगर (!ovr) अणु
		tcf_idr_release(*a, bind);
		वापस -EEXIST;
	पूर्ण
	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	police = to_police(*a);
	अगर (parm->rate.rate) अणु
		err = -ENOMEM;
		R_tab = qdisc_get_rtab(&parm->rate, tb[TCA_POLICE_RATE], शून्य);
		अगर (R_tab == शून्य)
			जाओ failure;

		अगर (parm->peakrate.rate) अणु
			P_tab = qdisc_get_rtab(&parm->peakrate,
					       tb[TCA_POLICE_PEAKRATE], शून्य);
			अगर (P_tab == शून्य)
				जाओ failure;
		पूर्ण
	पूर्ण

	अगर (est) अणु
		err = gen_replace_estimator(&police->tcf_bstats,
					    police->common.cpu_bstats,
					    &police->tcf_rate_est,
					    &police->tcf_lock,
					    शून्य, est);
		अगर (err)
			जाओ failure;
	पूर्ण अन्यथा अगर (tb[TCA_POLICE_AVRATE] &&
		   (ret == ACT_P_CREATED ||
		    !gen_estimator_active(&police->tcf_rate_est))) अणु
		err = -EINVAL;
		जाओ failure;
	पूर्ण

	अगर (tb[TCA_POLICE_RESULT]) अणु
		tcfp_result = nla_get_u32(tb[TCA_POLICE_RESULT]);
		अगर (TC_ACT_EXT_CMP(tcfp_result, TC_ACT_GOTO_CHAIN)) अणु
			NL_SET_ERR_MSG(extack,
				       "goto chain not allowed on fallback");
			err = -EINVAL;
			जाओ failure;
		पूर्ण
	पूर्ण

	अगर ((tb[TCA_POLICE_PKTRATE64] && !tb[TCA_POLICE_PKTBURST64]) ||
	    (!tb[TCA_POLICE_PKTRATE64] && tb[TCA_POLICE_PKTBURST64])) अणु
		NL_SET_ERR_MSG(extack,
			       "Both or neither packet-per-second burst and rate must be provided");
		err = -EINVAL;
		जाओ failure;
	पूर्ण

	अगर (tb[TCA_POLICE_PKTRATE64] && R_tab) अणु
		NL_SET_ERR_MSG(extack,
			       "packet-per-second and byte-per-second rate limits not allowed in same action");
		err = -EINVAL;
		जाओ failure;
	पूर्ण

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (unlikely(!new)) अणु
		err = -ENOMEM;
		जाओ failure;
	पूर्ण

	/* No failure allowed after this poपूर्णांक */
	new->tcfp_result = tcfp_result;
	new->tcfp_mtu = parm->mtu;
	अगर (!new->tcfp_mtu) अणु
		new->tcfp_mtu = ~0;
		अगर (R_tab)
			new->tcfp_mtu = 255 << R_tab->rate.cell_log;
	पूर्ण
	अगर (R_tab) अणु
		new->rate_present = true;
		rate64 = tb[TCA_POLICE_RATE64] ?
			 nla_get_u64(tb[TCA_POLICE_RATE64]) : 0;
		psched_ratecfg_precompute(&new->rate, &R_tab->rate, rate64);
		qdisc_put_rtab(R_tab);
	पूर्ण अन्यथा अणु
		new->rate_present = false;
	पूर्ण
	अगर (P_tab) अणु
		new->peak_present = true;
		prate64 = tb[TCA_POLICE_PEAKRATE64] ?
			  nla_get_u64(tb[TCA_POLICE_PEAKRATE64]) : 0;
		psched_ratecfg_precompute(&new->peak, &P_tab->rate, prate64);
		qdisc_put_rtab(P_tab);
	पूर्ण अन्यथा अणु
		new->peak_present = false;
	पूर्ण

	new->tcfp_burst = PSCHED_TICKS2NS(parm->burst);
	अगर (new->peak_present)
		new->tcfp_mtu_ptoks = (s64)psched_l2t_ns(&new->peak,
							 new->tcfp_mtu);

	अगर (tb[TCA_POLICE_AVRATE])
		new->tcfp_ewma_rate = nla_get_u32(tb[TCA_POLICE_AVRATE]);

	अगर (tb[TCA_POLICE_PKTRATE64]) अणु
		pps = nla_get_u64(tb[TCA_POLICE_PKTRATE64]);
		ppsburst = nla_get_u64(tb[TCA_POLICE_PKTBURST64]);
		new->pps_present = true;
		new->tcfp_pkt_burst = PSCHED_TICKS2NS(ppsburst);
		psched_ppscfg_precompute(&new->ppsrate, pps);
	पूर्ण

	spin_lock_bh(&police->tcf_lock);
	spin_lock_bh(&police->tcfp_lock);
	police->tcfp_t_c = kसमय_get_ns();
	police->tcfp_toks = new->tcfp_burst;
	अगर (new->peak_present)
		police->tcfp_ptoks = new->tcfp_mtu_ptoks;
	spin_unlock_bh(&police->tcfp_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	new = rcu_replace_poपूर्णांकer(police->params,
				  new,
				  lockdep_is_held(&police->tcf_lock));
	spin_unlock_bh(&police->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (new)
		kमुक्त_rcu(new, rcu);

	वापस ret;

failure:
	qdisc_put_rtab(P_tab);
	qdisc_put_rtab(R_tab);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_police_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_police *police = to_police(a);
	s64 now, toks, ppstoks = 0, ptoks = 0;
	काष्ठा tcf_police_params *p;
	पूर्णांक ret;

	tcf_lastuse_update(&police->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(police->common.cpu_bstats), skb);

	ret = READ_ONCE(police->tcf_action);
	p = rcu_dereference_bh(police->params);

	अगर (p->tcfp_ewma_rate) अणु
		काष्ठा gnet_stats_rate_est64 sample;

		अगर (!gen_estimator_पढ़ो(&police->tcf_rate_est, &sample) ||
		    sample.bps >= p->tcfp_ewma_rate)
			जाओ inc_overlimits;
	पूर्ण

	अगर (qdisc_pkt_len(skb) <= p->tcfp_mtu) अणु
		अगर (!p->rate_present && !p->pps_present) अणु
			ret = p->tcfp_result;
			जाओ end;
		पूर्ण

		now = kसमय_get_ns();
		spin_lock_bh(&police->tcfp_lock);
		toks = min_t(s64, now - police->tcfp_t_c, p->tcfp_burst);
		अगर (p->peak_present) अणु
			ptoks = toks + police->tcfp_ptoks;
			अगर (ptoks > p->tcfp_mtu_ptoks)
				ptoks = p->tcfp_mtu_ptoks;
			ptoks -= (s64)psched_l2t_ns(&p->peak,
						    qdisc_pkt_len(skb));
		पूर्ण
		अगर (p->rate_present) अणु
			toks += police->tcfp_toks;
			अगर (toks > p->tcfp_burst)
				toks = p->tcfp_burst;
			toks -= (s64)psched_l2t_ns(&p->rate, qdisc_pkt_len(skb));
		पूर्ण अन्यथा अगर (p->pps_present) अणु
			ppstoks = min_t(s64, now - police->tcfp_t_c, p->tcfp_pkt_burst);
			ppstoks += police->tcfp_pkttoks;
			अगर (ppstoks > p->tcfp_pkt_burst)
				ppstoks = p->tcfp_pkt_burst;
			ppstoks -= (s64)psched_pkt2t_ns(&p->ppsrate, 1);
		पूर्ण
		अगर ((toks | ptoks | ppstoks) >= 0) अणु
			police->tcfp_t_c = now;
			police->tcfp_toks = toks;
			police->tcfp_ptoks = ptoks;
			police->tcfp_pkttoks = ppstoks;
			spin_unlock_bh(&police->tcfp_lock);
			ret = p->tcfp_result;
			जाओ inc_drops;
		पूर्ण
		spin_unlock_bh(&police->tcfp_lock);
	पूर्ण

inc_overlimits:
	qstats_overlimit_inc(this_cpu_ptr(police->common.cpu_qstats));
inc_drops:
	अगर (ret == TC_ACT_SHOT)
		qstats_drop_inc(this_cpu_ptr(police->common.cpu_qstats));
end:
	वापस ret;
पूर्ण

अटल व्योम tcf_police_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_police *police = to_police(a);
	काष्ठा tcf_police_params *p;

	p = rcu_dereference_रक्षित(police->params, 1);
	अगर (p)
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल व्योम tcf_police_stats_update(काष्ठा tc_action *a,
				    u64 bytes, u64 packets, u64 drops,
				    u64 lastuse, bool hw)
अणु
	काष्ठा tcf_police *police = to_police(a);
	काष्ठा tcf_t *पंचांग = &police->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_police_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			       पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_police *police = to_police(a);
	काष्ठा tcf_police_params *p;
	काष्ठा tc_police opt = अणु
		.index = police->tcf_index,
		.refcnt = refcount_पढ़ो(&police->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&police->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&police->tcf_lock);
	opt.action = police->tcf_action;
	p = rcu_dereference_रक्षित(police->params,
				      lockdep_is_held(&police->tcf_lock));
	opt.mtu = p->tcfp_mtu;
	opt.burst = PSCHED_NS2TICKS(p->tcfp_burst);
	अगर (p->rate_present) अणु
		psched_ratecfg_getrate(&opt.rate, &p->rate);
		अगर ((police->params->rate.rate_bytes_ps >= (1ULL << 32)) &&
		    nla_put_u64_64bit(skb, TCA_POLICE_RATE64,
				      police->params->rate.rate_bytes_ps,
				      TCA_POLICE_PAD))
			जाओ nla_put_failure;
	पूर्ण
	अगर (p->peak_present) अणु
		psched_ratecfg_getrate(&opt.peakrate, &p->peak);
		अगर ((police->params->peak.rate_bytes_ps >= (1ULL << 32)) &&
		    nla_put_u64_64bit(skb, TCA_POLICE_PEAKRATE64,
				      police->params->peak.rate_bytes_ps,
				      TCA_POLICE_PAD))
			जाओ nla_put_failure;
	पूर्ण
	अगर (p->pps_present) अणु
		अगर (nla_put_u64_64bit(skb, TCA_POLICE_PKTRATE64,
				      police->params->ppsrate.rate_pkts_ps,
				      TCA_POLICE_PAD))
			जाओ nla_put_failure;
		अगर (nla_put_u64_64bit(skb, TCA_POLICE_PKTBURST64,
				      PSCHED_NS2TICKS(p->tcfp_pkt_burst),
				      TCA_POLICE_PAD))
			जाओ nla_put_failure;
	पूर्ण
	अगर (nla_put(skb, TCA_POLICE_TBF, माप(opt), &opt))
		जाओ nla_put_failure;
	अगर (p->tcfp_result &&
	    nla_put_u32(skb, TCA_POLICE_RESULT, p->tcfp_result))
		जाओ nla_put_failure;
	अगर (p->tcfp_ewma_rate &&
	    nla_put_u32(skb, TCA_POLICE_AVRATE, p->tcfp_ewma_rate))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &police->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_POLICE_TM, माप(t), &t, TCA_POLICE_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&police->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&police->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_police_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, police_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

MODULE_AUTHOR("Alexey Kuznetsov");
MODULE_DESCRIPTION("Policing actions");
MODULE_LICENSE("GPL");

अटल काष्ठा tc_action_ops act_police_ops = अणु
	.kind		=	"police",
	.id		=	TCA_ID_POLICE,
	.owner		=	THIS_MODULE,
	.stats_update	=	tcf_police_stats_update,
	.act		=	tcf_police_act,
	.dump		=	tcf_police_dump,
	.init		=	tcf_police_init,
	.walk		=	tcf_police_walker,
	.lookup		=	tcf_police_search,
	.cleanup	=	tcf_police_cleanup,
	.size		=	माप(काष्ठा tcf_police),
पूर्ण;

अटल __net_init पूर्णांक police_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, police_net_id);

	वापस tc_action_net_init(net, tn, &act_police_ops);
पूर्ण

अटल व्योम __net_निकास police_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, police_net_id);
पूर्ण

अटल काष्ठा pernet_operations police_net_ops = अणु
	.init = police_init_net,
	.निकास_batch = police_निकास_net,
	.id   = &police_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init police_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_police_ops, &police_net_ops);
पूर्ण

अटल व्योम __निकास police_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_police_ops, &police_net_ops);
पूर्ण

module_init(police_init_module);
module_निकास(police_cleanup_module);
