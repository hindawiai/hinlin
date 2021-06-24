<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_drr.c         Deficit Round Robin scheduler
 *
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

काष्ठा drr_class अणु
	काष्ठा Qdisc_class_common	common;
	अचिन्हित पूर्णांक			filter_cnt;

	काष्ठा gnet_stats_basic_packed		bstats;
	काष्ठा gnet_stats_queue		qstats;
	काष्ठा net_rate_estimator __rcu *rate_est;
	काष्ठा list_head		alist;
	काष्ठा Qdisc			*qdisc;

	u32				quantum;
	u32				deficit;
पूर्ण;

काष्ठा drr_sched अणु
	काष्ठा list_head		active;
	काष्ठा tcf_proto __rcu		*filter_list;
	काष्ठा tcf_block		*block;
	काष्ठा Qdisc_class_hash		clhash;
पूर्ण;

अटल काष्ठा drr_class *drr_find_class(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc_class_common *clc;

	clc = qdisc_class_find(&q->clhash, classid);
	अगर (clc == शून्य)
		वापस शून्य;
	वापस container_of(clc, काष्ठा drr_class, common);
पूर्ण

अटल स्थिर काष्ठा nla_policy drr_policy[TCA_DRR_MAX + 1] = अणु
	[TCA_DRR_QUANTUM]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक drr_change_class(काष्ठा Qdisc *sch, u32 classid, u32 parentid,
			    काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl = (काष्ठा drr_class *)*arg;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_DRR_MAX + 1];
	u32 quantum;
	पूर्णांक err;

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack, "DRR options are required for this operation");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_DRR_MAX, opt, drr_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_DRR_QUANTUM]) अणु
		quantum = nla_get_u32(tb[TCA_DRR_QUANTUM]);
		अगर (quantum == 0) अणु
			NL_SET_ERR_MSG(extack, "Specified DRR quantum cannot be zero");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		quantum = psched_mtu(qdisc_dev(sch));

	अगर (cl != शून्य) अणु
		अगर (tca[TCA_RATE]) अणु
			err = gen_replace_estimator(&cl->bstats, शून्य,
						    &cl->rate_est,
						    शून्य,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			अगर (err) अणु
				NL_SET_ERR_MSG(extack, "Failed to replace estimator");
				वापस err;
			पूर्ण
		पूर्ण

		sch_tree_lock(sch);
		अगर (tb[TCA_DRR_QUANTUM])
			cl->quantum = quantum;
		sch_tree_unlock(sch);

		वापस 0;
	पूर्ण

	cl = kzalloc(माप(काष्ठा drr_class), GFP_KERNEL);
	अगर (cl == शून्य)
		वापस -ENOBUFS;

	cl->common.classid = classid;
	cl->quantum	   = quantum;
	cl->qdisc	   = qdisc_create_dflt(sch->dev_queue,
					       &pfअगरo_qdisc_ops, classid,
					       शून्य);
	अगर (cl->qdisc == शून्य)
		cl->qdisc = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(cl->qdisc, true);

	अगर (tca[TCA_RATE]) अणु
		err = gen_replace_estimator(&cl->bstats, शून्य, &cl->rate_est,
					    शून्य,
					    qdisc_root_sleeping_running(sch),
					    tca[TCA_RATE]);
		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Failed to replace estimator");
			qdisc_put(cl->qdisc);
			kमुक्त(cl);
			वापस err;
		पूर्ण
	पूर्ण

	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->common);
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (अचिन्हित दीर्घ)cl;
	वापस 0;
पूर्ण

अटल व्योम drr_destroy_class(काष्ठा Qdisc *sch, काष्ठा drr_class *cl)
अणु
	gen_समाप्त_estimator(&cl->rate_est);
	qdisc_put(cl->qdisc);
	kमुक्त(cl);
पूर्ण

अटल पूर्णांक drr_delete_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;

	अगर (cl->filter_cnt > 0)
		वापस -EBUSY;

	sch_tree_lock(sch);

	qdisc_purge_queue(cl->qdisc);
	qdisc_class_hash_हटाओ(&q->clhash, &cl->common);

	sch_tree_unlock(sch);

	drr_destroy_class(sch, cl);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ drr_search_class(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस (अचिन्हित दीर्घ)drr_find_class(sch, classid);
पूर्ण

अटल काष्ठा tcf_block *drr_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);

	अगर (cl) अणु
		NL_SET_ERR_MSG(extack, "DRR classid must be zero");
		वापस शून्य;
	पूर्ण

	वापस q->block;
पूर्ण

अटल अचिन्हित दीर्घ drr_bind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
				  u32 classid)
अणु
	काष्ठा drr_class *cl = drr_find_class(sch, classid);

	अगर (cl != शून्य)
		cl->filter_cnt++;

	वापस (अचिन्हित दीर्घ)cl;
पूर्ण

अटल व्योम drr_unbind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;

	cl->filter_cnt--;
पूर्ण

अटल पूर्णांक drr_graft_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			   काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;

	अगर (new == शून्य) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					cl->common.classid, शून्य);
		अगर (new == शून्य)
			new = &noop_qdisc;
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *drr_class_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;

	वापस cl->qdisc;
पूर्ण

अटल व्योम drr_qlen_notअगरy(काष्ठा Qdisc *csh, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;

	list_del(&cl->alist);
पूर्ण

अटल पूर्णांक drr_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;
	काष्ठा nlattr *nest;

	tcm->tcm_parent	= TC_H_ROOT;
	tcm->tcm_handle	= cl->common.classid;
	tcm->tcm_info	= cl->qdisc->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, TCA_DRR_QUANTUM, cl->quantum))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक drr_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
				काष्ठा gnet_dump *d)
