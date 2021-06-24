<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) 2002 Ralf Baechle DO1GRB (ralf@gnu.org)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
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

अटल व्योम rose_heartbeat_expiry(काष्ठा समयr_list *t);
अटल व्योम rose_समयr_expiry(काष्ठा समयr_list *);
अटल व्योम rose_idleसमयr_expiry(काष्ठा समयr_list *);

व्योम rose_start_heartbeat(काष्ठा sock *sk)
अणु
	del_समयr(&sk->sk_समयr);

	sk->sk_समयr.function = rose_heartbeat_expiry;
	sk->sk_समयr.expires  = jअगरfies + 5 * HZ;

	add_समयr(&sk->sk_समयr);
पूर्ण

व्योम rose_start_t1समयr(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	del_समयr(&rose->समयr);

	rose->समयr.function = rose_समयr_expiry;
	rose->समयr.expires  = jअगरfies + rose->t1;

	add_समयr(&rose->समयr);
पूर्ण

व्योम rose_start_t2समयr(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	del_समयr(&rose->समयr);

	rose->समयr.function = rose_समयr_expiry;
	rose->समयr.expires  = jअगरfies + rose->t2;

	add_समयr(&rose->समयr);
पूर्ण

व्योम rose_start_t3समयr(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	del_समयr(&rose->समयr);

	rose->समयr.function = rose_समयr_expiry;
	rose->समयr.expires  = jअगरfies + rose->t3;

	add_समयr(&rose->समयr);
पूर्ण

व्योम rose_start_hbसमयr(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	del_समयr(&rose->समयr);

	rose->समयr.function = rose_समयr_expiry;
	rose->समयr.expires  = jअगरfies + rose->hb;

	add_समयr(&rose->समयr);
पूर्ण

व्योम rose_start_idleसमयr(काष्ठा sock *sk)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	del_समयr(&rose->idleसमयr);

	अगर (rose->idle > 0) अणु
		rose->idleसमयr.function = rose_idleसमयr_expiry;
		rose->idleसमयr.expires  = jअगरfies + rose->idle;

		add_समयr(&rose->idleसमयr);
	पूर्ण
पूर्ण

व्योम rose_stop_heartbeat(काष्ठा sock *sk)
अणु
	del_समयr(&sk->sk_समयr);
पूर्ण

व्योम rose_stop_समयr(काष्ठा sock *sk)
अणु
	del_समयr(&rose_sk(sk)->समयr);
पूर्ण

व्योम rose_stop_idleसमयr(काष्ठा sock *sk)
अणु
	del_समयr(&rose_sk(sk)->idleसमयr);
पूर्ण

अटल व्योम rose_heartbeat_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	काष्ठा rose_sock *rose = rose_sk(sk);

	bh_lock_sock(sk);
	चयन (rose->state) अणु
	हाल ROSE_STATE_0:
		/* Magic here: If we listen() and a new link dies beक्रमe it
		   is accepted() it isn't 'dead' so doesn't get हटाओd. */
		अगर (sock_flag(sk, SOCK_DESTROY) ||
		    (sk->sk_state == TCP_LISTEN && sock_flag(sk, SOCK_DEAD))) अणु
			bh_unlock_sock(sk);
			rose_destroy_socket(sk);
			वापस;
		पूर्ण
		अवरोध;

	हाल ROSE_STATE_3:
		/*
		 * Check क्रम the state of the receive buffer.
		 */
		अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) < (sk->sk_rcvbuf / 2) &&
		    (rose->condition & ROSE_COND_OWN_RX_BUSY)) अणु
			rose->condition &= ~ROSE_COND_OWN_RX_BUSY;
			rose->condition &= ~ROSE_COND_ACK_PENDING;
			rose->vl         = rose->vr;
			rose_ग_लिखो_पूर्णांकernal(sk, ROSE_RR);
			rose_stop_समयr(sk);	/* HB */
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	rose_start_heartbeat(sk);
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम rose_समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा rose_sock *rose = from_समयr(rose, t, समयr);
	काष्ठा sock *sk = &rose->sock;

	bh_lock_sock(sk);
	चयन (rose->state) अणु
	हाल ROSE_STATE_1:	/* T1 */
	हाल ROSE_STATE_4:	/* T2 */
		rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_REQUEST);
		rose->state = ROSE_STATE_2;
		rose_start_t3समयr(sk);
		अवरोध;

	हाल ROSE_STATE_2:	/* T3 */
		rose->neighbour->use--;
		rose_disconnect(sk, ETIMEDOUT, -1, -1);
		अवरोध;

	हाल ROSE_STATE_3:	/* HB */
		अगर (rose->condition & ROSE_COND_ACK_PENDING) अणु
			rose->condition &= ~ROSE_COND_ACK_PENDING;
			rose_enquiry_response(sk);
		पूर्ण
		अवरोध;
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम rose_idleसमयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा rose_sock *rose = from_समयr(rose, t, idleसमयr);
	काष्ठा sock *sk = &rose->sock;

	bh_lock_sock(sk);
	rose_clear_queues(sk);

	rose_ग_लिखो_पूर्णांकernal(sk, ROSE_CLEAR_REQUEST);
	rose_sk(sk)->state = ROSE_STATE_2;

	rose_start_t3समयr(sk);

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = 0;
	sk->sk_shutकरोwn |= SEND_SHUTDOWN;

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण
