<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/output.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/inet_sock.h>
#समावेश <net/sock.h>

#समावेश "ackvec.h"
#समावेश "ccid.h"
#समावेश "dccp.h"

अटल अंतरभूत व्योम dccp_event_ack_sent(काष्ठा sock *sk)
अणु
	inet_csk_clear_xmit_समयr(sk, ICSK_TIME_DACK);
पूर्ण

/* enqueue @skb on sk_send_head क्रम retransmission, वापस clone to send now */
अटल काष्ठा sk_buff *dccp_skb_entail(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_set_owner_w(skb, sk);
	WARN_ON(sk->sk_send_head);
	sk->sk_send_head = skb;
	वापस skb_clone(sk->sk_send_head, gfp_any());
पूर्ण

/*
 * All SKB's seen here are completely headerless. It is our
 * job to build the DCCP header, and pass the packet करोwn to
 * IP so it can करो the same plus pass the packet off to the
 * device.
 */
अटल पूर्णांक dccp_transmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (likely(skb != शून्य)) अणु
		काष्ठा inet_sock *inet = inet_sk(sk);
		स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
		काष्ठा dccp_sock *dp = dccp_sk(sk);
		काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
		काष्ठा dccp_hdr *dh;
		/* XXX For now we're using only 48 bits sequence numbers */
		स्थिर u32 dccp_header_size = माप(*dh) +
					     माप(काष्ठा dccp_hdr_ext) +
					  dccp_packet_hdr_len(dcb->dccpd_type);
		पूर्णांक err, set_ack = 1;
		u64 ackno = dp->dccps_gsr;
		/*
		 * Increment GSS here alपढ़ोy in हाल the option code needs it.
		 * Update GSS क्रम real only अगर option processing below succeeds.
		 */
		dcb->dccpd_seq = ADD48(dp->dccps_gss, 1);

		चयन (dcb->dccpd_type) अणु
		हाल DCCP_PKT_DATA:
			set_ack = 0;
			fallthrough;
		हाल DCCP_PKT_DATAACK:
		हाल DCCP_PKT_RESET:
			अवरोध;

		हाल DCCP_PKT_REQUEST:
			set_ack = 0;
			/* Use ISS on the first (non-retransmitted) Request. */
			अगर (icsk->icsk_retransmits == 0)
				dcb->dccpd_seq = dp->dccps_iss;
			fallthrough;

		हाल DCCP_PKT_SYNC:
		हाल DCCP_PKT_SYNCACK:
			ackno = dcb->dccpd_ack_seq;
			fallthrough;
		शेष:
			/*
			 * Set owner/deकाष्ठाor: some skbs are allocated via
			 * alloc_skb (e.g. when retransmission may happen).
			 * Only Data, DataAck, and Reset packets should come
			 * through here with skb->sk set.
			 */
			WARN_ON(skb->sk);
			skb_set_owner_w(skb, sk);
			अवरोध;
		पूर्ण

		अगर (dccp_insert_options(sk, skb)) अणु
			kमुक्त_skb(skb);
			वापस -EPROTO;
		पूर्ण


		/* Build DCCP header and checksum it. */
		dh = dccp_zeroed_hdr(skb, dccp_header_size);
		dh->dccph_type	= dcb->dccpd_type;
		dh->dccph_sport	= inet->inet_sport;
		dh->dccph_dport	= inet->inet_dport;
		dh->dccph_करोff	= (dccp_header_size + dcb->dccpd_opt_len) / 4;
		dh->dccph_ccval	= dcb->dccpd_ccval;
		dh->dccph_cscov = dp->dccps_pcslen;
		/* XXX For now we're using only 48 bits sequence numbers */
		dh->dccph_x	= 1;

		dccp_update_gss(sk, dcb->dccpd_seq);
		dccp_hdr_set_seq(dh, dp->dccps_gss);
		अगर (set_ack)
			dccp_hdr_set_ack(dccp_hdr_ack_bits(skb), ackno);

		चयन (dcb->dccpd_type) अणु
		हाल DCCP_PKT_REQUEST:
			dccp_hdr_request(skb)->dccph_req_service =
							dp->dccps_service;
			/*
			 * Limit Ack winकरोw to ISS <= P.ackno <= GSS, so that
			 * only Responses to Requests we sent are considered.
			 */
			dp->dccps_awl = dp->dccps_iss;
			अवरोध;
		हाल DCCP_PKT_RESET:
			dccp_hdr_reset(skb)->dccph_reset_code =
							dcb->dccpd_reset_code;
			अवरोध;
		पूर्ण

		icsk->icsk_af_ops->send_check(sk, skb);

		अगर (set_ack)
			dccp_event_ack_sent(sk);

		DCCP_INC_STATS(DCCP_MIB_OUTSEGS);

		err = icsk->icsk_af_ops->queue_xmit(sk, skb, &inet->cork.fl);
		वापस net_xmit_eval(err);
	पूर्ण
	वापस -ENOBUFS;
पूर्ण

/**
 * dccp_determine_ccmps  -  Find out about CCID-specअगरic packet-size limits
 * @dp: socket to find packet size limits of
 *
 * We only consider the HC-sender CCID क्रम setting the CCMPS (RFC 4340, 14.),
 * since the RX CCID is restricted to feedback packets (Acks), which are small
 * in comparison with the data traffic. A value of 0 means "no current CCMPS".
 */
अटल u32 dccp_determine_ccmps(स्थिर काष्ठा dccp_sock *dp)
अणु
	स्थिर काष्ठा ccid *tx_ccid = dp->dccps_hc_tx_ccid;

	अगर (tx_ccid == शून्य || tx_ccid->ccid_ops == शून्य)
		वापस 0;
	वापस tx_ccid->ccid_ops->ccid_ccmps;
पूर्ण

अचिन्हित पूर्णांक dccp_sync_mss(काष्ठा sock *sk, u32 pmtu)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	u32 ccmps = dccp_determine_ccmps(dp);
	u32 cur_mps = ccmps ? min(pmtu, ccmps) : pmtu;

	/* Account क्रम header lengths and IPv4/v6 option overhead */
	cur_mps -= (icsk->icsk_af_ops->net_header_len + icsk->icsk_ext_hdr_len +
		    माप(काष्ठा dccp_hdr) + माप(काष्ठा dccp_hdr_ext));

	/*
	 * Leave enough headroom क्रम common DCCP header options.
	 * This only considers options which may appear on DCCP-Data packets, as
	 * per table 3 in RFC 4340, 5.8. When running out of space क्रम other
	 * options (eg. Ack Vector which can take up to 255 bytes), it is better
	 * to schedule a separate Ack. Thus we leave headroom क्रम the following:
	 *  - 1 byte क्रम Slow Receiver (11.6)
	 *  - 6 bytes क्रम Timestamp (13.1)
	 *  - 10 bytes क्रम Timestamp Echo (13.3)
	 *  - 8 bytes क्रम NDP count (7.7, when activated)
	 *  - 6 bytes क्रम Data Checksum (9.3)
	 *  - %DCCPAV_MIN_OPTLEN bytes क्रम Ack Vector size (11.4, when enabled)
	 */
	cur_mps -= roundup(1 + 6 + 10 + dp->dccps_send_ndp_count * 8 + 6 +
			   (dp->dccps_hc_rx_ackvec ? DCCPAV_MIN_OPTLEN : 0), 4);

	/* And store cached results */
	icsk->icsk_pmtu_cookie = pmtu;
	dp->dccps_mss_cache = cur_mps;

	वापस cur_mps;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_sync_mss);

