<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_ipt.c		iptables target पूर्णांकerface
 *
 *TODO: Add other tables. For now we only support the ipv4 table tarमाला_लो
 *
 * Copyright:	Jamal Hadi Salim (2002-13)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/tc_act/tc_ipt.h>
#समावेश <net/tc_act/tc_ipt.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>


अटल अचिन्हित पूर्णांक ipt_net_id;
अटल काष्ठा tc_action_ops act_ipt_ops;

अटल अचिन्हित पूर्णांक xt_net_id;
अटल काष्ठा tc_action_ops act_xt_ops;

अटल पूर्णांक ipt_init_target(काष्ठा net *net, काष्ठा xt_entry_target *t,
			   अक्षर *table, अचिन्हित पूर्णांक hook)
अणु
	काष्ठा xt_tgchk_param par;
	काष्ठा xt_target *target;
	काष्ठा ipt_entry e = अणुपूर्ण;
	पूर्णांक ret = 0;

	target = xt_request_find_target(AF_INET, t->u.user.name,
					t->u.user.revision);
	अगर (IS_ERR(target))
		वापस PTR_ERR(target);

	t->u.kernel.target = target;
	स_रखो(&par, 0, माप(par));
	par.net       = net;
	par.table     = table;
	par.entryinfo = &e;
	par.target    = target;
	par.targinfo  = t->data;
	par.hook_mask = hook;
	par.family    = NFPROTO_IPV4;

	ret = xt_check_target(&par, t->u.target_size - माप(*t), 0, false);
	अगर (ret < 0) अणु
		module_put(t->u.kernel.target->me);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ipt_destroy_target(काष्ठा xt_entry_target *t, काष्ठा net *net)
अणु
	काष्ठा xt_tgdtor_param par = अणु
		.target   = t->u.kernel.target,
		.targinfo = t->data,
		.family   = NFPROTO_IPV4,
		.net      = net,
	पूर्ण;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);
	module_put(par.target->me);
पूर्ण

अटल व्योम tcf_ipt_release(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_ipt *ipt = to_ipt(a);

	अगर (ipt->tcfi_t) अणु
		ipt_destroy_target(ipt->tcfi_t, a->idrinfo->net);
		kमुक्त(ipt->tcfi_t);
	पूर्ण
	kमुक्त(ipt->tcfi_tname);
पूर्ण

अटल स्थिर काष्ठा nla_policy ipt_policy[TCA_IPT_MAX + 1] = अणु
	[TCA_IPT_TABLE]	= अणु .type = NLA_STRING, .len = IFNAMSIZ पूर्ण,
	[TCA_IPT_HOOK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_IPT_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_IPT_TARG]	= अणु .len = माप(काष्ठा xt_entry_target) पूर्ण,
पूर्ण;

अटल पूर्णांक __tcf_ipt_init(काष्ठा net *net, अचिन्हित पूर्णांक id, काष्ठा nlattr *nla,
			  काष्ठा nlattr *est, काष्ठा tc_action **a,
			  स्थिर काष्ठा tc_action_ops *ops, पूर्णांक ovr, पूर्णांक bind,
			  काष्ठा tcf_proto *tp, u32 flags)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, id);
	काष्ठा nlattr *tb[TCA_IPT_MAX + 1];
	काष्ठा tcf_ipt *ipt;
	काष्ठा xt_entry_target *td, *t;
	अक्षर *tname;
	bool exists = false;
	पूर्णांक ret = 0, err;
	u32 hook = 0;
	u32 index = 0;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_IPT_MAX, nla, ipt_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_IPT_INDEX] != शून्य)
		index = nla_get_u32(tb[TCA_IPT_INDEX]);

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (tb[TCA_IPT_HOOK] == शून्य || tb[TCA_IPT_TARG] == शून्य) अणु
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण

	td = (काष्ठा xt_entry_target *)nla_data(tb[TCA_IPT_TARG]);
	अगर (nla_len(tb[TCA_IPT_TARG]) != td->u.target_size) अणु
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a, ops, bind,
				     false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अणु
		अगर (bind)/* करोnt override शेषs */
			वापस 0;

		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	hook = nla_get_u32(tb[TCA_IPT_HOOK]);

	err = -ENOMEM;
	tname = kदो_स्मृति(IFNAMSIZ, GFP_KERNEL);
	अगर (unlikely(!tname))
		जाओ err1;
	अगर (tb[TCA_IPT_TABLE] == शून्य ||
	    nla_strscpy(tname, tb[TCA_IPT_TABLE], IFNAMSIZ) >= IFNAMSIZ)
		म_नकल(tname, "mangle");

	t = kmemdup(td, td->u.target_size, GFP_KERNEL);
	अगर (unlikely(!t))
		जाओ err2;

	err = ipt_init_target(net, t, tname, hook);
	अगर (err < 0)
		जाओ err3;

	ipt = to_ipt(*a);

	spin_lock_bh(&ipt->tcf_lock);
	अगर (ret != ACT_P_CREATED) अणु
		ipt_destroy_target(ipt->tcfi_t, net);
		kमुक्त(ipt->tcfi_tname);
		kमुक्त(ipt->tcfi_t);
	पूर्ण
	ipt->tcfi_tname = tname;
	ipt->tcfi_t     = t;
	ipt->tcfi_hook  = hook;
	spin_unlock_bh(&ipt->tcf_lock);
	वापस ret;

