<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* connection-level event handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/errqueue.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <net/ip.h>
#समावेश "ar-internal.h"

/*
 * Retransmit terminal ACK or ABORT of the previous call.
 */
अटल व्योम rxrpc_conn_retransmit_call(काष्ठा rxrpc_connection *conn,
				       काष्ठा sk_buff *skb,
				       अचिन्हित पूर्णांक channel)
अणु
	काष्ठा rxrpc_skb_priv *sp = skb ? rxrpc_skb(skb) : शून्य;
	काष्ठा rxrpc_channel *chan;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[3];
	काष्ठा अणु
		काष्ठा rxrpc_wire_header whdr;
		जोड़ अणु
			__be32 पात_code;
			काष्ठा rxrpc_ackpacket ack;
		पूर्ण;
	पूर्ण __attribute__((packed)) pkt;
	काष्ठा rxrpc_ackinfo ack_info;
	माप_प्रकार len;
	पूर्णांक ret, ioc;
	u32 serial, mtu, call_id, padding;

	_enter("%d", conn->debug_id);

	chan = &conn->channels[channel];

	/* If the last call got moved on whilst we were रुकोing to run, just
	 * ignore this packet.
	 */
	call_id = READ_ONCE(chan->last_call);
	/* Sync with __rxrpc_disconnect_call() */
	smp_rmb();
	अगर (skb && call_id != sp->hdr.callNumber)
		वापस;

	msg.msg_name	= &conn->params.peer->srx.transport;
	msg.msg_namelen	= conn->params.peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	iov[0].iov_base	= &pkt;
	iov[0].iov_len	= माप(pkt.whdr);
	iov[1].iov_base	= &padding;
	iov[1].iov_len	= 3;
	iov[2].iov_base	= &ack_info;
	iov[2].iov_len	= माप(ack_info);

	pkt.whdr.epoch		= htonl(conn->proto.epoch);
	pkt.whdr.cid		= htonl(conn->proto.cid | channel);
	pkt.whdr.callNumber	= htonl(call_id);
	pkt.whdr.seq		= 0;
	pkt.whdr.type		= chan->last_type;
	pkt.whdr.flags		= conn->out_clientflag;
	pkt.whdr.userStatus	= 0;
	pkt.whdr.securityIndex	= conn->security_ix;
	pkt.whdr._rsvd		= 0;
	pkt.whdr.serviceId	= htons(conn->service_id);

	len = माप(pkt.whdr);
	चयन (chan->last_type) अणु
	हाल RXRPC_PACKET_TYPE_ABORT:
		pkt.पात_code	= htonl(chan->last_पात);
		iov[0].iov_len += माप(pkt.पात_code);
		len += माप(pkt.पात_code);
		ioc = 1;
		अवरोध;

	हाल RXRPC_PACKET_TYPE_ACK:
		mtu = conn->params.peer->अगर_mtu;
		mtu -= conn->params.peer->hdrsize;
		pkt.ack.bufferSpace	= 0;
		pkt.ack.maxSkew		= htons(skb ? skb->priority : 0);
		pkt.ack.firstPacket	= htonl(chan->last_seq + 1);
		pkt.ack.previousPacket	= htonl(chan->last_seq);
		pkt.ack.serial		= htonl(skb ? sp->hdr.serial : 0);
		pkt.ack.reason		= skb ? RXRPC_ACK_DUPLICATE : RXRPC_ACK_IDLE;
		pkt.ack.nAcks		= 0;
		ack_info.rxMTU		= htonl(rxrpc_rx_mtu);
		ack_info.maxMTU		= htonl(mtu);
		ack_info.rwind		= htonl(rxrpc_rx_winकरोw_size);
		ack_info.jumbo_max	= htonl(rxrpc_rx_jumbo_max);
		pkt.whdr.flags		|= RXRPC_SLOW_START_OK;
		padding			= 0;
		iov[0].iov_len += माप(pkt.ack);
		len += माप(pkt.ack) + 3 + माप(ack_info);
		ioc = 3;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	/* Resync with __rxrpc_disconnect_call() and check that the last call
	 * didn't get advanced whilst we were filling out the packets.
	 */
	smp_rmb();
	अगर (READ_ONCE(chan->last_call) != call_id)
		वापस;

	serial = atomic_inc_वापस(&conn->serial);
	pkt.whdr.serial = htonl(serial);

	चयन (chan->last_type) अणु
	हाल RXRPC_PACKET_TYPE_ABORT:
		_proto("Tx ABORT %%%u { %d } [re]", serial, conn->पात_code);
		अवरोध;
	हाल RXRPC_PACKET_TYPE_ACK:
		trace_rxrpc_tx_ack(chan->call_debug_id, serial,
				   ntohl(pkt.ack.firstPacket),
				   ntohl(pkt.ack.serial),
				   pkt.ack.reason, 0);
		_proto("Tx ACK %%%u [re]", serial);
		अवरोध;
	पूर्ण

	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, ioc, len);
	conn->params.peer->last_tx_at = kसमय_get_seconds();
	अगर (ret < 0)
		trace_rxrpc_tx_fail(chan->call_debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_call_final_resend);
	अन्यथा
		trace_rxrpc_tx_packet(chan->call_debug_id, &pkt.whdr,
				      rxrpc_tx_poपूर्णांक_call_final_resend);

	_leave("");
