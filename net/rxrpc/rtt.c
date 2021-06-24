<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* RTT/RTO calculation.
 *
 * Adapted from TCP क्रम AF_RXRPC by David Howells (dhowells@redhat.com)
 *
 * https://tools.ietf.org/hपंचांगl/rfc6298
 * https://tools.ietf.org/hपंचांगl/rfc1122#section-4.2.3.1
 * http://ccr.sigcomm.org/archive/1995/jan95/ccr-9501-partridge87.pdf
 */

#समावेश <linux/net.h>
#समावेश "ar-internal.h"

#घोषणा RXRPC_RTO_MAX	((अचिन्हित)(120 * HZ))
#घोषणा RXRPC_TIMEOUT_INIT ((अचिन्हित)(1*HZ))	/* RFC6298 2.1 initial RTO value	*/
#घोषणा rxrpc_jअगरfies32 ((u32)jअगरfies)		/* As rxrpc_jअगरfies32 */

अटल u32 rxrpc_rto_min_us(काष्ठा rxrpc_peer *peer)
अणु
	वापस 200;
पूर्ण

अटल u32 __rxrpc_set_rto(स्थिर काष्ठा rxrpc_peer *peer)
अणु
	वापस _usecs_to_jअगरfies((peer->srtt_us >> 3) + peer->rttvar_us);
पूर्ण

अटल u32 rxrpc_bound_rto(u32 rto)
अणु
	वापस min(rto, RXRPC_RTO_MAX);
पूर्ण

/*
 * Called to compute a smoothed rtt estimate. The data fed to this
 * routine either comes from बारtamps, or from segments that were
 * known _not_ to have been retransmitted [see Karn/Partridge
 * Proceedings SIGCOMM 87]. The algorithm is from the SIGCOMM 88
 * piece by Van Jacobson.
 * NOTE: the next three routines used to be one big routine.
 * To save cycles in the RFC 1323 implementation it was better to अवरोध
 * it up पूर्णांकo three procedures. -- erics
 */
अटल व्योम rxrpc_rtt_estimator(काष्ठा rxrpc_peer *peer, दीर्घ sample_rtt_us)
अणु
	दीर्घ m = sample_rtt_us; /* RTT */
	u32 srtt = peer->srtt_us;

	/*	The following amusing code comes from Jacobson's
	 *	article in SIGCOMM '88.  Note that rtt and mdev
	 *	are scaled versions of rtt and mean deviation.
	 *	This is deचिन्हित to be as fast as possible
	 *	m stands क्रम "measurement".
	 *
	 *	On a 1990 paper the rto value is changed to:
	 *	RTO = rtt + 4 * mdev
	 *
	 * Funny. This algorithm seems to be very broken.
	 * These क्रमmulae increase RTO, when it should be decreased, increase
	 * too slowly, when it should be increased quickly, decrease too quickly
	 * etc. I guess in BSD RTO takes ONE value, so that it is असलolutely
	 * करोes not matter how to _calculate_ it. Seems, it was trap
	 * that VJ failed to aव्योम. 8)
	 */
	अगर (srtt != 0) अणु
		m -= (srtt >> 3);	/* m is now error in rtt est */
		srtt += m;		/* rtt = 7/8 rtt + 1/8 new */
		अगर (m < 0) अणु
			m = -m;		/* m is now असल(error) */
			m -= (peer->mdev_us >> 2);   /* similar update on mdev */
			/* This is similar to one of Eअगरel findings.
			 * Eअगरel blocks mdev updates when rtt decreases.
			 * This solution is a bit dअगरferent: we use finer gain
			 * क्रम mdev in this हाल (alpha*beta).
			 * Like Eअगरel it also prevents growth of rto,
			 * but also it limits too fast rto decreases,
			 * happening in pure Eअगरel.
			 */
			अगर (m > 0)
				m >>= 3;
		पूर्ण अन्यथा अणु
			m -= (peer->mdev_us >> 2);   /* similar update on mdev */
		पूर्ण

		peer->mdev_us += m;		/* mdev = 3/4 mdev + 1/4 new */
		अगर (peer->mdev_us > peer->mdev_max_us) अणु
			peer->mdev_max_us = peer->mdev_us;
			अगर (peer->mdev_max_us > peer->rttvar_us)
				peer->rttvar_us = peer->mdev_max_us;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no previous measure. */
		srtt = m << 3;		/* take the measured समय to be rtt */
		peer->mdev_us = m << 1;	/* make sure rto = 3*rtt */
		peer->rttvar_us = max(peer->mdev_us, rxrpc_rto_min_us(peer));
		peer->mdev_max_us = peer->rttvar_us;
	पूर्ण

	peer->srtt_us = max(1U, srtt);