err3:
	kमुक्त(t);
err2:
	kमुक्त(tname);
err1:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_ipt_init(काष्ठा net *net, काष्ठा nlattr *nla,
			काष्ठा nlattr *est, काष्ठा tc_action **a, पूर्णांक ovr,
			पूर्णांक bind, bool rtnl_held, काष्ठा tcf_proto *tp,
			u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	वापस __tcf_ipt_init(net, ipt_net_id, nla, est, a, &act_ipt_ops, ovr,
			      bind, tp, flags);
पूर्ण

अटल पूर्णांक tcf_xt_init(काष्ठा net *net, काष्ठा nlattr *nla,
		       काष्ठा nlattr *est, काष्ठा tc_action **a, पूर्णांक ovr,
		       पूर्णांक bind, bool unlocked, काष्ठा tcf_proto *tp,
		       u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	वापस __tcf_ipt_init(net, xt_net_id, nla, est, a, &act_xt_ops, ovr,
			      bind, tp, flags);
पूर्ण

अटल पूर्णांक tcf_ipt_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
		       काष्ठा tcf_result *res)
अणु
	पूर्णांक ret = 0, result = 0;
	काष्ठा tcf_ipt *ipt = to_ipt(a);
	काष्ठा xt_action_param par;
	काष्ठा nf_hook_state state = अणु
		.net	= dev_net(skb->dev),
		.in	= skb->dev,
		.hook	= ipt->tcfi_hook,
		.pf	= NFPROTO_IPV4,
	पूर्ण;

	अगर (skb_unclone(skb, GFP_ATOMIC))
		वापस TC_ACT_UNSPEC;

	spin_lock(&ipt->tcf_lock);

	tcf_lastuse_update(&ipt->tcf_पंचांग);
	bstats_update(&ipt->tcf_bstats, skb);

	/* yes, we have to worry about both in and out dev
	 * worry later - danger - this API seems to have changed
	 * from earlier kernels
	 */
	par.state    = &state;
	par.target   = ipt->tcfi_t->u.kernel.target;
	par.targinfo = ipt->tcfi_t->data;
	ret = par.target->target(skb, &par);

	चयन (ret) अणु
	हाल NF_ACCEPT:
		result = TC_ACT_OK;
		अवरोध;
	हाल NF_DROP:
		result = TC_ACT_SHOT;
		ipt->tcf_qstats.drops++;
		अवरोध;
	हाल XT_CONTINUE:
		result = TC_ACT_PIPE;
		अवरोध;
	शेष:
		net_notice_ratelimited("tc filter: Bogus netfilter code %d assume ACCEPT\n",
				       ret);
		result = TC_ACT_OK;
		अवरोध;
	पूर्ण
	spin_unlock(&ipt->tcf_lock);
	वापस result;

पूर्ण

अटल पूर्णांक tcf_ipt_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind,
			पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_ipt *ipt = to_ipt(a);
	काष्ठा xt_entry_target *t;
	काष्ठा tcf_t पंचांग;
	काष्ठा tc_cnt c;

	/* क्रम simple tarमाला_लो kernel size == user size
	 * user name = target name
	 * क्रम foolproof you need to not assume this
	 */

	spin_lock_bh(&ipt->tcf_lock);
	t = kmemdup(ipt->tcfi_t, ipt->tcfi_t->u.user.target_size, GFP_ATOMIC);
	अगर (unlikely(!t))
		जाओ nla_put_failure;

	c.bindcnt = atomic_पढ़ो(&ipt->tcf_bindcnt) - bind;
	c.refcnt = refcount_पढ़ो(&ipt->tcf_refcnt) - ref;
	म_नकल(t->u.user.name, ipt->tcfi_t->u.kernel.target->name);

	अगर (nla_put(skb, TCA_IPT_TARG, ipt->tcfi_t->u.user.target_size, t) ||
	    nla_put_u32(skb, TCA_IPT_INDEX, ipt->tcf_index) ||
	    nla_put_u32(skb, TCA_IPT_HOOK, ipt->tcfi_hook) ||
	    nla_put(skb, TCA_IPT_CNT, माप(काष्ठा tc_cnt), &c) ||
	    nla_put_string(skb, TCA_IPT_TABLE, ipt->tcfi_tname))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&पंचांग, &ipt->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_IPT_TM, माप(पंचांग), &पंचांग, TCA_IPT_PAD))
		जाओ nla_put_failure;

	spin_unlock_bh(&ipt->tcf_lock);
	kमुक्त(t);
	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&ipt->tcf_lock);
	nlmsg_trim(skb, b);
	kमुक्त(t);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_ipt_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			  काष्ठा netlink_callback *cb, पूर्णांक type,
			  स्थिर काष्ठा tc_action_ops *ops,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ipt_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_ipt_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ipt_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_ipt_ops = अणु
	.kind		=	"ipt",
	.id		=	TCA_ID_IPT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_ipt_act,
	.dump		=	tcf_ipt_dump,
	.cleanup	=	tcf_ipt_release,
	.init		=	tcf_ipt_init,
	.walk		=	tcf_ipt_walker,
	.lookup		=	tcf_ipt_search,
	.size		=	माप(काष्ठा tcf_ipt),
