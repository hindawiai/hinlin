<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/input.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

#समावेश <net/sock.h>

#समावेश "ackvec.h"
#समावेश "ccid.h"
#समावेश "dccp.h"

/* rate-limit क्रम syncs in reply to sequence-invalid packets; RFC 4340, 7.5.4 */
पूर्णांक sysctl_dccp_sync_ratelimit	__पढ़ो_mostly = HZ / 8;

अटल व्योम dccp_enqueue_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__skb_pull(skb, dccp_hdr(skb)->dccph_करोff * 4);
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	skb_set_owner_r(skb, sk);
	sk->sk_data_पढ़ोy(sk);
पूर्ण

अटल व्योम dccp_fin(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/*
	 * On receiving Close/CloseReq, both RD/WR shutकरोwn are perक्रमmed.
	 * RFC 4340, 8.3 says that we MAY send further Data/DataAcks after
	 * receiving the closing segment, but there is no guarantee that such
	 * data will be processed at all.
	 */
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	sock_set_flag(sk, SOCK_DONE);
	dccp_enqueue_skb(sk, skb);
पूर्ण

अटल पूर्णांक dccp_rcv_बंद(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queued = 0;

	चयन (sk->sk_state) अणु
	/*
	 * We ignore Close when received in one of the following states:
	 *  - CLOSED		(may be a late or duplicate packet)
	 *  - PASSIVE_CLOSEREQ	(the peer has sent a CloseReq earlier)
	 *  - RESPOND		(alपढ़ोy handled by dccp_check_req)
	 */
	हाल DCCP_CLOSING:
		/*
		 * Simultaneous-बंद: receiving a Close after sending one. This
		 * can happen अगर both client and server perक्रमm active-बंद and
		 * will result in an endless ping-pong of crossing and retrans-
		 * mitted Close packets, which only terminates when one of the
		 * nodes बार out (min. 64 seconds). Quicker convergence can be
		 * achieved when one of the nodes acts as tie-अवरोधer.
		 * This is ok as both ends are करोne with data transfer and each
		 * end is just रुकोing क्रम the other to acknowledge termination.
		 */
		अगर (dccp_sk(sk)->dccps_role != DCCP_ROLE_CLIENT)
			अवरोध;
		fallthrough;
	हाल DCCP_REQUESTING:
	हाल DCCP_ACTIVE_CLOSEREQ:
		dccp_send_reset(sk, DCCP_RESET_CODE_CLOSED);
		dccp_करोne(sk);
		अवरोध;
	हाल DCCP_OPEN:
	हाल DCCP_PARTOPEN:
		/* Give रुकोing application a chance to पढ़ो pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CLOSE);
		fallthrough;
	हाल DCCP_PASSIVE_CLOSE:
		/*
		 * Retransmitted Close: we have alपढ़ोy enqueued the first one.
		 */
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	पूर्ण
	वापस queued;
पूर्ण

अटल पूर्णांक dccp_rcv_बंदreq(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queued = 0;

	/*
	 *   Step 7: Check क्रम unexpected packet types
	 *      If (S.is_server and P.type == CloseReq)
	 *	  Send Sync packet acknowledging P.seqno
	 *	  Drop packet and वापस
	 */
	अगर (dccp_sk(sk)->dccps_role != DCCP_ROLE_CLIENT) अणु
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq, DCCP_PKT_SYNC);
		वापस queued;
	पूर्ण

	/* Step 13: process relevant Client states < CLOSEREQ */
	चयन (sk->sk_state) अणु
	हाल DCCP_REQUESTING:
		dccp_send_बंद(sk, 0);
		dccp_set_state(sk, DCCP_CLOSING);
		अवरोध;
	हाल DCCP_OPEN:
	हाल DCCP_PARTOPEN:
		/* Give रुकोing application a chance to पढ़ो pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CLOSEREQ);
		fallthrough;
	हाल DCCP_PASSIVE_CLOSEREQ:
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	पूर्ण
	वापस queued;
पूर्ण

अटल u16 dccp_reset_code_convert(स्थिर u8 code)
अणु
	अटल स्थिर u16 error_code[] = अणु
	[DCCP_RESET_CODE_CLOSED]	     = 0,	/* normal termination */
	[DCCP_RESET_CODE_UNSPECIFIED]	     = 0,	/* nothing known */
	[DCCP_RESET_CODE_ABORTED]	     = ECONNRESET,

	[DCCP_RESET_CODE_NO_CONNECTION]	     = ECONNREFUSED,
	[DCCP_RESET_CODE_CONNECTION_REFUSED] = ECONNREFUSED,
	[DCCP_RESET_CODE_TOO_BUSY]	     = EUSERS,
	[DCCP_RESET_CODE_AGGRESSION_PENALTY] = EDQUOT,

	[DCCP_RESET_CODE_PACKET_ERROR]	     = ENOMSG,
	[DCCP_RESET_CODE_BAD_INIT_COOKIE]    = EBADR,
	[DCCP_RESET_CODE_BAD_SERVICE_CODE]   = EBADRQC,
	[DCCP_RESET_CODE_OPTION_ERROR]	     = EILSEQ,
	[DCCP_RESET_CODE_MANDATORY_ERROR]    = EOPNOTSUPP,
	पूर्ण;

	वापस code >= DCCP_MAX_RESET_CODES ? 0 : error_code[code];
पूर्ण

अटल व्योम dccp_rcv_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 err = dccp_reset_code_convert(dccp_hdr_reset(skb)->dccph_reset_code);

	sk->sk_err = err;

	/* Queue the equivalent of TCP fin so that dccp_recvmsg निकासs the loop */
	dccp_fin(sk, skb);

	अगर (err && !sock_flag(sk, SOCK_DEAD))
		sk_wake_async(sk, SOCK_WAKE_IO, POLL_ERR);
	dccp_समय_रुको(sk, DCCP_TIME_WAIT, 0);
पूर्ण

अटल व्योम dccp_handle_ackvec_processing(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_ackvec *av = dccp_sk(sk)->dccps_hc_rx_ackvec;

	अगर (av == शून्य)
		वापस;
	अगर (DCCP_SKB_CB(skb)->dccpd_ack_seq != DCCP_PKT_WITHOUT_ACK_SEQ)
		dccp_ackvec_clear_state(av, DCCP_SKB_CB(skb)->dccpd_ack_seq);
	dccp_ackvec_input(av, skb);
पूर्ण

अटल व्योम dccp_deliver_input_to_ccids(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_sock *dp = dccp_sk(sk);

	/* Don't deliver to RX CCID when node has shut करोwn पढ़ो end. */
	अगर (!(sk->sk_shutकरोwn & RCV_SHUTDOWN))
		ccid_hc_rx_packet_recv(dp->dccps_hc_rx_ccid, sk, skb);
	/*
	 * Until the TX queue has been drained, we can not honour SHUT_WR, since
	 * we need received feedback as input to adjust congestion control.
	 */
	अगर (sk->sk_ग_लिखो_queue.qlen > 0 || !(sk->sk_shutकरोwn & SEND_SHUTDOWN))
		ccid_hc_tx_packet_recv(dp->dccps_hc_tx_ccid, sk, skb);
पूर्ण

अटल पूर्णांक dccp_check_seqno(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr *dh = dccp_hdr(skb);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	u64 lswl, lawl, seqno = DCCP_SKB_CB(skb)->dccpd_seq,
			ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;

	/*
	 *   Step 5: Prepare sequence numbers क्रम Sync
	 *     If P.type == Sync or P.type == SyncAck,
	 *	  If S.AWL <= P.ackno <= S.AWH and P.seqno >= S.SWL,
	 *	     / * P is valid, so update sequence number variables
	 *		 accordingly.  After this update, P will pass the tests
	 *		 in Step 6.  A SyncAck is generated अगर necessary in
	 *		 Step 15 * /
	 *	     Update S.GSR, S.SWL, S.SWH
	 *	  Otherwise,
	 *	     Drop packet and वापस
	 */
	अगर (dh->dccph_type == DCCP_PKT_SYNC ||
	    dh->dccph_type == DCCP_PKT_SYNCACK) अणु
		अगर (between48(ackno, dp->dccps_awl, dp->dccps_awh) &&
		    dccp_delta_seqno(dp->dccps_swl, seqno) >= 0)
			dccp_update_gsr(sk, seqno);
		अन्यथा
			वापस -1;
	पूर्ण

	/*
	 *   Step 6: Check sequence numbers
	 *      Let LSWL = S.SWL and LAWL = S.AWL
	 *      If P.type == CloseReq or P.type == Close or P.type == Reset,
	 *	  LSWL := S.GSR + 1, LAWL := S.GAR
	 *      If LSWL <= P.seqno <= S.SWH
	 *	     and (P.ackno करोes not exist or LAWL <= P.ackno <= S.AWH),
	 *	  Update S.GSR, S.SWL, S.SWH
	 *	  If P.type != Sync,
	 *	     Update S.GAR
	 */
	lswl = dp->dccps_swl;
	lawl = dp->dccps_awl;

	अगर (dh->dccph_type == DCCP_PKT_CLOSEREQ ||
	    dh->dccph_type == DCCP_PKT_CLOSE ||
	    dh->dccph_type == DCCP_PKT_RESET) अणु
		lswl = ADD48(dp->dccps_gsr, 1);
		lawl = dp->dccps_gar;
	पूर्ण

	अगर (between48(seqno, lswl, dp->dccps_swh) &&
	    (ackno == DCCP_PKT_WITHOUT_ACK_SEQ ||
	     between48(ackno, lawl, dp->dccps_awh))) अणु
		dccp_update_gsr(sk, seqno);

		अगर (dh->dccph_type != DCCP_PKT_SYNC &&
		    ackno != DCCP_PKT_WITHOUT_ACK_SEQ &&
		    after48(ackno, dp->dccps_gar))
			dp->dccps_gar = ackno;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ now = jअगरfies;
		/*
		 *   Step 6: Check sequence numbers
		 *      Otherwise,
		 *         If P.type == Reset,
		 *            Send Sync packet acknowledging S.GSR
		 *         Otherwise,
		 *            Send Sync packet acknowledging P.seqno
		 *      Drop packet and वापस
		 *
		 *   These Syncs are rate-limited as per RFC 4340, 7.5.4:
		 *   at most 1 / (dccp_sync_rate_limit * HZ) Syncs per second.
		 */
		अगर (समय_beक्रमe(now, (dp->dccps_rate_last +
				      sysctl_dccp_sync_ratelimit)))
			वापस -1;

		DCCP_WARN("Step 6 failed for %s packet, "
			  "(LSWL(%llu) <= P.seqno(%llu) <= S.SWH(%llu)) and "
			  "(P.ackno %s or LAWL(%llu) <= P.ackno(%llu) <= S.AWH(%llu), "
			  "sending SYNC...\n",  dccp_packet_name(dh->dccph_type),
			  (अचिन्हित दीर्घ दीर्घ) lswl, (अचिन्हित दीर्घ दीर्घ) seqno,
			  (अचिन्हित दीर्घ दीर्घ) dp->dccps_swh,
			  (ackno == DCCP_PKT_WITHOUT_ACK_SEQ) ? "doesn't exist"
							      : "exists",
			  (अचिन्हित दीर्घ दीर्घ) lawl, (अचिन्हित दीर्घ दीर्घ) ackno,
			  (अचिन्हित दीर्घ दीर्घ) dp->dccps_awh);

		dp->dccps_rate_last = now;

		अगर (dh->dccph_type == DCCP_PKT_RESET)
			seqno = dp->dccps_gsr;
		dccp_send_sync(sk, seqno, DCCP_PKT_SYNC);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __dccp_rcv_established(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  स्थिर काष्ठा dccp_hdr *dh, स्थिर अचिन्हित पूर्णांक len)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	चयन (dccp_hdr(skb)->dccph_type) अणु
	हाल DCCP_PKT_DATAACK:
	हाल DCCP_PKT_DATA:
		/*
		 * FIXME: schedule DATA_DROPPED (RFC 4340, 11.7.2) अगर and when
		 * - sk_shutकरोwn == RCV_SHUTDOWN, use Code 1, "Not Listening"
		 * - sk_receive_queue is full, use Code 2, "Receive Buffer"
		 */
		dccp_enqueue_skb(sk, skb);
		वापस 0;
	हाल DCCP_PKT_ACK:
		जाओ discard;
	हाल DCCP_PKT_RESET:
		/*
		 *  Step 9: Process Reset
		 *	If P.type == Reset,
		 *		Tear करोwn connection
		 *		S.state := TIMEWAIT
		 *		Set TIMEWAIT समयr
		 *		Drop packet and वापस
		 */
		dccp_rcv_reset(sk, skb);
		वापस 0;
	हाल DCCP_PKT_CLOSEREQ:
		अगर (dccp_rcv_बंदreq(sk, skb))
			वापस 0;
		जाओ discard;
	हाल DCCP_PKT_CLOSE:
		अगर (dccp_rcv_बंद(sk, skb))
			वापस 0;
		जाओ discard;
	हाल DCCP_PKT_REQUEST:
		/* Step 7
		 *   or (S.is_server and P.type == Response)
		 *   or (S.is_client and P.type == Request)
		 *   or (S.state >= OPEN and P.type == Request
		 *	and P.seqno >= S.OSR)
		 *    or (S.state >= OPEN and P.type == Response
		 *	and P.seqno >= S.OSR)
		 *    or (S.state == RESPOND and P.type == Data),
		 *  Send Sync packet acknowledging P.seqno
		 *  Drop packet and वापस
		 */
		अगर (dp->dccps_role != DCCP_ROLE_LISTEN)
			जाओ send_sync;
		जाओ check_seq;
	हाल DCCP_PKT_RESPONSE:
		अगर (dp->dccps_role != DCCP_ROLE_CLIENT)
			जाओ send_sync;
check_seq:
		अगर (dccp_delta_seqno(dp->dccps_osr,
				     DCCP_SKB_CB(skb)->dccpd_seq) >= 0) अणु
send_sync:
			dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
				       DCCP_PKT_SYNC);
		पूर्ण
		अवरोध;
	हाल DCCP_PKT_SYNC:
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
			       DCCP_PKT_SYNCACK);
		/*
		 * From RFC 4340, sec. 5.7
		 *
		 * As with DCCP-Ack packets, DCCP-Sync and DCCP-SyncAck packets
		 * MAY have non-zero-length application data areas, whose
		 * contents receivers MUST ignore.
		 */
		जाओ discard;
	पूर्ण

	DCCP_INC_STATS(DCCP_MIB_INERRS);
discard:
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक dccp_rcv_established(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा dccp_hdr *dh, स्थिर अचिन्हित पूर्णांक len)
अणु
	अगर (dccp_check_seqno(sk, skb))
		जाओ discard;

	अगर (dccp_parse_options(sk, शून्य, skb))
		वापस 1;

	dccp_handle_ackvec_processing(sk, skb);
	dccp_deliver_input_to_ccids(sk, skb);

	वापस __dccp_rcv_established(sk, skb, dh, len);
discard:
	__kमुक्त_skb(skb);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_rcv_established);

अटल पूर्णांक dccp_rcv_request_sent_state_process(काष्ठा sock *sk,
					       काष्ठा sk_buff *skb,
					       स्थिर काष्ठा dccp_hdr *dh,
					       स्थिर अचिन्हित पूर्णांक len)
अणु
	/*
	 *  Step 4: Prepare sequence numbers in REQUEST
	 *     If S.state == REQUEST,
	 *	  If (P.type == Response or P.type == Reset)
	 *		and S.AWL <= P.ackno <= S.AWH,
	 *	     / * Set sequence number variables corresponding to the
	 *		other endpoपूर्णांक, so P will pass the tests in Step 6 * /
	 *	     Set S.GSR, S.ISR, S.SWL, S.SWH
	 *	     / * Response processing जारीs in Step 10; Reset
	 *		processing जारीs in Step 9 * /
	*/
	अगर (dh->dccph_type == DCCP_PKT_RESPONSE) अणु
		स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
		काष्ठा dccp_sock *dp = dccp_sk(sk);
		दीर्घ tstamp = dccp_बारtamp();

		अगर (!between48(DCCP_SKB_CB(skb)->dccpd_ack_seq,
			       dp->dccps_awl, dp->dccps_awh)) अणु
			dccp_pr_debug("invalid ackno: S.AWL=%llu, "
				      "P.ackno=%llu, S.AWH=%llu\n",
				      (अचिन्हित दीर्घ दीर्घ)dp->dccps_awl,
			   (अचिन्हित दीर्घ दीर्घ)DCCP_SKB_CB(skb)->dccpd_ack_seq,
				      (अचिन्हित दीर्घ दीर्घ)dp->dccps_awh);
			जाओ out_invalid_packet;
		पूर्ण

		/*
		 * If option processing (Step 8) failed, वापस 1 here so that
		 * dccp_v4_करो_rcv() sends a Reset. The Reset code depends on
		 * the option type and is set in dccp_parse_options().
		 */
		अगर (dccp_parse_options(sk, शून्य, skb))
			वापस 1;

		/* Obtain usec RTT sample from SYN exchange (used by TFRC). */
		अगर (likely(dp->dccps_options_received.dccpor_बारtamp_echo))
			dp->dccps_syn_rtt = dccp_sample_rtt(sk, 10 * (tstamp -
			    dp->dccps_options_received.dccpor_बारtamp_echo));

		/* Stop the REQUEST समयr */
		inet_csk_clear_xmit_समयr(sk, ICSK_TIME_RETRANS);
		WARN_ON(sk->sk_send_head == शून्य);
		kमुक्त_skb(sk->sk_send_head);
		sk->sk_send_head = शून्य;

		/*
		 * Set ISR, GSR from packet. ISS was set in dccp_vअणु4,6पूर्ण_connect
		 * and GSS in dccp_transmit_skb(). Setting AWL/AWH and SWL/SWH
		 * is करोne as part of activating the feature values below, since
		 * these settings depend on the local/remote Sequence Winकरोw
		 * features, which were undefined or not confirmed until now.
		 */
		dp->dccps_gsr = dp->dccps_isr = DCCP_SKB_CB(skb)->dccpd_seq;

		dccp_sync_mss(sk, icsk->icsk_pmtu_cookie);

		/*
		 *    Step 10: Process REQUEST state (second part)
		 *       If S.state == REQUEST,
		 *	  / * If we get here, P is a valid Response from the
		 *	      server (see Step 4), and we should move to
		 *	      PARTOPEN state. PARTOPEN means send an Ack,
		 *	      करोn't send Data packets, retransmit Acks
		 *	      periodically, and always include any Init Cookie
		 *	      from the Response * /
		 *	  S.state := PARTOPEN
		 *	  Set PARTOPEN समयr
		 *	  Continue with S.state == PARTOPEN
		 *	  / * Step 12 will send the Ack completing the
		 *	      three-way handshake * /
		 */
		dccp_set_state(sk, DCCP_PARTOPEN);

		/*
		 * If feature negotiation was successful, activate features now;
		 * an activation failure means that this host could not activate
		 * one ore more features (e.g. insufficient memory), which would
		 * leave at least one feature in an undefined state.
		 */
		अगर (dccp_feat_activate_values(sk, &dp->dccps_featneg))
			जाओ unable_to_proceed;

		/* Make sure socket is routed, क्रम correct metrics. */
		icsk->icsk_af_ops->rebuild_header(sk);

		अगर (!sock_flag(sk, SOCK_DEAD)) अणु
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);
		पूर्ण

		अगर (sk->sk_ग_लिखो_pending || inet_csk_in_pingpong_mode(sk) ||
		    icsk->icsk_accept_queue.rskq_defer_accept) अणु
			/* Save one ACK. Data will be पढ़ोy after
			 * several ticks, अगर ग_लिखो_pending is set.
			 *
			 * It may be deleted, but with this feature tcpdumps
			 * look so _wonderfully_ clever, that I was not able
			 * to stand against the temptation 8)     --ANK
			 */
			/*
			 * OK, in DCCP we can as well करो a similar trick, its
			 * even in the draft, but there is no need क्रम us to
			 * schedule an ack here, as dccp_sendmsg करोes this क्रम
			 * us, also stated in the draft. -acme
			 */
			__kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
		dccp_send_ack(sk);
		वापस -1;
	पूर्ण

out_invalid_packet:
	/* dccp_v4_करो_rcv will send a reset */
	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_PACKET_ERROR;
	वापस 1;

unable_to_proceed:
	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_ABORTED;
	/*
	 * We mark this socket as no दीर्घer usable, so that the loop in
	 * dccp_sendmsg() terminates and the application माला_लो notअगरied.
	 */
	dccp_set_state(sk, DCCP_CLOSED);
	sk->sk_err = ECOMM;
	वापस 1;
पूर्ण

अटल पूर्णांक dccp_rcv_respond_partखोलो_state_process(काष्ठा sock *sk,
						   काष्ठा sk_buff *skb,
						   स्थिर काष्ठा dccp_hdr *dh,
						   स्थिर अचिन्हित पूर्णांक len)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	u32 sample = dp->dccps_options_received.dccpor_बारtamp_echo;
	पूर्णांक queued = 0;

	चयन (dh->dccph_type) अणु
	हाल DCCP_PKT_RESET:
		inet_csk_clear_xmit_समयr(sk, ICSK_TIME_DACK);
		अवरोध;
	हाल DCCP_PKT_DATA:
		अगर (sk->sk_state == DCCP_RESPOND)
			अवरोध;
		fallthrough;
	हाल DCCP_PKT_DATAACK:
	हाल DCCP_PKT_ACK:
		/*
		 * FIXME: we should be resetting the PARTOPEN (DELACK) समयr
		 * here but only अगर we haven't used the DELACK समयr क्रम
		 * something अन्यथा, like sending a delayed ack क्रम a TIMESTAMP
		 * echo, etc, क्रम now were not clearing it, sending an extra
		 * ACK when there is nothing अन्यथा to करो in DELACK is not a big
		 * deal after all.
		 */

		/* Stop the PARTOPEN समयr */
		अगर (sk->sk_state == DCCP_PARTOPEN)
			inet_csk_clear_xmit_समयr(sk, ICSK_TIME_DACK);

		/* Obtain usec RTT sample from SYN exchange (used by TFRC). */
		अगर (likely(sample)) अणु
			दीर्घ delta = dccp_बारtamp() - sample;

			dp->dccps_syn_rtt = dccp_sample_rtt(sk, 10 * delta);
		पूर्ण

		dp->dccps_osr = DCCP_SKB_CB(skb)->dccpd_seq;
		dccp_set_state(sk, DCCP_OPEN);

		अगर (dh->dccph_type == DCCP_PKT_DATAACK ||
		    dh->dccph_type == DCCP_PKT_DATA) अणु
			__dccp_rcv_established(sk, skb, dh, len);
			queued = 1; /* packet was queued
				       (by __dccp_rcv_established) */
		पूर्ण
		अवरोध;
	पूर्ण

	वापस queued;
पूर्ण

पूर्णांक dccp_rcv_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   काष्ठा dccp_hdr *dh, अचिन्हित पूर्णांक len)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
	स्थिर पूर्णांक old_state = sk->sk_state;
	bool acceptable;
	पूर्णांक queued = 0;

	/*
	 *  Step 3: Process LISTEN state
	 *
	 *     If S.state == LISTEN,
	 *	 If P.type == Request or P contains a valid Init Cookie option,
	 *	      (* Must scan the packet's options to check क्रम Init
	 *		 Cookies.  Only Init Cookies are processed here,
	 *		 however; other options are processed in Step 8.  This
	 *		 scan need only be perक्रमmed अगर the endpoपूर्णांक uses Init
	 *		 Cookies *)
	 *	      (* Generate a new socket and चयन to that socket *)
	 *	      Set S := new socket क्रम this port pair
	 *	      S.state = RESPOND
	 *	      Choose S.ISS (initial seqno) or set from Init Cookies
	 *	      Initialize S.GAR := S.ISS
	 *	      Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init
	 *	      Cookies Continue with S.state == RESPOND
	 *	      (* A Response packet will be generated in Step 11 *)
	 *	 Otherwise,
	 *	      Generate Reset(No Connection) unless P.type == Reset
	 *	      Drop packet and वापस
	 */
	अगर (sk->sk_state == DCCP_LISTEN) अणु
		अगर (dh->dccph_type == DCCP_PKT_REQUEST) अणु
			/* It is possible that we process SYN packets from backlog,
			 * so we need to make sure to disable BH and RCU right there.
			 */
			rcu_पढ़ो_lock();
			local_bh_disable();
			acceptable = inet_csk(sk)->icsk_af_ops->conn_request(sk, skb) >= 0;
			local_bh_enable();
			rcu_पढ़ो_unlock();
			अगर (!acceptable)
				वापस 1;
			consume_skb(skb);
			वापस 0;
		पूर्ण
		अगर (dh->dccph_type == DCCP_PKT_RESET)
			जाओ discard;

		/* Caller (dccp_v4_करो_rcv) will send Reset */
		dcb->dccpd_reset_code = DCCP_RESET_CODE_NO_CONNECTION;
		वापस 1;
	पूर्ण अन्यथा अगर (sk->sk_state == DCCP_CLOSED) अणु
		dcb->dccpd_reset_code = DCCP_RESET_CODE_NO_CONNECTION;
		वापस 1;
	पूर्ण

	/* Step 6: Check sequence numbers (omitted in LISTEN/REQUEST state) */
	अगर (sk->sk_state != DCCP_REQUESTING && dccp_check_seqno(sk, skb))
		जाओ discard;

	/*
	 *   Step 7: Check क्रम unexpected packet types
	 *      If (S.is_server and P.type == Response)
	 *	    or (S.is_client and P.type == Request)
	 *	    or (S.state == RESPOND and P.type == Data),
	 *	  Send Sync packet acknowledging P.seqno
	 *	  Drop packet and वापस
	 */
	अगर ((dp->dccps_role != DCCP_ROLE_CLIENT &&
	     dh->dccph_type == DCCP_PKT_RESPONSE) ||
	    (dp->dccps_role == DCCP_ROLE_CLIENT &&
	     dh->dccph_type == DCCP_PKT_REQUEST) ||
	    (sk->sk_state == DCCP_RESPOND && dh->dccph_type == DCCP_PKT_DATA)) अणु
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNC);
		जाओ discard;
	पूर्ण

	/*  Step 8: Process options */
	अगर (dccp_parse_options(sk, शून्य, skb))
		वापस 1;

	/*
	 *  Step 9: Process Reset
	 *	If P.type == Reset,
	 *		Tear करोwn connection
	 *		S.state := TIMEWAIT
	 *		Set TIMEWAIT समयr
	 *		Drop packet and वापस
	 */
	अगर (dh->dccph_type == DCCP_PKT_RESET) अणु
		dccp_rcv_reset(sk, skb);
		वापस 0;
	पूर्ण अन्यथा अगर (dh->dccph_type == DCCP_PKT_CLOSEREQ) अणु	/* Step 13 */
		अगर (dccp_rcv_बंदreq(sk, skb))
			वापस 0;
		जाओ discard;
	पूर्ण अन्यथा अगर (dh->dccph_type == DCCP_PKT_CLOSE) अणु		/* Step 14 */
		अगर (dccp_rcv_बंद(sk, skb))
			वापस 0;
		जाओ discard;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल DCCP_REQUESTING:
		queued = dccp_rcv_request_sent_state_process(sk, skb, dh, len);
		अगर (queued >= 0)
			वापस queued;

		__kमुक्त_skb(skb);
		वापस 0;

	हाल DCCP_PARTOPEN:
		/* Step 8: अगर using Ack Vectors, mark packet acknowledgeable */
		dccp_handle_ackvec_processing(sk, skb);
		dccp_deliver_input_to_ccids(sk, skb);
		fallthrough;
	हाल DCCP_RESPOND:
		queued = dccp_rcv_respond_partखोलो_state_process(sk, skb,
								 dh, len);
		अवरोध;
	पूर्ण

	अगर (dh->dccph_type == DCCP_PKT_ACK ||
	    dh->dccph_type == DCCP_PKT_DATAACK) अणु
		चयन (old_state) अणु
		हाल DCCP_PARTOPEN:
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(dh->dccph_type == DCCP_PKT_SYNC)) अणु
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNCACK);
		जाओ discard;
	पूर्ण

	अगर (!queued) अणु
discard:
		__kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_rcv_state_process);

/**
 *  dccp_sample_rtt  -  Validate and finalise computation of RTT sample
 *  @sk:	socket काष्ठाure
 *  @delta:	number of microseconds between packet and acknowledgment
 *
 *  The routine is kept generic to work in dअगरferent contexts. It should be
 *  called immediately when the ACK used क्रम the RTT sample arrives.
 */
u32 dccp_sample_rtt(काष्ठा sock *sk, दीर्घ delta)
अणु
	/* dccpor_elapsed_समय is either zeroed out or set and > 0 */
	delta -= dccp_sk(sk)->dccps_options_received.dccpor_elapsed_समय * 10;

	अगर (unlikely(delta <= 0)) अणु
		DCCP_WARN("unusable RTT sample %ld, using min\n", delta);
		वापस DCCP_SANE_RTT_MIN;
	पूर्ण
	अगर (unlikely(delta > DCCP_SANE_RTT_MAX)) अणु
		DCCP_WARN("RTT sample %ld too large, using max\n", delta);
		वापस DCCP_SANE_RTT_MAX;
	पूर्ण

	वापस delta;
पूर्ण
