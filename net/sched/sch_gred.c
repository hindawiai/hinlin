<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_gred.c	Generic Ranकरोm Early Detection queue.
 *
 * Authors:    J Hadi Salim (hadi@cyberus.ca) 1998-2002
 *
 *             991129: -  Bug fix with grio mode
 *		       - a better sing. AvgQ mode with Grio(WRED)
 *		       - A finer grained VQ dequeue based on sugestion
 *		         from Ren Liu
 *		       - More error checks
 *
 *  For all the glorious comments look at include/net/red.h
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/red.h>

#घोषणा GRED_DEF_PRIO (MAX_DPs / 2)
#घोषणा GRED_VQ_MASK (MAX_DPs - 1)

#घोषणा GRED_VQ_RED_FLAGS	(TC_RED_ECN | TC_RED_HARDDROP)

काष्ठा gred_sched_data;
काष्ठा gred_sched;

काष्ठा gred_sched_data अणु
	u32		limit;		/* HARD maximal queue length	*/
	u32		DP;		/* the drop parameters */
	u32		red_flags;	/* भवQ version of red_flags */
	u64		bytesin;	/* bytes seen on भवQ so far*/
	u32		packetsin;	/* packets seen on भवQ so far*/
	u32		backlog;	/* bytes on the भवQ */
	u8		prio;		/* the prio of this vq */

	काष्ठा red_parms parms;
	काष्ठा red_vars  vars;
	काष्ठा red_stats stats;
पूर्ण;

क्रमागत अणु
	GRED_WRED_MODE = 1,
	GRED_RIO_MODE,
पूर्ण;

काष्ठा gred_sched अणु
	काष्ठा gred_sched_data *tab[MAX_DPs];
	अचिन्हित दीर्घ	flags;
	u32		red_flags;
	u32 		DPs;
	u32 		def;
	काष्ठा red_vars wred_set;
पूर्ण;

अटल अंतरभूत पूर्णांक gred_wred_mode(काष्ठा gred_sched *table)
अणु
	वापस test_bit(GRED_WRED_MODE, &table->flags);
पूर्ण

अटल अंतरभूत व्योम gred_enable_wred_mode(काष्ठा gred_sched *table)
अणु
	__set_bit(GRED_WRED_MODE, &table->flags);
पूर्ण

अटल अंतरभूत व्योम gred_disable_wred_mode(काष्ठा gred_sched *table)
अणु
	__clear_bit(GRED_WRED_MODE, &table->flags);
पूर्ण

अटल अंतरभूत पूर्णांक gred_rio_mode(काष्ठा gred_sched *table)
अणु
	वापस test_bit(GRED_RIO_MODE, &table->flags);
पूर्ण

अटल अंतरभूत व्योम gred_enable_rio_mode(काष्ठा gred_sched *table)
अणु
	__set_bit(GRED_RIO_MODE, &table->flags);
पूर्ण

अटल अंतरभूत व्योम gred_disable_rio_mode(काष्ठा gred_sched *table)
अणु
	__clear_bit(GRED_RIO_MODE, &table->flags);
पूर्ण

अटल अंतरभूत पूर्णांक gred_wred_mode_check(काष्ठा Qdisc *sch)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	पूर्णांक i;

	/* Really ugly O(n^2) but shouldn't be necessary too frequent. */
	क्रम (i = 0; i < table->DPs; i++) अणु
		काष्ठा gred_sched_data *q = table->tab[i];
		पूर्णांक n;

		अगर (q == शून्य)
			जारी;

		क्रम (n = i + 1; n < table->DPs; n++)
			अगर (table->tab[n] && table->tab[n]->prio == q->prio)
				वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gred_backlog(काष्ठा gred_sched *table,
					काष्ठा gred_sched_data *q,
					काष्ठा Qdisc *sch)
अणु
	अगर (gred_wred_mode(table))
		वापस sch->qstats.backlog;
	अन्यथा
		वापस q->backlog;
पूर्ण

अटल अंतरभूत u16 tc_index_to_dp(काष्ठा sk_buff *skb)
अणु
	वापस skb->tc_index & GRED_VQ_MASK;
पूर्ण

अटल अंतरभूत व्योम gred_load_wred_set(स्थिर काष्ठा gred_sched *table,
				      काष्ठा gred_sched_data *q)
अणु
	q->vars.qavg = table->wred_set.qavg;
	q->vars.qidlestart = table->wred_set.qidlestart;
