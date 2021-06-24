<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Socket Timer Functions
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *
 *
 * Changes:
 *       Steve Whitehouse      : Made keepalive समयr part of the same
 *                               समयr idea.
 *       Steve Whitehouse      : Added checks क्रम sk->sock_पढ़ोers
 *       David S. Miller       : New socket locking
 *       Steve Whitehouse      : Timer grअसल socket ref.
 */
#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <net/sock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/flow.h>
#समावेश <net/dn.h>

/*
 * Slow समयr is क्रम everything अन्यथा (n * 500mS)
 */

#घोषणा SLOW_INTERVAL (HZ/2)

अटल व्योम dn_slow_समयr(काष्ठा समयr_list *t);

व्योम dn_start_slow_समयr(काष्ठा sock *sk)
अणु
	समयr_setup(&sk->sk_समयr, dn_slow_समयr, 0);
	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + SLOW_INTERVAL);
पूर्ण

व्योम dn_stop_slow_समयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &sk->sk_समयr);
पूर्ण

अटल व्योम dn_slow_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	काष्ठा dn_scp *scp = DN_SK(sk);

	bh_lock_sock(sk);

	अगर (sock_owned_by_user(sk)) अणु
		sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + HZ / 10);
		जाओ out;
	पूर्ण

	/*
	 * The persist समयr is the standard slow समयr used क्रम retransmits
	 * in both connection establishment and disconnection as well as
	 * in the RUN state. The dअगरferent states are catered क्रम by changing
	 * the function poपूर्णांकer in the socket. Setting the समयr to a value
	 * of zero turns it off. We allow the persist_fxn to turn the
	 * समयr off in a permant way by वापसing non-zero, so that
	 * समयr based routines may हटाओ sockets. This is why we have a
	 * sock_hold()/sock_put() around the समयr to prevent the socket
	 * going away in the middle.
	 */
	अगर (scp->persist && scp->persist_fxn) अणु
		अगर (scp->persist <= SLOW_INTERVAL) अणु
			scp->persist = 0;

			अगर (scp->persist_fxn(sk))
				जाओ out;
		पूर्ण अन्यथा अणु
			scp->persist -= SLOW_INTERVAL;
		पूर्ण
	पूर्ण

	/*
	 * Check क्रम keepalive समयout. After the other समयr 'cos अगर
	 * the previous समयr caused a retransmit, we करोn't need to
	 * करो this. scp->stamp is the last समय that we sent a packet.
	 * The keepalive function sends a link service packet to the
	 * other end. If it reमुख्यs unacknowledged, the standard
	 * socket समयrs will eventually shut the socket करोwn. Each
	 * समय we करो this, scp->stamp will be updated, thus
	 * we won't try and send another until scp->keepalive has passed
	 * since the last successful transmission.
	 */
	अगर (scp->keepalive && scp->keepalive_fxn && (scp->state == DN_RUN)) अणु
		अगर (समय_after_eq(jअगरfies, scp->stamp + scp->keepalive))
			scp->keepalive_fxn(sk);
	पूर्ण

	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + SLOW_INTERVAL);
out:
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण
