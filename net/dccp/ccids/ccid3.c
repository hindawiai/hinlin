<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-7 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2005-7 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 *
 *  An implementation of the DCCP protocol
 *
 *  This code has been developed by the University of Waikato WAND
 *  research group. For further inक्रमmation please see https://www.wand.net.nz/
 *
 *  This code also uses code from Lulea University, rereleased as GPL by its
 *  authors:
 *  Copyright (c) 2003 Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 *
 *  Changes to meet Linux coding standards, to make it meet latest ccid3 draft
 *  and to make it work as a loadable module in the DCCP stack written by
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>.
 *
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */
#समावेश "../dccp.h"
#समावेश "ccid3.h"

#समावेश <यंत्र/unaligned.h>

#अगर_घोषित CONFIG_IP_DCCP_CCID3_DEBUG
अटल bool ccid3_debug;
#घोषणा ccid3_pr_debug(क्रमmat, a...)	DCCP_PR_DEBUG(ccid3_debug, क्रमmat, ##a)
#अन्यथा
#घोषणा ccid3_pr_debug(क्रमmat, a...)
#पूर्ण_अगर

/*
 *	Transmitter Half-Connection Routines
 */
#अगर_घोषित CONFIG_IP_DCCP_CCID3_DEBUG
अटल स्थिर अक्षर *ccid3_tx_state_name(क्रमागत ccid3_hc_tx_states state)
अणु
	अटल स्थिर अक्षर *स्थिर ccid3_state_names[] = अणु
	[TFRC_SSTATE_NO_SENT]  = "NO_SENT",
	[TFRC_SSTATE_NO_FBACK] = "NO_FBACK",
	[TFRC_SSTATE_FBACK]    = "FBACK",
	पूर्ण;

	वापस ccid3_state_names[state];
पूर्ण
#पूर्ण_अगर

अटल व्योम ccid3_hc_tx_set_state(काष्ठा sock *sk,
				  क्रमागत ccid3_hc_tx_states state)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	क्रमागत ccid3_hc_tx_states oldstate = hc->tx_state;

	ccid3_pr_debug("%s(%p) %-8.8s -> %s\n",
		       dccp_role(sk), sk, ccid3_tx_state_name(oldstate),
		       ccid3_tx_state_name(state));
	WARN_ON(state == oldstate);
	hc->tx_state = state;
पूर्ण

/*
 * Compute the initial sending rate X_init in the manner of RFC 3390:
 *
 *	X_init  =  min(4 * s, max(2 * s, 4380 bytes)) / RTT
 *
 * Note that RFC 3390 uses MSS, RFC 4342 refers to RFC 3390, and rfc3448bis
 * (rev-02) clarअगरies the use of RFC 3390 with regard to the above क्रमmula.
 * For consistency with other parts of the code, X_init is scaled by 2^6.
 */
