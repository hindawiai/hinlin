<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/tcp.h>
#समावेश <net/tcp.h>

अटल bool tcp_rack_sent_after(u64 t1, u64 t2, u32 seq1, u32 seq2)
अणु
	वापस t1 > t2 || (t1 == t2 && after(seq1, seq2));
पूर्ण

अटल u32 tcp_rack_reo_wnd(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tp->reord_seen) अणु
		/* If reordering has not been observed, be aggressive during
		 * the recovery or starting the recovery by DUPACK threshold.
		 */
		अगर (inet_csk(sk)->icsk_ca_state >= TCP_CA_Recovery)
			वापस 0;

		अगर (tp->sacked_out >= tp->reordering &&
		    !(sock_net(sk)->ipv4.sysctl_tcp_recovery & TCP_RACK_NO_DUPTHRESH))
			वापस 0;
	पूर्ण

	/* To be more reordering resilient, allow min_rtt/4 settling delay.
	 * Use min_rtt instead of the smoothed RTT because reordering is
	 * often a path property and less related to queuing or delayed ACKs.
	 * Upon receiving DSACKs, linearly increase the winकरोw up to the
	 * smoothed RTT.
	 */
	वापस min((tcp_min_rtt(tp) >> 2) * tp->rack.reo_wnd_steps,
		   tp->srtt_us >> 3);
पूर्ण

s32 tcp_rack_skb_समयout(काष्ठा tcp_sock *tp, काष्ठा sk_buff *skb, u32 reo_wnd)
अणु
	वापस tp->rack.rtt_us + reo_wnd -
	       tcp_stamp_us_delta(tp->tcp_mstamp, tcp_skb_बारtamp_us(skb));
पूर्ण

/* RACK loss detection (IETF draft draft-ietf-tcpm-rack-01):
 *
 * Marks a packet lost, अगर some packet sent later has been (s)acked.
 * The underlying idea is similar to the traditional dupthresh and FACK
 * but they look at dअगरferent metrics:
 *
 * dupthresh: 3 OOO packets delivered (packet count)
 * FACK: sequence delta to highest sacked sequence (sequence space)
 * RACK: sent समय delta to the latest delivered packet (समय करोमुख्य)
 *
 * The advantage of RACK is it applies to both original and retransmitted
 * packet and thereक्रमe is robust against tail losses. Another advantage
 * is being more resilient to reordering by simply allowing some
 * "settling delay", instead of tweaking the dupthresh.
 *
 * When tcp_rack_detect_loss() detects some packets are lost and we
 * are not alपढ़ोy in the CA_Recovery state, either tcp_rack_reo_समयout()
 * or tcp_समय_प्रकारo_recover()'s "Trick#1: the loss is proven" code path will
 * make us enter the CA_Recovery state.
 */
अटल व्योम tcp_rack_detect_loss(काष्ठा sock *sk, u32 *reo_समयout)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb, *n;
	u32 reo_wnd;

	*reo_समयout = 0;
	reo_wnd = tcp_rack_reo_wnd(sk);
	list_क्रम_each_entry_safe(skb, n, &tp->tsorted_sent_queue,
				 tcp_tsorted_anchor) अणु
		काष्ठा tcp_skb_cb *scb = TCP_SKB_CB(skb);
		s32 reमुख्यing;

		/* Skip ones marked lost but not yet retransmitted */
		अगर ((scb->sacked & TCPCB_LOST) &&
		    !(scb->sacked & TCPCB_SACKED_RETRANS))
			जारी;

		अगर (!tcp_rack_sent_after(tp->rack.mstamp,
					 tcp_skb_बारtamp_us(skb),
					 tp->rack.end_seq, scb->end_seq))
			अवरोध;

		/* A packet is lost अगर it has not been s/acked beyond
		 * the recent RTT plus the reordering winकरोw.
		 */
		reमुख्यing = tcp_rack_skb_समयout(tp, skb, reo_wnd);
		अगर (reमुख्यing <= 0) अणु
			tcp_mark_skb_lost(sk, skb);
			list_del_init(&skb->tcp_tsorted_anchor);
		पूर्ण अन्यथा अणु
			/* Record maximum रुको समय */
			*reo_समयout = max_t(u32, *reo_समयout, reमुख्यing);
		पूर्ण
	पूर्ण
पूर्ण

bool tcp_rack_mark_lost(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 समयout;

	अगर (!tp->rack.advanced)
		वापस false;

	/* Reset the advanced flag to aव्योम unnecessary queue scanning */
	tp->rack.advanced = 0;
	tcp_rack_detect_loss(sk, &समयout);
	अगर (समयout) अणु
		समयout = usecs_to_jअगरfies(समयout) + TCP_TIMEOUT_MIN;
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_REO_TIMEOUT,
					  समयout, inet_csk(sk)->icsk_rto);
	पूर्ण
	वापस !!समयout;
पूर्ण

/* Record the most recently (re)sent समय among the (s)acked packets
 * This is "Step 3: Advance RACK.xmit_time and update RACK.RTT" from
 * draft-cheng-tcpm-rack-00.txt
 */
व्योम tcp_rack_advance(काष्ठा tcp_sock *tp, u8 sacked, u32 end_seq,
		      u64 xmit_समय)
