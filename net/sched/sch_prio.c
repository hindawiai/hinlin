<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_prio.c	Simple 3-band priority "scheduler".
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 * Fixes:       19990609: J Hadi Salim <hadi@nortelnetworks.com>:
 *              Init --  EINVAL when opt undefined
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

काष्ठा prio_sched_data अणु
	पूर्णांक bands;
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block *block;
	u8  prio2band[TC_PRIO_MAX+1];
	काष्ठा Qdisc *queues[TCQ_PRIO_BANDS];
पूर्ण;


अटल काष्ठा Qdisc *
prio_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, पूर्णांक *qerr)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	u32 band = skb->priority;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *fl;
	पूर्णांक err;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	अगर (TC_H_MAJ(skb->priority) != sch->handle) अणु
		fl = rcu_dereference_bh(q->filter_list);
		err = tcf_classअगरy(skb, fl, &res, false);
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (err) अणु
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस शून्य;
		पूर्ण
#पूर्ण_अगर
		अगर (!fl || err < 0) अणु
			अगर (TC_H_MAJ(band))
				band = 0;
			वापस q->queues[q->prio2band[band & TC_PRIO_MAX]];
		पूर्ण
		band = res.classid;
	पूर्ण
	band = TC_H_MIN(band) - 1;
	अगर (band >= q->bands)
		वापस q->queues[q->prio2band[0]];

	वापस q->queues[band];
पूर्ण

अटल पूर्णांक
prio_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा Qdisc *qdisc;
	पूर्णांक ret;

	qdisc = prio_classअगरy(skb, sch, &ret);
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (qdisc == शून्य) अणु

		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	ret = qdisc_enqueue(skb, qdisc, to_मुक्त);
	अगर (ret == NET_XMIT_SUCCESS) अणु
		sch->qstats.backlog += len;
		sch->q.qlen++;
		वापस NET_XMIT_SUCCESS;
	पूर्ण
	अगर (net_xmit_drop_count(ret))
		qdisc_qstats_drop(sch);
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *prio_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	क्रम (prio = 0; prio < q->bands; prio++) अणु
		काष्ठा Qdisc *qdisc = q->queues[prio];
		काष्ठा sk_buff *skb = qdisc->ops->peek(qdisc);
		अगर (skb)
			वापस skb;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *prio_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	क्रम (prio = 0; prio < q->bands; prio++) अणु
		काष्ठा Qdisc *qdisc = q->queues[prio];
		काष्ठा sk_buff *skb = qdisc_dequeue_peeked(qdisc);
		अगर (skb) अणु
			qdisc_bstats_update(sch, skb);
			qdisc_qstats_backlog_dec(sch, skb);
			sch->q.qlen--;
			वापस skb;
		पूर्ण
	पूर्ण
	वापस शून्य;

पूर्ण

अटल व्योम
prio_reset(काष्ठा Qdisc *sch)
अणु
	पूर्णांक prio;
	काष्ठा prio_sched_data *q = qdisc_priv(sch);

	क्रम (prio = 0; prio < q->bands; prio++)
		qdisc_reset(q->queues[prio]);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल पूर्णांक prio_offload(काष्ठा Qdisc *sch, काष्ठा tc_prio_qopt *qopt)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_prio_qopt_offload opt = अणु
		.handle = sch->handle,
		.parent = sch->parent,
	पूर्ण;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस -EOPNOTSUPP;

	अगर (qopt) अणु
		opt.command = TC_PRIO_REPLACE;
		opt.replace_params.bands = qopt->bands;
		स_नकल(&opt.replace_params.priomap, qopt->priomap,
		       TC_PRIO_MAX + 1);
		opt.replace_params.qstats = &sch->qstats;
	पूर्ण अन्यथा अणु
		opt.command = TC_PRIO_DESTROY;
	पूर्ण

	वापस dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_PRIO, &opt);
पूर्ण

अटल व्योम
prio_destroy(काष्ठा Qdisc *sch)
अणु
	पूर्णांक prio;
	काष्ठा prio_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	prio_offload(sch, शून्य);
	क्रम (prio = 0; prio < q->bands; prio++)
		qdisc_put(q->queues[prio]);
पूर्ण

