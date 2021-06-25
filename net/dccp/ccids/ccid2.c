<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2005, 2006 Andrea Bittau <a.bittau@cs.ucl.ac.uk>
 *
 *  Changes to meet Linux coding standards, and DCCP infraकाष्ठाure fixes.
 *
 *  Copyright (c) 2006 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

/*
 * This implementation should follow RFC 4341
 */
#समावेश <linux/slab.h>
#समावेश "../feat.h"
#समावेश "ccid2.h"


#अगर_घोषित CONFIG_IP_DCCP_CCID2_DEBUG
अटल bool ccid2_debug;
#घोषणा ccid2_pr_debug(क्रमmat, a...)	DCCP_PR_DEBUG(ccid2_debug, क्रमmat, ##a)
#अन्यथा
#घोषणा ccid2_pr_debug(क्रमmat, a...)
#पूर्ण_अगर

अटल पूर्णांक ccid2_hc_tx_alloc_seq(काष्ठा ccid2_hc_tx_sock *hc)
अणु
	काष्ठा ccid2_seq *seqp;
	पूर्णांक i;

	/* check अगर we have space to preserve the poपूर्णांकer to the buffer */
	अगर (hc->tx_seqbufc >= (माप(hc->tx_seqbuf) /
			       माप(काष्ठा ccid2_seq *)))
		वापस -ENOMEM;

	/* allocate buffer and initialize linked list */
	seqp = kदो_स्मृति_array(CCID2_SEQBUF_LEN, माप(काष्ठा ccid2_seq),
			     gfp_any());
	अगर (seqp == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < (CCID2_SEQBUF_LEN - 1); i++) अणु
		seqp[i].ccid2s_next = &seqp[i + 1];
		seqp[i + 1].ccid2s_prev = &seqp[i];
	पूर्ण
	seqp[CCID2_SEQBUF_LEN - 1].ccid2s_next = seqp;
	seqp->ccid2s_prev = &seqp[CCID2_SEQBUF_LEN - 1];

	/* This is the first allocation.  Initiate the head and tail.  */
	अगर (hc->tx_seqbufc == 0)
		hc->tx_seqh = hc->tx_seqt = seqp;
	अन्यथा अणु
		/* link the existing list with the one we just created */
		hc->tx_seqh->ccid2s_next = seqp;
		seqp->ccid2s_prev = hc->tx_seqh;

		hc->tx_seqt->ccid2s_prev = &seqp[CCID2_SEQBUF_LEN - 1];
		seqp[CCID2_SEQBUF_LEN - 1].ccid2s_next = hc->tx_seqt;
	पूर्ण

	/* store the original poपूर्णांकer to the buffer so we can मुक्त it */
	hc->tx_seqbuf[hc->tx_seqbufc] = seqp;
	hc->tx_seqbufc++;

	वापस 0;
पूर्ण

अटल पूर्णांक ccid2_hc_tx_send_packet(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (ccid2_cwnd_network_limited(ccid2_hc_tx_sk(sk)))
		वापस CCID_PACKET_WILL_DEQUEUE_LATER;
	वापस CCID_PACKET_SEND_AT_ONCE;
पूर्ण

अटल व्योम ccid2_change_l_ack_ratio(काष्ठा sock *sk, u32 val)
अणु
	u32 max_ratio = DIV_ROUND_UP(ccid2_hc_tx_sk(sk)->tx_cwnd, 2);

	/*
	 * Ensure that Ack Ratio करोes not exceed उच्चमान(cwnd/2), which is (2) from
	 * RFC 4341, 6.1.2. We ignore the statement that Ack Ratio 2 is always
	 * acceptable since this causes starvation/deadlock whenever cwnd < 2.
	 * The same problem arises when Ack Ratio is 0 (ie. Ack Ratio disabled).
	 */
	अगर (val == 0 || val > max_ratio) अणु
		DCCP_WARN("Limiting Ack Ratio (%u) to %u\n", val, max_ratio);
		val = max_ratio;
	पूर्ण
	dccp_feat_संकेत_nn_change(sk, DCCPF_ACK_RATIO,
				   min_t(u32, val, DCCPF_ACK_RATIO_MAX));
पूर्ण

अटल व्योम ccid2_check_l_ack_ratio(काष्ठा sock *sk)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	/*
	 * After a loss, idle period, application limited period, or RTO we
	 * need to check that the ack ratio is still less than the congestion
	 * winकरोw. Otherwise, we will send an entire congestion winकरोw of
	 * packets and got no response because we haven't sent ack ratio
	 * packets yet.
	 * If the ack ratio करोes need to be reduced, we reduce it to half of
	 * the congestion winकरोw (or 1 अगर that's zero) instead of to the
	 * congestion winकरोw. This prevents problems अगर one ack is lost.
	 */
	अगर (dccp_feat_nn_get(sk, DCCPF_ACK_RATIO) > hc->tx_cwnd)
		ccid2_change_l_ack_ratio(sk, hc->tx_cwnd/2 ? : 1U);
पूर्ण

अटल व्योम ccid2_change_l_seq_winकरोw(काष्ठा sock *sk, u64 val)
अणु
	dccp_feat_संकेत_nn_change(sk, DCCPF_SEQUENCE_WINDOW,
				   clamp_val(val, DCCPF_SEQ_WMIN,
						  DCCPF_SEQ_WMAX));
पूर्ण

अटल व्योम dccp_tasklet_schedule(काष्ठा sock *sk)
अणु
	काष्ठा tasklet_काष्ठा *t = &dccp_sk(sk)->dccps_xmitlet;

	अगर (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state)) अणु
		sock_hold(sk);
		__tasklet_schedule(t);
	पूर्ण
