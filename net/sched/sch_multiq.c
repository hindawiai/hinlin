<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, Intel Corporation.
 *
 * Author: Alexander Duyck <alexander.h.duyck@पूर्णांकel.com>
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

काष्ठा multiq_sched_data अणु
	u16 bands;
	u16 max_bands;
	u16 curband;
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block *block;
	काष्ठा Qdisc **queues;
पूर्ण;


अटल काष्ठा Qdisc *
multiq_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, पूर्णांक *qerr)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	u32 band;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *fl = rcu_dereference_bh(q->filter_list);
	पूर्णांक err;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
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
	band = skb_get_queue_mapping(skb);

	अगर (band >= q->bands)
		वापस q->queues[0];

	वापस q->queues[band];
पूर्ण

अटल पूर्णांक
multiq_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
	       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा Qdisc *qdisc;
	पूर्णांक ret;

	qdisc = multiq_classअगरy(skb, sch, &ret);
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
		sch->q.qlen++;
		वापस NET_XMIT_SUCCESS;
	पूर्ण
	अगर (net_xmit_drop_count(ret))
		qdisc_qstats_drop(sch);
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *multiq_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *qdisc;
	काष्ठा sk_buff *skb;
	पूर्णांक band;

	क्रम (band = 0; band < q->bands; band++) अणु
		/* cycle through bands to ensure fairness */
		q->curband++;
		अगर (q->curband >= q->bands)
			q->curband = 0;

		/* Check that target subqueue is available beक्रमe
		 * pulling an skb to aव्योम head-of-line blocking.
		 */
		अगर (!netअगर_xmit_stopped(
		    netdev_get_tx_queue(qdisc_dev(sch), q->curband))) अणु
			qdisc = q->queues[q->curband];
			skb = qdisc->dequeue(qdisc);
			अगर (skb) अणु
				qdisc_bstats_update(sch, skb);
				sch->q.qlen--;
				वापस skb;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;

पूर्ण

अटल काष्ठा sk_buff *multiq_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक curband = q->curband;
	काष्ठा Qdisc *qdisc;
	काष्ठा sk_buff *skb;
	पूर्णांक band;

	क्रम (band = 0; band < q->bands; band++) अणु
		/* cycle through bands to ensure fairness */
		curband++;
		अगर (curband >= q->bands)
			curband = 0;

		/* Check that target subqueue is available beक्रमe
		 * pulling an skb to aव्योम head-of-line blocking.
		 */
		अगर (!netअगर_xmit_stopped(
		    netdev_get_tx_queue(qdisc_dev(sch), curband))) अणु
			qdisc = q->queues[curband];
			skb = qdisc->ops->peek(qdisc);
			अगर (skb)
				वापस skb;
		पूर्ण
	पूर्ण
	वापस शून्य;

पूर्ण

अटल व्योम
multiq_reset(काष्ठा Qdisc *sch)
अणु
	u16 band;
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);

	क्रम (band = 0; band < q->bands; band++)
		qdisc_reset(q->queues[band]);
	sch->q.qlen = 0;
	q->curband = 0;
पूर्ण

अटल व्योम
multiq_destroy(काष्ठा Qdisc *sch)
अणु
	पूर्णांक band;
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	क्रम (band = 0; band < q->bands; band++)
		qdisc_put(q->queues[band]);

	kमुक्त(q->queues);
पूर्ण

