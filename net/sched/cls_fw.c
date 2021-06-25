<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_fw.c	Classअगरier mapping ipchains' fwmark to traffic class.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Changes:
 * Karlis Peisenieks <karlis@mt.lv> : 990415 : fw_walk off by one
 * Karlis Peisenieks <karlis@mt.lv> : 990415 : fw_delete समाप्तed all the filter (and kernel).
 * Alex <alex@pilotsoft.com> : 2004xxyy: Added Action extension
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sch_generic.h>

#घोषणा HTSIZE 256

काष्ठा fw_head अणु
	u32			mask;
	काष्ठा fw_filter __rcu	*ht[HTSIZE];
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा fw_filter अणु
	काष्ठा fw_filter __rcu	*next;
	u32			id;
	काष्ठा tcf_result	res;
	पूर्णांक			अगरindex;
	काष्ठा tcf_exts		exts;
	काष्ठा tcf_proto	*tp;
	काष्ठा rcu_work		rwork;
पूर्ण;

अटल u32 fw_hash(u32 handle)
अणु
	handle ^= (handle >> 16);
	handle ^= (handle >> 8);
	वापस handle % HTSIZE;
पूर्ण

अटल पूर्णांक fw_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
		       काष्ठा tcf_result *res)
अणु
	काष्ठा fw_head *head = rcu_dereference_bh(tp->root);
	काष्ठा fw_filter *f;
	पूर्णांक r;
	u32 id = skb->mark;

	अगर (head != शून्य) अणु
		id &= head->mask;

		क्रम (f = rcu_dereference_bh(head->ht[fw_hash(id)]); f;
		     f = rcu_dereference_bh(f->next)) अणु
			अगर (f->id == id) अणु
				*res = f->res;
				अगर (!tcf_match_indev(skb, f->अगरindex))
					जारी;
				r = tcf_exts_exec(skb, &f->exts, res);
				अगर (r < 0)
					जारी;

				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा Qdisc *q = tcf_block_q(tp->chain->block);

		/* Old method: classअगरy the packet using its skb mark. */
		अगर (id && (TC_H_MAJ(id) == 0 ||
			   !(TC_H_MAJ(id ^ q->handle)))) अणु
			res->classid = id;
			res->class = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम *fw_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	काष्ठा fw_filter *f;

	अगर (head == शून्य)
		वापस शून्य;

	f = rtnl_dereference(head->ht[fw_hash(handle)]);
	क्रम (; f; f = rtnl_dereference(f->next)) अणु
		अगर (f->id == handle)
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक fw_init(काष्ठा tcf_proto *tp)
अणु
	/* We करोn't allocate fw_head here, because in the old method
	 * we करोn't need it at all.
	 */
	वापस 0;
पूर्ण

अटल व्योम __fw_delete_filter(काष्ठा fw_filter *f)
अणु
	tcf_exts_destroy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kमुक्त(f);
पूर्ण

अटल व्योम fw_delete_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_filter *f = container_of(to_rcu_work(work),
					   काष्ठा fw_filter,
					   rwork);
	rtnl_lock();
	__fw_delete_filter(f);
	rtnl_unlock();
पूर्ण

अटल व्योम fw_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	काष्ठा fw_filter *f;
	पूर्णांक h;

	अगर (head == शून्य)
		वापस;

	क्रम (h = 0; h < HTSIZE; h++) अणु
		जबतक ((f = rtnl_dereference(head->ht[h])) != शून्य) अणु
			RCU_INIT_POINTER(head->ht[h],
					 rtnl_dereference(f->next));
			tcf_unbind_filter(tp, &f->res);
			अगर (tcf_exts_get_net(&f->exts))
				tcf_queue_work(&f->rwork, fw_delete_filter_work);
			अन्यथा
				__fw_delete_filter(f);
		पूर्ण
	पूर्ण
	kमुक्त_rcu(head, rcu);
पूर्ण

