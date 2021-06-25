<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* net/sched/act_ctinfo.c  netfilter ctinfo connmark actions
 *
 * Copyright (c) 2019 Kevin Darbyshire-Bryant <ldir@darbyshire-bryant.me.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>
#समावेश <uapi/linux/tc_act/tc_ctinfo.h>
#समावेश <net/tc_act/tc_ctinfo.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

अटल काष्ठा tc_action_ops act_ctinfo_ops;
अटल अचिन्हित पूर्णांक ctinfo_net_id;

अटल व्योम tcf_ctinfo_dscp_set(काष्ठा nf_conn *ct, काष्ठा tcf_ctinfo *ca,
				काष्ठा tcf_ctinfo_params *cp,
				काष्ठा sk_buff *skb, पूर्णांक wlen, पूर्णांक proto)
अणु
	u8 dscp, newdscp;

	newdscp = (((ct->mark & cp->dscpmask) >> cp->dscpmaskshअगरt) << 2) &
		     ~INET_ECN_MASK;

	चयन (proto) अणु
	हाल NFPROTO_IPV4:
		dscp = ipv4_get_dsfield(ip_hdr(skb)) & ~INET_ECN_MASK;
		अगर (dscp != newdscp) अणु
			अगर (likely(!skb_try_make_writable(skb, wlen))) अणु
				ipv4_change_dsfield(ip_hdr(skb),
						    INET_ECN_MASK,
						    newdscp);
				ca->stats_dscp_set++;
			पूर्ण अन्यथा अणु
				ca->stats_dscp_error++;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NFPROTO_IPV6:
		dscp = ipv6_get_dsfield(ipv6_hdr(skb)) & ~INET_ECN_MASK;
		अगर (dscp != newdscp) अणु
			अगर (likely(!skb_try_make_writable(skb, wlen))) अणु
				ipv6_change_dsfield(ipv6_hdr(skb),
						    INET_ECN_MASK,
						    newdscp);
				ca->stats_dscp_set++;
			पूर्ण अन्यथा अणु
				ca->stats_dscp_error++;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcf_ctinfo_cpmark_set(काष्ठा nf_conn *ct, काष्ठा tcf_ctinfo *ca,
				  काष्ठा tcf_ctinfo_params *cp,
				  काष्ठा sk_buff *skb)
अणु
	ca->stats_cpmark_set++;
	skb->mark = ct->mark & cp->cpmarkmask;
पूर्ण

अटल पूर्णांक tcf_ctinfo_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *thash = शून्य;
	काष्ठा tcf_ctinfo *ca = to_ctinfo(a);
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_zone zone;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा tcf_ctinfo_params *cp;
	काष्ठा nf_conn *ct;
	पूर्णांक proto, wlen;
	पूर्णांक action;

	cp = rcu_dereference_bh(ca->params);

	tcf_lastuse_update(&ca->tcf_पंचांग);
	bstats_update(&ca->tcf_bstats, skb);
	action = READ_ONCE(ca->tcf_action);

	wlen = skb_network_offset(skb);
	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		wlen += माप(काष्ठा iphdr);
		अगर (!pskb_may_pull(skb, wlen))
			जाओ out;

		proto = NFPROTO_IPV4;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		wlen += माप(काष्ठा ipv6hdr);
		अगर (!pskb_may_pull(skb, wlen))
			जाओ out;

		proto = NFPROTO_IPV6;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct) अणु /* look harder, usually ingress */
		अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
				       proto, cp->net, &tuple))
			जाओ out;
		zone.id = cp->zone;
		zone.dir = NF_CT_DEFAULT_ZONE_सूची;

		thash = nf_conntrack_find_get(cp->net, &zone, &tuple);
		अगर (!thash)
			जाओ out;

		ct = nf_ct_tuplehash_to_ctrack(thash);
	पूर्ण

	अगर (cp->mode & CTINFO_MODE_DSCP)
		अगर (!cp->dscpstatemask || (ct->mark & cp->dscpstatemask))
			tcf_ctinfo_dscp_set(ct, ca, cp, skb, wlen, proto);

	अगर (cp->mode & CTINFO_MODE_CPMARK)
		tcf_ctinfo_cpmark_set(ct, ca, cp, skb);

	अगर (thash)
		nf_ct_put(ct);