अटल पूर्णांक multiq_tune(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_multiq_qopt *qopt;
	काष्ठा Qdisc **हटाओd;
	पूर्णांक i, n_हटाओd = 0;

	अगर (!netअगर_is_multiqueue(qdisc_dev(sch)))
		वापस -EOPNOTSUPP;
	अगर (nla_len(opt) < माप(*qopt))
		वापस -EINVAL;

	qopt = nla_data(opt);

	qopt->bands = qdisc_dev(sch)->real_num_tx_queues;

	हटाओd = kदो_स्मृति(माप(*हटाओd) * (q->max_bands - q->bands),
			  GFP_KERNEL);
	अगर (!हटाओd)
		वापस -ENOMEM;

	sch_tree_lock(sch);
	q->bands = qopt->bands;
	क्रम (i = q->bands; i < q->max_bands; i++) अणु
		अगर (q->queues[i] != &noop_qdisc) अणु
			काष्ठा Qdisc *child = q->queues[i];

			q->queues[i] = &noop_qdisc;
			qdisc_purge_queue(child);
			हटाओd[n_हटाओd++] = child;
		पूर्ण
	पूर्ण

	sch_tree_unlock(sch);

	क्रम (i = 0; i < n_हटाओd; i++)
		qdisc_put(हटाओd[i]);
	kमुक्त(हटाओd);

	क्रम (i = 0; i < q->bands; i++) अणु
		अगर (q->queues[i] == &noop_qdisc) अणु
			काष्ठा Qdisc *child, *old;
			child = qdisc_create_dflt(sch->dev_queue,
						  &pfअगरo_qdisc_ops,
						  TC_H_MAKE(sch->handle,
							    i + 1), extack);
			अगर (child) अणु
				sch_tree_lock(sch);
				old = q->queues[i];
				q->queues[i] = child;
				अगर (child != &noop_qdisc)
					qdisc_hash_add(child, true);

				अगर (old != &noop_qdisc)
					qdisc_purge_queue(old);
				sch_tree_unlock(sch);
				qdisc_put(old);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक multiq_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	पूर्णांक i, err;

	q->queues = शून्य;

	अगर (!opt)
		वापस -EINVAL;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	q->max_bands = qdisc_dev(sch)->num_tx_queues;

	q->queues = kसुस्मृति(q->max_bands, माप(काष्ठा Qdisc *), GFP_KERNEL);
	अगर (!q->queues)
		वापस -ENOBUFS;
	क्रम (i = 0; i < q->max_bands; i++)
		q->queues[i] = &noop_qdisc;

	वापस multiq_tune(sch, opt, extack);
पूर्ण

अटल पूर्णांक multiq_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_multiq_qopt opt;

	opt.bands = q->bands;
	opt.max_bands = q->max_bands;

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक multiq_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
			काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	अचिन्हित दीर्घ band = arg - 1;

	अगर (new == शून्य)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->queues[band]);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *
multiq_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	अचिन्हित दीर्घ band = arg - 1;

	वापस q->queues[band];
पूर्ण

अटल अचिन्हित दीर्घ multiq_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	अचिन्हित दीर्घ band = TC_H_MIN(classid);

	अगर (band - 1 >= q->bands)
		वापस 0;
	वापस band;
पूर्ण

अटल अचिन्हित दीर्घ multiq_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
				 u32 classid)
अणु
	वापस multiq_find(sch, classid);
पूर्ण


अटल व्योम multiq_unbind(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल पूर्णांक multiq_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			     काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);

	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = q->queues[cl - 1]->handle;
	वापस 0;
पूर्ण

अटल पूर्णांक multiq_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				 काष्ठा gnet_dump *d)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *cl_q;

	cl_q = q->queues[cl - 1];
	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, cl_q->cpu_bstats, &cl_q->bstats) < 0 ||
	    qdisc_qstats_copy(d, cl_q) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम multiq_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);
	पूर्णांक band;

	अगर (arg->stop)
		वापस;

	क्रम (band = 0; band < q->bands; band++) अणु
		अगर (arg->count < arg->skip) अणु
			arg->count++;
			जारी;
		पूर्ण
		अगर (arg->fn(sch, band + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *multiq_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा multiq_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops multiq_class_ops = अणु
	.graft		=	multiq_graft,
	.leaf		=	multiq_leaf,
	.find		=	multiq_find,
	.walk		=	multiq_walk,
	.tcf_block	=	multiq_tcf_block,
	.bind_tcf	=	multiq_bind,
	.unbind_tcf	=	multiq_unbind,
	.dump		=	multiq_dump_class,
	.dump_stats	=	multiq_dump_class_stats,
पूर्ण;

अटल काष्ठा Qdisc_ops multiq_qdisc_ops __पढ़ो_mostly = अणु
	.next		=	शून्य,
	.cl_ops		=	&multiq_class_ops,
	.id		=	"multiq",
	.priv_size	=	माप(काष्ठा multiq_sched_data),
	.enqueue	=	multiq_enqueue,
	.dequeue	=	multiq_dequeue,
	.peek		=	multiq_peek,
	.init		=	multiq_init,
	.reset		=	multiq_reset,
	.destroy	=	multiq_destroy,
	.change		=	multiq_tune,
	.dump		=	multiq_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init multiq_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&multiq_qdisc_ops);
पूर्ण

अटल व्योम __निकास multiq_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&multiq_qdisc_ops);
पूर्ण

module_init(multiq_module_init)
module_निकास(multiq_module_निकास)

MODULE_LICENSE("GPL");
