<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC packet transmission
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/net.h>
#समावेश <linux/gfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

काष्ठा rxrpc_ack_buffer अणु
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा rxrpc_ackpacket ack;
	u8 acks[255];
	u8 pad[3];
	काष्ठा rxrpc_ackinfo ackinfo;
पूर्ण;

काष्ठा rxrpc_पात_buffer अणु
	काष्ठा rxrpc_wire_header whdr;
	__be32 पात_code;
पूर्ण;

अटल स्थिर अक्षर rxrpc_keepalive_string[] = "";

/*
 * Increase Tx backoff on transmission failure and clear it on success.
 */
अटल व्योम rxrpc_tx_backoff(काष्ठा rxrpc_call *call, पूर्णांक ret)
अणु
	अगर (ret < 0) अणु
		u16 tx_backoff = READ_ONCE(call->tx_backoff);

		अगर (tx_backoff < HZ)
			WRITE_ONCE(call->tx_backoff, tx_backoff + 1);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(call->tx_backoff, 0);
	पूर्ण
पूर्ण

/*
 * Arrange क्रम a keepalive ping a certain समय after we last transmitted.  This
 * lets the far side know we're still पूर्णांकerested in this call and helps keep
 * the route through any पूर्णांकervening firewall खोलो.
 *
 * Receiving a response to the ping will prevent the ->expect_rx_by समयr from
 * expiring.
 */
अटल व्योम rxrpc_set_keepalive(काष्ठा rxrpc_call *call)
अणु
	अचिन्हित दीर्घ now = jअगरfies, keepalive_at = call->next_rx_timo / 6;

	keepalive_at += now;
	WRITE_ONCE(call->keepalive_at, keepalive_at);
	rxrpc_reduce_call_समयr(call, keepalive_at, now,
				rxrpc_समयr_set_क्रम_keepalive);
पूर्ण

/*
 * Fill out an ACK packet.
 */
अटल माप_प्रकार rxrpc_fill_out_ack(काष्ठा rxrpc_connection *conn,
				 काष्ठा rxrpc_call *call,
				 काष्ठा rxrpc_ack_buffer *pkt,
				 rxrpc_seq_t *_hard_ack,
				 rxrpc_seq_t *_top,
				 u8 reason)
अणु
	rxrpc_serial_t serial;
	rxrpc_seq_t hard_ack, top, seq;
	पूर्णांक ix;
	u32 mtu, jmax;
	u8 *ackp = pkt->acks;

	/* Barrier against rxrpc_input_data(). */
	serial = call->ackr_serial;
	hard_ack = READ_ONCE(call->rx_hard_ack);
	top = smp_load_acquire(&call->rx_top);
	*_hard_ack = hard_ack;
	*_top = top;

	pkt->ack.bufferSpace	= htons(8);
	pkt->ack.maxSkew	= htons(0);
	pkt->ack.firstPacket	= htonl(hard_ack + 1);
	pkt->ack.previousPacket	= htonl(call->ackr_prev_seq);
	pkt->ack.serial		= htonl(serial);
	pkt->ack.reason		= reason;
	pkt->ack.nAcks		= top - hard_ack;

	अगर (reason == RXRPC_ACK_PING)
		pkt->whdr.flags |= RXRPC_REQUEST_ACK;

	अगर (after(top, hard_ack)) अणु
		seq = hard_ack + 1;
		करो अणु
			ix = seq & RXRPC_RXTX_BUFF_MASK;
			अगर (call->rxtx_buffer[ix])
				*ackp++ = RXRPC_ACK_TYPE_ACK;
			अन्यथा
				*ackp++ = RXRPC_ACK_TYPE_NACK;
			seq++;
		पूर्ण जबतक (beक्रमe_eq(seq, top));
	पूर्ण

	mtu = conn->params.peer->अगर_mtu;
	mtu -= conn->params.peer->hdrsize;
	jmax = (call->nr_jumbo_bad > 3) ? 1 : rxrpc_rx_jumbo_max;
	pkt->ackinfo.rxMTU	= htonl(rxrpc_rx_mtu);
	pkt->ackinfo.maxMTU	= htonl(mtu);
	pkt->ackinfo.rwind	= htonl(call->rx_winsize);
	pkt->ackinfo.jumbo_max	= htonl(jmax);

	*ackp++ = 0;
	*ackp++ = 0;
	*ackp++ = 0;
	वापस top - hard_ack + 3;
पूर्ण

/*
 * Record the beginning of an RTT probe.
 */
अटल पूर्णांक rxrpc_begin_rtt_probe(काष्ठा rxrpc_call *call, rxrpc_serial_t serial,
				 क्रमागत rxrpc_rtt_tx_trace why)
अणु
	अचिन्हित दीर्घ avail = call->rtt_avail;
	पूर्णांक rtt_slot = 9;

	अगर (!(avail & RXRPC_CALL_RTT_AVAIL_MASK))
		जाओ no_slot;

	rtt_slot = __ffs(avail & RXRPC_CALL_RTT_AVAIL_MASK);
	अगर (!test_and_clear_bit(rtt_slot, &call->rtt_avail))
		जाओ no_slot;

	call->rtt_serial[rtt_slot] = serial;
	call->rtt_sent_at[rtt_slot] = kसमय_get_real();
	smp_wmb(); /* Write data beक्रमe avail bit */
	set_bit(rtt_slot + RXRPC_CALL_RTT_PEND_SHIFT, &call->rtt_avail);

	trace_rxrpc_rtt_tx(call, why, rtt_slot, serial);
	वापस rtt_slot;

no_slot:
	trace_rxrpc_rtt_tx(call, rxrpc_rtt_tx_no_slot, rtt_slot, serial);
	वापस -1;
पूर्ण

/*
 * Cancel an RTT probe.
 */
अटल व्योम rxrpc_cancel_rtt_probe(काष्ठा rxrpc_call *call,
				   rxrpc_serial_t serial, पूर्णांक rtt_slot)
अणु
	अगर (rtt_slot != -1) अणु
		clear_bit(rtt_slot + RXRPC_CALL_RTT_PEND_SHIFT, &call->rtt_avail);
		smp_wmb(); /* Clear pending bit beक्रमe setting slot */
		set_bit(rtt_slot, &call->rtt_avail);
		trace_rxrpc_rtt_tx(call, rxrpc_rtt_tx_cancel, rtt_slot, serial);
	पूर्ण
पूर्ण

/*
 * Send an ACK call packet.
 */
पूर्णांक rxrpc_send_ack_packet(काष्ठा rxrpc_call *call, bool ping,
			  rxrpc_serial_t *_serial)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_ack_buffer *pkt;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	rxrpc_serial_t serial;
	rxrpc_seq_t hard_ack, top;
	माप_प्रकार len, n;
	पूर्णांक ret, rtt_slot = -1;
	u8 reason;

	अगर (test_bit(RXRPC_CALL_DISCONNECTED, &call->flags))
		वापस -ECONNRESET;

	pkt = kzalloc(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	conn = call->conn;

	msg.msg_name	= &call->peer->srx.transport;
	msg.msg_namelen	= call->peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	pkt->whdr.epoch		= htonl(conn->proto.epoch);
	pkt->whdr.cid		= htonl(call->cid);
	pkt->whdr.callNumber	= htonl(call->call_id);
	pkt->whdr.seq		= 0;
	pkt->whdr.type		= RXRPC_PACKET_TYPE_ACK;
	pkt->whdr.flags		= RXRPC_SLOW_START_OK | conn->out_clientflag;
	pkt->whdr.userStatus	= 0;
	pkt->whdr.securityIndex	= call->security_ix;
	pkt->whdr._rsvd		= 0;
	pkt->whdr.serviceId	= htons(call->service_id);

	spin_lock_bh(&call->lock);
	अगर (ping) अणु
		reason = RXRPC_ACK_PING;
	पूर्ण अन्यथा अणु
		reason = call->ackr_reason;
		अगर (!call->ackr_reason) अणु
			spin_unlock_bh(&call->lock);
			ret = 0;
			जाओ out;
		पूर्ण
		call->ackr_reason = 0;
	पूर्ण
	n = rxrpc_fill_out_ack(conn, call, pkt, &hard_ack, &top, reason);

	spin_unlock_bh(&call->lock);

	iov[0].iov_base	= pkt;
	iov[0].iov_len	= माप(pkt->whdr) + माप(pkt->ack) + n;
	iov[1].iov_base = &pkt->ackinfo;
	iov[1].iov_len	= माप(pkt->ackinfo);
	len = iov[0].iov_len + iov[1].iov_len;

	serial = atomic_inc_वापस(&conn->serial);
	pkt->whdr.serial = htonl(serial);
	trace_rxrpc_tx_ack(call->debug_id, serial,
			   ntohl(pkt->ack.firstPacket),
			   ntohl(pkt->ack.serial),
			   pkt->ack.reason, pkt->ack.nAcks);
	अगर (_serial)
		*_serial = serial;

	अगर (ping)
		rtt_slot = rxrpc_begin_rtt_probe(call, serial, rxrpc_rtt_tx_ping);

	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, 2, len);
	conn->params.peer->last_tx_at = kसमय_get_seconds();
	अगर (ret < 0)
		trace_rxrpc_tx_fail(call->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_call_ack);
	अन्यथा
		trace_rxrpc_tx_packet(call->debug_id, &pkt->whdr,
				      rxrpc_tx_poपूर्णांक_call_ack);
	rxrpc_tx_backoff(call, ret);

	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		अगर (ret < 0) अणु
			rxrpc_cancel_rtt_probe(call, serial, rtt_slot);
			rxrpc_propose_ACK(call, pkt->ack.reason,
					  ntohl(pkt->ack.serial),
					  false, true,
					  rxrpc_propose_ack_retry_tx);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&call->lock);
			अगर (after(hard_ack, call->ackr_consumed))
				call->ackr_consumed = hard_ack;
			अगर (after(top, call->ackr_seen))
				call->ackr_seen = top;
			spin_unlock_bh(&call->lock);
		पूर्ण

		rxrpc_set_keepalive(call);
	पूर्ण

