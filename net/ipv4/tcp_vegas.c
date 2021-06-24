<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP Vegas congestion control
 *
 * This is based on the congestion detection/aव्योमance scheme described in
 *    Lawrence S. Brakmo and Larry L. Peterson.
 *    "TCP Vegas: End to end congestion avoidance on a global internet."
 *    IEEE Journal on Selected Areas in Communication, 13(8):1465--1480,
 *    October 1995. Available from:
 *	ftp://ftp.cs.arizona.edu/xkernel/Papers/jsac.ps
 *
 * See http://www.cs.arizona.edu/xkernel/ क्रम their implementation.
 * The मुख्य aspects that distinguish this implementation from the
 * Arizona Vegas implementation are:
 *   o We करो not change the loss detection or recovery mechanisms of
 *     Linux in any way. Linux alपढ़ोy recovers from losses quite well,
 *     using fine-grained समयrs, NewReno, and FACK.
 *   o To aव्योम the perक्रमmance penalty imposed by increasing cwnd
 *     only every-other RTT during slow start, we increase during
 *     every RTT during slow start, just like Reno.
 *   o Largely to allow continuous cwnd growth during slow start,
 *     we use the rate at which ACKs come back as the "actual"
 *     rate, rather than the rate at which data is sent.
 *   o To speed convergence to the right rate, we set the cwnd
 *     to achieve the right ("actual") rate when we निकास slow start.
 *   o To filter out the noise caused by delayed ACKs, we use the
 *     minimum RTT sample observed during the last RTT to calculate
 *     the actual rate.
 *   o When the sender re-starts from idle, it रुकोs until it has
 *     received ACKs क्रम an entire flight of new data beक्रमe making
 *     a cwnd adjusपंचांगent decision. The original Vegas implementation
 *     assumed senders never went idle.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet_diag.h>

#समावेश <net/tcp.h>

#समावेश "tcp_vegas.h"

अटल पूर्णांक alpha = 2;
अटल पूर्णांक beta  = 4;
अटल पूर्णांक gamma = 1;

module_param(alpha, पूर्णांक, 0644);
MODULE_PARM_DESC(alpha, "lower bound of packets in network");
module_param(beta, पूर्णांक, 0644);
MODULE_PARM_DESC(beta, "upper bound of packets in network");
module_param(gamma, पूर्णांक, 0644);
MODULE_PARM_DESC(gamma, "limit on increase (scale by 2)");

/* There are several situations when we must "re-start" Vegas:
 *
 *  o when a connection is established
 *  o after an RTO
 *  o after fast recovery
 *  o when we send a packet and there is no outstanding
 *    unacknowledged data (restarting an idle connection)
 *
 * In these circumstances we cannot करो a Vegas calculation at the
 * end of the first RTT, because any calculation we करो is using
 * stale info -- both the saved cwnd and congestion feedback are
 * stale.
 *
 * Instead we must रुको until the completion of an RTT during
 * which we actually receive ACKs.
 */
अटल व्योम vegas_enable(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा vegas *vegas = inet_csk_ca(sk);

	/* Begin taking Vegas samples next समय we send something. */
	vegas->करोing_vegas_now = 1;

	/* Set the beginning of the next send winकरोw. */
	vegas->beg_snd_nxt = tp->snd_nxt;

	vegas->cntRTT = 0;
	vegas->minRTT = 0x7fffffff;
पूर्ण

/* Stop taking Vegas samples क्रम now. */
अटल अंतरभूत व्योम vegas_disable(काष्ठा sock *sk)
अणु
	काष्ठा vegas *vegas = inet_csk_ca(sk);

	vegas->करोing_vegas_now = 0;
पूर्ण

व्योम tcp_vegas_init(काष्ठा sock *sk)
अणु
	काष्ठा vegas *vegas = inet_csk_ca(sk);

	vegas->baseRTT = 0x7fffffff;
	vegas_enable(sk);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_vegas_init);

