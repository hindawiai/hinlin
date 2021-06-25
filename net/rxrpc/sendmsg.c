<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AF_RXRPC sendmsg() implementation.
 *
 * Copyright (C) 2007, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/net.h>
#समावेश <linux/gfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

/*
 * Return true अगर there's sufficient Tx queue space.
 */
अटल bool rxrpc_check_tx_space(काष्ठा rxrpc_call *call, rxrpc_seq_t *_tx_win)
अणु
	अचिन्हित पूर्णांक win_size =
		min_t(अचिन्हित पूर्णांक, call->tx_winsize,
		      call->cong_cwnd + call->cong_extra);
	rxrpc_seq_t tx_win = READ_ONCE(call->tx_hard_ack);

	अगर (_tx_win)
		*_tx_win = tx_win;
	वापस call->tx_top - tx_win < win_size;
पूर्ण

/*
 * Wait क्रम space to appear in the Tx queue or a संकेत to occur.
 */
अटल पूर्णांक rxrpc_रुको_क्रम_tx_winकरोw_पूर्णांकr(काष्ठा rxrpc_sock *rx,
					 काष्ठा rxrpc_call *call,
					 दीर्घ *समयo)
अणु
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (rxrpc_check_tx_space(call, शून्य))
			वापस 0;

		अगर (call->state >= RXRPC_CALL_COMPLETE)
			वापस call->error;

		अगर (संकेत_pending(current))
			वापस sock_पूर्णांकr_त्रुटि_सं(*समयo);

		trace_rxrpc_transmit(call, rxrpc_transmit_रुको);
		mutex_unlock(&call->user_mutex);
		*समयo = schedule_समयout(*समयo);
		अगर (mutex_lock_पूर्णांकerruptible(&call->user_mutex) < 0)
			वापस sock_पूर्णांकr_त्रुटि_सं(*समयo);
	पूर्ण
पूर्ण

/*
 * Wait क्रम space to appear in the Tx queue unपूर्णांकerruptibly, but with
 * a समयout of 2*RTT अगर no progress was made and a संकेत occurred.
 */
अटल पूर्णांक rxrpc_रुको_क्रम_tx_winकरोw_रुकोall(काष्ठा rxrpc_sock *rx,
					    काष्ठा rxrpc_call *call)
अणु
	rxrpc_seq_t tx_start, tx_win;
	चिन्हित दीर्घ rtt, समयout;

	rtt = READ_ONCE(call->peer->srtt_us) >> 3;
	rtt = usecs_to_jअगरfies(rtt) * 2;
	अगर (rtt < 2)
		rtt = 2;

	समयout = rtt;
	tx_start = READ_ONCE(call->tx_hard_ack);

	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);

		tx_win = READ_ONCE(call->tx_hard_ack);
		अगर (rxrpc_check_tx_space(call, &tx_win))
			वापस 0;

		अगर (call->state >= RXRPC_CALL_COMPLETE)
			वापस call->error;

		अगर (समयout == 0 &&
		    tx_win == tx_start && संकेत_pending(current))
			वापस -EINTR;

		अगर (tx_win != tx_start) अणु
			समयout = rtt;
			tx_start = tx_win;
		पूर्ण

		trace_rxrpc_transmit(call, rxrpc_transmit_रुको);
		समयout = schedule_समयout(समयout);
	पूर्ण
पूर्ण

/*
 * Wait क्रम space to appear in the Tx queue unपूर्णांकerruptibly.
 */
अटल पूर्णांक rxrpc_रुको_क्रम_tx_winकरोw_nonपूर्णांकr(काष्ठा rxrpc_sock *rx,
					    काष्ठा rxrpc_call *call,
					    दीर्घ *समयo)
अणु
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (rxrpc_check_tx_space(call, शून्य))
			वापस 0;

		अगर (call->state >= RXRPC_CALL_COMPLETE)
			वापस call->error;

		trace_rxrpc_transmit(call, rxrpc_transmit_रुको);
		*समयo = schedule_समयout(*समयo);
	पूर्ण
