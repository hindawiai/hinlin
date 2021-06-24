<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2013 Cisco Systems, Inc, 2013.
 *
 * Author: Vijay Subramanian <vijaynsu@cisco.com>
 * Author: Mythili Prabhu <mysuryan@cisco.com>
 *
 * ECN support is added by Naeem Khademi <naeemk@अगरi.uio.no>
 * University of Oslo, Norway.
 *
 * References:
 * RFC 8033: https://tools.ietf.org/hपंचांगl/rfc8033
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/pie.h>

/* निजी data क्रम the Qdisc */
काष्ठा pie_sched_data अणु
	काष्ठा pie_vars vars;
	काष्ठा pie_params params;
	काष्ठा pie_stats stats;
	काष्ठा समयr_list adapt_समयr;
	काष्ठा Qdisc *sch;
पूर्ण;

bool pie_drop_early(काष्ठा Qdisc *sch, काष्ठा pie_params *params,
		    काष्ठा pie_vars *vars, u32 backlog, u32 packet_size)
अणु
	u64 rnd;
	u64 local_prob = vars->prob;
	u32 mtu = psched_mtu(qdisc_dev(sch));

	/* If there is still burst allowance left skip अक्रमom early drop */
	अगर (vars->burst_समय > 0)
		वापस false;

	/* If current delay is less than half of target, and
	 * अगर drop prob is low alपढ़ोy, disable early_drop
	 */
	अगर ((vars->qdelay < params->target / 2) &&
	    (vars->prob < MAX_PROB / 5))
		वापस false;

	/* If we have fewer than 2 mtu-sized packets, disable pie_drop_early,
	 * similar to min_th in RED
	 */
	अगर (backlog < 2 * mtu)
		वापस false;

	/* If bytemode is turned on, use packet size to compute new
	 * probablity. Smaller packets will have lower drop prob in this हाल
	 */
	अगर (params->bytemode && packet_size <= mtu)
		local_prob = (u64)packet_size * भाग_u64(local_prob, mtu);
	अन्यथा
		local_prob = vars->prob;

	अगर (local_prob == 0)
		vars->accu_prob = 0;
	अन्यथा
		vars->accu_prob += local_prob;

	अगर (vars->accu_prob < (MAX_PROB / 100) * 85)
		वापस false;
	अगर (vars->accu_prob >= (MAX_PROB / 2) * 17)
		वापस true;

	pअक्रमom_bytes(&rnd, 8);
	अगर ((rnd >> BITS_PER_BYTE) < local_prob) अणु
		vars->accu_prob = 0;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(pie_drop_early);

अटल पूर्णांक pie_qdisc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			     काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);
	bool enqueue = false;

	अगर (unlikely(qdisc_qlen(sch) >= sch->limit)) अणु
		q->stats.overlimit++;
		जाओ out;
	पूर्ण

	अगर (!pie_drop_early(sch, &q->params, &q->vars, sch->qstats.backlog,
			    skb->len)) अणु
		enqueue = true;
	पूर्ण अन्यथा अगर (q->params.ecn && (q->vars.prob <= MAX_PROB / 10) &&
		   INET_ECN_set_ce(skb)) अणु
		/* If packet is ecn capable, mark it अगर drop probability
		 * is lower than 10%, अन्यथा drop it.
		 */
		q->stats.ecn_mark++;
		enqueue = true;
	पूर्ण

	/* we can enqueue the packet */
	अगर (enqueue) अणु
		/* Set enqueue समय only when dq_rate_estimator is disabled. */
		अगर (!q->params.dq_rate_estimator)
			pie_set_enqueue_समय(skb);

		q->stats.packets_in++;
		अगर (qdisc_qlen(sch) > q->stats.maxq)
			q->stats.maxq = qdisc_qlen(sch);

		वापस qdisc_enqueue_tail(skb, sch);
	पूर्ण

