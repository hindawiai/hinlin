<शैली गुरु>
/*
 * Codel - The Controlled-Delay Active Queue Management algorithm
 *
 *  Copyright (C) 2011-2012 Kathleen Nichols <nichols@pollere.com>
 *  Copyright (C) 2011-2012 Van Jacobson <van@pollere.net>
 *
 *  Implemented on linux by :
 *  Copyright (C) 2012 Michael D. Taht <dave.taht@bufferbloat.net>
 *  Copyright (C) 2012,2015 Eric Dumazet <edumazet@google.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the authors may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/prefetch.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/codel.h>
#समावेश <net/codel_impl.h>
#समावेश <net/codel_qdisc.h>


#घोषणा DEFAULT_CODEL_LIMIT 1000

काष्ठा codel_sched_data अणु
	काष्ठा codel_params	params;
	काष्ठा codel_vars	vars;
	काष्ठा codel_stats	stats;
	u32			drop_overlimit;
पूर्ण;

/* This is the specअगरic function called from codel_dequeue()
 * to dequeue a packet from queue. Note: backlog is handled in
 * codel, we करोnt need to reduce it here.
 */
अटल काष्ठा sk_buff *dequeue_func(काष्ठा codel_vars *vars, व्योम *ctx)
अणु
	काष्ठा Qdisc *sch = ctx;
	काष्ठा sk_buff *skb = __qdisc_dequeue_head(&sch->q);

	अगर (skb) अणु
		sch->qstats.backlog -= qdisc_pkt_len(skb);
		prefetch(&skb->end); /* we'll need skb_shinfo() */
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम drop_func(काष्ठा sk_buff *skb, व्योम *ctx)
अणु
	काष्ठा Qdisc *sch = ctx;

	kमुक्त_skb(skb);
	qdisc_qstats_drop(sch);
पूर्ण

अटल काष्ठा sk_buff *codel_qdisc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा codel_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

	skb = codel_dequeue(sch, &sch->qstats.backlog, &q->params, &q->vars,
			    &q->stats, qdisc_pkt_len, codel_get_enqueue_समय,
			    drop_func, dequeue_func);

	/* We cant call qdisc_tree_reduce_backlog() अगर our qlen is 0,
	 * or HTB crashes. Defer it क्रम next round.
	 */
	अगर (q->stats.drop_count && sch->q.qlen) अणु
		qdisc_tree_reduce_backlog(sch, q->stats.drop_count, q->stats.drop_len);
		q->stats.drop_count = 0;
		q->stats.drop_len = 0;
	पूर्ण
	अगर (skb)
		qdisc_bstats_update(sch, skb);
	वापस skb;
पूर्ण

अटल पूर्णांक codel_qdisc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			       काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा codel_sched_data *q;

	अगर (likely(qdisc_qlen(sch) < sch->limit)) अणु
		codel_set_enqueue_समय(skb);
		वापस qdisc_enqueue_tail(skb, sch);
	पूर्ण
	q = qdisc_priv(sch);
	q->drop_overlimit++;
	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल स्थिर काष्ठा nla_policy codel_policy[TCA_CODEL_MAX + 1] = अणु
	[TCA_CODEL_TARGET]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_CODEL_LIMIT]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_CODEL_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_CODEL_ECN]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_CODEL_CE_THRESHOLD]= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक codel_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा codel_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_CODEL_MAX + 1];
	अचिन्हित पूर्णांक qlen, dropped = 0;
	पूर्णांक err;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_CODEL_MAX, opt,
					  codel_policy, शून्य);
	अगर (err < 0)
		वापस err;

	sch_tree_lock(sch);

	अगर (tb[TCA_CODEL_TARGET]) अणु
		u32 target = nla_get_u32(tb[TCA_CODEL_TARGET]);

		q->params.target = ((u64)target * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_CODEL_CE_THRESHOLD]) अणु
		u64 val = nla_get_u32(tb[TCA_CODEL_CE_THRESHOLD]);

		q->params.ce_threshold = (val * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_CODEL_INTERVAL]) अणु
		u32 पूर्णांकerval = nla_get_u32(tb[TCA_CODEL_INTERVAL]);

		q->params.पूर्णांकerval = ((u64)पूर्णांकerval * NSEC_PER_USEC) >> CODEL_SHIFT;
	पूर्ण

	अगर (tb[TCA_CODEL_LIMIT])
		sch->limit = nla_get_u32(tb[TCA_CODEL_LIMIT]);

	अगर (tb[TCA_CODEL_ECN])
		q->params.ecn = !!nla_get_u32(tb[TCA_CODEL_ECN]);

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

अटल पूर्णांक codel_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा codel_sched_data *q = qdisc_priv(sch);

	sch->limit = DEFAULT_CODEL_LIMIT;

	codel_params_init(&q->params);
	codel_vars_init(&q->vars);
	codel_stats_init(&q->stats);
	q->params.mtu = psched_mtu(qdisc_dev(sch));

	अगर (opt) अणु
		पूर्णांक err = codel_change(sch, opt, extack);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (sch->limit >= 1)
		sch->flags |= TCQ_F_CAN_BYPASS;
	अन्यथा
		sch->flags &= ~TCQ_F_CAN_BYPASS;

	वापस 0;
पूर्ण

अटल पूर्णांक codel_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा codel_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_CODEL_TARGET,
			codel_समय_प्रकारo_us(q->params.target)) ||
	    nla_put_u32(skb, TCA_CODEL_LIMIT,
			sch->limit) ||
	    nla_put_u32(skb, TCA_CODEL_INTERVAL,
			codel_समय_प्रकारo_us(q->params.पूर्णांकerval)) ||
	    nla_put_u32(skb, TCA_CODEL_ECN,
			q->params.ecn))
		जाओ nla_put_failure;
	अगर (q->params.ce_threshold != CODEL_DISABLED_THRESHOLD &&
	    nla_put_u32(skb, TCA_CODEL_CE_THRESHOLD,
			codel_समय_प्रकारo_us(q->params.ce_threshold)))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -1;
पूर्ण

अटल पूर्णांक codel_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	स्थिर काष्ठा codel_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_codel_xstats st = अणु
		.maxpacket	= q->stats.maxpacket,
		.count		= q->vars.count,
		.lastcount	= q->vars.lastcount,
		.drop_overlimit = q->drop_overlimit,
		.ldelay		= codel_समय_प्रकारo_us(q->vars.ldelay),
		.dropping	= q->vars.dropping,
		.ecn_mark	= q->stats.ecn_mark,
		.ce_mark	= q->stats.ce_mark,
	पूर्ण;

	अगर (q->vars.dropping) अणु
		codel_tdअगरf_t delta = q->vars.drop_next - codel_get_समय();

		अगर (delta >= 0)
			st.drop_next = codel_समय_प्रकारo_us(delta);
		अन्यथा
			st.drop_next = -codel_समय_प्रकारo_us(-delta);
	पूर्ण

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल व्योम codel_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा codel_sched_data *q = qdisc_priv(sch);

	qdisc_reset_queue(sch);
	codel_vars_init(&q->vars);
पूर्ण

अटल काष्ठा Qdisc_ops codel_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"codel",
	.priv_size	=	माप(काष्ठा codel_sched_data),

	.enqueue	=	codel_qdisc_enqueue,
	.dequeue	=	codel_qdisc_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	codel_init,
	.reset		=	codel_reset,
	.change 	=	codel_change,
	.dump		=	codel_dump,
	.dump_stats	=	codel_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init codel_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&codel_qdisc_ops);
पूर्ण

अटल व्योम __निकास codel_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&codel_qdisc_ops);
पूर्ण

module_init(codel_module_init)
module_निकास(codel_module_निकास)

MODULE_DESCRIPTION("Controlled Delay queue discipline");
MODULE_AUTHOR("Dave Taht");
MODULE_AUTHOR("Eric Dumazet");
MODULE_LICENSE("Dual BSD/GPL");
