<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * H-TCP congestion control. The algorithm is detailed in:
 * R.N.Shorten, D.J.Leith:
 *   "H-TCP: TCP for high-speed and long-distance networks"
 *   Proc. PFLDnet, Argonne, 2004.
 * https://www.hamilton.ie/net/htcp3.pdf
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <net/tcp.h>

#घोषणा ALPHA_BASE	(1<<7)	/* 1.0 with shअगरt << 7 */
#घोषणा BETA_MIN	(1<<6)	/* 0.5 with shअगरt << 7 */
#घोषणा BETA_MAX	102	/* 0.8 with shअगरt << 7 */

अटल पूर्णांक use_rtt_scaling __पढ़ो_mostly = 1;
module_param(use_rtt_scaling, पूर्णांक, 0644);
MODULE_PARM_DESC(use_rtt_scaling, "turn on/off RTT scaling");

अटल पूर्णांक use_bandwidth_चयन __पढ़ो_mostly = 1;
module_param(use_bandwidth_चयन, पूर्णांक, 0644);
MODULE_PARM_DESC(use_bandwidth_चयन, "turn on/off bandwidth switcher");

काष्ठा htcp अणु
	u32	alpha;		/* Fixed poपूर्णांक arith, << 7 */
	u8	beta;           /* Fixed poपूर्णांक arith, << 7 */
	u8	modeचयन;	/* Delay modeचयन
				   until we had at least one congestion event */
	u16	pkts_acked;
	u32	packetcount;
	u32	minRTT;
	u32	maxRTT;
	u32	last_cong;	/* Time since last congestion event end */
	u32	unकरो_last_cong;

	u32	unकरो_maxRTT;
	u32	unकरो_old_maxB;

	/* Bandwidth estimation */
	u32	minB;
	u32	maxB;
	u32	old_maxB;
	u32	Bi;
	u32	lastसमय;
पूर्ण;

अटल अंतरभूत u32 htcp_cong_समय(स्थिर काष्ठा htcp *ca)
अणु
	वापस jअगरfies - ca->last_cong;
पूर्ण

अटल अंतरभूत u32 htcp_ccount(स्थिर काष्ठा htcp *ca)
अणु
	वापस htcp_cong_समय(ca) / ca->minRTT;
पूर्ण

अटल अंतरभूत व्योम htcp_reset(काष्ठा htcp *ca)
अणु
	ca->unकरो_last_cong = ca->last_cong;
	ca->unकरो_maxRTT = ca->maxRTT;
	ca->unकरो_old_maxB = ca->old_maxB;

	ca->last_cong = jअगरfies;
पूर्ण

अटल u32 htcp_cwnd_unकरो(काष्ठा sock *sk)
अणु
	काष्ठा htcp *ca = inet_csk_ca(sk);

	अगर (ca->unकरो_last_cong) अणु
		ca->last_cong = ca->unकरो_last_cong;
		ca->maxRTT = ca->unकरो_maxRTT;
		ca->old_maxB = ca->unकरो_old_maxB;
		ca->unकरो_last_cong = 0;
	पूर्ण

	वापस tcp_reno_unकरो_cwnd(sk);
पूर्ण

अटल अंतरभूत व्योम measure_rtt(काष्ठा sock *sk, u32 srtt)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा htcp *ca = inet_csk_ca(sk);

	/* keep track of minimum RTT seen so far, minRTT is zero at first */
	अगर (ca->minRTT > srtt || !ca->minRTT)
		ca->minRTT = srtt;

	/* max RTT */
	अगर (icsk->icsk_ca_state == TCP_CA_Open) अणु
		अगर (ca->maxRTT < ca->minRTT)
			ca->maxRTT = ca->minRTT;
		अगर (ca->maxRTT < srtt &&
		    srtt <= ca->maxRTT + msecs_to_jअगरfies(20))
			ca->maxRTT = srtt;
	पूर्ण
पूर्ण

अटल व्योम measure_achieved_throughput(काष्ठा sock *sk,
					स्थिर काष्ठा ack_sample *sample)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा htcp *ca = inet_csk_ca(sk);
	u32 now = tcp_jअगरfies32;

	अगर (icsk->icsk_ca_state == TCP_CA_Open)
		ca->pkts_acked = sample->pkts_acked;

	अगर (sample->rtt_us > 0)
		measure_rtt(sk, usecs_to_jअगरfies(sample->rtt_us));

	अगर (!use_bandwidth_चयन)
		वापस;

	/* achieved throughput calculations */
	अगर (!((1 << icsk->icsk_ca_state) & (TCPF_CA_Open | TCPF_CA_Disorder))) अणु
		ca->packetcount = 0;
		ca->lastसमय = now;
		वापस;
	पूर्ण

	ca->packetcount += sample->pkts_acked;

	अगर (ca->packetcount >= tp->snd_cwnd - (ca->alpha >> 7 ? : 1) &&
	    now - ca->lastसमय >= ca->minRTT &&
	    ca->minRTT > 0) अणु
		__u32 cur_Bi = ca->packetcount * HZ / (now - ca->lastसमय);

		अगर (htcp_ccount(ca) <= 3) अणु
			/* just after backoff */
			ca->minB = ca->maxB = ca->Bi = cur_Bi;
		पूर्ण अन्यथा अणु
			ca->Bi = (3 * ca->Bi + cur_Bi) / 4;
			अगर (ca->Bi > ca->maxB)
				ca->maxB = ca->Bi;
			अगर (ca->minB > ca->maxB)
				ca->minB = ca->maxB;
		पूर्ण
		ca->packetcount = 0;
		ca->lastसमय = now;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम htcp_beta_update(काष्ठा htcp *ca, u32 minRTT, u32 maxRTT)