पूर्ण

अटल व्योम ccid2_hc_tx_rto_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = from_समयr(hc, t, tx_rtoसमयr);
	काष्ठा sock *sk = hc->sk;
	स्थिर bool sender_was_blocked = ccid2_cwnd_network_limited(hc);

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		sk_reset_समयr(sk, &hc->tx_rtoसमयr, jअगरfies + HZ / 5);
		जाओ out;
	पूर्ण

	ccid2_pr_debug("RTO_EXPIRE\n");

	अगर (sk->sk_state == DCCP_CLOSED)
		जाओ out;

	/* back-off समयr */
	hc->tx_rto <<= 1;
	अगर (hc->tx_rto > DCCP_RTO_MAX)
		hc->tx_rto = DCCP_RTO_MAX;

	/* adjust pipe, cwnd etc */
	hc->tx_ssthresh = hc->tx_cwnd / 2;
	अगर (hc->tx_ssthresh < 2)
		hc->tx_ssthresh = 2;
	hc->tx_cwnd	= 1;
	hc->tx_pipe	= 0;

	/* clear state about stuff we sent */
	hc->tx_seqt = hc->tx_seqh;
	hc->tx_packets_acked = 0;

	/* clear ack ratio state. */
	hc->tx_rpseq    = 0;
	hc->tx_rpdupack = -1;
	ccid2_change_l_ack_ratio(sk, 1);

	/* अगर we were blocked beक्रमe, we may now send cwnd=1 packet */
	अगर (sender_was_blocked)
		dccp_tasklet_schedule(sk);
	/* restart backed-off समयr */
	sk_reset_समयr(sk, &hc->tx_rtoसमयr, jअगरfies + hc->tx_rto);
out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/*
 *	Congestion winकरोw validation (RFC 2861).
 */
अटल bool ccid2_करो_cwv = true;
module_param(ccid2_करो_cwv, bool, 0644);
MODULE_PARM_DESC(ccid2_करो_cwv, "Perform RFC2861 Congestion Window Validation");

/**
 * ccid2_update_used_winकरोw  -  Track how much of cwnd is actually used
 * @hc: socket to update winकरोw
 * @new_wnd: new winकरोw values to add पूर्णांकo the filter
 *
 * This is करोne in addition to CWV. The sender needs to have an idea of how many
 * packets may be in flight, to set the local Sequence Winकरोw value accordingly
 * (RFC 4340, 7.5.2). The CWV mechanism is exploited to keep track of the
 * maximum-used winकरोw. We use an EWMA low-pass filter to filter out noise.
 */
अटल व्योम ccid2_update_used_winकरोw(काष्ठा ccid2_hc_tx_sock *hc, u32 new_wnd)
अणु
	hc->tx_expected_wnd = (3 * hc->tx_expected_wnd + new_wnd) / 4;
पूर्ण