व्योम dccp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible(&wq->रुको);
	/* Should agree with poll, otherwise some programs अवरोध */
	अगर (sock_ग_लिखोable(sk))
		sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * dccp_रुको_क्रम_ccid  -  Aरुको CCID send permission
 * @sk:    socket to रुको क्रम
 * @delay: समयout in jअगरfies
 *
 * This is used by CCIDs which need to delay the send समय in process context.
 */
अटल पूर्णांक dccp_रुको_क्रम_ccid(काष्ठा sock *sk, अचिन्हित दीर्घ delay)
अणु
	DEFINE_WAIT(रुको);
	दीर्घ reमुख्यing;

	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	sk->sk_ग_लिखो_pending++;
	release_sock(sk);

	reमुख्यing = schedule_समयout(delay);

	lock_sock(sk);
	sk->sk_ग_लिखो_pending--;
	finish_रुको(sk_sleep(sk), &रुको);

	अगर (संकेत_pending(current) || sk->sk_err)
		वापस -1;
	वापस reमुख्यing;
पूर्ण

/**
 * dccp_xmit_packet  -  Send data packet under control of CCID
 * @sk: socket to send data packet on
 *
 * Transmits next-queued payload and inक्रमms CCID to account क्रम the packet.
 */
अटल व्योम dccp_xmit_packet(काष्ठा sock *sk)
अणु
	पूर्णांक err, len;
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा sk_buff *skb = dccp_qpolicy_pop(sk);

	अगर (unlikely(skb == शून्य))
		वापस;
	len = skb->len;

	अगर (sk->sk_state == DCCP_PARTOPEN) अणु
		स्थिर u32 cur_mps = dp->dccps_mss_cache - DCCP_FEATNEG_OVERHEAD;
		/*
		 * See 8.1.5 - Handshake Completion.
		 *
		 * For robustness we resend Confirm options until the client has
		 * entered OPEN. During the initial feature negotiation, the MPS
		 * is smaller than usual, reduced by the Change/Confirm options.
		 */
		अगर (!list_empty(&dp->dccps_featneg) && len > cur_mps) अणु
			DCCP_WARN("Payload too large (%d) for featneg.\n", len);
			dccp_send_ack(sk);
			dccp_feat_list_purge(&dp->dccps_featneg);
		पूर्ण

		inet_csk_schedule_ack(sk);
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_DACK,
					      inet_csk(sk)->icsk_rto,
					      DCCP_RTO_MAX);
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	पूर्ण अन्यथा अगर (dccp_ack_pending(sk)) अणु
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	पूर्ण अन्यथा अणु
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATA;
	पूर्ण

	err = dccp_transmit_skb(sk, skb);
	अगर (err)
		dccp_pr_debug("transmit_skb() returned err=%d\n", err);
	/*
	 * Register this one as sent even अगर an error occurred. To the remote
	 * end a local packet drop is indistinguishable from network loss, i.e.
	 * any local drop will eventually be reported via receiver feedback.
	 */
	ccid_hc_tx_packet_sent(dp->dccps_hc_tx_ccid, sk, len);

	/*
	 * If the CCID needs to transfer additional header options out-of-band
	 * (e.g. Ack Vectors or feature-negotiation options), it activates this
	 * flag to schedule a Sync. The Sync will स्वतःmatically incorporate all
	 * currently pending header options, thus clearing the backlog.
	 */
	अगर (dp->dccps_sync_scheduled)
		dccp_send_sync(sk, dp->dccps_gsr, DCCP_PKT_SYNC);
