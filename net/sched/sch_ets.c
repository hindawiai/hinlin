<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_ets.c         Enhanced Transmission Selection scheduler
 *
 * Description
 * -----------
 *
 * The Enhanced Transmission Selection scheduler is a classful queuing
 * discipline that merges functionality of PRIO and DRR qdiscs in one scheduler.
 * ETS makes it easy to configure a set of strict and bandwidth-sharing bands to
 * implement the transmission selection described in 802.1Qaz.
 *
 * Although ETS is technically classful, it's not possible to add and हटाओ
 * classes at will. Instead one specअगरies number of classes, how many are
 * PRIO-like and how many DRR-like, and quanta क्रम the latter.
 *
 * Algorithm
 * ---------
 *
 * The strict classes, अगर any, are tried क्रम traffic first: first band 0, अगर it
 * has no traffic then band 1, etc.
 *
 * When there is no traffic in any of the strict queues, the bandwidth-sharing
 * ones are tried next. Each band is asचिन्हित a deficit counter, initialized to
 * "quantum" of that band. ETS मुख्यtains a list of active bandwidth-sharing
 * bands whose qdiscs are non-empty. A packet is dequeued from the band at the
 * head of the list अगर the packet size is smaller or equal to the deficit
 * counter. If the counter is too small, it is increased by "quantum" and the
 * scheduler moves on to the next band in the active list.
 */

#समावेश <linux/module.h>
#समावेश <net/gen_stats.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sch_generic.h>

काष्ठा ets_class अणु
	काष्ठा list_head alist; /* In काष्ठा ets_sched.active. */
	काष्ठा Qdisc *qdisc;
	u32 quantum;
	u32 deficit;
	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा gnet_stats_queue qstats;
पूर्ण;

काष्ठा ets_sched अणु
	काष्ठा list_head active;
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block *block;
	अचिन्हित पूर्णांक nbands;
	अचिन्हित पूर्णांक nstrict;
	u8 prio2band[TC_PRIO_MAX + 1];
	काष्ठा ets_class classes[TCQ_ETS_MAX_BANDS];
पूर्ण;

अटल स्थिर काष्ठा nla_policy ets_policy[TCA_ETS_MAX + 1] = अणु
	[TCA_ETS_NBANDS] = अणु .type = NLA_U8 पूर्ण,
	[TCA_ETS_NSTRICT] = अणु .type = NLA_U8 पूर्ण,
	[TCA_ETS_QUANTA] = अणु .type = NLA_NESTED पूर्ण,
	[TCA_ETS_PRIOMAP] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy ets_priomap_policy[TCA_ETS_MAX + 1] = अणु
	[TCA_ETS_PRIOMAP_BAND] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy ets_quanta_policy[TCA_ETS_MAX + 1] = अणु
	[TCA_ETS_QUANTA_BAND] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy ets_class_policy[TCA_ETS_MAX + 1] = अणु
	[TCA_ETS_QUANTA_BAND] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक ets_quantum_parse(काष्ठा Qdisc *sch, स्थिर काष्ठा nlattr *attr,
			     अचिन्हित पूर्णांक *quantum,
			     काष्ठा netlink_ext_ack *extack)
अणु
	*quantum = nla_get_u32(attr);
	अगर (!*quantum) अणु
		NL_SET_ERR_MSG(extack, "ETS quantum cannot be zero");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ets_class *
ets_class_from_arg(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);

	वापस &q->classes[arg - 1];
पूर्ण

अटल u32 ets_class_id(काष्ठा Qdisc *sch, स्थिर काष्ठा ets_class *cl)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	पूर्णांक band = cl - q->classes;

	वापस TC_H_MAKE(sch->handle, band + 1);
पूर्ण