/* This borrows the code of tcp_cwnd_application_limited() */
अटल व्योम ccid2_cwnd_application_limited(काष्ठा sock *sk, स्थिर u32 now)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	/* करोn't reduce cwnd below the initial winकरोw (IW) */
	u32 init_win = rfc3390_bytes_to_packets(dccp_sk(sk)->dccps_mss_cache),
	    win_used = max(hc->tx_cwnd_used, init_win);

	अगर (win_used < hc->tx_cwnd) अणु
		hc->tx_ssthresh = max(hc->tx_ssthresh,
				     (hc->tx_cwnd >> 1) + (hc->tx_cwnd >> 2));
		hc->tx_cwnd = (hc->tx_cwnd + win_used) >> 1;
	पूर्ण
	hc->tx_cwnd_used  = 0;
	hc->tx_cwnd_stamp = now;

	ccid2_check_l_ack_ratio(sk);
पूर्ण

/* This borrows the code of tcp_cwnd_restart() */
अटल व्योम ccid2_cwnd_restart(काष्ठा sock *sk, स्थिर u32 now)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	u32 cwnd = hc->tx_cwnd, restart_cwnd,
	    iwnd = rfc3390_bytes_to_packets(dccp_sk(sk)->dccps_mss_cache);
	s32 delta = now - hc->tx_lsndसमय;

	hc->tx_ssthresh = max(hc->tx_ssthresh, (cwnd >> 1) + (cwnd >> 2));

	/* करोn't reduce cwnd below the initial winकरोw (IW) */
	restart_cwnd = min(cwnd, iwnd);

	जबतक ((delta -= hc->tx_rto) >= 0 && cwnd > restart_cwnd)
		cwnd >>= 1;
	hc->tx_cwnd = max(cwnd, restart_cwnd);
	hc->tx_cwnd_stamp = now;
	hc->tx_cwnd_used  = 0;

	ccid2_check_l_ack_ratio(sk);
पूर्ण

अटल व्योम ccid2_hc_tx_packet_sent(काष्ठा sock *sk, अचिन्हित पूर्णांक len)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	स्थिर u32 now = ccid2_jअगरfies32;
	काष्ठा ccid2_seq *next;

	/* slow-start after idle periods (RFC 2581, RFC 2861) */
	अगर (ccid2_करो_cwv && !hc->tx_pipe &&
	    (s32)(now - hc->tx_lsndसमय) >= hc->tx_rto)
		ccid2_cwnd_restart(sk, now);

	hc->tx_lsndसमय = now;
	hc->tx_pipe    += 1;

	/* see whether cwnd was fully used (RFC 2861), update expected winकरोw */
	अगर (ccid2_cwnd_network_limited(hc)) अणु
		ccid2_update_used_winकरोw(hc, hc->tx_cwnd);
		hc->tx_cwnd_used  = 0;
		hc->tx_cwnd_stamp = now;
	पूर्ण अन्यथा अणु
		अगर (hc->tx_pipe > hc->tx_cwnd_used)
			hc->tx_cwnd_used = hc->tx_pipe;

		ccid2_update_used_winकरोw(hc, hc->tx_cwnd_used);

		अगर (ccid2_करो_cwv && (s32)(now - hc->tx_cwnd_stamp) >= hc->tx_rto)
			ccid2_cwnd_application_limited(sk, now);
	पूर्ण

	hc->tx_seqh->ccid2s_seq   = dp->dccps_gss;
	hc->tx_seqh->ccid2s_acked = 0;
	hc->tx_seqh->ccid2s_sent  = now;

	next = hc->tx_seqh->ccid2s_next;
	/* check अगर we need to alloc more space */
	अगर (next == hc->tx_seqt) अणु
		अगर (ccid2_hc_tx_alloc_seq(hc)) अणु
			DCCP_CRIT("packet history - out of memory!");
			/* FIXME: find a more graceful way to bail out */
			वापस;
		पूर्ण
		next = hc->tx_seqh->ccid2s_next;
		BUG_ON(next == hc->tx_seqt);
	पूर्ण
	hc->tx_seqh = next;

	ccid2_pr_debug("cwnd=%d pipe=%d\n", hc->tx_cwnd, hc->tx_pipe);

	/*
	 * FIXME: The code below is broken and the variables have been हटाओd
	 * from the socket काष्ठा. The `ackloss' variable was always set to 0,
	 * and with arsent there are several problems:
	 *  (i) it करोesn't just count the number of Acks, but all sent packets;
	 *  (ii) it is expressed in # of packets, not # of winकरोws, so the
	 *  comparison below uses the wrong क्रमmula: Appendix A of RFC 4341
	 *  comes up with the number K = cwnd / (R^2 - R) of consecutive winकरोws
	 *  of data with no lost or marked Ack packets. If arsent were the # of
	 *  consecutive Acks received without loss, then Ack Ratio needs to be
	 *  decreased by 1 when
	 *	      arsent >=  K * cwnd / R  =  cwnd^2 / (R^3 - R^2)
	 *  where cwnd / R is the number of Acks received per winकरोw of data
	 *  (cf. RFC 4341, App. A). The problems are that
	 *  - arsent counts other packets as well;
	 *  - the comparison uses a क्रमmula dअगरferent from RFC 4341;
	 *  - computing a cubic/quadratic equation each समय is too complicated.
	 *  Hence a dअगरferent algorithm is needed.
	 */
