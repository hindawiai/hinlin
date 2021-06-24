<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC packet reception
 *
 * Copyright (C) 2007, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmp.h>
#समावेश <linux/gfp.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/net_namespace.h>
#समावेश "ar-internal.h"

अटल व्योम rxrpc_proto_पात(स्थिर अक्षर *why,
			      काष्ठा rxrpc_call *call, rxrpc_seq_t seq)
अणु
	अगर (rxrpc_पात_call(why, call, seq, RX_PROTOCOL_ERROR, -EBADMSG)) अणु
		set_bit(RXRPC_CALL_EV_ABORT, &call->events);
		rxrpc_queue_call(call);
	पूर्ण
पूर्ण

/*
 * Do TCP-style congestion management [RFC 5681].
 */
अटल व्योम rxrpc_congestion_management(काष्ठा rxrpc_call *call,
					काष्ठा sk_buff *skb,
					काष्ठा rxrpc_ack_summary *summary,
					rxrpc_serial_t acked_serial)
अणु
	क्रमागत rxrpc_congest_change change = rxrpc_cong_no_change;
	अचिन्हित पूर्णांक cumulative_acks = call->cong_cumul_acks;
	अचिन्हित पूर्णांक cwnd = call->cong_cwnd;
	bool resend = false;

	summary->flight_size =
		(call->tx_top - call->tx_hard_ack) - summary->nr_acks;

	अगर (test_and_clear_bit(RXRPC_CALL_RETRANS_TIMEOUT, &call->flags)) अणु
		summary->retrans_समयo = true;
		call->cong_ssthresh = max_t(अचिन्हित पूर्णांक,
					    summary->flight_size / 2, 2);
		cwnd = 1;
		अगर (cwnd >= call->cong_ssthresh &&
		    call->cong_mode == RXRPC_CALL_SLOW_START) अणु
			call->cong_mode = RXRPC_CALL_CONGEST_AVOIDANCE;
			call->cong_tstamp = skb->tstamp;
			cumulative_acks = 0;
		पूर्ण
	पूर्ण

	cumulative_acks += summary->nr_new_acks;
	cumulative_acks += summary->nr_rot_new_acks;
	अगर (cumulative_acks > 255)
		cumulative_acks = 255;

	summary->mode = call->cong_mode;
	summary->cwnd = call->cong_cwnd;
	summary->ssthresh = call->cong_ssthresh;
	summary->cumulative_acks = cumulative_acks;
	summary->dup_acks = call->cong_dup_acks;

	चयन (call->cong_mode) अणु
	हाल RXRPC_CALL_SLOW_START:
		अगर (summary->nr_nacks > 0)
			जाओ packet_loss_detected;
		अगर (summary->cumulative_acks > 0)
			cwnd += 1;
		अगर (cwnd >= call->cong_ssthresh) अणु
			call->cong_mode = RXRPC_CALL_CONGEST_AVOIDANCE;
			call->cong_tstamp = skb->tstamp;
		पूर्ण
		जाओ out;

	हाल RXRPC_CALL_CONGEST_AVOIDANCE:
		अगर (summary->nr_nacks > 0)
			जाओ packet_loss_detected;

		/* We analyse the number of packets that get ACK'd per RTT
		 * period and increase the winकरोw अगर we managed to fill it.
		 */
		अगर (call->peer->rtt_count == 0)
			जाओ out;
		अगर (kसमय_beक्रमe(skb->tstamp,
				 kसमय_add_us(call->cong_tstamp,
					      call->peer->srtt_us >> 3)))
			जाओ out_no_clear_ca;
		change = rxrpc_cong_rtt_winकरोw_end;
		call->cong_tstamp = skb->tstamp;
		अगर (cumulative_acks >= cwnd)
			cwnd++;
		जाओ out;

	हाल RXRPC_CALL_PACKET_LOSS:
		अगर (summary->nr_nacks == 0)
			जाओ resume_normality;

		अगर (summary->new_low_nack) अणु
			change = rxrpc_cong_new_low_nack;
			call->cong_dup_acks = 1;
			अगर (call->cong_extra > 1)
				call->cong_extra = 1;
			जाओ send_extra_data;
		पूर्ण

		call->cong_dup_acks++;
		अगर (call->cong_dup_acks < 3)
			जाओ send_extra_data;

		change = rxrpc_cong_begin_retransmission;
		call->cong_mode = RXRPC_CALL_FAST_RETRANSMIT;
		call->cong_ssthresh = max_t(अचिन्हित पूर्णांक,
					    summary->flight_size / 2, 2);
		cwnd = call->cong_ssthresh + 3;
		call->cong_extra = 0;
		call->cong_dup_acks = 0;
		resend = true;
		जाओ out;

	हाल RXRPC_CALL_FAST_RETRANSMIT:
		अगर (!summary->new_low_nack) अणु
			अगर (summary->nr_new_acks == 0)
				cwnd += 1;
			call->cong_dup_acks++;
			अगर (call->cong_dup_acks == 2) अणु
				change = rxrpc_cong_retransmit_again;
				call->cong_dup_acks = 0;
				resend = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			change = rxrpc_cong_progress;
			cwnd = call->cong_ssthresh;
			अगर (summary->nr_nacks == 0)
				जाओ resume_normality;
		पूर्ण
		जाओ out;

	शेष:
		BUG();
		जाओ out;
	पूर्ण

resume_normality:
	change = rxrpc_cong_cleared_nacks;
	call->cong_dup_acks = 0;
	call->cong_extra = 0;
	call->cong_tstamp = skb->tstamp;
	अगर (cwnd < call->cong_ssthresh)
		call->cong_mode = RXRPC_CALL_SLOW_START;
	अन्यथा
		call->cong_mode = RXRPC_CALL_CONGEST_AVOIDANCE;
out:
	cumulative_acks = 0;
out_no_clear_ca:
	अगर (cwnd >= RXRPC_RXTX_BUFF_SIZE - 1)
		cwnd = RXRPC_RXTX_BUFF_SIZE - 1;
	call->cong_cwnd = cwnd;
	call->cong_cumul_acks = cumulative_acks;
	trace_rxrpc_congest(call, summary, acked_serial, change);
	अगर (resend && !test_and_set_bit(RXRPC_CALL_EV_RESEND, &call->events))
		rxrpc_queue_call(call);
	वापस;

packet_loss_detected:
	change = rxrpc_cong_saw_nack;
	call->cong_mode = RXRPC_CALL_PACKET_LOSS;
	call->cong_dup_acks = 0;
	जाओ send_extra_data;

send_extra_data:
	/* Send some previously unsent DATA अगर we have some to advance the ACK
	 * state.
	 */
	अगर (call->rxtx_annotations[call->tx_top & RXRPC_RXTX_BUFF_MASK] &
	    RXRPC_TX_ANNO_LAST ||
	    summary->nr_acks != call->tx_top - call->tx_hard_ack) अणु
		call->cong_extra++;
		wake_up(&call->रुकोq);
	पूर्ण
	जाओ out_no_clear_ca;
