<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_matchll.c		Match-all classअगरier
 *
 * Copyright (c) 2016 Jiri Pirko <jiri@mellanox.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>

#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>

काष्ठा cls_mall_head अणु
	काष्ठा tcf_exts exts;
	काष्ठा tcf_result res;
	u32 handle;
	u32 flags;
	अचिन्हित पूर्णांक in_hw_count;
	काष्ठा tc_matchall_pcnt __percpu *pf;
	काष्ठा rcu_work rwork;
	bool deleting;
पूर्ण;

अटल पूर्णांक mall_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			 काष्ठा tcf_result *res)
अणु
	काष्ठा cls_mall_head *head = rcu_dereference_bh(tp->root);

	अगर (unlikely(!head))
		वापस -1;

	अगर (tc_skip_sw(head->flags))
		वापस -1;

	*res = head->res;
	__this_cpu_inc(head->pf->rhit);
	वापस tcf_exts_exec(skb, &head->exts, res);
पूर्ण

अटल पूर्णांक mall_init(काष्ठा tcf_proto *tp)
अणु
	वापस 0;
पूर्ण

अटल व्योम __mall_destroy(काष्ठा cls_mall_head *head)
अणु
	tcf_exts_destroy(&head->exts);
	tcf_exts_put_net(&head->exts);
	मुक्त_percpu(head->pf);
	kमुक्त(head);
पूर्ण

अटल व्योम mall_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cls_mall_head *head = container_of(to_rcu_work(work),
						  काष्ठा cls_mall_head,
						  rwork);
	rtnl_lock();
	__mall_destroy(head);
	rtnl_unlock();
पूर्ण

अटल व्योम mall_destroy_hw_filter(काष्ठा tcf_proto *tp,
				   काष्ठा cls_mall_head *head,
				   अचिन्हित दीर्घ cookie,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_cls_matchall_offload cls_mall = अणुपूर्ण;
	काष्ठा tcf_block *block = tp->chain->block;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, extack);
	cls_mall.command = TC_CLSMATCHALL_DESTROY;
	cls_mall.cookie = cookie;

	tc_setup_cb_destroy(block, tp, TC_SETUP_CLSMATCHALL, &cls_mall, false,
			    &head->flags, &head->in_hw_count, true);
पूर्ण

अटल पूर्णांक mall_replace_hw_filter(काष्ठा tcf_proto *tp,
				  काष्ठा cls_mall_head *head,
				  अचिन्हित दीर्घ cookie,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_cls_matchall_offload cls_mall = अणुपूर्ण;
	काष्ठा tcf_block *block = tp->chain->block;
	bool skip_sw = tc_skip_sw(head->flags);
	पूर्णांक err;

	cls_mall.rule =	flow_rule_alloc(tcf_exts_num_actions(&head->exts));
	अगर (!cls_mall.rule)
		वापस -ENOMEM;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, extack);
	cls_mall.command = TC_CLSMATCHALL_REPLACE;
	cls_mall.cookie = cookie;

	err = tc_setup_flow_action(&cls_mall.rule->action, &head->exts);
	अगर (err) अणु
		kमुक्त(cls_mall.rule);
		mall_destroy_hw_filter(tp, head, cookie, शून्य);
		अगर (skip_sw)
			NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
		अन्यथा
			err = 0;

		वापस err;
	पूर्ण

	err = tc_setup_cb_add(block, tp, TC_SETUP_CLSMATCHALL, &cls_mall,
			      skip_sw, &head->flags, &head->in_hw_count, true);
	tc_cleanup_flow_action(&cls_mall.rule->action);
	kमुक्त(cls_mall.rule);

	अगर (err) अणु
		mall_destroy_hw_filter(tp, head, cookie, शून्य);
		वापस err;
	पूर्ण

	अगर (skip_sw && !(head->flags & TCA_CLS_FLAGS_IN_HW))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम mall_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);

	अगर (!head)
		वापस;

	tcf_unbind_filter(tp, &head->res);

	अगर (!tc_skip_hw(head->flags))
		mall_destroy_hw_filter(tp, head, (अचिन्हित दीर्घ) head, extack);

	अगर (tcf_exts_get_net(&head->exts))
		tcf_queue_work(&head->rwork, mall_destroy_work);
	अन्यथा
		__mall_destroy(head);
