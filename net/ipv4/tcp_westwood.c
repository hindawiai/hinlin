<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TCP Westwood+: end-to-end bandwidth estimation क्रम TCP
 *
 *      Angelo Dell'Aera: author of the first version of TCP Westwood+ in Linux 2.4
 *
 * Support at http://c3lab.poliba.it/index.php/Westwood
 * Main references in literature:
 *
 * - Mascolo S, Casetti, M. Gerla et al.
 *   "TCP Westwood: bandwidth estimation for TCP" Proc. ACM Mobicom 2001
 *
 * - A. Grieco, s. Mascolo
 *   "Performance evaluation of New Reno, Vegas, Westwood+ TCP" ACM Computer
 *     Comm. Review, 2004
 *
 * - A. Dell'Aera, L. Grieco, S. Mascolo.
 *   "Linux 2.4 Implementation of Westwood+ TCP with Rate-Halving :
 *    A Perक्रमmance Evaluation Over the Internet" (ICC 2004), Paris, June 2004
 *
 * Westwood+ employs end-to-end bandwidth measurement to set cwnd and
 * ssthresh after packet loss. The probing phase is as the original Reno.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet_diag.h>
#समावेश <net/tcp.h>

/* TCP Westwood काष्ठाure */
काष्ठा westwood अणु
	u32    bw_ns_est;        /* first bandwidth estimation..not too smoothed 8) */
	u32    bw_est;           /* bandwidth estimate */
	u32    rtt_win_sx;       /* here starts a new evaluation... */
	u32    bk;
	u32    snd_una;          /* used क्रम evaluating the number of acked bytes */
	u32    cumul_ack;
	u32    accounted;
	u32    rtt;
	u32    rtt_min;          /* minimum observed RTT */
	u8     first_ack;        /* flag which infers that this is the first ack */
	u8     reset_rtt_min;    /* Reset RTT min to next RTT sample*/
पूर्ण;

/* TCP Westwood functions and स्थिरants */
#घोषणा TCP_WESTWOOD_RTT_MIN   (HZ/20)	/* 50ms */
#घोषणा TCP_WESTWOOD_INIT_RTT  (20*HZ)	/* maybe too conservative?! */

/*
 * @tcp_westwood_create
 * This function initializes fields used in TCP Westwood+,
 * it is called after the initial SYN, so the sequence numbers
 * are correct but new passive connections we have no
 * inक्रमmation about RTTmin at this समय so we simply set it to
 * TCP_WESTWOOD_INIT_RTT. This value was chosen to be too conservative
 * since in this way we're sure it will be updated in a consistent
 * way as soon as possible. It will reasonably happen within the first
 * RTT period of the connection lअगरeसमय.
 */
अटल व्योम tcp_westwood_init(काष्ठा sock *sk)
अणु
	काष्ठा westwood *w = inet_csk_ca(sk);

	w->bk = 0;
	w->bw_ns_est = 0;
	w->bw_est = 0;
	w->accounted = 0;
	w->cumul_ack = 0;
	w->reset_rtt_min = 1;
	w->rtt_min = w->rtt = TCP_WESTWOOD_INIT_RTT;
	w->rtt_win_sx = tcp_jअगरfies32;
	w->snd_una = tcp_sk(sk)->snd_una;
	w->first_ack = 1;
पूर्ण

/*
 * @westwood_करो_filter
 * Low-pass filter. Implemented using स्थिरant coefficients.
 */
अटल अंतरभूत u32 westwood_करो_filter(u32 a, u32 b)
अणु
	वापस ((7 * a) + b) >> 3;
पूर्ण

अटल व्योम westwood_filter(काष्ठा westwood *w, u32 delta)
अणु
	/* If the filter is empty fill it with the first sample of bandwidth  */
	अगर (w->bw_ns_est == 0 && w->bw_est == 0) अणु
		w->bw_ns_est = w->bk / delta;
		w->bw_est = w->bw_ns_est;
	पूर्ण अन्यथा अणु
		w->bw_ns_est = westwood_करो_filter(w->bw_ns_est, w->bk / delta);
		w->bw_est = westwood_करो_filter(w->bw_est, w->bw_ns_est);
	पूर्ण
पूर्ण

/*
 * @westwood_pkts_acked
 * Called after processing group of packets.
 * but all westwood needs is the last sample of srtt.
 */
अटल व्योम tcp_westwood_pkts_acked(काष्ठा sock *sk,
				    स्थिर काष्ठा ack_sample *sample)
अणु
	काष्ठा westwood *w = inet_csk_ca(sk);

	अगर (sample->rtt_us > 0)
		w->rtt = usecs_to_jअगरfies(sample->rtt_us);
पूर्ण

/*
 * @westwood_update_winकरोw
 * It updates RTT evaluation winकरोw अगर it is the right moment to करो
 * it. If so it calls filter क्रम evaluating bandwidth.
 */
अटल व्योम westwood_update_winकरोw(काष्ठा sock *sk)
अणु
	काष्ठा westwood *w = inet_csk_ca(sk);
	s32 delta = tcp_jअगरfies32 - w->rtt_win_sx;

	/* Initialize w->snd_una with the first acked sequence number in order
	 * to fix mismatch between tp->snd_una and w->snd_una क्रम the first
	 * bandwidth sample
	 */
	अगर (w->first_ack) अणु
		w->snd_una = tcp_sk(sk)->snd_una;
		w->first_ack = 0;
	पूर्ण

	/*
	 * See अगर a RTT-winकरोw has passed.
	 * Be careful since अगर RTT is less than
	 * 50ms we करोn't filter but we continue 'building the sample'.
	 * This minimum limit was chosen since an estimation on small
	 * समय पूर्णांकervals is better to aव्योम...
	 * Obviously on a LAN we reasonably will always have
	 * right_bound = left_bound + WESTWOOD_RTT_MIN
	 */
	अगर (w->rtt && delta > max_t(u32, w->rtt, TCP_WESTWOOD_RTT_MIN)) अणु
		westwood_filter(w, delta);

		w->bk = 0;
		w->rtt_win_sx = tcp_jअगरfies32;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_rtt_min(काष्ठा westwood *w)
