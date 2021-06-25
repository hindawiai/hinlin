<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP Veno congestion control
 *
 * This is based on the congestion detection/aव्योमance scheme described in
 *    C. P. Fu, S. C. Liew.
 *    "TCP Veno: TCP Enhancement for Transmission over Wireless Access Networks."
 *    IEEE Journal on Selected Areas in Communication,
 *    Feb. 2003.
 * 	See https://www.ie.cuhk.edu.hk/fileadmin/staff_upload/soung/Journal/J3.pdf
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet_diag.h>

#समावेश <net/tcp.h>

/* Default values of the Veno variables, in fixed-poपूर्णांक representation
 * with V_PARAM_SHIFT bits to the right of the binary poपूर्णांक.
 */
#घोषणा V_PARAM_SHIFT 1
अटल स्थिर पूर्णांक beta = 3 << V_PARAM_SHIFT;

/* Veno variables */
काष्ठा veno अणु
	u8 करोing_veno_now;	/* अगर true, करो veno क्रम this rtt */
	u16 cntrtt;		/* # of rtts measured within last rtt */
	u32 minrtt;		/* min of rtts measured within last rtt (in usec) */
	u32 basertt;		/* the min of all Veno rtt measurements seen (in usec) */
	u32 inc;		/* decide whether to increase cwnd */
	u32 dअगरf;		/* calculate the dअगरf rate */
पूर्ण;

/* There are several situations when we must "re-start" Veno:
 *
 *  o when a connection is established
 *  o after an RTO
 *  o after fast recovery
 *  o when we send a packet and there is no outstanding
 *    unacknowledged data (restarting an idle connection)
 *
 */
अटल अंतरभूत व्योम veno_enable(काष्ठा sock *sk)
अणु
	काष्ठा veno *veno = inet_csk_ca(sk);

	/* turn on Veno */
	veno->करोing_veno_now = 1;

	veno->minrtt = 0x7fffffff;
पूर्ण

अटल अंतरभूत व्योम veno_disable(काष्ठा sock *sk)
अणु
	काष्ठा veno *veno = inet_csk_ca(sk);

	/* turn off Veno */
	veno->करोing_veno_now = 0;
पूर्ण

अटल व्योम tcp_veno_init(काष्ठा sock *sk)
अणु
	काष्ठा veno *veno = inet_csk_ca(sk);

	veno->basertt = 0x7fffffff;
	veno->inc = 1;
	veno_enable(sk);
पूर्ण