पूर्ण

/*
 * Apply a hard ACK by advancing the Tx winकरोw.
 */
अटल bool rxrpc_rotate_tx_winकरोw(काष्ठा rxrpc_call *call, rxrpc_seq_t to,
				   काष्ठा rxrpc_ack_summary *summary)
अणु
	काष्ठा sk_buff *skb, *list = शून्य;
	bool rot_last = false;
	पूर्णांक ix;
	u8 annotation;

	अगर (call->acks_lowest_nak == call->tx_hard_ack) अणु
		call->acks_lowest_nak = to;
	पूर्ण अन्यथा अगर (beक्रमe_eq(call->acks_lowest_nak, to)) अणु
		summary->new_low_nack = true;
		call->acks_lowest_nak = to;
	पूर्ण

	spin_lock(&call->lock);

	जबतक (beक्रमe(call->tx_hard_ack, to)) अणु
		call->tx_hard_ack++;
		ix = call->tx_hard_ack & RXRPC_RXTX_BUFF_MASK;
		skb = call->rxtx_buffer[ix];
		annotation = call->rxtx_annotations[ix];
		rxrpc_see_skb(skb, rxrpc_skb_rotated);
		call->rxtx_buffer[ix] = शून्य;
		call->rxtx_annotations[ix] = 0;
		skb->next = list;
		list = skb;

		अगर (annotation & RXRPC_TX_ANNO_LAST) अणु
			set_bit(RXRPC_CALL_TX_LAST, &call->flags);
			rot_last = true;
		पूर्ण
		अगर ((annotation & RXRPC_TX_ANNO_MASK) != RXRPC_TX_ANNO_ACK)
			summary->nr_rot_new_acks++;
	पूर्ण

	spin_unlock(&call->lock);

	trace_rxrpc_transmit(call, (rot_last ?
				    rxrpc_transmit_rotate_last :
				    rxrpc_transmit_rotate));
	wake_up(&call->रुकोq);

	जबतक (list) अणु
		skb = list;
		list = skb->next;
		skb_mark_not_on_list(skb);
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	पूर्ण

	वापस rot_last;
पूर्ण

/*
 * End the transmission phase of a call.
 *
 * This occurs when we get an ACKALL packet, the first DATA packet of a reply,
 * or a final ACK packet.
 */
अटल bool rxrpc_end_tx_phase(काष्ठा rxrpc_call *call, bool reply_begun,
			       स्थिर अक्षर *पात_why)
अणु
	अचिन्हित पूर्णांक state;

	ASSERT(test_bit(RXRPC_CALL_TX_LAST, &call->flags));

	ग_लिखो_lock(&call->state_lock);

	state = call->state;
	चयन (state) अणु
	हाल RXRPC_CALL_CLIENT_SEND_REQUEST:
	हाल RXRPC_CALL_CLIENT_AWAIT_REPLY:
		अगर (reply_begun)
			call->state = state = RXRPC_CALL_CLIENT_RECV_REPLY;
		अन्यथा
			call->state = state = RXRPC_CALL_CLIENT_AWAIT_REPLY;
		अवरोध;

	हाल RXRPC_CALL_SERVER_AWAIT_ACK:
		__rxrpc_call_completed(call);
		state = call->state;
		अवरोध;

	शेष:
		जाओ bad_state;
	पूर्ण

	ग_लिखो_unlock(&call->state_lock);
	अगर (state == RXRPC_CALL_CLIENT_AWAIT_REPLY)
		trace_rxrpc_transmit(call, rxrpc_transmit_aरुको_reply);
	अन्यथा
		trace_rxrpc_transmit(call, rxrpc_transmit_end);
	_leave(" = ok");
	वापस true;

bad_state:
	ग_लिखो_unlock(&call->state_lock);
	kdebug("end_tx %s", rxrpc_call_states[call->state]);
	rxrpc_proto_पात(पात_why, call, call->tx_top);
	वापस false;
पूर्ण

/*
 * Begin the reply reception phase of a call.
 */
अटल bool rxrpc_receiving_reply(काष्ठा rxrpc_call *call)
अणु
	काष्ठा rxrpc_ack_summary summary = अणु 0 पूर्ण;
	अचिन्हित दीर्घ now, timo;
	rxrpc_seq_t top = READ_ONCE(call->tx_top);

	अगर (call->ackr_reason) अणु
		spin_lock_bh(&call->lock);
		call->ackr_reason = 0;
		spin_unlock_bh(&call->lock);
		now = jअगरfies;
		timo = now + MAX_JIFFY_OFFSET;
		WRITE_ONCE(call->resend_at, timo);
		WRITE_ONCE(call->ack_at, timo);
		trace_rxrpc_समयr(call, rxrpc_समयr_init_क्रम_reply, now);
	पूर्ण

	अगर (!test_bit(RXRPC_CALL_TX_LAST, &call->flags)) अणु
		अगर (!rxrpc_rotate_tx_winकरोw(call, top, &summary)) अणु
			rxrpc_proto_पात("TXL", call, top);
			वापस false;
		पूर्ण
	पूर्ण
	अगर (!rxrpc_end_tx_phase(call, true, "ETD"))
		वापस false;
	call->tx_phase = false;
	वापस true;
पूर्ण

/*
 * Scan a data packet to validate its काष्ठाure and to work out how many
 * subpackets it contains.
 *
 * A jumbo packet is a collection of consecutive packets glued together with
 * little headers between that indicate how to change the initial header क्रम
 * each subpacket.
 *
 * RXRPC_JUMBO_PACKET must be set on all but the last subpacket - and all but
 * the last are RXRPC_JUMBO_DATALEN in size.  The last subpacket may be of any
 * size.
 */
अटल bool rxrpc_validate_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	अचिन्हित पूर्णांक offset = माप(काष्ठा rxrpc_wire_header);
	अचिन्हित पूर्णांक len = skb->len;
	u8 flags = sp->hdr.flags;

	क्रम (;;) अणु
		अगर (flags & RXRPC_REQUEST_ACK)
			__set_bit(sp->nr_subpackets, sp->rx_req_ack);
		sp->nr_subpackets++;

		अगर (!(flags & RXRPC_JUMBO_PACKET))
			अवरोध;

		अगर (len - offset < RXRPC_JUMBO_SUBPKTLEN)
			जाओ protocol_error;
		अगर (flags & RXRPC_LAST_PACKET)
			जाओ protocol_error;
		offset += RXRPC_JUMBO_DATALEN;
		अगर (skb_copy_bits(skb, offset, &flags, 1) < 0)
			जाओ protocol_error;
		offset += माप(काष्ठा rxrpc_jumbo_header);
	पूर्ण

	अगर (flags & RXRPC_LAST_PACKET)
		sp->rx_flags |= RXRPC_SKB_INCL_LAST;
	वापस true;

protocol_error:
	वापस false;
पूर्ण

