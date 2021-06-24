<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_cgroup.c	Control Group Classअगरier
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sock.h>
#समावेश <net/cls_cgroup.h>

काष्ठा cls_cgroup_head अणु
	u32			handle;
	काष्ठा tcf_exts		exts;
	काष्ठा tcf_ematch_tree	ematches;
	काष्ठा tcf_proto	*tp;
	काष्ठा rcu_work		rwork;
पूर्ण;

अटल पूर्णांक cls_cgroup_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			       काष्ठा tcf_result *res)
अणु
	काष्ठा cls_cgroup_head *head = rcu_dereference_bh(tp->root);
	u32 classid = task_get_classid(skb);

	अगर (unlikely(!head))
		वापस -1;
	अगर (!classid)
		वापस -1;
	अगर (!tcf_em_tree_match(skb, &head->ematches, शून्य))
		वापस -1;

	res->classid = classid;
	res->class = 0;

	वापस tcf_exts_exec(skb, &head->exts, res);
पूर्ण

अटल व्योम *cls_cgroup_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक cls_cgroup_init(काष्ठा tcf_proto *tp)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy cgroup_policy[TCA_CGROUP_MAX + 1] = अणु
	[TCA_CGROUP_EMATCHES]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल व्योम __cls_cgroup_destroy(काष्ठा cls_cgroup_head *head)
अणु
	tcf_exts_destroy(&head->exts);
	tcf_em_tree_destroy(&head->ematches);
	tcf_exts_put_net(&head->exts);
	kमुक्त(head);
पूर्ण

अटल व्योम cls_cgroup_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cls_cgroup_head *head = container_of(to_rcu_work(work),
						    काष्ठा cls_cgroup_head,
						    rwork);
	rtnl_lock();
	__cls_cgroup_destroy(head);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक cls_cgroup_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
			     काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
			     u32 handle, काष्ठा nlattr **tca,
			     व्योम **arg, bool ovr, bool rtnl_held,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_CGROUP_MAX + 1];
	काष्ठा cls_cgroup_head *head = rtnl_dereference(tp->root);
	काष्ठा cls_cgroup_head *new;
	पूर्णांक err;

	अगर (!tca[TCA_OPTIONS])
		वापस -EINVAL;

	अगर (!head && !handle)
		वापस -EINVAL;

	अगर (head && handle != head->handle)
		वापस -ENOENT;

	new = kzalloc(माप(*head), GFP_KERNEL);
	अगर (!new)
		वापस -ENOBUFS;

	err = tcf_exts_init(&new->exts, net, TCA_CGROUP_ACT, TCA_CGROUP_POLICE);
	अगर (err < 0)
		जाओ errout;
	new->handle = handle;
	new->tp = tp;
	err = nla_parse_nested_deprecated(tb, TCA_CGROUP_MAX,
					  tca[TCA_OPTIONS], cgroup_policy,
					  शून्य);
	अगर (err < 0)
		जाओ errout;

	err = tcf_exts_validate(net, tp, tb, tca[TCA_RATE], &new->exts, ovr,
				true, extack);
	अगर (err < 0)
		जाओ errout;

	err = tcf_em_tree_validate(tp, tb[TCA_CGROUP_EMATCHES], &new->ematches);
	अगर (err < 0)
		जाओ errout;

	rcu_assign_poपूर्णांकer(tp->root, new);
	अगर (head) अणु
		tcf_exts_get_net(&head->exts);
		tcf_queue_work(&head->rwork, cls_cgroup_destroy_work);
	पूर्ण
	वापस 0;
errout:
	tcf_exts_destroy(&new->exts);
	kमुक्त(new);
	वापस err;
पूर्ण

अटल व्योम cls_cgroup_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_cgroup_head *head = rtnl_dereference(tp->root);

	/* Head can still be शून्य due to cls_cgroup_init(). */
	अगर (head) अणु
		अगर (tcf_exts_get_net(&head->exts))
			tcf_queue_work(&head->rwork, cls_cgroup_destroy_work);
		अन्यथा
			__cls_cgroup_destroy(head);
	पूर्ण
पूर्ण

अटल पूर्णांक cls_cgroup_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
			     bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम cls_cgroup_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
			    bool rtnl_held)
अणु
	काष्ठा cls_cgroup_head *head = rtnl_dereference(tp->root);

	अगर (arg->count < arg->skip)
		जाओ skip;

	अगर (!head)
		वापस;
	अगर (arg->fn(tp, head, arg) < 0) अणु
		arg->stop = 1;
		वापस;
	पूर्ण
skip:
	arg->count++;
पूर्ण

अटल पूर्णांक cls_cgroup_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
			   काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा cls_cgroup_head *head = rtnl_dereference(tp->root);
	काष्ठा nlattr *nest;

	t->tcm_handle = head->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &head->exts) < 0 ||
	    tcf_em_tree_dump(skb, &head->ematches, TCA_CGROUP_EMATCHES) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &head->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल काष्ठा tcf_proto_ops cls_cgroup_ops __पढ़ो_mostly = अणु
	.kind		=	"cgroup",
	.init		=	cls_cgroup_init,
	.change		=	cls_cgroup_change,
	.classअगरy	=	cls_cgroup_classअगरy,
	.destroy	=	cls_cgroup_destroy,
	.get		=	cls_cgroup_get,
	.delete		=	cls_cgroup_delete,
	.walk		=	cls_cgroup_walk,
	.dump		=	cls_cgroup_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_cgroup_cls(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_cgroup_ops);
पूर्ण

अटल व्योम __निकास निकास_cgroup_cls(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_cgroup_ops);
पूर्ण

module_init(init_cgroup_cls);
module_निकास(निकास_cgroup_cls);
MODULE_LICENSE("GPL");