पूर्ण

/*
 * रुको क्रम space to appear in the transmit/ACK winकरोw
 * - caller holds the socket locked
 */
अटल पूर्णांक rxrpc_रुको_क्रम_tx_winकरोw(काष्ठा rxrpc_sock *rx,
				    काष्ठा rxrpc_call *call,
				    दीर्घ *समयo,
				    bool रुकोall)
अणु
	DECLARE_WAITQUEUE(myself, current);
	पूर्णांक ret;

	_enter(",{%u,%u,%u}",
	       call->tx_hard_ack, call->tx_top, call->tx_winsize);

	add_रुको_queue(&call->रुकोq, &myself);

	चयन (call->पूर्णांकerruptibility) अणु
	हाल RXRPC_INTERRUPTIBLE:
		अगर (रुकोall)
			ret = rxrpc_रुको_क्रम_tx_winकरोw_रुकोall(rx, call);
		अन्यथा
			ret = rxrpc_रुको_क्रम_tx_winकरोw_पूर्णांकr(rx, call, समयo);
		अवरोध;
	हाल RXRPC_PREINTERRUPTIBLE:
	हाल RXRPC_UNINTERRUPTIBLE:
	शेष:
		ret = rxrpc_रुको_क्रम_tx_winकरोw_nonपूर्णांकr(rx, call, समयo);
		अवरोध;
	पूर्ण

	हटाओ_रुको_queue(&call->रुकोq, &myself);
	set_current_state(TASK_RUNNING);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Schedule an instant Tx resend.
 */
अटल अंतरभूत व्योम rxrpc_instant_resend(काष्ठा rxrpc_call *call, पूर्णांक ix)
अणु
	spin_lock_bh(&call->lock);

	अगर (call->state < RXRPC_CALL_COMPLETE) अणु
		call->rxtx_annotations[ix] =
			(call->rxtx_annotations[ix] & RXRPC_TX_ANNO_LAST) |
			RXRPC_TX_ANNO_RETRANS;
		अगर (!test_and_set_bit(RXRPC_CALL_EV_RESEND, &call->events))
			rxrpc_queue_call(call);
	पूर्ण

	spin_unlock_bh(&call->lock);
पूर्ण

/*
 * Notअगरy the owner of the call that the transmit phase is ended and the last
 * packet has been queued.
 */
अटल व्योम rxrpc_notअगरy_end_tx(काष्ठा rxrpc_sock *rx, काष्ठा rxrpc_call *call,
				rxrpc_notअगरy_end_tx_t notअगरy_end_tx)
अणु
	अगर (notअगरy_end_tx)
		notअगरy_end_tx(&rx->sk, call, call->user_call_ID);
पूर्ण

/*
 * Queue a DATA packet क्रम transmission, set the resend समयout and send
 * the packet immediately.  Returns the error from rxrpc_send_data_packet()
 * in हाल the caller wants to करो something with it.
 */