पूर्ण

अटल अंतरभूत व्योम gred_store_wred_set(काष्ठा gred_sched *table,
				       काष्ठा gred_sched_data *q)
अणु
	table->wred_set.qavg = q->vars.qavg;
	table->wred_set.qidlestart = q->vars.qidlestart;
पूर्ण

अटल पूर्णांक gred_use_ecn(काष्ठा gred_sched_data *q)
अणु
	वापस q->red_flags & TC_RED_ECN;
पूर्ण

अटल पूर्णांक gred_use_harddrop(काष्ठा gred_sched_data *q)
अणु
	वापस q->red_flags & TC_RED_HARDDROP;
पूर्ण

अटल bool gred_per_vq_red_flags_used(काष्ठा gred_sched *table)
अणु
	अचिन्हित पूर्णांक i;

	/* Local per-vq flags couldn't have been set unless global are 0 */
	अगर (table->red_flags)
		वापस false;
	क्रम (i = 0; i < MAX_DPs; i++)
		अगर (table->tab[i] && table->tab[i]->red_flags)
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक gred_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा gred_sched_data *q = शून्य;
	काष्ठा gred_sched *t = qdisc_priv(sch);
	अचिन्हित दीर्घ qavg = 0;
	u16 dp = tc_index_to_dp(skb);

	अगर (dp >= t->DPs || (q = t->tab[dp]) == शून्य) अणु
		dp = t->def;

		q = t->tab[dp];
		अगर (!q) अणु
			/* Pass through packets not asचिन्हित to a DP
			 * अगर no शेष DP has been configured. This
			 * allows क्रम DP flows to be left untouched.
			 */
			अगर (likely(sch->qstats.backlog + qdisc_pkt_len(skb) <=
					sch->limit))
				वापस qdisc_enqueue_tail(skb, sch);
			अन्यथा
				जाओ drop;
		पूर्ण

		/* fix tc_index? --could be controversial but needed क्रम
		   requeueing */
		skb->tc_index = (skb->tc_index & ~GRED_VQ_MASK) | dp;
	पूर्ण

	/* sum up all the qaves of prios < ours to get the new qave */
	अगर (!gred_wred_mode(t) && gred_rio_mode(t)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < t->DPs; i++) अणु
			अगर (t->tab[i] && t->tab[i]->prio < q->prio &&
			    !red_is_idling(&t->tab[i]->vars))
				qavg += t->tab[i]->vars.qavg;
		पूर्ण

	पूर्ण

	q->packetsin++;
	q->bytesin += qdisc_pkt_len(skb);

	अगर (gred_wred_mode(t))
		gred_load_wred_set(t, q);

	q->vars.qavg = red_calc_qavg(&q->parms,
				     &q->vars,
				     gred_backlog(t, q, sch));

	अगर (red_is_idling(&q->vars))
		red_end_of_idle_period(&q->vars);

	अगर (gred_wred_mode(t))
		gred_store_wred_set(t, q);

	चयन (red_action(&q->parms, &q->vars, q->vars.qavg + qavg)) अणु
	हाल RED_DONT_MARK:
		अवरोध;

	हाल RED_PROB_MARK:
		qdisc_qstats_overlimit(sch);
		अगर (!gred_use_ecn(q) || !INET_ECN_set_ce(skb)) अणु
			q->stats.prob_drop++;
			जाओ congestion_drop;
		पूर्ण

		q->stats.prob_mark++;
		अवरोध;

	हाल RED_HARD_MARK:
		qdisc_qstats_overlimit(sch);
		अगर (gred_use_harddrop(q) || !gred_use_ecn(q) ||
		    !INET_ECN_set_ce(skb)) अणु
			q->stats.क्रमced_drop++;
			जाओ congestion_drop;
		पूर्ण
		q->stats.क्रमced_mark++;
		अवरोध;
	पूर्ण

	अगर (gred_backlog(t, q, sch) + qdisc_pkt_len(skb) <= q->limit) अणु
		q->backlog += qdisc_pkt_len(skb);
		वापस qdisc_enqueue_tail(skb, sch);
	पूर्ण

	q->stats.pdrop++;
drop:
	वापस qdisc_drop(skb, sch, to_मुक्त);

congestion_drop:
	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_CN;
पूर्ण

