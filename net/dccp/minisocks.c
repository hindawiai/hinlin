<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/minisocks.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>

#समावेश <net/sock.h>
#समावेश <net/xfrm.h>
#समावेश <net/inet_समयरुको_sock.h>

#समावेश "ackvec.h"
#समावेश "ccid.h"
#समावेश "dccp.h"
#समावेश "feat.h"

काष्ठा inet_समयरुको_death_row dccp_death_row = अणु
	.sysctl_max_tw_buckets = NR_खाता * 2,
	.hashinfo	= &dccp_hashinfo,
पूर्ण;

EXPORT_SYMBOL_GPL(dccp_death_row);

व्योम dccp_समय_रुको(काष्ठा sock *sk, पूर्णांक state, पूर्णांक समयo)
अणु
	काष्ठा inet_समयरुको_sock *tw;

	tw = inet_twsk_alloc(sk, &dccp_death_row, state);

	अगर (tw != शून्य) अणु
		स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
		स्थिर पूर्णांक rto = (icsk->icsk_rto << 2) - (icsk->icsk_rto >> 1);
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (tw->tw_family == PF_INET6) अणु
			tw->tw_v6_daddr = sk->sk_v6_daddr;
			tw->tw_v6_rcv_saddr = sk->sk_v6_rcv_saddr;
			tw->tw_ipv6only = sk->sk_ipv6only;
		पूर्ण
#पूर्ण_अगर

		/* Get the TIME_WAIT समयout firing. */
		अगर (समयo < rto)
			समयo = rto;

		अगर (state == DCCP_TIME_WAIT)
			समयo = DCCP_TIMEWAIT_LEN;

		/* tw_समयr is pinned, so we need to make sure BH are disabled
		 * in following section, otherwise समयr handler could run beक्रमe
		 * we complete the initialization.
		 */
		local_bh_disable();
		inet_twsk_schedule(tw, समयo);
		/* Linkage updates.
		 * Note that access to tw after this poपूर्णांक is illegal.
		 */
		inet_twsk_hashdance(tw, sk, &dccp_hashinfo);
		local_bh_enable();
	पूर्ण अन्यथा अणु
		/* Sorry, अगर we're out of memory, just CLOSE this
		 * socket up.  We've got bigger problems than
		 * non-graceful socket closings.
		 */
		DCCP_WARN("time wait bucket table overflow\n");
	पूर्ण

	dccp_करोne(sk);
पूर्ण

काष्ठा sock *dccp_create_खोलोreq_child(स्थिर काष्ठा sock *sk,
				       स्थिर काष्ठा request_sock *req,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	/*
	 * Step 3: Process LISTEN state
	 *
	 *   (* Generate a new socket and चयन to that socket *)
	 *   Set S := new socket क्रम this port pair
	 */
	काष्ठा sock *newsk = inet_csk_clone_lock(sk, req, GFP_ATOMIC);

	अगर (newsk != शून्य) अणु
		काष्ठा dccp_request_sock *dreq = dccp_rsk(req);
		काष्ठा inet_connection_sock *newicsk = inet_csk(newsk);
		काष्ठा dccp_sock *newdp = dccp_sk(newsk);

		newdp->dccps_role	    = DCCP_ROLE_SERVER;
		newdp->dccps_hc_rx_ackvec   = शून्य;
		newdp->dccps_service_list   = शून्य;
		newdp->dccps_service	    = dreq->dreq_service;
		newdp->dccps_बारtamp_echo = dreq->dreq_बारtamp_echo;
		newdp->dccps_बारtamp_समय = dreq->dreq_बारtamp_समय;
		newicsk->icsk_rto	    = DCCP_TIMEOUT_INIT;

		INIT_LIST_HEAD(&newdp->dccps_featneg);
		/*
		 * Step 3: Process LISTEN state
		 *
		 *    Choose S.ISS (initial seqno) or set from Init Cookies
		 *    Initialize S.GAR := S.ISS
		 *    Set S.ISR, S.GSR from packet (or Init Cookies)
		 *
		 *    Setting AWL/AWH and SWL/SWH happens as part of the feature
		 *    activation below, as these winकरोws all depend on the local
		 *    and remote Sequence Winकरोw feature values (7.5.2).
		 */
		newdp->dccps_iss = dreq->dreq_iss;
		newdp->dccps_gss = dreq->dreq_gss;
		newdp->dccps_gar = newdp->dccps_iss;
		newdp->dccps_isr = dreq->dreq_isr;
		newdp->dccps_gsr = dreq->dreq_gsr;

		/*
		 * Activate features: initialise CCIDs, sequence winकरोws etc.
		 */
		अगर (dccp_feat_activate_values(newsk, &dreq->dreq_featneg)) अणु
			sk_मुक्त_unlock_clone(newsk);
			वापस शून्य;
		पूर्ण
		dccp_init_xmit_समयrs(newsk);

		__DCCP_INC_STATS(DCCP_MIB_PASSIVEOPENS);
	पूर्ण
	वापस newsk;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_create_खोलोreq_child);

/*
 * Process an incoming packet क्रम RESPOND sockets represented
 * as an request_sock.
 */