पूर्ण

/**
 * dccp_flush_ग_लिखो_queue  -  Drain queue at end of connection
 * @sk: socket to be drained
 * @समय_budget: समय allowed to drain the queue
 *
 * Since dccp_sendmsg queues packets without रुकोing क्रम them to be sent, it may
 * happen that the TX queue is not empty at the end of a connection. We give the
 * HC-sender CCID a grace period of up to @समय_budget jअगरfies. If this function
 * वापसs with a non-empty ग_लिखो queue, it will be purged later.
 */
व्योम dccp_flush_ग_लिखो_queue(काष्ठा sock *sk, दीर्घ *समय_budget)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा sk_buff *skb;
	दीर्घ delay, rc;

	जबतक (*समय_budget > 0 && (skb = skb_peek(&sk->sk_ग_लिखो_queue))) अणु
		rc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		चयन (ccid_packet_dequeue_eval(rc)) अणु
		हाल CCID_PACKET_WILL_DEQUEUE_LATER:
			/*
			 * If the CCID determines when to send, the next sending
			 * समय is unknown or the CCID may not even send again
			 * (e.g. remote host crashes or lost Ack packets).
			 */
			DCCP_WARN("CCID did not manage to send all packets\n");
			वापस;
		हाल CCID_PACKET_DELAY:
			delay = msecs_to_jअगरfies(rc);
			अगर (delay > *समय_budget)
				वापस;
			rc = dccp_रुको_क्रम_ccid(sk, delay);
			अगर (rc < 0)
				वापस;
			*समय_budget -= (delay - rc);
			/* check again अगर we can send now */
			अवरोध;
		हाल CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			अवरोध;
		हाल CCID_PACKET_ERR:
			skb_dequeue(&sk->sk_ग_लिखो_queue);
			kमुक्त_skb(skb);
			dccp_pr_debug("packet discarded due to err=%ld\n", rc);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dccp_ग_लिखो_xmit(काष्ठा sock *sk)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा sk_buff *skb;

	जबतक ((skb = dccp_qpolicy_top(sk))) अणु
		पूर्णांक rc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		चयन (ccid_packet_dequeue_eval(rc)) अणु
		हाल CCID_PACKET_WILL_DEQUEUE_LATER:
			वापस;
		हाल CCID_PACKET_DELAY:
			sk_reset_समयr(sk, &dp->dccps_xmit_समयr,
				       jअगरfies + msecs_to_jअगरfies(rc));
			वापस;
		हाल CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			अवरोध;
		हाल CCID_PACKET_ERR:
			dccp_qpolicy_drop(sk, skb);
			dccp_pr_debug("packet discarded due to err=%d\n", rc);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dccp_retransmit_skb  -  Retransmit Request, Close, or CloseReq packets
 * @sk: socket to perक्रमm retransmit on
 *
 * There are only four retransmittable packet types in DCCP:
 * - Request  in client-REQUEST  state (sec. 8.1.1),
 * - CloseReq in server-CLOSEREQ state (sec. 8.3),
 * - Close    in   node-CLOSING  state (sec. 8.3),
 * - Acks in client-PARTOPEN state (sec. 8.1.5, handled by dccp_delack_समयr()).
 * This function expects sk->sk_send_head to contain the original skb.
 */