/*
 * Handle reception of a duplicate packet.
 *
 * We have to take care to aव्योम an attack here whereby we're given a series of
 * jumbograms, each with a sequence number one beक्रमe the preceding one and
 * filled up to maximum UDP size.  If they never send us the first packet in
 * the sequence, they can cause us to have to hold on to around 2MiB of kernel
 * space until the call बार out.
 *
 * We limit the space usage by only accepting three duplicate jumbo packets per
 * call.  After that, we tell the other side we're no दीर्घer accepting jumbos
 * (that inक्रमmation is encoded in the ACK packet).
 */
अटल व्योम rxrpc_input_dup_data(काष्ठा rxrpc_call *call, rxrpc_seq_t seq,
				 bool is_jumbo, bool *_jumbo_bad)
अणु
	/* Discard normal packets that are duplicates. */
	अगर (is_jumbo)
		वापस;

	/* Skip jumbo subpackets that are duplicates.  When we've had three or
	 * more partially duplicate jumbo packets, we refuse to take any more
	 * jumbos क्रम this call.
	 */
	अगर (!*_jumbo_bad) अणु
		call->nr_jumbo_bad++;
		*_jumbo_bad = true;
	पूर्ण
पूर्ण

/*
 * Process a DATA packet, adding the packet to the Rx ring.  The caller's
 * packet ref must be passed on or discarded.
 */
अटल व्योम rxrpc_input_data(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	क्रमागत rxrpc_call_state state;
	अचिन्हित पूर्णांक j, nr_subpackets;
	rxrpc_serial_t serial = sp->hdr.serial, ack_serial = 0;
	rxrpc_seq_t seq0 = sp->hdr.seq, hard_ack;
	bool immediate_ack = false, jumbo_bad = false;
	u8 ack = 0;

	_enter("{%u,%u},{%u,%u}",
	       call->rx_hard_ack, call->rx_top, skb->len, seq0);

	_proto("Rx DATA %%%u { #%u f=%02x n=%u }",
	       sp->hdr.serial, seq0, sp->hdr.flags, sp->nr_subpackets);

	state = READ_ONCE(call->state);
	अगर (state >= RXRPC_CALL_COMPLETE) अणु
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
		वापस;
	पूर्ण

	अगर (state == RXRPC_CALL_SERVER_RECV_REQUEST) अणु
		अचिन्हित दीर्घ timo = READ_ONCE(call->next_req_timo);
		अचिन्हित दीर्घ now, expect_req_by;

		अगर (timo) अणु
			now = jअगरfies;
			expect_req_by = now + timo;
			WRITE_ONCE(call->expect_req_by, expect_req_by);
			rxrpc_reduce_call_समयr(call, expect_req_by, now,
						rxrpc_समयr_set_क्रम_idle);
		पूर्ण
	पूर्ण

	spin_lock(&call->input_lock);

	/* Received data implicitly ACKs all of the request packets we sent
	 * when we're acting as a client.
	 */
	अगर ((state == RXRPC_CALL_CLIENT_SEND_REQUEST ||
	     state == RXRPC_CALL_CLIENT_AWAIT_REPLY) &&
	    !rxrpc_receiving_reply(call))
		जाओ unlock;

	call->ackr_prev_seq = seq0;
	hard_ack = READ_ONCE(call->rx_hard_ack);

	nr_subpackets = sp->nr_subpackets;
	अगर (nr_subpackets > 1) अणु
		अगर (call->nr_jumbo_bad > 3) अणु
			ack = RXRPC_ACK_NOSPACE;
			ack_serial = serial;
			जाओ ack;
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < nr_subpackets; j++) अणु
		rxrpc_serial_t serial = sp->hdr.serial + j;
		rxrpc_seq_t seq = seq0 + j;
		अचिन्हित पूर्णांक ix = seq & RXRPC_RXTX_BUFF_MASK;
		bool terminal = (j == nr_subpackets - 1);
		bool last = terminal && (sp->rx_flags & RXRPC_SKB_INCL_LAST);
		u8 flags, annotation = j;

		_proto("Rx DATA+%u %%%u { #%x t=%u l=%u }",
		     j, serial, seq, terminal, last);

		अगर (last) अणु
			अगर (test_bit(RXRPC_CALL_RX_LAST, &call->flags) &&
			    seq != call->rx_top) अणु
				rxrpc_proto_पात("LSN", call, seq);
				जाओ unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (test_bit(RXRPC_CALL_RX_LAST, &call->flags) &&
			    after_eq(seq, call->rx_top)) अणु
				rxrpc_proto_पात("LSA", call, seq);
				जाओ unlock;
			पूर्ण
		पूर्ण

		flags = 0;
		अगर (last)
			flags |= RXRPC_LAST_PACKET;
		अगर (!terminal)
			flags |= RXRPC_JUMBO_PACKET;
		अगर (test_bit(j, sp->rx_req_ack))
			flags |= RXRPC_REQUEST_ACK;
		trace_rxrpc_rx_data(call->debug_id, seq, serial, flags, annotation);

		अगर (beक्रमe_eq(seq, hard_ack)) अणु
			ack = RXRPC_ACK_DUPLICATE;
			ack_serial = serial;
			जारी;
		पूर्ण

		अगर (call->rxtx_buffer[ix]) अणु
			rxrpc_input_dup_data(call, seq, nr_subpackets > 1,
					     &jumbo_bad);
			अगर (ack != RXRPC_ACK_DUPLICATE) अणु
				ack = RXRPC_ACK_DUPLICATE;
				ack_serial = serial;
			पूर्ण
			immediate_ack = true;
			जारी;
		पूर्ण

		अगर (after(seq, hard_ack + call->rx_winsize)) अणु
			ack = RXRPC_ACK_EXCEEDS_WINDOW;
			ack_serial = serial;
			अगर (flags & RXRPC_JUMBO_PACKET) अणु
				अगर (!jumbo_bad) अणु
					call->nr_jumbo_bad++;
					jumbo_bad = true;
				पूर्ण
			पूर्ण

			जाओ ack;
		पूर्ण

		अगर (flags & RXRPC_REQUEST_ACK && !ack) अणु
			ack = RXRPC_ACK_REQUESTED;
			ack_serial = serial;
		पूर्ण

		/* Queue the packet.  We use a couple of memory barriers here as need
		 * to make sure that rx_top is perceived to be set after the buffer
		 * poपूर्णांकer and that the buffer poपूर्णांकer is set after the annotation and
		 * the skb data.
		 *
		 * Barriers against rxrpc_recvmsg_data() and rxrpc_rotate_rx_winकरोw()
		 * and also rxrpc_fill_out_ack().
		 */
		अगर (!terminal)
			rxrpc_get_skb(skb, rxrpc_skb_got);
		call->rxtx_annotations[ix] = annotation;
		smp_wmb();
		call->rxtx_buffer[ix] = skb;
		अगर (after(seq, call->rx_top)) अणु
			smp_store_release(&call->rx_top, seq);
		पूर्ण अन्यथा अगर (beक्रमe(seq, call->rx_top)) अणु
			/* Send an immediate ACK अगर we fill in a hole */
			अगर (!ack) अणु
				ack = RXRPC_ACK_DELAY;
				ack_serial = serial;
			पूर्ण
			immediate_ack = true;
		पूर्ण

		अगर (terminal) अणु
			/* From this poपूर्णांक on, we're not allowed to touch the
			 * packet any दीर्घer as its ref now beदीर्घs to the Rx
			 * ring.
			 */
			skb = शून्य;
			sp = शून्य;
		पूर्ण

		अगर (last) अणु
			set_bit(RXRPC_CALL_RX_LAST, &call->flags);
			अगर (!ack) अणु
				ack = RXRPC_ACK_DELAY;
				ack_serial = serial;
			पूर्ण
			trace_rxrpc_receive(call, rxrpc_receive_queue_last, serial, seq);
		पूर्ण अन्यथा अणु
			trace_rxrpc_receive(call, rxrpc_receive_queue, serial, seq);
		पूर्ण

		अगर (after_eq(seq, call->rx_expect_next)) अणु
			अगर (after(seq, call->rx_expect_next)) अणु
				_net("OOS %u > %u", seq, call->rx_expect_next);
				ack = RXRPC_ACK_OUT_OF_SEQUENCE;
				ack_serial = serial;
			पूर्ण
			call->rx_expect_next = seq + 1;
		पूर्ण
	पूर्ण