अणु
	अगर (w->reset_rtt_min) अणु
		w->rtt_min = w->rtt;
		w->reset_rtt_min = 0;
	पूर्ण अन्यथा
		w->rtt_min = min(w->rtt, w->rtt_min);
पूर्ण

/*
 * @westwood_fast_bw
 * It is called when we are in fast path. In particular it is called when
 * header prediction is successful. In such हाल in fact update is
 * straight क्रमward and करोesn't need any particular care.
 */
अटल अंतरभूत व्योम westwood_fast_bw(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा westwood *w = inet_csk_ca(sk);

	westwood_update_winकरोw(sk);

	w->bk += tp->snd_una - w->snd_una;
	w->snd_una = tp->snd_una;
	update_rtt_min(w);
पूर्ण

/*
 * @westwood_acked_count
 * This function evaluates cumul_ack क्रम evaluating bk in हाल of
 * delayed or partial acks.
 */
अटल अंतरभूत u32 westwood_acked_count(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा westwood *w = inet_csk_ca(sk);

	w->cumul_ack = tp->snd_una - w->snd_una;

	/* If cumul_ack is 0 this is a dupack since it's not moving
	 * tp->snd_una.
	 */
	अगर (!w->cumul_ack) अणु
		w->accounted += tp->mss_cache;
		w->cumul_ack = tp->mss_cache;
	पूर्ण

	अगर (w->cumul_ack > tp->mss_cache) अणु
		/* Partial or delayed ack */
		अगर (w->accounted >= w->cumul_ack) अणु
			w->accounted -= w->cumul_ack;
			w->cumul_ack = tp->mss_cache;
		पूर्ण अन्यथा अणु
			w->cumul_ack -= w->accounted;
			w->accounted = 0;
		पूर्ण
	पूर्ण

	w->snd_una = tp->snd_una;

	वापस w->cumul_ack;
पूर्ण

/*
 * TCP Westwood
 * Here limit is evaluated as Bw estimation*RTTmin (क्रम obtaining it
 * in packets we use mss_cache). Rtपंचांगin is guaranteed to be >= 2
 * so aव्योमs ever वापसing 0.
 */
अटल u32 tcp_westwood_bw_rtपंचांगin(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर काष्ठा westwood *w = inet_csk_ca(sk);

	वापस max_t(u32, (w->bw_est * w->rtt_min) / tp->mss_cache, 2);
पूर्ण

अटल व्योम tcp_westwood_ack(काष्ठा sock *sk, u32 ack_flags)
अणु
	अगर (ack_flags & CA_ACK_SLOWPATH) अणु
		काष्ठा westwood *w = inet_csk_ca(sk);

		westwood_update_winकरोw(sk);
		w->bk += westwood_acked_count(sk);

		update_rtt_min(w);
		वापस;
	पूर्ण

	westwood_fast_bw(sk);
पूर्ण

अटल व्योम tcp_westwood_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा westwood *w = inet_csk_ca(sk);

	चयन (event) अणु
	हाल CA_EVENT_COMPLETE_CWR:
		tp->snd_cwnd = tp->snd_ssthresh = tcp_westwood_bw_rtपंचांगin(sk);
		अवरोध;
	हाल CA_EVENT_LOSS:
		tp->snd_ssthresh = tcp_westwood_bw_rtपंचांगin(sk);
		/* Update RTT_min when next ack arrives */
		w->reset_rtt_min = 1;
		अवरोध;
	शेष:
		/* करोn't care */
		अवरोध;
	पूर्ण
पूर्ण

/* Extract info क्रम Tcp socket info provided via netlink. */
अटल माप_प्रकार tcp_westwood_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
				जोड़ tcp_cc_info *info)
अणु
	स्थिर काष्ठा westwood *ca = inet_csk_ca(sk);

	अगर (ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		info->vegas.tcpv_enabled = 1;
		info->vegas.tcpv_rttcnt	= 0;
		info->vegas.tcpv_rtt	= jअगरfies_to_usecs(ca->rtt);
		info->vegas.tcpv_minrtt	= jअगरfies_to_usecs(ca->rtt_min);

		*attr = INET_DIAG_VEGASINFO;
		वापस माप(काष्ठा tcpvegas_info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_westwood __पढ़ो_mostly = अणु
	.init		= tcp_westwood_init,
	.ssthresh	= tcp_reno_ssthresh,
	.cong_aव्योम	= tcp_reno_cong_aव्योम,
	.unकरो_cwnd      = tcp_reno_unकरो_cwnd,
	.cwnd_event	= tcp_westwood_event,
	.in_ack_event	= tcp_westwood_ack,
	.get_info	= tcp_westwood_info,
	.pkts_acked	= tcp_westwood_pkts_acked,

	.owner		= THIS_MODULE,
	.name		= "westwood"
पूर्ण;

अटल पूर्णांक __init tcp_westwood_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा westwood) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&tcp_westwood);
पूर्ण

अटल व्योम __निकास tcp_westwood_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_westwood);
पूर्ण

module_init(tcp_westwood_रेजिस्टर);
module_निकास(tcp_westwood_unरेजिस्टर);

MODULE_AUTHOR("Stephen Hemminger, Angelo Dell'Aera");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Westwood+");
