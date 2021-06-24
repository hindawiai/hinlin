<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Binary Increase Congestion control क्रम TCP
 * Home page:
 *      http://netsrv.csc.ncsu.edu/twiki/bin/view/Main/BIC
 * This is from the implementation of BICTCP in
 * Lison-Xu, Kahaled Harfoush, and Injong Rhee.
 *  "Binary Increase Congestion Control क्रम Fast, Long Distance
 *  Networks" in InfoComm 2004
 * Available from:
 *  http://netsrv.csc.ncsu.edu/export/bitcp.pdf
 *
 * Unless BIC is enabled and congestion winकरोw is large
 * this behaves the same as the original Reno.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <net/tcp.h>

#घोषणा BICTCP_BETA_SCALE    1024	/* Scale factor beta calculation
					 * max_cwnd = snd_cwnd * beta
					 */
#घोषणा BICTCP_B		4	 /*
					  * In binary search,
					  * go to poपूर्णांक (max+min)/N
					  */

अटल पूर्णांक fast_convergence = 1;
अटल पूर्णांक max_increment = 16;
अटल पूर्णांक low_winकरोw = 14;
अटल पूर्णांक beta = 819;		/* = 819/1024 (BICTCP_BETA_SCALE) */
अटल पूर्णांक initial_ssthresh;
अटल पूर्णांक smooth_part = 20;

module_param(fast_convergence, पूर्णांक, 0644);
MODULE_PARM_DESC(fast_convergence, "turn on/off fast convergence");
module_param(max_increment, पूर्णांक, 0644);
MODULE_PARM_DESC(max_increment, "Limit on increment allowed during binary search");
module_param(low_winकरोw, पूर्णांक, 0644);
MODULE_PARM_DESC(low_winकरोw, "lower bound on congestion window (for TCP friendliness)");
module_param(beta, पूर्णांक, 0644);
MODULE_PARM_DESC(beta, "beta for multiplicative increase");
module_param(initial_ssthresh, पूर्णांक, 0644);
MODULE_PARM_DESC(initial_ssthresh, "initial value of slow start threshold");
module_param(smooth_part, पूर्णांक, 0644);
MODULE_PARM_DESC(smooth_part, "log(B/(B*Smin))/log(B/(B-1))+B, # of RTT from Wmax-B to Wmax");

/* BIC TCP Parameters */
काष्ठा bictcp अणु
	u32	cnt;		/* increase cwnd by 1 after ACKs */
	u32	last_max_cwnd;	/* last maximum snd_cwnd */
	u32	last_cwnd;	/* the last snd_cwnd */
	u32	last_समय;	/* समय when updated last_cwnd */
	u32	epoch_start;	/* beginning of an epoch */
#घोषणा ACK_RATIO_SHIFT	4
	u32	delayed_ack;	/* estimate the ratio of Packets/ACKs << 4 */
पूर्ण;

अटल अंतरभूत व्योम bictcp_reset(काष्ठा bictcp *ca)
अणु
	ca->cnt = 0;
	ca->last_max_cwnd = 0;
	ca->last_cwnd = 0;
	ca->last_समय = 0;
	ca->epoch_start = 0;
	ca->delayed_ack = 2 << ACK_RATIO_SHIFT;
पूर्ण

अटल व्योम bictcp_init(काष्ठा sock *sk)
अणु
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	bictcp_reset(ca);

	अगर (initial_ssthresh)
		tcp_sk(sk)->snd_ssthresh = initial_ssthresh;
पूर्ण

/*
 * Compute congestion winकरोw to use.
 */