/* Do RTT sampling needed क्रम Vegas.
 * Basically we:
 *   o min-filter RTT samples from within an RTT to get the current
 *     propagation delay + queuing delay (we are min-filtering to try to
 *     aव्योम the effects of delayed ACKs)
 *   o min-filter RTT samples from a much दीर्घer winकरोw (क्रमever क्रम now)
 *     to find the propagation delay (baseRTT)
 */
व्योम tcp_vegas_pkts_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा vegas *vegas = inet_csk_ca(sk);
	u32 vrtt;

	अगर (sample->rtt_us < 0)
		वापस;

	/* Never allow zero rtt or baseRTT */
	vrtt = sample->rtt_us + 1;

	/* Filter to find propagation delay: */
	अगर (vrtt < vegas->baseRTT)
		vegas->baseRTT = vrtt;

	/* Find the min RTT during the last RTT to find
	 * the current prop. delay + queuing delay:
	 */
	vegas->minRTT = min(vegas->minRTT, vrtt);
	vegas->cntRTT++;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_vegas_pkts_acked);

व्योम tcp_vegas_state(काष्ठा sock *sk, u8 ca_state)
अणु
	अगर (ca_state == TCP_CA_Open)
		vegas_enable(sk);
	अन्यथा
		vegas_disable(sk);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_vegas_state);

/*
 * If the connection is idle and we are restarting,
 * then we करोn't want to करो any Vegas calculations
 * until we get fresh RTT samples.  So when we
 * restart, we reset our Vegas state to a clean
 * slate. After we get acks क्रम this flight of
 * packets, _then_ we can make Vegas calculations
 * again.
 */
व्योम tcp_vegas_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	अगर (event == CA_EVENT_CWND_RESTART ||
	    event == CA_EVENT_TX_START)
		tcp_vegas_init(sk);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_vegas_cwnd_event);

अटल अंतरभूत u32 tcp_vegas_ssthresh(काष्ठा tcp_sock *tp)
अणु
	वापस  min(tp->snd_ssthresh, tp->snd_cwnd);
पूर्ण

