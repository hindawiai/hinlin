<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_basic.c	Basic Packet Classअगरier.
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/idr.h>
#समावेश <linux/percpu.h>
#समावेश <net/netlink.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>

काष्ठा basic_head अणु
	काष्ठा list_head	flist;
	काष्ठा idr		handle_idr;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा basic_filter अणु
	u32			handle;
	काष्ठा tcf_exts		exts;
	काष्ठा tcf_ematch_tree	ematches;
	काष्ठा tcf_result	res;
	काष्ठा tcf_proto	*tp;
	काष्ठा list_head	link;
	काष्ठा tc_basic_pcnt __percpu *pf;
	काष्ठा rcu_work		rwork;
पूर्ण;

अटल पूर्णांक basic_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			  काष्ठा tcf_result *res)
अणु
	पूर्णांक r;
	काष्ठा basic_head *head = rcu_dereference_bh(tp->root);
	काष्ठा basic_filter *f;

	list_क्रम_each_entry_rcu(f, &head->flist, link) अणु
		__this_cpu_inc(f->pf->rcnt);
		अगर (!tcf_em_tree_match(skb, &f->ematches, शून्य))
			जारी;
		__this_cpu_inc(f->pf->rhit);
		*res = f->res;
		r = tcf_exts_exec(skb, &f->exts, res);
		अगर (r < 0)
			जारी;
		वापस r;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम *basic_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा basic_head *head = rtnl_dereference(tp->root);
	काष्ठा basic_filter *f;

	list_क्रम_each_entry(f, &head->flist, link) अणु
		अगर (f->handle == handle) अणु
			वापस f;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक basic_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा basic_head *head;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (head == शून्य)
		वापस -ENOBUFS;
	INIT_LIST_HEAD(&head->flist);
	idr_init(&head->handle_idr);
	rcu_assign_poपूर्णांकer(tp->root, head);
	वापस 0;
पूर्ण

अटल व्योम __basic_delete_filter(काष्ठा basic_filter *f)
अणु
	tcf_exts_destroy(&f->exts);
	tcf_em_tree_destroy(&f->ematches);
	tcf_exts_put_net(&f->exts);
	मुक्त_percpu(f->pf);
	kमुक्त(f);
पूर्ण

अटल व्योम basic_delete_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा basic_filter *f = container_of(to_rcu_work(work),
					      काष्ठा basic_filter,
					      rwork);
	rtnl_lock();
	__basic_delete_filter(f);
	rtnl_unlock();
पूर्ण

अटल व्योम basic_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा basic_head *head = rtnl_dereference(tp->root);
	काष्ठा basic_filter *f, *n;

	list_क्रम_each_entry_safe(f, n, &head->flist, link) अणु
		list_del_rcu(&f->link);
		tcf_unbind_filter(tp, &f->res);
		idr_हटाओ(&head->handle_idr, f->handle);
		अगर (tcf_exts_get_net(&f->exts))
			tcf_queue_work(&f->rwork, basic_delete_filter_work);
		अन्यथा
			__basic_delete_filter(f);
	पूर्ण
	idr_destroy(&head->handle_idr);
	kमुक्त_rcu(head, rcu);
पूर्ण

अटल पूर्णांक basic_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
			bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा basic_head *head = rtnl_dereference(tp->root);
	काष्ठा basic_filter *f = arg;

	list_del_rcu(&f->link);
	tcf_unbind_filter(tp, &f->res);
	idr_हटाओ(&head->handle_idr, f->handle);
	tcf_exts_get_net(&f->exts);
	tcf_queue_work(&f->rwork, basic_delete_filter_work);
	*last = list_empty(&head->flist);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy basic_policy[TCA_BASIC_MAX + 1] = अणु
	[TCA_BASIC_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_BASIC_EMATCHES]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक basic_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			   काष्ठा basic_filter *f, अचिन्हित दीर्घ base,
			   काष्ठा nlattr **tb,
			   काष्ठा nlattr *est, bool ovr,
			   काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, est, &f->exts, ovr, true, extack);
	अगर (err < 0)
		वापस err;

	err = tcf_em_tree_validate(tp, tb[TCA_BASIC_EMATCHES], &f->ematches);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_BASIC_CLASSID]) अणु
		f->res.classid = nla_get_u32(tb[TCA_BASIC_CLASSID]);
		tcf_bind_filter(tp, &f->res, base);
	पूर्ण

	f->tp = tp;
	वापस 0;
पूर्ण

