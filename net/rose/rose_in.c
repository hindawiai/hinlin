<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 *
 * Most of this code is based on the SDL diagrams published in the 7th ARRL
 * Computer Networking Conference papers. The diagrams have mistakes in them,
 * but are mostly correct. Beक्रमe you modअगरy the code could you पढ़ो the SDL
 * diagrams as the code is not obvious and probably very easy to अवरोध.
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
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/rose.h>

/*
 * State machine क्रम state 1, Aरुकोing Call Accepted State.
 * The handling of the समयr(s) is in file rose_समयr.c.
 * Handling of state 0 and connection release is in af_rose.c.
 */
अटल पूर्णांक rose_state1_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	चयन (frametype) अणु
	हाल ROSE_CALL_ACCEPTED:
		rose_stop_समयr(sk);
		rose_start_idleसमयr(sk);
		rose->condition = 0x00;
		rose->vs        = 0;
		rose->va        = 0;
		rose->vr        = 0;
		rose->vl        = 0;
		rose->state     = ROSE_STATE_3;
		sk->sk_state	= TCP_ESTABLISHED;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		अवरोध;

	हाल ROSE_CLEAR_REQUEST:
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, ECONNREFUSED, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * State machine क्रम state 2, Aरुकोing Clear Confirmation State.
 * The handling of the समयr(s) is in file rose_समयr.c
 * Handling of state 0 and connection release is in af_rose.c.
 */
अटल पूर्णांक rose_state2_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	चयन (frametype) अणु
	हाल ROSE_CLEAR_REQUEST:
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		अवरोध;

	हाल ROSE_CLEAR_CONFIRMATION:
		rose_disconnect(sk, 0, -1, -1);
		rose->neighbour->use--;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * State machine क्रम state 3, Connected State.
 * The handling of the समयr(s) is in file rose_समयr.c
 * Handling of state 0 and connection release is in af_rose.c.
 */
अटल पूर्णांक rose_state3_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype, पूर्णांक ns, पूर्णांक nr, पूर्णांक q, पूर्णांक d, पूर्णांक m)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);
	पूर्णांक queued = 0;

	चयन (frametype) अणु
	हाल ROSE_RESET_REQUEST:
		rose_stop_समयr(sk);
		rose_start_idleसमयr(sk);
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RESET_CONFIRMATION);
		rose->condition = 0x00;
		rose->vs        = 0;
		rose->vr        = 0;
		rose->va        = 0;
		rose->vl        = 0;
		rose_requeue_frames(sk);
		अवरोध;

	हाल ROSE_CLEAR_REQUEST:
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		अवरोध;

	हाल ROSE_RR:
	हाल ROSE_RNR:
		अगर (!rose_validate_nr(sk, nr)) अणु
			rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RESET_REQUEST);
			rose->condition = 0x00;
			rose->vs        = 0;
			rose->vr        = 0;
			rose->va        = 0;
			rose->vl        = 0;
			rose->state     = ROSE_STATE_4;
			rose_start_t2समयr(sk);
			rose_stop_idleसमयr(sk);
		पूर्ण अन्यथा अणु
			rose_frames_acked(sk, nr);
			अगर (frametype == ROSE_RNR) अणु
				rose->condition |= ROSE_COND_PEER_RX_BUSY;
			पूर्ण अन्यथा अणु
				rose->condition &= ~ROSE_COND_PEER_RX_BUSY;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ROSE_DATA:	/* XXX */
		rose->condition &= ~ROSE_COND_PEER_RX_BUSY;
		अगर (!rose_validate_nr(sk, nr)) अणु
			rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RESET_REQUEST);
			rose->condition = 0x00;
			rose->vs        = 0;
			rose->vr        = 0;
			rose->va        = 0;
			rose->vl        = 0;
			rose->state     = ROSE_STATE_4;
			rose_start_t2समयr(sk);
			rose_stop_idleसमयr(sk);
			अवरोध;
		पूर्ण
		rose_frames_acked(sk, nr);
		अगर (ns == rose->vr) अणु
			rose_start_idleसमयr(sk);
			अगर (sk_filter_trim_cap(sk, skb, ROSE_MIN_LEN) == 0 &&
			    __sock_queue_rcv_skb(sk, skb) == 0) अणु
				rose->vr = (rose->vr + 1) % ROSE_MODULUS;
				queued = 1;
			पूर्ण अन्यथा अणु
				/* Should never happen ! */
				rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RESET_REQUEST);
				rose->condition = 0x00;
				rose->vs        = 0;
				rose->vr        = 0;
				rose->va        = 0;
				rose->vl        = 0;
				rose->state     = ROSE_STATE_4;
				rose_start_t2समयr(sk);
				rose_stop_idleसमयr(sk);
				अवरोध;
			पूर्ण
			अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >
			    (sk->sk_rcvbuf >> 1))
				rose->condition |= ROSE_COND_OWN_RX_BUSY;
		पूर्ण
		/*
		 * If the winकरोw is full, ack the frame, अन्यथा start the
		 * acknowledge hold back समयr.
		 */
		अगर (((rose->vl + sysctl_rose_winकरोw_size) % ROSE_MODULUS) == rose->vr) अणु
			rose->condition &= ~ROSE_COND_ACK_PENDING;
			rose_stop_समयr(sk);
			rose_enquiry_response(sk);
		पूर्ण अन्यथा अणु
			rose->condition |= ROSE_COND_ACK_PENDING;
			rose_start_hbसमयr(sk);
		पूर्ण
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "ROSE: unknown %02X in state 3\n", frametype);
		अवरोध;
	पूर्ण

	वापस queued;
