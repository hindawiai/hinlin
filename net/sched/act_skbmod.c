<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_skbmod.c  skb data modअगरier
 *
 * Copyright (c) 2016 Jamal Hadi Salim <jhs@mojatatu.com>
*/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_skbmod.h>
#समावेश <net/tc_act/tc_skbmod.h>

अटल अचिन्हित पूर्णांक skbmod_net_id;
अटल काष्ठा tc_action_ops act_skbmod_ops;

#घोषणा MAX_EDIT_LEN ETH_HLEN
अटल पूर्णांक tcf_skbmod_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_skbmod *d = to_skbmod(a);
	पूर्णांक action;
	काष्ठा tcf_skbmod_params *p;
	u64 flags;
	पूर्णांक err;

	tcf_lastuse_update(&d->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(d->common.cpu_bstats), skb);

	/* XXX: अगर you are going to edit more fields beyond ethernet header
	 * (example when you add IP header replacement or vlan swap)
	 * then MAX_EDIT_LEN needs to change appropriately
	*/
	err = skb_ensure_writable(skb, MAX_EDIT_LEN);
	अगर (unlikely(err)) /* best policy is to drop on the न्यूनमान */
		जाओ drop;

	action = READ_ONCE(d->tcf_action);
	अगर (unlikely(action == TC_ACT_SHOT))
		जाओ drop;

	p = rcu_dereference_bh(d->skbmod_p);
	flags = p->flags;
	अगर (flags & SKBMOD_F_DMAC)
		ether_addr_copy(eth_hdr(skb)->h_dest, p->eth_dst);
	अगर (flags & SKBMOD_F_SMAC)
		ether_addr_copy(eth_hdr(skb)->h_source, p->eth_src);
	अगर (flags & SKBMOD_F_ETYPE)
		eth_hdr(skb)->h_proto = p->eth_type;

	अगर (flags & SKBMOD_F_SWAPMAC) अणु
		u16 पंचांगpaddr[ETH_ALEN / 2]; /* ether_addr_copy() requirement */
		/*XXX: I am sure we can come up with more efficient swapping*/
		ether_addr_copy((u8 *)पंचांगpaddr, eth_hdr(skb)->h_dest);
		ether_addr_copy(eth_hdr(skb)->h_dest, eth_hdr(skb)->h_source);
		ether_addr_copy(eth_hdr(skb)->h_source, (u8 *)पंचांगpaddr);
	पूर्ण

	वापस action;

drop:
	qstats_overlimit_inc(this_cpu_ptr(d->common.cpu_qstats));
	वापस TC_ACT_SHOT;
पूर्ण

अटल स्थिर काष्ठा nla_policy skbmod_policy[TCA_SKBMOD_MAX + 1] = अणु
	[TCA_SKBMOD_PARMS]		= अणु .len = माप(काष्ठा tc_skbmod) पूर्ण,
	[TCA_SKBMOD_DMAC]		= अणु .len = ETH_ALEN पूर्ण,
	[TCA_SKBMOD_SMAC]		= अणु .len = ETH_ALEN पूर्ण,
	[TCA_SKBMOD_ETYPE]		= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_skbmod_init(काष्ठा net *net, काष्ठा nlattr *nla,
			   काष्ठा nlattr *est, काष्ठा tc_action **a,
			   पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			   काष्ठा tcf_proto *tp, u32 flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbmod_net_id);
	काष्ठा nlattr *tb[TCA_SKBMOD_MAX + 1];
	काष्ठा tcf_skbmod_params *p, *p_old;
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_skbmod *parm;
	u32 lflags = 0, index;
	काष्ठा tcf_skbmod *d;
	bool exists = false;
	u8 *daddr = शून्य;
	u8 *saddr = शून्य;
	u16 eth_type = 0;
	पूर्णांक ret = 0, err;

	अगर (!nla)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_SKBMOD_MAX, nla,
					  skbmod_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_SKBMOD_PARMS])
		वापस -EINVAL;

	अगर (tb[TCA_SKBMOD_DMAC]) अणु
		daddr = nla_data(tb[TCA_SKBMOD_DMAC]);
		lflags |= SKBMOD_F_DMAC;
	पूर्ण

	अगर (tb[TCA_SKBMOD_SMAC]) अणु
		saddr = nla_data(tb[TCA_SKBMOD_SMAC]);
		lflags |= SKBMOD_F_SMAC;
	पूर्ण

	अगर (tb[TCA_SKBMOD_ETYPE]) अणु
		eth_type = nla_get_u16(tb[TCA_SKBMOD_ETYPE]);
		lflags |= SKBMOD_F_ETYPE;
	पूर्ण

	parm = nla_data(tb[TCA_SKBMOD_PARMS]);
	index = parm->index;
	अगर (parm->flags & SKBMOD_F_SWAPMAC)
		lflags = SKBMOD_F_SWAPMAC;

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (!lflags) अणु
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_skbmod_ops, bind, true, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (!ovr) अणु
		tcf_idr_release(*a, bind);
		वापस -EEXIST;
	पूर्ण
	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	d = to_skbmod(*a);

	p = kzalloc(माप(काष्ठा tcf_skbmod_params), GFP_KERNEL);
	अगर (unlikely(!p)) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	p->flags = lflags;

	अगर (ovr)
		spin_lock_bh(&d->tcf_lock);
	/* Protected by tcf_lock अगर overwriting existing action. */
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	p_old = rcu_dereference_रक्षित(d->skbmod_p, 1);

	अगर (lflags & SKBMOD_F_DMAC)
		ether_addr_copy(p->eth_dst, daddr);
	अगर (lflags & SKBMOD_F_SMAC)
		ether_addr_copy(p->eth_src, saddr);
	अगर (lflags & SKBMOD_F_ETYPE)
		p->eth_type = htons(eth_type);

	rcu_assign_poपूर्णांकer(d->skbmod_p, p);
	अगर (ovr)
		spin_unlock_bh(&d->tcf_lock);

	अगर (p_old)
		kमुक्त_rcu(p_old, rcu);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	वापस ret;