अटल काष्ठा sk_buff *gred_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा gred_sched *t = qdisc_priv(sch);

	skb = qdisc_dequeue_head(sch);

	अगर (skb) अणु
		काष्ठा gred_sched_data *q;
		u16 dp = tc_index_to_dp(skb);

		अगर (dp >= t->DPs || (q = t->tab[dp]) == शून्य) अणु
			net_warn_ratelimited("GRED: Unable to relocate VQ 0x%x after dequeue, screwing up backlog\n",
					     tc_index_to_dp(skb));
		पूर्ण अन्यथा अणु
			q->backlog -= qdisc_pkt_len(skb);

			अगर (gred_wred_mode(t)) अणु
				अगर (!sch->qstats.backlog)
					red_start_of_idle_period(&t->wred_set);
			पूर्ण अन्यथा अणु
				अगर (!q->backlog)
					red_start_of_idle_period(&q->vars);
			पूर्ण
		पूर्ण

		वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम gred_reset(काष्ठा Qdisc *sch)
अणु
	पूर्णांक i;
	काष्ठा gred_sched *t = qdisc_priv(sch);

	qdisc_reset_queue(sch);

	क्रम (i = 0; i < t->DPs; i++) अणु
		काष्ठा gred_sched_data *q = t->tab[i];

		अगर (!q)
			जारी;

		red_restart(&q->vars);
		q->backlog = 0;
	पूर्ण
पूर्ण

अटल व्योम gred_offload(काष्ठा Qdisc *sch, क्रमागत tc_gred_command command)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_gred_qopt_offload opt = अणु
		.command	= command,
		.handle		= sch->handle,
		.parent		= sch->parent,
	पूर्ण;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	अगर (command == TC_GRED_REPLACE) अणु
		अचिन्हित पूर्णांक i;

		opt.set.grio_on = gred_rio_mode(table);
		opt.set.wred_on = gred_wred_mode(table);
		opt.set.dp_cnt = table->DPs;
		opt.set.dp_def = table->def;

		क्रम (i = 0; i < table->DPs; i++) अणु
			काष्ठा gred_sched_data *q = table->tab[i];

			अगर (!q)
				जारी;
			opt.set.tab[i].present = true;
			opt.set.tab[i].limit = q->limit;
			opt.set.tab[i].prio = q->prio;
			opt.set.tab[i].min = q->parms.qth_min >> q->parms.Wlog;
			opt.set.tab[i].max = q->parms.qth_max >> q->parms.Wlog;
			opt.set.tab[i].is_ecn = gred_use_ecn(q);
			opt.set.tab[i].is_harddrop = gred_use_harddrop(q);
			opt.set.tab[i].probability = q->parms.max_P;
			opt.set.tab[i].backlog = &q->backlog;
		पूर्ण
		opt.set.qstats = &sch->qstats;
	पूर्ण

	dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_GRED, &opt);
पूर्ण

अटल पूर्णांक gred_offload_dump_stats(काष्ठा Qdisc *sch)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा tc_gred_qopt_offload *hw_stats;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	hw_stats = kzalloc(माप(*hw_stats), GFP_KERNEL);
	अगर (!hw_stats)
		वापस -ENOMEM;

	hw_stats->command = TC_GRED_STATS;
	hw_stats->handle = sch->handle;
	hw_stats->parent = sch->parent;

	क्रम (i = 0; i < MAX_DPs; i++)
		अगर (table->tab[i])
			hw_stats->stats.xstats[i] = &table->tab[i]->stats;

	ret = qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_GRED, hw_stats);
	/* Even अगर driver वापसs failure adjust the stats - in हाल offload
	 * ended but driver still wants to adjust the values.
	 */
	क्रम (i = 0; i < MAX_DPs; i++) अणु
		अगर (!table->tab[i])
			जारी;
		table->tab[i]->packetsin += hw_stats->stats.bstats[i].packets;
		table->tab[i]->bytesin += hw_stats->stats.bstats[i].bytes;
		table->tab[i]->backlog += hw_stats->stats.qstats[i].backlog;

		_bstats_update(&sch->bstats,
			       hw_stats->stats.bstats[i].bytes,
			       hw_stats->stats.bstats[i].packets);
		sch->qstats.qlen += hw_stats->stats.qstats[i].qlen;
		sch->qstats.backlog += hw_stats->stats.qstats[i].backlog;
		sch->qstats.drops += hw_stats->stats.qstats[i].drops;
		sch->qstats.requeues += hw_stats->stats.qstats[i].requeues;
		sch->qstats.overlimits += hw_stats->stats.qstats[i].overlimits;
	पूर्ण

	kमुक्त(hw_stats);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम gred_destroy_vq(काष्ठा gred_sched_data *q)