#अगर 0
	/* Ack Ratio.  Need to मुख्यtain a concept of how many winकरोws we sent */
	hc->tx_arsent++;
	/* We had an ack loss in this winकरोw... */
	अगर (hc->tx_ackloss) अणु
		अगर (hc->tx_arsent >= hc->tx_cwnd) अणु
			hc->tx_arsent  = 0;
			hc->tx_ackloss = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No acks lost up to now... */
		/* decrease ack ratio अगर enough packets were sent */
		अगर (dp->dccps_l_ack_ratio > 1) अणु
			/* XXX करोn't calculate denominator each समय */
			पूर्णांक denom = dp->dccps_l_ack_ratio * dp->dccps_l_ack_ratio -
				    dp->dccps_l_ack_ratio;

			denom = hc->tx_cwnd * hc->tx_cwnd / denom;

			अगर (hc->tx_arsent >= denom) अणु
				ccid2_change_l_ack_ratio(sk, dp->dccps_l_ack_ratio - 1);
				hc->tx_arsent = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* we can't increase ack ratio further [1] */
			hc->tx_arsent = 0; /* or maybe set it to cwnd*/
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	sk_reset_समयr(sk, &hc->tx_rtoसमयr, jअगरfies + hc->tx_rto);

#अगर_घोषित CONFIG_IP_DCCP_CCID2_DEBUG
	करो अणु
		काष्ठा ccid2_seq *seqp = hc->tx_seqt;

		जबतक (seqp != hc->tx_seqh) अणु
			ccid2_pr_debug("out seq=%llu acked=%d time=%u\n",
				       (अचिन्हित दीर्घ दीर्घ)seqp->ccid2s_seq,
				       seqp->ccid2s_acked, seqp->ccid2s_sent);
			seqp = seqp->ccid2s_next;
		पूर्ण
	पूर्ण जबतक (0);
	ccid2_pr_debug("=========\n");
#पूर्ण_अगर
पूर्ण

/**
 * ccid2_rtt_estimator - Sample RTT and compute RTO using RFC2988 algorithm
 * @sk: socket to perक्रमm estimator on
 *
 * This code is almost identical with TCP's tcp_rtt_estimator(), since
 * - it has a higher sampling frequency (recommended by RFC 1323),
 * - the RTO करोes not collapse पूर्णांकo RTT due to RTTVAR going towards zero,
 * - it is simple (cf. more complex proposals such as Eअगरel समयr or research
 *   which suggests that the gain should be set according to winकरोw size),
 * - in tests it was found to work well with CCID2 [gerrit].
 */
