<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_red.c	Ranकरोm Early Detection queue.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Changes:
 * J Hadi Salim 980914:	computation fixes
 * Alexey Makarenko <makar@phoenix.kharkov.ua> 990814: qave on idle link was calculated incorrectly.
 * J Hadi Salim 980816:  ECN support
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/red.h>


/*	Parameters, settable by user:
	-----------------------------

	limit		- bytes (must be > qth_max + burst)

	Hard limit on queue length, should be chosen >qth_max
	to allow packet bursts. This parameter करोes not
	affect the algorithms behaviour and can be chosen
	arbitrarily high (well, less than ram size)
	Really, this limit will never be reached
	अगर RED works correctly.
 */

काष्ठा red_sched_data अणु
	u32			limit;		/* HARD maximal queue length */

	अचिन्हित अक्षर		flags;
	/* Non-flags in tc_red_qopt.flags. */
	अचिन्हित अक्षर		userbits;

	काष्ठा समयr_list	adapt_समयr;
	काष्ठा Qdisc		*sch;
	काष्ठा red_parms	parms;
	काष्ठा red_vars		vars;
	काष्ठा red_stats	stats;
	काष्ठा Qdisc		*qdisc;
	काष्ठा tcf_qevent	qe_early_drop;
	काष्ठा tcf_qevent	qe_mark;
पूर्ण;

#घोषणा TC_RED_SUPPORTED_FLAGS (TC_RED_HISTORIC_FLAGS | TC_RED_NODROP)

अटल अंतरभूत पूर्णांक red_use_ecn(काष्ठा red_sched_data *q)
अणु
	वापस q->flags & TC_RED_ECN;
पूर्ण

अटल अंतरभूत पूर्णांक red_use_harddrop(काष्ठा red_sched_data *q)
अणु
	वापस q->flags & TC_RED_HARDDROP;
पूर्ण

अटल पूर्णांक red_use_nodrop(काष्ठा red_sched_data *q)
अणु
	वापस q->flags & TC_RED_NODROP;
पूर्ण

अटल पूर्णांक red_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;
	पूर्णांक ret;

	q->vars.qavg = red_calc_qavg(&q->parms,
				     &q->vars,
				     child->qstats.backlog);

	अगर (red_is_idling(&q->vars))
		red_end_of_idle_period(&q->vars);

	चयन (red_action(&q->parms, &q->vars, q->vars.qavg)) अणु
	हाल RED_DONT_MARK:
		अवरोध;

	हाल RED_PROB_MARK:
		qdisc_qstats_overlimit(sch);
		अगर (!red_use_ecn(q)) अणु
			q->stats.prob_drop++;
			जाओ congestion_drop;
		पूर्ण

		अगर (INET_ECN_set_ce(skb)) अणु
			q->stats.prob_mark++;
			skb = tcf_qevent_handle(&q->qe_mark, sch, skb, to_मुक्त, &ret);
			अगर (!skb)
				वापस NET_XMIT_CN | ret;
		पूर्ण अन्यथा अगर (!red_use_nodrop(q)) अणु
			q->stats.prob_drop++;
			जाओ congestion_drop;
		पूर्ण

		/* Non-ECT packet in ECN nodrop mode: queue it. */
		अवरोध;

	हाल RED_HARD_MARK:
		qdisc_qstats_overlimit(sch);
		अगर (red_use_harddrop(q) || !red_use_ecn(q)) अणु
			q->stats.क्रमced_drop++;
			जाओ congestion_drop;
		पूर्ण

		अगर (INET_ECN_set_ce(skb)) अणु
			q->stats.क्रमced_mark++;
			skb = tcf_qevent_handle(&q->qe_mark, sch, skb, to_मुक्त, &ret);
			अगर (!skb)
				वापस NET_XMIT_CN | ret;
		पूर्ण अन्यथा अगर (!red_use_nodrop(q)) अणु
			q->stats.क्रमced_drop++;
			जाओ congestion_drop;
		पूर्ण

		/* Non-ECT packet in ECN nodrop mode: queue it. */
		अवरोध;
	पूर्ण

	ret = qdisc_enqueue(skb, child, to_मुक्त);
	अगर (likely(ret == NET_XMIT_SUCCESS)) अणु
		qdisc_qstats_backlog_inc(sch, skb);
		sch->q.qlen++;
	पूर्ण अन्यथा अगर (net_xmit_drop_count(ret)) अणु
		q->stats.pdrop++;
		qdisc_qstats_drop(sch);
	पूर्ण
	वापस ret;