अणु
	kमुक्त(q);
पूर्ण

अटल पूर्णांक gred_change_table_def(काष्ठा Qdisc *sch, काष्ठा nlattr *dps,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा tc_gred_sopt *sopt;
	bool red_flags_changed;
	पूर्णांक i;

	अगर (!dps)
		वापस -EINVAL;

	sopt = nla_data(dps);

	अगर (sopt->DPs > MAX_DPs) अणु
		NL_SET_ERR_MSG_MOD(extack, "number of virtual queues too high");
		वापस -EINVAL;
	पूर्ण
	अगर (sopt->DPs == 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "number of virtual queues can't be 0");
		वापस -EINVAL;
	पूर्ण
	अगर (sopt->def_DP >= sopt->DPs) अणु
		NL_SET_ERR_MSG_MOD(extack, "default virtual queue above virtual queue count");
		वापस -EINVAL;
	पूर्ण
	अगर (sopt->flags && gred_per_vq_red_flags_used(table)) अणु
		NL_SET_ERR_MSG_MOD(extack, "can't set per-Qdisc RED flags when per-virtual queue flags are used");
		वापस -EINVAL;
	पूर्ण

	sch_tree_lock(sch);
	table->DPs = sopt->DPs;
	table->def = sopt->def_DP;
	red_flags_changed = table->red_flags != sopt->flags;
	table->red_flags = sopt->flags;

	/*
	 * Every entry poपूर्णांक to GRED is synchronized with the above code
	 * and the DP is checked against DPs, i.e. shaकरोwed VQs can no
	 * दीर्घer be found so we can unlock right here.
	 */
	sch_tree_unlock(sch);

	अगर (sopt->grio) अणु
		gred_enable_rio_mode(table);
		gred_disable_wred_mode(table);
		अगर (gred_wred_mode_check(sch))
			gred_enable_wred_mode(table);
	पूर्ण अन्यथा अणु
		gred_disable_rio_mode(table);
		gred_disable_wred_mode(table);
	पूर्ण

	अगर (red_flags_changed)
		क्रम (i = 0; i < table->DPs; i++)
			अगर (table->tab[i])
				table->tab[i]->red_flags =
					table->red_flags & GRED_VQ_RED_FLAGS;

	क्रम (i = table->DPs; i < MAX_DPs; i++) अणु
		अगर (table->tab[i]) अणु
			pr_warn("GRED: Warning: Destroying shadowed VQ 0x%x\n",
				i);
			gred_destroy_vq(table->tab[i]);
			table->tab[i] = शून्य;
		पूर्ण
	पूर्ण

	gred_offload(sch, TC_GRED_REPLACE);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gred_change_vq(काष्ठा Qdisc *sch, पूर्णांक dp,
				 काष्ठा tc_gred_qopt *ctl, पूर्णांक prio,
				 u8 *stab, u32 max_P,
				 काष्ठा gred_sched_data **pपुनः_स्मृति,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा gred_sched_data *q = table->tab[dp];

	अगर (!red_check_params(ctl->qth_min, ctl->qth_max, ctl->Wlog, ctl->Scell_log, stab)) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid RED parameters");
		वापस -EINVAL;
	पूर्ण

	अगर (!q) अणु
		table->tab[dp] = q = *pपुनः_स्मृति;
		*pपुनः_स्मृति = शून्य;
		अगर (!q)
			वापस -ENOMEM;
		q->red_flags = table->red_flags & GRED_VQ_RED_FLAGS;
	पूर्ण

	q->DP = dp;
	q->prio = prio;
	अगर (ctl->limit > sch->limit)
		q->limit = sch->limit;
	अन्यथा
		q->limit = ctl->limit;

	अगर (q->backlog == 0)
		red_end_of_idle_period(&q->vars);

	red_set_parms(&q->parms,
		      ctl->qth_min, ctl->qth_max, ctl->Wlog, ctl->Plog,
		      ctl->Scell_log, stab, max_P);
	red_set_vars(&q->vars);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy gred_vq_policy[TCA_GRED_VQ_MAX + 1] = अणु
	[TCA_GRED_VQ_DP]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_GRED_VQ_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy gred_vqe_policy[TCA_GRED_VQ_ENTRY_MAX + 1] = अणु
	[TCA_GRED_VQ_ENTRY]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy gred_policy[TCA_GRED_MAX + 1] = अणु
	[TCA_GRED_PARMS]	= अणु .len = माप(काष्ठा tc_gred_qopt) पूर्ण,
	[TCA_GRED_STAB]		= अणु .len = 256 पूर्ण,
	[TCA_GRED_DPS]		= अणु .len = माप(काष्ठा tc_gred_sopt) पूर्ण,
	[TCA_GRED_MAX_P]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_GRED_LIMIT]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_GRED_VQ_LIST]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल व्योम gred_vq_apply(काष्ठा gred_sched *table, स्थिर काष्ठा nlattr *entry)
