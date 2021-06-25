<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 International Business Machines Corp.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * This module provides the असलtraction क्रम an SCTP transport representing
 * a remote transport address.  For local transport addresses, we just use
 * जोड़ sctp_addr.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Hui Huang             <hui.huang@nokia.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* 1st Level Abstractions.  */

/* Initialize a new transport from provided memory.  */
अटल काष्ठा sctp_transport *sctp_transport_init(काष्ठा net *net,
						  काष्ठा sctp_transport *peer,
						  स्थिर जोड़ sctp_addr *addr,
						  gfp_t gfp)
अणु
	/* Copy in the address.  */
	peer->af_specअगरic = sctp_get_af_specअगरic(addr->sa.sa_family);
	स_नकल(&peer->ipaddr, addr, peer->af_specअगरic->sockaddr_len);
	स_रखो(&peer->saddr, 0, माप(जोड़ sctp_addr));

	peer->sack_generation = 0;

	/* From 6.3.1 RTO Calculation:
	 *
	 * C1) Until an RTT measurement has been made क्रम a packet sent to the
	 * given destination transport address, set RTO to the protocol
	 * parameter 'RTO.Initial'.
	 */
	peer->rto = msecs_to_jअगरfies(net->sctp.rto_initial);

	peer->last_समय_heard = 0;
	peer->last_समय_ecne_reduced = jअगरfies;

	peer->param_flags = SPP_HB_DISABLE |
			    SPP_PMTUD_ENABLE |
			    SPP_SACKDELAY_ENABLE;

	/* Initialize the शेष path max_retrans.  */
	peer->pathmaxrxt  = net->sctp.max_retrans_path;
	peer->pf_retrans  = net->sctp.pf_retrans;

	INIT_LIST_HEAD(&peer->transmitted);
	INIT_LIST_HEAD(&peer->send_पढ़ोy);
	INIT_LIST_HEAD(&peer->transports);

	समयr_setup(&peer->T3_rtx_समयr, sctp_generate_t3_rtx_event, 0);
	समयr_setup(&peer->hb_समयr, sctp_generate_heartbeat_event, 0);
	समयr_setup(&peer->reconf_समयr, sctp_generate_reconf_event, 0);
	समयr_setup(&peer->proto_unreach_समयr,
		    sctp_generate_proto_unreach_event, 0);

	/* Initialize the 64-bit अक्रमom nonce sent with heartbeat. */
	get_अक्रमom_bytes(&peer->hb_nonce, माप(peer->hb_nonce));

	refcount_set(&peer->refcnt, 1);

	वापस peer;
पूर्ण

/* Allocate and initialize a new transport.  */
काष्ठा sctp_transport *sctp_transport_new(काष्ठा net *net,
					  स्थिर जोड़ sctp_addr *addr,
					  gfp_t gfp)
अणु
	काष्ठा sctp_transport *transport;

	transport = kzalloc(माप(*transport), gfp);
	अगर (!transport)
		जाओ fail;

	अगर (!sctp_transport_init(net, transport, addr, gfp))
		जाओ fail_init;

	SCTP_DBG_OBJCNT_INC(transport);

	वापस transport;

fail_init:
	kमुक्त(transport);

fail:
	वापस शून्य;
पूर्ण

/* This transport is no दीर्घer needed.  Free up अगर possible, or
 * delay until it last reference count.
 */
व्योम sctp_transport_मुक्त(काष्ठा sctp_transport *transport)
अणु
	/* Try to delete the heartbeat समयr.  */
	अगर (del_समयr(&transport->hb_समयr))
		sctp_transport_put(transport);

	/* Delete the T3_rtx समयr अगर it's active.
	 * There is no poपूर्णांक in not करोing this now and letting
	 * काष्ठाure hang around in memory since we know
	 * the transport is going away.
	 */
	अगर (del_समयr(&transport->T3_rtx_समयr))
		sctp_transport_put(transport);

	अगर (del_समयr(&transport->reconf_समयr))
		sctp_transport_put(transport);

	/* Delete the ICMP proto unreachable समयr अगर it's active. */
	अगर (del_समयr(&transport->proto_unreach_समयr))
		sctp_transport_put(transport);

	sctp_transport_put(transport);