अटल पूर्णांक fw_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		     bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	काष्ठा fw_filter *f = arg;
	काष्ठा fw_filter __rcu **fp;
	काष्ठा fw_filter *pfp;
	पूर्णांक ret = -EINVAL;
	पूर्णांक h;

	अगर (head == शून्य || f == शून्य)
		जाओ out;

	fp = &head->ht[fw_hash(f->id)];

	क्रम (pfp = rtnl_dereference(*fp); pfp;
	     fp = &pfp->next, pfp = rtnl_dereference(*fp)) अणु
		अगर (pfp == f) अणु
			RCU_INIT_POINTER(*fp, rtnl_dereference(f->next));
			tcf_unbind_filter(tp, &f->res);
			tcf_exts_get_net(&f->exts);
			tcf_queue_work(&f->rwork, fw_delete_filter_work);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	*last = true;
	क्रम (h = 0; h < HTSIZE; h++) अणु
		अगर (rcu_access_poपूर्णांकer(head->ht[h])) अणु
			*last = false;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy fw_policy[TCA_FW_MAX + 1] = अणु
	[TCA_FW_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FW_INDEV]		= अणु .type = NLA_STRING, .len = IFNAMSIZ पूर्ण,
	[TCA_FW_MASK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक fw_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			काष्ठा fw_filter *f, काष्ठा nlattr **tb,
			काष्ठा nlattr **tca, अचिन्हित दीर्घ base, bool ovr,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	u32 mask;
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, tca[TCA_RATE], &f->exts, ovr,
				true, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_FW_CLASSID]) अणु
		f->res.classid = nla_get_u32(tb[TCA_FW_CLASSID]);
		tcf_bind_filter(tp, &f->res, base);
	पूर्ण

	अगर (tb[TCA_FW_INDEV]) अणु
		पूर्णांक ret;
		ret = tcf_change_indev(net, tb[TCA_FW_INDEV], extack);
		अगर (ret < 0)
			वापस ret;
		f->अगरindex = ret;
	पूर्ण

	err = -EINVAL;
	अगर (tb[TCA_FW_MASK]) अणु
		mask = nla_get_u32(tb[TCA_FW_MASK]);
		अगर (mask != head->mask)
			वापस err;
	पूर्ण अन्यथा अगर (head->mask != 0xFFFFFFFF)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक fw_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		     काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		     u32 handle, काष्ठा nlattr **tca, व्योम **arg,
		     bool ovr, bool rtnl_held,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	काष्ठा fw_filter *f = *arg;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_FW_MAX + 1];
	पूर्णांक err;

	अगर (!opt)
		वापस handle ? -EINVAL : 0; /* Succeed अगर it is old method. */

	err = nla_parse_nested_deprecated(tb, TCA_FW_MAX, opt, fw_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (f) अणु
		काष्ठा fw_filter *pfp, *fnew;
		काष्ठा fw_filter __rcu **fp;

		अगर (f->id != handle && handle)
			वापस -EINVAL;

		fnew = kzalloc(माप(काष्ठा fw_filter), GFP_KERNEL);
		अगर (!fnew)
			वापस -ENOBUFS;

		fnew->id = f->id;
		fnew->res = f->res;
		fnew->अगरindex = f->अगरindex;
		fnew->tp = f->tp;

		err = tcf_exts_init(&fnew->exts, net, TCA_FW_ACT,
				    TCA_FW_POLICE);
		अगर (err < 0) अणु
			kमुक्त(fnew);
			वापस err;
		पूर्ण

		err = fw_set_parms(net, tp, fnew, tb, tca, base, ovr, extack);
		अगर (err < 0) अणु
			tcf_exts_destroy(&fnew->exts);
			kमुक्त(fnew);
			वापस err;
		पूर्ण

		fp = &head->ht[fw_hash(fnew->id)];
		क्रम (pfp = rtnl_dereference(*fp); pfp;
		     fp = &pfp->next, pfp = rtnl_dereference(*fp))
			अगर (pfp == f)
				अवरोध;

		RCU_INIT_POINTER(fnew->next, rtnl_dereference(pfp->next));
		rcu_assign_poपूर्णांकer(*fp, fnew);
		tcf_unbind_filter(tp, &f->res);
		tcf_exts_get_net(&f->exts);
		tcf_queue_work(&f->rwork, fw_delete_filter_work);

		*arg = fnew;
		वापस err;
	पूर्ण

	अगर (!handle)
		वापस -EINVAL;

	अगर (!head) अणु
		u32 mask = 0xFFFFFFFF;
		अगर (tb[TCA_FW_MASK])
			mask = nla_get_u32(tb[TCA_FW_MASK]);

		head = kzalloc(माप(*head), GFP_KERNEL);
		अगर (!head)
			वापस -ENOBUFS;
		head->mask = mask;

		rcu_assign_poपूर्णांकer(tp->root, head);
	पूर्ण

	f = kzalloc(माप(काष्ठा fw_filter), GFP_KERNEL);
	अगर (f == शून्य)
		वापस -ENOBUFS;

	err = tcf_exts_init(&f->exts, net, TCA_FW_ACT, TCA_FW_POLICE);
	अगर (err < 0)
		जाओ errout;
	f->id = handle;
	f->tp = tp;

	err = fw_set_parms(net, tp, f, tb, tca, base, ovr, extack);
	अगर (err < 0)
		जाओ errout;

	RCU_INIT_POINTER(f->next, head->ht[fw_hash(handle)]);
	rcu_assign_poपूर्णांकer(head->ht[fw_hash(handle)], f);

	*arg = f;
	वापस 0;

errout:
	tcf_exts_destroy(&f->exts);
	kमुक्त(f);
	वापस err;
पूर्ण

अटल व्योम fw_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		    bool rtnl_held)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	पूर्णांक h;

	अगर (head == शून्य)
		arg->stop = 1;

	अगर (arg->stop)
		वापस;

	क्रम (h = 0; h < HTSIZE; h++) अणु
		काष्ठा fw_filter *f;

		क्रम (f = rtnl_dereference(head->ht[h]); f;
		     f = rtnl_dereference(f->next)) अणु
			अगर (arg->count < arg->skip) अणु
				arg->count++;
				जारी;
			पूर्ण
			अगर (arg->fn(tp, f, arg) < 0) अणु
				arg->stop = 1;
				वापस;
			पूर्ण
			arg->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fw_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		   काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा fw_head *head = rtnl_dereference(tp->root);
	काष्ठा fw_filter *f = fh;
	काष्ठा nlattr *nest;

	अगर (f == शून्य)
		वापस skb->len;

	t->tcm_handle = f->id;

	अगर (!f->res.classid && !tcf_exts_has_actions(&f->exts))
		वापस skb->len;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (f->res.classid &&
	    nla_put_u32(skb, TCA_FW_CLASSID, f->res.classid))
		जाओ nla_put_failure;
	अगर (f->अगरindex) अणु
		काष्ठा net_device *dev;
		dev = __dev_get_by_index(net, f->अगरindex);
		अगर (dev && nla_put_string(skb, TCA_FW_INDEV, dev->name))
			जाओ nla_put_failure;
	पूर्ण
	अगर (head->mask != 0xFFFFFFFF &&
	    nla_put_u32(skb, TCA_FW_MASK, head->mask))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम fw_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			  अचिन्हित दीर्घ base)
अणु
	काष्ठा fw_filter *f = fh;

	अगर (f && f->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &f->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &f->res);
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops cls_fw_ops __पढ़ो_mostly = अणु
	.kind		=	"fw",
	.classअगरy	=	fw_classअगरy,
	.init		=	fw_init,
	.destroy	=	fw_destroy,
	.get		=	fw_get,
	.change		=	fw_change,
	.delete		=	fw_delete,
	.walk		=	fw_walk,
	.dump		=	fw_dump,
	.bind_class	=	fw_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_fw(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_fw_ops);
पूर्ण

अटल व्योम __निकास निकास_fw(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_fw_ops);
पूर्ण

module_init(init_fw)
module_निकास(निकास_fw)
MODULE_LICENSE("GPL");
