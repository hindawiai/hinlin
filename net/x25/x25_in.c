<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Jonathan Naylor	  Started coding.
 *	X.25 002	Jonathan Naylor	  Centralised disconnection code.
 *					  New समयr architecture.
 *	2000-03-20	Daniela Squassoni Disabling/enabling of facilities
 *					  negotiation.
 *	2000-11-10	Henner Eisen	  Check and reset क्रम out-of-sequence
 *					  i-frames.
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/x25.h>

अटल पूर्णांक x25_queue_rx_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक more)
अणु
	काष्ठा sk_buff *skbo, *skbn = skb;
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (more) अणु
		x25->fraglen += skb->len;
		skb_queue_tail(&x25->fragment_queue, skb);
		skb_set_owner_r(skb, sk);
		वापस 0;
	पूर्ण

	अगर (!more && x25->fraglen > 0) अणु	/* End of fragment */
		पूर्णांक len = x25->fraglen + skb->len;

		अगर ((skbn = alloc_skb(len, GFP_ATOMIC)) == शून्य)अणु
			kमुक्त_skb(skb);
			वापस 1;
		पूर्ण

		skb_queue_tail(&x25->fragment_queue, skb);

		skb_reset_transport_header(skbn);

		skbo = skb_dequeue(&x25->fragment_queue);
		skb_copy_from_linear_data(skbo, skb_put(skbn, skbo->len),
					  skbo->len);
		kमुक्त_skb(skbo);

		जबतक ((skbo =
			skb_dequeue(&x25->fragment_queue)) != शून्य) अणु
			skb_pull(skbo, (x25->neighbour->extended) ?
					X25_EXT_MIN_LEN : X25_STD_MIN_LEN);
			skb_copy_from_linear_data(skbo,
						  skb_put(skbn, skbo->len),
						  skbo->len);
			kमुक्त_skb(skbo);
		पूर्ण

		x25->fraglen = 0;
	पूर्ण

	skb_set_owner_r(skbn, sk);
	skb_queue_tail(&sk->sk_receive_queue, skbn);
	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);

	वापस 0;
पूर्ण

/*
 * State machine क्रम state 1, Aरुकोing Call Accepted State.
 * The handling of the समयr(s) is in file x25_समयr.c.
 * Handling of state 0 and connection release is in af_x25.c.
 */
अटल पूर्णांक x25_state1_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा x25_address source_addr, dest_addr;
	पूर्णांक len;
	काष्ठा x25_sock *x25 = x25_sk(sk);

	चयन (frametype) अणु
	हाल X25_CALL_ACCEPTED: अणु

		x25_stop_समयr(sk);
		x25->condition = 0x00;
		x25->vs        = 0;
		x25->va        = 0;
		x25->vr        = 0;
		x25->vl        = 0;
		x25->state     = X25_STATE_3;
		sk->sk_state   = TCP_ESTABLISHED;
		/*
		 *	Parse the data in the frame.
		 */
		अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN))
			जाओ out_clear;
		skb_pull(skb, X25_STD_MIN_LEN);

		len = x25_parse_address_block(skb, &source_addr,
					      &dest_addr);
		अगर (len > 0)
			skb_pull(skb, len);
		अन्यथा अगर (len < 0)
			जाओ out_clear;

		len = x25_parse_facilities(skb, &x25->facilities,
					   &x25->dte_facilities,
					   &x25->vc_facil_mask);
		अगर (len > 0)
			skb_pull(skb, len);
		अन्यथा अगर (len < 0)
			जाओ out_clear;
		/*
		 *	Copy any Call User Data.
		 */
		अगर (skb->len > 0) अणु
			अगर (skb->len > X25_MAX_CUD_LEN)
				जाओ out_clear;

			skb_copy_bits(skb, 0, x25->calluserdata.cuddata,
				skb->len);
			x25->calluserdata.cudlength = skb->len;
		पूर्ण
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अवरोध;
	पूर्ण
	हाल X25_CALL_REQUEST:
		/* call collision */
		x25->causediag.cause      = 0x01;
		x25->causediag.diagnostic = 0x48;

		x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
		x25_disconnect(sk, EISCONN, 0x01, 0x48);
		अवरोध;

	हाल X25_CLEAR_REQUEST:
		अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2))
			जाओ out_clear;

		x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_CONFIRMATION);
		x25_disconnect(sk, ECONNREFUSED, skb->data[3], skb->data[4]);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

