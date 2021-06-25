<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC recvmsg() implementation
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

/*
 * Post a call क्रम attention by the socket or kernel service.  Further
 * notअगरications are suppressed by putting recvmsg_link on a dummy queue.
 */
व्योम rxrpc_notअगरy_socket(काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_sock *rx;
	काष्ठा sock *sk;

	_enter("%d", call->debug_id);

	अगर (!list_empty(&call->recvmsg_link))
		वापस;

	rcu_पढ़ो_lock();

	rx = rcu_dereference(call->socket);
	sk = &rx->sk;
	अगर (rx && sk->sk_state < RXRPC_CLOSE) अणु
		अगर (call->notअगरy_rx) अणु
			spin_lock_bh(&call->notअगरy_lock);
			call->notअगरy_rx(sk, call, call->user_call_ID);
			spin_unlock_bh(&call->notअगरy_lock);
		पूर्ण अन्यथा अणु
			ग_लिखो_lock_bh(&rx->recvmsg_lock);
			अगर (list_empty(&call->recvmsg_link)) अणु
				rxrpc_get_call(call, rxrpc_call_got);
				list_add_tail(&call->recvmsg_link, &rx->recvmsg_q);
			पूर्ण
			ग_लिखो_unlock_bh(&rx->recvmsg_lock);

			अगर (!sock_flag(sk, SOCK_DEAD)) अणु
				_debug("call %ps", sk->sk_data_पढ़ोy);
				sk->sk_data_पढ़ोy(sk);
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	_leave("");
पूर्ण

/*
 * Transition a call to the complete state.
 */
bool __rxrpc_set_call_completion(काष्ठा rxrpc_call *call,
				 क्रमागत rxrpc_call_completion compl,
				 u32 पात_code,
				 पूर्णांक error)
अणु
	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		call->पात_code = पात_code;
		call->error = error;
		call->completion = compl;
		call->state = RXRPC_CALL_COMPLETE;
		trace_rxrpc_call_complete(call);
		wake_up(&call->रुकोq);
		rxrpc_notअगरy_socket(call);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool rxrpc_set_call_completion(काष्ठा rxrpc_call *call,
			       क्रमागत rxrpc_call_completion compl,
			       u32 पात_code,
			       पूर्णांक error)
अणु
	bool ret = false;

	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		ग_लिखो_lock_bh(&call->state_lock);
		ret = __rxrpc_set_call_completion(call, compl, पात_code, error);
		ग_लिखो_unlock_bh(&call->state_lock);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Record that a call successfully completed.
 */
bool __rxrpc_call_completed(काष्ठा rxrpc_call *call)
अणु
	वापस __rxrpc_set_call_completion(call, RXRPC_CALL_SUCCEEDED, 0, 0);
पूर्ण

bool rxrpc_call_completed(काष्ठा rxrpc_call *call)
अणु
	bool ret = false;

	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		ग_लिखो_lock_bh(&call->state_lock);
		ret = __rxrpc_call_completed(call);
		ग_लिखो_unlock_bh(&call->state_lock);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Record that a call is locally पातed.
 */
bool __rxrpc_पात_call(स्थिर अक्षर *why, काष्ठा rxrpc_call *call,
			rxrpc_seq_t seq, u32 पात_code, पूर्णांक error)
अणु
	trace_rxrpc_पात(call->debug_id, why, call->cid, call->call_id, seq,
			  पात_code, error);
	वापस __rxrpc_set_call_completion(call, RXRPC_CALL_LOCALLY_ABORTED,
					   पात_code, error);
पूर्ण

bool rxrpc_पात_call(स्थिर अक्षर *why, काष्ठा rxrpc_call *call,
		      rxrpc_seq_t seq, u32 पात_code, पूर्णांक error)
अणु
	bool ret;

	ग_लिखो_lock_bh(&call->state_lock);
	ret = __rxrpc_पात_call(why, call, seq, पात_code, error);
	ग_लिखो_unlock_bh(&call->state_lock);
	वापस ret;
पूर्ण

/*
 * Pass a call terminating message to userspace.
 */
अटल पूर्णांक rxrpc_recvmsg_term(काष्ठा rxrpc_call *call, काष्ठा msghdr *msg)
अणु
	u32 पंचांगp = 0;
	पूर्णांक ret;

	चयन (call->completion) अणु
	हाल RXRPC_CALL_SUCCEEDED:
		ret = 0;
		अगर (rxrpc_is_service_call(call))
			ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ACK, 0, &पंचांगp);
		अवरोध;
	हाल RXRPC_CALL_REMOTELY_ABORTED:
		पंचांगp = call->पात_code;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ABORT, 4, &पंचांगp);
		अवरोध;
	हाल RXRPC_CALL_LOCALLY_ABORTED:
		पंचांगp = call->पात_code;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_ABORT, 4, &पंचांगp);
		अवरोध;
	हाल RXRPC_CALL_NETWORK_ERROR:
		पंचांगp = -call->error;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_NET_ERROR, 4, &पंचांगp);
		अवरोध;
	हाल RXRPC_CALL_LOCAL_ERROR:
		पंचांगp = -call->error;
		ret = put_cmsg(msg, SOL_RXRPC, RXRPC_LOCAL_ERROR, 4, &पंचांगp);
		अवरोध;
	शेष:
		pr_err("Invalid terminal call state %u\n", call->state);
		BUG();
		अवरोध;
	पूर्ण

	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_terminal, call->rx_hard_ack,
			    call->rx_pkt_offset, call->rx_pkt_len, ret);
	वापस ret;