अटल पूर्णांक rxrpc_queue_packet(काष्ठा rxrpc_sock *rx, काष्ठा rxrpc_call *call,
			      काष्ठा sk_buff *skb, bool last,
			      rxrpc_notअगरy_end_tx_t notअगरy_end_tx)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	अचिन्हित दीर्घ now;
	rxrpc_seq_t seq = sp->hdr.seq;
	पूर्णांक ret, ix;
	u8 annotation = RXRPC_TX_ANNO_UNACK;

	_net("queue skb %p [%d]", skb, seq);

	ASSERTCMP(seq, ==, call->tx_top + 1);

	अगर (last)
		annotation |= RXRPC_TX_ANNO_LAST;

	/* We have to set the बारtamp beक्रमe queueing as the retransmit
	 * algorithm can see the packet as soon as we queue it.
	 */
	skb->tstamp = kसमय_get_real();

	ix = seq & RXRPC_RXTX_BUFF_MASK;
	rxrpc_get_skb(skb, rxrpc_skb_got);
	call->rxtx_annotations[ix] = annotation;
	smp_wmb();
	call->rxtx_buffer[ix] = skb;
	call->tx_top = seq;
	अगर (last)
		trace_rxrpc_transmit(call, rxrpc_transmit_queue_last);
	अन्यथा
		trace_rxrpc_transmit(call, rxrpc_transmit_queue);

	अगर (last || call->state == RXRPC_CALL_SERVER_ACK_REQUEST) अणु
		_debug("________awaiting reply/ACK__________");
		ग_लिखो_lock_bh(&call->state_lock);
		चयन (call->state) अणु
		हाल RXRPC_CALL_CLIENT_SEND_REQUEST:
			call->state = RXRPC_CALL_CLIENT_AWAIT_REPLY;
			rxrpc_notअगरy_end_tx(rx, call, notअगरy_end_tx);
			अवरोध;
		हाल RXRPC_CALL_SERVER_ACK_REQUEST:
			call->state = RXRPC_CALL_SERVER_SEND_REPLY;
			now = jअगरfies;
			WRITE_ONCE(call->ack_at, now + MAX_JIFFY_OFFSET);
			अगर (call->ackr_reason == RXRPC_ACK_DELAY)
				call->ackr_reason = 0;
			trace_rxrpc_समयr(call, rxrpc_समयr_init_क्रम_send_reply, now);
			अगर (!last)
				अवरोध;
			fallthrough;
		हाल RXRPC_CALL_SERVER_SEND_REPLY:
			call->state = RXRPC_CALL_SERVER_AWAIT_ACK;
			rxrpc_notअगरy_end_tx(rx, call, notअगरy_end_tx);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ग_लिखो_unlock_bh(&call->state_lock);
	पूर्ण

	अगर (seq == 1 && rxrpc_is_client_call(call))
		rxrpc_expose_client_call(call);

	ret = rxrpc_send_data_packet(call, skb, false);
	अगर (ret < 0) अणु
		चयन (ret) अणु
		हाल -ENETUNREACH:
		हाल -EHOSTUNREACH:
		हाल -ECONNREFUSED:
			rxrpc_set_call_completion(call, RXRPC_CALL_LOCAL_ERROR,
						  0, ret);
			जाओ out;
		पूर्ण
		_debug("need instant resend %d", ret);
		rxrpc_instant_resend(call, ix);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ resend_at = now + call->peer->rto_j;

		WRITE_ONCE(call->resend_at, resend_at);
		rxrpc_reduce_call_समयr(call, resend_at, now,
					rxrpc_समयr_set_क्रम_send);
	पूर्ण

out:
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * send data through a socket
 * - must be called in process context
 * - The caller holds the call user access mutex, but not the socket lock.
 */
अटल पूर्णांक rxrpc_send_data(काष्ठा rxrpc_sock *rx,
			   काष्ठा rxrpc_call *call,
			   काष्ठा msghdr *msg, माप_प्रकार len,
			   rxrpc_notअगरy_end_tx_t notअगरy_end_tx)