अटल व्योम ets_offload_change(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा tc_ets_qopt_offload qopt;
	अचिन्हित पूर्णांक w_psum_prev = 0;
	अचिन्हित पूर्णांक q_psum = 0;
	अचिन्हित पूर्णांक q_sum = 0;
	अचिन्हित पूर्णांक quantum;
	अचिन्हित पूर्णांक w_psum;
	अचिन्हित पूर्णांक weight;
	अचिन्हित पूर्णांक i;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_ETS_REPLACE;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.replace_params.bands = q->nbands;
	qopt.replace_params.qstats = &sch->qstats;
	स_नकल(&qopt.replace_params.priomap,
	       q->prio2band, माप(q->prio2band));

	क्रम (i = 0; i < q->nbands; i++)
		q_sum += q->classes[i].quantum;

	क्रम (i = 0; i < q->nbands; i++) अणु
		quantum = q->classes[i].quantum;
		q_psum += quantum;
		w_psum = quantum ? q_psum * 100 / q_sum : 0;
		weight = w_psum - w_psum_prev;
		w_psum_prev = w_psum;

		qopt.replace_params.quanta[i] = quantum;
		qopt.replace_params.weights[i] = weight;
	पूर्ण

	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_ETS, &qopt);
पूर्ण

अटल व्योम ets_offload_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_ets_qopt_offload qopt;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	qopt.command = TC_ETS_DESTROY;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_ETS, &qopt);
पूर्ण

अटल व्योम ets_offload_graft(काष्ठा Qdisc *sch, काष्ठा Qdisc *new,
			      काष्ठा Qdisc *old, अचिन्हित दीर्घ arg,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_ets_qopt_offload qopt;

	qopt.command = TC_ETS_GRAFT;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.graft_params.band = arg - 1;
	qopt.graft_params.child_handle = new->handle;

	qdisc_offload_graft_helper(dev, sch, new, old, TC_SETUP_QDISC_ETS,
				   &qopt, extack);
पूर्ण

अटल पूर्णांक ets_offload_dump(काष्ठा Qdisc *sch)
अणु
	काष्ठा tc_ets_qopt_offload qopt;

	qopt.command = TC_ETS_STATS;
	qopt.handle = sch->handle;
	qopt.parent = sch->parent;
	qopt.stats.bstats = &sch->bstats;
	qopt.stats.qstats = &sch->qstats;

	वापस qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_ETS, &qopt);
पूर्ण

अटल bool ets_class_is_strict(काष्ठा ets_sched *q, स्थिर काष्ठा ets_class *cl)
अणु
	अचिन्हित पूर्णांक band = cl - q->classes;

	वापस band < q->nstrict;
पूर्ण

अटल पूर्णांक ets_class_change(काष्ठा Qdisc *sch, u32 classid, u32 parentid,
			    काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, *arg);
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_ETS_MAX + 1];
	अचिन्हित पूर्णांक quantum;
	पूर्णांक err;

	/* Classes can be added and हटाओd only through Qdisc_ops.change
	 * पूर्णांकerface.
	 */
	अगर (!cl) अणु
		NL_SET_ERR_MSG(extack, "Fine-grained class addition and removal is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack, "ETS options are required for this operation");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_ETS_MAX, opt, ets_class_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_ETS_QUANTA_BAND])
		/* Nothing to configure. */
		वापस 0;

	अगर (ets_class_is_strict(q, cl)) अणु
		NL_SET_ERR_MSG(extack, "Strict bands do not have a configurable quantum");
		वापस -EINVAL;
	पूर्ण

	err = ets_quantum_parse(sch, tb[TCA_ETS_QUANTA_BAND], &quantum,
				extack);
	अगर (err)
		वापस err;

	sch_tree_lock(sch);
	cl->quantum = quantum;
	sch_tree_unlock(sch);

	ets_offload_change(sch);
	वापस 0;
पूर्ण

अटल पूर्णांक ets_class_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			   काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, arg);

	अगर (!new) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					ets_class_id(sch, cl), शून्य);
		अगर (!new)
			new = &noop_qdisc;
		अन्यथा
			qdisc_hash_add(new, true);
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->qdisc);
	ets_offload_graft(sch, new, *old, arg, extack);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *ets_class_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, arg);

	वापस cl->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ ets_class_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	अचिन्हित दीर्घ band = TC_H_MIN(classid);
	काष्ठा ets_sched *q = qdisc_priv(sch);

	अगर (band - 1 >= q->nbands)
		वापस 0;
	वापस band;
पूर्ण

अटल व्योम ets_class_qlen_notअगरy(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, arg);
	काष्ठा ets_sched *q = qdisc_priv(sch);

	/* We get notअगरied about zero-length child Qdiscs as well अगर they are
	 * offloaded. Those aren't on the active list though, so don't attempt
	 * to हटाओ them.
	 */
	अगर (!ets_class_is_strict(q, cl) && sch->q.qlen)
		list_del(&cl->alist);