पूर्ण

/*
 * End the packet reception phase.
 */
अटल व्योम rxrpc_end_rx_phase(काष्ठा rxrpc_call *call, rxrpc_serial_t serial)
अणु
	_enter("%d,%s", call->debug_id, rxrpc_call_states[call->state]);

	trace_rxrpc_receive(call, rxrpc_receive_end, 0, call->rx_top);
	ASSERTCMP(call->rx_hard_ack, ==, call->rx_top);

	अगर (call->state == RXRPC_CALL_CLIENT_RECV_REPLY) अणु
		rxrpc_propose_ACK(call, RXRPC_ACK_IDLE, serial, false, true,
				  rxrpc_propose_ack_terminal_ack);
		//rxrpc_send_ack_packet(call, false, शून्य);
	पूर्ण

	ग_लिखो_lock_bh(&call->state_lock);

	चयन (call->state) अणु
	हाल RXRPC_CALL_CLIENT_RECV_REPLY:
		__rxrpc_call_completed(call);
		ग_लिखो_unlock_bh(&call->state_lock);
		अवरोध;

	हाल RXRPC_CALL_SERVER_RECV_REQUEST:
		call->tx_phase = true;
		call->state = RXRPC_CALL_SERVER_ACK_REQUEST;
		call->expect_req_by = jअगरfies + MAX_JIFFY_OFFSET;
		ग_लिखो_unlock_bh(&call->state_lock);
		rxrpc_propose_ACK(call, RXRPC_ACK_DELAY, serial, false, true,
				  rxrpc_propose_ack_processing_op);
		अवरोध;
	शेष:
		ग_लिखो_unlock_bh(&call->state_lock);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Discard a packet we've used up and advance the Rx winकरोw by one.
 */
अटल व्योम rxrpc_rotate_rx_winकरोw(काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा sk_buff *skb;
	rxrpc_serial_t serial;
	rxrpc_seq_t hard_ack, top;
	bool last = false;
	u8 subpacket;
	पूर्णांक ix;

	_enter("%d", call->debug_id);

	hard_ack = call->rx_hard_ack;
	top = smp_load_acquire(&call->rx_top);
	ASSERT(beक्रमe(hard_ack, top));

	hard_ack++;
	ix = hard_ack & RXRPC_RXTX_BUFF_MASK;
	skb = call->rxtx_buffer[ix];
	rxrpc_see_skb(skb, rxrpc_skb_rotated);
	sp = rxrpc_skb(skb);

	subpacket = call->rxtx_annotations[ix] & RXRPC_RX_ANNO_SUBPACKET;
	serial = sp->hdr.serial + subpacket;

	अगर (subpacket == sp->nr_subpackets - 1 &&
	    sp->rx_flags & RXRPC_SKB_INCL_LAST)
		last = true;

	call->rxtx_buffer[ix] = शून्य;
	call->rxtx_annotations[ix] = 0;
	/* Barrier against rxrpc_input_data(). */
	smp_store_release(&call->rx_hard_ack, hard_ack);

	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);

	trace_rxrpc_receive(call, rxrpc_receive_rotate, serial, hard_ack);
	अगर (last) अणु
		rxrpc_end_rx_phase(call, serial);
	पूर्ण अन्यथा अणु
		/* Check to see अगर there's an ACK that needs sending. */
		अगर (after_eq(hard_ack, call->ackr_consumed + 2) ||
		    after_eq(top, call->ackr_seen + 2) ||
		    (hard_ack == top && after(hard_ack, call->ackr_consumed)))
			rxrpc_propose_ACK(call, RXRPC_ACK_DELAY, serial,
					  true, true,
					  rxrpc_propose_ack_rotate_rx);
		अगर (call->ackr_reason && call->ackr_reason != RXRPC_ACK_DELAY)
			rxrpc_send_ack_packet(call, false, शून्य);
	पूर्ण
