<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/netrom.h>

/*
 *	This routine purges all of the queues of frames.
 */
व्योम nr_clear_queues(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	skb_queue_purge(&sk->sk_ग_लिखो_queue);
	skb_queue_purge(&nr->ack_queue);
	skb_queue_purge(&nr->reseq_queue);
	skb_queue_purge(&nr->frag_queue);
पूर्ण

/*
 * This routine purges the input queue of those frames that have been
 * acknowledged. This replaces the boxes labelled "V(a) <- N(r)" on the
 * SDL diagram.
 */
व्योम nr_frames_acked(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा nr_sock *nrom = nr_sk(sk);
	काष्ठा sk_buff *skb;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	अगर (nrom->va != nr) अणु
		जबतक (skb_peek(&nrom->ack_queue) != शून्य && nrom->va != nr) अणु
			skb = skb_dequeue(&nrom->ack_queue);
			kमुक्त_skb(skb);
			nrom->va = (nrom->va + 1) % NR_MODULUS;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Requeue all the un-ack-ed frames on the output queue to be picked
 * up by nr_kick called from the समयr. This arrangement handles the
 * possibility of an empty output queue.
 */
व्योम nr_requeue_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *skb_prev = शून्य;

	जबतक ((skb = skb_dequeue(&nr_sk(sk)->ack_queue)) != शून्य) अणु
		अगर (skb_prev == शून्य)
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
पूर्णांक nr_validate_nr(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा nr_sock *nrom = nr_sk(sk);
	अचिन्हित लघु vc = nrom->va;

	जबतक (vc != nrom->vs) अणु
		अगर (nr == vc) वापस 1;
		vc = (vc + 1) % NR_MODULUS;
	पूर्ण

	वापस nr == nrom->vs;
पूर्ण

/*
 *	Check that ns is within the receive winकरोw.
 */
पूर्णांक nr_in_rx_winकरोw(काष्ठा sock *sk, अचिन्हित लघु ns)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	अचिन्हित लघु vc = nr->vr;
	अचिन्हित लघु vt = (nr->vl + nr->winकरोw) % NR_MODULUS;

	जबतक (vc != vt) अणु
		अगर (ns == vc) वापस 1;
		vc = (vc + 1) % NR_MODULUS;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  This routine is called when the HDLC layer पूर्णांकernally generates a
 *  control frame.
 */
व्योम nr_ग_लिखो_पूर्णांकernal(काष्ठा sock *sk, पूर्णांक frametype)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;
	पूर्णांक len, समयout;

	len = NR_NETWORK_LEN + NR_TRANSPORT_LEN;

	चयन (frametype & 0x0F) अणु
	हाल NR_CONNREQ:
		len += 17;
		अवरोध;
	हाल NR_CONNACK:
		len += (nr->bpqext) ? 2 : 1;
		अवरोध;
	हाल NR_DISCREQ:
	हाल NR_DISCACK:
	हाल NR_INFOACK:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "NET/ROM: nr_write_internal - invalid frame type %d\n", frametype);
		वापस;
	पूर्ण

	अगर ((skb = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	/*
	 *	Space क्रम AX.25 and NET/ROM network header
	 */
	skb_reserve(skb, NR_NETWORK_LEN);

	dptr = skb_put(skb, skb_tailroom(skb));

	चयन (frametype & 0x0F) अणु
	हाल NR_CONNREQ:
		समयout  = nr->t1 / HZ;
		*dptr++  = nr->my_index;
		*dptr++  = nr->my_id;
		*dptr++  = 0;
		*dptr++  = 0;
		*dptr++  = frametype;
		*dptr++  = nr->winकरोw;
		स_नकल(dptr, &nr->user_addr, AX25_ADDR_LEN);
		dptr[6] &= ~AX25_CBIT;
		dptr[6] &= ~AX25_EBIT;
		dptr[6] |= AX25_SSSID_SPARE;
		dptr    += AX25_ADDR_LEN;
		स_नकल(dptr, &nr->source_addr, AX25_ADDR_LEN);
		dptr[6] &= ~AX25_CBIT;
		dptr[6] &= ~AX25_EBIT;
		dptr[6] |= AX25_SSSID_SPARE;
		dptr    += AX25_ADDR_LEN;
		*dptr++  = समयout % 256;
		*dptr++  = समयout / 256;
		अवरोध;

	हाल NR_CONNACK:
		*dptr++ = nr->your_index;
		*dptr++ = nr->your_id;
		*dptr++ = nr->my_index;
		*dptr++ = nr->my_id;
		*dptr++ = frametype;
		*dptr++ = nr->winकरोw;
		अगर (nr->bpqext) *dptr++ = sysctl_netrom_network_ttl_initialiser;
		अवरोध;

	हाल NR_DISCREQ:
	हाल NR_DISCACK:
		*dptr++ = nr->your_index;
		*dptr++ = nr->your_id;
		*dptr++ = 0;
		*dptr++ = 0;
		*dptr++ = frametype;
		अवरोध;

	हाल NR_INFOACK:
		*dptr++ = nr->your_index;
		*dptr++ = nr->your_id;
		*dptr++ = 0;
		*dptr++ = nr->vr;
		*dptr++ = frametype;
		अवरोध;
	पूर्ण

	nr_transmit_buffer(sk, skb);
पूर्ण

/*
 * This routine is called to send an error reply.
 */
व्योम __nr_transmit_reply(काष्ठा sk_buff *skb, पूर्णांक mine, अचिन्हित अक्षर cmdflags)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर *dptr;
	पूर्णांक len;

	len = NR_NETWORK_LEN + NR_TRANSPORT_LEN + 1;

	अगर ((skbn = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skbn, 0);

	dptr = skb_put(skbn, NR_NETWORK_LEN + NR_TRANSPORT_LEN);

	skb_copy_from_linear_data_offset(skb, 7, dptr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] &= ~AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	skb_copy_from_linear_data(skb, dptr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] |= AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	*dptr++ = sysctl_netrom_network_ttl_initialiser;

	अगर (mine) अणु
		*dptr++ = 0;
		*dptr++ = 0;
		*dptr++ = skb->data[15];
		*dptr++ = skb->data[16];
	पूर्ण अन्यथा अणु
		*dptr++ = skb->data[15];
		*dptr++ = skb->data[16];
		*dptr++ = 0;
		*dptr++ = 0;
	पूर्ण

	*dptr++ = cmdflags;
	*dptr++ = 0;

	अगर (!nr_route_frame(skbn, शून्य))
		kमुक्त_skb(skbn);
पूर्ण

व्योम nr_disconnect(काष्ठा sock *sk, पूर्णांक reason)
अणु
	nr_stop_t1समयr(sk);
	nr_stop_t2समयr(sk);
	nr_stop_t4समयr(sk);
	nr_stop_idleसमयr(sk);

	nr_clear_queues(sk);

	nr_sk(sk)->state = NR_STATE_0;

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = reason;
	sk->sk_shutकरोwn |= SEND_SHUTDOWN;

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	पूर्ण
पूर्ण