अणु
	काष्ठा nlattr *tb[TCA_GRED_VQ_MAX + 1];
	u32 dp;

	nla_parse_nested_deprecated(tb, TCA_GRED_VQ_MAX, entry,
				    gred_vq_policy, शून्य);

	dp = nla_get_u32(tb[TCA_GRED_VQ_DP]);

	अगर (tb[TCA_GRED_VQ_FLAGS])
		table->tab[dp]->red_flags = nla_get_u32(tb[TCA_GRED_VQ_FLAGS]);
पूर्ण

अटल व्योम gred_vqs_apply(काष्ठा gred_sched *table, काष्ठा nlattr *vqs)
अणु
	स्थिर काष्ठा nlattr *attr;
	पूर्णांक rem;

	nla_क्रम_each_nested(attr, vqs, rem) अणु
		चयन (nla_type(attr)) अणु
		हाल TCA_GRED_VQ_ENTRY:
			gred_vq_apply(table, attr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gred_vq_validate(काष्ठा gred_sched *table, u32 cdp,
			    स्थिर काष्ठा nlattr *entry,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_GRED_VQ_MAX + 1];
	पूर्णांक err;
	u32 dp;

	err = nla_parse_nested_deprecated(tb, TCA_GRED_VQ_MAX, entry,
					  gred_vq_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_GRED_VQ_DP]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Virtual queue with no index specified");
		वापस -EINVAL;
	पूर्ण
	dp = nla_get_u32(tb[TCA_GRED_VQ_DP]);
	अगर (dp >= table->DPs) अणु
		NL_SET_ERR_MSG_MOD(extack, "Virtual queue with index out of bounds");
		वापस -EINVAL;
	पूर्ण
	अगर (dp != cdp && !table->tab[dp]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Virtual queue not yet instantiated");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_GRED_VQ_FLAGS]) अणु
		u32 red_flags = nla_get_u32(tb[TCA_GRED_VQ_FLAGS]);

		अगर (table->red_flags && table->red_flags != red_flags) अणु
			NL_SET_ERR_MSG_MOD(extack, "can't change per-virtual queue RED flags when per-Qdisc flags are used");
			वापस -EINVAL;
		पूर्ण
		अगर (red_flags & ~GRED_VQ_RED_FLAGS) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "invalid RED flags specified");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gred_vqs_validate(काष्ठा gred_sched *table, u32 cdp,
			     काष्ठा nlattr *vqs, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr *attr;
	पूर्णांक rem, err;

	err = nla_validate_nested_deprecated(vqs, TCA_GRED_VQ_ENTRY_MAX,
					     gred_vqe_policy, extack);
	अगर (err < 0)
		वापस err;

	nla_क्रम_each_nested(attr, vqs, rem) अणु
		चयन (nla_type(attr)) अणु
		हाल TCA_GRED_VQ_ENTRY:
			err = gred_vq_validate(table, cdp, attr, extack);
			अगर (err)
				वापस err;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "GRED_VQ_LIST can contain only entry attributes");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (rem > 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Trailing data after parsing virtual queue list");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gred_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा tc_gred_qopt *ctl;
	काष्ठा nlattr *tb[TCA_GRED_MAX + 1];
	पूर्णांक err, prio = GRED_DEF_PRIO;
	u8 *stab;
	u32 max_P;
	काष्ठा gred_sched_data *pपुनः_स्मृति;

	अगर (opt == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_GRED_MAX, opt, gred_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_GRED_PARMS] == शून्य && tb[TCA_GRED_STAB] == शून्य) अणु
		अगर (tb[TCA_GRED_LIMIT] != शून्य)
			sch->limit = nla_get_u32(tb[TCA_GRED_LIMIT]);
		वापस gred_change_table_def(sch, tb[TCA_GRED_DPS], extack);
	पूर्ण

	अगर (tb[TCA_GRED_PARMS] == शून्य ||
	    tb[TCA_GRED_STAB] == शून्य ||
	    tb[TCA_GRED_LIMIT] != शून्य) अणु
		NL_SET_ERR_MSG_MOD(extack, "can't configure Qdisc and virtual queue at the same time");
		वापस -EINVAL;
	पूर्ण

	max_P = tb[TCA_GRED_MAX_P] ? nla_get_u32(tb[TCA_GRED_MAX_P]) : 0;

	ctl = nla_data(tb[TCA_GRED_PARMS]);
	stab = nla_data(tb[TCA_GRED_STAB]);

	अगर (ctl->DP >= table->DPs) अणु
		NL_SET_ERR_MSG_MOD(extack, "virtual queue index above virtual queue count");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_GRED_VQ_LIST]) अणु
		err = gred_vqs_validate(table, ctl->DP, tb[TCA_GRED_VQ_LIST],
					extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (gred_rio_mode(table)) अणु
		अगर (ctl->prio == 0) अणु
			पूर्णांक def_prio = GRED_DEF_PRIO;

			अगर (table->tab[table->def])
				def_prio = table->tab[table->def]->prio;

			prपूर्णांकk(KERN_DEBUG "GRED: DP %u does not have a prio "
			       "setting default to %d\n", ctl->DP, def_prio);

			prio = def_prio;
		पूर्ण अन्यथा
			prio = ctl->prio;
	पूर्ण

	pपुनः_स्मृति = kzalloc(माप(*pपुनः_स्मृति), GFP_KERNEL);
	sch_tree_lock(sch);

	err = gred_change_vq(sch, ctl->DP, ctl, prio, stab, max_P, &pपुनः_स्मृति,
			     extack);
	अगर (err < 0)
		जाओ err_unlock_मुक्त;

	अगर (tb[TCA_GRED_VQ_LIST])
		gred_vqs_apply(table, tb[TCA_GRED_VQ_LIST]);

	अगर (gred_rio_mode(table)) अणु
		gred_disable_wred_mode(table);
		अगर (gred_wred_mode_check(sch))
			gred_enable_wred_mode(table);
	पूर्ण

	sch_tree_unlock(sch);
	kमुक्त(pपुनः_स्मृति);

	gred_offload(sch, TC_GRED_REPLACE);
	वापस 0;

err_unlock_मुक्त:
	sch_tree_unlock(sch);
	kमुक्त(pपुनः_स्मृति);
	वापस err;
पूर्ण

अटल पूर्णांक gred_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_GRED_MAX + 1];
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_GRED_MAX, opt, gred_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_GRED_PARMS] || tb[TCA_GRED_STAB]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "virtual queue configuration can't be specified at initialization time");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_GRED_LIMIT])
		sch->limit = nla_get_u32(tb[TCA_GRED_LIMIT]);
	अन्यथा
		sch->limit = qdisc_dev(sch)->tx_queue_len
		             * psched_mtu(qdisc_dev(sch));

	वापस gred_change_table_def(sch, tb[TCA_GRED_DPS], extack);