पूर्ण

/*
 * State machine क्रम state 4, Aरुकोing Reset Confirmation State.
 * The handling of the समयr(s) is in file rose_समयr.c
 * Handling of state 0 and connection release is in af_rose.c.
 */
अटल पूर्णांक rose_state4_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	चयन (frametype) अणु
	हाल ROSE_RESET_REQUEST:
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RESET_CONFIRMATION);
		fallthrough;
	हाल ROSE_RESET_CONFIRMATION:
		rose_stop_समयr(sk);
		rose_start_idleसमयr(sk);
		rose->condition = 0x00;
		rose->va        = 0;
		rose->vr        = 0;
		rose->vs        = 0;
		rose->vl        = 0;
		rose->state     = ROSE_STATE_3;
		rose_requeue_frames(sk);
		अवरोध;

	हाल ROSE_CLEAR_REQUEST:
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose->neighbour->use--;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * State machine क्रम state 5, Aरुकोing Call Acceptance State.
 * The handling of the समयr(s) is in file rose_समयr.c
 * Handling of state 0 and connection release is in af_rose.c.
 */
अटल पूर्णांक rose_state5_machine(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक frametype)
अणु
	अगर (frametype == ROSE_CLEAR_REQUEST) अणु
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_CONFIRMATION);
		rose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		rose_sk(sk)->neighbour->use--;
	पूर्ण

	वापस 0;
पूर्ण

/* Higher level upcall क्रम a LAPB frame */
पूर्णांक rose_process_rx_frame(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);
	पूर्णांक queued = 0, frametype, ns, nr, q, d, m;

	अगर (rose->state == ROSE_STATE_0)
		वापस 0;

	frametype = rose_decode(skb, &ns, &nr, &q, &d, &m);

	चयन (rose->state) अणु
	हाल ROSE_STATE_1:
		queued = rose_state1_machine(sk, skb, frametype);
		अवरोध;
	हाल ROSE_STATE_2:
		queued = rose_state2_machine(sk, skb, frametype);
		अवरोध;
	हाल ROSE_STATE_3:
		queued = rose_state3_machine(sk, skb, frametype, ns, nr, q, d, m);
		अवरोध;
	हाल ROSE_STATE_4:
		queued = rose_state4_machine(sk, skb, frametype);
		अवरोध;
	हाल ROSE_STATE_5:
		queued = rose_state5_machine(sk, skb, frametype);
		अवरोध;
	पूर्ण

	rose_kick(sk);

	वापस queued;
पूर्ण