ack:
	अगर (ack)
		rxrpc_propose_ACK(call, ack, ack_serial,
				  immediate_ack, true,
				  rxrpc_propose_ack_input_data);
	अन्यथा
		rxrpc_propose_ACK(call, RXRPC_ACK_DELAY, serial,
				  false, true,
				  rxrpc_propose_ack_input_data);

	trace_rxrpc_notअगरy_socket(call->debug_id, serial);
	rxrpc_notअगरy_socket(call);

unlock:
	spin_unlock(&call->input_lock);
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	_leave(" [queued]");
पूर्ण

/*
 * See अगर there's a cached RTT probe to complete.
 */
अटल व्योम rxrpc_complete_rtt_probe(काष्ठा rxrpc_call *call,
				     kसमय_प्रकार resp_समय,
				     rxrpc_serial_t acked_serial,
				     rxrpc_serial_t ack_serial,
				     क्रमागत rxrpc_rtt_rx_trace type)
अणु
	rxrpc_serial_t orig_serial;
	अचिन्हित दीर्घ avail;
	kसमय_प्रकार sent_at;
	bool matched = false;
	पूर्णांक i;

	avail = READ_ONCE(call->rtt_avail);
	smp_rmb(); /* Read avail bits beक्रमe accessing data. */

	क्रम (i = 0; i < ARRAY_SIZE(call->rtt_serial); i++) अणु
		अगर (!test_bit(i + RXRPC_CALL_RTT_PEND_SHIFT, &avail))
			जारी;

		sent_at = call->rtt_sent_at[i];
		orig_serial = call->rtt_serial[i];

		अगर (orig_serial == acked_serial) अणु
			clear_bit(i + RXRPC_CALL_RTT_PEND_SHIFT, &call->rtt_avail);
			smp_mb(); /* Read data beक्रमe setting avail bit */
			set_bit(i, &call->rtt_avail);
			अगर (type != rxrpc_rtt_rx_cancel)
				rxrpc_peer_add_rtt(call, type, i, acked_serial, ack_serial,
						   sent_at, resp_समय);
			अन्यथा
				trace_rxrpc_rtt_rx(call, rxrpc_rtt_rx_cancel, i,
						   orig_serial, acked_serial, 0, 0);
			matched = true;
		पूर्ण

		/* If a later serial is being acked, then mark this slot as
		 * being available.
		 */
		अगर (after(acked_serial, orig_serial)) अणु
			trace_rxrpc_rtt_rx(call, rxrpc_rtt_rx_obsolete, i,
					   orig_serial, acked_serial, 0, 0);
			clear_bit(i + RXRPC_CALL_RTT_PEND_SHIFT, &call->rtt_avail);
			smp_wmb();
			set_bit(i, &call->rtt_avail);
		पूर्ण
	पूर्ण

	अगर (!matched)
		trace_rxrpc_rtt_rx(call, rxrpc_rtt_rx_lost, 9, 0, acked_serial, 0, 0);
पूर्ण

/*
 * Process the response to a ping that we sent to find out अगर we lost an ACK.
 *
 * If we got back a ping response that indicates a lower tx_top than what we
 * had at the समय of the ping transmission, we adjudge all the DATA packets
 * sent between the response tx_top and the ping-समय tx_top to have been lost.
 */
अटल व्योम rxrpc_input_check_क्रम_lost_ack(काष्ठा rxrpc_call *call)
अणु
	rxrpc_seq_t top, bottom, seq;
	bool resend = false;

	spin_lock_bh(&call->lock);

	bottom = call->tx_hard_ack + 1;
	top = call->acks_lost_top;
	अगर (beक्रमe(bottom, top)) अणु
		क्रम (seq = bottom; beक्रमe_eq(seq, top); seq++) अणु
			पूर्णांक ix = seq & RXRPC_RXTX_BUFF_MASK;
			u8 annotation = call->rxtx_annotations[ix];
			u8 anno_type = annotation & RXRPC_TX_ANNO_MASK;

			अगर (anno_type != RXRPC_TX_ANNO_UNACK)
				जारी;
			annotation &= ~RXRPC_TX_ANNO_MASK;
			annotation |= RXRPC_TX_ANNO_RETRANS;
			call->rxtx_annotations[ix] = annotation;
			resend = true;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&call->lock);

	अगर (resend && !test_and_set_bit(RXRPC_CALL_EV_RESEND, &call->events))
		rxrpc_queue_call(call);
पूर्ण

/*
 * Process a ping response.
 */
अटल व्योम rxrpc_input_ping_response(काष्ठा rxrpc_call *call,
				      kसमय_प्रकार resp_समय,
				      rxrpc_serial_t acked_serial,
				      rxrpc_serial_t ack_serial)
अणु
	अगर (acked_serial == call->acks_lost_ping)
		rxrpc_input_check_क्रम_lost_ack(call);
पूर्ण

/*
 * Process the extra inक्रमmation that may be appended to an ACK packet
 */
अटल व्योम rxrpc_input_ackinfo(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb,
				काष्ठा rxrpc_ackinfo *ackinfo)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	काष्ठा rxrpc_peer *peer;
	अचिन्हित पूर्णांक mtu;
	bool wake = false;
	u32 rwind = ntohl(ackinfo->rwind);

	_proto("Rx ACK %%%u Info { rx=%u max=%u rwin=%u jm=%u }",
	       sp->hdr.serial,
	       ntohl(ackinfo->rxMTU), ntohl(ackinfo->maxMTU),
	       rwind, ntohl(ackinfo->jumbo_max));

	अगर (rwind > RXRPC_RXTX_BUFF_SIZE - 1)
		rwind = RXRPC_RXTX_BUFF_SIZE - 1;
	अगर (call->tx_winsize != rwind) अणु
		अगर (rwind > call->tx_winsize)
			wake = true;
		trace_rxrpc_rx_rwind_change(call, sp->hdr.serial, rwind, wake);
		call->tx_winsize = rwind;
	पूर्ण

	अगर (call->cong_ssthresh > rwind)
		call->cong_ssthresh = rwind;

	mtu = min(ntohl(ackinfo->rxMTU), ntohl(ackinfo->maxMTU));

	peer = call->peer;
	अगर (mtu < peer->maxdata) अणु
		spin_lock_bh(&peer->lock);
		peer->maxdata = mtu;
		peer->mtu = mtu + peer->hdrsize;
		spin_unlock_bh(&peer->lock);
		_net("Net MTU %u (maxdata %u)", peer->mtu, peer->maxdata);
	पूर्ण

	अगर (wake)
		wake_up(&call->रुकोq);