out:
	q->stats.dropped++;
	q->vars.accu_prob = 0;
	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल स्थिर काष्ठा nla_policy pie_policy[TCA_PIE_MAX + 1] = अणु
	[TCA_PIE_TARGET]		= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_LIMIT]			= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_TUPDATE]		= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_ALPHA]			= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_BETA]			= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_ECN]			= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_BYTEMODE]		= अणु.type = NLA_U32पूर्ण,
	[TCA_PIE_DQ_RATE_ESTIMATOR]	= अणु.type = NLA_U32पूर्ण,
पूर्ण;

अटल पूर्णांक pie_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_PIE_MAX + 1];
	अचिन्हित पूर्णांक qlen, dropped = 0;
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_PIE_MAX, opt, pie_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	sch_tree_lock(sch);

	/* convert from microseconds to pschedसमय */
	अगर (tb[TCA_PIE_TARGET]) अणु
		/* target is in us */
		u32 target = nla_get_u32(tb[TCA_PIE_TARGET]);

		/* convert to pschedसमय */
		q->params.target = PSCHED_NS2TICKS((u64)target * NSEC_PER_USEC);
	पूर्ण

	/* tupdate is in jअगरfies */
	अगर (tb[TCA_PIE_TUPDATE])
		q->params.tupdate =
			usecs_to_jअगरfies(nla_get_u32(tb[TCA_PIE_TUPDATE]));

	अगर (tb[TCA_PIE_LIMIT]) अणु
		u32 limit = nla_get_u32(tb[TCA_PIE_LIMIT]);

		q->params.limit = limit;
		sch->limit = limit;
	पूर्ण

	अगर (tb[TCA_PIE_ALPHA])
		q->params.alpha = nla_get_u32(tb[TCA_PIE_ALPHA]);

	अगर (tb[TCA_PIE_BETA])
		q->params.beta = nla_get_u32(tb[TCA_PIE_BETA]);

	अगर (tb[TCA_PIE_ECN])
		q->params.ecn = nla_get_u32(tb[TCA_PIE_ECN]);

	अगर (tb[TCA_PIE_BYTEMODE])
		q->params.bytemode = nla_get_u32(tb[TCA_PIE_BYTEMODE]);

	अगर (tb[TCA_PIE_DQ_RATE_ESTIMATOR])
		q->params.dq_rate_estimator =
				nla_get_u32(tb[TCA_PIE_DQ_RATE_ESTIMATOR]);

	/* Drop excess packets अगर new limit is lower */
	qlen = sch->q.qlen;
	जबतक (sch->q.qlen > sch->limit) अणु
		काष्ठा sk_buff *skb = __qdisc_dequeue_head(&sch->q);

		dropped += qdisc_pkt_len(skb);
		qdisc_qstats_backlog_dec(sch, skb);
		rtnl_qdisc_drop(skb, sch);
	पूर्ण
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen, dropped);

	sch_tree_unlock(sch);
	वापस 0;
पूर्ण

व्योम pie_process_dequeue(काष्ठा sk_buff *skb, काष्ठा pie_params *params,
			 काष्ठा pie_vars *vars, u32 backlog)