अटल अंतरभूत व्योम bictcp_update(काष्ठा bictcp *ca, u32 cwnd)
अणु
	अगर (ca->last_cwnd == cwnd &&
	    (s32)(tcp_jअगरfies32 - ca->last_समय) <= HZ / 32)
		वापस;

	ca->last_cwnd = cwnd;
	ca->last_समय = tcp_jअगरfies32;

	अगर (ca->epoch_start == 0) /* record the beginning of an epoch */
		ca->epoch_start = tcp_jअगरfies32;

	/* start off normal */
	अगर (cwnd <= low_winकरोw) अणु
		ca->cnt = cwnd;
		वापस;
	पूर्ण

	/* binary increase */
	अगर (cwnd < ca->last_max_cwnd) अणु
		__u32	dist = (ca->last_max_cwnd - cwnd)
			/ BICTCP_B;

		अगर (dist > max_increment)
			/* linear increase */
			ca->cnt = cwnd / max_increment;
		अन्यथा अगर (dist <= 1U)
			/* binary search increase */
			ca->cnt = (cwnd * smooth_part) / BICTCP_B;
		अन्यथा
			/* binary search increase */
			ca->cnt = cwnd / dist;
	पूर्ण अन्यथा अणु
		/* slow start AMD linear increase */
		अगर (cwnd < ca->last_max_cwnd + BICTCP_B)
			/* slow start */
			ca->cnt = (cwnd * smooth_part) / BICTCP_B;
		अन्यथा अगर (cwnd < ca->last_max_cwnd + max_increment*(BICTCP_B-1))
			/* slow start */
			ca->cnt = (cwnd * (BICTCP_B-1))
				/ (cwnd - ca->last_max_cwnd);
		अन्यथा
			/* linear increase */
			ca->cnt = cwnd / max_increment;
	पूर्ण

	/* अगर in slow start or link utilization is very low */
	अगर (ca->last_max_cwnd == 0) अणु
		अगर (ca->cnt > 20) /* increase cwnd 5% per RTT */
			ca->cnt = 20;
	पूर्ण

	ca->cnt = (ca->cnt << ACK_RATIO_SHIFT) / ca->delayed_ack;
	अगर (ca->cnt == 0)			/* cannot be zero */
		ca->cnt = 1;
पूर्ण

अटल व्योम bictcp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp)) अणु
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			वापस;
	पूर्ण
	bictcp_update(ca, tp->snd_cwnd);
	tcp_cong_aव्योम_ai(tp, ca->cnt, acked);
पूर्ण

/*
 *	behave like Reno until low_winकरोw is reached,
 *	then increase congestion winकरोw slowly
 */
अटल u32 bictcp_recalc_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा bictcp *ca = inet_csk_ca(sk);

	ca->epoch_start = 0;	/* end of epoch */

	/* Wmax and fast convergence */
	अगर (tp->snd_cwnd < ca->last_max_cwnd && fast_convergence)
		ca->last_max_cwnd = (tp->snd_cwnd * (BICTCP_BETA_SCALE + beta))
			/ (2 * BICTCP_BETA_SCALE);
	अन्यथा
		ca->last_max_cwnd = tp->snd_cwnd;

	अगर (tp->snd_cwnd <= low_winकरोw)
		वापस max(tp->snd_cwnd >> 1U, 2U);
	अन्यथा
		वापस max((tp->snd_cwnd * beta) / BICTCP_BETA_SCALE, 2U);
पूर्ण

अटल व्योम bictcp_state(काष्ठा sock *sk, u8 new_state)
अणु
	अगर (new_state == TCP_CA_Loss)
		bictcp_reset(inet_csk_ca(sk));
पूर्ण

/* Track delayed acknowledgment ratio using sliding winकरोw
 * ratio = (15*ratio + sample) / 16
 */
अटल व्योम bictcp_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_state == TCP_CA_Open) अणु
		काष्ठा bictcp *ca = inet_csk_ca(sk);

		ca->delayed_ack += sample->pkts_acked -
			(ca->delayed_ack >> ACK_RATIO_SHIFT);
	पूर्ण
पूर्ण

अटल काष्ठा tcp_congestion_ops bictcp __पढ़ो_mostly = अणु
	.init		= bictcp_init,
	.ssthresh	= bictcp_recalc_ssthresh,
	.cong_aव्योम	= bictcp_cong_aव्योम,
	.set_state	= bictcp_state,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.pkts_acked     = bictcp_acked,
	.owner		= THIS_MODULE,
	.name		= "bic",
पूर्ण;

अटल पूर्णांक __init bictcp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा bictcp) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&bictcp);
पूर्ण

अटल व्योम __निकास bictcp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&bictcp);
पूर्ण

module_init(bictcp_रेजिस्टर);
module_निकास(bictcp_unरेजिस्टर);

MODULE_AUTHOR("Stephen Hemminger");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BIC TCP");
