<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP Illinois congestion control.
 * Home page:
 *	http://www.ews.uiuc.edu/~shaoliu/tcpillinois/index.hपंचांगl
 *
 * The algorithm is described in:
 * "TCP-Illinois: A Loss and Delay-Based Congestion Control Algorithm
 *  क्रम High-Speed Networks"
 * http://tamerbasar.csl.illinois.edu/LiuBasarSrikantPerfEvalArtJun2008.pdf
 *
 * Implemented from description in paper and ns-2 simulation.
 * Copyright (C) 2007 Stephen Hemminger <shemminger@linux-foundation.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet_diag.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <net/tcp.h>

#घोषणा ALPHA_SHIFT	7
#घोषणा ALPHA_SCALE	(1u<<ALPHA_SHIFT)
#घोषणा ALPHA_MIN	((3*ALPHA_SCALE)/10)	/* ~0.3 */
#घोषणा ALPHA_MAX	(10*ALPHA_SCALE)	/* 10.0 */
#घोषणा ALPHA_BASE	ALPHA_SCALE		/* 1.0 */
#घोषणा RTT_MAX		(U32_MAX / ALPHA_MAX)	/* 3.3 secs */

#घोषणा BETA_SHIFT	6
#घोषणा BETA_SCALE	(1u<<BETA_SHIFT)
#घोषणा BETA_MIN	(BETA_SCALE/8)		/* 0.125 */
#घोषणा BETA_MAX	(BETA_SCALE/2)		/* 0.5 */
#घोषणा BETA_BASE	BETA_MAX

अटल पूर्णांक win_thresh __पढ़ो_mostly = 15;
module_param(win_thresh, पूर्णांक, 0);
MODULE_PARM_DESC(win_thresh, "Window threshold for starting adaptive sizing");

अटल पूर्णांक theta __पढ़ो_mostly = 5;
module_param(theta, पूर्णांक, 0);
MODULE_PARM_DESC(theta, "# of fast RTT's before full growth");

/* TCP Illinois Parameters */
काष्ठा illinois अणु
	u64	sum_rtt;	/* sum of rtt's measured within last rtt */
	u16	cnt_rtt;	/* # of rtts measured within last rtt */
	u32	base_rtt;	/* min of all rtt in usec */
	u32	max_rtt;	/* max of all rtt in usec */
	u32	end_seq;	/* right edge of current RTT */
	u32	alpha;		/* Additive increase */
	u32	beta;		/* Muliplicative decrease */
	u16	acked;		/* # packets acked by current ACK */
	u8	rtt_above;	/* average rtt has gone above threshold */
	u8	rtt_low;	/* # of rtts measurements below threshold */
पूर्ण;