अणु
	psched_समय_प्रकार now = psched_get_समय();
	u32 dसमय = 0;

	/* If dq_rate_estimator is disabled, calculate qdelay using the
	 * packet बारtamp.
	 */
	अगर (!params->dq_rate_estimator) अणु
		vars->qdelay = now - pie_get_enqueue_समय(skb);

		अगर (vars->dq_tstamp != DTIME_INVALID)
			dसमय = now - vars->dq_tstamp;

		vars->dq_tstamp = now;

		अगर (backlog == 0)
			vars->qdelay = 0;

		अगर (dसमय == 0)
			वापस;

		जाओ burst_allowance_reduction;
	पूर्ण

	/* If current queue is about 10 packets or more and dq_count is unset
	 * we have enough packets to calculate the drain rate. Save
	 * current समय as dq_tstamp and start measurement cycle.
	 */
	अगर (backlog >= QUEUE_THRESHOLD && vars->dq_count == DQCOUNT_INVALID) अणु
		vars->dq_tstamp = psched_get_समय();
		vars->dq_count = 0;
	पूर्ण

	/* Calculate the average drain rate from this value. If queue length
	 * has receded to a small value viz., <= QUEUE_THRESHOLD bytes, reset
	 * the dq_count to -1 as we करोn't have enough packets to calculate the
	 * drain rate anymore. The following अगर block is entered only when we
	 * have a substantial queue built up (QUEUE_THRESHOLD bytes or more)
	 * and we calculate the drain rate क्रम the threshold here.  dq_count is
	 * in bytes, समय dअगरference in psched_समय, hence rate is in
	 * bytes/psched_समय.
	 */
	अगर (vars->dq_count != DQCOUNT_INVALID) अणु
		vars->dq_count += skb->len;

		अगर (vars->dq_count >= QUEUE_THRESHOLD) अणु
			u32 count = vars->dq_count << PIE_SCALE;

			dसमय = now - vars->dq_tstamp;

			अगर (dसमय == 0)
				वापस;

			count = count / dसमय;

			अगर (vars->avg_dq_rate == 0)
				vars->avg_dq_rate = count;
			अन्यथा
				vars->avg_dq_rate =
				    (vars->avg_dq_rate -
				     (vars->avg_dq_rate >> 3)) + (count >> 3);

			/* If the queue has receded below the threshold, we hold
			 * on to the last drain rate calculated, अन्यथा we reset
			 * dq_count to 0 to re-enter the अगर block when the next
			 * packet is dequeued
			 */
			अगर (backlog < QUEUE_THRESHOLD) अणु
				vars->dq_count = DQCOUNT_INVALID;
			पूर्ण अन्यथा अणु
				vars->dq_count = 0;
				vars->dq_tstamp = psched_get_समय();
			पूर्ण

			जाओ burst_allowance_reduction;
		पूर्ण
	पूर्ण

	वापस;

burst_allowance_reduction:
	अगर (vars->burst_समय > 0) अणु
		अगर (vars->burst_समय > dसमय)
			vars->burst_समय -= dसमय;
		अन्यथा
			vars->burst_समय = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pie_process_dequeue);

व्योम pie_calculate_probability(काष्ठा pie_params *params, काष्ठा pie_vars *vars,
			       u32 backlog)