पूर्ण

अटल व्योम sctp_transport_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा sctp_transport *transport;

	transport = container_of(head, काष्ठा sctp_transport, rcu);

	dst_release(transport->dst);
	kमुक्त(transport);
	SCTP_DBG_OBJCNT_DEC(transport);
पूर्ण

/* Destroy the transport data काष्ठाure.
 * Assumes there are no more users of this काष्ठाure.
 */
अटल व्योम sctp_transport_destroy(काष्ठा sctp_transport *transport)
अणु
	अगर (unlikely(refcount_पढ़ो(&transport->refcnt))) अणु
		WARN(1, "Attempt to destroy undead transport %p!\n", transport);
		वापस;
	पूर्ण

	sctp_packet_मुक्त(&transport->packet);

	अगर (transport->asoc)
		sctp_association_put(transport->asoc);

	call_rcu(&transport->rcu, sctp_transport_destroy_rcu);
पूर्ण

/* Start T3_rtx समयr अगर it is not alपढ़ोy running and update the heartbeat
 * समयr.  This routine is called every समय a DATA chunk is sent.
 */
व्योम sctp_transport_reset_t3_rtx(काष्ठा sctp_transport *transport)
अणु
	/* RFC 2960 6.3.2 Retransmission Timer Rules
	 *
	 * R1) Every समय a DATA chunk is sent to any address(including a
	 * retransmission), अगर the T3-rtx समयr of that address is not running
	 * start it running so that it will expire after the RTO of that
	 * address.
	 */

	अगर (!समयr_pending(&transport->T3_rtx_समयr))
		अगर (!mod_समयr(&transport->T3_rtx_समयr,
			       jअगरfies + transport->rto))
			sctp_transport_hold(transport);
पूर्ण

व्योम sctp_transport_reset_hb_समयr(काष्ठा sctp_transport *transport)
अणु
	अचिन्हित दीर्घ expires;

	/* When a data chunk is sent, reset the heartbeat पूर्णांकerval.  */
	expires = jअगरfies + sctp_transport_समयout(transport);
	अगर ((समय_beक्रमe(transport->hb_समयr.expires, expires) ||
	     !समयr_pending(&transport->hb_समयr)) &&
	    !mod_समयr(&transport->hb_समयr,
		       expires + pअक्रमom_u32_max(transport->rto)))
		sctp_transport_hold(transport);
पूर्ण

व्योम sctp_transport_reset_reconf_समयr(काष्ठा sctp_transport *transport)
अणु
	अगर (!समयr_pending(&transport->reconf_समयr))
		अगर (!mod_समयr(&transport->reconf_समयr,
			       jअगरfies + transport->rto))
			sctp_transport_hold(transport);
पूर्ण

/* This transport has been asचिन्हित to an association.
 * Initialize fields from the association or from the sock itself.
 * Register the reference count in the association.
 */
व्योम sctp_transport_set_owner(काष्ठा sctp_transport *transport,
			      काष्ठा sctp_association *asoc)
अणु
	transport->asoc = asoc;
	sctp_association_hold(asoc);
पूर्ण

/* Initialize the pmtu of a transport. */
व्योम sctp_transport_pmtu(काष्ठा sctp_transport *transport, काष्ठा sock *sk)
अणु
	/* If we करोn't have a fresh route, look one up */
	अगर (!transport->dst || transport->dst->obsolete) अणु
		sctp_transport_dst_release(transport);
		transport->af_specअगरic->get_dst(transport, &transport->saddr,
						&transport->fl, sk);
	पूर्ण

	अगर (transport->param_flags & SPP_PMTUD_DISABLE) अणु
		काष्ठा sctp_association *asoc = transport->asoc;

		अगर (!transport->pathmtu && asoc && asoc->pathmtu)
			transport->pathmtu = asoc->pathmtu;
		अगर (transport->pathmtu)
			वापस;
	पूर्ण

	अगर (transport->dst)
		transport->pathmtu = sctp_dst_mtu(transport->dst);
	अन्यथा
		transport->pathmtu = SCTP_DEFAULT_MAXSEGMENT;