अटल पूर्णांक basic_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
			काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base, u32 handle,
			काष्ठा nlattr **tca, व्योम **arg, bool ovr,
			bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा basic_head *head = rtnl_dereference(tp->root);
	काष्ठा nlattr *tb[TCA_BASIC_MAX + 1];
	काष्ठा basic_filter *fold = (काष्ठा basic_filter *) *arg;
	काष्ठा basic_filter *fnew;

	अगर (tca[TCA_OPTIONS] == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_BASIC_MAX, tca[TCA_OPTIONS],
					  basic_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (fold != शून्य) अणु
		अगर (handle && fold->handle != handle)
			वापस -EINVAL;
	पूर्ण

	fnew = kzalloc(माप(*fnew), GFP_KERNEL);
	अगर (!fnew)
		वापस -ENOBUFS;

	err = tcf_exts_init(&fnew->exts, net, TCA_BASIC_ACT, TCA_BASIC_POLICE);
	अगर (err < 0)
		जाओ errout;

	अगर (!handle) अणु
		handle = 1;
		err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
				    पूर्णांक_उच्च, GFP_KERNEL);
	पूर्ण अन्यथा अगर (!fold) अणु
		err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
				    handle, GFP_KERNEL);
	पूर्ण
	अगर (err)
		जाओ errout;
	fnew->handle = handle;
	fnew->pf = alloc_percpu(काष्ठा tc_basic_pcnt);
	अगर (!fnew->pf) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	err = basic_set_parms(net, tp, fnew, base, tb, tca[TCA_RATE], ovr,
			      extack);
	अगर (err < 0) अणु
		अगर (!fold)
			idr_हटाओ(&head->handle_idr, fnew->handle);
		जाओ errout;
	पूर्ण

	*arg = fnew;

	अगर (fold) अणु
		idr_replace(&head->handle_idr, fnew, fnew->handle);
		list_replace_rcu(&fold->link, &fnew->link);
		tcf_unbind_filter(tp, &fold->res);
		tcf_exts_get_net(&fold->exts);
		tcf_queue_work(&fold->rwork, basic_delete_filter_work);
	पूर्ण अन्यथा अणु
		list_add_rcu(&fnew->link, &head->flist);
	पूर्ण

	वापस 0;
errout:
	मुक्त_percpu(fnew->pf);
	tcf_exts_destroy(&fnew->exts);
	kमुक्त(fnew);
	वापस err;
पूर्ण

अटल व्योम basic_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		       bool rtnl_held)
अणु
	काष्ठा basic_head *head = rtnl_dereference(tp->root);
	काष्ठा basic_filter *f;

	list_क्रम_each_entry(f, &head->flist, link) अणु
		अगर (arg->count < arg->skip)
			जाओ skip;

		अगर (arg->fn(tp, f, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
skip:
		arg->count++;
	पूर्ण
पूर्ण

अटल व्योम basic_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			     अचिन्हित दीर्घ base)
अणु
	काष्ठा basic_filter *f = fh;

	अगर (f && f->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &f->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &f->res);
	पूर्ण
पूर्ण

अटल पूर्णांक basic_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		      काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा tc_basic_pcnt gpf = अणुपूर्ण;
	काष्ठा basic_filter *f = fh;
	काष्ठा nlattr *nest;
	पूर्णांक cpu;

	अगर (f == शून्य)
		वापस skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (f->res.classid &&
	    nla_put_u32(skb, TCA_BASIC_CLASSID, f->res.classid))
		जाओ nla_put_failure;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा tc_basic_pcnt *pf = per_cpu_ptr(f->pf, cpu);

		gpf.rcnt += pf->rcnt;
		gpf.rhit += pf->rhit;
	पूर्ण

	अगर (nla_put_64bit(skb, TCA_BASIC_PCNT,
			  माप(काष्ठा tc_basic_pcnt),
			  &gpf, TCA_BASIC_PAD))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts) < 0 ||
	    tcf_em_tree_dump(skb, &f->ematches, TCA_BASIC_EMATCHES) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल काष्ठा tcf_proto_ops cls_basic_ops __पढ़ो_mostly = अणु
	.kind		=	"basic",
	.classअगरy	=	basic_classअगरy,
	.init		=	basic_init,
	.destroy	=	basic_destroy,
	.get		=	basic_get,
	.change		=	basic_change,
	.delete		=	basic_delete,
	.walk		=	basic_walk,
	.dump		=	basic_dump,
	.bind_class	=	basic_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_basic(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_basic_ops);
पूर्ण

अटल व्योम __निकास निकास_basic(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_basic_ops);
पूर्ण

module_init(init_basic)
module_निकास(निकास_basic)
MODULE_LICENSE("GPL");
