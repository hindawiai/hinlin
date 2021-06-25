<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_connmark.c  netfilter connmark retriever action
 * skb mark is over-written
 *
 * Copyright (c) 2011 Felix Fietkau <nbd@खोलोwrt.org>
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
#समावेश <uapi/linux/tc_act/tc_connmark.h>
#समावेश <net/tc_act/tc_connmark.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

अटल अचिन्हित पूर्णांक connmark_net_id;
अटल काष्ठा tc_action_ops act_connmark_ops;

अटल पूर्णांक tcf_connmark_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			    काष्ठा tcf_result *res)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *thash;
	काष्ठा nf_conntrack_tuple tuple;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा tcf_connmark_info *ca = to_connmark(a);
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn *c;
	पूर्णांक proto;

	spin_lock(&ca->tcf_lock);
	tcf_lastuse_update(&ca->tcf_पंचांग);
	bstats_update(&ca->tcf_bstats, skb);

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		अगर (skb->len < माप(काष्ठा iphdr))
			जाओ out;

		proto = NFPROTO_IPV4;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (skb->len < माप(काष्ठा ipv6hdr))
			जाओ out;

		proto = NFPROTO_IPV6;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	c = nf_ct_get(skb, &ctinfo);
	अगर (c) अणु
		skb->mark = c->mark;
		/* using overlimits stats to count how many packets marked */
		ca->tcf_qstats.overlimits++;
		जाओ out;
	पूर्ण

	अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
			       proto, ca->net, &tuple))
		जाओ out;

	zone.id = ca->zone;
	zone.dir = NF_CT_DEFAULT_ZONE_सूची;

	thash = nf_conntrack_find_get(ca->net, &zone, &tuple);
	अगर (!thash)
		जाओ out;

	c = nf_ct_tuplehash_to_ctrack(thash);
	/* using overlimits stats to count how many packets marked */
	ca->tcf_qstats.overlimits++;
	skb->mark = c->mark;
	nf_ct_put(c);

out:
	spin_unlock(&ca->tcf_lock);
	वापस ca->tcf_action;
पूर्ण

अटल स्थिर काष्ठा nla_policy connmark_policy[TCA_CONNMARK_MAX + 1] = अणु
	[TCA_CONNMARK_PARMS] = अणु .len = माप(काष्ठा tc_connmark) पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_connmark_init(काष्ठा net *net, काष्ठा nlattr *nla,
			     काष्ठा nlattr *est, काष्ठा tc_action **a,
			     पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			     काष्ठा tcf_proto *tp, u32 flags,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, connmark_net_id);
	काष्ठा nlattr *tb[TCA_CONNMARK_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_connmark_info *ci;
	काष्ठा tc_connmark *parm;
	पूर्णांक ret = 0, err;
	u32 index;

	अगर (!nla)
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(tb, TCA_CONNMARK_MAX, nla,
					  connmark_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[TCA_CONNMARK_PARMS])
		वापस -EINVAL;

	parm = nla_data(tb[TCA_CONNMARK_PARMS]);
	index = parm->index;
	ret = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!ret) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_connmark_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		ci = to_connmark(*a);
		err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch,
					       extack);
		अगर (err < 0)
			जाओ release_idr;
		tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
		ci->net = net;
		ci->zone = parm->zone;

		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ci = to_connmark(*a);
		अगर (bind)
			वापस 0;
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
		err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch,
					       extack);
		अगर (err < 0)
			जाओ release_idr;
		/* replacing action and zone */
		spin_lock_bh(&ci->tcf_lock);
		जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
		ci->zone = parm->zone;
		spin_unlock_bh(&ci->tcf_lock);
		अगर (जाओ_ch)
			tcf_chain_put_by_act(जाओ_ch);
		ret = 0;
	पूर्ण

	वापस ret;
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_connmark_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
				    पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_connmark_info *ci = to_connmark(a);
	काष्ठा tc_connmark opt = अणु
		.index   = ci->tcf_index,
		.refcnt  = refcount_पढ़ो(&ci->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&ci->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&ci->tcf_lock);
	opt.action = ci->tcf_action;
	opt.zone = ci->zone;
	अगर (nla_put(skb, TCA_CONNMARK_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &ci->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_CONNMARK_TM, माप(t), &t,
			  TCA_CONNMARK_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&ci->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&ci->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_connmark_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb, पूर्णांक type,
			       स्थिर काष्ठा tc_action_ops *ops,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, connmark_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_connmark_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, connmark_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_connmark_ops = अणु
	.kind		=	"connmark",
	.id		=	TCA_ID_CONNMARK,
	.owner		=	THIS_MODULE,
	.act		=	tcf_connmark_act,
	.dump		=	tcf_connmark_dump,
	.init		=	tcf_connmark_init,
	.walk		=	tcf_connmark_walker,
	.lookup		=	tcf_connmark_search,
	.size		=	माप(काष्ठा tcf_connmark_info),
पूर्ण;

अटल __net_init पूर्णांक connmark_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, connmark_net_id);

	वापस tc_action_net_init(net, tn, &act_connmark_ops);
पूर्ण

अटल व्योम __net_निकास connmark_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, connmark_net_id);
पूर्ण

अटल काष्ठा pernet_operations connmark_net_ops = अणु
	.init = connmark_init_net,
	.निकास_batch = connmark_निकास_net,
	.id   = &connmark_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init connmark_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_connmark_ops, &connmark_net_ops);
पूर्ण

अटल व्योम __निकास connmark_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_connmark_ops, &connmark_net_ops);
पूर्ण

module_init(connmark_init_module);
module_निकास(connmark_cleanup_module);
MODULE_AUTHOR("Felix Fietkau <nbd@openwrt.org>");
MODULE_DESCRIPTION("Connection tracking mark restoring");
MODULE_LICENSE("GPL");
