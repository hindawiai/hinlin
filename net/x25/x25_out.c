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
 *	X.25 001	Jonathan Naylor	Started coding.
 *	X.25 002	Jonathan Naylor	New समयr architecture.
 *	2000-09-04	Henner Eisen	Prevented x25_output() skb leakage.
 *	2000-10-27	Henner Eisen	MSG_DONTWAIT क्रम fragment allocation.
 *	2000-11-10	Henner Eisen	x25_send_अगरrame(): re-queued frames
 *					needed cleaned seq-number fields.
 */

#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/x25.h>

अटल पूर्णांक x25_pacमाप_प्रकारo_bytes(अचिन्हित पूर्णांक pacsize)
अणु
	पूर्णांक bytes = 1;

	अगर (!pacsize)
		वापस 128;

	जबतक (pacsize-- > 0)
		bytes *= 2;

	वापस bytes;
पूर्ण

/*
 *	This is where all X.25 inक्रमmation frames pass.
 *
 *      Returns the amount of user data bytes sent on success
 *      or a negative error code on failure.
 */
पूर्णांक x25_output(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर header[X25_EXT_MIN_LEN];
	पूर्णांक err, frontlen, len;
	पूर्णांक sent=0, noblock = X25_SKB_CB(skb)->flags & MSG_DONTWAIT;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	पूर्णांक header_len = x25->neighbour->extended ? X25_EXT_MIN_LEN :
						    X25_STD_MIN_LEN;
	पूर्णांक max_len = x25_pacमाप_प्रकारo_bytes(x25->facilities.pacsize_out);

	अगर (skb->len - header_len > max_len) अणु
		/* Save a copy of the Header */
		skb_copy_from_linear_data(skb, header, header_len);
		skb_pull(skb, header_len);

		frontlen = skb_headroom(skb);

		जबतक (skb->len > 0) अणु
			release_sock(sk);
			skbn = sock_alloc_send_skb(sk, frontlen + max_len,
						   noblock, &err);
			lock_sock(sk);
			अगर (!skbn) अणु
				अगर (err == -EWOULDBLOCK && noblock)अणु
					kमुक्त_skb(skb);
					वापस sent;
				पूर्ण
				SOCK_DEBUG(sk, "x25_output: fragment alloc"
					       " failed, err=%d, %d bytes "
					       "sent\n", err, sent);
				वापस err;
			पूर्ण

			skb_reserve(skbn, frontlen);

			len = max_len > skb->len ? skb->len : max_len;

			/* Copy the user data */
			skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
			skb_pull(skb, len);

			/* Duplicate the Header */
			skb_push(skbn, header_len);
			skb_copy_to_linear_data(skbn, header, header_len);

			अगर (skb->len > 0) अणु
				अगर (x25->neighbour->extended)
					skbn->data[3] |= X25_EXT_M_BIT;
				अन्यथा
					skbn->data[2] |= X25_STD_M_BIT;
			पूर्ण

			skb_queue_tail(&sk->sk_ग_लिखो_queue, skbn);
			sent += len;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
		sent = skb->len - header_len;
	पूर्ण
	वापस sent;
पूर्ण

/*
 *	This procedure is passed a buffer descriptor क्रम an अगरrame. It builds
 *	the rest of the control part of the frame and then ग_लिखोs it out.
 */
अटल व्योम x25_send_अगरrame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (!skb)
		वापस;

	अगर (x25->neighbour->extended) अणु
		skb->data[2]  = (x25->vs << 1) & 0xFE;
		skb->data[3] &= X25_EXT_M_BIT;
		skb->data[3] |= (x25->vr << 1) & 0xFE;
	पूर्ण अन्यथा अणु
		skb->data[2] &= X25_STD_M_BIT;
		skb->data[2] |= (x25->vs << 1) & 0x0E;
		skb->data[2] |= (x25->vr << 5) & 0xE0;
	पूर्ण

	x25_transmit_link(skb, x25->neighbour);
पूर्ण

व्योम x25_kick(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *skbn;
	अचिन्हित लघु start, end;
	पूर्णांक modulus;
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (x25->state != X25_STATE_3)
		वापस;

	/*
	 *	Transmit पूर्णांकerrupt data.
	 */
	अगर (skb_peek(&x25->पूर्णांकerrupt_out_queue) != शून्य &&
		!test_and_set_bit(X25_INTERRUPT_FLAG, &x25->flags)) अणु

		skb = skb_dequeue(&x25->पूर्णांकerrupt_out_queue);
		x25_transmit_link(skb, x25->neighbour);
	पूर्ण

	अगर (x25->condition & X25_COND_PEER_RX_BUSY)
		वापस;

	अगर (!skb_peek(&sk->sk_ग_लिखो_queue))
		वापस;

	modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	start   = skb_peek(&x25->ack_queue) ? x25->vs : x25->va;
	end     = (x25->va + x25->facilities.winsize_out) % modulus;

	अगर (start == end)
		वापस;

	x25->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the winकरोw is full.
	 */

	skb = skb_dequeue(&sk->sk_ग_लिखो_queue);

	करो अणु
		अगर ((skbn = skb_clone(skb, GFP_ATOMIC)) == शून्य) अणु
			skb_queue_head(&sk->sk_ग_लिखो_queue, skb);
			अवरोध;
		पूर्ण

		skb_set_owner_w(skbn, sk);

		/*
		 * Transmit the frame copy.
		 */
		x25_send_अगरrame(sk, skbn);

		x25->vs = (x25->vs + 1) % modulus;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&x25->ack_queue, skb);

	पूर्ण जबतक (x25->vs != end &&
		 (skb = skb_dequeue(&sk->sk_ग_लिखो_queue)) != शून्य);

	x25->vl         = x25->vr;
	x25->condition &= ~X25_COND_ACK_PENDING;

	x25_stop_समयr(sk);
पूर्ण

/*
 * The following routines are taken from page 170 of the 7th ARRL Computer
 * Networking Conference paper, as is the whole state machine.
 */

व्योम x25_enquiry_response(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (x25->condition & X25_COND_OWN_RX_BUSY)
		x25_ग_लिखो_पूर्णांकernal(sk, X25_RNR);
	अन्यथा
		x25_ग_लिखो_पूर्णांकernal(sk, X25_RR);

	x25->vl         = x25->vr;
	x25->condition &= ~X25_COND_ACK_PENDING;

	x25_stop_समयr(sk);
पूर्ण