अणु
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = &rx->sk;
	दीर्घ समयo;
	bool more;
	पूर्णांक ret, copied;

	समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);

	/* this should be in poll */
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN)
		वापस -EPIPE;

	more = msg->msg_flags & MSG_MORE;

	अगर (call->tx_total_len != -1) अणु
		अगर (len > call->tx_total_len)
			वापस -EMSGSIZE;
		अगर (!more && len != call->tx_total_len)
			वापस -EMSGSIZE;
	पूर्ण

	skb = call->tx_pending;
	call->tx_pending = शून्य;
	rxrpc_see_skb(skb, rxrpc_skb_seen);

	copied = 0;
	करो अणु
		/* Check to see अगर there's a ping ACK to reply to. */
		अगर (call->ackr_reason == RXRPC_ACK_PING_RESPONSE)
			rxrpc_send_ack_packet(call, false, शून्य);

		अगर (!skb) अणु
			माप_प्रकार reमुख्य, bufsize, chunk, offset;

			_debug("alloc");

			अगर (!rxrpc_check_tx_space(call, शून्य)) अणु
				ret = -EAGAIN;
				अगर (msg->msg_flags & MSG_DONTWAIT)
					जाओ maybe_error;
				ret = rxrpc_रुको_क्रम_tx_winकरोw(rx, call,
							       &समयo,
							       msg->msg_flags & MSG_WAITALL);
				अगर (ret < 0)
					जाओ maybe_error;
			पूर्ण

			/* Work out the maximum size of a packet.  Assume that
			 * the security header is going to be in the padded
			 * region (enc blocksize), but the trailer is not.
			 */
			reमुख्य = more ? पूर्णांक_उच्च : msg_data_left(msg);
			ret = call->conn->security->how_much_data(call, reमुख्य,
								  &bufsize, &chunk, &offset);
			अगर (ret < 0)
				जाओ maybe_error;

			_debug("SIZE: %zu/%zu @%zu", chunk, bufsize, offset);

			/* create a buffer that we can retain until it's ACK'd */
			skb = sock_alloc_send_skb(
				sk, bufsize, msg->msg_flags & MSG_DONTWAIT, &ret);
			अगर (!skb)
				जाओ maybe_error;

			sp = rxrpc_skb(skb);
			sp->rx_flags |= RXRPC_SKB_TX_BUFFER;
			rxrpc_new_skb(skb, rxrpc_skb_new);

			_debug("ALLOC SEND %p", skb);

			ASSERTCMP(skb->mark, ==, 0);

			__skb_put(skb, offset);

			sp->reमुख्य = chunk;
			अगर (sp->reमुख्य > skb_tailroom(skb))
				sp->reमुख्य = skb_tailroom(skb);

			_net("skb: hr %d, tr %d, hl %d, rm %d",
			       skb_headroom(skb),
			       skb_tailroom(skb),
			       skb_headlen(skb),
			       sp->reमुख्य);

			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण

		_debug("append");
		sp = rxrpc_skb(skb);

		/* append next segment of data to the current buffer */
		अगर (msg_data_left(msg) > 0) अणु
			पूर्णांक copy = skb_tailroom(skb);
			ASSERTCMP(copy, >, 0);
			अगर (copy > msg_data_left(msg))
				copy = msg_data_left(msg);
			अगर (copy > sp->reमुख्य)
				copy = sp->reमुख्य;

			_debug("add");
			ret = skb_add_data(skb, &msg->msg_iter, copy);
			_debug("added");
			अगर (ret < 0)
				जाओ efault;
			sp->reमुख्य -= copy;
			skb->mark += copy;
			copied += copy;
			अगर (call->tx_total_len != -1)
				call->tx_total_len -= copy;
		पूर्ण

		/* check क्रम the far side पातing the call or a network error
		 * occurring */
		अगर (call->state == RXRPC_CALL_COMPLETE)
			जाओ call_terminated;

		/* add the packet to the send queue अगर it's now full */
		अगर (sp->reमुख्य <= 0 ||
		    (msg_data_left(msg) == 0 && !more)) अणु
			काष्ठा rxrpc_connection *conn = call->conn;
			uपूर्णांक32_t seq;

			seq = call->tx_top + 1;

			sp->hdr.seq	= seq;
			sp->hdr._rsvd	= 0;
			sp->hdr.flags	= conn->out_clientflag;

			अगर (msg_data_left(msg) == 0 && !more)
				sp->hdr.flags |= RXRPC_LAST_PACKET;
			अन्यथा अगर (call->tx_top - call->tx_hard_ack <
				 call->tx_winsize)
				sp->hdr.flags |= RXRPC_MORE_PACKETS;

			ret = call->security->secure_packet(call, skb, skb->mark);
			अगर (ret < 0)
				जाओ out;

			ret = rxrpc_queue_packet(rx, call, skb,
						 !msg_data_left(msg) && !more,
						 notअगरy_end_tx);
			/* Should check क्रम failure here */
			skb = शून्य;
		पूर्ण
	पूर्ण जबतक (msg_data_left(msg) > 0);