पूर्णांक dccp_retransmit_skb(काष्ठा sock *sk)
अणु
	WARN_ON(sk->sk_send_head == शून्य);

	अगर (inet_csk(sk)->icsk_af_ops->rebuild_header(sk) != 0)
		वापस -EHOSTUNREACH; /* Routing failure or similar. */

	/* this count is used to distinguish original and retransmitted skb */
	inet_csk(sk)->icsk_retransmits++;

	वापस dccp_transmit_skb(sk, skb_clone(sk->sk_send_head, GFP_ATOMIC));
पूर्ण

काष्ठा sk_buff *dccp_make_response(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
				   काष्ठा request_sock *req)
अणु
	काष्ठा dccp_hdr *dh;
	काष्ठा dccp_request_sock *dreq;
	स्थिर u32 dccp_header_size = माप(काष्ठा dccp_hdr) +
				     माप(काष्ठा dccp_hdr_ext) +
				     माप(काष्ठा dccp_hdr_response);
	काष्ठा sk_buff *skb;

	/* sk is marked स्थिर to clearly express we करोnt hold socket lock.
	 * sock_wदो_स्मृति() will atomically change sk->sk_wmem_alloc,
	 * it is safe to promote sk to non स्थिर.
	 */
	skb = sock_wदो_स्मृति((काष्ठा sock *)sk, MAX_DCCP_HEADER, 1,
			   GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, MAX_DCCP_HEADER);

	skb_dst_set(skb, dst_clone(dst));

	dreq = dccp_rsk(req);
	अगर (inet_rsk(req)->acked)	/* increase GSS upon retransmission */
		dccp_inc_seqno(&dreq->dreq_gss);
	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_RESPONSE;
	DCCP_SKB_CB(skb)->dccpd_seq  = dreq->dreq_gss;

	/* Resolve feature dependencies resulting from choice of CCID */
	अगर (dccp_feat_server_ccid_dependencies(dreq))
		जाओ response_failed;

	अगर (dccp_insert_options_rsk(dreq, skb))
		जाओ response_failed;

	/* Build and checksum header */
	dh = dccp_zeroed_hdr(skb, dccp_header_size);

	dh->dccph_sport	= htons(inet_rsk(req)->ir_num);
	dh->dccph_dport	= inet_rsk(req)->ir_rmt_port;
	dh->dccph_करोff	= (dccp_header_size +
			   DCCP_SKB_CB(skb)->dccpd_opt_len) / 4;
	dh->dccph_type	= DCCP_PKT_RESPONSE;
	dh->dccph_x	= 1;
	dccp_hdr_set_seq(dh, dreq->dreq_gss);
	dccp_hdr_set_ack(dccp_hdr_ack_bits(skb), dreq->dreq_gsr);
	dccp_hdr_response(skb)->dccph_resp_service = dreq->dreq_service;

	dccp_csum_outgoing(skb);

	/* We use `acked' to remember that a Response was alपढ़ोy sent. */
	inet_rsk(req)->acked = 1;
	DCCP_INC_STATS(DCCP_MIB_OUTSEGS);
	वापस skb;