पूर्ण

/*
 * Decrypt and verअगरy a (sub)packet.  The packet's length may be changed due to
 * padding, but अगर this is the हाल, the packet length will be resident in the
 * socket buffer.  Note that we can't modअगरy the master skb info as the skb may
 * be the home to multiple subpackets.
 */
अटल पूर्णांक rxrpc_verअगरy_packet(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			       u8 annotation,
			       अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	rxrpc_seq_t seq = sp->hdr.seq;
	u16 cksum = sp->hdr.cksum;
	u8 subpacket = annotation & RXRPC_RX_ANNO_SUBPACKET;

	_enter("");

	/* For all but the head jumbo subpacket, the security checksum is in a
	 * jumbo header immediately prior to the data.
	 */
	अगर (subpacket > 0) अणु
		__be16 पंचांगp;
		अगर (skb_copy_bits(skb, offset - 2, &पंचांगp, 2) < 0)
			BUG();
		cksum = ntohs(पंचांगp);
		seq += subpacket;
	पूर्ण

	वापस call->security->verअगरy_packet(call, skb, offset, len,
					     seq, cksum);
पूर्ण

/*
 * Locate the data within a packet.  This is complicated by:
 *
 * (1) An skb may contain a jumbo packet - so we have to find the appropriate
 *     subpacket.
 *
 * (2) The (sub)packets may be encrypted and, अगर so, the encrypted portion
 *     contains an extra header which includes the true length of the data,
 *     excluding any encrypted padding.
 */
अटल पूर्णांक rxrpc_locate_data(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
			     u8 *_annotation,
			     अचिन्हित पूर्णांक *_offset, अचिन्हित पूर्णांक *_len,
			     bool *_last)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	अचिन्हित पूर्णांक offset = माप(काष्ठा rxrpc_wire_header);
	अचिन्हित पूर्णांक len;
	bool last = false;
	पूर्णांक ret;
	u8 annotation = *_annotation;
	u8 subpacket = annotation & RXRPC_RX_ANNO_SUBPACKET;

	/* Locate the subpacket */
	offset += subpacket * RXRPC_JUMBO_SUBPKTLEN;
	len = skb->len - offset;
	अगर (subpacket < sp->nr_subpackets - 1)
		len = RXRPC_JUMBO_DATALEN;
	अन्यथा अगर (sp->rx_flags & RXRPC_SKB_INCL_LAST)
		last = true;

	अगर (!(annotation & RXRPC_RX_ANNO_VERIFIED)) अणु
		ret = rxrpc_verअगरy_packet(call, skb, annotation, offset, len);
		अगर (ret < 0)
			वापस ret;
		*_annotation |= RXRPC_RX_ANNO_VERIFIED;
	पूर्ण

	*_offset = offset;
	*_len = len;
	*_last = last;
	call->security->locate_data(call, skb, _offset, _len);
	वापस 0;
पूर्ण

/*
 * Deliver messages to a call.  This keeps processing packets until the buffer
 * is filled and we find either more DATA (वापसs 0) or the end of the DATA
 * (वापसs 1).  If more packets are required, it वापसs -EAGAIN.
 */
अटल पूर्णांक rxrpc_recvmsg_data(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			      काष्ठा msghdr *msg, काष्ठा iov_iter *iter,
			      माप_प्रकार len, पूर्णांक flags, माप_प्रकार *_offset)
अणु
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा sk_buff *skb;
	rxrpc_serial_t serial;
	rxrpc_seq_t hard_ack, top, seq;
	माप_प्रकार reमुख्य;
	bool rx_pkt_last;
	अचिन्हित पूर्णांक rx_pkt_offset, rx_pkt_len;
	पूर्णांक ix, copy, ret = -EAGAIN, ret2;

	अगर (test_and_clear_bit(RXRPC_CALL_RX_UNDERRUN, &call->flags) &&
	    call->ackr_reason)
		rxrpc_send_ack_packet(call, false, शून्य);

	rx_pkt_offset = call->rx_pkt_offset;
	rx_pkt_len = call->rx_pkt_len;
	rx_pkt_last = call->rx_pkt_last;

	अगर (call->state >= RXRPC_CALL_SERVER_ACK_REQUEST) अणु
		seq = call->rx_hard_ack;
		ret = 1;
		जाओ करोne;
	पूर्ण

	/* Barriers against rxrpc_input_data(). */
	hard_ack = call->rx_hard_ack;
	seq = hard_ack + 1;

	जबतक (top = smp_load_acquire(&call->rx_top),
	       beक्रमe_eq(seq, top)
	       ) अणु
		ix = seq & RXRPC_RXTX_BUFF_MASK;
		skb = call->rxtx_buffer[ix];
		अगर (!skb) अणु
			trace_rxrpc_recvmsg(call, rxrpc_recvmsg_hole, seq,
					    rx_pkt_offset, rx_pkt_len, 0);
			अवरोध;
		पूर्ण
		smp_rmb();
		rxrpc_see_skb(skb, rxrpc_skb_seen);
		sp = rxrpc_skb(skb);

		अगर (!(flags & MSG_PEEK)) अणु
			serial = sp->hdr.serial;
			serial += call->rxtx_annotations[ix] & RXRPC_RX_ANNO_SUBPACKET;
			trace_rxrpc_receive(call, rxrpc_receive_front,
					    serial, seq);
		पूर्ण

		अगर (msg)
			sock_recv_बारtamp(msg, sock->sk, skb);

		अगर (rx_pkt_offset == 0) अणु
			ret2 = rxrpc_locate_data(call, skb,
						 &call->rxtx_annotations[ix],
						 &rx_pkt_offset, &rx_pkt_len,
						 &rx_pkt_last);
			trace_rxrpc_recvmsg(call, rxrpc_recvmsg_next, seq,
					    rx_pkt_offset, rx_pkt_len, ret2);
			अगर (ret2 < 0) अणु
				ret = ret2;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			trace_rxrpc_recvmsg(call, rxrpc_recvmsg_cont, seq,
					    rx_pkt_offset, rx_pkt_len, 0);
		पूर्ण

		/* We have to handle लघु, empty and used-up DATA packets. */
		reमुख्य = len - *_offset;
		copy = rx_pkt_len;
		अगर (copy > reमुख्य)
			copy = reमुख्य;
		अगर (copy > 0) अणु
			ret2 = skb_copy_datagram_iter(skb, rx_pkt_offset, iter,
						      copy);
			अगर (ret2 < 0) अणु
				ret = ret2;
				जाओ out;
			पूर्ण

			/* handle piecemeal consumption of data packets */
			rx_pkt_offset += copy;
			rx_pkt_len -= copy;
			*_offset += copy;
		पूर्ण

		अगर (rx_pkt_len > 0) अणु
			trace_rxrpc_recvmsg(call, rxrpc_recvmsg_full, seq,
					    rx_pkt_offset, rx_pkt_len, 0);
			ASSERTCMP(*_offset, ==, len);
			ret = 0;
			अवरोध;
		पूर्ण

		/* The whole packet has been transferred. */
		अगर (!(flags & MSG_PEEK))
			rxrpc_rotate_rx_winकरोw(call);
		rx_pkt_offset = 0;
		rx_pkt_len = 0;

		अगर (rx_pkt_last) अणु
			ASSERTCMP(seq, ==, READ_ONCE(call->rx_top));
			ret = 1;
			जाओ out;
		पूर्ण

		seq++;
	पूर्ण

out:
	अगर (!(flags & MSG_PEEK)) अणु
		call->rx_pkt_offset = rx_pkt_offset;
		call->rx_pkt_len = rx_pkt_len;
		call->rx_pkt_last = rx_pkt_last;
	पूर्ण
करोne:
	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_data_वापस, seq,
			    rx_pkt_offset, rx_pkt_len, ret);
	अगर (ret == -EAGAIN)
		set_bit(RXRPC_CALL_RX_UNDERRUN, &call->flags);
	वापस ret;
