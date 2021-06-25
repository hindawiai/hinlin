<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mpls.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tc_act/tc_mpls.h>
#समावेश <net/mpls.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_mpls.h>

अटल अचिन्हित पूर्णांक mpls_net_id;
अटल काष्ठा tc_action_ops act_mpls_ops;

#घोषणा ACT_MPLS_TTL_DEFAULT	255

अटल __be32 tcf_mpls_get_lse(काष्ठा mpls_shim_hdr *lse,
			       काष्ठा tcf_mpls_params *p, bool set_bos)
अणु
	u32 new_lse = 0;

	अगर (lse)
		new_lse = be32_to_cpu(lse->label_stack_entry);

	अगर (p->tcfm_label != ACT_MPLS_LABEL_NOT_SET) अणु
		new_lse &= ~MPLS_LS_LABEL_MASK;
		new_lse |= p->tcfm_label << MPLS_LS_LABEL_SHIFT;
	पूर्ण
	अगर (p->tcfm_ttl) अणु
		new_lse &= ~MPLS_LS_TTL_MASK;
		new_lse |= p->tcfm_ttl << MPLS_LS_TTL_SHIFT;
	पूर्ण
	अगर (p->tcfm_tc != ACT_MPLS_TC_NOT_SET) अणु
		new_lse &= ~MPLS_LS_TC_MASK;
		new_lse |= p->tcfm_tc << MPLS_LS_TC_SHIFT;
	पूर्ण
	अगर (p->tcfm_bos != ACT_MPLS_BOS_NOT_SET) अणु
		new_lse &= ~MPLS_LS_S_MASK;
		new_lse |= p->tcfm_bos << MPLS_LS_S_SHIFT;
	पूर्ण अन्यथा अगर (set_bos) अणु
		new_lse |= 1 << MPLS_LS_S_SHIFT;
	पूर्ण

	वापस cpu_to_be32(new_lse);
पूर्ण

अटल पूर्णांक tcf_mpls_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_mpls *m = to_mpls(a);
	काष्ठा tcf_mpls_params *p;
	__be32 new_lse;
	पूर्णांक ret, mac_len;

	tcf_lastuse_update(&m->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(m->common.cpu_bstats), skb);

	/* Ensure 'data' poपूर्णांकs at mac_header prior calling mpls manipulating
	 * functions.
	 */
	अगर (skb_at_tc_ingress(skb)) अणु
		skb_push_rcsum(skb, skb->mac_len);
		mac_len = skb->mac_len;
	पूर्ण अन्यथा अणु
		mac_len = skb_network_header(skb) - skb_mac_header(skb);
	पूर्ण

	ret = READ_ONCE(m->tcf_action);

	p = rcu_dereference_bh(m->mpls_p);

	चयन (p->tcfm_action) अणु
	हाल TCA_MPLS_ACT_POP:
		अगर (skb_mpls_pop(skb, p->tcfm_proto, mac_len,
				 skb->dev && skb->dev->type == ARPHRD_ETHER))
			जाओ drop;
		अवरोध;
	हाल TCA_MPLS_ACT_PUSH:
		new_lse = tcf_mpls_get_lse(शून्य, p, !eth_p_mpls(skb_protocol(skb, true)));
		अगर (skb_mpls_push(skb, new_lse, p->tcfm_proto, mac_len,
				  skb->dev && skb->dev->type == ARPHRD_ETHER))
			जाओ drop;
		अवरोध;
	हाल TCA_MPLS_ACT_MAC_PUSH:
		अगर (skb_vlan_tag_present(skb)) अणु
			अगर (__vlan_insert_inner_tag(skb, skb->vlan_proto,
						    skb_vlan_tag_get(skb),
						    ETH_HLEN) < 0)
				जाओ drop;

			skb->protocol = skb->vlan_proto;
			__vlan_hwaccel_clear_tag(skb);
		पूर्ण

		new_lse = tcf_mpls_get_lse(शून्य, p, mac_len ||
					   !eth_p_mpls(skb->protocol));

		अगर (skb_mpls_push(skb, new_lse, p->tcfm_proto, 0, false))
			जाओ drop;
		अवरोध;
	हाल TCA_MPLS_ACT_MODIFY:
		अगर (!pskb_may_pull(skb,
				   skb_network_offset(skb) + MPLS_HLEN))
			जाओ drop;
		new_lse = tcf_mpls_get_lse(mpls_hdr(skb), p, false);
		अगर (skb_mpls_update_lse(skb, new_lse))
			जाओ drop;
		अवरोध;
	हाल TCA_MPLS_ACT_DEC_TTL:
		अगर (skb_mpls_dec_ttl(skb))
			जाओ drop;
		अवरोध;
	पूर्ण

	अगर (skb_at_tc_ingress(skb))
		skb_pull_rcsum(skb, skb->mac_len);

	वापस ret;