पूर्ण

अटल पूर्णांक gred_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	काष्ठा nlattr *parms, *vqs, *opts = शून्य;
	पूर्णांक i;
	u32 max_p[MAX_DPs];
	काष्ठा tc_gred_sopt sopt = अणु
		.DPs	= table->DPs,
		.def_DP	= table->def,
		.grio	= gred_rio_mode(table),
		.flags	= table->red_flags,
	पूर्ण;

	अगर (gred_offload_dump_stats(sch))
		जाओ nla_put_failure;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put(skb, TCA_GRED_DPS, माप(sopt), &sopt))
		जाओ nla_put_failure;

	क्रम (i = 0; i < MAX_DPs; i++) अणु
		काष्ठा gred_sched_data *q = table->tab[i];

		max_p[i] = q ? q->parms.max_P : 0;
	पूर्ण
	अगर (nla_put(skb, TCA_GRED_MAX_P, माप(max_p), max_p))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_GRED_LIMIT, sch->limit))
		जाओ nla_put_failure;

	/* Old style all-in-one dump of VQs */
	parms = nla_nest_start_noflag(skb, TCA_GRED_PARMS);
	अगर (parms == शून्य)
		जाओ nla_put_failure;

	क्रम (i = 0; i < MAX_DPs; i++) अणु
		काष्ठा gred_sched_data *q = table->tab[i];
		काष्ठा tc_gred_qopt opt;
		अचिन्हित दीर्घ qavg;

		स_रखो(&opt, 0, माप(opt));

		अगर (!q) अणु
			/* hack -- fix at some poपूर्णांक with proper message
			   This is how we indicate to tc that there is no VQ
			   at this DP */

			opt.DP = MAX_DPs + i;
			जाओ append_opt;
		पूर्ण

		opt.limit	= q->limit;
		opt.DP		= q->DP;
		opt.backlog	= gred_backlog(table, q, sch);
		opt.prio	= q->prio;
		opt.qth_min	= q->parms.qth_min >> q->parms.Wlog;
		opt.qth_max	= q->parms.qth_max >> q->parms.Wlog;
		opt.Wlog	= q->parms.Wlog;
		opt.Plog	= q->parms.Plog;
		opt.Scell_log	= q->parms.Scell_log;
		opt.other	= q->stats.other;
		opt.early	= q->stats.prob_drop;
		opt.क्रमced	= q->stats.क्रमced_drop;
		opt.pdrop	= q->stats.pdrop;
		opt.packets	= q->packetsin;
		opt.bytesin	= q->bytesin;

		अगर (gred_wred_mode(table))
			gred_load_wred_set(table, q);

		qavg = red_calc_qavg(&q->parms, &q->vars,
				     q->vars.qavg >> q->parms.Wlog);
		opt.qave = qavg >> q->parms.Wlog;