out:
	kमुक्त(pkt);
	वापस ret;
पूर्ण

/*
 * Send an ABORT call packet.
 */
पूर्णांक rxrpc_send_पात_packet(काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_पात_buffer pkt;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[1];
	rxrpc_serial_t serial;
	पूर्णांक ret;

	/* Don't bother sending पातs क्रम a client call once the server has
	 * hard-ACK'd all of its request data.  After that point, we're not
	 * going to stop the operation proceeding, and whilst we might limit
	 * the reply, it's not worth it अगर we can send a new call on the same
	 * channel instead, thereby closing off this call.
	 */
	अगर (rxrpc_is_client_call(call) &&
	    test_bit(RXRPC_CALL_TX_LAST, &call->flags))
		वापस 0;

	अगर (test_bit(RXRPC_CALL_DISCONNECTED, &call->flags))
		वापस -ECONNRESET;

	conn = call->conn;

	msg.msg_name	= &call->peer->srx.transport;
	msg.msg_namelen	= call->peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	pkt.whdr.epoch		= htonl(conn->proto.epoch);
	pkt.whdr.cid		= htonl(call->cid);
	pkt.whdr.callNumber	= htonl(call->call_id);
	pkt.whdr.seq		= 0;
	pkt.whdr.type		= RXRPC_PACKET_TYPE_ABORT;
	pkt.whdr.flags		= conn->out_clientflag;
	pkt.whdr.userStatus	= 0;
	pkt.whdr.securityIndex	= call->security_ix;
	pkt.whdr._rsvd		= 0;
	pkt.whdr.serviceId	= htons(call->service_id);
	pkt.पात_code		= htonl(call->पात_code);

	iov[0].iov_base	= &pkt;
	iov[0].iov_len	= माप(pkt);

	serial = atomic_inc_वापस(&conn->serial);
	pkt.whdr.serial = htonl(serial);

	ret = kernel_sendmsg(conn->params.local->socket,
			     &msg, iov, 1, माप(pkt));
	conn->params.peer->last_tx_at = kसमय_get_seconds();
	अगर (ret < 0)
		trace_rxrpc_tx_fail(call->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_call_पात);
	अन्यथा
		trace_rxrpc_tx_packet(call->debug_id, &pkt.whdr,
				      rxrpc_tx_poपूर्णांक_call_पात);
	rxrpc_tx_backoff(call, ret);
	वापस ret;
पूर्ण

/*
 * send a packet through the transport endpoपूर्णांक
 */
पूर्णांक rxrpc_send_data_packet(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			   bool retrans)
अणु
	काष्ठा rxrpc_connection *conn = call->conn;
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	rxrpc_serial_t serial;
	माप_प्रकार len;
	पूर्णांक ret, rtt_slot = -1;

	_enter(",{%d}", skb->len);

	अगर (hlist_unhashed(&call->error_link)) अणु
		spin_lock_bh(&call->peer->lock);
		hlist_add_head_rcu(&call->error_link, &call->peer->error_tarमाला_लो);
		spin_unlock_bh(&call->peer->lock);
	पूर्ण

	/* Each transmission of a Tx packet needs a new serial number */
	serial = atomic_inc_वापस(&conn->serial);

	whdr.epoch	= htonl(conn->proto.epoch);
	whdr.cid	= htonl(call->cid);
	whdr.callNumber	= htonl(call->call_id);
	whdr.seq	= htonl(sp->hdr.seq);
	whdr.serial	= htonl(serial);
	whdr.type	= RXRPC_PACKET_TYPE_DATA;
	whdr.flags	= sp->hdr.flags;
	whdr.userStatus	= 0;
	whdr.securityIndex = call->security_ix;
	whdr._rsvd	= htons(sp->hdr._rsvd);
	whdr.serviceId	= htons(call->service_id);

	अगर (test_bit(RXRPC_CONN_PROBING_FOR_UPGRADE, &conn->flags) &&
	    sp->hdr.seq == 1)
		whdr.userStatus	= RXRPC_USERSTATUS_SERVICE_UPGRADE;

	iov[0].iov_base = &whdr;
	iov[0].iov_len = माप(whdr);
	iov[1].iov_base = skb->head;
	iov[1].iov_len = skb->len;
	len = iov[0].iov_len + iov[1].iov_len;

	msg.msg_name = &call->peer->srx.transport;
	msg.msg_namelen = call->peer->srx.transport_len;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	/* If our RTT cache needs working on, request an ACK.  Also request
	 * ACKs अगर a DATA packet appears to have been lost.
	 *
	 * However, we mustn't request an ACK on the last reply packet of a
	 * service call, lest OpenAFS incorrectly send us an ACK with some
	 * soft-ACKs in it and then never follow up with a proper hard ACK.
	 */
	अगर ((!(sp->hdr.flags & RXRPC_LAST_PACKET) ||
	     rxrpc_to_server(sp)
	     ) &&
	    (test_and_clear_bit(RXRPC_CALL_EV_ACK_LOST, &call->events) ||
	     retrans ||
	     call->cong_mode == RXRPC_CALL_SLOW_START ||
	     (call->peer->rtt_count < 3 && sp->hdr.seq & 1) ||
	     kसमय_beक्रमe(kसमय_add_ms(call->peer->rtt_last_req, 1000),
			  kसमय_get_real())))
		whdr.flags |= RXRPC_REQUEST_ACK;

	अगर (IS_ENABLED(CONFIG_AF_RXRPC_INJECT_LOSS)) अणु
		अटल पूर्णांक lose;
		अगर ((lose++ & 7) == 7) अणु
			ret = 0;
			trace_rxrpc_tx_data(call, sp->hdr.seq, serial,
					    whdr.flags, retrans, true);
			जाओ करोne;
		पूर्ण
	पूर्ण

	trace_rxrpc_tx_data(call, sp->hdr.seq, serial, whdr.flags, retrans,
			    false);

	/* send the packet with the करोn't fragment bit set अगर we currently
	 * think it's small enough */
	अगर (iov[1].iov_len >= call->peer->maxdata)
		जाओ send_fragmentable;

	करोwn_पढ़ो(&conn->params.local->defrag_sem);

	sp->hdr.serial = serial;
	smp_wmb(); /* Set serial beक्रमe बारtamp */
	skb->tstamp = kसमय_get_real();
	अगर (whdr.flags & RXRPC_REQUEST_ACK)
		rtt_slot = rxrpc_begin_rtt_probe(call, serial, rxrpc_rtt_tx_data);

	/* send the packet by UDP
	 * - वापसs -EMSGSIZE अगर UDP would have to fragment the packet
	 *   to go out of the पूर्णांकerface
	 *   - in which हाल, we'll have processed the ICMP error
	 *     message and update the peer record
	 */
	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, 2, len);
	conn->params.peer->last_tx_at = kसमय_get_seconds();

	up_पढ़ो(&conn->params.local->defrag_sem);
	अगर (ret < 0) अणु
		rxrpc_cancel_rtt_probe(call, serial, rtt_slot);
		trace_rxrpc_tx_fail(call->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_call_data_nofrag);
	पूर्ण अन्यथा अणु
		trace_rxrpc_tx_packet(call->debug_id, &whdr,
				      rxrpc_tx_poपूर्णांक_call_data_nofrag);
	पूर्ण

	rxrpc_tx_backoff(call, ret);
	अगर (ret == -EMSGSIZE)
		जाओ send_fragmentable;