put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल व्योम tcf_skbmod_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_skbmod *d = to_skbmod(a);
	काष्ठा tcf_skbmod_params  *p;

	p = rcu_dereference_रक्षित(d->skbmod_p, 1);
	अगर (p)
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल पूर्णांक tcf_skbmod_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			   पूर्णांक bind, पूर्णांक ref)
अणु
	काष्ठा tcf_skbmod *d = to_skbmod(a);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_skbmod_params  *p;
	काष्ठा tc_skbmod opt = अणु
		.index   = d->tcf_index,
		.refcnt  = refcount_पढ़ो(&d->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&d->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&d->tcf_lock);
	opt.action = d->tcf_action;
	p = rcu_dereference_रक्षित(d->skbmod_p,
				      lockdep_is_held(&d->tcf_lock));
	opt.flags  = p->flags;
	अगर (nla_put(skb, TCA_SKBMOD_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
	अगर ((p->flags & SKBMOD_F_DMAC) &&
	    nla_put(skb, TCA_SKBMOD_DMAC, ETH_ALEN, p->eth_dst))
		जाओ nla_put_failure;
	अगर ((p->flags & SKBMOD_F_SMAC) &&
	    nla_put(skb, TCA_SKBMOD_SMAC, ETH_ALEN, p->eth_src))
		जाओ nla_put_failure;
	अगर ((p->flags & SKBMOD_F_ETYPE) &&
	    nla_put_u16(skb, TCA_SKBMOD_ETYPE, ntohs(p->eth_type)))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &d->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_SKBMOD_TM, माप(t), &t, TCA_SKBMOD_PAD))
		जाओ nla_put_failure;

	spin_unlock_bh(&d->tcf_lock);
	वापस skb->len;
nla_put_failure:
	spin_unlock_bh(&d->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_skbmod_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb, पूर्णांक type,
			     स्थिर काष्ठा tc_action_ops *ops,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbmod_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_skbmod_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbmod_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_skbmod_ops = अणु
	.kind		=	"skbmod",
	.id		=	TCA_ACT_SKBMOD,
	.owner		=	THIS_MODULE,
	.act		=	tcf_skbmod_act,
	.dump		=	tcf_skbmod_dump,
	.init		=	tcf_skbmod_init,
	.cleanup	=	tcf_skbmod_cleanup,
	.walk		=	tcf_skbmod_walker,
	.lookup		=	tcf_skbmod_search,
	.size		=	माप(काष्ठा tcf_skbmod),
पूर्ण;

अटल __net_init पूर्णांक skbmod_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbmod_net_id);

	वापस tc_action_net_init(net, tn, &act_skbmod_ops);
पूर्ण

अटल व्योम __net_निकास skbmod_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, skbmod_net_id);
पूर्ण

अटल काष्ठा pernet_operations skbmod_net_ops = अणु
	.init = skbmod_init_net,
	.निकास_batch = skbmod_निकास_net,
	.id   = &skbmod_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim, <jhs@mojatatu.com>");
MODULE_DESCRIPTION("SKB data mod-ing");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init skbmod_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_skbmod_ops, &skbmod_net_ops);
पूर्ण

अटल व्योम __निकास skbmod_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_skbmod_ops, &skbmod_net_ops);
पूर्ण

module_init(skbmod_init_module);
module_निकास(skbmod_cleanup_module);