/* Do rtt sampling needed क्रम Veno. */
अटल व्योम tcp_veno_pkts_acked(काष्ठा sock *sk,
				स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा veno *veno = inet_csk_ca(sk);
	u32 vrtt;

	अगर (sample->rtt_us < 0)
		वापस;

	/* Never allow zero rtt or baseRTT */
	vrtt = sample->rtt_us + 1;

	/* Filter to find propagation delay: */
	अगर (vrtt < veno->basertt)
		veno->basertt = vrtt;

	/* Find the min rtt during the last rtt to find
	 * the current prop. delay + queuing delay:
	 */
	veno->minrtt = min(veno->minrtt, vrtt);
	veno->cntrtt++;
पूर्ण

अटल व्योम tcp_veno_state(काष्ठा sock *sk, u8 ca_state)
अणु
	अगर (ca_state == TCP_CA_Open)
		veno_enable(sk);
	अन्यथा
		veno_disable(sk);
पूर्ण

/*
 * If the connection is idle and we are restarting,
 * then we करोn't want to करो any Veno calculations
 * until we get fresh rtt samples.  So when we
 * restart, we reset our Veno state to a clean
 * state. After we get acks क्रम this flight of
 * packets, _then_ we can make Veno calculations
 * again.
 */
अटल व्योम tcp_veno_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	अगर (event == CA_EVENT_CWND_RESTART || event == CA_EVENT_TX_START)
		tcp_veno_init(sk);
पूर्ण

अटल व्योम tcp_veno_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा veno *veno = inet_csk_ca(sk);

	अगर (!veno->करोing_veno_now) अणु
		tcp_reno_cong_aव्योम(sk, ack, acked);
		वापस;
	पूर्ण

	/* limited by applications */
	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	/* We करो the Veno calculations only अगर we got enough rtt samples */
	अगर (veno->cntrtt <= 2) अणु
		/* We करोn't have enough rtt samples to करो the Veno
		 * calculation, so we'll behave like Reno.
		 */
		tcp_reno_cong_aव्योम(sk, ack, acked);
	पूर्ण अन्यथा अणु
		u64 target_cwnd;
		u32 rtt;

		/* We have enough rtt samples, so, using the Veno
		 * algorithm, we determine the state of the network.
		 */

		rtt = veno->minrtt;

		target_cwnd = (u64)tp->snd_cwnd * veno->basertt;
		target_cwnd <<= V_PARAM_SHIFT;
		करो_भाग(target_cwnd, rtt);

		veno->dअगरf = (tp->snd_cwnd << V_PARAM_SHIFT) - target_cwnd;

		अगर (tcp_in_slow_start(tp)) अणु
			/* Slow start. */
			acked = tcp_slow_start(tp, acked);
			अगर (!acked)
				जाओ करोne;
		पूर्ण

		/* Congestion aव्योमance. */
		अगर (veno->dअगरf < beta) अणु
			/* In the "non-congestive state", increase cwnd
			 * every rtt.
			 */
			tcp_cong_aव्योम_ai(tp, tp->snd_cwnd, acked);
		पूर्ण अन्यथा अणु
			/* In the "congestive state", increase cwnd
			 * every other rtt.
			 */
			अगर (tp->snd_cwnd_cnt >= tp->snd_cwnd) अणु
				अगर (veno->inc &&
				    tp->snd_cwnd < tp->snd_cwnd_clamp) अणु
					tp->snd_cwnd++;
					veno->inc = 0;
				पूर्ण अन्यथा
					veno->inc = 1;
				tp->snd_cwnd_cnt = 0;
			पूर्ण अन्यथा
				tp->snd_cwnd_cnt += acked;
		पूर्ण
करोne:
		अगर (tp->snd_cwnd < 2)
			tp->snd_cwnd = 2;
		अन्यथा अगर (tp->snd_cwnd > tp->snd_cwnd_clamp)
			tp->snd_cwnd = tp->snd_cwnd_clamp;
	पूर्ण
	/* Wipe the slate clean क्रम the next rtt. */
	/* veno->cntrtt = 0; */
	veno->minrtt = 0x7fffffff;
पूर्ण

/* Veno MD phase */
अटल u32 tcp_veno_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा veno *veno = inet_csk_ca(sk);

	अगर (veno->dअगरf < beta)
		/* in "non-congestive state", cut cwnd by 1/5 */
		वापस max(tp->snd_cwnd * 4 / 5, 2U);
	अन्यथा
		/* in "congestive state", cut cwnd by 1/2 */
		वापस max(tp->snd_cwnd >> 1U, 2U);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_veno __पढ़ो_mostly = अणु
	.init		= tcp_veno_init,
	.ssthresh	= tcp_veno_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= tcp_veno_cong_aव्योम,
	.pkts_acked	= tcp_veno_pkts_acked,
	.set_state	= tcp_veno_state,
	.cwnd_event	= tcp_veno_cwnd_event,

	.owner		= THIS_MODULE,
	.name		= "veno",
पूर्ण;

अटल पूर्णांक __init tcp_veno_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा veno) > ICSK_CA_PRIV_SIZE);
	tcp_रेजिस्टर_congestion_control(&tcp_veno);
	वापस 0;
पूर्ण

अटल व्योम __निकास tcp_veno_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_veno);
पूर्ण

module_init(tcp_veno_रेजिस्टर);
module_निकास(tcp_veno_unरेजिस्टर);

MODULE_AUTHOR("Bin Zhou, Cheng Peng Fu");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Veno");