response_failed:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_make_response);

/* answer offending packet in @rcv_skb with Reset from control socket @ctl */
काष्ठा sk_buff *dccp_ctl_make_reset(काष्ठा sock *sk, काष्ठा sk_buff *rcv_skb)
अणु
	काष्ठा dccp_hdr *rxdh = dccp_hdr(rcv_skb), *dh;
	काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(rcv_skb);
	स्थिर u32 dccp_hdr_reset_len = माप(काष्ठा dccp_hdr) +
				       माप(काष्ठा dccp_hdr_ext) +
				       माप(काष्ठा dccp_hdr_reset);
	काष्ठा dccp_hdr_reset *dhr;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(sk->sk_prot->max_header, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस शून्य;

	skb_reserve(skb, sk->sk_prot->max_header);

	/* Swap the send and the receive. */
	dh = dccp_zeroed_hdr(skb, dccp_hdr_reset_len);
	dh->dccph_type	= DCCP_PKT_RESET;
	dh->dccph_sport	= rxdh->dccph_dport;
	dh->dccph_dport	= rxdh->dccph_sport;
	dh->dccph_करोff	= dccp_hdr_reset_len / 4;
	dh->dccph_x	= 1;

	dhr = dccp_hdr_reset(skb);
	dhr->dccph_reset_code = dcb->dccpd_reset_code;

	चयन (dcb->dccpd_reset_code) अणु
	हाल DCCP_RESET_CODE_PACKET_ERROR:
		dhr->dccph_reset_data[0] = rxdh->dccph_type;
		अवरोध;
	हाल DCCP_RESET_CODE_OPTION_ERROR:
	हाल DCCP_RESET_CODE_MANDATORY_ERROR:
		स_नकल(dhr->dccph_reset_data, dcb->dccpd_reset_data, 3);
		अवरोध;
	पूर्ण
	/*
	 * From RFC 4340, 8.3.1:
	 *   If P.ackno exists, set R.seqno := P.ackno + 1.
	 *   Else set R.seqno := 0.
	 */
	अगर (dcb->dccpd_ack_seq != DCCP_PKT_WITHOUT_ACK_SEQ)
		dccp_hdr_set_seq(dh, ADD48(dcb->dccpd_ack_seq, 1));
	dccp_hdr_set_ack(dccp_hdr_ack_bits(skb), dcb->dccpd_seq);

	dccp_csum_outgoing(skb);
	वापस skb;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_ctl_make_reset);

