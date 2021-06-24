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
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/netrom.h>

अटल पूर्णांक nr_queue_rx_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक more)
अणु
	काष्ठा sk_buff *skbo, *skbn = skb;
	काष्ठा nr_sock *nr = nr_sk(sk);

	skb_pull(skb, NR_NETWORK_LEN + NR_TRANSPORT_LEN);

	nr_start_idleसमयr(sk);

	अगर (more) अणु
		nr->fraglen += skb->len;
		skb_queue_tail(&nr->frag_queue, skb);
		वापस 0;
	पूर्ण

	अगर (!more && nr->fraglen > 0) अणु	/* End of fragment */
		nr->fraglen += skb->len;
		skb_queue_tail(&nr->frag_queue, skb);

		अगर ((skbn = alloc_skb(nr->fraglen, GFP_ATOMIC)) == शून्य)
			वापस 1;

		skb_reset_transport_header(skbn);

		जबतक ((skbo = skb_dequeue(&nr->frag_queue)) != शून्य) अणु
			skb_copy_from_linear_data(skbo,
						  skb_put(skbn, skbo->len),
						  skbo->len);
			kमुक्त_skb(skbo);
		पूर्ण

		nr->fraglen = 0;
	पूर्ण

	वापस sock_queue_rcv_skb(sk, skbn);
पूर्ण

/*
 * State machine क्रम state 1, Aरुकोing Connection State.
 * The handling of the समयr(s) is in file nr_समयr.c.
 * Handling of state 0 and connection release is in netrom.c.
 */
अटल पूर्णांक nr_state1_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb,
	पूर्णांक frametype)
अणु
	चयन (frametype) अणु
	हाल NR_CONNACK: अणु
		काष्ठा nr_sock *nr = nr_sk(sk);

		nr_stop_t1समयr(sk);
		nr_start_idleसमयr(sk);
		nr->your_index = skb->data[17];
		nr->your_id    = skb->data[18];
		nr->vs	       = 0;
		nr->va	       = 0;
		nr->vr	       = 0;
		nr->vl	       = 0;
		nr->state      = NR_STATE_3;
		nr->n2count    = 0;
		nr->winकरोw     = skb->data[20];
		sk->sk_state   = TCP_ESTABLISHED;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अवरोध;
	पूर्ण

	हाल NR_CONNACK | NR_CHOKE_FLAG:
		nr_disconnect(sk, ECONNREFUSED);
		अवरोध;

	हाल NR_RESET:
		अगर (sysctl_netrom_reset_circuit)
			nr_disconnect(sk, ECONNRESET);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 2, Aरुकोing Release State.
 * The handling of the समयr(s) is in file nr_समयr.c
 * Handling of state 0 and connection release is in netrom.c.
 */
अटल पूर्णांक nr_state2_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb,
	पूर्णांक frametype)
अणु
	चयन (frametype) अणु
	हाल NR_CONNACK | NR_CHOKE_FLAG:
		nr_disconnect(sk, ECONNRESET);
		अवरोध;

	हाल NR_DISCREQ:
		nr_ग_लिखो_पूर्णांकernal(sk, NR_DISCACK);
		fallthrough;
	हाल NR_DISCACK:
		nr_disconnect(sk, 0);
		अवरोध;

	हाल NR_RESET:
		अगर (sysctl_netrom_reset_circuit)
			nr_disconnect(sk, ECONNRESET);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * State machine क्रम state 3, Connected State.
 * The handling of the समयr(s) is in file nr_समयr.c
 * Handling of state 0 and connection release is in netrom.c.
 */