success:
	ret = copied;
out:
	call->tx_pending = skb;
	_leave(" = %d", ret);
	वापस ret;

call_terminated:
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	_leave(" = %d", call->error);
	वापस call->error;

maybe_error:
	अगर (copied)
		जाओ success;
	जाओ out;

efault:
	ret = -EFAULT;
	जाओ out;
पूर्ण

/*
 * extract control messages from the sendmsg() control buffer
 */
अटल पूर्णांक rxrpc_sendmsg_cmsg(काष्ठा msghdr *msg, काष्ठा rxrpc_send_params *p)
अणु
	काष्ठा cmsghdr *cmsg;
	bool got_user_ID = false;
	पूर्णांक len;

	अगर (msg->msg_controllen == 0)
		वापस -EINVAL;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		len = cmsg->cmsg_len - माप(काष्ठा cmsghdr);
		_debug("CMSG %d, %d, %d",
		       cmsg->cmsg_level, cmsg->cmsg_type, len);

		अगर (cmsg->cmsg_level != SOL_RXRPC)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल RXRPC_USER_CALL_ID:
			अगर (msg->msg_flags & MSG_CMSG_COMPAT) अणु
				अगर (len != माप(u32))
					वापस -EINVAL;
				p->call.user_call_ID = *(u32 *)CMSG_DATA(cmsg);
			पूर्ण अन्यथा अणु
				अगर (len != माप(अचिन्हित दीर्घ))
					वापस -EINVAL;
				p->call.user_call_ID = *(अचिन्हित दीर्घ *)
					CMSG_DATA(cmsg);
			पूर्ण
			got_user_ID = true;
			अवरोध;

		हाल RXRPC_ABORT:
			अगर (p->command != RXRPC_CMD_SEND_DATA)
				वापस -EINVAL;
			p->command = RXRPC_CMD_SEND_ABORT;
			अगर (len != माप(p->पात_code))
				वापस -EINVAL;
			p->पात_code = *(अचिन्हित पूर्णांक *)CMSG_DATA(cmsg);
			अगर (p->पात_code == 0)
				वापस -EINVAL;
			अवरोध;

		हाल RXRPC_CHARGE_ACCEPT:
			अगर (p->command != RXRPC_CMD_SEND_DATA)
				वापस -EINVAL;
			p->command = RXRPC_CMD_CHARGE_ACCEPT;
			अगर (len != 0)
				वापस -EINVAL;
			अवरोध;

		हाल RXRPC_EXCLUSIVE_CALL:
			p->exclusive = true;
			अगर (len != 0)
				वापस -EINVAL;
			अवरोध;

		हाल RXRPC_UPGRADE_SERVICE:
			p->upgrade = true;
			अगर (len != 0)
				वापस -EINVAL;
			अवरोध;

		हाल RXRPC_TX_LENGTH:
			अगर (p->call.tx_total_len != -1 || len != माप(__s64))
				वापस -EINVAL;
			p->call.tx_total_len = *(__s64 *)CMSG_DATA(cmsg);
			अगर (p->call.tx_total_len < 0)
				वापस -EINVAL;
			अवरोध;

		हाल RXRPC_SET_CALL_TIMEOUT:
			अगर (len & 3 || len < 4 || len > 12)
				वापस -EINVAL;
			स_नकल(&p->call.समयouts, CMSG_DATA(cmsg), len);
			p->call.nr_समयouts = len / 4;
			अगर (p->call.समयouts.hard > पूर्णांक_उच्च / HZ)
				वापस -दुस्फल;
			अगर (p->call.nr_समयouts >= 2 && p->call.समयouts.idle > 60 * 60 * 1000)
				वापस -दुस्फल;
			अगर (p->call.nr_समयouts >= 3 && p->call.समयouts.normal > 60 * 60 * 1000)
				वापस -दुस्फल;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!got_user_ID)
		वापस -EINVAL;
	अगर (p->call.tx_total_len != -1 && p->command != RXRPC_CMD_SEND_DATA)
		वापस -EINVAL;
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Create a new client call क्रम sendmsg().
 * - Called with the socket lock held, which it must release.
 * - If it वापसs a call, the call's lock will need releasing by the caller.
 */