append_opt:
		अगर (nla_append(skb, माप(opt), &opt) < 0)
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(skb, parms);

	/* Dump the VQs again, in more काष्ठाured way */
	vqs = nla_nest_start_noflag(skb, TCA_GRED_VQ_LIST);
	अगर (!vqs)
		जाओ nla_put_failure;

	क्रम (i = 0; i < MAX_DPs; i++) अणु
		काष्ठा gred_sched_data *q = table->tab[i];
		काष्ठा nlattr *vq;

		अगर (!q)
			जारी;

		vq = nla_nest_start_noflag(skb, TCA_GRED_VQ_ENTRY);
		अगर (!vq)
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, TCA_GRED_VQ_DP, q->DP))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, TCA_GRED_VQ_FLAGS, q->red_flags))
			जाओ nla_put_failure;

		/* Stats */
		अगर (nla_put_u64_64bit(skb, TCA_GRED_VQ_STAT_BYTES, q->bytesin,
				      TCA_GRED_VQ_PAD))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_PACKETS, q->packetsin))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_BACKLOG,
				gred_backlog(table, q, sch)))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_PROB_DROP,
				q->stats.prob_drop))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_PROB_MARK,
				q->stats.prob_mark))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_FORCED_DROP,
				q->stats.क्रमced_drop))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_FORCED_MARK,
				q->stats.क्रमced_mark))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_PDROP, q->stats.pdrop))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, TCA_GRED_VQ_STAT_OTHER, q->stats.other))
			जाओ nla_put_failure;

		nla_nest_end(skb, vq);
	पूर्ण
	nla_nest_end(skb, vqs);

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम gred_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा gred_sched *table = qdisc_priv(sch);
	पूर्णांक i;

	क्रम (i = 0; i < table->DPs; i++) अणु
		अगर (table->tab[i])
			gred_destroy_vq(table->tab[i]);
	पूर्ण
	gred_offload(sch, TC_GRED_DESTROY);
पूर्ण

अटल काष्ठा Qdisc_ops gred_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"gred",
	.priv_size	=	माप(काष्ठा gred_sched),
	.enqueue	=	gred_enqueue,
	.dequeue	=	gred_dequeue,
	.peek		=	qdisc_peek_head,
	.init		=	gred_init,
	.reset		=	gred_reset,
	.destroy	=	gred_destroy,
	.change		=	gred_change,
	.dump		=	gred_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init gred_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&gred_qdisc_ops);
पूर्ण

अटल व्योम __निकास gred_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&gred_qdisc_ops);
पूर्ण

module_init(gred_module_init)
module_निकास(gred_module_निकास)

MODULE_LICENSE("GPL");