out_clear:
	x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
	x25->state = X25_STATE_2;
	x25_start_t23समयr(sk);
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 2, Aरुकोing Clear Confirmation State.
 * The handling of the समयr(s) is in file x25_समयr.c
 * Handling of state 0 and connection release is in af_x25.c.
 */
अटल पूर्णांक x25_state2_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	चयन (frametype) अणु

		हाल X25_CLEAR_REQUEST:
			अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2))
				जाओ out_clear;

			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			अवरोध;

		हाल X25_CLEAR_CONFIRMATION:
			x25_disconnect(sk, 0, 0, 0);
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण

	वापस 0;

out_clear:
	x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
	x25_start_t23समयr(sk);
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 3, Connected State.
 * The handling of the समयr(s) is in file x25_समयr.c
 * Handling of state 0 and connection release is in af_x25.c.
 */
अटल पूर्णांक x25_state3_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype, पूर्णांक ns, पूर्णांक nr, पूर्णांक q, पूर्णांक d, पूर्णांक m)
अणु
	पूर्णांक queued = 0;
	पूर्णांक modulus;
	काष्ठा x25_sock *x25 = x25_sk(sk);

	modulus = (x25->neighbour->extended) ? X25_EMODULUS : X25_SMODULUS;

	चयन (frametype) अणु

		हाल X25_RESET_REQUEST:
			x25_ग_लिखो_पूर्णांकernal(sk, X25_RESET_CONFIRMATION);
			x25_stop_समयr(sk);
			x25->condition = 0x00;
			x25->vs        = 0;
			x25->vr        = 0;
			x25->va        = 0;
			x25->vl        = 0;
			x25_requeue_frames(sk);
			अवरोध;

		हाल X25_CLEAR_REQUEST:
			अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2))
				जाओ out_clear;

			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			अवरोध;

		हाल X25_RR:
		हाल X25_RNR:
			अगर (!x25_validate_nr(sk, nr)) अणु
				x25_clear_queues(sk);
				x25_ग_लिखो_पूर्णांकernal(sk, X25_RESET_REQUEST);
				x25_start_t22समयr(sk);
				x25->condition = 0x00;
				x25->vs        = 0;
				x25->vr        = 0;
				x25->va        = 0;
				x25->vl        = 0;
				x25->state     = X25_STATE_4;
			पूर्ण अन्यथा अणु
				x25_frames_acked(sk, nr);
				अगर (frametype == X25_RNR) अणु
					x25->condition |= X25_COND_PEER_RX_BUSY;
				पूर्ण अन्यथा अणु
					x25->condition &= ~X25_COND_PEER_RX_BUSY;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल X25_DATA:	/* XXX */
			x25->condition &= ~X25_COND_PEER_RX_BUSY;
			अगर ((ns != x25->vr) || !x25_validate_nr(sk, nr)) अणु
				x25_clear_queues(sk);
				x25_ग_लिखो_पूर्णांकernal(sk, X25_RESET_REQUEST);
				x25_start_t22समयr(sk);
				x25->condition = 0x00;
				x25->vs        = 0;
				x25->vr        = 0;
				x25->va        = 0;
				x25->vl        = 0;
				x25->state     = X25_STATE_4;
				अवरोध;
			पूर्ण
			x25_frames_acked(sk, nr);
			अगर (ns == x25->vr) अणु
				अगर (x25_queue_rx_frame(sk, skb, m) == 0) अणु
					x25->vr = (x25->vr + 1) % modulus;
					queued = 1;
				पूर्ण अन्यथा अणु
					/* Should never happen */
					x25_clear_queues(sk);
					x25_ग_लिखो_पूर्णांकernal(sk, X25_RESET_REQUEST);
					x25_start_t22समयr(sk);
					x25->condition = 0x00;
					x25->vs        = 0;
					x25->vr        = 0;
					x25->va        = 0;
					x25->vl        = 0;
					x25->state     = X25_STATE_4;
					अवरोध;
				पूर्ण
				अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >
				    (sk->sk_rcvbuf >> 1))
					x25->condition |= X25_COND_OWN_RX_BUSY;
			पूर्ण
			/*
			 *	If the winकरोw is full Ack it immediately, अन्यथा
			 *	start the holdback समयr.
			 */
			अगर (((x25->vl + x25->facilities.winsize_in) % modulus) == x25->vr) अणु
				x25->condition &= ~X25_COND_ACK_PENDING;
				x25_stop_समयr(sk);
				x25_enquiry_response(sk);
			पूर्ण अन्यथा अणु
				x25->condition |= X25_COND_ACK_PENDING;
				x25_start_t2समयr(sk);
			पूर्ण
			अवरोध;

		हाल X25_INTERRUPT_CONFIRMATION:
			clear_bit(X25_INTERRUPT_FLAG, &x25->flags);
			अवरोध;

		हाल X25_INTERRUPT:
			अगर (sock_flag(sk, SOCK_URGINLINE))
				queued = !sock_queue_rcv_skb(sk, skb);
			अन्यथा अणु
				skb_set_owner_r(skb, sk);
				skb_queue_tail(&x25->पूर्णांकerrupt_in_queue, skb);
				queued = 1;
			पूर्ण
			sk_send_sigurg(sk);
			x25_ग_लिखो_पूर्णांकernal(sk, X25_INTERRUPT_CONFIRMATION);
			अवरोध;

		शेष:
			pr_warn("unknown %02X in state 3\n", frametype);
			अवरोध;
	पूर्ण

	वापस queued;