अटल व्योम tcp_vegas_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा vegas *vegas = inet_csk_ca(sk);

	अगर (!vegas->करोing_vegas_now) अणु
		tcp_reno_cong_aव्योम(sk, ack, acked);
		वापस;
	पूर्ण

	अगर (after(ack, vegas->beg_snd_nxt)) अणु
		/* Do the Vegas once-per-RTT cwnd adjusपंचांगent. */

		/* Save the extent of the current winकरोw so we can use this
		 * at the end of the next RTT.
		 */
		vegas->beg_snd_nxt  = tp->snd_nxt;

		/* We करो the Vegas calculations only अगर we got enough RTT
		 * samples that we can be reasonably sure that we got
		 * at least one RTT sample that wasn't from a delayed ACK.
		 * If we only had 2 samples total,
		 * then that means we're getting only 1 ACK per RTT, which
		 * means they're almost certainly delayed ACKs.
		 * If  we have 3 samples, we should be OK.
		 */

		अगर (vegas->cntRTT <= 2) अणु
			/* We करोn't have enough RTT samples to करो the Vegas
			 * calculation, so we'll behave like Reno.
			 */
			tcp_reno_cong_aव्योम(sk, ack, acked);
		पूर्ण अन्यथा अणु
			u32 rtt, dअगरf;
			u64 target_cwnd;

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
			rtt = vegas->minRTT;

			/* Calculate the cwnd we should have, अगर we weren't
			 * going too fast.
			 *
			 * This is:
			 *     (actual rate in segments) * baseRTT
			 */
			target_cwnd = (u64)tp->snd_cwnd * vegas->baseRTT;
			करो_भाग(target_cwnd, rtt);

			/* Calculate the dअगरference between the winकरोw we had,
			 * and the winकरोw we would like to have. This quantity
			 * is the "Diff" from the Arizona Vegas papers.
			 */
			dअगरf = tp->snd_cwnd * (rtt-vegas->baseRTT) / vegas->baseRTT;

			अगर (dअगरf > gamma && tcp_in_slow_start(tp)) अणु
				/* Going too fast. Time to slow करोwn
				 * and चयन to congestion aव्योमance.
				 */

				/* Set cwnd to match the actual rate
				 * exactly:
				 *   cwnd = (actual rate) * baseRTT
				 * Then we add 1 because the पूर्णांकeger
				 * truncation robs us of full link
				 * utilization.
				 */
				tp->snd_cwnd = min(tp->snd_cwnd, (u32)target_cwnd+1);
				tp->snd_ssthresh = tcp_vegas_ssthresh(tp);

			पूर्ण अन्यथा अगर (tcp_in_slow_start(tp)) अणु
				/* Slow start.  */
				tcp_slow_start(tp, acked);
			पूर्ण अन्यथा अणु
				/* Congestion aव्योमance. */

				/* Figure out where we would like cwnd
				 * to be.
				 */
				अगर (dअगरf > beta) अणु
					/* The old winकरोw was too fast, so
					 * we slow करोwn.
					 */
					tp->snd_cwnd--;
					tp->snd_ssthresh
						= tcp_vegas_ssthresh(tp);
				पूर्ण अन्यथा अगर (dअगरf < alpha) अणु
					/* We करोn't have enough extra packets
					 * in the network, so speed up.
					 */
					tp->snd_cwnd++;
				पूर्ण अन्यथा अणु
					/* Sending just as fast as we
					 * should be.
					 */
				पूर्ण
			पूर्ण

			अगर (tp->snd_cwnd < 2)
				tp->snd_cwnd = 2;
			अन्यथा अगर (tp->snd_cwnd > tp->snd_cwnd_clamp)
				tp->snd_cwnd = tp->snd_cwnd_clamp;

			tp->snd_ssthresh = tcp_current_ssthresh(sk);
		पूर्ण

		/* Wipe the slate clean क्रम the next RTT. */
		vegas->cntRTT = 0;
		vegas->minRTT = 0x7fffffff;
	पूर्ण
	/* Use normal slow start */
	अन्यथा अगर (tcp_in_slow_start(tp))
		tcp_slow_start(tp, acked);
पूर्ण

/* Extract info क्रम Tcp socket info provided via netlink. */
माप_प्रकार tcp_vegas_get_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			  जोड़ tcp_cc_info *info)
अणु
	स्थिर काष्ठा vegas *ca = inet_csk_ca(sk);

	अगर (ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		info->vegas.tcpv_enabled = ca->करोing_vegas_now;
		info->vegas.tcpv_rttcnt = ca->cntRTT;
		info->vegas.tcpv_rtt = ca->baseRTT;
		info->vegas.tcpv_minrtt = ca->minRTT;

		*attr = INET_DIAG_VEGASINFO;
		वापस माप(काष्ठा tcpvegas_info);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_vegas_get_info);

अटल काष्ठा tcp_congestion_ops tcp_vegas __पढ़ो_mostly = अणु
	.init		= tcp_vegas_init,
	.ssthresh	= tcp_reno_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= tcp_vegas_cong_aव्योम,
	.pkts_acked	= tcp_vegas_pkts_acked,
	.set_state	= tcp_vegas_state,
	.cwnd_event	= tcp_vegas_cwnd_event,
	.get_info	= tcp_vegas_get_info,

	.owner		= THIS_MODULE,
	.name		= "vegas",
पूर्ण;

अटल पूर्णांक __init tcp_vegas_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा vegas) > ICSK_CA_PRIV_SIZE);
	tcp_रेजिस्टर_congestion_control(&tcp_vegas);
	वापस 0;
पूर्ण

अटल व्योम __निकास tcp_vegas_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_vegas);
पूर्ण

module_init(tcp_vegas_रेजिस्टर);
module_निकास(tcp_vegas_unरेजिस्टर);

MODULE_AUTHOR("Stephen Hemminger");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Vegas");