पूर्ण

अटल पूर्णांक ets_class_dump(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, arg);
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *nest;

	tcm->tcm_parent = TC_H_ROOT;
	tcm->tcm_handle = ets_class_id(sch, cl);
	tcm->tcm_info = cl->qdisc->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;
	अगर (!ets_class_is_strict(q, cl)) अणु
		अगर (nla_put_u32(skb, TCA_ETS_QUANTA_BAND, cl->quantum))
			जाओ nla_put_failure;
	पूर्ण
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ets_class_dump_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
				काष्ठा gnet_dump *d)
अणु
	काष्ठा ets_class *cl = ets_class_from_arg(sch, arg);
	काष्ठा Qdisc *cl_q = cl->qdisc;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &cl_q->bstats) < 0 ||
	    qdisc_qstats_copy(d, cl_q) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम ets_qdisc_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->nbands; i++) अणु
		अगर (arg->count < arg->skip) अणु
			arg->count++;
			जारी;
		पूर्ण
		अगर (arg->fn(sch, i + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *
ets_qdisc_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);

	अगर (cl) अणु
		NL_SET_ERR_MSG(extack, "ETS classid must be zero");
		वापस शून्य;
	पूर्ण

	वापस q->block;
पूर्ण

अटल अचिन्हित दीर्घ ets_qdisc_bind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
					u32 classid)
अणु
	वापस ets_class_find(sch, classid);
पूर्ण

अटल व्योम ets_qdisc_unbind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
पूर्ण

अटल काष्ठा ets_class *ets_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				      पूर्णांक *qerr)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
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
			वापस &q->classes[q->prio2band[band & TC_PRIO_MAX]];
		पूर्ण
		band = res.classid;
	पूर्ण
	band = TC_H_MIN(band) - 1;
	अगर (band >= q->nbands)
		वापस &q->classes[q->prio2band[0]];
	वापस &q->classes[band];
पूर्ण

अटल पूर्णांक ets_qdisc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			     काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा ets_class *cl;
	पूर्णांक err = 0;
	bool first;

	cl = ets_classअगरy(skb, sch, &err);
	अगर (!cl) अणु
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

	अगर (first && !ets_class_is_strict(q, cl)) अणु
		list_add_tail(&cl->alist, &q->active);
		cl->deficit = cl->quantum;
	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *
ets_qdisc_dequeue_skb(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ets_qdisc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा ets_class *cl;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक band;
	अचिन्हित पूर्णांक len;

	जबतक (1) अणु
		क्रम (band = 0; band < q->nstrict; band++) अणु
			cl = &q->classes[band];
			skb = qdisc_dequeue_peeked(cl->qdisc);
			अगर (skb)
				वापस ets_qdisc_dequeue_skb(sch, skb);
		पूर्ण

		अगर (list_empty(&q->active))
			जाओ out;

		cl = list_first_entry(&q->active, काष्ठा ets_class, alist);
		skb = cl->qdisc->ops->peek(cl->qdisc);
		अगर (!skb) अणु
			qdisc_warn_nonwc(__func__, cl->qdisc);
			जाओ out;
		पूर्ण

		len = qdisc_pkt_len(skb);
		अगर (len <= cl->deficit) अणु
			cl->deficit -= len;
			skb = qdisc_dequeue_peeked(cl->qdisc);
			अगर (unlikely(!skb))
				जाओ out;
			अगर (cl->qdisc->q.qlen == 0)
				list_del(&cl->alist);
			वापस ets_qdisc_dequeue_skb(sch, skb);
		पूर्ण

		cl->deficit += cl->quantum;
		list_move_tail(&cl->alist, &q->active);
	पूर्ण
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक ets_qdisc_priomap_parse(काष्ठा nlattr *priomap_attr,
				   अचिन्हित पूर्णांक nbands, u8 *priomap,
				   काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr *attr;
	पूर्णांक prio = 0;
	u8 band;
	पूर्णांक rem;
	पूर्णांक err;

	err = __nla_validate_nested(priomap_attr, TCA_ETS_MAX,
				    ets_priomap_policy, NL_VALIDATE_STRICT,
				    extack);
	अगर (err)
		वापस err;

	nla_क्रम_each_nested(attr, priomap_attr, rem) अणु
		चयन (nla_type(attr)) अणु
		हाल TCA_ETS_PRIOMAP_BAND:
			अगर (prio > TC_PRIO_MAX) अणु
				NL_SET_ERR_MSG_MOD(extack, "Too many priorities in ETS priomap");
				वापस -EINVAL;
			पूर्ण
			band = nla_get_u8(attr);
			अगर (band >= nbands) अणु
				NL_SET_ERR_MSG_MOD(extack, "Invalid band number in ETS priomap");
				वापस -EINVAL;
			पूर्ण
			priomap[prio++] = band;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1); /* Validate should have caught this. */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ets_qdisc_quanta_parse(काष्ठा Qdisc *sch, काष्ठा nlattr *quanta_attr,
				  अचिन्हित पूर्णांक nbands, अचिन्हित पूर्णांक nstrict,
				  अचिन्हित पूर्णांक *quanta,
				  काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr *attr;
	पूर्णांक band = nstrict;
	पूर्णांक rem;
	पूर्णांक err;

	err = __nla_validate_nested(quanta_attr, TCA_ETS_MAX,
				    ets_quanta_policy, NL_VALIDATE_STRICT,
				    extack);
	अगर (err < 0)
		वापस err;

	nla_क्रम_each_nested(attr, quanta_attr, rem) अणु
		चयन (nla_type(attr)) अणु
		हाल TCA_ETS_QUANTA_BAND:
			अगर (band >= nbands) अणु
				NL_SET_ERR_MSG_MOD(extack, "ETS quanta has more values than bands");
				वापस -EINVAL;
			पूर्ण
			err = ets_quantum_parse(sch, attr, &quanta[band++],
						extack);
			अगर (err)
				वापस err;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1); /* Validate should have caught this. */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ets_qdisc_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			    काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक quanta[TCQ_ETS_MAX_BANDS] = अणु0पूर्ण;
	काष्ठा Qdisc *queues[TCQ_ETS_MAX_BANDS];
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_ETS_MAX + 1];
	अचिन्हित पूर्णांक oldbands = q->nbands;
	u8 priomap[TC_PRIO_MAX + 1];
	अचिन्हित पूर्णांक nstrict = 0;
	अचिन्हित पूर्णांक nbands;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack, "ETS options are required for this operation");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_ETS_MAX, opt, ets_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_ETS_NBANDS]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Number of bands is a required argument");
		वापस -EINVAL;
	पूर्ण
	nbands = nla_get_u8(tb[TCA_ETS_NBANDS]);
	अगर (nbands < 1 || nbands > TCQ_ETS_MAX_BANDS) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid number of bands");
		वापस -EINVAL;
	पूर्ण
	/* Unless overridden, traffic goes to the last band. */
	स_रखो(priomap, nbands - 1, माप(priomap));

	अगर (tb[TCA_ETS_NSTRICT]) अणु
		nstrict = nla_get_u8(tb[TCA_ETS_NSTRICT]);
		अगर (nstrict > nbands) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid number of strict bands");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (tb[TCA_ETS_PRIOMAP]) अणु
		err = ets_qdisc_priomap_parse(tb[TCA_ETS_PRIOMAP],
					      nbands, priomap, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[TCA_ETS_QUANTA]) अणु
		err = ets_qdisc_quanta_parse(sch, tb[TCA_ETS_QUANTA],
					     nbands, nstrict, quanta, extack);
		अगर (err)
			वापस err;
	पूर्ण
	/* If there are more bands than strict + quanta provided, the reमुख्यing
	 * ones are ETS with quantum of MTU. Initialize the missing values here.
	 */
	क्रम (i = nstrict; i < nbands; i++) अणु
		अगर (!quanta[i])
			quanta[i] = psched_mtu(qdisc_dev(sch));
	पूर्ण

	/* Beक्रमe commit, make sure we can allocate all new qdiscs */
	क्रम (i = oldbands; i < nbands; i++) अणु
		queues[i] = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					      ets_class_id(sch, &q->classes[i]),
					      extack);
		अगर (!queues[i]) अणु
			जबतक (i > oldbands)
				qdisc_put(queues[--i]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	sch_tree_lock(sch);

	q->nbands = nbands;
	q->nstrict = nstrict;
	स_नकल(q->prio2band, priomap, माप(priomap));

	क्रम (i = q->nbands; i < oldbands; i++)
		qdisc_tree_flush_backlog(q->classes[i].qdisc);

	क्रम (i = 0; i < q->nbands; i++)
		q->classes[i].quantum = quanta[i];

	क्रम (i = oldbands; i < q->nbands; i++) अणु
		q->classes[i].qdisc = queues[i];
		अगर (q->classes[i].qdisc != &noop_qdisc)
			qdisc_hash_add(q->classes[i].qdisc, true);
	पूर्ण

	sch_tree_unlock(sch);

	ets_offload_change(sch);
	क्रम (i = q->nbands; i < oldbands; i++) अणु
		qdisc_put(q->classes[i].qdisc);
		स_रखो(&q->classes[i], 0, माप(q->classes[i]));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ets_qdisc_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	INIT_LIST_HEAD(&q->active);
	वापस ets_qdisc_change(sch, opt, extack);
पूर्ण

अटल व्योम ets_qdisc_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	पूर्णांक band;

	क्रम (band = q->nstrict; band < q->nbands; band++) अणु
		अगर (q->classes[band].qdisc->q.qlen)
			list_del(&q->classes[band].alist);
	पूर्ण
	क्रम (band = 0; band < q->nbands; band++)
		qdisc_reset(q->classes[band].qdisc);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम ets_qdisc_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	पूर्णांक band;

	ets_offload_destroy(sch);
	tcf_block_put(q->block);
	क्रम (band = 0; band < q->nbands; band++)
		qdisc_put(q->classes[band].qdisc);
पूर्ण

अटल पूर्णांक ets_qdisc_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा ets_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;
	काष्ठा nlattr *nest;
	पूर्णांक band;
	पूर्णांक prio;
	पूर्णांक err;

	err = ets_offload_dump(sch);
	अगर (err)
		वापस err;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!opts)
		जाओ nla_err;

	अगर (nla_put_u8(skb, TCA_ETS_NBANDS, q->nbands))
		जाओ nla_err;

	अगर (q->nstrict &&
	    nla_put_u8(skb, TCA_ETS_NSTRICT, q->nstrict))
		जाओ nla_err;

	अगर (q->nbands > q->nstrict) अणु
		nest = nla_nest_start(skb, TCA_ETS_QUANTA);
		अगर (!nest)
			जाओ nla_err;

		क्रम (band = q->nstrict; band < q->nbands; band++) अणु
			अगर (nla_put_u32(skb, TCA_ETS_QUANTA_BAND,
					q->classes[band].quantum))
				जाओ nla_err;
		पूर्ण

		nla_nest_end(skb, nest);
	पूर्ण

	nest = nla_nest_start(skb, TCA_ETS_PRIOMAP);
	अगर (!nest)
		जाओ nla_err;

	क्रम (prio = 0; prio <= TC_PRIO_MAX; prio++) अणु
		अगर (nla_put_u8(skb, TCA_ETS_PRIOMAP_BAND, q->prio2band[prio]))
			जाओ nla_err;
	पूर्ण

	nla_nest_end(skb, nest);

	वापस nla_nest_end(skb, opts);

