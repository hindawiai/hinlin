<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_simple.c	Simple example of an action
 *
 * Authors:	Jamal Hadi Salim (2005-8)
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_defact.h>
#समावेश <net/tc_act/tc_defact.h>

अटल अचिन्हित पूर्णांक simp_net_id;
अटल काष्ठा tc_action_ops act_simp_ops;

#घोषणा SIMP_MAX_DATA	32
अटल पूर्णांक tcf_simp_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_defact *d = to_defact(a);

	spin_lock(&d->tcf_lock);
	tcf_lastuse_update(&d->tcf_पंचांग);
	bstats_update(&d->tcf_bstats, skb);

	/* prपूर्णांक policy string followed by _ then packet count
	 * Example अगर this was the 3rd packet and the string was "hello"
	 * then it would look like "hello_3" (without quotes)
	 */
	pr_info("simple: %s_%llu\n",
	       (अक्षर *)d->tcfd_defdata, d->tcf_bstats.packets);
	spin_unlock(&d->tcf_lock);
	वापस d->tcf_action;
पूर्ण

अटल व्योम tcf_simp_release(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_defact *d = to_defact(a);
	kमुक्त(d->tcfd_defdata);
पूर्ण

अटल पूर्णांक alloc_defdata(काष्ठा tcf_defact *d, स्थिर काष्ठा nlattr *defdata)
अणु
	d->tcfd_defdata = kzalloc(SIMP_MAX_DATA, GFP_KERNEL);
	अगर (unlikely(!d->tcfd_defdata))
		वापस -ENOMEM;
	nla_strscpy(d->tcfd_defdata, defdata, SIMP_MAX_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक reset_policy(काष्ठा tc_action *a, स्थिर काष्ठा nlattr *defdata,
			काष्ठा tc_defact *p, काष्ठा tcf_proto *tp,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_defact *d;
	पूर्णांक err;

	err = tcf_action_check_ctrlact(p->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		वापस err;
	d = to_defact(a);
	spin_lock_bh(&d->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(a, p->action, जाओ_ch);
	स_रखो(d->tcfd_defdata, 0, SIMP_MAX_DATA);
	nla_strscpy(d->tcfd_defdata, defdata, SIMP_MAX_DATA);
	spin_unlock_bh(&d->tcf_lock);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy simple_policy[TCA_DEF_MAX + 1] = अणु
	[TCA_DEF_PARMS]	= अणु .len = माप(काष्ठा tc_defact) पूर्ण,
	[TCA_DEF_DATA]	= अणु .type = NLA_STRING, .len = SIMP_MAX_DATA पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_simp_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a,
			 पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			 काष्ठा tcf_proto *tp, u32 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, simp_net_id);
	काष्ठा nlattr *tb[TCA_DEF_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_defact *parm;
	काष्ठा tcf_defact *d;
	bool exists = false;
	पूर्णांक ret = 0, err;
	u32 index;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_DEF_MAX, nla, simple_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_DEF_PARMS] == शून्य)
		वापस -EINVAL;

	parm = nla_data(tb[TCA_DEF_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	अगर (tb[TCA_DEF_DATA] == शून्य) अणु
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		वापस -EINVAL;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_simp_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		d = to_defact(*a);
		err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch,
					       extack);
		अगर (err < 0)
			जाओ release_idr;

		err = alloc_defdata(d, tb[TCA_DEF_DATA]);
		अगर (err < 0)
			जाओ put_chain;

		tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अणु
		अगर (!ovr) अणु
			err = -EEXIST;
			जाओ release_idr;
		पूर्ण

		err = reset_policy(*a, tb[TCA_DEF_DATA], parm, tp, extack);
		अगर (err)
			जाओ release_idr;
	पूर्ण

	वापस ret;
put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_simp_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			 पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_defact *d = to_defact(a);
	काष्ठा tc_defact opt = अणु
		.index   = d->tcf_index,
		.refcnt  = refcount_पढ़ो(&d->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&d->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&d->tcf_lock);
	opt.action = d->tcf_action;
	अगर (nla_put(skb, TCA_DEF_PARMS, माप(opt), &opt) ||
	    nla_put_string(skb, TCA_DEF_DATA, d->tcfd_defdata))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &d->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_DEF_TM, माप(t), &t, TCA_DEF_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&d->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&d->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_simp_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, simp_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_simp_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, simp_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_simp_ops = अणु
	.kind		=	"simple",
	.id		=	TCA_ID_SIMP,
	.owner		=	THIS_MODULE,
	.act		=	tcf_simp_act,
	.dump		=	tcf_simp_dump,
	.cleanup	=	tcf_simp_release,
	.init		=	tcf_simp_init,
	.walk		=	tcf_simp_walker,
	.lookup		=	tcf_simp_search,
	.size		=	माप(काष्ठा tcf_defact),
पूर्ण;

अटल __net_init पूर्णांक simp_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, simp_net_id);

	वापस tc_action_net_init(net, tn, &act_simp_ops);
पूर्ण

अटल व्योम __net_निकास simp_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, simp_net_id);
पूर्ण

अटल काष्ठा pernet_operations simp_net_ops = अणु
	.init = simp_init_net,
	.निकास_batch = simp_निकास_net,
	.id   = &simp_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim(2005)");
MODULE_DESCRIPTION("Simple example action");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init simp_init_module(व्योम)
अणु
	पूर्णांक ret = tcf_रेजिस्टर_action(&act_simp_ops, &simp_net_ops);
	अगर (!ret)
		pr_info("Simple TC action Loaded\n");
	वापस ret;
पूर्ण

अटल व्योम __निकास simp_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_simp_ops, &simp_net_ops);
पूर्ण

module_init(simp_init_module);
module_निकास(simp_cleanup_module);