करोne:
	अगर (ret >= 0) अणु
		अगर (whdr.flags & RXRPC_REQUEST_ACK) अणु
			call->peer->rtt_last_req = skb->tstamp;
			अगर (call->peer->rtt_count > 1) अणु
				अचिन्हित दीर्घ nowj = jअगरfies, ack_lost_at;

				ack_lost_at = rxrpc_get_rto_backoff(call->peer, retrans);
				ack_lost_at += nowj;
				WRITE_ONCE(call->ack_lost_at, ack_lost_at);
				rxrpc_reduce_call_समयr(call, ack_lost_at, nowj,
							rxrpc_समयr_set_क्रम_lost_ack);
			पूर्ण
		पूर्ण

		अगर (sp->hdr.seq == 1 &&
		    !test_and_set_bit(RXRPC_CALL_BEGAN_RX_TIMER,
				      &call->flags)) अणु
			अचिन्हित दीर्घ nowj = jअगरfies, expect_rx_by;

			expect_rx_by = nowj + call->next_rx_timo;
			WRITE_ONCE(call->expect_rx_by, expect_rx_by);
			rxrpc_reduce_call_समयr(call, expect_rx_by, nowj,
						rxrpc_समयr_set_क्रम_normal);
		पूर्ण

		rxrpc_set_keepalive(call);
	पूर्ण अन्यथा अणु
		/* Cancel the call अगर the initial transmission fails,
		 * particularly अगर that's due to network routing issues that
		 * aren't going away anyसमय soon.  The layer above can arrange
		 * the retransmission.
		 */
		अगर (!test_and_set_bit(RXRPC_CALL_BEGAN_RX_TIMER, &call->flags))
			rxrpc_set_call_completion(call, RXRPC_CALL_LOCAL_ERROR,
						  RX_USER_ABORT, ret);
	पूर्ण

	_leave(" = %d [%u]", ret, call->peer->maxdata);
	वापस ret;