अणु
	काष्ठा drr_class *cl = (काष्ठा drr_class *)arg;
	__u32 qlen = qdisc_qlen_sum(cl->qdisc);
	काष्ठा Qdisc *cl_q = cl->qdisc;
	काष्ठा tc_drr_stats xstats;

	स_रखो(&xstats, 0, माप(xstats));
	अगर (qlen)
		xstats.deficit = cl->deficit;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, cl_q->cpu_qstats, &cl_q->qstats, qlen) < 0)
		वापस -1;

	वापस gnet_stats_copy_app(d, &xstats, माप(xstats));
पूर्ण

अटल व्योम drr_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			अगर (arg->count < arg->skip) अणु
				arg->count++;
				जारी;
			पूर्ण
			अगर (arg->fn(sch, (अचिन्हित दीर्घ)cl, arg) < 0) अणु
				arg->stop = 1;
				वापस;
			पूर्ण
			arg->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा drr_class *drr_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				      पूर्णांक *qerr)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *fl;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority ^ sch->handle) == 0) अणु
		cl = drr_find_class(sch, skb->priority);
		अगर (cl != शून्य)
			वापस cl;
	पूर्ण

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	fl = rcu_dereference_bh(q->filter_list);
	result = tcf_classअगरy(skb, fl, &res, false);
	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस शून्य;
		पूर्ण
#पूर्ण_अगर
		cl = (काष्ठा drr_class *)res.class;
		अगर (cl == शून्य)
			cl = drr_find_class(sch, res.classid);
		वापस cl;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक drr_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	पूर्णांक err = 0;
	bool first;

	cl = drr_classअगरy(skb, sch, &err);
	अगर (cl == शून्य) अणु
		अगर (err & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस err;
	पूर्ण

	first = !cl->qdisc->q.qlen;
	err = qdisc_enqueue(skb, cl->qdisc, to_मुक्त);
	अगर (unlikely(err != NET_XMIT_SUCCESS)) अणु
		अगर (net_xmit_drop_count(err)) अणु
			cl->qstats.drops++;
			qdisc_qstats_drop(sch);
		पूर्ण
		वापस err;
	पूर्ण

	अगर (first) अणु
		list_add_tail(&cl->alist, &q->active);
		cl->deficit = cl->quantum;
	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *drr_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	अगर (list_empty(&q->active))
		जाओ out;
	जबतक (1) अणु
		cl = list_first_entry(&q->active, काष्ठा drr_class, alist);
		skb = cl->qdisc->ops->peek(cl->qdisc);
		अगर (skb == शून्य) अणु
			qdisc_warn_nonwc(__func__, cl->qdisc);
			जाओ out;
		पूर्ण

		len = qdisc_pkt_len(skb);
		अगर (len <= cl->deficit) अणु
			cl->deficit -= len;
			skb = qdisc_dequeue_peeked(cl->qdisc);
			अगर (unlikely(skb == शून्य))
				जाओ out;
			अगर (cl->qdisc->q.qlen == 0)
				list_del(&cl->alist);

			bstats_update(&cl->bstats, skb);
			qdisc_bstats_update(sch, skb);
			qdisc_qstats_backlog_dec(sch, skb);
			sch->q.qlen--;
			वापस skb;
		पूर्ण

		cl->deficit += cl->quantum;
		list_move_tail(&cl->alist, &q->active);
	पूर्ण
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक drr_init_qdisc(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	पूर्णांक err;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;
	err = qdisc_class_hash_init(&q->clhash);
	अगर (err < 0)
		वापस err;
	INIT_LIST_HEAD(&q->active);
	वापस 0;
पूर्ण

अटल व्योम drr_reset_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			अगर (cl->qdisc->q.qlen)
				list_del(&cl->alist);
			qdisc_reset(cl->qdisc);
		पूर्ण
	पूर्ण
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम drr_destroy_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा drr_sched *q = qdisc_priv(sch);
	काष्ठा drr_class *cl;
	काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक i;

	tcf_block_put(q->block);

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry_safe(cl, next, &q->clhash.hash[i],
					  common.hnode)
			drr_destroy_class(sch, cl);
	पूर्ण
	qdisc_class_hash_destroy(&q->clhash);
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops drr_class_ops = अणु
	.change		= drr_change_class,
	.delete		= drr_delete_class,
	.find		= drr_search_class,
	.tcf_block	= drr_tcf_block,
	.bind_tcf	= drr_bind_tcf,
	.unbind_tcf	= drr_unbind_tcf,
	.graft		= drr_graft_class,
	.leaf		= drr_class_leaf,
	.qlen_notअगरy	= drr_qlen_notअगरy,
	.dump		= drr_dump_class,
	.dump_stats	= drr_dump_class_stats,
	.walk		= drr_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops drr_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &drr_class_ops,
	.id		= "drr",
	.priv_size	= माप(काष्ठा drr_sched),
	.enqueue	= drr_enqueue,
	.dequeue	= drr_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= drr_init_qdisc,
	.reset		= drr_reset_qdisc,
	.destroy	= drr_destroy_qdisc,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init drr_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&drr_qdisc_ops);
पूर्ण

अटल व्योम __निकास drr_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&drr_qdisc_ops);
पूर्ण

module_init(drr_init);
module_निकास(drr_निकास);
MODULE_LICENSE("GPL");
