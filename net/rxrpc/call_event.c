<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Management of Tx winकरोw, Tx resend, ACKs and out-of-sequence reception
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/udp.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश "ar-internal.h"

/*
 * Propose a PING ACK be sent.
 */
अटल व्योम rxrpc_propose_ping(काष्ठा rxrpc_call *call,
			       bool immediate, bool background)
अणु
	अगर (immediate) अणु
		अगर (background &&
		    !test_and_set_bit(RXRPC_CALL_EV_PING, &call->events))
			rxrpc_queue_call(call);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ ping_at = now + rxrpc_idle_ack_delay;

		अगर (समय_beक्रमe(ping_at, call->ping_at)) अणु
			WRITE_ONCE(call->ping_at, ping_at);
			rxrpc_reduce_call_समयr(call, ping_at, now,
						rxrpc_समयr_set_क्रम_ping);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * propose an ACK be sent
 */
अटल व्योम __rxrpc_propose_ACK(काष्ठा rxrpc_call *call, u8 ack_reason,
				u32 serial, bool immediate, bool background,
				क्रमागत rxrpc_propose_ack_trace why)
अणु
	क्रमागत rxrpc_propose_ack_outcome outcome = rxrpc_propose_ack_use;
	अचिन्हित दीर्घ expiry = rxrpc_soft_ack_delay;
	s8 prior = rxrpc_ack_priority[ack_reason];

	/* Pings are handled specially because we करोn't want to accidentally
	 * lose a ping response by subsuming it पूर्णांकo a ping.
	 */
	अगर (ack_reason == RXRPC_ACK_PING) अणु
		rxrpc_propose_ping(call, immediate, background);
		जाओ trace;
	पूर्ण

	/* Update DELAY, IDLE, REQUESTED and PING_RESPONSE ACK serial
	 * numbers, but we करोn't alter the समयout.
	 */
	_debug("prior %u %u vs %u %u",
	       ack_reason, prior,
	       call->ackr_reason, rxrpc_ack_priority[call->ackr_reason]);
	अगर (ack_reason == call->ackr_reason) अणु
		अगर (RXRPC_ACK_UPDATEABLE & (1 << ack_reason)) अणु
			outcome = rxrpc_propose_ack_update;
			call->ackr_serial = serial;
		पूर्ण
		अगर (!immediate)
			जाओ trace;
	पूर्ण अन्यथा अगर (prior > rxrpc_ack_priority[call->ackr_reason]) अणु
		call->ackr_reason = ack_reason;
		call->ackr_serial = serial;
	पूर्ण अन्यथा अणु
		outcome = rxrpc_propose_ack_subsume;
	पूर्ण

	चयन (ack_reason) अणु
	हाल RXRPC_ACK_REQUESTED:
		अगर (rxrpc_requested_ack_delay < expiry)
			expiry = rxrpc_requested_ack_delay;
		अगर (serial == 1)
			immediate = false;
		अवरोध;

	हाल RXRPC_ACK_DELAY:
		अगर (rxrpc_soft_ack_delay < expiry)
			expiry = rxrpc_soft_ack_delay;
		अवरोध;

	हाल RXRPC_ACK_IDLE:
		अगर (rxrpc_idle_ack_delay < expiry)
			expiry = rxrpc_idle_ack_delay;
		अवरोध;

	शेष:
		immediate = true;
		अवरोध;
	पूर्ण

	अगर (test_bit(RXRPC_CALL_EV_ACK, &call->events)) अणु
		_debug("already scheduled");
	पूर्ण अन्यथा अगर (immediate || expiry == 0) अणु
		_debug("immediate ACK %lx", call->events);
		अगर (!test_and_set_bit(RXRPC_CALL_EV_ACK, &call->events) &&
		    background)
			rxrpc_queue_call(call);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ now = jअगरfies, ack_at;

		अगर (call->peer->srtt_us != 0)
			ack_at = usecs_to_jअगरfies(call->peer->srtt_us >> 3);
		अन्यथा
			ack_at = expiry;

		ack_at += READ_ONCE(call->tx_backoff);
		ack_at += now;
		अगर (समय_beक्रमe(ack_at, call->ack_at)) अणु
			WRITE_ONCE(call->ack_at, ack_at);
			rxrpc_reduce_call_समयr(call, ack_at, now,
						rxrpc_समयr_set_क्रम_ack);
		पूर्ण
	पूर्ण