पूर्ण

bool sctp_transport_update_pmtu(काष्ठा sctp_transport *t, u32 pmtu)
अणु
	काष्ठा dst_entry *dst = sctp_transport_dst_check(t);
	काष्ठा sock *sk = t->asoc->base.sk;
	bool change = true;

	अगर (unlikely(pmtu < SCTP_DEFAULT_MINSEGMENT)) अणु
		pr_warn_ratelimited("%s: Reported pmtu %d too low, using default minimum of %d\n",
				    __func__, pmtu, SCTP_DEFAULT_MINSEGMENT);
		/* Use शेष minimum segment instead */
		pmtu = SCTP_DEFAULT_MINSEGMENT;
	पूर्ण
	pmtu = SCTP_TRUNC4(pmtu);

	अगर (dst) अणु
		काष्ठा sctp_pf *pf = sctp_get_pf_specअगरic(dst->ops->family);
		जोड़ sctp_addr addr;

		pf->af->from_sk(&addr, sk);
		pf->to_sk_daddr(&t->ipaddr, sk);
		dst->ops->update_pmtu(dst, sk, शून्य, pmtu, true);
		pf->to_sk_daddr(&addr, sk);

		dst = sctp_transport_dst_check(t);
	पूर्ण

	अगर (!dst) अणु
		t->af_specअगरic->get_dst(t, &t->saddr, &t->fl, sk);
		dst = t->dst;
	पूर्ण

	अगर (dst) अणु
		/* Re-fetch, as under layers may have a higher minimum size */
		pmtu = sctp_dst_mtu(dst);
		change = t->pathmtu != pmtu;
	पूर्ण
	t->pathmtu = pmtu;

	वापस change;
पूर्ण

/* Caches the dst entry and source address क्रम a transport's destination
 * address.
 */
व्योम sctp_transport_route(काष्ठा sctp_transport *transport,
			  जोड़ sctp_addr *saddr, काष्ठा sctp_sock *opt)
अणु
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sctp_af *af = transport->af_specअगरic;

	sctp_transport_dst_release(transport);
	af->get_dst(transport, saddr, &transport->fl, sctp_opt2sk(opt));

	अगर (saddr)
		स_नकल(&transport->saddr, saddr, माप(जोड़ sctp_addr));
	अन्यथा
		af->get_saddr(opt, transport, &transport->fl);

	sctp_transport_pmtu(transport, sctp_opt2sk(opt));

	/* Initialize sk->sk_rcv_saddr, अगर the transport is the
	 * association's active path क्रम माला_लोockname().
	 */
	अगर (transport->dst && asoc &&
	    (!asoc->peer.primary_path || transport == asoc->peer.active_path))
		opt->pf->to_sk_saddr(&transport->saddr, asoc->base.sk);
पूर्ण

/* Hold a reference to a transport.  */
पूर्णांक sctp_transport_hold(काष्ठा sctp_transport *transport)
अणु
	वापस refcount_inc_not_zero(&transport->refcnt);
पूर्ण

/* Release a reference to a transport and clean up
 * अगर there are no more references.
 */
व्योम sctp_transport_put(काष्ठा sctp_transport *transport)
अणु
	अगर (refcount_dec_and_test(&transport->refcnt))
		sctp_transport_destroy(transport);
पूर्ण

/* Update transport's RTO based on the newly calculated RTT. */
व्योम sctp_transport_update_rto(काष्ठा sctp_transport *tp, __u32 rtt)
अणु
	अगर (unlikely(!tp->rto_pending))
		/* We should not be करोing any RTO updates unless rto_pending is set.  */
		pr_debug("%s: rto_pending not set on transport %p!\n", __func__, tp);

	अगर (tp->rttvar || tp->srtt) अणु
		काष्ठा net *net = tp->asoc->base.net;
		/* 6.3.1 C3) When a new RTT measurement R' is made, set
		 * RTTVAR <- (1 - RTO.Beta) * RTTVAR + RTO.Beta * |SRTT - R'|
		 * SRTT <- (1 - RTO.Alpha) * SRTT + RTO.Alpha * R'
		 */

		/* Note:  The above algorithm has been rewritten to
		 * express rto_beta and rto_alpha as inverse घातers
		 * of two.
		 * For example, assuming the शेष value of RTO.Alpha of
		 * 1/8, rto_alpha would be expressed as 3.
		 */
		tp->rttvar = tp->rttvar - (tp->rttvar >> net->sctp.rto_beta)
			+ (((__u32)असल((__s64)tp->srtt - (__s64)rtt)) >> net->sctp.rto_beta);
		tp->srtt = tp->srtt - (tp->srtt >> net->sctp.rto_alpha)
			+ (rtt >> net->sctp.rto_alpha);
	पूर्ण अन्यथा अणु
		/* 6.3.1 C2) When the first RTT measurement R is made, set
		 * SRTT <- R, RTTVAR <- R/2.
		 */
		tp->srtt = rtt;
		tp->rttvar = rtt >> 1;
	पूर्ण

	/* 6.3.1 G1) Whenever RTTVAR is computed, अगर RTTVAR = 0, then
	 * adjust RTTVAR <- G, where G is the CLOCK GRANULARITY.
	 */
	अगर (tp->rttvar == 0)
		tp->rttvar = SCTP_CLOCK_GRANULARITY;

	/* 6.3.1 C3) After the computation, update RTO <- SRTT + 4 * RTTVAR. */
	tp->rto = tp->srtt + (tp->rttvar << 2);

	/* 6.3.1 C6) Whenever RTO is computed, अगर it is less than RTO.Min
	 * seconds then it is rounded up to RTO.Min seconds.
	 */
	अगर (tp->rto < tp->asoc->rto_min)
		tp->rto = tp->asoc->rto_min;

	/* 6.3.1 C7) A maximum value may be placed on RTO provided it is
	 * at least RTO.max seconds.
	 */
	अगर (tp->rto > tp->asoc->rto_max)
		tp->rto = tp->asoc->rto_max;

	sctp_max_rto(tp->asoc, tp);
	tp->rtt = rtt;

	/* Reset rto_pending so that a new RTT measurement is started when a
	 * new data chunk is sent.
	 */
	tp->rto_pending = 0;

	pr_debug("%s: transport:%p, rtt:%d, srtt:%d rttvar:%d, rto:%ld\n",
		 __func__, tp, rtt, tp->srtt, tp->rttvar, tp->rto);
पूर्ण

/* This routine updates the transport's cwnd and partial_bytes_acked
 * parameters based on the bytes acked in the received SACK.
 */
व्योम sctp_transport_उठाओ_cwnd(काष्ठा sctp_transport *transport,
			       __u32 sack_ctsn, __u32 bytes_acked)