पूर्ण;

अटल __net_init पूर्णांक ipt_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ipt_net_id);

	वापस tc_action_net_init(net, tn, &act_ipt_ops);
पूर्ण

अटल व्योम __net_निकास ipt_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, ipt_net_id);
पूर्ण

अटल काष्ठा pernet_operations ipt_net_ops = अणु
	.init = ipt_init_net,
	.निकास_batch = ipt_निकास_net,
	.id   = &ipt_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक tcf_xt_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा netlink_callback *cb, पूर्णांक type,
			 स्थिर काष्ठा tc_action_ops *ops,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, xt_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_xt_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, xt_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_xt_ops = अणु
	.kind		=	"xt",
	.id		=	TCA_ID_XT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_ipt_act,
	.dump		=	tcf_ipt_dump,
	.cleanup	=	tcf_ipt_release,
	.init		=	tcf_xt_init,
	.walk		=	tcf_xt_walker,
	.lookup		=	tcf_xt_search,
	.size		=	माप(काष्ठा tcf_ipt),
पूर्ण;

अटल __net_init पूर्णांक xt_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, xt_net_id);

	वापस tc_action_net_init(net, tn, &act_xt_ops);
पूर्ण

अटल व्योम __net_निकास xt_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, xt_net_id);
पूर्ण

अटल काष्ठा pernet_operations xt_net_ops = अणु
	.init = xt_init_net,
	.निकास_batch = xt_निकास_net,
	.id   = &xt_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim(2002-13)");
MODULE_DESCRIPTION("Iptables target actions");
MODULE_LICENSE("GPL");
MODULE_ALIAS("act_xt");

अटल पूर्णांक __init ipt_init_module(व्योम)
अणु
	पूर्णांक ret1, ret2;

	ret1 = tcf_रेजिस्टर_action(&act_xt_ops, &xt_net_ops);
	अगर (ret1 < 0)
		pr_err("Failed to load xt action\n");

	ret2 = tcf_रेजिस्टर_action(&act_ipt_ops, &ipt_net_ops);
	अगर (ret2 < 0)
		pr_err("Failed to load ipt action\n");

	अगर (ret1 < 0 && ret2 < 0) अणु
		वापस ret1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल व्योम __निकास ipt_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_ipt_ops, &ipt_net_ops);
	tcf_unरेजिस्टर_action(&act_xt_ops, &xt_net_ops);
पूर्ण

module_init(ipt_init_module);
module_निकास(ipt_cleanup_module);