अणु
	अगर (use_bandwidth_चयन) अणु
		u32 maxB = ca->maxB;
		u32 old_maxB = ca->old_maxB;

		ca->old_maxB = ca->maxB;
		अगर (!between(5 * maxB, 4 * old_maxB, 6 * old_maxB)) अणु
			ca->beta = BETA_MIN;
			ca->modeचयन = 0;
			वापस;
		पूर्ण
	पूर्ण

	अगर (ca->modeचयन && minRTT > msecs_to_jअगरfies(10) && maxRTT) अणु
		ca->beta = (minRTT << 7) / maxRTT;
		अगर (ca->beta < BETA_MIN)
			ca->beta = BETA_MIN;
		अन्यथा अगर (ca->beta > BETA_MAX)
			ca->beta = BETA_MAX;
	पूर्ण अन्यथा अणु
		ca->beta = BETA_MIN;
		ca->modeचयन = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम htcp_alpha_update(काष्ठा htcp *ca)
अणु
	u32 minRTT = ca->minRTT;
	u32 factor = 1;
	u32 dअगरf = htcp_cong_समय(ca);

	अगर (dअगरf > HZ) अणु
		dअगरf -= HZ;
		factor = 1 + (10 * dअगरf + ((dअगरf / 2) * (dअगरf / 2) / HZ)) / HZ;
	पूर्ण

	अगर (use_rtt_scaling && minRTT) अणु
		u32 scale = (HZ << 3) / (10 * minRTT);

		/* clamping ratio to पूर्णांकerval [0.5,10]<<3 */
		scale = min(max(scale, 1U << 2), 10U << 3);
		factor = (factor << 3) / scale;
		अगर (!factor)
			factor = 1;
	पूर्ण

	ca->alpha = 2 * factor * ((1 << 7) - ca->beta);
	अगर (!ca->alpha)
		ca->alpha = ALPHA_BASE;
पूर्ण

/*
 * After we have the rtt data to calculate beta, we'd still prefer to रुको one
 * rtt beक्रमe we adjust our beta to ensure we are working from a consistent
 * data.
 *
 * This function should be called when we hit a congestion event since only at
 * that poपूर्णांक करो we really have a real sense of maxRTT (the queues en route
 * were getting just too full now).
 */
अटल व्योम htcp_param_update(काष्ठा sock *sk)
अणु
	काष्ठा htcp *ca = inet_csk_ca(sk);
	u32 minRTT = ca->minRTT;
	u32 maxRTT = ca->maxRTT;

	htcp_beta_update(ca, minRTT, maxRTT);
	htcp_alpha_update(ca);

	/* add slowly fading memory क्रम maxRTT to accommodate routing changes */
	अगर (minRTT > 0 && maxRTT > minRTT)
		ca->maxRTT = minRTT + ((maxRTT - minRTT) * 95) / 100;
पूर्ण

अटल u32 htcp_recalc_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा htcp *ca = inet_csk_ca(sk);

	htcp_param_update(sk);
	वापस max((tp->snd_cwnd * ca->beta) >> 7, 2U);
पूर्ण

अटल व्योम htcp_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा htcp *ca = inet_csk_ca(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp))
		tcp_slow_start(tp, acked);
	अन्यथा अणु
		/* In dangerous area, increase slowly.
		 * In theory this is tp->snd_cwnd += alpha / tp->snd_cwnd
		 */
		अगर ((tp->snd_cwnd_cnt * ca->alpha)>>7 >= tp->snd_cwnd) अणु
			अगर (tp->snd_cwnd < tp->snd_cwnd_clamp)
				tp->snd_cwnd++;
			tp->snd_cwnd_cnt = 0;
			htcp_alpha_update(ca);
		पूर्ण अन्यथा
			tp->snd_cwnd_cnt += ca->pkts_acked;

		ca->pkts_acked = 1;
	पूर्ण
पूर्ण

अटल व्योम htcp_init(काष्ठा sock *sk)
अणु
	काष्ठा htcp *ca = inet_csk_ca(sk);

	स_रखो(ca, 0, माप(काष्ठा htcp));
	ca->alpha = ALPHA_BASE;
	ca->beta = BETA_MIN;
	ca->pkts_acked = 1;
	ca->last_cong = jअगरfies;
पूर्ण

अटल व्योम htcp_state(काष्ठा sock *sk, u8 new_state)
अणु
	चयन (new_state) अणु
	हाल TCP_CA_Open:
		अणु
			काष्ठा htcp *ca = inet_csk_ca(sk);

			अगर (ca->unकरो_last_cong) अणु
				ca->last_cong = jअगरfies;
				ca->unकरो_last_cong = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल TCP_CA_CWR:
	हाल TCP_CA_Recovery:
	हाल TCP_CA_Loss:
		htcp_reset(inet_csk_ca(sk));
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा tcp_congestion_ops htcp __पढ़ो_mostly = अणु
	.init		= htcp_init,
	.ssthresh	= htcp_recalc_ssthresh,
	.cong_aव्योम	= htcp_cong_aव्योम,
	.set_state	= htcp_state,
	.unकरो_cwnd	= htcp_cwnd_unकरो,
	.pkts_acked	= measure_achieved_throughput,
	.owner		= THIS_MODULE,
	.name		= "htcp",
पूर्ण;

अटल पूर्णांक __init htcp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा htcp) > ICSK_CA_PRIV_SIZE);
	BUILD_BUG_ON(BETA_MIN >= BETA_MAX);
	वापस tcp_रेजिस्टर_congestion_control(&htcp);
पूर्ण

अटल व्योम __निकास htcp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&htcp);
पूर्ण

module_init(htcp_रेजिस्टर);
module_निकास(htcp_unरेजिस्टर);

MODULE_AUTHOR("Baruch Even");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("H-TCP");
