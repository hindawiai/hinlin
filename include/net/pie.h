<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __NET_SCHED_PIE_H
#घोषणा __NET_SCHED_PIE_H

#समावेश <linux/kसमय.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/pkt_sched.h>

#घोषणा MAX_PROB	(U64_MAX >> BITS_PER_BYTE)
#घोषणा DTIME_INVALID	U64_MAX
#घोषणा QUEUE_THRESHOLD	16384
#घोषणा DQCOUNT_INVALID	-1
#घोषणा PIE_SCALE	8

/**
 * काष्ठा pie_params - contains pie parameters
 * @target:		target delay in pschedसमय
 * @tudpate:		पूर्णांकerval at which drop probability is calculated
 * @limit:		total number of packets that can be in the queue
 * @alpha:		parameter to control drop probability
 * @beta:		parameter to control drop probability
 * @ecn:		is ECN marking of packets enabled
 * @bytemode:		is drop probability scaled based on pkt size
 * @dq_rate_estimator:	is Little's law used क्रम qdelay calculation
 */
काष्ठा pie_params अणु
	psched_समय_प्रकार target;
	u32 tupdate;
	u32 limit;
	u32 alpha;
	u32 beta;
	u8 ecn;
	u8 bytemode;
	u8 dq_rate_estimator;
पूर्ण;

/**
 * काष्ठा pie_vars - contains pie variables
 * @qdelay:		current queue delay
 * @qdelay_old:		queue delay in previous qdelay calculation
 * @burst_समय:		burst समय allowance
 * @dq_tstamp:		बारtamp at which dq rate was last calculated
 * @prob:		drop probability
 * @accu_prob:		accumulated drop probability
 * @dq_count:		number of bytes dequeued in a measurement cycle
 * @avg_dq_rate:	calculated average dq rate
 * @backlog_old:	queue backlog during previous qdelay calculation
 */
काष्ठा pie_vars अणु
	psched_समय_प्रकार qdelay;
	psched_समय_प्रकार qdelay_old;
	psched_समय_प्रकार burst_समय;
	psched_समय_प्रकार dq_tstamp;
	u64 prob;
	u64 accu_prob;
	u64 dq_count;
	u32 avg_dq_rate;
	u32 backlog_old;
पूर्ण;

/**
 * काष्ठा pie_stats - contains pie stats
 * @packets_in:	total number of packets enqueued
 * @dropped:	packets dropped due to pie action
 * @overlimit:	packets dropped due to lack of space in queue
 * @ecn_mark:	packets marked with ECN
 * @maxq:	maximum queue size
 */
काष्ठा pie_stats अणु
	u32 packets_in;
	u32 dropped;
	u32 overlimit;
	u32 ecn_mark;
	u32 maxq;
पूर्ण;

/**
 * काष्ठा pie_skb_cb - contains निजी skb vars
 * @enqueue_समय:	बारtamp when the packet is enqueued
 * @mem_usage:		size of the skb during enqueue
 */
काष्ठा pie_skb_cb अणु
	psched_समय_प्रकार enqueue_समय;
	u32 mem_usage;
पूर्ण;

अटल अंतरभूत व्योम pie_params_init(काष्ठा pie_params *params)
अणु
	params->target = PSCHED_NS2TICKS(15 * NSEC_PER_MSEC);	/* 15 ms */
	params->tupdate = usecs_to_jअगरfies(15 * USEC_PER_MSEC);	/* 15 ms */
	params->limit = 1000;
	params->alpha = 2;
	params->beta = 20;
	params->ecn = false;
	params->bytemode = false;
	params->dq_rate_estimator = false;
पूर्ण

अटल अंतरभूत व्योम pie_vars_init(काष्ठा pie_vars *vars)
अणु
	vars->burst_समय = PSCHED_NS2TICKS(150 * NSEC_PER_MSEC); /* 150 ms */
	vars->dq_tstamp = DTIME_INVALID;
	vars->accu_prob = 0;
	vars->dq_count = DQCOUNT_INVALID;
	vars->avg_dq_rate = 0;
पूर्ण

अटल अंतरभूत काष्ठा pie_skb_cb *get_pie_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	qdisc_cb_निजी_validate(skb, माप(काष्ठा pie_skb_cb));
	वापस (काष्ठा pie_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

अटल अंतरभूत psched_समय_प्रकार pie_get_enqueue_समय(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस get_pie_cb(skb)->enqueue_समय;
पूर्ण

अटल अंतरभूत व्योम pie_set_enqueue_समय(काष्ठा sk_buff *skb)
अणु
	get_pie_cb(skb)->enqueue_समय = psched_get_समय();
पूर्ण

bool pie_drop_early(काष्ठा Qdisc *sch, काष्ठा pie_params *params,
		    काष्ठा pie_vars *vars, u32 backlog, u32 packet_size);

व्योम pie_process_dequeue(काष्ठा sk_buff *skb, काष्ठा pie_params *params,
			 काष्ठा pie_vars *vars, u32 backlog);

व्योम pie_calculate_probability(काष्ठा pie_params *params, काष्ठा pie_vars *vars,
			       u32 backlog);

#पूर्ण_अगर