trace:
	trace_rxrpc_propose_ack(call, why, ack_reason, serial, immediate,
				background, outcome);
पूर्ण

/*
 * propose an ACK be sent, locking the call काष्ठाure
 */
व्योम rxrpc_propose_ACK(काष्ठा rxrpc_call *call, u8 ack_reason,
		       u32 serial, bool immediate, bool background,
		       क्रमागत rxrpc_propose_ack_trace why)
अणु
	spin_lock_bh(&call->lock);
	__rxrpc_propose_ACK(call, ack_reason, serial,
			    immediate, background, why);
	spin_unlock_bh(&call->lock);
पूर्ण

/*
 * Handle congestion being detected by the retransmit समयout.
 */
अटल व्योम rxrpc_congestion_समयout(काष्ठा rxrpc_call *call)
अणु
	set_bit(RXRPC_CALL_RETRANS_TIMEOUT, &call->flags);
पूर्ण

/*
 * Perक्रमm retransmission of NAK'd and unack'd packets.
 */
अटल व्योम rxrpc_resend(काष्ठा rxrpc_call *call, अचिन्हित दीर्घ now_j)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ resend_at, rto_j;
	rxrpc_seq_t cursor, seq, top;
	kसमय_प्रकार now, max_age, oldest, ack_ts;
	पूर्णांक ix;
	u8 annotation, anno_type, retrans = 0, unacked = 0;

	_enter("{%d,%d}", call->tx_hard_ack, call->tx_top);

	rto_j = call->peer->rto_j;

	now = kसमय_get_real();
	max_age = kसमय_sub(now, jअगरfies_to_usecs(rto_j));

	spin_lock_bh(&call->lock);

	cursor = call->tx_hard_ack;
	top = call->tx_top;
	ASSERT(beक्रमe_eq(cursor, top));
	अगर (cursor == top)
		जाओ out_unlock;

	/* Scan the packet list without dropping the lock and decide which of
	 * the packets in the Tx buffer we're going to resend and what the new
	 * resend समयout will be.
	 */
	trace_rxrpc_resend(call, (cursor + 1) & RXRPC_RXTX_BUFF_MASK);
	oldest = now;
	क्रम (seq = cursor + 1; beक्रमe_eq(seq, top); seq++) अणु
		ix = seq & RXRPC_RXTX_BUFF_MASK;
		annotation = call->rxtx_annotations[ix];
		anno_type = annotation & RXRPC_TX_ANNO_MASK;
		annotation &= ~RXRPC_TX_ANNO_MASK;
		अगर (anno_type == RXRPC_TX_ANNO_ACK)
			जारी;

		skb = call->rxtx_buffer[ix];
		rxrpc_see_skb(skb, rxrpc_skb_seen);

		अगर (anno_type == RXRPC_TX_ANNO_UNACK) अणु
			अगर (kसमय_after(skb->tstamp, max_age)) अणु
				अगर (kसमय_beक्रमe(skb->tstamp, oldest))
					oldest = skb->tstamp;
				जारी;
			पूर्ण
			अगर (!(annotation & RXRPC_TX_ANNO_RESENT))
				unacked++;
		पूर्ण

		/* Okay, we need to retransmit a packet. */
		call->rxtx_annotations[ix] = RXRPC_TX_ANNO_RETRANS | annotation;
		retrans++;
		trace_rxrpc_retransmit(call, seq, annotation | anno_type,
				       kसमय_प्रकारo_ns(kसमय_sub(skb->tstamp, max_age)));
	पूर्ण

	resend_at = nsecs_to_jअगरfies(kसमय_प्रकारo_ns(kसमय_sub(now, oldest)));
	resend_at += jअगरfies + rto_j;
	WRITE_ONCE(call->resend_at, resend_at);

	अगर (unacked)
		rxrpc_congestion_समयout(call);

	/* If there was nothing that needed retransmission then it's likely
	 * that an ACK got lost somewhere.  Send a ping to find out instead of
	 * retransmitting data.
	 */
	अगर (!retrans) अणु
		rxrpc_reduce_call_समयr(call, resend_at, now_j,
					rxrpc_समयr_set_क्रम_resend);
		spin_unlock_bh(&call->lock);
		ack_ts = kसमय_sub(now, call->acks_latest_ts);
		अगर (kसमय_प्रकारo_us(ack_ts) < (call->peer->srtt_us >> 3))
			जाओ out;
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, 0, true, false,
				  rxrpc_propose_ack_ping_क्रम_lost_ack);
		rxrpc_send_ack_packet(call, true, शून्य);
		जाओ out;
	पूर्ण

	/* Now go through the Tx winकरोw and perक्रमm the retransmissions.  We
	 * have to drop the lock क्रम each send.  If an ACK comes in whilst the
	 * lock is dropped, it may clear some of the retransmission markers क्रम
	 * packets that it soft-ACKs.
	 */
	क्रम (seq = cursor + 1; beक्रमe_eq(seq, top); seq++) अणु
		ix = seq & RXRPC_RXTX_BUFF_MASK;
		annotation = call->rxtx_annotations[ix];
		anno_type = annotation & RXRPC_TX_ANNO_MASK;
		अगर (anno_type != RXRPC_TX_ANNO_RETRANS)
			जारी;

		/* We need to reset the retransmission state, but we need to करो
		 * so beक्रमe we drop the lock as a new ACK/NAK may come in and
		 * confuse things
		 */
		annotation &= ~RXRPC_TX_ANNO_MASK;
		annotation |= RXRPC_TX_ANNO_UNACK | RXRPC_TX_ANNO_RESENT;
		call->rxtx_annotations[ix] = annotation;

		skb = call->rxtx_buffer[ix];
		अगर (!skb)
			जारी;

		rxrpc_get_skb(skb, rxrpc_skb_got);
		spin_unlock_bh(&call->lock);

		अगर (rxrpc_send_data_packet(call, skb, true) < 0) अणु
			rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
			वापस;
		पूर्ण

		अगर (rxrpc_is_client_call(call))
			rxrpc_expose_client_call(call);

		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
		spin_lock_bh(&call->lock);
		अगर (after(call->tx_hard_ack, seq))
			seq = call->tx_hard_ack;
	पूर्ण