काष्ठा sock *dccp_check_req(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा request_sock *req)
अणु
	काष्ठा sock *child = शून्य;
	काष्ठा dccp_request_sock *dreq = dccp_rsk(req);
	bool own_req;

	/* TCP/DCCP listeners became lockless.
	 * DCCP stores complex state in its request_sock, so we need
	 * a protection क्रम them, now this code runs without being रक्षित
	 * by the parent (listener) lock.
	 */
	spin_lock_bh(&dreq->dreq_lock);

	/* Check क्रम retransmitted REQUEST */
	अगर (dccp_hdr(skb)->dccph_type == DCCP_PKT_REQUEST) अणु

		अगर (after48(DCCP_SKB_CB(skb)->dccpd_seq, dreq->dreq_gsr)) अणु
			dccp_pr_debug("Retransmitted REQUEST\n");
			dreq->dreq_gsr = DCCP_SKB_CB(skb)->dccpd_seq;
			/*
			 * Send another RESPONSE packet
			 * To protect against Request floods, increment retrans
			 * counter (backoff, monitored by dccp_response_समयr).
			 */
			inet_rtx_syn_ack(sk, req);
		पूर्ण
		/* Network Duplicate, discard packet */
		जाओ out;
	पूर्ण

	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_PACKET_ERROR;

	अगर (dccp_hdr(skb)->dccph_type != DCCP_PKT_ACK &&
	    dccp_hdr(skb)->dccph_type != DCCP_PKT_DATAACK)
		जाओ drop;

	/* Invalid ACK */
	अगर (!between48(DCCP_SKB_CB(skb)->dccpd_ack_seq,
				dreq->dreq_iss, dreq->dreq_gss)) अणु
		dccp_pr_debug("Invalid ACK number: ack_seq=%llu, "
			      "dreq_iss=%llu, dreq_gss=%llu\n",
			      (अचिन्हित दीर्घ दीर्घ)
			      DCCP_SKB_CB(skb)->dccpd_ack_seq,
			      (अचिन्हित दीर्घ दीर्घ) dreq->dreq_iss,
			      (अचिन्हित दीर्घ दीर्घ) dreq->dreq_gss);
		जाओ drop;
	पूर्ण

	अगर (dccp_parse_options(sk, dreq, skb))
		 जाओ drop;

	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, शून्य,
							 req, &own_req);
	अगर (child) अणु
		child = inet_csk_complete_hashdance(sk, child, req, own_req);
		जाओ out;
	पूर्ण

	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_TOO_BUSY;
drop:
	अगर (dccp_hdr(skb)->dccph_type != DCCP_PKT_RESET)
		req->rsk_ops->send_reset(sk, skb);

	inet_csk_reqsk_queue_drop(sk, req);
out:
	spin_unlock_bh(&dreq->dreq_lock);
	वापस child;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_check_req);

/*
 *  Queue segment on the new socket अगर the new socket is active,
 *  otherwise we just लघुcircuit this and जारी with
 *  the new socket.
 */
पूर्णांक dccp_child_process(काष्ठा sock *parent, काष्ठा sock *child,
		       काष्ठा sk_buff *skb)
	__releases(child)
अणु
	पूर्णांक ret = 0;
	स्थिर पूर्णांक state = child->sk_state;

	अगर (!sock_owned_by_user(child)) अणु
		ret = dccp_rcv_state_process(child, skb, dccp_hdr(skb),
					     skb->len);

		/* Wakeup parent, send SIGIO */
		अगर (state == DCCP_RESPOND && child->sk_state != state)
			parent->sk_data_पढ़ोy(parent);
	पूर्ण अन्यथा अणु
		/* Alas, it is possible again, because we करो lookup
		 * in मुख्य socket hash table and lock on listening
		 * socket करोes not protect us more.
		 */
		__sk_add_backlog(child, skb);
	पूर्ण

	bh_unlock_sock(child);
	sock_put(child);
	वापस ret;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_child_process);

व्योम dccp_reqsk_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 काष्ठा request_sock *rsk)
अणु
	DCCP_BUG("DCCP-ACK packets are never sent in LISTEN/RESPOND state");
पूर्ण

EXPORT_SYMBOL_GPL(dccp_reqsk_send_ack);

पूर्णांक dccp_reqsk_init(काष्ठा request_sock *req,
		    काष्ठा dccp_sock स्थिर *dp, काष्ठा sk_buff स्थिर *skb)
अणु
	काष्ठा dccp_request_sock *dreq = dccp_rsk(req);

	spin_lock_init(&dreq->dreq_lock);
	inet_rsk(req)->ir_rmt_port = dccp_hdr(skb)->dccph_sport;
	inet_rsk(req)->ir_num	   = ntohs(dccp_hdr(skb)->dccph_dport);
	inet_rsk(req)->acked	   = 0;
	dreq->dreq_बारtamp_echo  = 0;

	/* inherit feature negotiation options from listening socket */
	वापस dccp_feat_clone_list(&dp->dccps_featneg, &dreq->dreq_featneg);
पूर्ण

EXPORT_SYMBOL_GPL(dccp_reqsk_init);