अणु
	psched_समय_प्रकार qdelay = 0;	/* in pschedसमय */
	psched_समय_प्रकार qdelay_old = 0;	/* in pschedसमय */
	s64 delta = 0;		/* determines the change in probability */
	u64 oldprob;
	u64 alpha, beta;
	u32 घातer;
	bool update_prob = true;

	अगर (params->dq_rate_estimator) अणु
		qdelay_old = vars->qdelay;
		vars->qdelay_old = vars->qdelay;

		अगर (vars->avg_dq_rate > 0)
			qdelay = (backlog << PIE_SCALE) / vars->avg_dq_rate;
		अन्यथा
			qdelay = 0;
	पूर्ण अन्यथा अणु
		qdelay = vars->qdelay;
		qdelay_old = vars->qdelay_old;
	पूर्ण

	/* If qdelay is zero and backlog is not, it means backlog is very small,
	 * so we करो not update probabilty in this round.
	 */
	अगर (qdelay == 0 && backlog != 0)
		update_prob = false;

	/* In the algorithm, alpha and beta are between 0 and 2 with typical
	 * value क्रम alpha as 0.125. In this implementation, we use values 0-32
	 * passed from user space to represent this. Also, alpha and beta have
	 * unit of HZ and need to be scaled beक्रमe they can used to update
	 * probability. alpha/beta are updated locally below by scaling करोwn
	 * by 16 to come to 0-2 range.
	 */
	alpha = ((u64)params->alpha * (MAX_PROB / PSCHED_TICKS_PER_SEC)) >> 4;
	beta = ((u64)params->beta * (MAX_PROB / PSCHED_TICKS_PER_SEC)) >> 4;

	/* We scale alpha and beta dअगरferently depending on how heavy the
	 * congestion is. Please see RFC 8033 क्रम details.
	 */
	अगर (vars->prob < MAX_PROB / 10) अणु
		alpha >>= 1;
		beta >>= 1;

		घातer = 100;
		जबतक (vars->prob < भाग_u64(MAX_PROB, घातer) &&
		       घातer <= 1000000) अणु
			alpha >>= 2;
			beta >>= 2;
			घातer *= 10;
		पूर्ण
	पूर्ण

	/* alpha and beta should be between 0 and 32, in multiples of 1/16 */
	delta += alpha * (qdelay - params->target);
	delta += beta * (qdelay - qdelay_old);

	oldprob = vars->prob;

	/* to ensure we increase probability in steps of no more than 2% */
	अगर (delta > (s64)(MAX_PROB / (100 / 2)) &&
	    vars->prob >= MAX_PROB / 10)
		delta = (MAX_PROB / 100) * 2;

	/* Non-linear drop:
	 * Tune drop probability to increase quickly क्रम high delays(>= 250ms)
	 * 250ms is derived through experiments and provides error protection
	 */

	अगर (qdelay > (PSCHED_NS2TICKS(250 * NSEC_PER_MSEC)))
		delta += MAX_PROB / (100 / 2);

	vars->prob += delta;

	अगर (delta > 0) अणु
		/* prevent overflow */
		अगर (vars->prob < oldprob) अणु
			vars->prob = MAX_PROB;
			/* Prevent normalization error. If probability is at
			 * maximum value alपढ़ोy, we normalize it here, and
			 * skip the check to करो a non-linear drop in the next
			 * section.
			 */
			update_prob = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* prevent underflow */
		अगर (vars->prob > oldprob)
			vars->prob = 0;
	पूर्ण

	/* Non-linear drop in probability: Reduce drop probability quickly अगर
	 * delay is 0 क्रम 2 consecutive Tupdate periods.
	 */

	अगर (qdelay == 0 && qdelay_old == 0 && update_prob)
		/* Reduce drop probability to 98.4% */
		vars->prob -= vars->prob / 64;

	vars->qdelay = qdelay;
	vars->backlog_old = backlog;

	/* We restart the measurement cycle अगर the following conditions are met
	 * 1. If the delay has been low क्रम 2 consecutive Tupdate periods
	 * 2. Calculated drop probability is zero
	 * 3. If average dq_rate_estimator is enabled, we have at least one
	 *    estimate क्रम the avg_dq_rate ie., is a non-zero value
	 */
	अगर ((vars->qdelay < params->target / 2) &&
	    (vars->qdelay_old < params->target / 2) &&
	    vars->prob == 0 &&
	    (!params->dq_rate_estimator || vars->avg_dq_rate > 0)) अणु
		pie_vars_init(vars);
	पूर्ण

	अगर (!params->dq_rate_estimator)
		vars->qdelay_old = qdelay;
पूर्ण
EXPORT_SYMBOL_GPL(pie_calculate_probability);

अटल व्योम pie_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pie_sched_data *q = from_समयr(q, t, adapt_समयr);
	काष्ठा Qdisc *sch = q->sch;
	spinlock_t *root_lock = qdisc_lock(qdisc_root_sleeping(sch));

	spin_lock(root_lock);
	pie_calculate_probability(&q->params, &q->vars, sch->qstats.backlog);

	/* reset the समयr to fire after 'tupdate'. tupdate is in jअगरfies. */
	अगर (q->params.tupdate)
		mod_समयr(&q->adapt_समयr, jअगरfies + q->params.tupdate);
	spin_unlock(root_lock);
पूर्ण