अटल पूर्णांक nr_state3_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा nr_sock *nrom = nr_sk(sk);
	काष्ठा sk_buff_head temp_queue;
	काष्ठा sk_buff *skbn;
	अचिन्हित लघु save_vr;
	अचिन्हित लघु nr, ns;
	पूर्णांक queued = 0;

	nr = skb->data[18];

	चयन (frametype) अणु
	हाल NR_CONNREQ:
		nr_ग_लिखो_पूर्णांकernal(sk, NR_CONNACK);
		अवरोध;

	हाल NR_DISCREQ:
		nr_ग_लिखो_पूर्णांकernal(sk, NR_DISCACK);
		nr_disconnect(sk, 0);
		अवरोध;

	हाल NR_CONNACK | NR_CHOKE_FLAG:
	हाल NR_DISCACK:
		nr_disconnect(sk, ECONNRESET);
		अवरोध;

	हाल NR_INFOACK:
	हाल NR_INFOACK | NR_CHOKE_FLAG:
	हाल NR_INFOACK | NR_NAK_FLAG:
	हाल NR_INFOACK | NR_NAK_FLAG | NR_CHOKE_FLAG:
		अगर (frametype & NR_CHOKE_FLAG) अणु
			nrom->condition |= NR_COND_PEER_RX_BUSY;
			nr_start_t4समयr(sk);
		पूर्ण अन्यथा अणु
			nrom->condition &= ~NR_COND_PEER_RX_BUSY;
			nr_stop_t4समयr(sk);
		पूर्ण
		अगर (!nr_validate_nr(sk, nr)) अणु
			अवरोध;
		पूर्ण
		अगर (frametype & NR_NAK_FLAG) अणु
			nr_frames_acked(sk, nr);
			nr_send_nak_frame(sk);
		पूर्ण अन्यथा अणु
			अगर (nrom->condition & NR_COND_PEER_RX_BUSY) अणु
				nr_frames_acked(sk, nr);
			पूर्ण अन्यथा अणु
				nr_check_अगरrames_acked(sk, nr);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल NR_INFO:
	हाल NR_INFO | NR_NAK_FLAG:
	हाल NR_INFO | NR_CHOKE_FLAG:
	हाल NR_INFO | NR_MORE_FLAG:
	हाल NR_INFO | NR_NAK_FLAG | NR_CHOKE_FLAG:
	हाल NR_INFO | NR_CHOKE_FLAG | NR_MORE_FLAG:
	हाल NR_INFO | NR_NAK_FLAG | NR_MORE_FLAG:
	हाल NR_INFO | NR_NAK_FLAG | NR_CHOKE_FLAG | NR_MORE_FLAG:
		अगर (frametype & NR_CHOKE_FLAG) अणु
			nrom->condition |= NR_COND_PEER_RX_BUSY;
			nr_start_t4समयr(sk);
		पूर्ण अन्यथा अणु
			nrom->condition &= ~NR_COND_PEER_RX_BUSY;
			nr_stop_t4समयr(sk);
		पूर्ण
		अगर (nr_validate_nr(sk, nr)) अणु
			अगर (frametype & NR_NAK_FLAG) अणु
				nr_frames_acked(sk, nr);
				nr_send_nak_frame(sk);
			पूर्ण अन्यथा अणु
				अगर (nrom->condition & NR_COND_PEER_RX_BUSY) अणु
					nr_frames_acked(sk, nr);
				पूर्ण अन्यथा अणु
					nr_check_अगरrames_acked(sk, nr);
				पूर्ण
			पूर्ण
		पूर्ण
		queued = 1;
		skb_queue_head(&nrom->reseq_queue, skb);
		अगर (nrom->condition & NR_COND_OWN_RX_BUSY)
			अवरोध;
		skb_queue_head_init(&temp_queue);
		करो अणु
			save_vr = nrom->vr;
			जबतक ((skbn = skb_dequeue(&nrom->reseq_queue)) != शून्य) अणु
				ns = skbn->data[17];
				अगर (ns == nrom->vr) अणु
					अगर (nr_queue_rx_frame(sk, skbn, frametype & NR_MORE_FLAG) == 0) अणु
						nrom->vr = (nrom->vr + 1) % NR_MODULUS;
					पूर्ण अन्यथा अणु
						nrom->condition |= NR_COND_OWN_RX_BUSY;
						skb_queue_tail(&temp_queue, skbn);
					पूर्ण
				पूर्ण अन्यथा अगर (nr_in_rx_winकरोw(sk, ns)) अणु
					skb_queue_tail(&temp_queue, skbn);
				पूर्ण अन्यथा अणु
					kमुक्त_skb(skbn);
				पूर्ण
			पूर्ण
			जबतक ((skbn = skb_dequeue(&temp_queue)) != शून्य) अणु
				skb_queue_tail(&nrom->reseq_queue, skbn);
			पूर्ण
		पूर्ण जबतक (save_vr != nrom->vr);
		/*
		 * Winकरोw is full, ack it immediately.
		 */
		अगर (((nrom->vl + nrom->winकरोw) % NR_MODULUS) == nrom->vr) अणु
			nr_enquiry_response(sk);
		पूर्ण अन्यथा अणु
			अगर (!(nrom->condition & NR_COND_ACK_PENDING)) अणु
				nrom->condition |= NR_COND_ACK_PENDING;
				nr_start_t2समयr(sk);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल NR_RESET:
		अगर (sysctl_netrom_reset_circuit)
			nr_disconnect(sk, ECONNRESET);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस queued;
पूर्ण

/* Higher level upcall क्रम a LAPB frame - called with sk locked */
पूर्णांक nr_process_rx_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);
	पूर्णांक queued = 0, frametype;

	अगर (nr->state == NR_STATE_0)
		वापस 0;

	frametype = skb->data[19];

	चयन (nr->state) अणु
	हाल NR_STATE_1:
		queued = nr_state1_machine(sk, skb, frametype);
		अवरोध;
	हाल NR_STATE_2:
		queued = nr_state2_machine(sk, skb, frametype);
		अवरोध;
	हाल NR_STATE_3:
		queued = nr_state3_machine(sk, skb, frametype);
		अवरोध;
	पूर्ण

	nr_kick(sk);

	वापस queued;
पूर्ण