अटल व्योम ccid2_rtt_estimator(काष्ठा sock *sk, स्थिर दीर्घ mrtt)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	दीर्घ m = mrtt ? : 1;

	अगर (hc->tx_srtt == 0) अणु
		/* First measurement m */
		hc->tx_srtt = m << 3;
		hc->tx_mdev = m << 1;

		hc->tx_mdev_max = max(hc->tx_mdev, tcp_rto_min(sk));
		hc->tx_rttvar   = hc->tx_mdev_max;

		hc->tx_rtt_seq  = dccp_sk(sk)->dccps_gss;
	पूर्ण अन्यथा अणु
		/* Update scaled SRTT as SRTT += 1/8 * (m - SRTT) */
		m -= (hc->tx_srtt >> 3);
		hc->tx_srtt += m;

		/* Similarly, update scaled mdev with regard to |m| */
		अगर (m < 0) अणु
			m = -m;
			m -= (hc->tx_mdev >> 2);
			/*
			 * This neutralises RTO increase when RTT < SRTT - mdev
			 * (see P. Sarolahti, A. Kuznetsov,"Congestion Control
			 * in Linux TCP", USENIX 2002, pp. 49-62).
			 */
			अगर (m > 0)
				m >>= 3;
		पूर्ण अन्यथा अणु
			m -= (hc->tx_mdev >> 2);
		पूर्ण
		hc->tx_mdev += m;

		अगर (hc->tx_mdev > hc->tx_mdev_max) अणु
			hc->tx_mdev_max = hc->tx_mdev;
			अगर (hc->tx_mdev_max > hc->tx_rttvar)
				hc->tx_rttvar = hc->tx_mdev_max;
		पूर्ण

		/*
		 * Decay RTTVAR at most once per flight, exploiting that
		 *  1) pipe <= cwnd <= Sequence_Winकरोw = W  (RFC 4340, 7.5.2)
		 *  2) AWL = GSS-W+1 <= GAR <= GSS          (RFC 4340, 7.5.1)
		 * GAR is a useful bound क्रम FlightSize = pipe.
		 * AWL is probably too low here, as it over-estimates pipe.
		 */
		अगर (after48(dccp_sk(sk)->dccps_gar, hc->tx_rtt_seq)) अणु
			अगर (hc->tx_mdev_max < hc->tx_rttvar)
				hc->tx_rttvar -= (hc->tx_rttvar -
						  hc->tx_mdev_max) >> 2;
			hc->tx_rtt_seq  = dccp_sk(sk)->dccps_gss;
			hc->tx_mdev_max = tcp_rto_min(sk);
		पूर्ण
	पूर्ण

	/*
	 * Set RTO from SRTT and RTTVAR
	 * As in TCP, 4 * RTTVAR >= TCP_RTO_MIN, giving a minimum RTO of 200 ms.
	 * This agrees with RFC 4341, 5:
	 *	"Because DCCP करोes not retransmit data, DCCP करोes not require
	 *	 TCP's recommended minimum समयout of one second".
	 */
	hc->tx_rto = (hc->tx_srtt >> 3) + hc->tx_rttvar;

	अगर (hc->tx_rto > DCCP_RTO_MAX)
		hc->tx_rto = DCCP_RTO_MAX;
पूर्ण

अटल व्योम ccid2_new_ack(काष्ठा sock *sk, काष्ठा ccid2_seq *seqp,
			  अचिन्हित पूर्णांक *maxincr)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	पूर्णांक r_seq_used = hc->tx_cwnd / dp->dccps_l_ack_ratio;

	अगर (hc->tx_cwnd < dp->dccps_l_seq_win &&
	    r_seq_used < dp->dccps_r_seq_win) अणु
		अगर (hc->tx_cwnd < hc->tx_ssthresh) अणु
			अगर (*maxincr > 0 && ++hc->tx_packets_acked >= 2) अणु
				hc->tx_cwnd += 1;
				*maxincr    -= 1;
				hc->tx_packets_acked = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (++hc->tx_packets_acked >= hc->tx_cwnd) अणु
			hc->tx_cwnd += 1;
			hc->tx_packets_acked = 0;
		पूर्ण
	पूर्ण

	/*
	 * Adjust the local sequence winकरोw and the ack ratio to allow about
	 * 5 बार the number of packets in the network (RFC 4340 7.5.2)
	 */
	अगर (r_seq_used * CCID2_WIN_CHANGE_FACTOR >= dp->dccps_r_seq_win)
		ccid2_change_l_ack_ratio(sk, dp->dccps_l_ack_ratio * 2);
	अन्यथा अगर (r_seq_used * CCID2_WIN_CHANGE_FACTOR < dp->dccps_r_seq_win/2)
		ccid2_change_l_ack_ratio(sk, dp->dccps_l_ack_ratio / 2 ? : 1U);

	अगर (hc->tx_cwnd * CCID2_WIN_CHANGE_FACTOR >= dp->dccps_l_seq_win)
		ccid2_change_l_seq_winकरोw(sk, dp->dccps_l_seq_win * 2);
	अन्यथा अगर (hc->tx_cwnd * CCID2_WIN_CHANGE_FACTOR < dp->dccps_l_seq_win/2)
		ccid2_change_l_seq_winकरोw(sk, dp->dccps_l_seq_win / 2);

	/*
	 * FIXME: RTT is sampled several बार per acknowledgment (क्रम each
	 * entry in the Ack Vector), instead of once per Ack (as in TCP SACK).
	 * This causes the RTT to be over-estimated, since the older entries
	 * in the Ack Vector have earlier sending बार.
	 * The cleanest solution is to not use the ccid2s_sent field at all
	 * and instead use DCCP बारtamps: requires changes in other places.
	 */
	ccid2_rtt_estimator(sk, ccid2_jअगरfies32 - seqp->ccid2s_sent);