out:
	वापस action;
पूर्ण

अटल स्थिर काष्ठा nla_policy ctinfo_policy[TCA_CTINFO_MAX + 1] = अणु
	[TCA_CTINFO_ACT]		  =
		NLA_POLICY_EXACT_LEN(माप(काष्ठा tc_ctinfo)),
	[TCA_CTINFO_ZONE]		  = अणु .type = NLA_U16 पूर्ण,
	[TCA_CTINFO_PARMS_DSCP_MASK]	  = अणु .type = NLA_U32 पूर्ण,
	[TCA_CTINFO_PARMS_DSCP_STATEMASK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CTINFO_PARMS_CPMARK_MASK]	  = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_ctinfo_init(काष्ठा net *net, काष्ठा nlattr *nla,
			   काष्ठा nlattr *est, काष्ठा tc_action **a,
			   पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			   काष्ठा tcf_proto *tp, u32 flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ctinfo_net_id);
	u32 dscpmask = 0, dscpstatemask, index;
	काष्ठा nlattr *tb[TCA_CTINFO_MAX + 1];
	काष्ठा tcf_ctinfo_params *cp_new;
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_ctinfo *actparm;
	काष्ठा tcf_ctinfo *ci;
	u8 dscpmaskshअगरt;
	पूर्णांक ret = 0, err;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "ctinfo requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_CTINFO_MAX, nla, ctinfo_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_CTINFO_ACT]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing required TCA_CTINFO_ACT attribute");
		वापस -EINVAL;
	पूर्ण
	actparm = nla_data(tb[TCA_CTINFO_ACT]);

	/* करो some basic validation here beक्रमe dynamically allocating things */
	/* that we would otherwise have to clean up.			      */
	अगर (tb[TCA_CTINFO_PARMS_DSCP_MASK]) अणु
		dscpmask = nla_get_u32(tb[TCA_CTINFO_PARMS_DSCP_MASK]);
		/* need contiguous 6 bit mask */
		dscpmaskshअगरt = dscpmask ? __ffs(dscpmask) : 0;
		अगर ((~0 & (dscpmask >> dscpmaskshअगरt)) != 0x3f) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_CTINFO_PARMS_DSCP_MASK],
					    "dscp mask must be 6 contiguous bits");
			वापस -EINVAL;
		पूर्ण
		dscpstatemask = tb[TCA_CTINFO_PARMS_DSCP_STATEMASK] ?
			nla_get_u32(tb[TCA_CTINFO_PARMS_DSCP_STATEMASK]) : 0;
		/* mask & statemask must not overlap */
		अगर (dscpmask & dscpstatemask) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_CTINFO_PARMS_DSCP_STATEMASK],
					    "dscp statemask must not overlap dscp mask");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* करोne the validation:now to the actual action allocation */
	index = actparm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!err) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_ctinfo_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (err > 0) अणु
		अगर (bind) /* करोn't override शेषs */
			वापस 0;
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस err;
	पूर्ण

	err = tcf_action_check_ctrlact(actparm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	ci = to_ctinfo(*a);

	cp_new = kzalloc(माप(*cp_new), GFP_KERNEL);
	अगर (unlikely(!cp_new)) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	cp_new->net = net;
	cp_new->zone = tb[TCA_CTINFO_ZONE] ?
			nla_get_u16(tb[TCA_CTINFO_ZONE]) : 0;
	अगर (dscpmask) अणु
		cp_new->dscpmask = dscpmask;
		cp_new->dscpmaskshअगरt = dscpmaskshअगरt;
		cp_new->dscpstatemask = dscpstatemask;
		cp_new->mode |= CTINFO_MODE_DSCP;
	पूर्ण

	अगर (tb[TCA_CTINFO_PARMS_CPMARK_MASK]) अणु
		cp_new->cpmarkmask =
				nla_get_u32(tb[TCA_CTINFO_PARMS_CPMARK_MASK]);
		cp_new->mode |= CTINFO_MODE_CPMARK;
	पूर्ण

	spin_lock_bh(&ci->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, actparm->action, जाओ_ch);
	cp_new = rcu_replace_poपूर्णांकer(ci->params, cp_new,
				     lockdep_is_held(&ci->tcf_lock));
	spin_unlock_bh(&ci->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (cp_new)
		kमुक्त_rcu(cp_new, rcu);

	वापस ret;

put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_ctinfo_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			   पूर्णांक bind, पूर्णांक ref)
अणु
	काष्ठा tcf_ctinfo *ci = to_ctinfo(a);
	काष्ठा tc_ctinfo opt = अणु
		.index   = ci->tcf_index,
		.refcnt  = refcount_पढ़ो(&ci->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&ci->tcf_bindcnt) - bind,
	पूर्ण;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_ctinfo_params *cp;
	काष्ठा tcf_t t;

	spin_lock_bh(&ci->tcf_lock);
	cp = rcu_dereference_रक्षित(ci->params,
				       lockdep_is_held(&ci->tcf_lock));

	tcf_पंचांग_dump(&t, &ci->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_CTINFO_TM, माप(t), &t, TCA_CTINFO_PAD))
		जाओ nla_put_failure;

	opt.action = ci->tcf_action;
	अगर (nla_put(skb, TCA_CTINFO_ACT, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, TCA_CTINFO_ZONE, cp->zone))
		जाओ nla_put_failure;

	अगर (cp->mode & CTINFO_MODE_DSCP) अणु
		अगर (nla_put_u32(skb, TCA_CTINFO_PARMS_DSCP_MASK,
				cp->dscpmask))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_CTINFO_PARMS_DSCP_STATEMASK,
				cp->dscpstatemask))
			जाओ nla_put_failure;
	पूर्ण

	अगर (cp->mode & CTINFO_MODE_CPMARK) अणु
		अगर (nla_put_u32(skb, TCA_CTINFO_PARMS_CPMARK_MASK,
				cp->cpmarkmask))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_SET,
			      ci->stats_dscp_set, TCA_CTINFO_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_ERROR,
			      ci->stats_dscp_error, TCA_CTINFO_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_CPMARK_SET,
			      ci->stats_cpmark_set, TCA_CTINFO_PAD))
		जाओ nla_put_failure;

	spin_unlock_bh(&ci->tcf_lock);
	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&ci->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_ctinfo_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb, पूर्णांक type,
			     स्थिर काष्ठा tc_action_ops *ops,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ctinfo_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_ctinfo_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ctinfo_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल व्योम tcf_ctinfo_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_ctinfo *ci = to_ctinfo(a);
	काष्ठा tcf_ctinfo_params *cp;

	cp = rcu_dereference_रक्षित(ci->params, 1);
	अगर (cp)
		kमुक्त_rcu(cp, rcu);
