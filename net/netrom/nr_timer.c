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
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/netrom.h>

अटल व्योम nr_heartbeat_expiry(काष्ठा समयr_list *);
अटल व्योम nr_t1समयr_expiry(काष्ठा समयr_list *);
अटल व्योम nr_t2समयr_expiry(काष्ठा समयr_list *);
अटल व्योम nr_t4समयr_expiry(काष्ठा समयr_list *);
अटल व्योम nr_idleसमयr_expiry(काष्ठा समयr_list *);

व्योम nr_init_समयrs(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	समयr_setup(&nr->t1समयr, nr_t1समयr_expiry, 0);
	समयr_setup(&nr->t2समयr, nr_t2समयr_expiry, 0);
	समयr_setup(&nr->t4समयr, nr_t4समयr_expiry, 0);
	समयr_setup(&nr->idleसमयr, nr_idleसमयr_expiry, 0);

	/* initialized by sock_init_data */
	sk->sk_समयr.function = nr_heartbeat_expiry;
पूर्ण

व्योम nr_start_t1समयr(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	sk_reset_समयr(sk, &nr->t1समयr, jअगरfies + nr->t1);
पूर्ण

व्योम nr_start_t2समयr(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	sk_reset_समयr(sk, &nr->t2समयr, jअगरfies + nr->t2);
पूर्ण

व्योम nr_start_t4समयr(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	sk_reset_समयr(sk, &nr->t4समयr, jअगरfies + nr->t4);
पूर्ण

व्योम nr_start_idleसमयr(काष्ठा sock *sk)
अणु
	काष्ठा nr_sock *nr = nr_sk(sk);

	अगर (nr->idle > 0)
		sk_reset_समयr(sk, &nr->idleसमयr, jअगरfies + nr->idle);
पूर्ण

व्योम nr_start_heartbeat(काष्ठा sock *sk)
अणु
	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + 5 * HZ);
पूर्ण

व्योम nr_stop_t1समयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &nr_sk(sk)->t1समयr);
पूर्ण

व्योम nr_stop_t2समयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &nr_sk(sk)->t2समयr);
पूर्ण

व्योम nr_stop_t4समयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &nr_sk(sk)->t4समयr);
पूर्ण

व्योम nr_stop_idleसमयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &nr_sk(sk)->idleसमयr);
पूर्ण

व्योम nr_stop_heartbeat(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &sk->sk_समयr);
पूर्ण

पूर्णांक nr_t1समयr_running(काष्ठा sock *sk)
अणु
	वापस समयr_pending(&nr_sk(sk)->t1समयr);
पूर्ण

अटल व्योम nr_heartbeat_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	काष्ठा nr_sock *nr = nr_sk(sk);

	bh_lock_sock(sk);
	चयन (nr->state) अणु
	हाल NR_STATE_0:
		/* Magic here: If we listen() and a new link dies beक्रमe it
		   is accepted() it isn't 'dead' so doesn't get हटाओd. */
		अगर (sock_flag(sk, SOCK_DESTROY) ||
		    (sk->sk_state == TCP_LISTEN && sock_flag(sk, SOCK_DEAD))) अणु
			sock_hold(sk);
			bh_unlock_sock(sk);
			nr_destroy_socket(sk);
			sock_put(sk);
			वापस;
		पूर्ण
		अवरोध;

	हाल NR_STATE_3:
		/*
		 * Check क्रम the state of the receive buffer.
		 */
		अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) < (sk->sk_rcvbuf / 2) &&
		    (nr->condition & NR_COND_OWN_RX_BUSY)) अणु
			nr->condition &= ~NR_COND_OWN_RX_BUSY;
			nr->condition &= ~NR_COND_ACK_PENDING;
			nr->vl         = nr->vr;
			nr_ग_लिखो_पूर्णांकernal(sk, NR_INFOACK);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	nr_start_heartbeat(sk);
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम nr_t2समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा nr_sock *nr = from_समयr(nr, t, t2समयr);
	काष्ठा sock *sk = &nr->sock;

	bh_lock_sock(sk);
	अगर (nr->condition & NR_COND_ACK_PENDING) अणु
		nr->condition &= ~NR_COND_ACK_PENDING;
		nr_enquiry_response(sk);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम nr_t4समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा nr_sock *nr = from_समयr(nr, t, t4समयr);
	काष्ठा sock *sk = &nr->sock;

	bh_lock_sock(sk);
	nr_sk(sk)->condition &= ~NR_COND_PEER_RX_BUSY;
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम nr_idleसमयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा nr_sock *nr = from_समयr(nr, t, idleसमयr);
	काष्ठा sock *sk = &nr->sock;

	bh_lock_sock(sk);

	nr_clear_queues(sk);

	nr->n2count = 0;
	nr_ग_लिखो_पूर्णांकernal(sk, NR_DISCREQ);
	nr->state = NR_STATE_2;

	nr_start_t1समयr(sk);
	nr_stop_t2समयr(sk);
	nr_stop_t4समयr(sk);

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = 0;
	sk->sk_shutकरोwn |= SEND_SHUTDOWN;

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

अटल व्योम nr_t1समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा nr_sock *nr = from_समयr(nr, t, t1समयr);
	काष्ठा sock *sk = &nr->sock;

	bh_lock_sock(sk);
	चयन (nr->state) अणु
	हाल NR_STATE_1:
		अगर (nr->n2count == nr->n2) अणु
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			वापस;
		पूर्ण अन्यथा अणु
			nr->n2count++;
			nr_ग_लिखो_पूर्णांकernal(sk, NR_CONNREQ);
		पूर्ण
		अवरोध;

	हाल NR_STATE_2:
		अगर (nr->n2count == nr->n2) अणु
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			वापस;
		पूर्ण अन्यथा अणु
			nr->n2count++;
			nr_ग_लिखो_पूर्णांकernal(sk, NR_DISCREQ);
		पूर्ण
		अवरोध;

	हाल NR_STATE_3:
		अगर (nr->n2count == nr->n2) अणु
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			वापस;
		पूर्ण अन्यथा अणु
			nr->n2count++;
			nr_requeue_frames(sk);
		पूर्ण
		अवरोध;
	पूर्ण

	nr_start_t1समयr(sk);
	bh_unlock_sock(sk);
पूर्ण
