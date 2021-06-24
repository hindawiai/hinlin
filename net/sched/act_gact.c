<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_gact.c		Generic actions
 *
 * copyright 	Jamal Hadi Salim (2002-4)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_gact.h>

अटल अचिन्हित पूर्णांक gact_net_id;
अटल काष्ठा tc_action_ops act_gact_ops;

#अगर_घोषित CONFIG_GACT_PROB
अटल पूर्णांक gact_net_अक्रम(काष्ठा tcf_gact *gact)
अणु
	smp_rmb(); /* coupled with smp_wmb() in tcf_gact_init() */
	अगर (pअक्रमom_u32() % gact->tcfg_pval)
		वापस gact->tcf_action;
	वापस gact->tcfg_paction;
पूर्ण

अटल पूर्णांक gact_determ(काष्ठा tcf_gact *gact)
अणु
	u32 pack = atomic_inc_वापस(&gact->packets);

	smp_rmb(); /* coupled with smp_wmb() in tcf_gact_init() */
	अगर (pack % gact->tcfg_pval)
		वापस gact->tcf_action;
	वापस gact->tcfg_paction;
पूर्ण

प्रकार पूर्णांक (*g_अक्रम)(काष्ठा tcf_gact *gact);
अटल g_अक्रम gact_अक्रम[MAX_RAND] = अणु शून्य, gact_net_अक्रम, gact_determ पूर्ण;
#पूर्ण_अगर /* CONFIG_GACT_PROB */

अटल स्थिर काष्ठा nla_policy gact_policy[TCA_GACT_MAX + 1] = अणु
	[TCA_GACT_PARMS]	= अणु .len = माप(काष्ठा tc_gact) पूर्ण,
	[TCA_GACT_PROB]		= अणु .len = माप(काष्ठा tc_gact_p) पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_gact_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a,
			 पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			 काष्ठा tcf_proto *tp, u32 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gact_net_id);
	काष्ठा nlattr *tb[TCA_GACT_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_gact *parm;
	काष्ठा tcf_gact *gact;
	पूर्णांक ret = 0;
	u32 index;
	पूर्णांक err;
#अगर_घोषित CONFIG_GACT_PROB
	काष्ठा tc_gact_p *p_parm = शून्य;
#पूर्ण_अगर

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_GACT_MAX, nla, gact_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_GACT_PARMS] == शून्य)
		वापस -EINVAL;
	parm = nla_data(tb[TCA_GACT_PARMS]);
	index = parm->index;

#अगर_अघोषित CONFIG_GACT_PROB
	अगर (tb[TCA_GACT_PROB] != शून्य)
		वापस -EOPNOTSUPP;
