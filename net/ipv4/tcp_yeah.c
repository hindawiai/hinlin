<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *   YeAH TCP
 *
 * For further details look at:
 *   https://web.archive.org/web/20080316215752/http://wil.cs.caltech.edu/pfldnet2007/paper/YeAH_TCP.pdf
 *
 */
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet_diag.h>

#समावेश <net/tcp.h>

#समावेश "tcp_vegas.h"

#घोषणा TCP_YEAH_ALPHA       80 /* number of packets queued at the bottleneck */
#घोषणा TCP_YEAH_GAMMA        1 /* fraction of queue to be हटाओd per rtt */
#घोषणा TCP_YEAH_DELTA        3 /* log minimum fraction of cwnd to be हटाओd on loss */
#घोषणा TCP_YEAH_EPSILON      1 /* log maximum fraction to be हटाओd on early decongestion */
#घोषणा TCP_YEAH_PHY          8 /* maximum delta from base */
#घोषणा TCP_YEAH_RHO         16 /* minimum number of consecutive rtt to consider competition on loss */
#घोषणा TCP_YEAH_ZETA        50 /* minimum number of state चयनes to reset reno_count */

#घोषणा TCP_SCALABLE_AI_CNT	 100U

/* YeAH variables */
काष्ठा yeah अणु
	काष्ठा vegas vegas;	/* must be first */

	/* YeAH */
	u32 lastQ;
	u32 करोing_reno_now;

	u32 reno_count;
	u32 fast_count;
पूर्ण;

अटल व्योम tcp_yeah_init(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा yeah *yeah = inet_csk_ca(sk);

	tcp_vegas_init(sk);

	yeah->करोing_reno_now = 0;
	yeah->lastQ = 0;

	yeah->reno_count = 2;

	/* Ensure the MD arithmetic works.  This is somewhat pedantic,
	 * since I करोn't think we will see a cwnd this large. :) */
	tp->snd_cwnd_clamp = min_t(u32, tp->snd_cwnd_clamp, 0xffffffff/128);
पूर्ण

अटल व्योम tcp_yeah_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा yeah *yeah = inet_csk_ca(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp)) अणु
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			जाओ करो_vegas;
	पूर्ण

	अगर (!yeah->करोing_reno_now) अणु
		/* Scalable */
		tcp_cong_aव्योम_ai(tp, min(tp->snd_cwnd, TCP_SCALABLE_AI_CNT),
				  acked);
	पूर्ण अन्यथा अणु
		/* Reno */
		tcp_cong_aव्योम_ai(tp, tp->snd_cwnd, acked);
	पूर्ण

	/* The key players are v_vegas.beg_snd_una and v_beg_snd_nxt.
	 *
	 * These are so named because they represent the approximate values
	 * of snd_una and snd_nxt at the beginning of the current RTT. More
	 * precisely, they represent the amount of data sent during the RTT.
	 * At the end of the RTT, when we receive an ACK क्रम v_beg_snd_nxt,
	 * we will calculate that (v_beg_snd_nxt - v_vegas.beg_snd_una) outstanding
	 * bytes of data have been ACKed during the course of the RTT, giving
	 * an "actual" rate of:
	 *
	 *     (v_beg_snd_nxt - v_vegas.beg_snd_una) / (rtt duration)
	 *
	 * Unक्रमtunately, v_vegas.beg_snd_una is not exactly equal to snd_una,
	 * because delayed ACKs can cover more than one segment, so they
	 * करोn't line up yeahly with the boundaries of RTTs.
	 *
	 * Another unक्रमtunate fact of lअगरe is that delayed ACKs delay the
	 * advance of the left edge of our send winकरोw, so that the number
	 * of bytes we send in an RTT is often less than our cwnd will allow.
	 * So we keep track of our cwnd separately, in v_beg_snd_cwnd.
	 */
