<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)
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
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

व्योम ax25_std_heartbeat_expiry(ax25_cb *ax25)
अणु
	काष्ठा sock *sk = ax25->sk;

	अगर (sk)
		bh_lock_sock(sk);

	चयन (ax25->state) अणु
	हाल AX25_STATE_0:
	हाल AX25_STATE_2:
		/* Magic here: If we listen() and a new link dies beक्रमe it
		   is accepted() it isn't 'dead' so doesn't get हटाओd. */
		अगर (!sk || sock_flag(sk, SOCK_DESTROY) ||
		    (sk->sk_state == TCP_LISTEN &&
		     sock_flag(sk, SOCK_DEAD))) अणु
			अगर (sk) अणु
				sock_hold(sk);
				ax25_destroy_socket(ax25);
				bh_unlock_sock(sk);
				/* Ungrab socket and destroy it */
				sock_put(sk);
			पूर्ण अन्यथा
				ax25_destroy_socket(ax25);
			वापस;
		पूर्ण
		अवरोध;

	हाल AX25_STATE_3:
	हाल AX25_STATE_4:
		/*
		 * Check the state of the receive buffer.
		 */
		अगर (sk != शून्य) अणु
			अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <
			    (sk->sk_rcvbuf >> 1) &&
			    (ax25->condition & AX25_COND_OWN_RX_BUSY)) अणु
				ax25->condition &= ~AX25_COND_OWN_RX_BUSY;
				ax25->condition &= ~AX25_COND_ACK_PENDING;
				ax25_send_control(ax25, AX25_RR, AX25_POLLOFF, AX25_RESPONSE);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sk)
		bh_unlock_sock(sk);

	ax25_start_heartbeat(ax25);
पूर्ण

व्योम ax25_std_t2समयr_expiry(ax25_cb *ax25)
अणु
	अगर (ax25->condition & AX25_COND_ACK_PENDING) अणु
		ax25->condition &= ~AX25_COND_ACK_PENDING;
		ax25_std_समयout_response(ax25);
	पूर्ण
पूर्ण

व्योम ax25_std_t3समयr_expiry(ax25_cb *ax25)
अणु
	ax25->n2count = 0;
	ax25_std_transmit_enquiry(ax25);
	ax25->state   = AX25_STATE_4;
पूर्ण

व्योम ax25_std_idleसमयr_expiry(ax25_cb *ax25)
अणु
	ax25_clear_queues(ax25);

	ax25->n2count = 0;
	ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
	ax25->state   = AX25_STATE_2;

	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
	ax25_stop_t2समयr(ax25);
	ax25_stop_t3समयr(ax25);

	अगर (ax25->sk != शून्य) अणु
		bh_lock_sock(ax25->sk);
		ax25->sk->sk_state     = TCP_CLOSE;
		ax25->sk->sk_err       = 0;
		ax25->sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		अगर (!sock_flag(ax25->sk, SOCK_DEAD)) अणु
			ax25->sk->sk_state_change(ax25->sk);
			sock_set_flag(ax25->sk, SOCK_DEAD);
		पूर्ण
		bh_unlock_sock(ax25->sk);
	पूर्ण
पूर्ण

व्योम ax25_std_t1समयr_expiry(ax25_cb *ax25)
अणु
	चयन (ax25->state) अणु
	हाल AX25_STATE_1:
		अगर (ax25->n2count == ax25->n2) अणु
			अगर (ax25->modulus == AX25_MODULUS) अणु
				ax25_disconnect(ax25, ETIMEDOUT);
				वापस;
			पूर्ण अन्यथा अणु
				ax25->modulus = AX25_MODULUS;
				ax25->winकरोw  = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
				ax25->n2count = 0;
				ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
			पूर्ण
		पूर्ण अन्यथा अणु
			ax25->n2count++;
			अगर (ax25->modulus == AX25_MODULUS)
				ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
			अन्यथा
				ax25_send_control(ax25, AX25_SABME, AX25_POLLON, AX25_COMMAND);
		पूर्ण
		अवरोध;

	हाल AX25_STATE_2:
		अगर (ax25->n2count == ax25->n2) अणु
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			अगर (!sock_flag(ax25->sk, SOCK_DESTROY))
				ax25_disconnect(ax25, ETIMEDOUT);
			वापस;
		पूर्ण अन्यथा अणु
			ax25->n2count++;
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
		पूर्ण
		अवरोध;

	हाल AX25_STATE_3:
		ax25->n2count = 1;
		ax25_std_transmit_enquiry(ax25);
		ax25->state   = AX25_STATE_4;
		अवरोध;

	हाल AX25_STATE_4:
		अगर (ax25->n2count == ax25->n2) अणु
			ax25_send_control(ax25, AX25_DM, AX25_POLLON, AX25_RESPONSE);
			ax25_disconnect(ax25, ETIMEDOUT);
			वापस;
		पूर्ण अन्यथा अणु
			ax25->n2count++;
			ax25_std_transmit_enquiry(ax25);
		पूर्ण
		अवरोध;
	पूर्ण

	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
पूर्ण