पूर्ण

अटल व्योम ccid2_congestion_event(काष्ठा sock *sk, काष्ठा ccid2_seq *seqp)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	अगर ((s32)(seqp->ccid2s_sent - hc->tx_last_cong) < 0) अणु
		ccid2_pr_debug("Multiple losses in an RTT---treating as one\n");
		वापस;
	पूर्ण

	hc->tx_last_cong = ccid2_jअगरfies32;

	hc->tx_cwnd      = hc->tx_cwnd / 2 ? : 1U;
	hc->tx_ssthresh  = max(hc->tx_cwnd, 2U);

	ccid2_check_l_ack_ratio(sk);
पूर्ण

अटल पूर्णांक ccid2_hc_tx_parse_options(काष्ठा sock *sk, u8 packet_type,
				     u8 option, u8 *optval, u8 optlen)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	चयन (option) अणु
	हाल DCCPO_ACK_VECTOR_0:
	हाल DCCPO_ACK_VECTOR_1:
		वापस dccp_ackvec_parsed_add(&hc->tx_av_chunks, optval, optlen,
					      option - DCCPO_ACK_VECTOR_0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ccid2_hc_tx_packet_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	स्थिर bool sender_was_blocked = ccid2_cwnd_network_limited(hc);
	काष्ठा dccp_ackvec_parsed *avp;
	u64 ackno, seqno;
	काष्ठा ccid2_seq *seqp;
	पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक maxincr = 0;

	/* check reverse path congestion */
	seqno = DCCP_SKB_CB(skb)->dccpd_seq;

	/* XXX this whole "algorithm" is broken.  Need to fix it to keep track
	 * of the seqnos of the dupacks so that rpseq and rpdupack are correct
	 * -sorbo.
	 */
	/* need to bootstrap */
	अगर (hc->tx_rpdupack == -1) अणु
		hc->tx_rpdupack = 0;
		hc->tx_rpseq    = seqno;
	पूर्ण अन्यथा अणु
		/* check अगर packet is consecutive */
		अगर (dccp_delta_seqno(hc->tx_rpseq, seqno) == 1)
			hc->tx_rpseq = seqno;
		/* it's a later packet */
		अन्यथा अगर (after48(seqno, hc->tx_rpseq)) अणु
			hc->tx_rpdupack++;

			/* check अगर we got enough dupacks */
			अगर (hc->tx_rpdupack >= NUMDUPACK) अणु
				hc->tx_rpdupack = -1; /* XXX lame */
				hc->tx_rpseq    = 0;
#अगर_घोषित __CCID2_COPES_GRACEFULLY_WITH_ACK_CONGESTION_CONTROL__
				/*
				 * FIXME: Ack Congestion Control is broken; in
				 * the current state instabilities occurred with
				 * Ack Ratios greater than 1; causing hang-ups
				 * and दीर्घ RTO समयouts. This needs to be fixed
				 * beक्रमe खोलोing up dynamic changes. -- gerrit
				 */
				ccid2_change_l_ack_ratio(sk, 2 * dp->dccps_l_ack_ratio);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
	पूर्ण

	/* check क्रमward path congestion */
	अगर (dccp_packet_without_ack(skb))
		वापस;

	/* still didn't send out new data packets */
	अगर (hc->tx_seqh == hc->tx_seqt)
		जाओ करोne;

	ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;
	अगर (after48(ackno, hc->tx_high_ack))
		hc->tx_high_ack = ackno;

	seqp = hc->tx_seqt;
	जबतक (beक्रमe48(seqp->ccid2s_seq, ackno)) अणु
		seqp = seqp->ccid2s_next;
		अगर (seqp == hc->tx_seqh) अणु
			seqp = hc->tx_seqh->ccid2s_prev;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * In slow-start, cwnd can increase up to a maximum of Ack Ratio/2
	 * packets per acknowledgement. Rounding up aव्योमs that cwnd is not
	 * advanced when Ack Ratio is 1 and gives a slight edge otherwise.
	 */
	अगर (hc->tx_cwnd < hc->tx_ssthresh)
		maxincr = DIV_ROUND_UP(dp->dccps_l_ack_ratio, 2);

	/* go through all ack vectors */
	list_क्रम_each_entry(avp, &hc->tx_av_chunks, node) अणु
		/* go through this ack vector */
		क्रम (; avp->len--; avp->vec++) अणु
			u64 ackno_end_rl = SUB48(ackno,
						 dccp_ackvec_runlen(avp->vec));

			ccid2_pr_debug("ackvec %llu |%u,%u|\n",
				       (अचिन्हित दीर्घ दीर्घ)ackno,
				       dccp_ackvec_state(avp->vec) >> 6,
				       dccp_ackvec_runlen(avp->vec));
			/* अगर the seqno we are analyzing is larger than the
			 * current ackno, then move towards the tail of our
			 * seqnos.
			 */
			जबतक (after48(seqp->ccid2s_seq, ackno)) अणु
				अगर (seqp == hc->tx_seqt) अणु
					करोne = 1;
					अवरोध;
				पूर्ण
				seqp = seqp->ccid2s_prev;
			पूर्ण
			अगर (करोne)
				अवरोध;

			/* check all seqnos in the range of the vector
			 * run length
			 */
			जबतक (between48(seqp->ccid2s_seq,ackno_end_rl,ackno)) अणु
				स्थिर u8 state = dccp_ackvec_state(avp->vec);

				/* new packet received or marked */
				अगर (state != DCCPAV_NOT_RECEIVED &&
				    !seqp->ccid2s_acked) अणु
					अगर (state == DCCPAV_ECN_MARKED)
						ccid2_congestion_event(sk,
								       seqp);
					अन्यथा
						ccid2_new_ack(sk, seqp,
							      &maxincr);

					seqp->ccid2s_acked = 1;
					ccid2_pr_debug("Got ack for %llu\n",
						       (अचिन्हित दीर्घ दीर्घ)seqp->ccid2s_seq);
					hc->tx_pipe--;
				पूर्ण
				अगर (seqp == hc->tx_seqt) अणु
					करोne = 1;
					अवरोध;
				पूर्ण
				seqp = seqp->ccid2s_prev;
			पूर्ण
			अगर (करोne)
				अवरोध;

			ackno = SUB48(ackno_end_rl, 1);
		पूर्ण
		अगर (करोne)
			अवरोध;
	पूर्ण

	/* The state about what is acked should be correct now
	 * Check क्रम NUMDUPACK
	 */
	seqp = hc->tx_seqt;
	जबतक (beक्रमe48(seqp->ccid2s_seq, hc->tx_high_ack)) अणु
		seqp = seqp->ccid2s_next;
		अगर (seqp == hc->tx_seqh) अणु
			seqp = hc->tx_seqh->ccid2s_prev;
			अवरोध;
		पूर्ण
	पूर्ण
	करोne = 0;
	जबतक (1) अणु
		अगर (seqp->ccid2s_acked) अणु
			करोne++;
			अगर (करोne == NUMDUPACK)
				अवरोध;
		पूर्ण
		अगर (seqp == hc->tx_seqt)
			अवरोध;
		seqp = seqp->ccid2s_prev;
	पूर्ण

	/* If there are at least 3 acknowledgements, anything unacknowledged
	 * below the last sequence number is considered lost
	 */
	अगर (करोne == NUMDUPACK) अणु
		काष्ठा ccid2_seq *last_acked = seqp;

		/* check क्रम lost packets */
		जबतक (1) अणु
			अगर (!seqp->ccid2s_acked) अणु
				ccid2_pr_debug("Packet lost: %llu\n",
					       (अचिन्हित दीर्घ दीर्घ)seqp->ccid2s_seq);
				/* XXX need to traverse from tail -> head in
				 * order to detect multiple congestion events in
				 * one ack vector.
				 */
				ccid2_congestion_event(sk, seqp);
				hc->tx_pipe--;
			पूर्ण
			अगर (seqp == hc->tx_seqt)
				अवरोध;
			seqp = seqp->ccid2s_prev;
		पूर्ण

		hc->tx_seqt = last_acked;
	पूर्ण

	/* trim acked packets in tail */
	जबतक (hc->tx_seqt != hc->tx_seqh) अणु
		अगर (!hc->tx_seqt->ccid2s_acked)
			अवरोध;

		hc->tx_seqt = hc->tx_seqt->ccid2s_next;
	पूर्ण

	/* restart RTO समयr अगर not all outstanding data has been acked */
	अगर (hc->tx_pipe == 0)
		sk_stop_समयr(sk, &hc->tx_rtoसमयr);
	अन्यथा
		sk_reset_समयr(sk, &hc->tx_rtoसमयr, jअगरfies + hc->tx_rto);
करोne:
	/* check अगर incoming Acks allow pending packets to be sent */
	अगर (sender_was_blocked && !ccid2_cwnd_network_limited(hc))
		dccp_tasklet_schedule(sk);
	dccp_ackvec_parsed_cleanup(&hc->tx_av_chunks);
पूर्ण

अटल पूर्णांक ccid2_hc_tx_init(काष्ठा ccid *ccid, काष्ठा sock *sk)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid_priv(ccid);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	u32 max_ratio;

	/* RFC 4341, 5: initialise ssthresh to arbitrarily high (max) value */
	hc->tx_ssthresh = ~0U;

	/* Use larger initial winकरोws (RFC 4341, section 5). */
	hc->tx_cwnd = rfc3390_bytes_to_packets(dp->dccps_mss_cache);
	hc->tx_expected_wnd = hc->tx_cwnd;

	/* Make sure that Ack Ratio is enabled and within bounds. */
	max_ratio = DIV_ROUND_UP(hc->tx_cwnd, 2);
	अगर (dp->dccps_l_ack_ratio == 0 || dp->dccps_l_ack_ratio > max_ratio)
		dp->dccps_l_ack_ratio = max_ratio;

	/* XXX init ~ to winकरोw size... */
	अगर (ccid2_hc_tx_alloc_seq(hc))
		वापस -ENOMEM;

	hc->tx_rto	 = DCCP_TIMEOUT_INIT;
	hc->tx_rpdupack  = -1;
	hc->tx_last_cong = hc->tx_lsndसमय = hc->tx_cwnd_stamp = ccid2_jअगरfies32;
	hc->tx_cwnd_used = 0;
	hc->sk		 = sk;
	समयr_setup(&hc->tx_rtoसमयr, ccid2_hc_tx_rto_expire, 0);
	INIT_LIST_HEAD(&hc->tx_av_chunks);
	वापस 0;
पूर्ण

अटल व्योम ccid2_hc_tx_निकास(काष्ठा sock *sk)
अणु
	काष्ठा ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	पूर्णांक i;

	sk_stop_समयr(sk, &hc->tx_rtoसमयr);

	क्रम (i = 0; i < hc->tx_seqbufc; i++)
		kमुक्त(hc->tx_seqbuf[i]);
	hc->tx_seqbufc = 0;
	dccp_ackvec_parsed_cleanup(&hc->tx_av_chunks);
पूर्ण

अटल व्योम ccid2_hc_rx_packet_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ccid2_hc_rx_sock *hc = ccid2_hc_rx_sk(sk);

	अगर (!dccp_data_packet(skb))
		वापस;

	अगर (++hc->rx_num_data_pkts >= dccp_sk(sk)->dccps_r_ack_ratio) अणु
		dccp_send_ack(sk);
		hc->rx_num_data_pkts = 0;
	पूर्ण
पूर्ण

काष्ठा ccid_operations ccid2_ops = अणु
	.ccid_id		  = DCCPC_CCID2,
	.ccid_name		  = "TCP-like",
	.ccid_hc_tx_obj_size	  = माप(काष्ठा ccid2_hc_tx_sock),
	.ccid_hc_tx_init	  = ccid2_hc_tx_init,
	.ccid_hc_tx_निकास	  = ccid2_hc_tx_निकास,
	.ccid_hc_tx_send_packet	  = ccid2_hc_tx_send_packet,
	.ccid_hc_tx_packet_sent	  = ccid2_hc_tx_packet_sent,
	.ccid_hc_tx_parse_options = ccid2_hc_tx_parse_options,
	.ccid_hc_tx_packet_recv	  = ccid2_hc_tx_packet_recv,
	.ccid_hc_rx_obj_size	  = माप(काष्ठा ccid2_hc_rx_sock),
	.ccid_hc_rx_packet_recv	  = ccid2_hc_rx_packet_recv,
पूर्ण;

#अगर_घोषित CONFIG_IP_DCCP_CCID2_DEBUG
module_param(ccid2_debug, bool, 0644);
MODULE_PARM_DESC(ccid2_debug, "Enable CCID-2 debug messages");
#पूर्ण_अगर