congestion_drop:
	skb = tcf_qevent_handle(&q->qe_early_drop, sch, skb, to_मुक्त, &ret);
	अगर (!skb)
		वापस NET_XMIT_CN | ret;

	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_CN;
पूर्ण

अटल काष्ठा sk_buff *red_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;

	skb = child->dequeue(child);
	अगर (skb) अणु
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;
	पूर्ण अन्यथा अणु
		अगर (!red_is_idling(&q->vars))
			red_start_of_idle_period(&q->vars);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *red_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा Qdisc *child = q->qdisc;

	वापस child->ops->peek(child);
पूर्ण

अटल व्योम red_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);

	qdisc_reset(q->qdisc);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
	red_restart(&q->vars);
पूर्ण

अटल पूर्णांक red_offload(काष्ठा Qdisc *sch, bool enable)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_red_qopt_offload opt = अणु
		.handle = sch->handle,
		.parent = sch->parent,
	पूर्ण;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस -EOPNOTSUPP;

	अगर (enable) अणु
		opt.command = TC_RED_REPLACE;
		opt.set.min = q->parms.qth_min >> q->parms.Wlog;
		opt.set.max = q->parms.qth_max >> q->parms.Wlog;
		opt.set.probability = q->parms.max_P;
		opt.set.limit = q->limit;
		opt.set.is_ecn = red_use_ecn(q);
		opt.set.is_harddrop = red_use_harddrop(q);
		opt.set.is_nodrop = red_use_nodrop(q);
		opt.set.qstats = &sch->qstats;
	पूर्ण अन्यथा अणु
		opt.command = TC_RED_DESTROY;
	पूर्ण

	वापस dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_RED, &opt);
पूर्ण

अटल व्योम red_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);

	tcf_qevent_destroy(&q->qe_mark, sch);
	tcf_qevent_destroy(&q->qe_early_drop, sch);
	del_समयr_sync(&q->adapt_समयr);
	red_offload(sch, false);
	qdisc_put(q->qdisc);
पूर्ण