पूर्ण

अटल व्योम *mall_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);

	अगर (head && head->handle == handle)
		वापस head;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nla_policy mall_policy[TCA_MATCHALL_MAX + 1] = अणु
	[TCA_MATCHALL_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TCA_MATCHALL_CLASSID]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_MATCHALL_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक mall_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			  काष्ठा cls_mall_head *head,
			  अचिन्हित दीर्घ base, काष्ठा nlattr **tb,
			  काष्ठा nlattr *est, bool ovr,
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, est, &head->exts, ovr, true,
				extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_MATCHALL_CLASSID]) अणु
		head->res.classid = nla_get_u32(tb[TCA_MATCHALL_CLASSID]);
		tcf_bind_filter(tp, &head->res, base);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mall_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		       काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		       u32 handle, काष्ठा nlattr **tca,
		       व्योम **arg, bool ovr, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);
	काष्ठा nlattr *tb[TCA_MATCHALL_MAX + 1];
	काष्ठा cls_mall_head *new;
	u32 flags = 0;
	पूर्णांक err;

	अगर (!tca[TCA_OPTIONS])
		वापस -EINVAL;

	अगर (head)
		वापस -EEXIST;

	err = nla_parse_nested_deprecated(tb, TCA_MATCHALL_MAX,
					  tca[TCA_OPTIONS], mall_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_MATCHALL_FLAGS]) अणु
		flags = nla_get_u32(tb[TCA_MATCHALL_FLAGS]);
		अगर (!tc_flags_valid(flags))
			वापस -EINVAL;
	पूर्ण

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस -ENOBUFS;

	err = tcf_exts_init(&new->exts, net, TCA_MATCHALL_ACT, 0);
	अगर (err)
		जाओ err_exts_init;

	अगर (!handle)
		handle = 1;
	new->handle = handle;
	new->flags = flags;
	new->pf = alloc_percpu(काष्ठा tc_matchall_pcnt);
	अगर (!new->pf) अणु
		err = -ENOMEM;
		जाओ err_alloc_percpu;
	पूर्ण

	err = mall_set_parms(net, tp, new, base, tb, tca[TCA_RATE], ovr,
			     extack);
	अगर (err)
		जाओ err_set_parms;

	अगर (!tc_skip_hw(new->flags)) अणु
		err = mall_replace_hw_filter(tp, new, (अचिन्हित दीर्घ)new,
					     extack);
		अगर (err)
			जाओ err_replace_hw_filter;
	पूर्ण

	अगर (!tc_in_hw(new->flags))
		new->flags |= TCA_CLS_FLAGS_NOT_IN_HW;

	*arg = head;
	rcu_assign_poपूर्णांकer(tp->root, new);
	वापस 0;

err_replace_hw_filter:
err_set_parms:
	मुक्त_percpu(new->pf);
err_alloc_percpu:
	tcf_exts_destroy(&new->exts);
err_exts_init:
	kमुक्त(new);
	वापस err;
पूर्ण

अटल पूर्णांक mall_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		       bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);

	head->deleting = true;
	*last = true;
	वापस 0;
पूर्ण

अटल व्योम mall_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		      bool rtnl_held)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);

	अगर (arg->count < arg->skip)
		जाओ skip;

	अगर (!head || head->deleting)
		वापस;
	अगर (arg->fn(tp, head, arg) < 0)
		arg->stop = 1;
skip:
	arg->count++;
पूर्ण