पूर्ण

/*
 * Receive a message from an RxRPC socket
 * - we need to be careful about two or more thपढ़ोs calling recvmsg
 *   simultaneously
 */
पूर्णांक rxrpc_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		  पूर्णांक flags)
अणु
	काष्ठा rxrpc_call *call;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	काष्ठा list_head *l;
	माप_प्रकार copied = 0;
	दीर्घ समयo;
	पूर्णांक ret;

	DEFINE_WAIT(रुको);

	trace_rxrpc_recvmsg(शून्य, rxrpc_recvmsg_enter, 0, 0, 0, 0);

	अगर (flags & (MSG_OOB | MSG_TRUNC))
		वापस -EOPNOTSUPP;

	समयo = sock_rcvसमयo(&rx->sk, flags & MSG_DONTWAIT);

try_again:
	lock_sock(&rx->sk);

	/* Return immediately अगर a client socket has no outstanding calls */
	अगर (RB_EMPTY_ROOT(&rx->calls) &&
	    list_empty(&rx->recvmsg_q) &&
	    rx->sk.sk_state != RXRPC_SERVER_LISTENING) अणु
		release_sock(&rx->sk);
		वापस -EAGAIN;
	पूर्ण

	अगर (list_empty(&rx->recvmsg_q)) अणु
		ret = -EWOULDBLOCK;
		अगर (समयo == 0) अणु
			call = शून्य;
			जाओ error_no_call;
		पूर्ण

		release_sock(&rx->sk);

		/* Wait क्रम something to happen */
		prepare_to_रुको_exclusive(sk_sleep(&rx->sk), &रुको,
					  TASK_INTERRUPTIBLE);
		ret = sock_error(&rx->sk);
		अगर (ret)
			जाओ रुको_error;

		अगर (list_empty(&rx->recvmsg_q)) अणु
			अगर (संकेत_pending(current))
				जाओ रुको_पूर्णांकerrupted;
			trace_rxrpc_recvmsg(शून्य, rxrpc_recvmsg_रुको,
					    0, 0, 0, 0);
			समयo = schedule_समयout(समयo);
		पूर्ण
		finish_रुको(sk_sleep(&rx->sk), &रुको);
		जाओ try_again;
	पूर्ण

	/* Find the next call and dequeue it अगर we're not just peeking.  If we
	 * करो dequeue it, that comes with a ref that we will need to release.
	 */
	ग_लिखो_lock_bh(&rx->recvmsg_lock);
	l = rx->recvmsg_q.next;
	call = list_entry(l, काष्ठा rxrpc_call, recvmsg_link);
	अगर (!(flags & MSG_PEEK))
		list_del_init(&call->recvmsg_link);
	अन्यथा
		rxrpc_get_call(call, rxrpc_call_got);
	ग_लिखो_unlock_bh(&rx->recvmsg_lock);

	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_dequeue, 0, 0, 0, 0);

	/* We're going to drop the socket lock, so we need to lock the call
	 * against पूर्णांकerference by sendmsg.
	 */
	अगर (!mutex_trylock(&call->user_mutex)) अणु
		ret = -EWOULDBLOCK;
		अगर (flags & MSG_DONTWAIT)
			जाओ error_requeue_call;
		ret = -ERESTARTSYS;
		अगर (mutex_lock_पूर्णांकerruptible(&call->user_mutex) < 0)
			जाओ error_requeue_call;
	पूर्ण

	release_sock(&rx->sk);

	अगर (test_bit(RXRPC_CALL_RELEASED, &call->flags))
		BUG();

	अगर (test_bit(RXRPC_CALL_HAS_USERID, &call->flags)) अणु
		अगर (flags & MSG_CMSG_COMPAT) अणु
			अचिन्हित पूर्णांक id32 = call->user_call_ID;

			ret = put_cmsg(msg, SOL_RXRPC, RXRPC_USER_CALL_ID,
				       माप(अचिन्हित पूर्णांक), &id32);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ idl = call->user_call_ID;

			ret = put_cmsg(msg, SOL_RXRPC, RXRPC_USER_CALL_ID,
				       माप(अचिन्हित दीर्घ), &idl);
		पूर्ण
		अगर (ret < 0)
			जाओ error_unlock_call;
	पूर्ण

	अगर (msg->msg_name && call->peer) अणु
		काष्ठा sockaddr_rxrpc *srx = msg->msg_name;
		माप_प्रकार len = माप(call->peer->srx);

		स_नकल(msg->msg_name, &call->peer->srx, len);
		srx->srx_service = call->service_id;
		msg->msg_namelen = len;
	पूर्ण

	चयन (READ_ONCE(call->state)) अणु
	हाल RXRPC_CALL_CLIENT_RECV_REPLY:
	हाल RXRPC_CALL_SERVER_RECV_REQUEST:
	हाल RXRPC_CALL_SERVER_ACK_REQUEST:
		ret = rxrpc_recvmsg_data(sock, call, msg, &msg->msg_iter, len,
					 flags, &copied);
		अगर (ret == -EAGAIN)
			ret = 0;

		अगर (after(call->rx_top, call->rx_hard_ack) &&
		    call->rxtx_buffer[(call->rx_hard_ack + 1) & RXRPC_RXTX_BUFF_MASK])
			rxrpc_notअगरy_socket(call);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ error_unlock_call;

	अगर (call->state == RXRPC_CALL_COMPLETE) अणु
		ret = rxrpc_recvmsg_term(call, msg);
		अगर (ret < 0)
			जाओ error_unlock_call;
		अगर (!(flags & MSG_PEEK))
			rxrpc_release_call(rx, call);
		msg->msg_flags |= MSG_EOR;
		ret = 1;
	पूर्ण

	अगर (ret == 0)
		msg->msg_flags |= MSG_MORE;
	अन्यथा
		msg->msg_flags &= ~MSG_MORE;
	ret = copied;