अटल पूर्णांक pie_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);

	pie_params_init(&q->params);
	pie_vars_init(&q->vars);
	sch->limit = q->params.limit;

	q->sch = sch;
	समयr_setup(&q->adapt_समयr, pie_समयr, 0);

	अगर (opt) अणु
		पूर्णांक err = pie_change(sch, opt, extack);

		अगर (err)
			वापस err;
	पूर्ण

	mod_समयr(&q->adapt_समयr, jअगरfies + HZ / 2);
	वापस 0;
पूर्ण

अटल पूर्णांक pie_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!opts)
		जाओ nla_put_failure;

	/* convert target from pschedसमय to us */
	अगर (nla_put_u32(skb, TCA_PIE_TARGET,
			((u32)PSCHED_TICKS2NS(q->params.target)) /
			NSEC_PER_USEC) ||
	    nla_put_u32(skb, TCA_PIE_LIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_PIE_TUPDATE,
			jअगरfies_to_usecs(q->params.tupdate)) ||
	    nla_put_u32(skb, TCA_PIE_ALPHA, q->params.alpha) ||
	    nla_put_u32(skb, TCA_PIE_BETA, q->params.beta) ||
	    nla_put_u32(skb, TCA_PIE_ECN, q->params.ecn) ||
	    nla_put_u32(skb, TCA_PIE_BYTEMODE, q->params.bytemode) ||
	    nla_put_u32(skb, TCA_PIE_DQ_RATE_ESTIMATOR,
			q->params.dq_rate_estimator))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -1;
पूर्ण

अटल पूर्णांक pie_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_pie_xstats st = अणु
		.prob		= q->vars.prob << BITS_PER_BYTE,
		.delay		= ((u32)PSCHED_TICKS2NS(q->vars.qdelay)) /
				   NSEC_PER_USEC,
		.packets_in	= q->stats.packets_in,
		.overlimit	= q->stats.overlimit,
		.maxq		= q->stats.maxq,
		.dropped	= q->stats.dropped,
		.ecn_mark	= q->stats.ecn_mark,
	पूर्ण;

	/* avg_dq_rate is only valid अगर dq_rate_estimator is enabled */
	st.dq_rate_estimating = q->params.dq_rate_estimator;

	/* unscale and वापस dq_rate in bytes per sec */
	अगर (q->params.dq_rate_estimator)
		st.avg_dq_rate = q->vars.avg_dq_rate *
				 (PSCHED_TICKS_PER_SEC) >> PIE_SCALE;

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल काष्ठा sk_buff *pie_qdisc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb = qdisc_dequeue_head(sch);

	अगर (!skb)
		वापस शून्य;

	pie_process_dequeue(skb, &q->params, &q->vars, sch->qstats.backlog);
	वापस skb;
पूर्ण

अटल व्योम pie_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);

	qdisc_reset_queue(sch);
	pie_vars_init(&q->vars);
पूर्ण

अटल व्योम pie_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा pie_sched_data *q = qdisc_priv(sch);

	q->params.tupdate = 0;
	del_समयr_sync(&q->adapt_समयr);
पूर्ण

अटल काष्ठा Qdisc_ops pie_qdisc_ops __पढ़ो_mostly = अणु
	.id		= "pie",
	.priv_size	= माप(काष्ठा pie_sched_data),
	.enqueue	= pie_qdisc_enqueue,
	.dequeue	= pie_qdisc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= pie_init,
	.destroy	= pie_destroy,
	.reset		= pie_reset,
	.change		= pie_change,
	.dump		= pie_dump,
	.dump_stats	= pie_dump_stats,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pie_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&pie_qdisc_ops);
पूर्ण

अटल व्योम __निकास pie_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&pie_qdisc_ops);
पूर्ण

module_init(pie_module_init);
module_निकास(pie_module_निकास);

MODULE_DESCRIPTION("Proportional Integral controller Enhanced (PIE) scheduler");
MODULE_AUTHOR("Vijay Subramanian");
MODULE_AUTHOR("Mythili Prabhu");
MODULE_LICENSE("GPL");
