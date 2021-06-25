<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 Jiri Pirko <jiri@resnulli.us>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_vlan.h>
#समावेश <net/tc_act/tc_vlan.h>

अटल अचिन्हित पूर्णांक vlan_net_id;
अटल काष्ठा tc_action_ops act_vlan_ops;

अटल पूर्णांक tcf_vlan_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_vlan *v = to_vlan(a);
	काष्ठा tcf_vlan_params *p;
	पूर्णांक action;
	पूर्णांक err;
	u16 tci;

	tcf_lastuse_update(&v->tcf_पंचांग);
	tcf_action_update_bstats(&v->common, skb);

	/* Ensure 'data' poपूर्णांकs at mac_header prior calling vlan manipulating
	 * functions.
	 */
	अगर (skb_at_tc_ingress(skb))
		skb_push_rcsum(skb, skb->mac_len);

	action = READ_ONCE(v->tcf_action);

	p = rcu_dereference_bh(v->vlan_p);

	चयन (p->tcfv_action) अणु
	हाल TCA_VLAN_ACT_POP:
		err = skb_vlan_pop(skb);
		अगर (err)
			जाओ drop;
		अवरोध;
	हाल TCA_VLAN_ACT_PUSH:
		err = skb_vlan_push(skb, p->tcfv_push_proto, p->tcfv_push_vid |
				    (p->tcfv_push_prio << VLAN_PRIO_SHIFT));
		अगर (err)
			जाओ drop;
		अवरोध;
	हाल TCA_VLAN_ACT_MODIFY:
		/* No-op अगर no vlan tag (either hw-accel or in-payload) */
		अगर (!skb_vlan_tagged(skb))
			जाओ out;
		/* extract existing tag (and guarantee no hw-accel tag) */
		अगर (skb_vlan_tag_present(skb)) अणु
			tci = skb_vlan_tag_get(skb);
			__vlan_hwaccel_clear_tag(skb);
		पूर्ण अन्यथा अणु
			/* in-payload vlan tag, pop it */
			err = __skb_vlan_pop(skb, &tci);
			अगर (err)
				जाओ drop;
		पूर्ण
		/* replace the vid */
		tci = (tci & ~VLAN_VID_MASK) | p->tcfv_push_vid;
		/* replace prio bits, अगर tcfv_push_prio specअगरied */
		अगर (p->tcfv_push_prio) अणु
			tci &= ~VLAN_PRIO_MASK;
			tci |= p->tcfv_push_prio << VLAN_PRIO_SHIFT;
		पूर्ण
		/* put updated tci as hwaccel tag */
		__vlan_hwaccel_put_tag(skb, p->tcfv_push_proto, tci);
		अवरोध;
	हाल TCA_VLAN_ACT_POP_ETH:
		err = skb_eth_pop(skb);
		अगर (err)
			जाओ drop;
		अवरोध;
	हाल TCA_VLAN_ACT_PUSH_ETH:
		err = skb_eth_push(skb, p->tcfv_push_dst, p->tcfv_push_src);
		अगर (err)
			जाओ drop;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

out:
	अगर (skb_at_tc_ingress(skb))
		skb_pull_rcsum(skb, skb->mac_len);

	वापस action;

drop:
	tcf_action_inc_drop_qstats(&v->common);
	वापस TC_ACT_SHOT;
पूर्ण

अटल स्थिर काष्ठा nla_policy vlan_policy[TCA_VLAN_MAX + 1] = अणु
	[TCA_VLAN_UNSPEC]		= अणु .strict_start_type = TCA_VLAN_PUSH_ETH_DST पूर्ण,
	[TCA_VLAN_PARMS]		= अणु .len = माप(काष्ठा tc_vlan) पूर्ण,
	[TCA_VLAN_PUSH_VLAN_ID]		= अणु .type = NLA_U16 पूर्ण,
	[TCA_VLAN_PUSH_VLAN_PROTOCOL]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_VLAN_PUSH_VLAN_PRIORITY]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_VLAN_PUSH_ETH_DST]		= NLA_POLICY_ETH_ADDR,
	[TCA_VLAN_PUSH_ETH_SRC]		= NLA_POLICY_ETH_ADDR,
पूर्ण;