error_unlock_call:
	mutex_unlock(&call->user_mutex);
	rxrpc_put_call(call, rxrpc_call_put);
	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_वापस, 0, 0, 0, ret);
	वापस ret;

error_requeue_call:
	अगर (!(flags & MSG_PEEK)) अणु
		ग_लिखो_lock_bh(&rx->recvmsg_lock);
		list_add(&call->recvmsg_link, &rx->recvmsg_q);
		ग_लिखो_unlock_bh(&rx->recvmsg_lock);
		trace_rxrpc_recvmsg(call, rxrpc_recvmsg_requeue, 0, 0, 0, 0);
	पूर्ण अन्यथा अणु
		rxrpc_put_call(call, rxrpc_call_put);
	पूर्ण
error_no_call:
	release_sock(&rx->sk);
error_trace:
	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_वापस, 0, 0, 0, ret);
	वापस ret;

रुको_पूर्णांकerrupted:
	ret = sock_पूर्णांकr_त्रुटि_सं(समयo);
रुको_error:
	finish_रुको(sk_sleep(&rx->sk), &रुको);
	call = शून्य;
	जाओ error_trace;
पूर्ण

/**
 * rxrpc_kernel_recv_data - Allow a kernel service to receive data/info
 * @sock: The socket that the call exists on
 * @call: The call to send data through
 * @iter: The buffer to receive पूर्णांकo
 * @_len: The amount of data we want to receive (decreased on वापस)
 * @want_more: True अगर more data is expected to be पढ़ो
 * @_पात: Where the पात code is stored अगर -ECONNABORTED is वापसed
 * @_service: Where to store the actual service ID (may be upgraded)
 *
 * Allow a kernel service to receive data and pick up inक्रमmation about the
 * state of a call.  Returns 0 अगर got what was asked क्रम and there's more
 * available, 1 अगर we got what was asked क्रम and we're at the end of the data
 * and -EAGAIN अगर we need more data.
 *
 * Note that we may वापस -EAGAIN to drain empty packets at the end of the
 * data, even अगर we've alपढ़ोy copied over the requested data.
 *
 * *_पात should also be initialised to 0.
 */