drop:
	qstats_drop_inc(this_cpu_ptr(m->common.cpu_qstats));
	वापस TC_ACT_SHOT;
पूर्ण

अटल पूर्णांक valid_label(स्थिर काष्ठा nlattr *attr,
		       काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर u32 *label = nla_data(attr);

	अगर (*label & ~MPLS_LABEL_MASK || *label == MPLS_LABEL_IMPLशून्य) अणु
		NL_SET_ERR_MSG_MOD(extack, "MPLS label out of range");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy mpls_policy[TCA_MPLS_MAX + 1] = अणु
	[TCA_MPLS_PARMS]	= NLA_POLICY_EXACT_LEN(माप(काष्ठा tc_mpls)),
	[TCA_MPLS_PROTO]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_MPLS_LABEL]	= NLA_POLICY_VALIDATE_FN(NLA_U32, valid_label),
	[TCA_MPLS_TC]		= NLA_POLICY_RANGE(NLA_U8, 0, 7),
	[TCA_MPLS_TTL]		= NLA_POLICY_MIN(NLA_U8, 1),
	[TCA_MPLS_BOS]		= NLA_POLICY_RANGE(NLA_U8, 0, 1),
पूर्ण;

अटल पूर्णांक tcf_mpls_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a,
			 पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			 काष्ठा tcf_proto *tp, u32 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mpls_net_id);
	काष्ठा nlattr *tb[TCA_MPLS_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_mpls_params *p;
	काष्ठा tc_mpls *parm;
	bool exists = false;
	काष्ठा tcf_mpls *m;
	पूर्णांक ret = 0, err;
	u8 mpls_ttl = 0;
	u32 index;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing netlink attributes");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_MPLS_MAX, nla, mpls_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_MPLS_PARMS]) अणु
		NL_SET_ERR_MSG_MOD(extack, "No MPLS params");
		वापस -EINVAL;
	पूर्ण
	parm = nla_data(tb[TCA_MPLS_PARMS]);
	index = parm->index;

	/* Verअगरy parameters against action type. */
	चयन (parm->m_action) अणु
	हाल TCA_MPLS_ACT_POP:
		अगर (!tb[TCA_MPLS_PROTO]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Protocol must be set for MPLS pop");
			वापस -EINVAL;
		पूर्ण
		अगर (!eth_proto_is_802_3(nla_get_be16(tb[TCA_MPLS_PROTO]))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid protocol type for MPLS pop");
			वापस -EINVAL;
		पूर्ण
		अगर (tb[TCA_MPLS_LABEL] || tb[TCA_MPLS_TTL] || tb[TCA_MPLS_TC] ||
		    tb[TCA_MPLS_BOS]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Label, TTL, TC or BOS cannot be used with MPLS pop");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल TCA_MPLS_ACT_DEC_TTL:
		अगर (tb[TCA_MPLS_PROTO] || tb[TCA_MPLS_LABEL] ||
		    tb[TCA_MPLS_TTL] || tb[TCA_MPLS_TC] || tb[TCA_MPLS_BOS]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Label, TTL, TC, BOS or protocol cannot be used with MPLS dec_ttl");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल TCA_MPLS_ACT_PUSH:
	हाल TCA_MPLS_ACT_MAC_PUSH:
		अगर (!tb[TCA_MPLS_LABEL]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Label is required for MPLS push");
			वापस -EINVAL;
		पूर्ण
		अगर (tb[TCA_MPLS_PROTO] &&
		    !eth_p_mpls(nla_get_be16(tb[TCA_MPLS_PROTO]))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Protocol must be an MPLS type for MPLS push");
			वापस -EPROTONOSUPPORT;
		पूर्ण
		/* Push needs a TTL - अगर not specअगरied, set a शेष value. */
		अगर (!tb[TCA_MPLS_TTL]) अणु
#अगर IS_ENABLED(CONFIG_MPLS)
			mpls_ttl = net->mpls.शेष_ttl ?
				   net->mpls.शेष_ttl : ACT_MPLS_TTL_DEFAULT;
#अन्यथा
			mpls_ttl = ACT_MPLS_TTL_DEFAULT;
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल TCA_MPLS_ACT_MODIFY:
		अगर (tb[TCA_MPLS_PROTO]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Protocol cannot be used with MPLS modify");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Unknown MPLS action");
		वापस -EINVAL;
	पूर्ण

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_mpls_ops, bind, true, 0);
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

	m = to_mpls(*a);

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	p->tcfm_action = parm->m_action;
	p->tcfm_label = tb[TCA_MPLS_LABEL] ? nla_get_u32(tb[TCA_MPLS_LABEL]) :
					     ACT_MPLS_LABEL_NOT_SET;
	p->tcfm_tc = tb[TCA_MPLS_TC] ? nla_get_u8(tb[TCA_MPLS_TC]) :
				       ACT_MPLS_TC_NOT_SET;
	p->tcfm_ttl = tb[TCA_MPLS_TTL] ? nla_get_u8(tb[TCA_MPLS_TTL]) :
					 mpls_ttl;
	p->tcfm_bos = tb[TCA_MPLS_BOS] ? nla_get_u8(tb[TCA_MPLS_BOS]) :
					 ACT_MPLS_BOS_NOT_SET;
	p->tcfm_proto = tb[TCA_MPLS_PROTO] ? nla_get_be16(tb[TCA_MPLS_PROTO]) :
					     htons(ETH_P_MPLS_UC);

	spin_lock_bh(&m->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	p = rcu_replace_poपूर्णांकer(m->mpls_p, p, lockdep_is_held(&m->tcf_lock));
	spin_unlock_bh(&m->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (p)
		kमुक्त_rcu(p, rcu);

	वापस ret;
put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल व्योम tcf_mpls_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_mpls *m = to_mpls(a);
	काष्ठा tcf_mpls_params *p;

	p = rcu_dereference_रक्षित(m->mpls_p, 1);
	अगर (p)
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल पूर्णांक tcf_mpls_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			 पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_mpls *m = to_mpls(a);
	काष्ठा tcf_mpls_params *p;
	काष्ठा tc_mpls opt = अणु
		.index    = m->tcf_index,
		.refcnt   = refcount_पढ़ो(&m->tcf_refcnt) - ref,
		.bindcnt  = atomic_पढ़ो(&m->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&m->tcf_lock);
	opt.action = m->tcf_action;
	p = rcu_dereference_रक्षित(m->mpls_p, lockdep_is_held(&m->tcf_lock));
	opt.m_action = p->tcfm_action;

	अगर (nla_put(skb, TCA_MPLS_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर (p->tcfm_label != ACT_MPLS_LABEL_NOT_SET &&
	    nla_put_u32(skb, TCA_MPLS_LABEL, p->tcfm_label))
		जाओ nla_put_failure;

	अगर (p->tcfm_tc != ACT_MPLS_TC_NOT_SET &&
	    nla_put_u8(skb, TCA_MPLS_TC, p->tcfm_tc))
		जाओ nla_put_failure;

	अगर (p->tcfm_ttl && nla_put_u8(skb, TCA_MPLS_TTL, p->tcfm_ttl))
		जाओ nla_put_failure;

	अगर (p->tcfm_bos != ACT_MPLS_BOS_NOT_SET &&
	    nla_put_u8(skb, TCA_MPLS_BOS, p->tcfm_bos))
		जाओ nla_put_failure;

	अगर (nla_put_be16(skb, TCA_MPLS_PROTO, p->tcfm_proto))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &m->tcf_पंचांग);

	अगर (nla_put_64bit(skb, TCA_MPLS_TM, माप(t), &t, TCA_MPLS_PAD))
		जाओ nla_put_failure;

	spin_unlock_bh(&m->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&m->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक tcf_mpls_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mpls_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_mpls_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mpls_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_mpls_ops = अणु
	.kind		=	"mpls",
	.id		=	TCA_ID_MPLS,
	.owner		=	THIS_MODULE,
	.act		=	tcf_mpls_act,
	.dump		=	tcf_mpls_dump,
	.init		=	tcf_mpls_init,
	.cleanup	=	tcf_mpls_cleanup,
	.walk		=	tcf_mpls_walker,
	.lookup		=	tcf_mpls_search,
	.size		=	माप(काष्ठा tcf_mpls),
पूर्ण;

अटल __net_init पूर्णांक mpls_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mpls_net_id);

	वापस tc_action_net_init(net, tn, &act_mpls_ops);
पूर्ण

अटल व्योम __net_निकास mpls_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, mpls_net_id);
पूर्ण

अटल काष्ठा pernet_operations mpls_net_ops = अणु
	.init = mpls_init_net,
	.निकास_batch = mpls_निकास_net,
	.id   = &mpls_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init mpls_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_mpls_ops, &mpls_net_ops);
पूर्ण

अटल व्योम __निकास mpls_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_mpls_ops, &mpls_net_ops);
पूर्ण

module_init(mpls_init_module);
module_निकास(mpls_cleanup_module);

MODULE_SOFTDEP("post: mpls_gso");
MODULE_AUTHOR("Netronome Systems <oss-drivers@netronome.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MPLS manipulation actions");