करो_vegas:
	अगर (after(ack, yeah->vegas.beg_snd_nxt)) अणु
		/* We करो the Vegas calculations only अगर we got enough RTT
		 * samples that we can be reasonably sure that we got
		 * at least one RTT sample that wasn't from a delayed ACK.
		 * If we only had 2 samples total,
		 * then that means we're getting only 1 ACK per RTT, which
		 * means they're almost certainly delayed ACKs.
		 * If  we have 3 samples, we should be OK.
		 */

		अगर (yeah->vegas.cntRTT > 2) अणु
			u32 rtt, queue;
			u64 bw;

			/* We have enough RTT samples, so, using the Vegas
			 * algorithm, we determine अगर we should increase or
			 * decrease cwnd, and by how much.
			 */

			/* Pluck out the RTT we are using क्रम the Vegas
			 * calculations. This is the min RTT seen during the
			 * last RTT. Taking the min filters out the effects
			 * of delayed ACKs, at the cost of noticing congestion
			 * a bit later.
			 */
			rtt = yeah->vegas.minRTT;

			/* Compute excess number of packets above bandwidth
			 * Aव्योम करोing full 64 bit भागide.
			 */
			bw = tp->snd_cwnd;
			bw *= rtt - yeah->vegas.baseRTT;
			करो_भाग(bw, rtt);
			queue = bw;

			अगर (queue > TCP_YEAH_ALPHA ||
			    rtt - yeah->vegas.baseRTT > (yeah->vegas.baseRTT / TCP_YEAH_PHY)) अणु
				अगर (queue > TCP_YEAH_ALPHA &&
				    tp->snd_cwnd > yeah->reno_count) अणु
					u32 reduction = min(queue / TCP_YEAH_GAMMA ,
							    tp->snd_cwnd >> TCP_YEAH_EPSILON);

					tp->snd_cwnd -= reduction;

					tp->snd_cwnd = max(tp->snd_cwnd,
							   yeah->reno_count);

					tp->snd_ssthresh = tp->snd_cwnd;
				पूर्ण

				अगर (yeah->reno_count <= 2)
					yeah->reno_count = max(tp->snd_cwnd>>1, 2U);
				अन्यथा
					yeah->reno_count++;

				yeah->करोing_reno_now = min(yeah->करोing_reno_now + 1,
							   0xffffffU);
			पूर्ण अन्यथा अणु
				yeah->fast_count++;

				अगर (yeah->fast_count > TCP_YEAH_ZETA) अणु
					yeah->reno_count = 2;
					yeah->fast_count = 0;
				पूर्ण

				yeah->करोing_reno_now = 0;
			पूर्ण

			yeah->lastQ = queue;
		पूर्ण

		/* Save the extent of the current winकरोw so we can use this
		 * at the end of the next RTT.
		 */
		yeah->vegas.beg_snd_una  = yeah->vegas.beg_snd_nxt;
		yeah->vegas.beg_snd_nxt  = tp->snd_nxt;
		yeah->vegas.beg_snd_cwnd = tp->snd_cwnd;

		/* Wipe the slate clean क्रम the next RTT. */
		yeah->vegas.cntRTT = 0;
		yeah->vegas.minRTT = 0x7fffffff;
	पूर्ण
पूर्ण

अटल u32 tcp_yeah_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा yeah *yeah = inet_csk_ca(sk);
	u32 reduction;

	अगर (yeah->करोing_reno_now < TCP_YEAH_RHO) अणु
		reduction = yeah->lastQ;

		reduction = min(reduction, max(tp->snd_cwnd>>1, 2U));

		reduction = max(reduction, tp->snd_cwnd >> TCP_YEAH_DELTA);
	पूर्ण अन्यथा
		reduction = max(tp->snd_cwnd>>1, 2U);

	yeah->fast_count = 0;
	yeah->reno_count = max(yeah->reno_count>>1, 2U);

	वापस max_t(पूर्णांक, tp->snd_cwnd - reduction, 2);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_yeah __पढ़ो_mostly = अणु
	.init		= tcp_yeah_init,
	.ssthresh	= tcp_yeah_ssthresh,
	.unकरो_cwnd      = tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= tcp_yeah_cong_aव्योम,
	.set_state	= tcp_vegas_state,
	.cwnd_event	= tcp_vegas_cwnd_event,
	.get_info	= tcp_vegas_get_info,
	.pkts_acked	= tcp_vegas_pkts_acked,

	.owner		= THIS_MODULE,
	.name		= "yeah",
पूर्ण;

अटल पूर्णांक __init tcp_yeah_रेजिस्टर(व्योम)
अणु
	BUG_ON(माप(काष्ठा yeah) > ICSK_CA_PRIV_SIZE);
	tcp_रेजिस्टर_congestion_control(&tcp_yeah);
	वापस 0;
पूर्ण

अटल व्योम __निकास tcp_yeah_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_yeah);
पूर्ण

module_init(tcp_yeah_रेजिस्टर);
module_निकास(tcp_yeah_unरेजिस्टर);

MODULE_AUTHOR("Angelo P. Castellani");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("YeAH TCP");
