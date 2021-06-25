<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/act_sample.c - Packet sampling tc action
 * Copyright (c) 2017 Yotam Gigi <yotamg@mellanox.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/tc_act/tc_sample.h>
#समावेश <net/tc_act/tc_sample.h>
#समावेश <net/psample.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/अगर_arp.h>

अटल अचिन्हित पूर्णांक sample_net_id;
अटल काष्ठा tc_action_ops act_sample_ops;

अटल स्थिर काष्ठा nla_policy sample_policy[TCA_SAMPLE_MAX + 1] = अणु
	[TCA_SAMPLE_PARMS]		= अणु .len = माप(काष्ठा tc_sample) पूर्ण,
	[TCA_SAMPLE_RATE]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_SAMPLE_TRUNC_SIZE]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_SAMPLE_PSAMPLE_GROUP]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_sample_init(काष्ठा net *net, काष्ठा nlattr *nla,
			   काष्ठा nlattr *est, काष्ठा tc_action **a, पूर्णांक ovr,
			   पूर्णांक bind, bool rtnl_held, काष्ठा tcf_proto *tp,
			   u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, sample_net_id);
	काष्ठा nlattr *tb[TCA_SAMPLE_MAX + 1];
	काष्ठा psample_group *psample_group;
	u32 psample_group_num, rate, index;
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_sample *parm;
	काष्ठा tcf_sample *s;
	bool exists = false;
	पूर्णांक ret, err;

	अगर (!nla)
		वापस -EINVAL;
	ret = nla_parse_nested_deprecated(tb, TCA_SAMPLE_MAX, nla,
					  sample_policy, शून्य);
	अगर (ret < 0)
		वापस ret;
	अगर (!tb[TCA_SAMPLE_PARMS] || !tb[TCA_SAMPLE_RATE] ||
	    !tb[TCA_SAMPLE_PSAMPLE_GROUP])
		वापस -EINVAL;

	parm = nla_data(tb[TCA_SAMPLE_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_sample_ops, bind, true, 0);
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

	rate = nla_get_u32(tb[TCA_SAMPLE_RATE]);
	अगर (!rate) अणु
		NL_SET_ERR_MSG(extack, "invalid sample rate");
		err = -EINVAL;
		जाओ put_chain;
	पूर्ण
	psample_group_num = nla_get_u32(tb[TCA_SAMPLE_PSAMPLE_GROUP]);
	psample_group = psample_group_get(net, psample_group_num);
	अगर (!psample_group) अणु
		err = -ENOMEM;
		जाओ put_chain;
	पूर्ण

	s = to_sample(*a);

	spin_lock_bh(&s->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	s->rate = rate;
	s->psample_group_num = psample_group_num;
	psample_group = rcu_replace_poपूर्णांकer(s->psample_group, psample_group,
					    lockdep_is_held(&s->tcf_lock));

	अगर (tb[TCA_SAMPLE_TRUNC_SIZE]) अणु
		s->truncate = true;
		s->trunc_size = nla_get_u32(tb[TCA_SAMPLE_TRUNC_SIZE]);
	पूर्ण
	spin_unlock_bh(&s->tcf_lock);

	अगर (psample_group)
		psample_group_put(psample_group);
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

अटल व्योम tcf_sample_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_sample *s = to_sample(a);
	काष्ठा psample_group *psample_group;

	/* last reference to action, no need to lock */
	psample_group = rcu_dereference_रक्षित(s->psample_group, 1);
	RCU_INIT_POINTER(s->psample_group, शून्य);
	अगर (psample_group)
		psample_group_put(psample_group);
पूर्ण

अटल bool tcf_sample_dev_ok_push(काष्ठा net_device *dev)
अणु
	चयन (dev->type) अणु
	हाल ARPHRD_TUNNEL:
	हाल ARPHRD_TUNNEL6:
	हाल ARPHRD_SIT:
	हाल ARPHRD_IPGRE:
	हाल ARPHRD_IP6GRE:
	हाल ARPHRD_VOID:
	हाल ARPHRD_NONE:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक tcf_sample_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_sample *s = to_sample(a);
	काष्ठा psample_group *psample_group;
	काष्ठा psample_metadata md = अणुपूर्ण;
	पूर्णांक retval;

	tcf_lastuse_update(&s->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(s->common.cpu_bstats), skb);
	retval = READ_ONCE(s->tcf_action);

	psample_group = rcu_dereference_bh(s->psample_group);

	/* अक्रमomly sample packets according to rate */
	अगर (psample_group && (pअक्रमom_u32() % s->rate == 0)) अणु
		अगर (!skb_at_tc_ingress(skb)) अणु
			md.in_अगरindex = skb->skb_iअगर;
			md.out_अगरindex = skb->dev->अगरindex;
		पूर्ण अन्यथा अणु
			md.in_अगरindex = skb->dev->अगरindex;
		पूर्ण

		/* on ingress, the mac header माला_लो popped, so push it back */
		अगर (skb_at_tc_ingress(skb) && tcf_sample_dev_ok_push(skb->dev))
			skb_push(skb, skb->mac_len);

		md.trunc_size = s->truncate ? s->trunc_size : skb->len;
		psample_sample_packet(psample_group, skb, s->rate, &md);

		अगर (skb_at_tc_ingress(skb) && tcf_sample_dev_ok_push(skb->dev))
			skb_pull(skb, skb->mac_len);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम tcf_sample_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
				    u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_sample *s = to_sample(a);
	काष्ठा tcf_t *पंचांग = &s->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_sample_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			   पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_sample *s = to_sample(a);
	काष्ठा tc_sample opt = अणु
		.index      = s->tcf_index,
		.refcnt     = refcount_पढ़ो(&s->tcf_refcnt) - ref,
		.bindcnt    = atomic_पढ़ो(&s->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&s->tcf_lock);
	opt.action = s->tcf_action;
	अगर (nla_put(skb, TCA_SAMPLE_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &s->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_SAMPLE_TM, माप(t), &t, TCA_SAMPLE_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_SAMPLE_RATE, s->rate))
		जाओ nla_put_failure;

	अगर (s->truncate)
		अगर (nla_put_u32(skb, TCA_SAMPLE_TRUNC_SIZE, s->trunc_size))
			जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_SAMPLE_PSAMPLE_GROUP, s->psample_group_num))
		जाओ nla_put_failure;
	spin_unlock_bh(&s->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&s->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_sample_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb, पूर्णांक type,
			     स्थिर काष्ठा tc_action_ops *ops,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, sample_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_sample_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, sample_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल व्योम tcf_psample_group_put(व्योम *priv)
अणु
	काष्ठा psample_group *group = priv;

	psample_group_put(group);
पूर्ण

अटल काष्ठा psample_group *
tcf_sample_get_group(स्थिर काष्ठा tc_action *a,
		     tc_action_priv_deकाष्ठाor *deकाष्ठाor)
अणु
	काष्ठा tcf_sample *s = to_sample(a);
	काष्ठा psample_group *group;

	group = rcu_dereference_रक्षित(s->psample_group,
					  lockdep_is_held(&s->tcf_lock));
	अगर (group) अणु
		psample_group_take(group);
		*deकाष्ठाor = tcf_psample_group_put;
	पूर्ण

	वापस group;
पूर्ण

अटल काष्ठा tc_action_ops act_sample_ops = अणु
	.kind	  = "sample",
	.id	  = TCA_ID_SAMPLE,
	.owner	  = THIS_MODULE,
	.act	  = tcf_sample_act,
	.stats_update = tcf_sample_stats_update,
	.dump	  = tcf_sample_dump,
	.init	  = tcf_sample_init,
	.cleanup  = tcf_sample_cleanup,
	.walk	  = tcf_sample_walker,
	.lookup	  = tcf_sample_search,
	.get_psample_group = tcf_sample_get_group,
	.size	  = माप(काष्ठा tcf_sample),
पूर्ण;

अटल __net_init पूर्णांक sample_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, sample_net_id);

	वापस tc_action_net_init(net, tn, &act_sample_ops);
पूर्ण

अटल व्योम __net_निकास sample_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, sample_net_id);
पूर्ण

अटल काष्ठा pernet_operations sample_net_ops = अणु
	.init = sample_init_net,
	.निकास_batch = sample_निकास_net,
	.id   = &sample_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init sample_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_sample_ops, &sample_net_ops);
पूर्ण

अटल व्योम __निकास sample_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_sample_ops, &sample_net_ops);
पूर्ण

module_init(sample_init_module);
module_निकास(sample_cleanup_module);

MODULE_AUTHOR("Yotam Gigi <yotam.gi@gmail.com>");
MODULE_DESCRIPTION("Packet sampling action");
MODULE_LICENSE("GPL v2");