अटल स्थिर काष्ठा nla_policy red_policy[TCA_RED_MAX + 1] = अणु
	[TCA_RED_UNSPEC] = अणु .strict_start_type = TCA_RED_FLAGS पूर्ण,
	[TCA_RED_PARMS]	= अणु .len = माप(काष्ठा tc_red_qopt) पूर्ण,
	[TCA_RED_STAB]	= अणु .len = RED_STAB_SIZE पूर्ण,
	[TCA_RED_MAX_P] = अणु .type = NLA_U32 पूर्ण,
	[TCA_RED_FLAGS] = NLA_POLICY_BITFIELD32(TC_RED_SUPPORTED_FLAGS),
	[TCA_RED_EARLY_DROP_BLOCK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_RED_MARK_BLOCK] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक __red_change(काष्ठा Qdisc *sch, काष्ठा nlattr **tb,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा Qdisc *old_child = शून्य, *child = शून्य;
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा nla_bitfield32 flags_bf;
	काष्ठा tc_red_qopt *ctl;
	अचिन्हित अक्षर userbits;
	अचिन्हित अक्षर flags;
	पूर्णांक err;
	u32 max_P;
	u8 *stab;

	अगर (tb[TCA_RED_PARMS] == शून्य ||
	    tb[TCA_RED_STAB] == शून्य)
		वापस -EINVAL;

	max_P = tb[TCA_RED_MAX_P] ? nla_get_u32(tb[TCA_RED_MAX_P]) : 0;

	ctl = nla_data(tb[TCA_RED_PARMS]);
	stab = nla_data(tb[TCA_RED_STAB]);
	अगर (!red_check_params(ctl->qth_min, ctl->qth_max, ctl->Wlog,
			      ctl->Scell_log, stab))
		वापस -EINVAL;

	err = red_get_flags(ctl->flags, TC_RED_HISTORIC_FLAGS,
			    tb[TCA_RED_FLAGS], TC_RED_SUPPORTED_FLAGS,
			    &flags_bf, &userbits, extack);
	अगर (err)
		वापस err;

	अगर (ctl->limit > 0) अणु
		child = fअगरo_create_dflt(sch, &bfअगरo_qdisc_ops, ctl->limit,
					 extack);
		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		/* child is fअगरo, no need to check क्रम noop_qdisc */
		qdisc_hash_add(child, true);
	पूर्ण

	sch_tree_lock(sch);

	flags = (q->flags & ~flags_bf.selector) | flags_bf.value;
	err = red_validate_flags(flags, extack);
	अगर (err)
		जाओ unlock_out;

	q->flags = flags;
	q->userbits = userbits;
	q->limit = ctl->limit;
	अगर (child) अणु
		qdisc_tree_flush_backlog(q->qdisc);
		old_child = q->qdisc;
		q->qdisc = child;
	पूर्ण

	red_set_parms(&q->parms,
		      ctl->qth_min, ctl->qth_max, ctl->Wlog,
		      ctl->Plog, ctl->Scell_log,
		      stab,
		      max_P);
	red_set_vars(&q->vars);

	del_समयr(&q->adapt_समयr);
	अगर (ctl->flags & TC_RED_ADAPTATIVE)
		mod_समयr(&q->adapt_समयr, jअगरfies + HZ/2);

	अगर (!q->qdisc->q.qlen)
		red_start_of_idle_period(&q->vars);

	sch_tree_unlock(sch);

	red_offload(sch, true);

	अगर (old_child)
		qdisc_put(old_child);
	वापस 0;

unlock_out:
	sch_tree_unlock(sch);
	अगर (child)
		qdisc_put(child);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम red_adaptative_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा red_sched_data *q = from_समयr(q, t, adapt_समयr);
	काष्ठा Qdisc *sch = q->sch;
	spinlock_t *root_lock = qdisc_lock(qdisc_root_sleeping(sch));

	spin_lock(root_lock);
	red_adaptative_algo(&q->parms, &q->vars);
	mod_समयr(&q->adapt_समयr, jअगरfies + HZ/2);
	spin_unlock(root_lock);
पूर्ण

अटल पूर्णांक red_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_RED_MAX + 1];
	पूर्णांक err;

	q->qdisc = &noop_qdisc;
	q->sch = sch;
	समयr_setup(&q->adapt_समयr, red_adaptative_समयr, 0);

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_RED_MAX, opt, red_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	err = __red_change(sch, tb, extack);
	अगर (err)
		वापस err;

	err = tcf_qevent_init(&q->qe_early_drop, sch,
			      FLOW_BLOCK_BINDER_TYPE_RED_EARLY_DROP,
			      tb[TCA_RED_EARLY_DROP_BLOCK], extack);
	अगर (err)
		वापस err;

	वापस tcf_qevent_init(&q->qe_mark, sch,
			       FLOW_BLOCK_BINDER_TYPE_RED_MARK,
			       tb[TCA_RED_MARK_BLOCK], extack);
पूर्ण

अटल पूर्णांक red_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_RED_MAX + 1];
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_RED_MAX, opt, red_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	err = tcf_qevent_validate_change(&q->qe_early_drop,
					 tb[TCA_RED_EARLY_DROP_BLOCK], extack);
	अगर (err)
		वापस err;

	err = tcf_qevent_validate_change(&q->qe_mark,
					 tb[TCA_RED_MARK_BLOCK], extack);
	अगर (err)
		वापस err;

	वापस __red_change(sch, tb, extack);
पूर्ण

अटल पूर्णांक red_dump_offload_stats(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_red_qopt_offload hw_stats = अणु
		.command = TC_RED_STATS,
		.handle = sch->handle,
		.parent = sch->parent,
		अणु
			.stats.bstats = &sch->bstats,
			.stats.qstats = &sch->qstats,
		पूर्ण,
	पूर्ण;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_RED, &hw_stats);