अटल व्योम rtt_reset(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा illinois *ca = inet_csk_ca(sk);

	ca->end_seq = tp->snd_nxt;
	ca->cnt_rtt = 0;
	ca->sum_rtt = 0;

	/* TODO: age max_rtt? */
पूर्ण

अटल व्योम tcp_illinois_init(काष्ठा sock *sk)
अणु
	काष्ठा illinois *ca = inet_csk_ca(sk);

	ca->alpha = ALPHA_MAX;
	ca->beta = BETA_BASE;
	ca->base_rtt = 0x7fffffff;
	ca->max_rtt = 0;

	ca->acked = 0;
	ca->rtt_low = 0;
	ca->rtt_above = 0;

	rtt_reset(sk);
पूर्ण

/* Measure RTT क्रम each ack. */
अटल व्योम tcp_illinois_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा illinois *ca = inet_csk_ca(sk);
	s32 rtt_us = sample->rtt_us;

	ca->acked = sample->pkts_acked;

	/* dup ack, no rtt sample */
	अगर (rtt_us < 0)
		वापस;

	/* ignore bogus values, this prevents wraparound in alpha math */
	अगर (rtt_us > RTT_MAX)
		rtt_us = RTT_MAX;

	/* keep track of minimum RTT seen so far */
	अगर (ca->base_rtt > rtt_us)
		ca->base_rtt = rtt_us;

	/* and max */
	अगर (ca->max_rtt < rtt_us)
		ca->max_rtt = rtt_us;

	++ca->cnt_rtt;
	ca->sum_rtt += rtt_us;
पूर्ण

/* Maximum queuing delay */
अटल अंतरभूत u32 max_delay(स्थिर काष्ठा illinois *ca)
अणु
	वापस ca->max_rtt - ca->base_rtt;
पूर्ण

/* Average queuing delay */
अटल अंतरभूत u32 avg_delay(स्थिर काष्ठा illinois *ca)
अणु
	u64 t = ca->sum_rtt;

	करो_भाग(t, ca->cnt_rtt);
	वापस t - ca->base_rtt;
पूर्ण

/*
 * Compute value of alpha used क्रम additive increase.
 * If small winकरोw then use 1.0, equivalent to Reno.
 *
 * For larger winकरोws, adjust based on average delay.
 * A. If average delay is at minimum (we are uncongested),
 *    then use large alpha (10.0) to increase faster.
 * B. If average delay is at maximum (getting congested)
 *    then use small alpha (0.3)
 *
 * The result is a convex winकरोw growth curve.
 */
अटल u32 alpha(काष्ठा illinois *ca, u32 da, u32 dm)
अणु
	u32 d1 = dm / 100;	/* Low threshold */

	अगर (da <= d1) अणु
		/* If never got out of low delay zone, then use max */
		अगर (!ca->rtt_above)
			वापस ALPHA_MAX;

		/* Wait क्रम 5 good RTT's beक्रमe allowing alpha to go alpha max.
		 * This prevents one good RTT from causing sudden winकरोw increase.
		 */
		अगर (++ca->rtt_low < theta)
			वापस ca->alpha;

		ca->rtt_low = 0;
		ca->rtt_above = 0;
		वापस ALPHA_MAX;
	पूर्ण

	ca->rtt_above = 1;

	/*
	 * Based on:
	 *
	 *      (dm - d1) amin amax
	 * k1 = -------------------
	 *         amax - amin
	 *
	 *       (dm - d1) amin
	 * k2 = ----------------  - d1
	 *        amax - amin
	 *
	 *             k1
	 * alpha = ----------
	 *          k2 + da
	 */

	dm -= d1;
	da -= d1;
	वापस (dm * ALPHA_MAX) /
		(dm + (da  * (ALPHA_MAX - ALPHA_MIN)) / ALPHA_MIN);
पूर्ण

/*
 * Beta used क्रम multiplicative decrease.
 * For small winकरोw sizes वापसs same value as Reno (0.5)
 *
 * If delay is small (10% of max) then beta = 1/8
 * If delay is up to 80% of max then beta = 1/2
 * In between is a linear function
 */
अटल u32 beta(u32 da, u32 dm)
अणु
	u32 d2, d3;

	d2 = dm / 10;
	अगर (da <= d2)
		वापस BETA_MIN;

	d3 = (8 * dm) / 10;
	अगर (da >= d3 || d3 <= d2)
		वापस BETA_MAX;

	/*
	 * Based on:
	 *
	 *       bmin d3 - bmax d2
	 * k3 = -------------------
	 *         d3 - d2
	 *
	 *       bmax - bmin
	 * k4 = -------------
	 *         d3 - d2
	 *
	 * b = k3 + k4 da
	 */
	वापस (BETA_MIN * d3 - BETA_MAX * d2 + (BETA_MAX - BETA_MIN) * da)
		/ (d3 - d2);
पूर्ण

/* Update alpha and beta values once per RTT */
अटल व्योम update_params(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा illinois *ca = inet_csk_ca(sk);

	अगर (tp->snd_cwnd < win_thresh) अणु
		ca->alpha = ALPHA_BASE;
		ca->beta = BETA_BASE;
	पूर्ण अन्यथा अगर (ca->cnt_rtt > 0) अणु
		u32 dm = max_delay(ca);
		u32 da = avg_delay(ca);

		ca->alpha = alpha(ca, da, dm);
		ca->beta = beta(da, dm);
	पूर्ण

	rtt_reset(sk);
पूर्ण

/*
 * In हाल of loss, reset to शेष values
 */
अटल व्योम tcp_illinois_state(काष्ठा sock *sk, u8 new_state)
अणु
	काष्ठा illinois *ca = inet_csk_ca(sk);

	अगर (new_state == TCP_CA_Loss) अणु
		ca->alpha = ALPHA_BASE;
		ca->beta = BETA_BASE;
		ca->rtt_low = 0;
		ca->rtt_above = 0;
		rtt_reset(sk);
	पूर्ण
पूर्ण

/*
 * Increase winकरोw in response to successful acknowledgment.
 */
अटल व्योम tcp_illinois_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा illinois *ca = inet_csk_ca(sk);

	अगर (after(ack, ca->end_seq))
		update_params(sk);

	/* RFC2861 only increase cwnd अगर fully utilized */
	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	/* In slow start */
	अगर (tcp_in_slow_start(tp))
		tcp_slow_start(tp, acked);

	अन्यथा अणु
		u32 delta;

		/* snd_cwnd_cnt is # of packets since last cwnd increment */
		tp->snd_cwnd_cnt += ca->acked;
		ca->acked = 1;

		/* This is बंद approximation of:
		 * tp->snd_cwnd += alpha/tp->snd_cwnd
		*/
		delta = (tp->snd_cwnd_cnt * ca->alpha) >> ALPHA_SHIFT;
		अगर (delta >= tp->snd_cwnd) अणु
			tp->snd_cwnd = min(tp->snd_cwnd + delta / tp->snd_cwnd,
					   (u32)tp->snd_cwnd_clamp);
			tp->snd_cwnd_cnt = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 tcp_illinois_ssthresh(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा illinois *ca = inet_csk_ca(sk);

	/* Multiplicative decrease */
	वापस max(tp->snd_cwnd - ((tp->snd_cwnd * ca->beta) >> BETA_SHIFT), 2U);
पूर्ण

/* Extract info क्रम Tcp socket info provided via netlink. */
अटल माप_प्रकार tcp_illinois_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
				जोड़ tcp_cc_info *info)
अणु
	स्थिर काष्ठा illinois *ca = inet_csk_ca(sk);

	अगर (ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		info->vegas.tcpv_enabled = 1;
		info->vegas.tcpv_rttcnt = ca->cnt_rtt;
		info->vegas.tcpv_minrtt = ca->base_rtt;
		info->vegas.tcpv_rtt = 0;

		अगर (info->vegas.tcpv_rttcnt > 0) अणु
			u64 t = ca->sum_rtt;

			करो_भाग(t, info->vegas.tcpv_rttcnt);
			info->vegas.tcpv_rtt = t;
		पूर्ण
		*attr = INET_DIAG_VEGASINFO;
		वापस माप(काष्ठा tcpvegas_info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_illinois __पढ़ो_mostly = अणु
	.init		= tcp_illinois_init,
	.ssthresh	= tcp_illinois_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= tcp_illinois_cong_aव्योम,
	.set_state	= tcp_illinois_state,
	.get_info	= tcp_illinois_info,
	.pkts_acked	= tcp_illinois_acked,

	.owner		= THIS_MODULE,
	.name		= "illinois",
पूर्ण;

अटल पूर्णांक __init tcp_illinois_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा illinois) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_illinois);
पूर्ण

अटल व्योम __निकास tcp_illinois_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_illinois);
पूर्ण

module_init(tcp_illinois_रेजिस्टर);
module_निकास(tcp_illinois_unरेजिस्टर);

MODULE_AUTHOR("Stephen Hemminger, Shao Liu");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Illinois");
MODULE_VERSION("1.0");