send_fragmentable:
	/* attempt to send this message with fragmentation enabled */
	_debug("send fragment");

	करोwn_ग_लिखो(&conn->params.local->defrag_sem);

	sp->hdr.serial = serial;
	smp_wmb(); /* Set serial beक्रमe बारtamp */
	skb->tstamp = kसमय_get_real();
	अगर (whdr.flags & RXRPC_REQUEST_ACK)
		rtt_slot = rxrpc_begin_rtt_probe(call, serial, rxrpc_rtt_tx_data);

	चयन (conn->params.local->srx.transport.family) अणु
	हाल AF_INET6:
	हाल AF_INET:
		ip_sock_set_mtu_discover(conn->params.local->socket->sk,
				IP_PMTUDISC_DONT);
		ret = kernel_sendmsg(conn->params.local->socket, &msg,
				     iov, 2, len);
		conn->params.peer->last_tx_at = kसमय_get_seconds();

		ip_sock_set_mtu_discover(conn->params.local->socket->sk,
				IP_PMTUDISC_DO);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	अगर (ret < 0) अणु
		rxrpc_cancel_rtt_probe(call, serial, rtt_slot);
		trace_rxrpc_tx_fail(call->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_call_data_frag);
	पूर्ण अन्यथा अणु
		trace_rxrpc_tx_packet(call->debug_id, &whdr,
				      rxrpc_tx_poपूर्णांक_call_data_frag);
	पूर्ण
	rxrpc_tx_backoff(call, ret);

	up_ग_लिखो(&conn->params.local->defrag_sem);
	जाओ करोne;
पूर्ण