पूर्ण

/*
 * pass a connection-level पात onto all calls on that connection
 */
अटल व्योम rxrpc_पात_calls(काष्ठा rxrpc_connection *conn,
			      क्रमागत rxrpc_call_completion compl,
			      rxrpc_serial_t serial)
अणु
	काष्ठा rxrpc_call *call;
	पूर्णांक i;

	_enter("{%d},%x", conn->debug_id, conn->पात_code);

	spin_lock(&conn->bundle->channel_lock);

	क्रम (i = 0; i < RXRPC_MAXCALLS; i++) अणु
		call = rcu_dereference_रक्षित(
			conn->channels[i].call,
			lockdep_is_held(&conn->bundle->channel_lock));
		अगर (call) अणु
			अगर (compl == RXRPC_CALL_LOCALLY_ABORTED)
				trace_rxrpc_पात(call->debug_id,
						  "CON", call->cid,
						  call->call_id, 0,
						  conn->पात_code,
						  conn->error);
			अन्यथा
				trace_rxrpc_rx_पात(call, serial,
						     conn->पात_code);
			rxrpc_set_call_completion(call, compl,
						  conn->पात_code,
						  conn->error);
		पूर्ण
	पूर्ण

	spin_unlock(&conn->bundle->channel_lock);
	_leave("");
पूर्ण

/*
 * generate a connection-level पात
 */
अटल पूर्णांक rxrpc_पात_connection(काष्ठा rxrpc_connection *conn,
				  पूर्णांक error, u32 पात_code)
अणु
	काष्ठा rxrpc_wire_header whdr;
	काष्ठा msghdr msg;
	काष्ठा kvec iov[2];
	__be32 word;
	माप_प्रकार len;
	u32 serial;
	पूर्णांक ret;

	_enter("%d,,%u,%u", conn->debug_id, error, पात_code);

	/* generate a connection-level पात */
	spin_lock_bh(&conn->state_lock);
	अगर (conn->state >= RXRPC_CONN_REMOTELY_ABORTED) अणु
		spin_unlock_bh(&conn->state_lock);
		_leave(" = 0 [already dead]");
		वापस 0;
	पूर्ण

	conn->error = error;
	conn->पात_code = पात_code;
	conn->state = RXRPC_CONN_LOCALLY_ABORTED;
	set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
	spin_unlock_bh(&conn->state_lock);

	msg.msg_name	= &conn->params.peer->srx.transport;
	msg.msg_namelen	= conn->params.peer->srx.transport_len;
	msg.msg_control	= शून्य;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	whdr.epoch	= htonl(conn->proto.epoch);
	whdr.cid	= htonl(conn->proto.cid);
	whdr.callNumber	= 0;
	whdr.seq	= 0;
	whdr.type	= RXRPC_PACKET_TYPE_ABORT;
	whdr.flags	= conn->out_clientflag;
	whdr.userStatus	= 0;
	whdr.securityIndex = conn->security_ix;
	whdr._rsvd	= 0;
	whdr.serviceId	= htons(conn->service_id);

	word		= htonl(conn->पात_code);

	iov[0].iov_base	= &whdr;
	iov[0].iov_len	= माप(whdr);
	iov[1].iov_base	= &word;
	iov[1].iov_len	= माप(word);

	len = iov[0].iov_len + iov[1].iov_len;

	serial = atomic_inc_वापस(&conn->serial);
	rxrpc_पात_calls(conn, RXRPC_CALL_LOCALLY_ABORTED, serial);
	whdr.serial = htonl(serial);
	_proto("Tx CONN ABORT %%%u { %d }", serial, conn->पात_code);

	ret = kernel_sendmsg(conn->params.local->socket, &msg, iov, 2, len);
	अगर (ret < 0) अणु
		trace_rxrpc_tx_fail(conn->debug_id, serial, ret,
				    rxrpc_tx_poपूर्णांक_conn_पात);
		_debug("sendmsg failed: %d", ret);
		वापस -EAGAIN;
	पूर्ण

	trace_rxrpc_tx_packet(conn->debug_id, &whdr, rxrpc_tx_poपूर्णांक_conn_पात);

	conn->params.peer->last_tx_at = kसमय_get_seconds();

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * mark a call as being on a now-secured channel
 * - must be called with BH's disabled.
 */