अटल पूर्णांक mall_reoffload(काष्ठा tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			  व्योम *cb_priv, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_mall_head *head = rtnl_dereference(tp->root);
	काष्ठा tc_cls_matchall_offload cls_mall = अणुपूर्ण;
	काष्ठा tcf_block *block = tp->chain->block;
	पूर्णांक err;

	अगर (tc_skip_hw(head->flags))
		वापस 0;

	cls_mall.rule =	flow_rule_alloc(tcf_exts_num_actions(&head->exts));
	अगर (!cls_mall.rule)
		वापस -ENOMEM;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, extack);
	cls_mall.command = add ?
		TC_CLSMATCHALL_REPLACE : TC_CLSMATCHALL_DESTROY;
	cls_mall.cookie = (अचिन्हित दीर्घ)head;

	err = tc_setup_flow_action(&cls_mall.rule->action, &head->exts);
	अगर (err) अणु
		kमुक्त(cls_mall.rule);
		अगर (add && tc_skip_sw(head->flags)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
			वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	err = tc_setup_cb_reoffload(block, tp, add, cb, TC_SETUP_CLSMATCHALL,
				    &cls_mall, cb_priv, &head->flags,
				    &head->in_hw_count);
	tc_cleanup_flow_action(&cls_mall.rule->action);
	kमुक्त(cls_mall.rule);

	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम mall_stats_hw_filter(काष्ठा tcf_proto *tp,
				 काष्ठा cls_mall_head *head,
				 अचिन्हित दीर्घ cookie)
अणु
	काष्ठा tc_cls_matchall_offload cls_mall = अणुपूर्ण;
	काष्ठा tcf_block *block = tp->chain->block;

	tc_cls_common_offload_init(&cls_mall.common, tp, head->flags, शून्य);
	cls_mall.command = TC_CLSMATCHALL_STATS;
	cls_mall.cookie = cookie;

	tc_setup_cb_call(block, TC_SETUP_CLSMATCHALL, &cls_mall, false, true);

	tcf_exts_stats_update(&head->exts, cls_mall.stats.bytes,
			      cls_mall.stats.pkts, cls_mall.stats.drops,
			      cls_mall.stats.lastused,
			      cls_mall.stats.used_hw_stats,
			      cls_mall.stats.used_hw_stats_valid);
पूर्ण

अटल पूर्णांक mall_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		     काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा tc_matchall_pcnt gpf = अणुपूर्ण;
	काष्ठा cls_mall_head *head = fh;
	काष्ठा nlattr *nest;
	पूर्णांक cpu;

	अगर (!head)
		वापस skb->len;

	अगर (!tc_skip_hw(head->flags))
		mall_stats_hw_filter(tp, head, (अचिन्हित दीर्घ)head);

	t->tcm_handle = head->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (head->res.classid &&
	    nla_put_u32(skb, TCA_MATCHALL_CLASSID, head->res.classid))
		जाओ nla_put_failure;

	अगर (head->flags && nla_put_u32(skb, TCA_MATCHALL_FLAGS, head->flags))
		जाओ nla_put_failure;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा tc_matchall_pcnt *pf = per_cpu_ptr(head->pf, cpu);

		gpf.rhit += pf->rhit;
	पूर्ण

	अगर (nla_put_64bit(skb, TCA_MATCHALL_PCNT,
			  माप(काष्ठा tc_matchall_pcnt),
			  &gpf, TCA_MATCHALL_PAD))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &head->exts))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &head->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम mall_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			    अचिन्हित दीर्घ base)
अणु
	काष्ठा cls_mall_head *head = fh;

	अगर (head && head->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &head->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &head->res);
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops cls_mall_ops __पढ़ो_mostly = अणु
	.kind		= "matchall",
	.classअगरy	= mall_classअगरy,
	.init		= mall_init,
	.destroy	= mall_destroy,
	.get		= mall_get,
	.change		= mall_change,
	.delete		= mall_delete,
	.walk		= mall_walk,
	.reoffload	= mall_reoffload,
	.dump		= mall_dump,
	.bind_class	= mall_bind_class,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init cls_mall_init(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_mall_ops);
पूर्ण

अटल व्योम __निकास cls_mall_निकास(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_mall_ops);
पूर्ण

module_init(cls_mall_init);
module_निकास(cls_mall_निकास);

MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Match-all classifier");
MODULE_LICENSE("GPL v2");