अटल पूर्णांक prio_tune(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *queues[TCQ_PRIO_BANDS];
	पूर्णांक oldbands = q->bands, i;
	काष्ठा tc_prio_qopt *qopt;

	अगर (nla_len(opt) < माप(*qopt))
		वापस -EINVAL;
	qopt = nla_data(opt);

	अगर (qopt->bands > TCQ_PRIO_BANDS || qopt->bands < 2)
		वापस -EINVAL;

	क्रम (i = 0; i <= TC_PRIO_MAX; i++) अणु
		अगर (qopt->priomap[i] >= qopt->bands)
			वापस -EINVAL;
	पूर्ण

	/* Beक्रमe commit, make sure we can allocate all new qdiscs */
	क्रम (i = oldbands; i < qopt->bands; i++) अणु
		queues[i] = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					      TC_H_MAKE(sch->handle, i + 1),
					      extack);
		अगर (!queues[i]) अणु
			जबतक (i > oldbands)
				qdisc_put(queues[--i]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	prio_offload(sch, qopt);
	sch_tree_lock(sch);
	q->bands = qopt->bands;
	स_नकल(q->prio2band, qopt->priomap, TC_PRIO_MAX+1);

	क्रम (i = q->bands; i < oldbands; i++)
		qdisc_tree_flush_backlog(q->queues[i]);

	क्रम (i = oldbands; i < q->bands; i++) अणु
		q->queues[i] = queues[i];
		अगर (q->queues[i] != &noop_qdisc)
			qdisc_hash_add(q->queues[i], true);
	पूर्ण

	sch_tree_unlock(sch);

	क्रम (i = q->bands; i < oldbands; i++)
		qdisc_put(q->queues[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक prio_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	वापस prio_tune(sch, opt, extack);
पूर्ण

अटल पूर्णांक prio_dump_offload(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_prio_qopt_offload hw_stats = अणु
		.command = TC_PRIO_STATS,
		.handle = sch->handle,
		.parent = sch->parent,
		अणु
			.stats = अणु
				.bstats = &sch->bstats,
				.qstats = &sch->qstats,
			पूर्ण,
		पूर्ण,
	पूर्ण;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_PRIO, &hw_stats);
पूर्ण

अटल पूर्णांक prio_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_prio_qopt opt;
	पूर्णांक err;

	opt.bands = q->bands;
	स_नकल(&opt.priomap, q->prio2band, TC_PRIO_MAX + 1);

	err = prio_dump_offload(sch);
	अगर (err)
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक prio_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		      काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_prio_qopt_offload graft_offload;
	अचिन्हित दीर्घ band = arg - 1;

	अगर (!new) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					TC_H_MAKE(sch->handle, arg), extack);
		अगर (!new)
			new = &noop_qdisc;
		अन्यथा
			qdisc_hash_add(new, true);
	पूर्ण

	*old = qdisc_replace(sch, new, &q->queues[band]);

	graft_offload.handle = sch->handle;
	graft_offload.parent = sch->parent;
	graft_offload.graft_params.band = band;
	graft_offload.graft_params.child_handle = new->handle;
	graft_offload.command = TC_PRIO_GRAFT;

	qdisc_offload_graft_helper(qdisc_dev(sch), sch, new, *old,
				   TC_SETUP_QDISC_PRIO, &graft_offload,
				   extack);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *
prio_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	अचिन्हित दीर्घ band = arg - 1;

	वापस q->queues[band];
पूर्ण

अटल अचिन्हित दीर्घ prio_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	अचिन्हित दीर्घ band = TC_H_MIN(classid);

	अगर (band - 1 >= q->bands)
		वापस 0;
	वापस band;
पूर्ण

अटल अचिन्हित दीर्घ prio_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent, u32 classid)
अणु
	वापस prio_find(sch, classid);
पूर्ण


अटल व्योम prio_unbind(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल पूर्णांक prio_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl, काष्ठा sk_buff *skb,
			   काष्ठा tcmsg *tcm)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);

	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = q->queues[cl-1]->handle;
	वापस 0;
पूर्ण

अटल पूर्णांक prio_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				 काष्ठा gnet_dump *d)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *cl_q;

	cl_q = q->queues[cl - 1];
	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, cl_q->cpu_bstats, &cl_q->bstats) < 0 ||
	    qdisc_qstats_copy(d, cl_q) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम prio_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);
	पूर्णांक prio;

	अगर (arg->stop)
		वापस;

	क्रम (prio = 0; prio < q->bands; prio++) अणु
		अगर (arg->count < arg->skip) अणु
			arg->count++;
			जारी;
		पूर्ण
		अगर (arg->fn(sch, prio + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *prio_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prio_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops prio_class_ops = अणु
	.graft		=	prio_graft,
	.leaf		=	prio_leaf,
	.find		=	prio_find,
	.walk		=	prio_walk,
	.tcf_block	=	prio_tcf_block,
	.bind_tcf	=	prio_bind,
	.unbind_tcf	=	prio_unbind,
	.dump		=	prio_dump_class,
	.dump_stats	=	prio_dump_class_stats,
पूर्ण;

अटल काष्ठा Qdisc_ops prio_qdisc_ops __पढ़ो_mostly = अणु
	.next		=	शून्य,
	.cl_ops		=	&prio_class_ops,
	.id		=	"prio",
	.priv_size	=	माप(काष्ठा prio_sched_data),
	.enqueue	=	prio_enqueue,
	.dequeue	=	prio_dequeue,
	.peek		=	prio_peek,
	.init		=	prio_init,
	.reset		=	prio_reset,
	.destroy	=	prio_destroy,
	.change		=	prio_tune,
	.dump		=	prio_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init prio_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&prio_qdisc_ops);
पूर्ण

अटल व्योम __निकास prio_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&prio_qdisc_ops);
पूर्ण

module_init(prio_module_init)
module_निकास(prio_module_निकास)

MODULE_LICENSE("GPL");