पूर्णांक rxrpc_kernel_recv_data(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			   काष्ठा iov_iter *iter, माप_प्रकार *_len,
			   bool want_more, u32 *_पात, u16 *_service)
अणु
	माप_प्रकार offset = 0;
	पूर्णांक ret;

	_enter("{%d,%s},%zu,%d",
	       call->debug_id, rxrpc_call_states[call->state],
	       *_len, want_more);

	ASSERTCMP(call->state, !=, RXRPC_CALL_SERVER_SECURING);

	mutex_lock(&call->user_mutex);

	चयन (READ_ONCE(call->state)) अणु
	हाल RXRPC_CALL_CLIENT_RECV_REPLY:
	हाल RXRPC_CALL_SERVER_RECV_REQUEST:
	हाल RXRPC_CALL_SERVER_ACK_REQUEST:
		ret = rxrpc_recvmsg_data(sock, call, शून्य, iter,
					 *_len, 0, &offset);
		*_len -= offset;
		अगर (ret < 0)
			जाओ out;

		/* We can only reach here with a partially full buffer अगर we
		 * have reached the end of the data.  We must otherwise have a
		 * full buffer or have been given -EAGAIN.
		 */
		अगर (ret == 1) अणु
			अगर (iov_iter_count(iter) > 0)
				जाओ लघु_data;
			अगर (!want_more)
				जाओ पढ़ो_phase_complete;
			ret = 0;
			जाओ out;
		पूर्ण

		अगर (!want_more)
			जाओ excess_data;
		जाओ out;

	हाल RXRPC_CALL_COMPLETE:
		जाओ call_complete;

	शेष:
		ret = -EINPROGRESS;
		जाओ out;
	पूर्ण