nla_err:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops ets_class_ops = अणु
	.change		= ets_class_change,
	.graft		= ets_class_graft,
	.leaf		= ets_class_leaf,
	.find		= ets_class_find,
	.qlen_notअगरy	= ets_class_qlen_notअगरy,
	.dump		= ets_class_dump,
	.dump_stats	= ets_class_dump_stats,
	.walk		= ets_qdisc_walk,
	.tcf_block	= ets_qdisc_tcf_block,
	.bind_tcf	= ets_qdisc_bind_tcf,
	.unbind_tcf	= ets_qdisc_unbind_tcf,
पूर्ण;

अटल काष्ठा Qdisc_ops ets_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &ets_class_ops,
	.id		= "ets",
	.priv_size	= माप(काष्ठा ets_sched),
	.enqueue	= ets_qdisc_enqueue,
	.dequeue	= ets_qdisc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.change		= ets_qdisc_change,
	.init		= ets_qdisc_init,
	.reset		= ets_qdisc_reset,
	.destroy	= ets_qdisc_destroy,
	.dump		= ets_qdisc_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ets_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&ets_qdisc_ops);
पूर्ण

अटल व्योम __निकास ets_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&ets_qdisc_ops);
पूर्ण

module_init(ets_init);
module_निकास(ets_निकास);
MODULE_LICENSE("GPL");