अटल काष्ठा rxrpc_call *
rxrpc_new_client_call_क्रम_sendmsg(काष्ठा rxrpc_sock *rx, काष्ठा msghdr *msg,
				  काष्ठा rxrpc_send_params *p)
	__releases(&rx->sk.sk_lock.slock)
	__acquires(&call->user_mutex)
अणु
	काष्ठा rxrpc_conn_parameters cp;
	काष्ठा rxrpc_call *call;
	काष्ठा key *key;

	DECLARE_SOCKADDR(काष्ठा sockaddr_rxrpc *, srx, msg->msg_name);

	_enter("");

	अगर (!msg->msg_name) अणु
		release_sock(&rx->sk);
		वापस ERR_PTR(-EDESTADDRREQ);
	पूर्ण

	key = rx->key;
	अगर (key && !rx->key->payload.data[0])
		key = शून्य;

	स_रखो(&cp, 0, माप(cp));
	cp.local		= rx->local;
	cp.key			= rx->key;
	cp.security_level	= rx->min_sec_level;
	cp.exclusive		= rx->exclusive | p->exclusive;
	cp.upgrade		= p->upgrade;
	cp.service_id		= srx->srx_service;
	call = rxrpc_new_client_call(rx, &cp, srx, &p->call, GFP_KERNEL,
				     atomic_inc_वापस(&rxrpc_debug_id));
	/* The socket is now unlocked */

	rxrpc_put_peer(cp.peer);
	_leave(" = %p\n", call);
	वापस call;
पूर्ण

/*
 * send a message क्रमming part of a client call through an RxRPC socket
 * - caller holds the socket locked
 * - the socket may be either a client socket or a server socket
 */
पूर्णांक rxrpc_करो_sendmsg(काष्ठा rxrpc_sock *rx, काष्ठा msghdr *msg, माप_प्रकार len)
	__releases(&rx->sk.sk_lock.slock)
	__releases(&call->user_mutex)