पूर्ण

अटल काष्ठा tc_action_ops act_ctinfo_ops = अणु
	.kind	= "ctinfo",
	.id	= TCA_ID_CTINFO,
	.owner	= THIS_MODULE,
	.act	= tcf_ctinfo_act,
	.dump	= tcf_ctinfo_dump,
	.init	= tcf_ctinfo_init,
	.cleanup= tcf_ctinfo_cleanup,
	.walk	= tcf_ctinfo_walker,
	.lookup	= tcf_ctinfo_search,
	.size	= माप(काष्ठा tcf_ctinfo),
पूर्ण;

अटल __net_init पूर्णांक ctinfo_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ctinfo_net_id);

	वापस tc_action_net_init(net, tn, &act_ctinfo_ops);
पूर्ण

अटल व्योम __net_निकास ctinfo_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, ctinfo_net_id);
पूर्ण

अटल काष्ठा pernet_operations ctinfo_net_ops = अणु
	.init		= ctinfo_init_net,
	.निकास_batch	= ctinfo_निकास_net,
	.id		= &ctinfo_net_id,
	.size		= माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init ctinfo_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_ctinfo_ops, &ctinfo_net_ops);
पूर्ण

अटल व्योम __निकास ctinfo_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_ctinfo_ops, &ctinfo_net_ops);
पूर्ण

module_init(ctinfo_init_module);
module_निकास(ctinfo_cleanup_module);
MODULE_AUTHOR("Kevin Darbyshire-Bryant <ldir@darbyshire-bryant.me.uk>");
MODULE_DESCRIPTION("Connection tracking mark actions");
MODULE_LICENSE("GPL");