पूर्ण

/*
 * Calculate rto without backoff.  This is the second half of Van Jacobson's
 * routine referred to above.
 */
अटल व्योम rxrpc_set_rto(काष्ठा rxrpc_peer *peer)
अणु
	u32 rto;

	/* 1. If rtt variance happened to be less 50msec, it is hallucination.
	 *    It cannot be less due to utterly erratic ACK generation made
	 *    at least by solaris and मुक्तbsd. "Erratic ACKs" has _nothing_
	 *    to करो with delayed acks, because at cwnd>2 true delack समयout
	 *    is invisible. Actually, Linux-2.4 also generates erratic
	 *    ACKs in some circumstances.
	 */
	rto = __rxrpc_set_rto(peer);

	/* 2. Fixups made earlier cannot be right.
	 *    If we करो not estimate RTO correctly without them,
	 *    all the algo is pure shit and should be replaced
	 *    with correct one. It is exactly, which we pretend to करो.
	 */

	/* NOTE: clamping at RXRPC_RTO_MIN is not required, current algo
	 * guarantees that rto is higher.
	 */
	peer->rto_j = rxrpc_bound_rto(rto);
पूर्ण

अटल व्योम rxrpc_ack_update_rtt(काष्ठा rxrpc_peer *peer, दीर्घ rtt_us)
अणु
	अगर (rtt_us < 0)
		वापस;

	//rxrpc_update_rtt_min(peer, rtt_us);
	rxrpc_rtt_estimator(peer, rtt_us);
	rxrpc_set_rto(peer);

	/* RFC6298: only reset backoff on valid RTT measurement. */
	peer->backoff = 0;
पूर्ण

/*
 * Add RTT inक्रमmation to cache.  This is called in softirq mode and has
 * exclusive access to the peer RTT data.
 */
व्योम rxrpc_peer_add_rtt(काष्ठा rxrpc_call *call, क्रमागत rxrpc_rtt_rx_trace why,
			पूर्णांक rtt_slot,
			rxrpc_serial_t send_serial, rxrpc_serial_t resp_serial,
			kसमय_प्रकार send_समय, kसमय_प्रकार resp_समय)
अणु
	काष्ठा rxrpc_peer *peer = call->peer;
	s64 rtt_us;

	rtt_us = kसमय_प्रकारo_us(kसमय_sub(resp_समय, send_समय));
	अगर (rtt_us < 0)
		वापस;

	spin_lock(&peer->rtt_input_lock);
	rxrpc_ack_update_rtt(peer, rtt_us);
	अगर (peer->rtt_count < 3)
		peer->rtt_count++;
	spin_unlock(&peer->rtt_input_lock);

	trace_rxrpc_rtt_rx(call, why, rtt_slot, send_serial, resp_serial,
			   peer->srtt_us >> 3, peer->rto_j);
पूर्ण

/*
 * Get the retransmission समयout to set in jअगरfies, backing it off each समय
 * we retransmit.
 */
अचिन्हित दीर्घ rxrpc_get_rto_backoff(काष्ठा rxrpc_peer *peer, bool retrans)
अणु
	u64 timo_j;
	u8 backoff = READ_ONCE(peer->backoff);

	timo_j = peer->rto_j;
	timo_j <<= backoff;
	अगर (retrans && timo_j * 2 <= RXRPC_RTO_MAX)
		WRITE_ONCE(peer->backoff, backoff + 1);

	अगर (timo_j < 1)
		timo_j = 1;

	वापस timo_j;
पूर्ण

व्योम rxrpc_peer_init_rtt(काष्ठा rxrpc_peer *peer)
अणु
	peer->rto_j	= RXRPC_TIMEOUT_INIT;
	peer->mdev_us	= jअगरfies_to_usecs(RXRPC_TIMEOUT_INIT);
	peer->backoff	= 0;
	//minmax_reset(&peer->rtt_min, rxrpc_jअगरfies32, ~0U);
पूर्ण