#अन्यथा
	अगर (tb[TCA_GACT_PROB]) अणु
		p_parm = nla_data(tb[TCA_GACT_PROB]);
		अगर (p_parm->ptype >= MAX_RAND)
			वापस -EINVAL;
		अगर (TC_ACT_EXT_CMP(p_parm->paction, TC_ACT_GOTO_CHAIN)) अणु
			NL_SET_ERR_MSG(extack,
				       "goto chain not allowed on fallback");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!err) अणु
		ret = tcf_idr_create_from_flags(tn, index, est, a,
						&act_gact_ops, bind, flags);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (err > 0) अणु
		अगर (bind)/* करोnt override शेषs */
			वापस 0;
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस err;
	पूर्ण

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;
	gact = to_gact(*a);

	spin_lock_bh(&gact->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
#अगर_घोषित CONFIG_GACT_PROB
	अगर (p_parm) अणु
		gact->tcfg_paction = p_parm->paction;
		gact->tcfg_pval    = max_t(u16, 1, p_parm->pval);
		/* Make sure tcfg_pval is written beक्रमe tcfg_ptype
		 * coupled with smp_rmb() in gact_net_अक्रम() & gact_determ()
		 */
		smp_wmb();
		gact->tcfg_ptype   = p_parm->ptype;
	पूर्ण
#पूर्ण_अगर
	spin_unlock_bh(&gact->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	वापस ret;
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_gact_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_gact *gact = to_gact(a);
	पूर्णांक action = READ_ONCE(gact->tcf_action);

#अगर_घोषित CONFIG_GACT_PROB
	अणु
	u32 ptype = READ_ONCE(gact->tcfg_ptype);

	अगर (ptype)
		action = gact_अक्रम[ptype](gact);
	पूर्ण
#पूर्ण_अगर
	tcf_action_update_bstats(&gact->common, skb);
	अगर (action == TC_ACT_SHOT)
		tcf_action_inc_drop_qstats(&gact->common);

	tcf_lastuse_update(&gact->tcf_पंचांग);

	वापस action;
पूर्ण

अटल व्योम tcf_gact_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
				  u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_gact *gact = to_gact(a);
	पूर्णांक action = READ_ONCE(gact->tcf_action);
	काष्ठा tcf_t *पंचांग = &gact->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets,
				action == TC_ACT_SHOT ? packets : drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_gact_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			 पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_gact *gact = to_gact(a);
	काष्ठा tc_gact opt = अणु
		.index   = gact->tcf_index,
		.refcnt  = refcount_पढ़ो(&gact->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&gact->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&gact->tcf_lock);
	opt.action = gact->tcf_action;
	अगर (nla_put(skb, TCA_GACT_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_GACT_PROB
	अगर (gact->tcfg_ptype) अणु
		काष्ठा tc_gact_p p_opt = अणु
			.paction = gact->tcfg_paction,
			.pval    = gact->tcfg_pval,
			.ptype   = gact->tcfg_ptype,
		पूर्ण;

		अगर (nla_put(skb, TCA_GACT_PROB, माप(p_opt), &p_opt))
			जाओ nla_put_failure;
	पूर्ण
#पूर्ण_अगर
	tcf_पंचांग_dump(&t, &gact->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_GACT_TM, माप(t), &t, TCA_GACT_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&gact->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&gact->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_gact_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gact_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_gact_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gact_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल माप_प्रकार tcf_gact_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	माप_प्रकार sz = nla_total_size(माप(काष्ठा tc_gact)); /* TCA_GACT_PARMS */

#अगर_घोषित CONFIG_GACT_PROB
	अगर (to_gact(act)->tcfg_ptype)
		/* TCA_GACT_PROB */
		sz += nla_total_size(माप(काष्ठा tc_gact_p));
#पूर्ण_अगर

	वापस sz;
पूर्ण

अटल काष्ठा tc_action_ops act_gact_ops = अणु
	.kind		=	"gact",
	.id		=	TCA_ID_GACT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_gact_act,
	.stats_update	=	tcf_gact_stats_update,
	.dump		=	tcf_gact_dump,
	.init		=	tcf_gact_init,
	.walk		=	tcf_gact_walker,
	.lookup		=	tcf_gact_search,
	.get_fill_size	=	tcf_gact_get_fill_size,
	.size		=	माप(काष्ठा tcf_gact),
पूर्ण;

अटल __net_init पूर्णांक gact_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gact_net_id);

	वापस tc_action_net_init(net, tn, &act_gact_ops);
पूर्ण

अटल व्योम __net_निकास gact_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, gact_net_id);
पूर्ण

अटल काष्ठा pernet_operations gact_net_ops = अणु
	.init = gact_init_net,
	.निकास_batch = gact_निकास_net,
	.id   = &gact_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim(2002-4)");
MODULE_DESCRIPTION("Generic Classifier actions");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init gact_init_module(व्योम)
अणु
#अगर_घोषित CONFIG_GACT_PROB
	pr_info("GACT probability on\n");
#अन्यथा
	pr_info("GACT probability NOT on\n");
#पूर्ण_अगर

	वापस tcf_रेजिस्टर_action(&act_gact_ops, &gact_net_ops);
पूर्ण

अटल व्योम __निकास gact_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_gact_ops, &gact_net_ops);
पूर्ण

module_init(gact_init_module);
module_निकास(gact_cleanup_module);
