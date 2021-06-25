<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright Darryl Miles G7LED (dlm@g7led.demon.co.uk)
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
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/netrom.h>

/*
 *	This is where all NET/ROM frames pass, except क्रम IP-over-NET/ROM which
 *	cannot be fragmented in this manner.
 */
व्योम nr_output(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर transport[NR_TRANSPORT_LEN];
	पूर्णांक err, frontlen, len;

	अगर (skb->len - NR_TRANSPORT_LEN > NR_MAX_PACKET_SIZE) अणु
		/* Save a copy of the Transport Header */
		skb_copy_from_linear_data(skb, transport, NR_TRANSPORT_LEN);
		skb_pull(skb, NR_TRANSPORT_LEN);

		frontlen = skb_headroom(skb);

		जबतक (skb->len > 0) अणु
			अगर ((skbn = sock_alloc_send_skb(sk, frontlen + NR_MAX_PACKET_SIZE, 0, &err)) == शून्य)
				वापस;

			skb_reserve(skbn, frontlen);

			len = (NR_MAX_PACKET_SIZE > skb->len) ? skb->len : NR_MAX_PACKET_SIZE;

			/* Copy the user data */
			skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
			skb_pull(skb, len);

			/* Duplicate the Transport Header */
			skb_push(skbn, NR_TRANSPORT_LEN);
			skb_copy_to_linear_data(skbn, transport,
						NR_TRANSPORT_LEN);
			अगर (skb->len > 0)
				skbn->data[4] |= NR_MORE_FLAG;

			skb_queue_tail(&sk->sk_ग_लिखो_queue, skbn); /* Throw it on the queue */
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);		/* Throw it on the queue */
	पूर्ण

	nr_kick(sk);
पूर्ण

/*
 *	This procedure is passed a buffer descriptor क्रम an अगरrame. It builds
 *	the rest of the control part of the frame and then ग_लिखोs it out.
 */
अटल व्योम nr_send_अगरrame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	अगर (skb == शून्य)
		वापस;

	skb->data[2] = nr->vs;
	skb->data[3] = nr->vr;

	अगर (nr->condition & NR_COND_OWN_RX_BUSY)
		skb->data[4] |= NR_CHOKE_FLAG;

	nr_start_idleसमयr(sk);

	nr_transmit_buffer(sk, skb);
पूर्ण

व्योम nr_send_nak_frame(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *skbn;
	काष्ठा nr_sock *nr = nr_sk(sk);

	अगर ((skb = skb_peek(&nr->ack_queue)) == शून्य)
		वापस;

	अगर ((skbn = skb_clone(skb, GFP_ATOMIC)) == शून्य)
		वापस;

	skbn->data[2] = nr->va;
	skbn->data[3] = nr->vr;

	अगर (nr->condition & NR_COND_OWN_RX_BUSY)
		skbn->data[4] |= NR_CHOKE_FLAG;

	nr_transmit_buffer(sk, skbn);

	nr->condition &= ~NR_COND_ACK_PENDING;
	nr->vl         = nr->vr;

	nr_stop_t1समयr(sk);
पूर्ण

व्योम nr_kick(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	काष्ठा sk_buff *skb, *skbn;
	अचिन्हित लघु start, end;

	अगर (nr->state != NR_STATE_3)
		वापस;

	अगर (nr->condition & NR_COND_PEER_RX_BUSY)
		वापस;

	अगर (!skb_peek(&sk->sk_ग_लिखो_queue))
		वापस;

	start = (skb_peek(&nr->ack_queue) == शून्य) ? nr->va : nr->vs;
	end   = (nr->va + nr->winकरोw) % NR_MODULUS;

	अगर (start == end)
		वापस;

	nr->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the winकरोw is full.
	 */

	/*
	 * Dequeue the frame and copy it.
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
		nr_send_अगरrame(sk, skbn);

		nr->vs = (nr->vs + 1) % NR_MODULUS;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&nr->ack_queue, skb);

	पूर्ण जबतक (nr->vs != end &&
		 (skb = skb_dequeue(&sk->sk_ग_लिखो_queue)) != शून्य);

	nr->vl         = nr->vr;
	nr->condition &= ~NR_COND_ACK_PENDING;

	अगर (!nr_t1समयr_running(sk))
		nr_start_t1समयr(sk);
पूर्ण

व्योम nr_transmit_buffer(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	अचिन्हित अक्षर *dptr;

	/*
	 *	Add the protocol byte and network header.
	 */
	dptr = skb_push(skb, NR_NETWORK_LEN);

	स_नकल(dptr, &nr->source_addr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] &= ~AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	स_नकल(dptr, &nr->dest_addr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] |= AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	*dptr++ = sysctl_netrom_network_ttl_initialiser;

	अगर (!nr_route_frame(skb, शून्य)) अणु
		kमुक्त_skb(skb);
		nr_disconnect(sk, ENETUNREACH);
	पूर्ण
पूर्ण

/*
 * The following routines are taken from page 170 of the 7th ARRL Computer
 * Networking Conference paper, as is the whole state machine.
 */

व्योम nr_establish_data_link(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	nr->condition = 0x00;
	nr->n2count   = 0;

	nr_ग_लिखो_पूर्णांकernal(sk, NR_CONNREQ);

	nr_stop_t2समयr(sk);
	nr_stop_t4समयr(sk);
	nr_stop_idleसमयr(sk);
	nr_start_t1समयr(sk);
पूर्ण

/*
 * Never send a NAK when we are CHOKEd.
 */
व्योम nr_enquiry_response(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	पूर्णांक frametype = NR_INFOACK;

	अगर (nr->condition & NR_COND_OWN_RX_BUSY) अणु
		frametype |= NR_CHOKE_FLAG;
	पूर्ण अन्यथा अणु
		अगर (skb_peek(&nr->reseq_queue) != शून्य)
			frametype |= NR_NAK_FLAG;
	पूर्ण

	nr_ग_लिखो_पूर्णांकernal(sk, frametype);

	nr->vl         = nr->vr;
	nr->condition &= ~NR_COND_ACK_PENDING;
पूर्ण

व्योम nr_check_अगरrames_acked(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा nr_sock *nrom = nr_sk(sk);

	अगर (nrom->vs == nr) अणु
		nr_frames_acked(sk, nr);
		nr_stop_t1समयr(sk);
		nrom->n2count = 0;
	पूर्ण अन्यथा अणु
		अगर (nrom->va != nr) अणु
			nr_frames_acked(sk, nr);
			nr_start_t1समयr(sk);
		पूर्ण
	पूर्ण
पूर्ण
