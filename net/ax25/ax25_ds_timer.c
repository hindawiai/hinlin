<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <net/tcp_states.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

अटल व्योम ax25_ds_समयout(काष्ठा समयr_list *);

/*
 *	Add DAMA slave समयout समयr to समयr list.
 *	Unlike the connection based समयrs the समयout function माला_लो
 *	triggered every second. Please note that NET_AX25_DAMA_SLAVE_TIMEOUT
 *	(aka /proc/sys/net/ax25/अणुdevपूर्ण/dama_slave_समयout) is still in
 *	1/10th of a second.
 */

व्योम ax25_ds_setup_समयr(ax25_dev *ax25_dev)
अणु
	समयr_setup(&ax25_dev->dama.slave_समयr, ax25_ds_समयout, 0);
पूर्ण

व्योम ax25_ds_del_समयr(ax25_dev *ax25_dev)
अणु
	अगर (ax25_dev)
		del_समयr(&ax25_dev->dama.slave_समयr);
पूर्ण

व्योम ax25_ds_set_समयr(ax25_dev *ax25_dev)
अणु
	अगर (ax25_dev == शून्य)		/* paranoia */
		वापस;

	ax25_dev->dama.slave_समयout =
		msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_DS_TIMEOUT]) / 10;
	mod_समयr(&ax25_dev->dama.slave_समयr, jअगरfies + HZ);
पूर्ण

/*
 *	DAMA Slave Timeout
 *	Silently discard all (slave) connections in हाल our master क्रमgot us...
 */

अटल व्योम ax25_ds_समयout(काष्ठा समयr_list *t)
अणु
	ax25_dev *ax25_dev = from_समयr(ax25_dev, t, dama.slave_समयr);
	ax25_cb *ax25;

	अगर (ax25_dev == शून्य || !ax25_dev->dama.slave)
		वापस;			/* Yikes! */

	अगर (!ax25_dev->dama.slave_समयout || --ax25_dev->dama.slave_समयout) अणु
		ax25_ds_set_समयr(ax25_dev);
		वापस;
	पूर्ण

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(ax25, &ax25_list) अणु
		अगर (ax25->ax25_dev != ax25_dev || !(ax25->condition & AX25_COND_DAMA_MODE))
			जारी;

		ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
		ax25_disconnect(ax25, ETIMEDOUT);
	पूर्ण
	spin_unlock(&ax25_list_lock);

	ax25_dev_dama_off(ax25_dev);
पूर्ण

व्योम ax25_ds_heartbeat_expiry(ax25_cb *ax25)
अणु
	काष्ठा sock *sk=ax25->sk;

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
		/*
		 * Check the state of the receive buffer.
		 */
		अगर (sk != शून्य) अणु
			अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <
			    (sk->sk_rcvbuf >> 1) &&
			    (ax25->condition & AX25_COND_OWN_RX_BUSY)) अणु
				ax25->condition &= ~AX25_COND_OWN_RX_BUSY;
				ax25->condition &= ~AX25_COND_ACK_PENDING;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (sk)
		bh_unlock_sock(sk);

	ax25_start_heartbeat(ax25);
पूर्ण

/* dl1bke 960114: T3 works much like the IDLE समयout, but
 *                माला_लो reloaded with every frame क्रम this
 *		  connection.
 */
व्योम ax25_ds_t3समयr_expiry(ax25_cb *ax25)
अणु
	ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
	ax25_dama_off(ax25);
	ax25_disconnect(ax25, ETIMEDOUT);
पूर्ण

/* dl1bke 960228: बंद the connection when IDLE expires.
 *		  unlike T3 this समयr माला_लो reloaded only on
 *		  I frames.
 */
व्योम ax25_ds_idleसमयr_expiry(ax25_cb *ax25)
अणु
	ax25_clear_queues(ax25);

	ax25->n2count = 0;
	ax25->state = AX25_STATE_2;

	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
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

/* dl1bke 960114: The DAMA protocol requires to send data and SABM/DISC
 *                within the poll of any connected channel. Remember
 *                that we are not allowed to send anything unless we
 *                get polled by the Master.
 *
 *                Thus we'll have to करो parts of our T1 handling in
 *                ax25_enquiry_response().
 */
व्योम ax25_ds_t1_समयout(ax25_cb *ax25)
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
				ax25_send_control(ax25, AX25_SABM, AX25_POLLOFF, AX25_COMMAND);
			पूर्ण
		पूर्ण अन्यथा अणु
			ax25->n2count++;
			अगर (ax25->modulus == AX25_MODULUS)
				ax25_send_control(ax25, AX25_SABM, AX25_POLLOFF, AX25_COMMAND);
			अन्यथा
				ax25_send_control(ax25, AX25_SABME, AX25_POLLOFF, AX25_COMMAND);
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
		पूर्ण
		अवरोध;

	हाल AX25_STATE_3:
		अगर (ax25->n2count == ax25->n2) अणु
			ax25_send_control(ax25, AX25_DM, AX25_POLLON, AX25_RESPONSE);
			ax25_disconnect(ax25, ETIMEDOUT);
			वापस;
		पूर्ण अन्यथा अणु
			ax25->n2count++;
		पूर्ण
		अवरोध;
	पूर्ण

	ax25_calculate_t1(ax25);
	ax25_start_t1समयr(ax25);
पूर्ण