अणु
	काष्ठा sctp_association *asoc = transport->asoc;
	__u32 cwnd, ssthresh, flight_size, pba, pmtu;

	cwnd = transport->cwnd;
	flight_size = transport->flight_size;

	/* See अगर we need to निकास Fast Recovery first */
	अगर (asoc->fast_recovery &&
	    TSN_lte(asoc->fast_recovery_निकास, sack_ctsn))
		asoc->fast_recovery = 0;

	ssthresh = transport->ssthresh;
	pba = transport->partial_bytes_acked;
	pmtu = transport->asoc->pathmtu;

	अगर (cwnd <= ssthresh) अणु
		/* RFC 4960 7.2.1
		 * o  When cwnd is less than or equal to ssthresh, an SCTP
		 *    endpoपूर्णांक MUST use the slow-start algorithm to increase
		 *    cwnd only अगर the current congestion winकरोw is being fully
		 *    utilized, an incoming SACK advances the Cumulative TSN
		 *    Ack Poपूर्णांक, and the data sender is not in Fast Recovery.
		 *    Only when these three conditions are met can the cwnd be
		 *    increased; otherwise, the cwnd MUST not be increased.
		 *    If these conditions are met, then cwnd MUST be increased
		 *    by, at most, the lesser of 1) the total size of the
		 *    previously outstanding DATA chunk(s) acknowledged, and
		 *    2) the destination's path MTU.  This upper bound protects
		 *    against the ACK-Splitting attack outlined in [SAVAGE99].
		 */
		अगर (asoc->fast_recovery)
			वापस;

		/* The appropriate cwnd increase algorithm is perक्रमmed
		 * अगर, and only अगर the congestion winकरोw is being fully
		 * utilized.  Note that RFC4960 Errata 3.22 हटाओd the
		 * other condition on ctsn moving.
		 */
		अगर (flight_size < cwnd)
			वापस;

		अगर (bytes_acked > pmtu)
			cwnd += pmtu;
		अन्यथा
			cwnd += bytes_acked;

		pr_debug("%s: slow start: transport:%p, bytes_acked:%d, "
			 "cwnd:%d, ssthresh:%d, flight_size:%d, pba:%d\n",
			 __func__, transport, bytes_acked, cwnd, ssthresh,
			 flight_size, pba);
	पूर्ण अन्यथा अणु
		/* RFC 2960 7.2.2 Whenever cwnd is greater than ssthresh,
		 * upon each SACK arrival, increase partial_bytes_acked
		 * by the total number of bytes of all new chunks
		 * acknowledged in that SACK including chunks
		 * acknowledged by the new Cumulative TSN Ack and by Gap
		 * Ack Blocks. (updated by RFC4960 Errata 3.22)
		 *
		 * When partial_bytes_acked is greater than cwnd and
		 * beक्रमe the arrival of the SACK the sender had less
		 * bytes of data outstanding than cwnd (i.e., beक्रमe
		 * arrival of the SACK, flightsize was less than cwnd),
		 * reset partial_bytes_acked to cwnd. (RFC 4960 Errata
		 * 3.26)
		 *
		 * When partial_bytes_acked is equal to or greater than
		 * cwnd and beक्रमe the arrival of the SACK the sender
		 * had cwnd or more bytes of data outstanding (i.e.,
		 * beक्रमe arrival of the SACK, flightsize was greater
		 * than or equal to cwnd), partial_bytes_acked is reset
		 * to (partial_bytes_acked - cwnd). Next, cwnd is
		 * increased by MTU. (RFC 4960 Errata 3.12)
		 */
		pba += bytes_acked;
		अगर (pba > cwnd && flight_size < cwnd)
			pba = cwnd;
		अगर (pba >= cwnd && flight_size >= cwnd) अणु
			pba = pba - cwnd;
			cwnd += pmtu;
		पूर्ण

		pr_debug("%s: congestion avoidance: transport:%p, "
			 "bytes_acked:%d, cwnd:%d, ssthresh:%d, "
			 "flight_size:%d, pba:%d\n", __func__,
			 transport, bytes_acked, cwnd, ssthresh,
			 flight_size, pba);
	पूर्ण

	transport->cwnd = cwnd;
	transport->partial_bytes_acked = pba;
पूर्ण

/* This routine is used to lower the transport's cwnd when congestion is
 * detected.
 */
व्योम sctp_transport_lower_cwnd(काष्ठा sctp_transport *transport,
			       क्रमागत sctp_lower_cwnd reason)