पूर्ण

/*
 * Process inभागidual soft ACKs.
 *
 * Each ACK in the array corresponds to one packet and can be either an ACK or
 * a NAK.  If we get find an explicitly NAK'd packet we resend immediately;
 * packets that lie beyond the end of the ACK list are scheduled क्रम resend by
 * the समयr on the basis that the peer might just not have processed them at
 * the समय the ACK was sent.
 */
अटल व्योम rxrpc_input_soft_acks(काष्ठा rxrpc_call *call, u8 *acks,
				  rxrpc_seq_t seq, पूर्णांक nr_acks,
				  काष्ठा rxrpc_ack_summary *summary)
अणु
	पूर्णांक ix;
	u8 annotation, anno_type;

	क्रम (; nr_acks > 0; nr_acks--, seq++) अणु
		ix = seq & RXRPC_RXTX_BUFF_MASK;
		annotation = call->rxtx_annotations[ix];
		anno_type = annotation & RXRPC_TX_ANNO_MASK;
		annotation &= ~RXRPC_TX_ANNO_MASK;
		चयन (*acks++) अणु
		हाल RXRPC_ACK_TYPE_ACK:
			summary->nr_acks++;
			अगर (anno_type == RXRPC_TX_ANNO_ACK)
				जारी;
			summary->nr_new_acks++;
			call->rxtx_annotations[ix] =
				RXRPC_TX_ANNO_ACK | annotation;
			अवरोध;
		हाल RXRPC_ACK_TYPE_NACK:
			अगर (!summary->nr_nacks &&
			    call->acks_lowest_nak != seq) अणु
				call->acks_lowest_nak = seq;
				summary->new_low_nack = true;
			पूर्ण
			summary->nr_nacks++;
			अगर (anno_type == RXRPC_TX_ANNO_NAK)
				जारी;
			summary->nr_new_nacks++;
			अगर (anno_type == RXRPC_TX_ANNO_RETRANS)
				जारी;
			call->rxtx_annotations[ix] =
				RXRPC_TX_ANNO_NAK | annotation;
			अवरोध;
		शेष:
			वापस rxrpc_proto_पात("SFT", call, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return true अगर the ACK is valid - ie. it करोesn't appear to have regressed
 * with respect to the ack state conveyed by preceding ACKs.
 */
अटल bool rxrpc_is_ack_valid(काष्ठा rxrpc_call *call,
			       rxrpc_seq_t first_pkt, rxrpc_seq_t prev_pkt)
अणु
	rxrpc_seq_t base = READ_ONCE(call->ackr_first_seq);

	अगर (after(first_pkt, base))
		वापस true; /* The winकरोw advanced */

	अगर (beक्रमe(first_pkt, base))
		वापस false; /* firstPacket regressed */

	अगर (after_eq(prev_pkt, call->ackr_prev_seq))
		वापस true; /* previousPacket hasn't regressed. */

	/* Some rx implementations put a serial number in previousPacket. */
	अगर (after_eq(prev_pkt, base + call->tx_winsize))
		वापस false;
	वापस true;
पूर्ण

/*
 * Process an ACK packet.
 *
 * ack.firstPacket is the sequence number of the first soft-ACK'd/NAK'd packet
 * in the ACK array.  Anything beक्रमe that is hard-ACK'd and may be discarded.
 *
 * A hard-ACK means that a packet has been processed and may be discarded; a
 * soft-ACK means that the packet may be discarded and retransmission
 * requested.  A phase is complete when all packets are hard-ACK'd.
 */
अटल व्योम rxrpc_input_ack(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_ack_summary summary = अणु 0 पूर्ण;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	जोड़ अणु
		काष्ठा rxrpc_ackpacket ack;
		काष्ठा rxrpc_ackinfo info;
		u8 acks[RXRPC_MAXACKS];
	पूर्ण buf;
	rxrpc_serial_t ack_serial, acked_serial;
	rxrpc_seq_t first_soft_ack, hard_ack, prev_pkt;
	पूर्णांक nr_acks, offset, ioffset;

	_enter("");

	offset = माप(काष्ठा rxrpc_wire_header);
	अगर (skb_copy_bits(skb, offset, &buf.ack, माप(buf.ack)) < 0) अणु
		_debug("extraction failure");
		वापस rxrpc_proto_पात("XAK", call, 0);
	पूर्ण
	offset += माप(buf.ack);

	ack_serial = sp->hdr.serial;
	acked_serial = ntohl(buf.ack.serial);
	first_soft_ack = ntohl(buf.ack.firstPacket);
	prev_pkt = ntohl(buf.ack.previousPacket);
	hard_ack = first_soft_ack - 1;
	nr_acks = buf.ack.nAcks;
	summary.ack_reason = (buf.ack.reason < RXRPC_ACK__INVALID ?
			      buf.ack.reason : RXRPC_ACK__INVALID);

	trace_rxrpc_rx_ack(call, ack_serial, acked_serial,
			   first_soft_ack, prev_pkt,
			   summary.ack_reason, nr_acks);

	चयन (buf.ack.reason) अणु
	हाल RXRPC_ACK_PING_RESPONSE:
		rxrpc_input_ping_response(call, skb->tstamp, acked_serial,
					  ack_serial);
		rxrpc_complete_rtt_probe(call, skb->tstamp, acked_serial, ack_serial,
					 rxrpc_rtt_rx_ping_response);
		अवरोध;
	हाल RXRPC_ACK_REQUESTED:
		rxrpc_complete_rtt_probe(call, skb->tstamp, acked_serial, ack_serial,
					 rxrpc_rtt_rx_requested_ack);
		अवरोध;
	शेष:
		अगर (acked_serial != 0)
			rxrpc_complete_rtt_probe(call, skb->tstamp, acked_serial, ack_serial,
						 rxrpc_rtt_rx_cancel);
		अवरोध;
	पूर्ण

	अगर (buf.ack.reason == RXRPC_ACK_PING) अणु
		_proto("Rx ACK %%%u PING Request", ack_serial);
		rxrpc_propose_ACK(call, RXRPC_ACK_PING_RESPONSE,
				  ack_serial, true, true,
				  rxrpc_propose_ack_respond_to_ping);
	पूर्ण अन्यथा अगर (sp->hdr.flags & RXRPC_REQUEST_ACK) अणु
		rxrpc_propose_ACK(call, RXRPC_ACK_REQUESTED,
				  ack_serial, true, true,
				  rxrpc_propose_ack_respond_to_ack);
	पूर्ण

	/* Discard any out-of-order or duplicate ACKs (outside lock). */
	अगर (!rxrpc_is_ack_valid(call, first_soft_ack, prev_pkt)) अणु
		trace_rxrpc_rx_discard_ack(call->debug_id, ack_serial,
					   first_soft_ack, call->ackr_first_seq,
					   prev_pkt, call->ackr_prev_seq);
		वापस;
	पूर्ण

	buf.info.rxMTU = 0;
	ioffset = offset + nr_acks + 3;
	अगर (skb->len >= ioffset + माप(buf.info) &&
	    skb_copy_bits(skb, ioffset, &buf.info, माप(buf.info)) < 0)
		वापस rxrpc_proto_पात("XAI", call, 0);

	spin_lock(&call->input_lock);

	/* Discard any out-of-order or duplicate ACKs (inside lock). */
	अगर (!rxrpc_is_ack_valid(call, first_soft_ack, prev_pkt)) अणु
		trace_rxrpc_rx_discard_ack(call->debug_id, ack_serial,
					   first_soft_ack, call->ackr_first_seq,
					   prev_pkt, call->ackr_prev_seq);
		जाओ out;
	पूर्ण
	call->acks_latest_ts = skb->tstamp;

	call->ackr_first_seq = first_soft_ack;
	call->ackr_prev_seq = prev_pkt;

	/* Parse rwind and mtu sizes अगर provided. */
	अगर (buf.info.rxMTU)
		rxrpc_input_ackinfo(call, skb, &buf.info);

	अगर (first_soft_ack == 0) अणु
		rxrpc_proto_पात("AK0", call, 0);
		जाओ out;
	पूर्ण

	/* Ignore ACKs unless we are or have just been transmitting. */
	चयन (READ_ONCE(call->state)) अणु
	हाल RXRPC_CALL_CLIENT_SEND_REQUEST:
	हाल RXRPC_CALL_CLIENT_AWAIT_REPLY:
	हाल RXRPC_CALL_SERVER_SEND_REPLY:
	हाल RXRPC_CALL_SERVER_AWAIT_ACK:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	अगर (beक्रमe(hard_ack, call->tx_hard_ack) ||
	    after(hard_ack, call->tx_top)) अणु
		rxrpc_proto_पात("AKW", call, 0);
		जाओ out;
	पूर्ण
	अगर (nr_acks > call->tx_top - hard_ack) अणु
		rxrpc_proto_पात("AKN", call, 0);
		जाओ out;
	पूर्ण

	अगर (after(hard_ack, call->tx_hard_ack)) अणु
		अगर (rxrpc_rotate_tx_winकरोw(call, hard_ack, &summary)) अणु
			rxrpc_end_tx_phase(call, false, "ETA");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (nr_acks > 0) अणु
		अगर (skb_copy_bits(skb, offset, buf.acks, nr_acks) < 0) अणु
			rxrpc_proto_पात("XSA", call, 0);
			जाओ out;
		पूर्ण
		rxrpc_input_soft_acks(call, buf.acks, first_soft_ack, nr_acks,
				      &summary);
	पूर्ण

	अगर (call->rxtx_annotations[call->tx_top & RXRPC_RXTX_BUFF_MASK] &
	    RXRPC_TX_ANNO_LAST &&
	    summary.nr_acks == call->tx_top - hard_ack &&
	    rxrpc_is_client_call(call))
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, ack_serial,
				  false, true,
				  rxrpc_propose_ack_ping_क्रम_lost_reply);

	rxrpc_congestion_management(call, skb, &summary, acked_serial);
out:
	spin_unlock(&call->input_lock);
पूर्ण

/*
 * Process an ACKALL packet.
 */
अटल व्योम rxrpc_input_ackall(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_ack_summary summary = अणु 0 पूर्ण;
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);

	_proto("Rx ACKALL %%%u", sp->hdr.serial);

	spin_lock(&call->input_lock);

	अगर (rxrpc_rotate_tx_winकरोw(call, call->tx_top, &summary))
		rxrpc_end_tx_phase(call, false, "ETL");

	spin_unlock(&call->input_lock);
पूर्ण

/*
 * Process an ABORT packet directed at a call.
 */
अटल व्योम rxrpc_input_पात(काष्ठा rxrpc_call *call, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	__be32 wपंचांगp;
	u32 पात_code = RX_CALL_DEAD;

	_enter("");

	अगर (skb->len >= 4 &&
	    skb_copy_bits(skb, माप(काष्ठा rxrpc_wire_header),
			  &wपंचांगp, माप(wपंचांगp)) >= 0)
		पात_code = ntohl(wपंचांगp);

	trace_rxrpc_rx_पात(call, sp->hdr.serial, पात_code);

	_proto("Rx ABORT %%%u { %x }", sp->hdr.serial, पात_code);

	rxrpc_set_call_completion(call, RXRPC_CALL_REMOTELY_ABORTED,
				  पात_code, -ECONNABORTED);
पूर्ण

/*
 * Process an incoming call packet.
 */
अटल व्योम rxrpc_input_call_packet(काष्ठा rxrpc_call *call,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_skb_priv *sp = rxrpc_skb(skb);
	अचिन्हित दीर्घ timo;

	_enter("%p,%p", call, skb);

	timo = READ_ONCE(call->next_rx_timo);
	अगर (timo) अणु
		अचिन्हित दीर्घ now = jअगरfies, expect_rx_by;

		expect_rx_by = now + timo;
		WRITE_ONCE(call->expect_rx_by, expect_rx_by);
		rxrpc_reduce_call_समयr(call, expect_rx_by, now,
					rxrpc_समयr_set_क्रम_normal);
	पूर्ण

	चयन (sp->hdr.type) अणु
	हाल RXRPC_PACKET_TYPE_DATA:
		rxrpc_input_data(call, skb);
		जाओ no_मुक्त;

	हाल RXRPC_PACKET_TYPE_ACK:
		rxrpc_input_ack(call, skb);
		अवरोध;

	हाल RXRPC_PACKET_TYPE_BUSY:
		_proto("Rx BUSY %%%u", sp->hdr.serial);

		/* Just ignore BUSY packets from the server; the retry and
		 * lअगरespan समयrs will take care of business.  BUSY packets
		 * from the client करोn't make sense.
		 */
		अवरोध;

	हाल RXRPC_PACKET_TYPE_ABORT:
		rxrpc_input_पात(call, skb);
		अवरोध;

	हाल RXRPC_PACKET_TYPE_ACKALL:
		rxrpc_input_ackall(call, skb);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
no_मुक्त:
	_leave("");
पूर्ण

/*
 * Handle a new service call on a channel implicitly completing the preceding
 * call on that channel.  This करोes not apply to client conns.
 *
 * TODO: If callNumber > call_id + 1, renegotiate security.
 */
अटल व्योम rxrpc_input_implicit_end_call(काष्ठा rxrpc_sock *rx,
					  काष्ठा rxrpc_connection *conn,
					  काष्ठा rxrpc_call *call)
अणु
	चयन (READ_ONCE(call->state)) अणु
	हाल RXRPC_CALL_SERVER_AWAIT_ACK:
		rxrpc_call_completed(call);
		fallthrough;
	हाल RXRPC_CALL_COMPLETE:
		अवरोध;
	शेष:
		अगर (rxrpc_पात_call("IMP", call, 0, RX_CALL_DEAD, -ESHUTDOWN)) अणु
			set_bit(RXRPC_CALL_EV_ABORT, &call->events);
			rxrpc_queue_call(call);
		पूर्ण
		trace_rxrpc_improper_term(call);
		अवरोध;
	पूर्ण

	spin_lock(&rx->incoming_lock);
	__rxrpc_disconnect_call(conn, call);
	spin_unlock(&rx->incoming_lock);
पूर्ण

/*
 * post connection-level events to the connection
 * - this includes challenges, responses, some पातs and call terminal packet
 *   retransmission.
 */
अटल व्योम rxrpc_post_packet_to_conn(काष्ठा rxrpc_connection *conn,
				      काष्ठा sk_buff *skb)
अणु
	_enter("%p,%p", conn, skb);

	skb_queue_tail(&conn->rx_queue, skb);
	rxrpc_queue_conn(conn);
पूर्ण

/*
 * post endpoपूर्णांक-level events to the local endpoपूर्णांक
 * - this includes debug and version messages
 */
अटल व्योम rxrpc_post_packet_to_local(काष्ठा rxrpc_local *local,
				       काष्ठा sk_buff *skb)
अणु
	_enter("%p,%p", local, skb);

	अगर (rxrpc_get_local_maybe(local)) अणु
		skb_queue_tail(&local->event_queue, skb);
		rxrpc_queue_local(local);
	पूर्ण अन्यथा अणु
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	पूर्ण
पूर्ण

/*
 * put a packet up क्रम transport-level पात
 */
अटल व्योम rxrpc_reject_packet(काष्ठा rxrpc_local *local, काष्ठा sk_buff *skb)
अणु
	CHECK_SLAB_OKAY(&local->usage);

	अगर (rxrpc_get_local_maybe(local)) अणु
		skb_queue_tail(&local->reject_queue, skb);
		rxrpc_queue_local(local);
	पूर्ण अन्यथा अणु
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	पूर्ण
पूर्ण

/*
 * Extract the wire header from a packet and translate the byte order.
 */
अटल noअंतरभूत
पूर्णांक rxrpc_extract_header(काष्ठा rxrpc_skb_priv *sp, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_wire_header whdr;

	/* dig out the RxRPC connection details */
	अगर (skb_copy_bits(skb, 0, &whdr, माप(whdr)) < 0) अणु
		trace_rxrpc_rx_eproto(शून्य, sp->hdr.serial,
				      tracepoपूर्णांक_string("bad_hdr"));
		वापस -EBADMSG;
	पूर्ण

	स_रखो(sp, 0, माप(*sp));
	sp->hdr.epoch		= ntohl(whdr.epoch);
	sp->hdr.cid		= ntohl(whdr.cid);
	sp->hdr.callNumber	= ntohl(whdr.callNumber);
	sp->hdr.seq		= ntohl(whdr.seq);
	sp->hdr.serial		= ntohl(whdr.serial);
	sp->hdr.flags		= whdr.flags;
	sp->hdr.type		= whdr.type;
	sp->hdr.userStatus	= whdr.userStatus;
	sp->hdr.securityIndex	= whdr.securityIndex;
	sp->hdr._rsvd		= ntohs(whdr._rsvd);
	sp->hdr.serviceId	= ntohs(whdr.serviceId);
	वापस 0;
पूर्ण

/*
 * handle data received on the local endpoपूर्णांक
 * - may be called in पूर्णांकerrupt context
 *
 * [!] Note that as this is called from the encap_rcv hook, the socket is not
 * held locked by the caller and nothing prevents sk_user_data on the UDP from
 * being cleared in the middle of processing this function.
 *
 * Called with the RCU पढ़ो lock held from the IP layer via UDP.
 */
पूर्णांक rxrpc_input_packet(काष्ठा sock *udp_sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxrpc_local *local = rcu_dereference_sk_user_data(udp_sk);
	काष्ठा rxrpc_connection *conn;
	काष्ठा rxrpc_channel *chan;
	काष्ठा rxrpc_call *call = शून्य;
	काष्ठा rxrpc_skb_priv *sp;
	काष्ठा rxrpc_peer *peer = शून्य;
	काष्ठा rxrpc_sock *rx = शून्य;
	अचिन्हित पूर्णांक channel;

	_enter("%p", udp_sk);

	अगर (unlikely(!local)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	अगर (skb->tstamp == 0)
		skb->tstamp = kसमय_get_real();

	rxrpc_new_skb(skb, rxrpc_skb_received);

	skb_pull(skb, माप(काष्ठा udphdr));

	/* The UDP protocol alपढ़ोy released all skb resources;
	 * we are मुक्त to add our own data there.
	 */
	sp = rxrpc_skb(skb);

	/* dig out the RxRPC connection details */
	अगर (rxrpc_extract_header(sp, skb) < 0)
		जाओ bad_message;

	अगर (IS_ENABLED(CONFIG_AF_RXRPC_INJECT_LOSS)) अणु
		अटल पूर्णांक lose;
		अगर ((lose++ & 7) == 7) अणु
			trace_rxrpc_rx_lose(sp);
			rxrpc_मुक्त_skb(skb, rxrpc_skb_lost);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (skb->tstamp == 0)
		skb->tstamp = kसमय_get_real();
	trace_rxrpc_rx_packet(sp);

	चयन (sp->hdr.type) अणु
	हाल RXRPC_PACKET_TYPE_VERSION:
		अगर (rxrpc_to_client(sp))
			जाओ discard;
		rxrpc_post_packet_to_local(local, skb);
		जाओ out;

	हाल RXRPC_PACKET_TYPE_BUSY:
		अगर (rxrpc_to_server(sp))
			जाओ discard;
		fallthrough;
	हाल RXRPC_PACKET_TYPE_ACK:
	हाल RXRPC_PACKET_TYPE_ACKALL:
		अगर (sp->hdr.callNumber == 0)
			जाओ bad_message;
		fallthrough;
	हाल RXRPC_PACKET_TYPE_ABORT:
		अवरोध;

	हाल RXRPC_PACKET_TYPE_DATA:
		अगर (sp->hdr.callNumber == 0 ||
		    sp->hdr.seq == 0)
			जाओ bad_message;
		अगर (!rxrpc_validate_data(skb))
			जाओ bad_message;

		/* Unshare the packet so that it can be modअगरied क्रम in-place
		 * decryption.
		 */
		अगर (sp->hdr.securityIndex != 0) अणु
			काष्ठा sk_buff *nskb = skb_unshare(skb, GFP_ATOMIC);
			अगर (!nskb) अणु
				rxrpc_eaten_skb(skb, rxrpc_skb_unshared_nomem);
				जाओ out;
			पूर्ण

			अगर (nskb != skb) अणु
				rxrpc_eaten_skb(skb, rxrpc_skb_received);
				skb = nskb;
				rxrpc_new_skb(skb, rxrpc_skb_unshared);
				sp = rxrpc_skb(skb);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल RXRPC_PACKET_TYPE_CHALLENGE:
		अगर (rxrpc_to_server(sp))
			जाओ discard;
		अवरोध;
	हाल RXRPC_PACKET_TYPE_RESPONSE:
		अगर (rxrpc_to_client(sp))
			जाओ discard;
		अवरोध;

		/* Packet types 9-11 should just be ignored. */
	हाल RXRPC_PACKET_TYPE_PARAMS:
	हाल RXRPC_PACKET_TYPE_10:
	हाल RXRPC_PACKET_TYPE_11:
		जाओ discard;

	शेष:
		_proto("Rx Bad Packet Type %u", sp->hdr.type);
		जाओ bad_message;
	पूर्ण

	अगर (sp->hdr.serviceId == 0)
		जाओ bad_message;

	अगर (rxrpc_to_server(sp)) अणु
		/* Weed out packets to services we're not offering.  Packets
		 * that would begin a call are explicitly rejected and the rest
		 * are just discarded.
		 */
		rx = rcu_dereference(local->service);
		अगर (!rx || (sp->hdr.serviceId != rx->srx.srx_service &&
			    sp->hdr.serviceId != rx->second_service)) अणु
			अगर (sp->hdr.type == RXRPC_PACKET_TYPE_DATA &&
			    sp->hdr.seq == 1)
				जाओ unsupported_service;
			जाओ discard;
		पूर्ण
	पूर्ण

	conn = rxrpc_find_connection_rcu(local, skb, &peer);
	अगर (conn) अणु
		अगर (sp->hdr.securityIndex != conn->security_ix)
			जाओ wrong_security;

		अगर (sp->hdr.serviceId != conn->service_id) अणु
			पूर्णांक old_id;

			अगर (!test_bit(RXRPC_CONN_PROBING_FOR_UPGRADE, &conn->flags))
				जाओ reupgrade;
			old_id = cmpxchg(&conn->service_id, conn->params.service_id,
					 sp->hdr.serviceId);

			अगर (old_id != conn->params.service_id &&
			    old_id != sp->hdr.serviceId)
				जाओ reupgrade;
		पूर्ण

		अगर (sp->hdr.callNumber == 0) अणु
			/* Connection-level packet */
			_debug("CONN %p {%d}", conn, conn->debug_id);
			rxrpc_post_packet_to_conn(conn, skb);
			जाओ out;
		पूर्ण

		अगर ((पूर्णांक)sp->hdr.serial - (पूर्णांक)conn->hi_serial > 0)
			conn->hi_serial = sp->hdr.serial;

		/* Call-bound packets are routed by connection channel. */
		channel = sp->hdr.cid & RXRPC_CHANNELMASK;
		chan = &conn->channels[channel];

		/* Ignore really old calls */
		अगर (sp->hdr.callNumber < chan->last_call)
			जाओ discard;

		अगर (sp->hdr.callNumber == chan->last_call) अणु
			अगर (chan->call ||
			    sp->hdr.type == RXRPC_PACKET_TYPE_ABORT)
				जाओ discard;

			/* For the previous service call, अगर completed
			 * successfully, we discard all further packets.
			 */
			अगर (rxrpc_conn_is_service(conn) &&
			    chan->last_type == RXRPC_PACKET_TYPE_ACK)
				जाओ discard;

			/* But otherwise we need to retransmit the final packet
			 * from data cached in the connection record.
			 */
			अगर (sp->hdr.type == RXRPC_PACKET_TYPE_DATA)
				trace_rxrpc_rx_data(chan->call_debug_id,
						    sp->hdr.seq,
						    sp->hdr.serial,
						    sp->hdr.flags, 0);
			rxrpc_post_packet_to_conn(conn, skb);
			जाओ out;
		पूर्ण

		call = rcu_dereference(chan->call);

		अगर (sp->hdr.callNumber > chan->call_id) अणु
			अगर (rxrpc_to_client(sp))
				जाओ reject_packet;
			अगर (call)
				rxrpc_input_implicit_end_call(rx, conn, call);
			call = शून्य;
		पूर्ण

		अगर (call) अणु
			अगर (sp->hdr.serviceId != call->service_id)
				call->service_id = sp->hdr.serviceId;
			अगर ((पूर्णांक)sp->hdr.serial - (पूर्णांक)call->rx_serial > 0)
				call->rx_serial = sp->hdr.serial;
			अगर (!test_bit(RXRPC_CALL_RX_HEARD, &call->flags))
				set_bit(RXRPC_CALL_RX_HEARD, &call->flags);
		पूर्ण
	पूर्ण

	अगर (!call || atomic_पढ़ो(&call->usage) == 0) अणु
		अगर (rxrpc_to_client(sp) ||
		    sp->hdr.type != RXRPC_PACKET_TYPE_DATA)
			जाओ bad_message;
		अगर (sp->hdr.seq != 1)
			जाओ discard;
		call = rxrpc_new_incoming_call(local, rx, skb);
		अगर (!call)
			जाओ reject_packet;
	पूर्ण

	/* Process a call packet; this either discards or passes on the ref
	 * अन्यथाwhere.
	 */
	rxrpc_input_call_packet(call, skb);
	जाओ out;

discard:
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
out:
	trace_rxrpc_rx_करोne(0, 0);
	वापस 0;

wrong_security:
	trace_rxrpc_पात(0, "SEC", sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
			  RXKADINCONSISTENCY, EBADMSG);
	skb->priority = RXKADINCONSISTENCY;
	जाओ post_पात;

unsupported_service:
	trace_rxrpc_पात(0, "INV", sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
			  RX_INVALID_OPERATION, EOPNOTSUPP);
	skb->priority = RX_INVALID_OPERATION;
	जाओ post_पात;

reupgrade:
	trace_rxrpc_पात(0, "UPG", sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
			  RX_PROTOCOL_ERROR, EBADMSG);
	जाओ protocol_error;

bad_message:
	trace_rxrpc_पात(0, "BAD", sp->hdr.cid, sp->hdr.callNumber, sp->hdr.seq,
			  RX_PROTOCOL_ERROR, EBADMSG);
protocol_error:
	skb->priority = RX_PROTOCOL_ERROR;
post_पात:
	skb->mark = RXRPC_SKB_MARK_REJECT_ABORT;
reject_packet:
	trace_rxrpc_rx_करोne(skb->mark, skb->priority);
	rxrpc_reject_packet(local, skb);
	_leave(" [badmsg]");
	वापस 0;
पूर्ण