out_clear:
	x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
	x25->state = X25_STATE_2;
	x25_start_t23समयr(sk);
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 4, Aरुकोing Reset Confirmation State.
 * The handling of the समयr(s) is in file x25_समयr.c
 * Handling of state 0 and connection release is in af_x25.c.
 */
अटल पूर्णांक x25_state4_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	चयन (frametype) अणु

		हाल X25_RESET_REQUEST:
			x25_ग_लिखो_पूर्णांकernal(sk, X25_RESET_CONFIRMATION);
			fallthrough;
		हाल X25_RESET_CONFIRMATION: अणु
			x25_stop_समयr(sk);
			x25->condition = 0x00;
			x25->va        = 0;
			x25->vr        = 0;
			x25->vs        = 0;
			x25->vl        = 0;
			x25->state     = X25_STATE_3;
			x25_requeue_frames(sk);
			अवरोध;
		पूर्ण
		हाल X25_CLEAR_REQUEST:
			अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2))
				जाओ out_clear;

			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण

	वापस 0;

out_clear:
	x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
	x25->state = X25_STATE_2;
	x25_start_t23समयr(sk);
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 5, Call Accepted / Call Connected pending (X25_ACCPT_APPRV_FLAG).
 * The handling of the समयr(s) is in file x25_समयr.c
 * Handling of state 0 and connection release is in af_x25.c.
 */
अटल पूर्णांक x25_state5_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	चयन (frametype) अणु
		हाल X25_CLEAR_REQUEST:
			अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2)) अणु
				x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
				x25->state = X25_STATE_2;
				x25_start_t23समयr(sk);
				वापस 0;
			पूर्ण

			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Higher level upcall क्रम a LAPB frame */
पूर्णांक x25_process_rx_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);
	पूर्णांक queued = 0, frametype, ns, nr, q, d, m;

	अगर (x25->state == X25_STATE_0)
		वापस 0;

	frametype = x25_decode(sk, skb, &ns, &nr, &q, &d, &m);

	चयन (x25->state) अणु
	हाल X25_STATE_1:
		queued = x25_state1_machine(sk, skb, frametype);
		अवरोध;
	हाल X25_STATE_2:
		queued = x25_state2_machine(sk, skb, frametype);
		अवरोध;
	हाल X25_STATE_3:
		queued = x25_state3_machine(sk, skb, frametype, ns, nr, q, d, m);
		अवरोध;
	हाल X25_STATE_4:
		queued = x25_state4_machine(sk, skb, frametype);
		अवरोध;
	हाल X25_STATE_5:
		queued = x25_state5_machine(sk, skb, frametype);
		अवरोध;
	पूर्ण

	x25_kick(sk);

	वापस queued;
पूर्ण

पूर्णांक x25_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक queued = x25_process_rx_frame(sk, skb);

	अगर (!queued)
		kमुक्त_skb(skb);

	वापस 0;
पूर्ण