अणु
	u32 rtt_us;

	rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, xmit_समय);
	अगर (rtt_us < tcp_min_rtt(tp) && (sacked & TCPCB_RETRANS)) अणु
		/* If the sacked packet was retransmitted, it's ambiguous
		 * whether the retransmission or the original (or the prior
		 * retransmission) was sacked.
		 *
		 * If the original is lost, there is no ambiguity. Otherwise
		 * we assume the original can be delayed up to aRTT + min_rtt.
		 * the aRTT term is bounded by the fast recovery or समयout,
		 * so it's at least one RTT (i.e., retransmission is at least
		 * an RTT later).
		 */
		वापस;
	पूर्ण
	tp->rack.advanced = 1;
	tp->rack.rtt_us = rtt_us;
	अगर (tcp_rack_sent_after(xmit_समय, tp->rack.mstamp,
				end_seq, tp->rack.end_seq)) अणु
		tp->rack.mstamp = xmit_समय;
		tp->rack.end_seq = end_seq;
	पूर्ण
पूर्ण

/* We have रुकोed दीर्घ enough to accommodate reordering. Mark the expired
 * packets lost and retransmit them.
 */
व्योम tcp_rack_reo_समयout(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 समयout, prior_inflight;
	u32 lost = tp->lost;

	prior_inflight = tcp_packets_in_flight(tp);
	tcp_rack_detect_loss(sk, &समयout);
	अगर (prior_inflight != tcp_packets_in_flight(tp)) अणु
		अगर (inet_csk(sk)->icsk_ca_state != TCP_CA_Recovery) अणु
			tcp_enter_recovery(sk, false);
			अगर (!inet_csk(sk)->icsk_ca_ops->cong_control)
				tcp_cwnd_reduction(sk, 1, tp->lost - lost, 0);
		पूर्ण
		tcp_xmit_retransmit_queue(sk);
	पूर्ण
	अगर (inet_csk(sk)->icsk_pending != ICSK_TIME_RETRANS)
		tcp_rearm_rto(sk);
पूर्ण

/* Updates the RACK's reo_wnd based on DSACK and no. of recoveries.
 *
 * If DSACK is received, increment reo_wnd by min_rtt/4 (upper bounded
 * by srtt), since there is possibility that spurious retransmission was
 * due to reordering delay दीर्घer than reo_wnd.
 *
 * Persist the current reo_wnd value क्रम TCP_RACK_RECOVERY_THRESH (16)
 * no. of successful recoveries (accounts क्रम full DSACK-based loss
 * recovery unकरो). After that, reset it to शेष (min_rtt/4).
 *
 * At max, reo_wnd is incremented only once per rtt. So that the new
 * DSACK on which we are reacting, is due to the spurious retx (approx)
 * after the reo_wnd has been updated last समय.
 *
 * reo_wnd is tracked in terms of steps (of min_rtt/4), rather than
 * असलolute value to account क्रम change in rtt.
 */
व्योम tcp_rack_update_reo_wnd(काष्ठा sock *sk, काष्ठा rate_sample *rs)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (sock_net(sk)->ipv4.sysctl_tcp_recovery & TCP_RACK_STATIC_REO_WND ||
	    !rs->prior_delivered)
		वापस;

	/* Disregard DSACK अगर a rtt has not passed since we adjusted reo_wnd */
	अगर (beक्रमe(rs->prior_delivered, tp->rack.last_delivered))
		tp->rack.dsack_seen = 0;

	/* Adjust the reo_wnd अगर update is pending */
	अगर (tp->rack.dsack_seen) अणु
		tp->rack.reo_wnd_steps = min_t(u32, 0xFF,
					       tp->rack.reo_wnd_steps + 1);
		tp->rack.dsack_seen = 0;
		tp->rack.last_delivered = tp->delivered;
		tp->rack.reo_wnd_persist = TCP_RACK_RECOVERY_THRESH;
	पूर्ण अन्यथा अगर (!tp->rack.reo_wnd_persist) अणु
		tp->rack.reo_wnd_steps = 1;
	पूर्ण
पूर्ण

/* RFC6582 NewReno recovery क्रम non-SACK connection. It simply retransmits
 * the next unacked packet upon receiving
 * a) three or more DUPACKs to start the fast recovery
 * b) an ACK acknowledging new data during the fast recovery.
 */
व्योम tcp_newreno_mark_lost(काष्ठा sock *sk, bool snd_una_advanced)
अणु
	स्थिर u8 state = inet_csk(sk)->icsk_ca_state;
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर ((state < TCP_CA_Recovery && tp->sacked_out >= tp->reordering) ||
	    (state == TCP_CA_Recovery && snd_una_advanced)) अणु
		काष्ठा sk_buff *skb = tcp_rtx_queue_head(sk);
		u32 mss;

		अगर (TCP_SKB_CB(skb)->sacked & TCPCB_LOST)
			वापस;

		mss = tcp_skb_mss(skb);
		अगर (tcp_skb_pcount(skb) > 1 && skb->len > mss)
			tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb,
				     mss, mss, GFP_ATOMIC);

		tcp_mark_skb_lost(sk, skb);
	पूर्ण
पूर्ण