अटल व्योम rxrpc_call_is_secure(काष्ठा rxrpc_call *call)
अणु
	_enter("%p", call);
	अगर (call) अणु
		ग_लिखो_lock_bh(&call->state_lock);
		अगर (call->state == RXRPC_CALL_SERVER_SECURING) अणु
			call->state = RXRPC_CALL_SERVER_RECV_REQUEST;
			rxrpc_notअगरy_socket(call);
		पूर्ण
		ग_लिखो_unlock_bh(&call->state_lock);
	पूर्ण
पूर्ण

/*
 * connection-level Rx packet processor
 */
अटल पूर्णांक rxrpc_process_event(काष्ठा rxrpc_connection *conn,
			       काष्ठा sk_buff *skb,
			       u32 *_पात_code)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	__be32 wपंचांगp;
	u32 पात_code;
	पूर्णांक loop, ret;

	अगर (conn->state >= RXRPC_CONN_REMOTELY_ABORTED) अणु
		_leave(" = -ECONNABORTED [%u]", conn->state);
		वापस -ECONNABORTED;
	पूर्ण

	_enter("{%d},{%u,%%%u},", conn->debug_id, sp->hdr.type, sp->hdr.serial);

	चयन (sp->hdr.type) अणु
	हाल RXRPC_PACKET_TYPE_DATA:
	हाल RXRPC_PACKET_TYPE_ACK:
		rxrpc_conn_retransmit_call(conn, skb,
					   sp->hdr.cid & RXRPC_CHANNELMASK);
		वापस 0;

	हाल RXRPC_PACKET_TYPE_BUSY:
		/* Just ignore BUSY packets क्रम now. */
		वापस 0;

	हाल RXRPC_PACKET_TYPE_ABORT:
		अगर (skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header),
				  &wपंचांगp, माप(wपंचांगp)) < 0) अणु
			trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial,
					      tracepoपूर्णांक_string("bad_abort"));
			वापस -EPROTO;
		पूर्ण
		पात_code = ntohl(wपंचांगp);
		_proto("Rx ABORT %%%u { ac=%d }", sp->hdr.serial, पात_code);

		conn->error = -ECONNABORTED;
		conn->पात_code = पात_code;
		conn->state = RXRPC_CONN_REMOTELY_ABORTED;
		set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
		rxrpc_पात_calls(conn, RXRPC_CALL_REMOTELY_ABORTED, sp->hdr.serial);
		वापस -ECONNABORTED;

	हाल RXRPC_PACKET_TYPE_CHALLENGE:
		वापस conn->security->respond_to_challenge(conn, skb,
							    _पात_code);

	हाल RXRPC_PACKET_TYPE_RESPONSE:
		ret = conn->security->verअगरy_response(conn, skb, _पात_code);
		अगर (ret < 0)
			वापस ret;

		ret = conn->security->init_connection_security(
			conn, conn->params.key->payload.data[0]);
		अगर (ret < 0)
			वापस ret;

		spin_lock(&conn->bundle->channel_lock);
		spin_lock_bh(&conn->state_lock);

		अगर (conn->state == RXRPC_CONN_SERVICE_CHALLENGING) अणु
			conn->state = RXRPC_CONN_SERVICE;
			spin_unlock_bh(&conn->state_lock);
			क्रम (loop = 0; loop < RXRPC_MAXCALLS; loop++)
				rxrpc_call_is_secure(
					rcu_dereference_रक्षित(
						conn->channels[loop].call,
						lockdep_is_held(&conn->bundle->channel_lock)));
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&conn->state_lock);
		पूर्ण

		spin_unlock(&conn->bundle->channel_lock);
		वापस 0;

	शेष:
		trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial,
				      tracepoपूर्णांक_string("bad_conn_pkt"));
		वापस -EPROTO;
	पूर्ण