अणु
	क्रमागत rxrpc_call_state state;
	काष्ठा rxrpc_call *call;
	अचिन्हित दीर्घ now, j;
	पूर्णांक ret;

	काष्ठा rxrpc_send_params p = अणु
		.call.tx_total_len	= -1,
		.call.user_call_ID	= 0,
		.call.nr_समयouts	= 0,
		.call.पूर्णांकerruptibility	= RXRPC_INTERRUPTIBLE,
		.पात_code		= 0,
		.command		= RXRPC_CMD_SEND_DATA,
		.exclusive		= false,
		.upgrade		= false,
	पूर्ण;

	_enter("");

	ret = rxrpc_sendmsg_cmsg(msg, &p);
	अगर (ret < 0)
		जाओ error_release_sock;

	अगर (p.command == RXRPC_CMD_CHARGE_ACCEPT) अणु
		ret = -EINVAL;
		अगर (rx->sk.sk_state != RXRPC_SERVER_LISTENING)
			जाओ error_release_sock;
		ret = rxrpc_user_अक्षरge_accept(rx, p.call.user_call_ID);
		जाओ error_release_sock;
	पूर्ण

	call = rxrpc_find_call_by_user_ID(rx, p.call.user_call_ID);
	अगर (!call) अणु
		ret = -EBADSLT;
		अगर (p.command != RXRPC_CMD_SEND_DATA)
			जाओ error_release_sock;
		call = rxrpc_new_client_call_क्रम_sendmsg(rx, msg, &p);
		/* The socket is now unlocked... */
		अगर (IS_ERR(call))
			वापस PTR_ERR(call);
		/* ... and we have the call lock. */
		ret = 0;
		अगर (READ_ONCE(call->state) == RXRPC_CALL_COMPLETE)
			जाओ out_put_unlock;
	पूर्ण अन्यथा अणु
		चयन (READ_ONCE(call->state)) अणु
		हाल RXRPC_CALL_UNINITIALISED:
		हाल RXRPC_CALL_CLIENT_AWAIT_CONN:
		हाल RXRPC_CALL_SERVER_PREALLOC:
		हाल RXRPC_CALL_SERVER_SECURING:
			rxrpc_put_call(call, rxrpc_call_put);
			ret = -EBUSY;
			जाओ error_release_sock;
		शेष:
			अवरोध;
		पूर्ण

		ret = mutex_lock_पूर्णांकerruptible(&call->user_mutex);
		release_sock(&rx->sk);
		अगर (ret < 0) अणु
			ret = -ERESTARTSYS;
			जाओ error_put;
		पूर्ण

		अगर (p.call.tx_total_len != -1) अणु
			ret = -EINVAL;
			अगर (call->tx_total_len != -1 ||
			    call->tx_pending ||
			    call->tx_top != 0)
				जाओ error_put;
			call->tx_total_len = p.call.tx_total_len;
		पूर्ण
	पूर्ण

	चयन (p.call.nr_समयouts) अणु
	हाल 3:
		j = msecs_to_jअगरfies(p.call.समयouts.normal);
		अगर (p.call.समयouts.normal > 0 && j == 0)
			j = 1;
		WRITE_ONCE(call->next_rx_timo, j);
		fallthrough;
	हाल 2:
		j = msecs_to_jअगरfies(p.call.समयouts.idle);
		अगर (p.call.समयouts.idle > 0 && j == 0)
			j = 1;
		WRITE_ONCE(call->next_req_timo, j);
		fallthrough;
	हाल 1:
		अगर (p.call.समयouts.hard > 0) अणु
			j = msecs_to_jअगरfies(p.call.समयouts.hard);
			now = jअगरfies;
			j += now;
			WRITE_ONCE(call->expect_term_by, j);
			rxrpc_reduce_call_समयr(call, j, now,
						rxrpc_समयr_set_क्रम_hard);
		पूर्ण
		अवरोध;
	पूर्ण

	state = READ_ONCE(call->state);
	_debug("CALL %d USR %lx ST %d on CONN %p",
	       call->debug_id, call->user_call_ID, state, call->conn);

	अगर (state >= RXRPC_CALL_COMPLETE) अणु
		/* it's too late क्रम this call */
		ret = -ESHUTDOWN;
	पूर्ण अन्यथा अगर (p.command == RXRPC_CMD_SEND_ABORT) अणु
		ret = 0;
		अगर (rxrpc_पात_call("CMD", call, 0, p.पात_code, -ECONNABORTED))
			ret = rxrpc_send_पात_packet(call);
	पूर्ण अन्यथा अगर (p.command != RXRPC_CMD_SEND_DATA) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (rxrpc_is_client_call(call) &&
		   state != RXRPC_CALL_CLIENT_SEND_REQUEST) अणु
		/* request phase complete क्रम this client call */
		ret = -EPROTO;
	पूर्ण अन्यथा अगर (rxrpc_is_service_call(call) &&
		   state != RXRPC_CALL_SERVER_ACK_REQUEST &&
		   state != RXRPC_CALL_SERVER_SEND_REPLY) अणु
		/* Reply phase not begun or not complete क्रम service call. */
		ret = -EPROTO;
	पूर्ण अन्यथा अणु
		ret = rxrpc_send_data(rx, call, msg, len, शून्य);
	पूर्ण

out_put_unlock:
	mutex_unlock(&call->user_mutex);
error_put:
	rxrpc_put_call(call, rxrpc_call_put);
	_leave(" = %d", ret);
	वापस ret;

error_release_sock:
	release_sock(&rx->sk);
	वापस ret;