out_unlock:
	spin_unlock_bh(&call->lock);
out:
	_leave("");
पूर्ण

/*
 * Handle retransmission and deferred ACK/पात generation.
 */
व्योम rxrpc_process_call(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_call *call =
		container_of(work, काष्ठा rxrpc_call, processor);
	rxrpc_serial_t *send_ack;
	अचिन्हित दीर्घ now, next, t;
	अचिन्हित पूर्णांक iterations = 0;

	rxrpc_see_call(call);

	//prपूर्णांकk("\n--------------------\n");
	_enter("{%d,%s,%lx}",
	       call->debug_id, rxrpc_call_states[call->state], call->events);

recheck_state:
	/* Limit the number of बार we करो this beक्रमe वापसing to the manager */
	iterations++;
	अगर (iterations > 5)
		जाओ requeue;

	अगर (test_and_clear_bit(RXRPC_CALL_EV_ABORT, &call->events)) अणु
		rxrpc_send_पात_packet(call);
		जाओ recheck_state;
	पूर्ण

	अगर (call->state == RXRPC_CALL_COMPLETE) अणु
		del_समयr_sync(&call->समयr);
		जाओ out_put;
	पूर्ण

	/* Work out अगर any समयouts tripped */
	now = jअगरfies;
	t = READ_ONCE(call->expect_rx_by);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_normal, now);
		set_bit(RXRPC_CALL_EV_EXPIRED, &call->events);
	पूर्ण

	t = READ_ONCE(call->expect_req_by);
	अगर (call->state == RXRPC_CALL_SERVER_RECV_REQUEST &&
	    समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_idle, now);
		set_bit(RXRPC_CALL_EV_EXPIRED, &call->events);
	पूर्ण

	t = READ_ONCE(call->expect_term_by);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_hard, now);
		set_bit(RXRPC_CALL_EV_EXPIRED, &call->events);
	पूर्ण

	t = READ_ONCE(call->ack_at);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_ack, now);
		cmpxchg(&call->ack_at, t, now + MAX_JIFFY_OFFSET);
		set_bit(RXRPC_CALL_EV_ACK, &call->events);
	पूर्ण

	t = READ_ONCE(call->ack_lost_at);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_lost_ack, now);
		cmpxchg(&call->ack_lost_at, t, now + MAX_JIFFY_OFFSET);
		set_bit(RXRPC_CALL_EV_ACK_LOST, &call->events);
	पूर्ण

	t = READ_ONCE(call->keepalive_at);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_keepalive, now);
		cmpxchg(&call->keepalive_at, t, now + MAX_JIFFY_OFFSET);
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, 0, true, true,
				  rxrpc_propose_ack_ping_क्रम_keepalive);
		set_bit(RXRPC_CALL_EV_PING, &call->events);
	पूर्ण

	t = READ_ONCE(call->ping_at);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_ping, now);
		cmpxchg(&call->ping_at, t, now + MAX_JIFFY_OFFSET);
		set_bit(RXRPC_CALL_EV_PING, &call->events);
	पूर्ण

	t = READ_ONCE(call->resend_at);
	अगर (समय_after_eq(now, t)) अणु
		trace_rxrpc_समयr(call, rxrpc_समयr_exp_resend, now);
		cmpxchg(&call->resend_at, t, now + MAX_JIFFY_OFFSET);
		set_bit(RXRPC_CALL_EV_RESEND, &call->events);
	पूर्ण

	/* Process events */
	अगर (test_and_clear_bit(RXRPC_CALL_EV_EXPIRED, &call->events)) अणु
		अगर (test_bit(RXRPC_CALL_RX_HEARD, &call->flags) &&
		    (पूर्णांक)call->conn->hi_serial - (पूर्णांक)call->rx_serial > 0) अणु
			trace_rxrpc_call_reset(call);
			rxrpc_पात_call("EXP", call, 0, RX_USER_ABORT, -ECONNRESET);
		पूर्ण अन्यथा अणु
			rxrpc_पात_call("EXP", call, 0, RX_USER_ABORT, -ETIME);
		पूर्ण
		set_bit(RXRPC_CALL_EV_ABORT, &call->events);
		जाओ recheck_state;
	पूर्ण

	send_ack = शून्य;
	अगर (test_and_clear_bit(RXRPC_CALL_EV_ACK_LOST, &call->events)) अणु
		call->acks_lost_top = call->tx_top;
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, 0, true, false,
				  rxrpc_propose_ack_ping_क्रम_lost_ack);
		send_ack = &call->acks_lost_ping;
	पूर्ण

	अगर (test_and_clear_bit(RXRPC_CALL_EV_ACK, &call->events) ||
	    send_ack) अणु
		अगर (call->ackr_reason) अणु
			rxrpc_send_ack_packet(call, false, send_ack);
			जाओ recheck_state;
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(RXRPC_CALL_EV_PING, &call->events)) अणु
		rxrpc_send_ack_packet(call, true, शून्य);
		जाओ recheck_state;
	पूर्ण

	अगर (test_and_clear_bit(RXRPC_CALL_EV_RESEND, &call->events)) अणु
		rxrpc_resend(call, now);
		जाओ recheck_state;
	पूर्ण

	/* Make sure the समयr is restarted */
	next = call->expect_rx_by;

#घोषणा set(T) अणु t = READ_ONCE(T); अगर (समय_beक्रमe(t, next)) next = t; पूर्ण

	set(call->expect_req_by);
	set(call->expect_term_by);
	set(call->ack_at);
	set(call->ack_lost_at);
	set(call->resend_at);
	set(call->keepalive_at);
	set(call->ping_at);

	now = jअगरfies;
	अगर (समय_after_eq(now, next))
		जाओ recheck_state;

	rxrpc_reduce_call_समयr(call, next, now, rxrpc_समयr_restart);

	/* other events may have been उठाओd since we started checking */
	अगर (call->events && call->state < RXRPC_CALL_COMPLETE)
		जाओ requeue;

out_put:
	rxrpc_put_call(call, rxrpc_call_put);
out:
	_leave("");
	वापस;

requeue:
	__rxrpc_queue_call(call);
	जाओ out;
पूर्ण