अटल अंतरभूत u64 rfc3390_initial_rate(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	स्थिर __u32 w_init = clamp_t(__u32, 4380U, 2 * hc->tx_s, 4 * hc->tx_s);

	वापस scaled_भाग(w_init << 6, hc->tx_rtt);
पूर्ण

/**
 * ccid3_update_send_पूर्णांकerval  -  Calculate new t_ipi = s / X_inst
 * @hc: socket to have the send पूर्णांकerval updated
 *
 * This respects the granularity of X_inst (64 * bytes/second).
 */
अटल व्योम ccid3_update_send_पूर्णांकerval(काष्ठा ccid3_hc_tx_sock *hc)
अणु
	hc->tx_t_ipi = scaled_भाग32(((u64)hc->tx_s) << 6, hc->tx_x);

	DCCP_BUG_ON(hc->tx_t_ipi == 0);
	ccid3_pr_debug("t_ipi=%u, s=%u, X=%u\n", hc->tx_t_ipi,
		       hc->tx_s, (अचिन्हित पूर्णांक)(hc->tx_x >> 6));
पूर्ण

अटल u32 ccid3_hc_tx_idle_rtt(काष्ठा ccid3_hc_tx_sock *hc, kसमय_प्रकार now)
अणु
	u32 delta = kसमय_us_delta(now, hc->tx_t_last_win_count);

	वापस delta / hc->tx_rtt;
पूर्ण

/**
 * ccid3_hc_tx_update_x  -  Update allowed sending rate X
 * @sk: socket to be updated
 * @stamp: most recent समय अगर available - can be left शून्य.
 *
 * This function tracks draft rfc3448bis, check there क्रम latest details.
 *
 * Note: X and X_recv are both stored in units of 64 * bytes/second, to support
 *       fine-grained resolution of sending rates. This requires scaling by 2^6
 *       throughout the code. Only X_calc is unscaled (in bytes/second).
 *
 */
अटल व्योम ccid3_hc_tx_update_x(काष्ठा sock *sk, kसमय_प्रकार *stamp)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	__u64 min_rate = 2 * hc->tx_x_recv;
	स्थिर __u64 old_x = hc->tx_x;
	kसमय_प्रकार now = stamp ? *stamp : kसमय_get_real();

	/*
	 * Handle IDLE periods: करो not reduce below RFC3390 initial sending rate
	 * when idling [RFC 4342, 5.1]. Definition of idling is from rfc3448bis:
	 * a sender is idle अगर it has not sent anything over a 2-RTT-period.
	 * For consistency with X and X_recv, min_rate is also scaled by 2^6.
	 */
	अगर (ccid3_hc_tx_idle_rtt(hc, now) >= 2) अणु
		min_rate = rfc3390_initial_rate(sk);
		min_rate = max(min_rate, 2 * hc->tx_x_recv);
	पूर्ण

	अगर (hc->tx_p > 0) अणु

		hc->tx_x = min(((__u64)hc->tx_x_calc) << 6, min_rate);
		hc->tx_x = max(hc->tx_x, (((__u64)hc->tx_s) << 6) / TFRC_T_MBI);

	पूर्ण अन्यथा अगर (kसमय_us_delta(now, hc->tx_t_ld) - (s64)hc->tx_rtt >= 0) अणु

		hc->tx_x = min(2 * hc->tx_x, min_rate);
		hc->tx_x = max(hc->tx_x,
			       scaled_भाग(((__u64)hc->tx_s) << 6, hc->tx_rtt));
		hc->tx_t_ld = now;
	पूर्ण

	अगर (hc->tx_x != old_x) अणु
		ccid3_pr_debug("X_prev=%u, X_now=%u, X_calc=%u, "
			       "X_recv=%u\n", (अचिन्हित पूर्णांक)(old_x >> 6),
			       (अचिन्हित पूर्णांक)(hc->tx_x >> 6), hc->tx_x_calc,
			       (अचिन्हित पूर्णांक)(hc->tx_x_recv >> 6));

		ccid3_update_send_पूर्णांकerval(hc);
	पूर्ण
पूर्ण

/**
 *	ccid3_hc_tx_update_s - Track the mean packet size `s'
 *	@hc: socket to be updated
 *	@len: DCCP packet payload size in bytes
 *
 *	cf. RFC 4342, 5.3 and  RFC 3448, 4.1
 */
अटल अंतरभूत व्योम ccid3_hc_tx_update_s(काष्ठा ccid3_hc_tx_sock *hc, पूर्णांक len)
अणु
	स्थिर u16 old_s = hc->tx_s;

	hc->tx_s = tfrc_ewma(hc->tx_s, len, 9);

	अगर (hc->tx_s != old_s)
		ccid3_update_send_पूर्णांकerval(hc);
पूर्ण

/*
 *	Update Winकरोw Counter using the algorithm from [RFC 4342, 8.1].
 *	As अन्यथाwhere, RTT > 0 is assumed by using dccp_sample_rtt().
 */
अटल अंतरभूत व्योम ccid3_hc_tx_update_win_count(काष्ठा ccid3_hc_tx_sock *hc,
						kसमय_प्रकार now)
अणु
	u32 delta = kसमय_us_delta(now, hc->tx_t_last_win_count),
	    quarter_rtts = (4 * delta) / hc->tx_rtt;

	अगर (quarter_rtts > 0) अणु
		hc->tx_t_last_win_count = now;
		hc->tx_last_win_count  += min(quarter_rtts, 5U);
		hc->tx_last_win_count  &= 0xF;		/* mod 16 */
	पूर्ण
पूर्ण

अटल व्योम ccid3_hc_tx_no_feedback_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = from_समयr(hc, t, tx_no_feedback_समयr);
	काष्ठा sock *sk = hc->sk;
	अचिन्हित दीर्घ t_nfb = USEC_PER_SEC / 5;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		/* Try again later. */
		/* XXX: set some sensible MIB */
		जाओ restart_समयr;
	पूर्ण

	ccid3_pr_debug("%s(%p, state=%s) - entry\n", dccp_role(sk), sk,
		       ccid3_tx_state_name(hc->tx_state));

	/* Ignore and करो not restart after leaving the established state */
	अगर ((1 << sk->sk_state) & ~(DCCPF_OPEN | DCCPF_PARTOPEN))
		जाओ out;

	/* Reset feedback state to "no feedback received" */
	अगर (hc->tx_state == TFRC_SSTATE_FBACK)
		ccid3_hc_tx_set_state(sk, TFRC_SSTATE_NO_FBACK);

	/*
	 * Determine new allowed sending rate X as per draft rfc3448bis-00, 4.4
	 * RTO is 0 अगर and only अगर no feedback has been received yet.
	 */
	अगर (hc->tx_t_rto == 0 || hc->tx_p == 0) अणु

		/* halve send rate directly */
		hc->tx_x = max(hc->tx_x / 2,
			       (((__u64)hc->tx_s) << 6) / TFRC_T_MBI);
		ccid3_update_send_पूर्णांकerval(hc);
	पूर्ण अन्यथा अणु
		/*
		 *  Modअगरy the cached value of X_recv
		 *
		 *  If (X_calc > 2 * X_recv)
		 *    X_recv = max(X_recv / 2, s / (2 * t_mbi));
		 *  Else
		 *    X_recv = X_calc / 4;
		 *
		 *  Note that X_recv is scaled by 2^6 जबतक X_calc is not
		 */
		अगर (hc->tx_x_calc > (hc->tx_x_recv >> 5))
			hc->tx_x_recv =
				max(hc->tx_x_recv / 2,
				    (((__u64)hc->tx_s) << 6) / (2*TFRC_T_MBI));
		अन्यथा अणु
			hc->tx_x_recv = hc->tx_x_calc;
			hc->tx_x_recv <<= 4;
		पूर्ण
		ccid3_hc_tx_update_x(sk, शून्य);
	पूर्ण
	ccid3_pr_debug("Reduced X to %llu/64 bytes/sec\n",
			(अचिन्हित दीर्घ दीर्घ)hc->tx_x);

	/*
	 * Set new समयout क्रम the nofeedback समयr.
	 * See comments in packet_recv() regarding the value of t_RTO.
	 */
	अगर (unlikely(hc->tx_t_rto == 0))	/* no feedback received yet */
		t_nfb = TFRC_INITIAL_TIMEOUT;
	अन्यथा
		t_nfb = max(hc->tx_t_rto, 2 * hc->tx_t_ipi);

restart_समयr:
	sk_reset_समयr(sk, &hc->tx_no_feedback_समयr,
			   jअगरfies + usecs_to_jअगरfies(t_nfb));
out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/**
 * ccid3_hc_tx_send_packet  -  Delay-based dequeueing of TX packets
 * @sk: socket to send packet from
 * @skb: next packet candidate to send on @sk
 *
 * This function uses the convention of ccid_packet_dequeue_eval() and
 * वापसs a millisecond-delay value between 0 and t_mbi = 64000 msec.
 */
अटल पूर्णांक ccid3_hc_tx_send_packet(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	kसमय_प्रकार now = kसमय_get_real();
	s64 delay;

	/*
	 * This function is called only क्रम Data and DataAck packets. Sending
	 * zero-sized Data(Ack)s is theoretically possible, but क्रम congestion
	 * control this हाल is pathological - ignore it.
	 */
	अगर (unlikely(skb->len == 0))
		वापस -EBADMSG;

	अगर (hc->tx_state == TFRC_SSTATE_NO_SENT) अणु
		sk_reset_समयr(sk, &hc->tx_no_feedback_समयr, (jअगरfies +
			       usecs_to_jअगरfies(TFRC_INITIAL_TIMEOUT)));
		hc->tx_last_win_count	= 0;
		hc->tx_t_last_win_count = now;

		/* Set t_0 क्रम initial packet */
		hc->tx_t_nom = now;

		hc->tx_s = skb->len;

		/*
		 * Use initial RTT sample when available: recommended by erratum
		 * to RFC 4342. This implements the initialisation procedure of
		 * draft rfc3448bis, section 4.2. Remember, X is scaled by 2^6.
		 */
		अगर (dp->dccps_syn_rtt) अणु
			ccid3_pr_debug("SYN RTT = %uus\n", dp->dccps_syn_rtt);
			hc->tx_rtt  = dp->dccps_syn_rtt;
			hc->tx_x    = rfc3390_initial_rate(sk);
			hc->tx_t_ld = now;
		पूर्ण अन्यथा अणु
			/*
			 * Sender करोes not have RTT sample:
			 * - set fallback RTT (RFC 4340, 3.4) since a RTT value
			 *   is needed in several parts (e.g.  winकरोw counter);
			 * - set sending rate X_pps = 1pps as per RFC 3448, 4.2.
			 */
			hc->tx_rtt = DCCP_FALLBACK_RTT;
			hc->tx_x   = hc->tx_s;
			hc->tx_x <<= 6;
		पूर्ण
		ccid3_update_send_पूर्णांकerval(hc);

		ccid3_hc_tx_set_state(sk, TFRC_SSTATE_NO_FBACK);

	पूर्ण अन्यथा अणु
		delay = kसमय_us_delta(hc->tx_t_nom, now);
		ccid3_pr_debug("delay=%ld\n", (दीर्घ)delay);
		/*
		 *	Scheduling of packet transmissions (RFC 5348, 8.3)
		 *
		 * अगर (t_now > t_nom - delta)
		 *       // send the packet now
		 * अन्यथा
		 *       // send the packet in (t_nom - t_now) milliseconds.
		 */
		अगर (delay >= TFRC_T_DELTA)
			वापस (u32)delay / USEC_PER_MSEC;

		ccid3_hc_tx_update_win_count(hc, now);
	पूर्ण

	/* prepare to send now (add options etc.) */
	dp->dccps_hc_tx_insert_options = 1;
	DCCP_SKB_CB(skb)->dccpd_ccval  = hc->tx_last_win_count;

	/* set the nominal send समय क्रम the next following packet */
	hc->tx_t_nom = kसमय_add_us(hc->tx_t_nom, hc->tx_t_ipi);
	वापस CCID_PACKET_SEND_AT_ONCE;
पूर्ण

अटल व्योम ccid3_hc_tx_packet_sent(काष्ठा sock *sk, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);

	ccid3_hc_tx_update_s(hc, len);

	अगर (tfrc_tx_hist_add(&hc->tx_hist, dccp_sk(sk)->dccps_gss))
		DCCP_CRIT("packet history - out of memory!");
पूर्ण

अटल व्योम ccid3_hc_tx_packet_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	काष्ठा tfrc_tx_hist_entry *acked;
	kसमय_प्रकार now;
	अचिन्हित दीर्घ t_nfb;
	u32 r_sample;

	/* we are only पूर्णांकerested in ACKs */
	अगर (!(DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_ACK ||
	      DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_DATAACK))
		वापस;
	/*
	 * Locate the acknowledged packet in the TX history.
	 *
	 * Returning "entry not found" here can क्रम instance happen when
	 *  - the host has not sent out anything (e.g. a passive server),
	 *  - the Ack is outdated (packet with higher Ack number was received),
	 *  - it is a bogus Ack (क्रम a packet not sent on this connection).
	 */
	acked = tfrc_tx_hist_find_entry(hc->tx_hist, dccp_hdr_ack_seq(skb));
	अगर (acked == शून्य)
		वापस;
	/* For the sake of RTT sampling, ignore/हटाओ all older entries */
	tfrc_tx_hist_purge(&acked->next);

	/* Update the moving average क्रम the RTT estimate (RFC 3448, 4.3) */
	now	  = kसमय_get_real();
	r_sample  = dccp_sample_rtt(sk, kसमय_us_delta(now, acked->stamp));
	hc->tx_rtt = tfrc_ewma(hc->tx_rtt, r_sample, 9);

	/*
	 * Update allowed sending rate X as per draft rfc3448bis-00, 4.2/3
	 */
	अगर (hc->tx_state == TFRC_SSTATE_NO_FBACK) अणु
		ccid3_hc_tx_set_state(sk, TFRC_SSTATE_FBACK);

		अगर (hc->tx_t_rto == 0) अणु
			/*
			 * Initial feedback packet: Larger Initial Winकरोws (4.2)
			 */
			hc->tx_x    = rfc3390_initial_rate(sk);
			hc->tx_t_ld = now;

			ccid3_update_send_पूर्णांकerval(hc);

			जाओ करोne_computing_x;
		पूर्ण अन्यथा अगर (hc->tx_p == 0) अणु
			/*
			 * First feedback after nofeedback समयr expiry (4.3)
			 */
			जाओ करोne_computing_x;
		पूर्ण
	पूर्ण

	/* Update sending rate (step 4 of [RFC 3448, 4.3]) */
	अगर (hc->tx_p > 0)
		hc->tx_x_calc = tfrc_calc_x(hc->tx_s, hc->tx_rtt, hc->tx_p);
	ccid3_hc_tx_update_x(sk, &now);

करोne_computing_x:
	ccid3_pr_debug("%s(%p), RTT=%uus (sample=%uus), s=%u, "
			       "p=%u, X_calc=%u, X_recv=%u, X=%u\n",
			       dccp_role(sk), sk, hc->tx_rtt, r_sample,
			       hc->tx_s, hc->tx_p, hc->tx_x_calc,
			       (अचिन्हित पूर्णांक)(hc->tx_x_recv >> 6),
			       (अचिन्हित पूर्णांक)(hc->tx_x >> 6));

	/* unschedule no feedback समयr */
	sk_stop_समयr(sk, &hc->tx_no_feedback_समयr);

	/*
	 * As we have calculated new ipi, delta, t_nom it is possible
	 * that we now can send a packet, so wake up dccp_रुको_क्रम_ccid
	 */
	sk->sk_ग_लिखो_space(sk);

	/*
	 * Update समयout पूर्णांकerval क्रम the nofeedback समयr. In order to control
	 * rate halving on networks with very low RTTs (<= 1 ms), use per-route
	 * tunable RTAX_RTO_MIN value as the lower bound.
	 */
	hc->tx_t_rto = max_t(u32, 4 * hc->tx_rtt,
				  USEC_PER_SEC/HZ * tcp_rto_min(sk));
	/*
	 * Schedule no feedback समयr to expire in
	 * max(t_RTO, 2 * s/X)  =  max(t_RTO, 2 * t_ipi)
	 */
	t_nfb = max(hc->tx_t_rto, 2 * hc->tx_t_ipi);

	ccid3_pr_debug("%s(%p), Scheduled no feedback timer to "
		       "expire in %lu jiffies (%luus)\n",
		       dccp_role(sk), sk, usecs_to_jअगरfies(t_nfb), t_nfb);

	sk_reset_समयr(sk, &hc->tx_no_feedback_समयr,
			   jअगरfies + usecs_to_jअगरfies(t_nfb));
पूर्ण

अटल पूर्णांक ccid3_hc_tx_parse_options(काष्ठा sock *sk, u8 packet_type,
				     u8 option, u8 *optval, u8 optlen)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	__be32 opt_val;

	चयन (option) अणु
	हाल TFRC_OPT_RECEIVE_RATE:
	हाल TFRC_OPT_LOSS_EVENT_RATE:
		/* Must be ignored on Data packets, cf. RFC 4342 8.3 and 8.5 */
		अगर (packet_type == DCCP_PKT_DATA)
			अवरोध;
		अगर (unlikely(optlen != 4)) अणु
			DCCP_WARN("%s(%p), invalid len %d for %u\n",
				  dccp_role(sk), sk, optlen, option);
			वापस -EINVAL;
		पूर्ण
		opt_val = ntohl(get_unaligned((__be32 *)optval));

		अगर (option == TFRC_OPT_RECEIVE_RATE) अणु
			/* Receive Rate is kept in units of 64 bytes/second */
			hc->tx_x_recv = opt_val;
			hc->tx_x_recv <<= 6;

			ccid3_pr_debug("%s(%p), RECEIVE_RATE=%u\n",
				       dccp_role(sk), sk, opt_val);
		पूर्ण अन्यथा अणु
			/* Update the fixpoपूर्णांक Loss Event Rate fraction */
			hc->tx_p = tfrc_invert_loss_event_rate(opt_val);

			ccid3_pr_debug("%s(%p), LOSS_EVENT_RATE=%u\n",
				       dccp_role(sk), sk, opt_val);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ccid3_hc_tx_init(काष्ठा ccid *ccid, काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid_priv(ccid);

	hc->tx_state = TFRC_SSTATE_NO_SENT;
	hc->tx_hist  = शून्य;
	hc->sk	     = sk;
	समयr_setup(&hc->tx_no_feedback_समयr,
		    ccid3_hc_tx_no_feedback_समयr, 0);
	वापस 0;
पूर्ण

अटल व्योम ccid3_hc_tx_निकास(काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);

	sk_stop_समयr(sk, &hc->tx_no_feedback_समयr);
	tfrc_tx_hist_purge(&hc->tx_hist);
पूर्ण

अटल व्योम ccid3_hc_tx_get_info(काष्ठा sock *sk, काष्ठा tcp_info *info)
अणु
	info->tcpi_rto = ccid3_hc_tx_sk(sk)->tx_t_rto;
	info->tcpi_rtt = ccid3_hc_tx_sk(sk)->tx_rtt;
पूर्ण

अटल पूर्णांक ccid3_hc_tx_माला_लोockopt(काष्ठा sock *sk, स्थिर पूर्णांक optname, पूर्णांक len,
				  u32 __user *optval, पूर्णांक __user *optlen)
अणु
	स्थिर काष्ठा ccid3_hc_tx_sock *hc = ccid3_hc_tx_sk(sk);
	काष्ठा tfrc_tx_info tfrc;
	स्थिर व्योम *val;

	चयन (optname) अणु
	हाल DCCP_SOCKOPT_CCID_TX_INFO:
		अगर (len < माप(tfrc))
			वापस -EINVAL;
		स_रखो(&tfrc, 0, माप(tfrc));
		tfrc.tfrctx_x	   = hc->tx_x;
		tfrc.tfrctx_x_recv = hc->tx_x_recv;
		tfrc.tfrctx_x_calc = hc->tx_x_calc;
		tfrc.tfrctx_rtt	   = hc->tx_rtt;
		tfrc.tfrctx_p	   = hc->tx_p;
		tfrc.tfrctx_rto	   = hc->tx_t_rto;
		tfrc.tfrctx_ipi	   = hc->tx_t_ipi;
		len = माप(tfrc);
		val = &tfrc;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen) || copy_to_user(optval, val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 *	Receiver Half-Connection Routines
 */

/* CCID3 feedback types */
क्रमागत ccid3_fback_type अणु
	CCID3_FBACK_NONE = 0,
	CCID3_FBACK_INITIAL,
	CCID3_FBACK_PERIODIC,
	CCID3_FBACK_PARAM_CHANGE
पूर्ण;

#अगर_घोषित CONFIG_IP_DCCP_CCID3_DEBUG
अटल स्थिर अक्षर *ccid3_rx_state_name(क्रमागत ccid3_hc_rx_states state)
अणु
	अटल स्थिर अक्षर *स्थिर ccid3_rx_state_names[] = अणु
	[TFRC_RSTATE_NO_DATA] = "NO_DATA",
	[TFRC_RSTATE_DATA]    = "DATA",
	पूर्ण;

	वापस ccid3_rx_state_names[state];
पूर्ण
#पूर्ण_अगर

अटल व्योम ccid3_hc_rx_set_state(काष्ठा sock *sk,
				  क्रमागत ccid3_hc_rx_states state)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	क्रमागत ccid3_hc_rx_states oldstate = hc->rx_state;

	ccid3_pr_debug("%s(%p) %-8.8s -> %s\n",
		       dccp_role(sk), sk, ccid3_rx_state_name(oldstate),
		       ccid3_rx_state_name(state));
	WARN_ON(state == oldstate);
	hc->rx_state = state;
पूर्ण

अटल व्योम ccid3_hc_rx_send_feedback(काष्ठा sock *sk,
				      स्थिर काष्ठा sk_buff *skb,
				      क्रमागत ccid3_fback_type fbtype)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	kसमय_प्रकार now = kसमय_get();
	s64 delta = 0;

	चयन (fbtype) अणु
	हाल CCID3_FBACK_INITIAL:
		hc->rx_x_recv = 0;
		hc->rx_pinv   = ~0U;   /* see RFC 4342, 8.5 */
		अवरोध;
	हाल CCID3_FBACK_PARAM_CHANGE:
		/*
		 * When parameters change (new loss or p > p_prev), we करो not
		 * have a reliable estimate क्रम R_m of [RFC 3448, 6.2] and so
		 * need to  reuse the previous value of X_recv. However, when
		 * X_recv was 0 (due to early loss), this would समाप्त X करोwn to
		 * s/t_mbi (i.e. one packet in 64 seconds).
		 * To aव्योम such drastic reduction, we approximate X_recv as
		 * the number of bytes since last feedback.
		 * This is a safe fallback, since X is bounded above by X_calc.
		 */
		अगर (hc->rx_x_recv > 0)
			अवरोध;
		fallthrough;
	हाल CCID3_FBACK_PERIODIC:
		delta = kसमय_us_delta(now, hc->rx_tstamp_last_feedback);
		अगर (delta <= 0)
			delta = 1;
		hc->rx_x_recv = scaled_भाग32(hc->rx_bytes_recv, delta);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ccid3_pr_debug("Interval %lldusec, X_recv=%u, 1/p=%u\n", delta,
		       hc->rx_x_recv, hc->rx_pinv);

	hc->rx_tstamp_last_feedback = now;
	hc->rx_last_counter	    = dccp_hdr(skb)->dccph_ccval;
	hc->rx_bytes_recv	    = 0;

	dp->dccps_hc_rx_insert_options = 1;
	dccp_send_ack(sk);
पूर्ण

अटल पूर्णांक ccid3_hc_rx_insert_options(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	__be32 x_recv, pinv;

	अगर (!(sk->sk_state == DCCP_OPEN || sk->sk_state == DCCP_PARTOPEN))
		वापस 0;

	अगर (dccp_packet_without_ack(skb))
		वापस 0;

	x_recv = htonl(hc->rx_x_recv);
	pinv   = htonl(hc->rx_pinv);

	अगर (dccp_insert_option(skb, TFRC_OPT_LOSS_EVENT_RATE,
			       &pinv, माप(pinv)) ||
	    dccp_insert_option(skb, TFRC_OPT_RECEIVE_RATE,
			       &x_recv, माप(x_recv)))
		वापस -1;

	वापस 0;
पूर्ण

/**
 * ccid3_first_li  -  Implements [RFC 5348, 6.3.1]
 * @sk: socket to calculate loss पूर्णांकerval क्रम
 *
 * Determine the length of the first loss पूर्णांकerval via inverse lookup.
 * Assume that X_recv can be computed by the throughput equation
 *		    s
 *	X_recv = --------
 *		 R * fval
 * Find some p such that f(p) = fval; वापस 1/p (scaled).
 */
अटल u32 ccid3_first_li(काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	u32 x_recv, p;
	s64 delta;
	u64 fval;

	अगर (hc->rx_rtt == 0) अणु
		DCCP_WARN("No RTT estimate available, using fallback RTT\n");
		hc->rx_rtt = DCCP_FALLBACK_RTT;
	पूर्ण

	delta = kसमय_us_delta(kसमय_get(), hc->rx_tstamp_last_feedback);
	अगर (delta <= 0)
		delta = 1;
	x_recv = scaled_भाग32(hc->rx_bytes_recv, delta);
	अगर (x_recv == 0) अणु		/* would also trigger भागide-by-zero */
		DCCP_WARN("X_recv==0\n");
		अगर (hc->rx_x_recv == 0) अणु
			DCCP_BUG("stored value of X_recv is zero");
			वापस ~0U;
		पूर्ण
		x_recv = hc->rx_x_recv;
	पूर्ण

	fval = scaled_भाग(hc->rx_s, hc->rx_rtt);
	fval = scaled_भाग32(fval, x_recv);
	p = tfrc_calc_x_reverse_lookup(fval);

	ccid3_pr_debug("%s(%p), receive rate=%u bytes/s, implied "
		       "loss rate=%u\n", dccp_role(sk), sk, x_recv, p);

	वापस p == 0 ? ~0U : scaled_भाग(1, p);
पूर्ण

अटल व्योम ccid3_hc_rx_packet_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	क्रमागत ccid3_fback_type करो_feedback = CCID3_FBACK_NONE;
	स्थिर u64 ndp = dccp_sk(sk)->dccps_options_received.dccpor_ndp;
	स्थिर bool is_data_packet = dccp_data_packet(skb);

	अगर (unlikely(hc->rx_state == TFRC_RSTATE_NO_DATA)) अणु
		अगर (is_data_packet) अणु
			स्थिर u32 payload = skb->len - dccp_hdr(skb)->dccph_करोff * 4;
			करो_feedback = CCID3_FBACK_INITIAL;
			ccid3_hc_rx_set_state(sk, TFRC_RSTATE_DATA);
			hc->rx_s = payload;
			/*
			 * Not necessary to update rx_bytes_recv here,
			 * since X_recv = 0 क्रम the first feedback packet (cf.
			 * RFC 3448, 6.3) -- gerrit
			 */
		पूर्ण
		जाओ update_records;
	पूर्ण

	अगर (tfrc_rx_hist_duplicate(&hc->rx_hist, skb))
		वापस; /* करोne receiving */

	अगर (is_data_packet) अणु
		स्थिर u32 payload = skb->len - dccp_hdr(skb)->dccph_करोff * 4;
		/*
		 * Update moving-average of s and the sum of received payload bytes
		 */
		hc->rx_s = tfrc_ewma(hc->rx_s, payload, 9);
		hc->rx_bytes_recv += payload;
	पूर्ण

	/*
	 * Perक्रमm loss detection and handle pending losses
	 */
	अगर (tfrc_rx_handle_loss(&hc->rx_hist, &hc->rx_li_hist,
				skb, ndp, ccid3_first_li, sk)) अणु
		करो_feedback = CCID3_FBACK_PARAM_CHANGE;
		जाओ करोne_receiving;
	पूर्ण

	अगर (tfrc_rx_hist_loss_pending(&hc->rx_hist))
		वापस; /* करोne receiving */

	/*
	 * Handle data packets: RTT sampling and monitoring p
	 */
	अगर (unlikely(!is_data_packet))
		जाओ update_records;

	अगर (!tfrc_lh_is_initialised(&hc->rx_li_hist)) अणु
		स्थिर u32 sample = tfrc_rx_hist_sample_rtt(&hc->rx_hist, skb);
		/*
		 * Empty loss history: no loss so far, hence p stays 0.
		 * Sample RTT values, since an RTT estimate is required क्रम the
		 * computation of p when the first loss occurs; RFC 3448, 6.3.1.
		 */
		अगर (sample != 0)
			hc->rx_rtt = tfrc_ewma(hc->rx_rtt, sample, 9);

	पूर्ण अन्यथा अगर (tfrc_lh_update_i_mean(&hc->rx_li_hist, skb)) अणु
		/*
		 * Step (3) of [RFC 3448, 6.1]: Recompute I_mean and, अगर I_mean
		 * has decreased (resp. p has increased), send feedback now.
		 */
		करो_feedback = CCID3_FBACK_PARAM_CHANGE;
	पूर्ण

	/*
	 * Check अगर the periodic once-per-RTT feedback is due; RFC 4342, 10.3
	 */
	अगर (SUB16(dccp_hdr(skb)->dccph_ccval, hc->rx_last_counter) > 3)
		करो_feedback = CCID3_FBACK_PERIODIC;

update_records:
	tfrc_rx_hist_add_packet(&hc->rx_hist, skb, ndp);

करोne_receiving:
	अगर (करो_feedback)
		ccid3_hc_rx_send_feedback(sk, skb, करो_feedback);
पूर्ण

अटल पूर्णांक ccid3_hc_rx_init(काष्ठा ccid *ccid, काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid_priv(ccid);

	hc->rx_state = TFRC_RSTATE_NO_DATA;
	tfrc_lh_init(&hc->rx_li_hist);
	वापस tfrc_rx_hist_alloc(&hc->rx_hist);
पूर्ण

अटल व्योम ccid3_hc_rx_निकास(काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);

	tfrc_rx_hist_purge(&hc->rx_hist);
	tfrc_lh_cleanup(&hc->rx_li_hist);
पूर्ण

अटल व्योम ccid3_hc_rx_get_info(काष्ठा sock *sk, काष्ठा tcp_info *info)
अणु
	info->tcpi_ca_state = ccid3_hc_rx_sk(sk)->rx_state;
	info->tcpi_options  |= TCPI_OPT_TIMESTAMPS;
	info->tcpi_rcv_rtt  = ccid3_hc_rx_sk(sk)->rx_rtt;
पूर्ण

अटल पूर्णांक ccid3_hc_rx_माला_लोockopt(काष्ठा sock *sk, स्थिर पूर्णांक optname, पूर्णांक len,
				  u32 __user *optval, पूर्णांक __user *optlen)
अणु
	स्थिर काष्ठा ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	काष्ठा tfrc_rx_info rx_info;
	स्थिर व्योम *val;

	चयन (optname) अणु
	हाल DCCP_SOCKOPT_CCID_RX_INFO:
		अगर (len < माप(rx_info))
			वापस -EINVAL;
		rx_info.tfrcrx_x_recv = hc->rx_x_recv;
		rx_info.tfrcrx_rtt    = hc->rx_rtt;
		rx_info.tfrcrx_p      = tfrc_invert_loss_event_rate(hc->rx_pinv);
		len = माप(rx_info);
		val = &rx_info;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen) || copy_to_user(optval, val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

काष्ठा ccid_operations ccid3_ops = अणु
	.ccid_id		   = DCCPC_CCID3,
	.ccid_name		   = "TCP-Friendly Rate Control",
	.ccid_hc_tx_obj_size	   = माप(काष्ठा ccid3_hc_tx_sock),
	.ccid_hc_tx_init	   = ccid3_hc_tx_init,
	.ccid_hc_tx_निकास	   = ccid3_hc_tx_निकास,
	.ccid_hc_tx_send_packet	   = ccid3_hc_tx_send_packet,
	.ccid_hc_tx_packet_sent	   = ccid3_hc_tx_packet_sent,
	.ccid_hc_tx_packet_recv	   = ccid3_hc_tx_packet_recv,
	.ccid_hc_tx_parse_options  = ccid3_hc_tx_parse_options,
	.ccid_hc_rx_obj_size	   = माप(काष्ठा ccid3_hc_rx_sock),
	.ccid_hc_rx_init	   = ccid3_hc_rx_init,
	.ccid_hc_rx_निकास	   = ccid3_hc_rx_निकास,
	.ccid_hc_rx_insert_options = ccid3_hc_rx_insert_options,
	.ccid_hc_rx_packet_recv	   = ccid3_hc_rx_packet_recv,
	.ccid_hc_rx_get_info	   = ccid3_hc_rx_get_info,
	.ccid_hc_tx_get_info	   = ccid3_hc_tx_get_info,
	.ccid_hc_rx_माला_लोockopt	   = ccid3_hc_rx_माला_लोockopt,
	.ccid_hc_tx_माला_लोockopt	   = ccid3_hc_tx_माला_लोockopt,
पूर्ण;

#अगर_घोषित CONFIG_IP_DCCP_CCID3_DEBUG
module_param(ccid3_debug, bool, 0644);
MODULE_PARM_DESC(ccid3_debug, "Enable CCID-3 debug messages");
#पूर्ण_अगर