अणु
	काष्ठा sctp_association *asoc = transport->asoc;

	चयन (reason) अणु
	हाल SCTP_LOWER_CWND_T3_RTX:
		/* RFC 2960 Section 7.2.3, sctpimpguide
		 * When the T3-rtx समयr expires on an address, SCTP should
		 * perक्रमm slow start by:
		 *      ssthresh = max(cwnd/2, 4*MTU)
		 *      cwnd = 1*MTU
		 *      partial_bytes_acked = 0
		 */
		transport->ssthresh = max(transport->cwnd/2,
					  4*asoc->pathmtu);
		transport->cwnd = asoc->pathmtu;

		/* T3-rtx also clears fast recovery */
		asoc->fast_recovery = 0;
		अवरोध;

	हाल SCTP_LOWER_CWND_FAST_RTX:
		/* RFC 2960 7.2.4 Adjust the ssthresh and cwnd of the
		 * destination address(es) to which the missing DATA chunks
		 * were last sent, according to the क्रमmula described in
		 * Section 7.2.3.
		 *
		 * RFC 2960 7.2.3, sctpimpguide Upon detection of packet
		 * losses from SACK (see Section 7.2.4), An endpoपूर्णांक
		 * should करो the following:
		 *      ssthresh = max(cwnd/2, 4*MTU)
		 *      cwnd = ssthresh
		 *      partial_bytes_acked = 0
		 */
		अगर (asoc->fast_recovery)
			वापस;

		/* Mark Fast recovery */
		asoc->fast_recovery = 1;
		asoc->fast_recovery_निकास = asoc->next_tsn - 1;

		transport->ssthresh = max(transport->cwnd/2,
					  4*asoc->pathmtu);
		transport->cwnd = transport->ssthresh;
		अवरोध;

	हाल SCTP_LOWER_CWND_ECNE:
		/* RFC 2481 Section 6.1.2.
		 * If the sender receives an ECN-Echo ACK packet
		 * then the sender knows that congestion was encountered in the
		 * network on the path from the sender to the receiver. The
		 * indication of congestion should be treated just as a
		 * congestion loss in non-ECN Capable TCP. That is, the TCP
		 * source halves the congestion winकरोw "cwnd" and reduces the
		 * slow start threshold "ssthresh".
		 * A critical condition is that TCP करोes not react to
		 * congestion indications more than once every winकरोw of
		 * data (or more loosely more than once every round-trip समय).
		 */
		अगर (समय_after(jअगरfies, transport->last_समय_ecne_reduced +
					transport->rtt)) अणु
			transport->ssthresh = max(transport->cwnd/2,
						  4*asoc->pathmtu);
			transport->cwnd = transport->ssthresh;
			transport->last_समय_ecne_reduced = jअगरfies;
		पूर्ण
		अवरोध;

	हाल SCTP_LOWER_CWND_INACTIVE:
		/* RFC 2960 Section 7.2.1, sctpimpguide
		 * When the endpoपूर्णांक करोes not transmit data on a given
		 * transport address, the cwnd of the transport address
		 * should be adjusted to max(cwnd/2, 4*MTU) per RTO.
		 * NOTE: Although the draft recommends that this check needs
		 * to be करोne every RTO पूर्णांकerval, we करो it every hearbeat
		 * पूर्णांकerval.
		 */
		transport->cwnd = max(transport->cwnd/2,
					 4*asoc->pathmtu);
		/* RFC 4960 Errata 3.27.2: also adjust sshthresh */
		transport->ssthresh = transport->cwnd;
		अवरोध;
	पूर्ण

	transport->partial_bytes_acked = 0;

	pr_debug("%s: transport:%p, reason:%d, cwnd:%d, ssthresh:%d\n",
		 __func__, transport, reason, transport->cwnd,
		 transport->ssthresh);
पूर्ण

/* Apply Max.Burst limit to the congestion winकरोw:
 * sctpimpguide-05 2.14.2
 * D) When the समय comes क्रम the sender to
 * transmit new DATA chunks, the protocol parameter Max.Burst MUST
 * first be applied to limit how many new DATA chunks may be sent.
 * The limit is applied by adjusting cwnd as follows:
 * 	अगर ((flightsize+ Max.Burst * MTU) < cwnd)
 * 		cwnd = flightsize + Max.Burst * MTU
 */