पूर्ण

/*
 * set up security and issue a challenge
 */
अटल व्योम rxrpc_secure_connection(काष्ठा rxrpc_connection *conn)
अणु
	u32 पात_code;
	पूर्णांक ret;

	_enter("{%d}", conn->debug_id);

	ASSERT(conn->security_ix != 0);

	अगर (conn->security->issue_challenge(conn) < 0) अणु
		पात_code = RX_CALL_DEAD;
		ret = -ENOMEM;
		जाओ पात;
	पूर्ण

	_leave("");
	वापस;

पात:
	_debug("abort %d, %d", ret, पात_code);
	rxrpc_पात_connection(conn, ret, पात_code);
	_leave(" [aborted]");
पूर्ण

/*
 * Process delayed final ACKs that we haven't subsumed पूर्णांकo a subsequent call.
 */
व्योम rxrpc_process_delayed_final_acks(काष्ठा rxrpc_connection *conn, bool क्रमce)
अणु
	अचिन्हित दीर्घ j = jअगरfies, next_j;
	अचिन्हित पूर्णांक channel;
	bool set;

again:
	next_j = j + दीर्घ_उच्च;
	set = false;
	क्रम (channel = 0; channel < RXRPC_MAXCALLS; channel++) अणु
		काष्ठा rxrpc_channel *chan = &conn->channels[channel];
		अचिन्हित दीर्घ ack_at;

		अगर (!test_bit(RXRPC_CONN_FINAL_ACK_0 + channel, &conn->flags))
			जारी;

		smp_rmb(); /* vs rxrpc_disconnect_client_call */
		ack_at = READ_ONCE(chan->final_ack_at);

		अगर (समय_beक्रमe(j, ack_at) && !क्रमce) अणु
			अगर (समय_beक्रमe(ack_at, next_j)) अणु
				next_j = ack_at;
				set = true;
			पूर्ण
			जारी;
		पूर्ण

		अगर (test_and_clear_bit(RXRPC_CONN_FINAL_ACK_0 + channel,
				       &conn->flags))
			rxrpc_conn_retransmit_call(conn, शून्य, channel);
	पूर्ण

	j = jअगरfies;
	अगर (समय_beक्रमe_eq(next_j, j))
		जाओ again;
	अगर (set)
		rxrpc_reduce_conn_समयr(conn, next_j);
पूर्ण

/*
 * connection-level event processor
 */
अटल व्योम rxrpc_करो_process_connection(काष्ठा rxrpc_connection *conn)
अणु
	काष्ठा sk_buff *skb;
	u32 पात_code = RX_PROTOCOL_ERROR;
	पूर्णांक ret;

	अगर (test_and_clear_bit(RXRPC_CONN_EV_CHALLENGE, &conn->events))
		rxrpc_secure_connection(conn);

	/* Process delayed ACKs whose समय has come. */
	अगर (conn->flags & RXRPC_CONN_FINAL_ACK_MASK)
		rxrpc_process_delayed_final_acks(conn, false);

	/* go through the conn-level event packets, releasing the ref on this
	 * connection that each one has when we've finished with it */
	जबतक ((skb = skb_dequeue(&conn->rx_queue))) अणु
		rxrpc_see_skb(skb, rxrpc_skb_seen);
		ret = rxrpc_process_event(conn, skb, &पात_code);
		चयन (ret) अणु
		हाल -EPROTO:
		हाल -EKEYEXPIRED:
		हाल -EKEYREJECTED:
			जाओ protocol_error;
		हाल -ENOMEM:
		हाल -EAGAIN:
			जाओ requeue_and_leave;
		हाल -ECONNABORTED:
		शेष:
			rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस;

requeue_and_leave:
	skb_queue_head(&conn->rx_queue, skb);
	वापस;

protocol_error:
	अगर (rxrpc_पात_connection(conn, ret, पात_code) < 0)
		जाओ requeue_and_leave;
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	वापस;
पूर्ण

व्योम rxrpc_process_connection(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_connection *conn =
		container_of(work, काष्ठा rxrpc_connection, processor);

	rxrpc_see_connection(conn);

	अगर (__rxrpc_use_local(conn->params.local)) अणु
		rxrpc_करो_process_connection(conn);
		rxrpc_unuse_local(conn->params.local);
	पूर्ण

	rxrpc_put_connection(conn);
	_leave("");
	वापस;
पूर्ण
