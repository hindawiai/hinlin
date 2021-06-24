<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, Intel Corporation.
 *
 * Author: Alexander Duyck <alexander.h.duyck@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/dsfield.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_skbedit.h>
#समावेश <net/tc_act/tc_skbedit.h>

अटल अचिन्हित पूर्णांक skbedit_net_id;
अटल काष्ठा tc_action_ops act_skbedit_ops;

अटल पूर्णांक tcf_skbedit_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			   काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_skbedit *d = to_skbedit(a);
	काष्ठा tcf_skbedit_params *params;
	पूर्णांक action;

	tcf_lastuse_update(&d->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(d->common.cpu_bstats), skb);

	params = rcu_dereference_bh(d->params);
	action = READ_ONCE(d->tcf_action);

	अगर (params->flags & SKBEDIT_F_PRIORITY)
		skb->priority = params->priority;
	अगर (params->flags & SKBEDIT_F_INHERITDSFIELD) अणु
		पूर्णांक wlen = skb_network_offset(skb);

		चयन (skb_protocol(skb, true)) अणु
		हाल htons(ETH_P_IP):
			wlen += माप(काष्ठा iphdr);
			अगर (!pskb_may_pull(skb, wlen))
				जाओ err;
			skb->priority = ipv4_get_dsfield(ip_hdr(skb)) >> 2;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			wlen += माप(काष्ठा ipv6hdr);
			अगर (!pskb_may_pull(skb, wlen))
				जाओ err;
			skb->priority = ipv6_get_dsfield(ipv6_hdr(skb)) >> 2;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (params->flags & SKBEDIT_F_QUEUE_MAPPING &&
	    skb->dev->real_num_tx_queues > params->queue_mapping)
		skb_set_queue_mapping(skb, params->queue_mapping);
	अगर (params->flags & SKBEDIT_F_MARK) अणु
		skb->mark &= ~params->mask;
		skb->mark |= params->mark & params->mask;
	पूर्ण
	अगर (params->flags & SKBEDIT_F_PTYPE)
		skb->pkt_type = params->ptype;
	वापस action;

err:
	qstats_drop_inc(this_cpu_ptr(d->common.cpu_qstats));
	वापस TC_ACT_SHOT;
पूर्ण

अटल व्योम tcf_skbedit_stats_update(काष्ठा tc_action *a, u64 bytes,
				     u64 packets, u64 drops,
				     u64 lastuse, bool hw)