व्योम sctp_transport_burst_limited(काष्ठा sctp_transport *t)
अणु
	काष्ठा sctp_association *asoc = t->asoc;
	u32 old_cwnd = t->cwnd;
	u32 max_burst_bytes;

	अगर (t->burst_limited || asoc->max_burst == 0)
		वापस;

	max_burst_bytes = t->flight_size + (asoc->max_burst * asoc->pathmtu);
	अगर (max_burst_bytes < old_cwnd) अणु
		t->cwnd = max_burst_bytes;
		t->burst_limited = old_cwnd;
	पूर्ण
पूर्ण

/* Restore the old cwnd congestion winकरोw, after the burst had it's
 * desired effect.
 */
व्योम sctp_transport_burst_reset(काष्ठा sctp_transport *t)
अणु
	अगर (t->burst_limited) अणु
		t->cwnd = t->burst_limited;
		t->burst_limited = 0;
	पूर्ण
पूर्ण

/* What is the next समयout value क्रम this transport? */
अचिन्हित दीर्घ sctp_transport_समयout(काष्ठा sctp_transport *trans)
अणु
	/* RTO + समयr slack +/- 50% of RTO */
	अचिन्हित दीर्घ समयout = trans->rto >> 1;

	अगर (trans->state != SCTP_UNCONFIRMED &&
	    trans->state != SCTP_PF)
		समयout += trans->hbपूर्णांकerval;

	वापस max_t(अचिन्हित दीर्घ, समयout, HZ / 5);
पूर्ण

/* Reset transport variables to their initial values */
व्योम sctp_transport_reset(काष्ठा sctp_transport *t)
अणु
	काष्ठा sctp_association *asoc = t->asoc;

	/* RFC 2960 (bis), Section 5.2.4
	 * All the congestion control parameters (e.g., cwnd, ssthresh)
	 * related to this peer MUST be reset to their initial values
	 * (see Section 6.2.1)
	 */
	t->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));
	t->burst_limited = 0;
	t->ssthresh = asoc->peer.i.a_rwnd;
	t->rto = asoc->rto_initial;
	sctp_max_rto(asoc, t);
	t->rtt = 0;
	t->srtt = 0;
	t->rttvar = 0;

	/* Reset these additional variables so that we have a clean slate. */
	t->partial_bytes_acked = 0;
	t->flight_size = 0;
	t->error_count = 0;
	t->rto_pending = 0;
	t->hb_sent = 0;

	/* Initialize the state inक्रमmation क्रम SFR-CACC */
	t->cacc.changeover_active = 0;
	t->cacc.cycling_changeover = 0;
	t->cacc.next_tsn_at_change = 0;
	t->cacc.cacc_saw_newack = 0;
पूर्ण

/* Schedule retransmission on the given transport */
व्योम sctp_transport_immediate_rtx(काष्ठा sctp_transport *t)
अणु
	/* Stop pending T3_rtx_समयr */
	अगर (del_समयr(&t->T3_rtx_समयr))
		sctp_transport_put(t);

	sctp_retransmit(&t->asoc->outqueue, t, SCTP_RTXR_T3_RTX);
	अगर (!समयr_pending(&t->T3_rtx_समयr)) अणु
		अगर (!mod_समयr(&t->T3_rtx_समयr, jअगरfies + t->rto))
			sctp_transport_hold(t);
	पूर्ण
पूर्ण

/* Drop dst */
व्योम sctp_transport_dst_release(काष्ठा sctp_transport *t)
अणु
	dst_release(t->dst);
	t->dst = शून्य;
	t->dst_pending_confirm = 0;
पूर्ण

/* Schedule neighbour confirm */
व्योम sctp_transport_dst_confirm(काष्ठा sctp_transport *t)
अणु
	t->dst_pending_confirm = 1;
पूर्ण