/*
 * reject packets through the local endpoपूर्णांक
 */
व्योम rxrpc_reject_packets(काष्ठा rxrpc_local *local)
अणु
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा sk_buff *skb;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	माप_प्रकार size;
	__be32 code;
	पूर्णांक ret, ioc;

	_enter("%d", local->debug_id);

	iov[0].iov_base = &whdr;
	iov[0].iov_len = माप(whdr);
	iov[1].iov_base = &code;
	iov[1].iov_len = माप(code);

	msg.msg_name = &srx.transport;
	msg.msg_control = शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	स_रखो(&whdr, 0, माप(whdr));

	जबतक ((skb = skb_dequeue(&local->reject_queue))) अणु
		rxrpc_see_skb(skb, rxrpc_skb_seen);
		sp = rxrpc_skb(skb);

		चयन (skb->mark) अणु
		हाल RXRPC_SKB_MARK_REJECT_BUSY:
			whdr.type = RXRPC_PACKET_TYPE_BUSY;
			size = माप(whdr);
			ioc = 1;
			अवरोध;
		हाल RXRPC_SKB_MARK_REJECT_ABORT:
			whdr.type = RXRPC_PACKET_TYPE_ABORT;
			code = htonl(skb->priority);
			size = माप(whdr) + माप(code);
			ioc = 2;
			अवरोध;
		शेष:
			rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
			जारी;
		पूर्ण

		अगर (rxrpc_extract_addr_from_skb(&srx, skb) == 0) अणु
			msg.msg_namelen = srx.transport_len;

			whdr.epoch	= htonl(sp->hdr.epoch);
			whdr.cid	= htonl(sp->hdr.cid);
			whdr.callNumber	= htonl(sp->hdr.callNumber);
			whdr.serviceId	= htons(sp->hdr.serviceId);
			whdr.flags	= sp->hdr.flags;
			whdr.flags	^= RXRPC_CLIENT_INITIATED;
			whdr.flags	&= RXRPC_CLIENT_INITIATED;

			ret = kernel_sendmsg(local->socket, &msg,
					     iov, ioc, size);
			अगर (ret < 0)
				trace_rxrpc_tx_fail(local->debug_id, 0, ret,
						    rxrpc_tx_poपूर्णांक_reject);
			अन्यथा
				trace_rxrpc_tx_packet(local->debug_id, &whdr,
						      rxrpc_tx_poपूर्णांक_reject);
		पूर्ण

		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	पूर्ण

	_leave("");
पूर्ण

/*
 * Send a VERSION reply to a peer as a keepalive.
 */
व्योम rxrpc_send_keepalive(काष्ठा rxrpc_peer *peer)
अणु
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	माप_प्रकार len;
	पूर्णांक ret;

	_enter("");

	msg.msg_name	= &peer->srx.transport;
	msg.msg_namelen	= peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	whdr.epoch	= htonl(peer->local->rxnet->epoch);
	whdr.cid	= 0;
	whdr.callNumber	= 0;
	whdr.seq	= 0;
	whdr.serial	= 0;
	whdr.type	= RXRPC_PACKET_TYPE_VERSION; /* Not client-initiated */
	whdr.flags	= RXRPC_LAST_PACKET;
	whdr.userStatus	= 0;
	whdr.securityIndex = 0;
	whdr._rsvd	= 0;
	whdr.serviceId	= 0;

	iov[0].iov_base	= &whdr;
	iov[0].iov_len	= माप(whdr);
	iov[1].iov_base	= (अक्षर *)rxrpc_keepalive_string;
	iov[1].iov_len	= माप(rxrpc_keepalive_string);

	len = iov[0].iov_len + iov[1].iov_len;

	_proto("Tx VERSION (keepalive)");

	ret = kernel_sendmsg(peer->local->socket, &msg, iov, 2, len);
	अगर (ret < 0)
		trace_rxrpc_tx_fail(peer->debug_id, 0, ret,
				    rxrpc_tx_poपूर्णांक_version_keepalive);
	अन्यथा
		trace_rxrpc_tx_packet(peer->debug_id, &whdr,
				      rxrpc_tx_poपूर्णांक_version_keepalive);

	peer->last_tx_at = kसमय_get_seconds();
	_leave("");
पूर्ण