अटल पूर्णांक tcf_vlan_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a,
			 पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			 काष्ठा tcf_proto *tp, u32 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, vlan_net_id);
	काष्ठा nlattr *tb[TCA_VLAN_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_vlan_params *p;
	काष्ठा tc_vlan *parm;
	काष्ठा tcf_vlan *v;
	पूर्णांक action;
	u16 push_vid = 0;
	__be16 push_proto = 0;
	u8 push_prio = 0;
	bool exists = false;
	पूर्णांक ret = 0, err;
	u32 index;

	अगर (!nla)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_VLAN_MAX, nla, vlan_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_VLAN_PARMS])
		वापस -EINVAL;
	parm = nla_data(tb[TCA_VLAN_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	चयन (parm->v_action) अणु
	हाल TCA_VLAN_ACT_POP:
		अवरोध;
	हाल TCA_VLAN_ACT_PUSH:
	हाल TCA_VLAN_ACT_MODIFY:
		अगर (!tb[TCA_VLAN_PUSH_VLAN_ID]) अणु
			अगर (exists)
				tcf_idr_release(*a, bind);
			अन्यथा
				tcf_idr_cleanup(tn, index);
			वापस -EINVAL;
		पूर्ण
		push_vid = nla_get_u16(tb[TCA_VLAN_PUSH_VLAN_ID]);
		अगर (push_vid >= VLAN_VID_MASK) अणु
			अगर (exists)
				tcf_idr_release(*a, bind);
			अन्यथा
				tcf_idr_cleanup(tn, index);
			वापस -दुस्फल;
		पूर्ण

		अगर (tb[TCA_VLAN_PUSH_VLAN_PROTOCOL]) अणु
			push_proto = nla_get_be16(tb[TCA_VLAN_PUSH_VLAN_PROTOCOL]);
			चयन (push_proto) अणु
			हाल htons(ETH_P_8021Q):
			हाल htons(ETH_P_8021AD):
				अवरोध;
			शेष:
				अगर (exists)
					tcf_idr_release(*a, bind);
				अन्यथा
					tcf_idr_cleanup(tn, index);
				वापस -EPROTONOSUPPORT;
			पूर्ण
		पूर्ण अन्यथा अणु
			push_proto = htons(ETH_P_8021Q);
		पूर्ण

		अगर (tb[TCA_VLAN_PUSH_VLAN_PRIORITY])
			push_prio = nla_get_u8(tb[TCA_VLAN_PUSH_VLAN_PRIORITY]);
		अवरोध;
	हाल TCA_VLAN_ACT_POP_ETH:
		अवरोध;
	हाल TCA_VLAN_ACT_PUSH_ETH:
		अगर (!tb[TCA_VLAN_PUSH_ETH_DST] || !tb[TCA_VLAN_PUSH_ETH_SRC]) अणु
			अगर (exists)
				tcf_idr_release(*a, bind);
			अन्यथा
				tcf_idr_cleanup(tn, index);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण
	action = parm->v_action;

	अगर (!exists) अणु
		ret = tcf_idr_create_from_flags(tn, index, est, a,
						&act_vlan_ops, bind, flags);
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

	v = to_vlan(*a);

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	p->tcfv_action = action;
	p->tcfv_push_vid = push_vid;
	p->tcfv_push_prio = push_prio;
	p->tcfv_push_proto = push_proto;

	अगर (action == TCA_VLAN_ACT_PUSH_ETH) अणु
		nla_स_नकल(&p->tcfv_push_dst, tb[TCA_VLAN_PUSH_ETH_DST],
			   ETH_ALEN);
		nla_स_नकल(&p->tcfv_push_src, tb[TCA_VLAN_PUSH_ETH_SRC],
			   ETH_ALEN);
	पूर्ण

	spin_lock_bh(&v->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	p = rcu_replace_poपूर्णांकer(v->vlan_p, p, lockdep_is_held(&v->tcf_lock));
	spin_unlock_bh(&v->tcf_lock);

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

अटल व्योम tcf_vlan_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_vlan *v = to_vlan(a);
	काष्ठा tcf_vlan_params *p;

	p = rcu_dereference_रक्षित(v->vlan_p, 1);
	अगर (p)
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल पूर्णांक tcf_vlan_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			 पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_vlan *v = to_vlan(a);
	काष्ठा tcf_vlan_params *p;
	काष्ठा tc_vlan opt = अणु
		.index    = v->tcf_index,
		.refcnt   = refcount_पढ़ो(&v->tcf_refcnt) - ref,
		.bindcnt  = atomic_पढ़ो(&v->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&v->tcf_lock);
	opt.action = v->tcf_action;
	p = rcu_dereference_रक्षित(v->vlan_p, lockdep_is_held(&v->tcf_lock));
	opt.v_action = p->tcfv_action;
	अगर (nla_put(skb, TCA_VLAN_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर ((p->tcfv_action == TCA_VLAN_ACT_PUSH ||
	     p->tcfv_action == TCA_VLAN_ACT_MODIFY) &&
	    (nla_put_u16(skb, TCA_VLAN_PUSH_VLAN_ID, p->tcfv_push_vid) ||
	     nla_put_be16(skb, TCA_VLAN_PUSH_VLAN_PROTOCOL,
			  p->tcfv_push_proto) ||
	     (nla_put_u8(skb, TCA_VLAN_PUSH_VLAN_PRIORITY,
					      p->tcfv_push_prio))))
		जाओ nla_put_failure;

	अगर (p->tcfv_action == TCA_VLAN_ACT_PUSH_ETH) अणु
		अगर (nla_put(skb, TCA_VLAN_PUSH_ETH_DST, ETH_ALEN,
			    p->tcfv_push_dst))
			जाओ nla_put_failure;
		अगर (nla_put(skb, TCA_VLAN_PUSH_ETH_SRC, ETH_ALEN,
			    p->tcfv_push_src))
			जाओ nla_put_failure;
	पूर्ण

	tcf_पंचांग_dump(&t, &v->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_VLAN_TM, माप(t), &t, TCA_VLAN_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&v->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&v->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_vlan_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, vlan_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल व्योम tcf_vlan_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
				  u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_vlan *v = to_vlan(a);
	काष्ठा tcf_t *पंचांग = &v->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_vlan_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, vlan_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल माप_प्रकार tcf_vlan_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	वापस nla_total_size(माप(काष्ठा tc_vlan))
		+ nla_total_size(माप(u16)) /* TCA_VLAN_PUSH_VLAN_ID */
		+ nla_total_size(माप(u16)) /* TCA_VLAN_PUSH_VLAN_PROTOCOL */
		+ nla_total_size(माप(u8)); /* TCA_VLAN_PUSH_VLAN_PRIORITY */
पूर्ण

अटल काष्ठा tc_action_ops act_vlan_ops = अणु
	.kind		=	"vlan",
	.id		=	TCA_ID_VLAN,
	.owner		=	THIS_MODULE,
	.act		=	tcf_vlan_act,
	.dump		=	tcf_vlan_dump,
	.init		=	tcf_vlan_init,
	.cleanup	=	tcf_vlan_cleanup,
	.walk		=	tcf_vlan_walker,
	.stats_update	=	tcf_vlan_stats_update,
	.get_fill_size	=	tcf_vlan_get_fill_size,
	.lookup		=	tcf_vlan_search,
	.size		=	माप(काष्ठा tcf_vlan),
पूर्ण;

अटल __net_init पूर्णांक vlan_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, vlan_net_id);

	वापस tc_action_net_init(net, tn, &act_vlan_ops);
पूर्ण

अटल व्योम __net_निकास vlan_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, vlan_net_id);
पूर्ण

अटल काष्ठा pernet_operations vlan_net_ops = अणु
	.init = vlan_init_net,
	.निकास_batch = vlan_निकास_net,
	.id   = &vlan_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init vlan_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_vlan_ops, &vlan_net_ops);
पूर्ण

अटल व्योम __निकास vlan_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_vlan_ops, &vlan_net_ops);
पूर्ण

module_init(vlan_init_module);
module_निकास(vlan_cleanup_module);

MODULE_AUTHOR("Jiri Pirko <jiri@resnulli.us>");
MODULE_DESCRIPTION("vlan manipulation actions");
MODULE_LICENSE("GPL v2");
