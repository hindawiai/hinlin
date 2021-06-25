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
 *					Centralised disconnection processing.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/x25.h>

अटल व्योम x25_heartbeat_expiry(काष्ठा समयr_list *t);
अटल व्योम x25_समयr_expiry(काष्ठा समयr_list *t);

व्योम x25_init_समयrs(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	समयr_setup(&x25->समयr, x25_समयr_expiry, 0);

	/* initialized by sock_init_data */
	sk->sk_समयr.function = x25_heartbeat_expiry;
पूर्ण

व्योम x25_start_heartbeat(काष्ठा sock *sk)
अणु
	mod_समयr(&sk->sk_समयr, jअगरfies + 5 * HZ);
पूर्ण

व्योम x25_stop_heartbeat(काष्ठा sock *sk)
अणु
	del_समयr(&sk->sk_समयr);
पूर्ण

व्योम x25_start_t2समयr(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	mod_समयr(&x25->समयr, jअगरfies + x25->t2);
पूर्ण

व्योम x25_start_t21समयr(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	mod_समयr(&x25->समयr, jअगरfies + x25->t21);
पूर्ण

व्योम x25_start_t22समयr(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	mod_समयr(&x25->समयr, jअगरfies + x25->t22);
पूर्ण

व्योम x25_start_t23समयr(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	mod_समयr(&x25->समयr, jअगरfies + x25->t23);
पूर्ण

व्योम x25_stop_समयr(काष्ठा sock *sk)
अणु
	del_समयr(&x25_sk(sk)->समयr);
पूर्ण

अचिन्हित दीर्घ x25_display_समयr(काष्ठा sock *sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	अगर (!समयr_pending(&x25->समयr))
		वापस 0;

	वापस x25->समयr.expires - jअगरfies;
पूर्ण

अटल व्योम x25_heartbeat_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) /* can currently only occur in state 3 */
		जाओ restart_heartbeat;

	चयन (x25_sk(sk)->state) अणु

		हाल X25_STATE_0:
			/*
			 * Magic here: If we listen() and a new link dies
			 * beक्रमe it is accepted() it isn't 'dead' so doesn't
			 * get हटाओd.
			 */
			अगर (sock_flag(sk, SOCK_DESTROY) ||
			    (sk->sk_state == TCP_LISTEN &&
			     sock_flag(sk, SOCK_DEAD))) अणु
				bh_unlock_sock(sk);
				x25_destroy_socket_from_समयr(sk);
				वापस;
			पूर्ण
			अवरोध;

		हाल X25_STATE_3:
			/*
			 * Check क्रम the state of the receive buffer.
			 */
			x25_check_rbuf(sk);
			अवरोध;
	पूर्ण
restart_heartbeat:
	x25_start_heartbeat(sk);
	bh_unlock_sock(sk);
पूर्ण

/*
 *	Timer has expired, it may have been T2, T21, T22, or T23. We can tell
 *	by the state machine state.
 */
अटल अंतरभूत व्योम x25_करो_समयr_expiry(काष्ठा sock * sk)
अणु
	काष्ठा x25_sock *x25 = x25_sk(sk);

	चयन (x25->state) अणु

		हाल X25_STATE_3:	/* T2 */
			अगर (x25->condition & X25_COND_ACK_PENDING) अणु
				x25->condition &= ~X25_COND_ACK_PENDING;
				x25_enquiry_response(sk);
			पूर्ण
			अवरोध;

		हाल X25_STATE_1:	/* T21 */
		हाल X25_STATE_4:	/* T22 */
			x25_ग_लिखो_पूर्णांकernal(sk, X25_CLEAR_REQUEST);
			x25->state = X25_STATE_2;
			x25_start_t23समयr(sk);
			अवरोध;

		हाल X25_STATE_2:	/* T23 */
			x25_disconnect(sk, ETIMEDOUT, 0, 0);
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम x25_समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा x25_sock *x25 = from_समयr(x25, t, समयr);
	काष्ठा sock *sk = &x25->sk;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु /* can currently only occur in state 3 */
		अगर (x25_sk(sk)->state == X25_STATE_3)
			x25_start_t2समयr(sk);
	पूर्ण अन्यथा
		x25_करो_समयr_expiry(sk);
	bh_unlock_sock(sk);
पूर्ण
