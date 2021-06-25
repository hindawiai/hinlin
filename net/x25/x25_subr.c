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
 *	X.25 002	Jonathan Naylor	  Centralised disconnection processing.
 *	mar/20/00	Daniela Squassoni Disabling/enabling of facilities
 *					  negotiation.
 *	jun/24/01	Arnalकरो C. Melo	  use skb_queue_purge, cleanups
 *	apr/04/15	Shaun Pereira		Fast select with no
 *						restriction on response.
 */

#घोषणा pr_fmt(fmt) "X25: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/x25.h>

/*
 *	This routine purges all of the queues of frames.
 */
व्योम x25_clear_queues(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	skb_queue_purge(&sk->sk_ग_लिखो_queue);
	skb_queue_purge(&x25->ack_queue);
	skb_queue_purge(&x25->पूर्णांकerrupt_in_queue);
	skb_queue_purge(&x25->पूर्णांकerrupt_out_queue);
	skb_queue_purge(&x25->fragment_queue);
पूर्ण


/*
 * This routine purges the input queue of those frames that have been
 * acknowledged. This replaces the boxes labelled "V(a) <- N(r)" on the
 * SDL diagram.
*/
व्योम x25_frames_acked(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा x25_sock *x25 = x25_sk(sk);
	पूर्णांक modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	अगर (x25->va != nr)
		जबतक (skb_peek(&x25->ack_queue) && x25->va != nr) अणु
			skb = skb_dequeue(&x25->ack_queue);
			kमुक्त_skb(skb);
			x25->va = (x25->va + 1) % modulus;
		पूर्ण
पूर्ण

व्योम x25_requeue_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *skb_prev = शून्य;

	/*
	 * Requeue all the un-ack-ed frames on the output queue to be picked
	 * up by x25_kick. This arrangement handles the possibility of an empty
	 * output queue.
	 */
	जबतक ((skb = skb_dequeue(&x25_sk(sk)->ack_queue)) != शून्य) अणु
		अगर (!skb_prev)
			skb_queue_head(&sk->sk_ग_लिखो_queue, skb);
		अन्यथा
			skb_append(skb_prev, skb, &sk->sk_ग_लिखो_queue);
		skb_prev = skb;
	पूर्ण
पूर्ण

/*
 *	Validate that the value of nr is between va and vs. Return true or
 *	false क्रम testing.
 */
पूर्णांक x25_validate_nr(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);
	अचिन्हित लघु vc = x25->va;
	पूर्णांक modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	जबतक (vc != x25->vs) अणु
		अगर (nr == vc)
			वापस 1;
		vc = (vc + 1) % modulus;
	पूर्ण

	वापस nr == x25->vs ? 1 : 0;
पूर्ण

/*
 *  This routine is called when the packet layer पूर्णांकernally generates a
 *  control frame.
 */
व्योम x25_ग_लिखो_पूर्णांकernal(काष्ठा sock *sk, पूर्णांक frametype)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;
	अचिन्हित अक्षर  facilities[X25_MAX_FAC_LEN];
	अचिन्हित अक्षर  addresses[1 + X25_ADDR_LEN];
	अचिन्हित अक्षर  lci1, lci2;
	/*
	 *	Default safe frame size.
	 */
	पूर्णांक len = X25_MAX_L2_LEN + X25_EXT_MIN_LEN;

	/*
	 *	Adjust frame size.
	 */
	चयन (frametype) अणु
	हाल X25_CALL_REQUEST:
		len += 1 + X25_ADDR_LEN + X25_MAX_FAC_LEN + X25_MAX_CUD_LEN;
		अवरोध;
	हाल X25_CALL_ACCEPTED: /* fast sel with no restr on resp */
		अगर (x25->facilities.reverse & 0x80) अणु
			len += 1 + X25_MAX_FAC_LEN + X25_MAX_CUD_LEN;
		पूर्ण अन्यथा अणु
			len += 1 + X25_MAX_FAC_LEN;
		पूर्ण
		अवरोध;
	हाल X25_CLEAR_REQUEST:
	हाल X25_RESET_REQUEST:
		len += 2;
		अवरोध;
	हाल X25_RR:
	हाल X25_RNR:
	हाल X25_REJ:
	हाल X25_CLEAR_CONFIRMATION:
	हाल X25_INTERRUPT_CONFIRMATION:
	हाल X25_RESET_CONFIRMATION:
		अवरोध;
	शेष:
		pr_err("invalid frame type %02X\n", frametype);
		वापस;
	पूर्ण

	अगर ((skb = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	/*
	 *	Space क्रम Ethernet and 802.2 LLC headers.
	 */
	skb_reserve(skb, X25_MAX_L2_LEN);

	/*
	 *	Make space क्रम the GFI and LCI, and fill them in.
	 */
	dptr = skb_put(skb, 2);

	lci1 = (x25->lci >> 8) & 0x0F;
	lci2 = (x25->lci >> 0) & 0xFF;

	अगर (x25->neighbour->extended) अणु
		*dptr++ = lci1 | X25_GFI_EXTSEQ;
		*dptr++ = lci2;
	पूर्ण अन्यथा अणु
		*dptr++ = lci1 | X25_GFI_STDSEQ;
		*dptr++ = lci2;
	पूर्ण

	/*
	 *	Now fill in the frame type specअगरic inक्रमmation.
	 */
	चयन (frametype) अणु

		हाल X25_CALL_REQUEST:
			dptr    = skb_put(skb, 1);
			*dptr++ = X25_CALL_REQUEST;
			len     = x25_addr_aton(addresses, &x25->dest_addr,
						&x25->source_addr);
			skb_put_data(skb, addresses, len);
			len     = x25_create_facilities(facilities,
					&x25->facilities,
					&x25->dte_facilities,
					x25->neighbour->global_facil_mask);
			skb_put_data(skb, facilities, len);
			skb_put_data(skb, x25->calluserdata.cuddata,
				     x25->calluserdata.cudlength);
			x25->calluserdata.cudlength = 0;
			अवरोध;

		हाल X25_CALL_ACCEPTED:
			dptr    = skb_put(skb, 2);
			*dptr++ = X25_CALL_ACCEPTED;
			*dptr++ = 0x00;		/* Address lengths */
			len     = x25_create_facilities(facilities,
							&x25->facilities,
							&x25->dte_facilities,
							x25->vc_facil_mask);
			skb_put_data(skb, facilities, len);

			/* fast select with no restriction on response
				allows call user data. Userland must
				ensure it is ours and not theirs */
			अगर(x25->facilities.reverse & 0x80) अणु
				skb_put_data(skb,
					     x25->calluserdata.cuddata,
					     x25->calluserdata.cudlength);
			पूर्ण
			x25->calluserdata.cudlength = 0;
			अवरोध;

		हाल X25_CLEAR_REQUEST:
			dptr    = skb_put(skb, 3);
			*dptr++ = frametype;
			*dptr++ = x25->causediag.cause;
			*dptr++ = x25->causediag.diagnostic;
			अवरोध;

		हाल X25_RESET_REQUEST:
			dptr    = skb_put(skb, 3);
			*dptr++ = frametype;
			*dptr++ = 0x00;		/* XXX */
			*dptr++ = 0x00;		/* XXX */
			अवरोध;

		हाल X25_RR:
		हाल X25_RNR:
		हाल X25_REJ:
			अगर (x25->neighbour->extended) अणु
				dptr     = skb_put(skb, 2);
				*dptr++  = frametype;
				*dptr++  = (x25->vr << 1) & 0xFE;
			पूर्ण अन्यथा अणु
				dptr     = skb_put(skb, 1);
				*dptr    = frametype;
				*dptr++ |= (x25->vr << 5) & 0xE0;
			पूर्ण
			अवरोध;

		हाल X25_CLEAR_CONFIRMATION:
		हाल X25_INTERRUPT_CONFIRMATION:
		हाल X25_RESET_CONFIRMATION:
			dptr  = skb_put(skb, 1);
			*dptr = frametype;
			अवरोध;
	पूर्ण

	x25_transmit_link(skb, x25->neighbour);
पूर्ण

/*
 *	Unpick the contents of the passed X.25 Packet Layer frame.
 */
पूर्णांक x25_decode(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक *ns, पूर्णांक *nr, पूर्णांक *q,
	       पूर्णांक *d, पूर्णांक *m)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);
	अचिन्हित अक्षर *frame;

	अगर (!pskb_may_pull(skb, X25_STD_MIN_LEN))
		वापस X25_ILLEGAL;
	frame = skb->data;

	*ns = *nr = *q = *d = *m = 0;

	चयन (frame[2]) अणु
	हाल X25_CALL_REQUEST:
	हाल X25_CALL_ACCEPTED:
	हाल X25_CLEAR_REQUEST:
	हाल X25_CLEAR_CONFIRMATION:
	हाल X25_INTERRUPT:
	हाल X25_INTERRUPT_CONFIRMATION:
	हाल X25_RESET_REQUEST:
	हाल X25_RESET_CONFIRMATION:
	हाल X25_RESTART_REQUEST:
	हाल X25_RESTART_CONFIRMATION:
	हाल X25_REGISTRATION_REQUEST:
	हाल X25_REGISTRATION_CONFIRMATION:
	हाल X25_DIAGNOSTIC:
		वापस frame[2];
	पूर्ण

	अगर (x25->neighbour->extended) अणु
		अगर (frame[2] == X25_RR  ||
		    frame[2] == X25_RNR ||
		    frame[2] == X25_REJ) अणु
			अगर (!pskb_may_pull(skb, X25_EXT_MIN_LEN))
				वापस X25_ILLEGAL;
			frame = skb->data;

			*nr = (frame[3] >> 1) & 0x7F;
			वापस frame[2];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((frame[2] & 0x1F) == X25_RR  ||
		    (frame[2] & 0x1F) == X25_RNR ||
		    (frame[2] & 0x1F) == X25_REJ) अणु
			*nr = (frame[2] >> 5) & 0x07;
			वापस frame[2] & 0x1F;
		पूर्ण
	पूर्ण

	अगर (x25->neighbour->extended) अणु
		अगर ((frame[2] & 0x01) == X25_DATA) अणु
			अगर (!pskb_may_pull(skb, X25_EXT_MIN_LEN))
				वापस X25_ILLEGAL;
			frame = skb->data;

			*q  = (frame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (frame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (frame[3] & X25_EXT_M_BIT) == X25_EXT_M_BIT;
			*nr = (frame[3] >> 1) & 0x7F;
			*ns = (frame[2] >> 1) & 0x7F;
			वापस X25_DATA;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((frame[2] & 0x01) == X25_DATA) अणु
			*q  = (frame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (frame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (frame[2] & X25_STD_M_BIT) == X25_STD_M_BIT;
			*nr = (frame[2] >> 5) & 0x07;
			*ns = (frame[2] >> 1) & 0x07;
			वापस X25_DATA;
		पूर्ण
	पूर्ण

	pr_debug("invalid PLP frame %3ph\n", frame);

	वापस X25_ILLEGAL;
पूर्ण

व्योम x25_disconnect(काष्ठा sock *sk, पूर्णांक reason, अचिन्हित अक्षर cause,
		    अचिन्हित अक्षर diagnostic)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	x25_clear_queues(sk);
	x25_stop_समयr(sk);

	x25->lci   = 0;
	x25->state = X25_STATE_0;

	x25->causediag.cause      = cause;
	x25->causediag.diagnostic = diagnostic;

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = reason;
	sk->sk_shutकरोwn |= SEND_SHUTDOWN;

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	पूर्ण
	अगर (x25->neighbour) अणु
		पढ़ो_lock_bh(&x25_list_lock);
		x25_neigh_put(x25->neighbour);
		x25->neighbour = शून्य;
		पढ़ो_unlock_bh(&x25_list_lock);
	पूर्ण
पूर्ण

/*
 * Clear an own-rx-busy condition and tell the peer about this, provided
 * that there is a signअगरicant amount of मुक्त receive buffer space available.
 */
व्योम x25_check_rbuf(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) < (sk->sk_rcvbuf >> 1) &&
	    (x25->condition & X25_COND_OWN_RX_BUSY)) अणु
		x25->condition &= ~X25_COND_OWN_RX_BUSY;
		x25->condition &= ~X25_COND_ACK_PENDING;
		x25->vl         = x25->vr;
		x25_ग_लिखो_पूर्णांकernal(sk, X25_RR);
		x25_stop_समयr(sk);
	पूर्ण
पूर्ण