पढ़ो_phase_complete:
	ret = 1;
out:
	चयन (call->ackr_reason) अणु
	हाल RXRPC_ACK_IDLE:
		अवरोध;
	हाल RXRPC_ACK_DELAY:
		अगर (ret != -EAGAIN)
			अवरोध;
		fallthrough;
	शेष:
		rxrpc_send_ack_packet(call, false, शून्य);
	पूर्ण

	अगर (_service)
		*_service = call->service_id;
	mutex_unlock(&call->user_mutex);
	_leave(" = %d [%zu,%d]", ret, iov_iter_count(iter), *_पात);
	वापस ret;

लघु_data:
	trace_rxrpc_rx_eproto(call, 0, tracepoपूर्णांक_string("short_data"));
	ret = -EBADMSG;
	जाओ out;
excess_data:
	trace_rxrpc_rx_eproto(call, 0, tracepoपूर्णांक_string("excess_data"));
	ret = -EMSGSIZE;
	जाओ out;
call_complete:
	*_पात = call->पात_code;
	ret = call->error;
	अगर (call->completion == RXRPC_CALL_SUCCEEDED) अणु
		ret = 1;
		अगर (iov_iter_count(iter) > 0)
			ret = -ECONNRESET;
	पूर्ण
	जाओ out;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_recv_data);

/**
 * rxrpc_kernel_get_reply_समय - Get बारtamp on first reply packet
 * @sock: The socket that the call exists on
 * @call: The call to query
 * @_ts: Where to put the बारtamp
 *
 * Retrieve the बारtamp from the first DATA packet of the reply अगर it is
 * in the ring.  Returns true अगर successful, false अगर not.
 */
bool rxrpc_kernel_get_reply_समय(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
				 kसमय_प्रकार *_ts)
अणु
	काष्ठा sk_buff *skb;
	rxrpc_seq_t hard_ack, top, seq;
	bool success = false;

	mutex_lock(&call->user_mutex);

	अगर (READ_ONCE(call->state) != RXRPC_CALL_CLIENT_RECV_REPLY)
		जाओ out;

	hard_ack = call->rx_hard_ack;
	अगर (hard_ack != 0)
		जाओ out;

	seq = hard_ack + 1;
	top = smp_load_acquire(&call->rx_top);
	अगर (after(seq, top))
		जाओ out;

	skb = call->rxtx_buffer[seq & RXRPC_RXTX_BUFF_MASK];
	अगर (!skb)
		जाओ out;

	*_ts = skb_get_kसमय(skb);
	success = true;

out:
	mutex_unlock(&call->user_mutex);
	वापस success;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_get_reply_समय);