पूर्ण

/**
 * rxrpc_kernel_send_data - Allow a kernel service to send data on a call
 * @sock: The socket the call is on
 * @call: The call to send data through
 * @msg: The data to send
 * @len: The amount of data to send
 * @notअगरy_end_tx: Notअगरication that the last packet is queued.
 *
 * Allow a kernel service to send data on a call.  The call must be in an state
 * appropriate to sending data.  No control data should be supplied in @msg,
 * nor should an address be supplied.  MSG_MORE should be flagged अगर there's
 * more data to come, otherwise this data will end the transmission phase.
 */
पूर्णांक rxrpc_kernel_send_data(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			   काष्ठा msghdr *msg, माप_प्रकार len,
			   rxrpc_notअगरy_end_tx_t notअगरy_end_tx)
अणु
	पूर्णांक ret;

	_enter("{%d,%s},", call->debug_id, rxrpc_call_states[call->state]);

	ASSERTCMP(msg->msg_name, ==, शून्य);
	ASSERTCMP(msg->msg_control, ==, शून्य);

	mutex_lock(&call->user_mutex);

	_debug("CALL %d USR %lx ST %d on CONN %p",
	       call->debug_id, call->user_call_ID, call->state, call->conn);

	चयन (READ_ONCE(call->state)) अणु
	हाल RXRPC_CALL_CLIENT_SEND_REQUEST:
	हाल RXRPC_CALL_SERVER_ACK_REQUEST:
	हाल RXRPC_CALL_SERVER_SEND_REPLY:
		ret = rxrpc_send_data(rxrpc_sk(sock->sk), call, msg, len,
				      notअगरy_end_tx);
		अवरोध;
	हाल RXRPC_CALL_COMPLETE:
		पढ़ो_lock_bh(&call->state_lock);
		ret = call->error;
		पढ़ो_unlock_bh(&call->state_lock);
		अवरोध;
	शेष:
		/* Request phase complete क्रम this client call */
		trace_rxrpc_rx_eproto(call, 0, tracepoपूर्णांक_string("late_send"));
		ret = -EPROTO;
		अवरोध;
	पूर्ण

	mutex_unlock(&call->user_mutex);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_send_data);

/**
 * rxrpc_kernel_पात_call - Allow a kernel service to पात a call
 * @sock: The socket the call is on
 * @call: The call to be पातed
 * @पात_code: The पात code to stick पूर्णांकo the ABORT packet
 * @error: Local error value
 * @why: 3-अक्षर string indicating why.
 *
 * Allow a kernel service to पात a call, अगर it's still in an पातable state
 * and वापस true अगर the call was पातed, false अगर it was alपढ़ोy complete.
 */
bool rxrpc_kernel_पात_call(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			     u32 पात_code, पूर्णांक error, स्थिर अक्षर *why)
अणु
	bool पातed;

	_enter("{%d},%d,%d,%s", call->debug_id, पात_code, error, why);

	mutex_lock(&call->user_mutex);

	पातed = rxrpc_पात_call(why, call, 0, पात_code, error);
	अगर (पातed)
		rxrpc_send_पात_packet(call);

	mutex_unlock(&call->user_mutex);
	वापस पातed;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_पात_call);

/**
 * rxrpc_kernel_set_tx_length - Set the total Tx length on a call
 * @sock: The socket the call is on
 * @call: The call to be inक्रमmed
 * @tx_total_len: The amount of data to be transmitted क्रम this call
 *
 * Allow a kernel service to set the total transmit length on a call.  This
 * allows buffer-to-packet encrypt-and-copy to be perक्रमmed.
 *
 * This function is primarily क्रम use क्रम setting the reply length since the
 * request length can be set when beginning the call.
 */
व्योम rxrpc_kernel_set_tx_length(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
				s64 tx_total_len)
अणु
	WARN_ON(call->tx_total_len != -1);
	call->tx_total_len = tx_total_len;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_set_tx_length);