पूर्ण

अटल पूर्णांक red_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts = शून्य;
	काष्ठा tc_red_qopt opt = अणु
		.limit		= q->limit,
		.flags		= (q->flags & TC_RED_HISTORIC_FLAGS) |
				  q->userbits,
		.qth_min	= q->parms.qth_min >> q->parms.Wlog,
		.qth_max	= q->parms.qth_max >> q->parms.Wlog,
		.Wlog		= q->parms.Wlog,
		.Plog		= q->parms.Plog,
		.Scell_log	= q->parms.Scell_log,
	पूर्ण;
	पूर्णांक err;

	err = red_dump_offload_stats(sch);
	अगर (err)
		जाओ nla_put_failure;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put(skb, TCA_RED_PARMS, माप(opt), &opt) ||
	    nla_put_u32(skb, TCA_RED_MAX_P, q->parms.max_P) ||
	    nla_put_bitfield32(skb, TCA_RED_FLAGS,
			       q->flags, TC_RED_SUPPORTED_FLAGS) ||
	    tcf_qevent_dump(skb, TCA_RED_MARK_BLOCK, &q->qe_mark) ||
	    tcf_qevent_dump(skb, TCA_RED_EARLY_DROP_BLOCK, &q->qe_early_drop))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक red_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_red_xstats st = अणु0पूर्ण;

	अगर (sch->flags & TCQ_F_OFFLOADED) अणु
		काष्ठा tc_red_qopt_offload hw_stats_request = अणु
			.command = TC_RED_XSTATS,
			.handle = sch->handle,
			.parent = sch->parent,
			अणु
				.xstats = &q->stats,
			पूर्ण,
		पूर्ण;
		dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_RED,
					      &hw_stats_request);
	पूर्ण
	st.early = q->stats.prob_drop + q->stats.क्रमced_drop;
	st.pdrop = q->stats.pdrop;
	st.other = q->stats.other;
	st.marked = q->stats.prob_mark + q->stats.क्रमced_mark;

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल पूर्णांक red_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);

	tcm->tcm_handle |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handle;
	वापस 0;
पूर्ण

अटल व्योम red_graft_offload(काष्ठा Qdisc *sch,
			      काष्ठा Qdisc *new, काष्ठा Qdisc *old,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_red_qopt_offload graft_offload = अणु
		.handle		= sch->handle,
		.parent		= sch->parent,
		.child_handle	= new->handle,
		.command	= TC_RED_GRAFT,
	पूर्ण;

	qdisc_offload_graft_helper(qdisc_dev(sch), sch, new, old,
				   TC_SETUP_QDISC_RED, &graft_offload, extack);
पूर्ण

अटल पूर्णांक red_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);

	अगर (new == शून्य)
		new = &noop_qdisc;

	*old = qdisc_replace(sch, new, &q->qdisc);

	red_graft_offload(sch, new, *old, extack);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *red_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा red_sched_data *q = qdisc_priv(sch);
	वापस q->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ red_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 1;
पूर्ण

अटल व्योम red_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	अगर (!walker->stop) अणु
		अगर (walker->count >= walker->skip)
			अगर (walker->fn(sch, 1, walker) < 0) अणु
				walker->stop = 1;
				वापस;
			पूर्ण
		walker->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops red_class_ops = अणु
	.graft		=	red_graft,
	.leaf		=	red_leaf,
	.find		=	red_find,
	.walk		=	red_walk,
	.dump		=	red_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops red_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"red",
	.priv_size	=	माप(काष्ठा red_sched_data),
	.cl_ops		=	&red_class_ops,
	.enqueue	=	red_enqueue,
	.dequeue	=	red_dequeue,
	.peek		=	red_peek,
	.init		=	red_init,
	.reset		=	red_reset,
	.destroy	=	red_destroy,
	.change		=	red_change,
	.dump		=	red_dump,
	.dump_stats	=	red_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init red_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&red_qdisc_ops);
पूर्ण

अटल व्योम __निकास red_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&red_qdisc_ops);
पूर्ण

module_init(red_module_init)
module_निकास(red_module_निकास)

MODULE_LICENSE("GPL");