अणु
	काष्ठा tcf_skbedit *d = to_skbedit(a);
	काष्ठा tcf_t *पंचांग = &d->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल स्थिर काष्ठा nla_policy skbedit_policy[TCA_SKBEDIT_MAX + 1] = अणु
	[TCA_SKBEDIT_PARMS]		= अणु .len = माप(काष्ठा tc_skbedit) पूर्ण,
	[TCA_SKBEDIT_PRIORITY]		= अणु .len = माप(u32) पूर्ण,
	[TCA_SKBEDIT_QUEUE_MAPPING]	= अणु .len = माप(u16) पूर्ण,
	[TCA_SKBEDIT_MARK]		= अणु .len = माप(u32) पूर्ण,
	[TCA_SKBEDIT_PTYPE]		= अणु .len = माप(u16) पूर्ण,
	[TCA_SKBEDIT_MASK]		= अणु .len = माप(u32) पूर्ण,
	[TCA_SKBEDIT_FLAGS]		= अणु .len = माप(u64) पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_skbedit_init(काष्ठा net *net, काष्ठा nlattr *nla,
			    काष्ठा nlattr *est, काष्ठा tc_action **a,
			    पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			    काष्ठा tcf_proto *tp, u32 act_flags,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbedit_net_id);
	काष्ठा tcf_skbedit_params *params_new;
	काष्ठा nlattr *tb[TCA_SKBEDIT_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_skbedit *parm;
	काष्ठा tcf_skbedit *d;
	u32 flags = 0, *priority = शून्य, *mark = शून्य, *mask = शून्य;
	u16 *queue_mapping = शून्य, *ptype = शून्य;
	bool exists = false;
	पूर्णांक ret = 0, err;
	u32 index;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_SKBEDIT_MAX, nla,
					  skbedit_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_SKBEDIT_PARMS] == शून्य)
		वापस -EINVAL;

	अगर (tb[TCA_SKBEDIT_PRIORITY] != शून्य) अणु
		flags |= SKBEDIT_F_PRIORITY;
		priority = nla_data(tb[TCA_SKBEDIT_PRIORITY]);
	पूर्ण

	अगर (tb[TCA_SKBEDIT_QUEUE_MAPPING] != शून्य) अणु
		flags |= SKBEDIT_F_QUEUE_MAPPING;
		queue_mapping = nla_data(tb[TCA_SKBEDIT_QUEUE_MAPPING]);
	पूर्ण

	अगर (tb[TCA_SKBEDIT_PTYPE] != शून्य) अणु
		ptype = nla_data(tb[TCA_SKBEDIT_PTYPE]);
		अगर (!skb_pkt_type_ok(*ptype))
			वापस -EINVAL;
		flags |= SKBEDIT_F_PTYPE;
	पूर्ण

	अगर (tb[TCA_SKBEDIT_MARK] != शून्य) अणु
		flags |= SKBEDIT_F_MARK;
		mark = nla_data(tb[TCA_SKBEDIT_MARK]);
	पूर्ण

	अगर (tb[TCA_SKBEDIT_MASK] != शून्य) अणु
		flags |= SKBEDIT_F_MASK;
		mask = nla_data(tb[TCA_SKBEDIT_MASK]);
	पूर्ण

	अगर (tb[TCA_SKBEDIT_FLAGS] != शून्य) अणु
		u64 *pure_flags = nla_data(tb[TCA_SKBEDIT_FLAGS]);

		अगर (*pure_flags & SKBEDIT_F_INHERITDSFIELD)
			flags |= SKBEDIT_F_INHERITDSFIELD;
	पूर्ण

	parm = nla_data(tb[TCA_SKBEDIT_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (!flags) अणु
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_skbedit_ops, bind, true, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		d = to_skbedit(*a);
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अणु
		d = to_skbedit(*a);
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	params_new = kzalloc(माप(*params_new), GFP_KERNEL);
	अगर (unlikely(!params_new)) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	params_new->flags = flags;
	अगर (flags & SKBEDIT_F_PRIORITY)
		params_new->priority = *priority;
	अगर (flags & SKBEDIT_F_QUEUE_MAPPING)
		params_new->queue_mapping = *queue_mapping;
	अगर (flags & SKBEDIT_F_MARK)
		params_new->mark = *mark;
	अगर (flags & SKBEDIT_F_PTYPE)
		params_new->ptype = *ptype;
	/* शेष behaviour is to use all the bits */
	params_new->mask = 0xffffffff;
	अगर (flags & SKBEDIT_F_MASK)
		params_new->mask = *mask;

	spin_lock_bh(&d->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	params_new = rcu_replace_poपूर्णांकer(d->params, params_new,
					 lockdep_is_held(&d->tcf_lock));
	spin_unlock_bh(&d->tcf_lock);
	अगर (params_new)
		kमुक्त_rcu(params_new, rcu);
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

अटल पूर्णांक tcf_skbedit_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			    पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_skbedit *d = to_skbedit(a);
	काष्ठा tcf_skbedit_params *params;
	काष्ठा tc_skbedit opt = अणु
		.index   = d->tcf_index,
		.refcnt  = refcount_पढ़ो(&d->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&d->tcf_bindcnt) - bind,
	पूर्ण;
	u64 pure_flags = 0;
	काष्ठा tcf_t t;

	spin_lock_bh(&d->tcf_lock);
	params = rcu_dereference_रक्षित(d->params,
					   lockdep_is_held(&d->tcf_lock));
	opt.action = d->tcf_action;

	अगर (nla_put(skb, TCA_SKBEDIT_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
	अगर ((params->flags & SKBEDIT_F_PRIORITY) &&
	    nla_put_u32(skb, TCA_SKBEDIT_PRIORITY, params->priority))
		जाओ nla_put_failure;
	अगर ((params->flags & SKBEDIT_F_QUEUE_MAPPING) &&
	    nla_put_u16(skb, TCA_SKBEDIT_QUEUE_MAPPING, params->queue_mapping))
		जाओ nla_put_failure;
	अगर ((params->flags & SKBEDIT_F_MARK) &&
	    nla_put_u32(skb, TCA_SKBEDIT_MARK, params->mark))
		जाओ nla_put_failure;
	अगर ((params->flags & SKBEDIT_F_PTYPE) &&
	    nla_put_u16(skb, TCA_SKBEDIT_PTYPE, params->ptype))
		जाओ nla_put_failure;
	अगर ((params->flags & SKBEDIT_F_MASK) &&
	    nla_put_u32(skb, TCA_SKBEDIT_MASK, params->mask))
		जाओ nla_put_failure;
	अगर (params->flags & SKBEDIT_F_INHERITDSFIELD)
		pure_flags |= SKBEDIT_F_INHERITDSFIELD;
	अगर (pure_flags != 0 &&
	    nla_put(skb, TCA_SKBEDIT_FLAGS, माप(pure_flags), &pure_flags))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &d->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_SKBEDIT_TM, माप(t), &t, TCA_SKBEDIT_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&d->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&d->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल व्योम tcf_skbedit_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_skbedit *d = to_skbedit(a);
	काष्ठा tcf_skbedit_params *params;

	params = rcu_dereference_रक्षित(d->params, 1);
	अगर (params)
		kमुक्त_rcu(params, rcu);
पूर्ण

अटल पूर्णांक tcf_skbedit_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb, पूर्णांक type,
			      स्थिर काष्ठा tc_action_ops *ops,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbedit_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_skbedit_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbedit_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल माप_प्रकार tcf_skbedit_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	वापस nla_total_size(माप(काष्ठा tc_skbedit))
		+ nla_total_size(माप(u32)) /* TCA_SKBEDIT_PRIORITY */
		+ nla_total_size(माप(u16)) /* TCA_SKBEDIT_QUEUE_MAPPING */
		+ nla_total_size(माप(u32)) /* TCA_SKBEDIT_MARK */
		+ nla_total_size(माप(u16)) /* TCA_SKBEDIT_PTYPE */
		+ nla_total_size(माप(u32)) /* TCA_SKBEDIT_MASK */
		+ nla_total_size_64bit(माप(u64)); /* TCA_SKBEDIT_FLAGS */
पूर्ण

अटल काष्ठा tc_action_ops act_skbedit_ops = अणु
	.kind		=	"skbedit",
	.id		=	TCA_ID_SKBEDIT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_skbedit_act,
	.stats_update	=	tcf_skbedit_stats_update,
	.dump		=	tcf_skbedit_dump,
	.init		=	tcf_skbedit_init,
	.cleanup	=	tcf_skbedit_cleanup,
	.walk		=	tcf_skbedit_walker,
	.get_fill_size	=	tcf_skbedit_get_fill_size,
	.lookup		=	tcf_skbedit_search,
	.size		=	माप(काष्ठा tcf_skbedit),
पूर्ण;

अटल __net_init पूर्णांक skbedit_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, skbedit_net_id);

	वापस tc_action_net_init(net, tn, &act_skbedit_ops);
पूर्ण

अटल व्योम __net_निकास skbedit_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, skbedit_net_id);
पूर्ण

अटल काष्ठा pernet_operations skbedit_net_ops = अणु
	.init = skbedit_init_net,
	.निकास_batch = skbedit_निकास_net,
	.id   = &skbedit_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Alexander Duyck, <alexander.h.duyck@intel.com>");
MODULE_DESCRIPTION("SKB Editing");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init skbedit_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_skbedit_ops, &skbedit_net_ops);
पूर्ण

अटल व्योम __निकास skbedit_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_skbedit_ops, &skbedit_net_ops);
पूर्ण

module_init(skbedit_init_module);
module_निकास(skbedit_cleanup_module);