/* send Reset on established socket, to बंद or पात the connection */
पूर्णांक dccp_send_reset(काष्ठा sock *sk, क्रमागत dccp_reset_codes code)
अणु
	काष्ठा sk_buff *skb;
	/*
	 * FIXME: what अगर rebuild_header fails?
	 * Should we be करोing a rebuild_header here?
	 */
	पूर्णांक err = inet_csk(sk)->icsk_af_ops->rebuild_header(sk);

	अगर (err != 0)
		वापस err;

	skb = sock_wदो_स्मृति(sk, sk->sk_prot->max_header, 1, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOBUFS;

	/* Reserve space क्रम headers and prepare control bits. */
	skb_reserve(skb, sk->sk_prot->max_header);
	DCCP_SKB_CB(skb)->dccpd_type	   = DCCP_PKT_RESET;
	DCCP_SKB_CB(skb)->dccpd_reset_code = code;

	वापस dccp_transmit_skb(sk, skb);
पूर्ण

/*
 * Do all connect socket setups that can be करोne AF independent.
 */
पूर्णांक dccp_connect(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा dst_entry *dst = __sk_dst_get(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	sk->sk_err = 0;
	sock_reset_flag(sk, SOCK_DONE);

	dccp_sync_mss(sk, dst_mtu(dst));

	/* करो not connect अगर feature negotiation setup fails */
	अगर (dccp_feat_finalise_settings(dccp_sk(sk)))
		वापस -EPROTO;

	/* Initialise GAR as per 8.5; AWL/AWH are set in dccp_transmit_skb() */
	dp->dccps_gar = dp->dccps_iss;

	skb = alloc_skb(sk->sk_prot->max_header, sk->sk_allocation);
	अगर (unlikely(skb == शून्य))
		वापस -ENOBUFS;

	/* Reserve space क्रम headers. */
	skb_reserve(skb, sk->sk_prot->max_header);

	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_REQUEST;

	dccp_transmit_skb(sk, dccp_skb_entail(sk, skb));
	DCCP_INC_STATS(DCCP_MIB_ACTIVEOPENS);

	/* Timer क्रम repeating the REQUEST until an answer. */
	icsk->icsk_retransmits = 0;
	inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
				  icsk->icsk_rto, DCCP_RTO_MAX);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_connect);

व्योम dccp_send_ack(काष्ठा sock *sk)
अणु
	/* If we have been reset, we may not send again. */
	अगर (sk->sk_state != DCCP_CLOSED) अणु
		काष्ठा sk_buff *skb = alloc_skb(sk->sk_prot->max_header,
						GFP_ATOMIC);

		अगर (skb == शून्य) अणु
			inet_csk_schedule_ack(sk);
			inet_csk(sk)->icsk_ack.ato = TCP_ATO_MIN;
			inet_csk_reset_xmit_समयr(sk, ICSK_TIME_DACK,
						  TCP_DELACK_MAX,
						  DCCP_RTO_MAX);
			वापस;
		पूर्ण

		/* Reserve space क्रम headers */
		skb_reserve(skb, sk->sk_prot->max_header);
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_ACK;
		dccp_transmit_skb(sk, skb);
	पूर्ण
पूर्ण

EXPORT_SYMBOL_GPL(dccp_send_ack);

#अगर 0
/* FIXME: Is this still necessary (11.3) - currently nowhere used by DCCP. */
व्योम dccp_send_delayed_ack(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	/*
	 * FIXME: tune this समयr. elapsed समय fixes the skew, so no problem
	 * with using 2s, and active senders also piggyback the ACK पूर्णांकo a
	 * DATAACK packet, so this is really क्रम quiescent senders.
	 */
	अचिन्हित दीर्घ समयout = jअगरfies + 2 * HZ;

	/* Use new समयout only अगर there wasn't a older one earlier. */
	अगर (icsk->icsk_ack.pending & ICSK_ACK_TIMER) अणु
		/* If delack समयr was blocked or is about to expire,
		 * send ACK now.
		 *
		 * FIXME: check the "about to expire" part
		 */
		अगर (icsk->icsk_ack.blocked) अणु
			dccp_send_ack(sk);
			वापस;
		पूर्ण

		अगर (!समय_beक्रमe(समयout, icsk->icsk_ack.समयout))
			समयout = icsk->icsk_ack.समयout;
	पूर्ण
	icsk->icsk_ack.pending |= ICSK_ACK_SCHED | ICSK_ACK_TIMER;
	icsk->icsk_ack.समयout = समयout;
	sk_reset_समयr(sk, &icsk->icsk_delack_समयr, समयout);
पूर्ण
#पूर्ण_अगर

व्योम dccp_send_sync(काष्ठा sock *sk, स्थिर u64 ackno,
		    स्थिर क्रमागत dccp_pkt_type pkt_type)
अणु
	/*
	 * We are not putting this on the ग_लिखो queue, so
	 * dccp_transmit_skb() will set the ownership to this
	 * sock.
	 */
	काष्ठा sk_buff *skb = alloc_skb(sk->sk_prot->max_header, GFP_ATOMIC);

	अगर (skb == शून्य) अणु
		/* FIXME: how to make sure the sync is sent? */
		DCCP_CRIT("could not send %s", dccp_packet_name(pkt_type));
		वापस;
	पूर्ण

	/* Reserve space क्रम headers and prepare control bits. */
	skb_reserve(skb, sk->sk_prot->max_header);
	DCCP_SKB_CB(skb)->dccpd_type = pkt_type;
	DCCP_SKB_CB(skb)->dccpd_ack_seq = ackno;

	/*
	 * Clear the flag in हाल the Sync was scheduled क्रम out-of-band data,
	 * such as carrying a दीर्घ Ack Vector.
	 */
	dccp_sk(sk)->dccps_sync_scheduled = 0;

	dccp_transmit_skb(sk, skb);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_send_sync);

/*
 * Send a DCCP_PKT_CLOSE/CLOSEREQ. The caller locks the socket क्रम us. This
 * cannot be allowed to fail queueing a DCCP_PKT_CLOSE/CLOSEREQ frame under
 * any circumstances.
 */
व्योम dccp_send_बंद(काष्ठा sock *sk, स्थिर पूर्णांक active)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा sk_buff *skb;
	स्थिर gfp_t prio = active ? GFP_KERNEL : GFP_ATOMIC;

	skb = alloc_skb(sk->sk_prot->max_header, prio);
	अगर (skb == शून्य)
		वापस;

	/* Reserve space क्रम headers and prepare control bits. */
	skb_reserve(skb, sk->sk_prot->max_header);
	अगर (dp->dccps_role == DCCP_ROLE_SERVER && !dp->dccps_server_समयरुको)
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CLOSEREQ;
	अन्यथा
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CLOSE;

	अगर (active) अणु
		skb = dccp_skb_entail(sk, skb);
		/*
		 * Retransmission समयr क्रम active-बंद: RFC 4340, 8.3 requires
		 * to retransmit the Close/CloseReq until the CLOSING/CLOSEREQ
		 * state can be left. The initial समयout is 2 RTTs.
		 * Since RTT measurement is करोne by the CCIDs, there is no easy
		 * way to get an RTT sample. The fallback RTT from RFC 4340, 3.4
		 * is too low (200ms); we use a high value to aव्योम unnecessary
		 * retransmissions when the link RTT is > 0.2 seconds.
		 * FIXME: Let मुख्य module sample RTTs and use that instead.
		 */
		inet_csk_reset_xmit_समयr(sk, ICSK_TIME_RETRANS,
					  DCCP_TIMEOUT_INIT, DCCP_RTO_MAX);
	पूर्ण
	dccp_transmit_skb(sk, skb);
पूर्ण
