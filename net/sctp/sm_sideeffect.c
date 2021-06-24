<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions work with the state functions in sctp_sm_statefuns.c
 * to implement that state operations.  These functions implement the
 * steps which require modअगरying existing data काष्ठाures.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@austin.ibm.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Dajiang Zhang	    <dajiang.zhang@nokia.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/ip.h>
#समावेश <linux/gfp.h>
#समावेश <net/sock.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/stream_sched.h>

अटल पूर्णांक sctp_cmd_पूर्णांकerpreter(क्रमागत sctp_event_type event_type,
				जोड़ sctp_subtype subtype,
				क्रमागत sctp_state state,
				काष्ठा sctp_endpoपूर्णांक *ep,
				काष्ठा sctp_association *asoc,
				व्योम *event_arg,
				क्रमागत sctp_disposition status,
				काष्ठा sctp_cmd_seq *commands,
				gfp_t gfp);
अटल पूर्णांक sctp_side_effects(क्रमागत sctp_event_type event_type,
			     जोड़ sctp_subtype subtype,
			     क्रमागत sctp_state state,
			     काष्ठा sctp_endpoपूर्णांक *ep,
			     काष्ठा sctp_association **asoc,
			     व्योम *event_arg,
			     क्रमागत sctp_disposition status,
			     काष्ठा sctp_cmd_seq *commands,
			     gfp_t gfp);

/********************************************************************
 * Helper functions
 ********************************************************************/

/* A helper function क्रम delayed processing of INET ECN CE bit. */
अटल व्योम sctp_करो_ecn_ce_work(काष्ठा sctp_association *asoc,
				__u32 lowest_tsn)
अणु
	/* Save the TSN away क्रम comparison when we receive CWR */

	asoc->last_ecne_tsn = lowest_tsn;
	asoc->need_ecne = 1;
पूर्ण

/* Helper function क्रम delayed processing of SCTP ECNE chunk.  */
/* RFC 2960 Appendix A
 *
 * RFC 2481 details a specअगरic bit क्रम a sender to send in
 * the header of its next outbound TCP segment to indicate to
 * its peer that it has reduced its congestion winकरोw.  This
 * is termed the CWR bit.  For SCTP the same indication is made
 * by including the CWR chunk.  This chunk contains one data
 * element, i.e. the TSN number that was sent in the ECNE chunk.
 * This element represents the lowest TSN number in the datagram
 * that was originally marked with the CE bit.
 */
अटल काष्ठा sctp_chunk *sctp_करो_ecn_ecne_work(काष्ठा sctp_association *asoc,
						__u32 lowest_tsn,
						काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *repl;

	/* Our previously transmitted packet ran पूर्णांकo some congestion
	 * so we should take action by reducing cwnd and ssthresh
	 * and then ACK our peer that we we've करोne so by
	 * sending a CWR.
	 */

	/* First, try to determine अगर we want to actually lower
	 * our cwnd variables.  Only lower them अगर the ECNE looks more
	 * recent than the last response.
	 */
	अगर (TSN_lt(asoc->last_cwr_tsn, lowest_tsn)) अणु
		काष्ठा sctp_transport *transport;

		/* Find which transport's congestion variables
		 * need to be adjusted.
		 */
		transport = sctp_assoc_lookup_tsn(asoc, lowest_tsn);

		/* Update the congestion variables. */
		अगर (transport)
			sctp_transport_lower_cwnd(transport,
						  SCTP_LOWER_CWND_ECNE);
		asoc->last_cwr_tsn = lowest_tsn;
	पूर्ण

	/* Always try to quiet the other end.  In हाल of lost CWR,
	 * resend last_cwr_tsn.
	 */
	repl = sctp_make_cwr(asoc, asoc->last_cwr_tsn, chunk);

	/* If we run out of memory, it will look like a lost CWR.  We'll
	 * get back in sync eventually.
	 */
	वापस repl;
पूर्ण

/* Helper function to करो delayed processing of ECN CWR chunk.  */
अटल व्योम sctp_करो_ecn_cwr_work(काष्ठा sctp_association *asoc,
				 __u32 lowest_tsn)
अणु
	/* Turn off ECNE getting स्वतः-prepended to every outgoing
	 * packet
	 */
	asoc->need_ecne = 0;
पूर्ण

/* Generate SACK अगर necessary.  We call this at the end of a packet.  */
अटल पूर्णांक sctp_gen_sack(काष्ठा sctp_association *asoc, पूर्णांक क्रमce,
			 काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_transport *trans = asoc->peer.last_data_from;
	__u32 ctsn, max_tsn_seen;
	काष्ठा sctp_chunk *sack;
	पूर्णांक error = 0;

	अगर (क्रमce ||
	    (!trans && (asoc->param_flags & SPP_SACKDELAY_DISABLE)) ||
	    (trans && (trans->param_flags & SPP_SACKDELAY_DISABLE)))
		asoc->peer.sack_needed = 1;

	ctsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	max_tsn_seen = sctp_tsnmap_get_max_tsn_seen(&asoc->peer.tsn_map);

	/* From 12.2 Parameters necessary per association (i.e. the TCB):
	 *
	 * Ack State : This flag indicates अगर the next received packet
	 * 	     : is to be responded to with a SACK. ...
	 *	     : When DATA chunks are out of order, SACK's
	 *           : are not delayed (see Section 6).
	 *
	 * [This is actually not mentioned in Section 6, but we
	 * implement it here anyway. --piggy]
	 */
	अगर (max_tsn_seen != ctsn)
		asoc->peer.sack_needed = 1;

	/* From 6.2  Acknowledgement on Reception of DATA Chunks:
	 *
	 * Section 4.2 of [RFC2581] SHOULD be followed. Specअगरically,
	 * an acknowledgement SHOULD be generated क्रम at least every
	 * second packet (not every second DATA chunk) received, and
	 * SHOULD be generated within 200 ms of the arrival of any
	 * unacknowledged DATA chunk. ...
	 */
	अगर (!asoc->peer.sack_needed) अणु
		asoc->peer.sack_cnt++;

		/* Set the SACK delay समयout based on the
		 * SACK delay क्रम the last transport
		 * data was received from, or the शेष
		 * क्रम the association.
		 */
		अगर (trans) अणु
			/* We will need a SACK क्रम the next packet.  */
			अगर (asoc->peer.sack_cnt >= trans->sackfreq - 1)
				asoc->peer.sack_needed = 1;

			asoc->समयouts[SCTP_EVENT_TIMEOUT_SACK] =
				trans->sackdelay;
		पूर्ण अन्यथा अणु
			/* We will need a SACK क्रम the next packet.  */
			अगर (asoc->peer.sack_cnt >= asoc->sackfreq - 1)
				asoc->peer.sack_needed = 1;

			asoc->समयouts[SCTP_EVENT_TIMEOUT_SACK] =
				asoc->sackdelay;
		पूर्ण

		/* Restart the SACK समयr. */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	पूर्ण अन्यथा अणु
		__u32 old_a_rwnd = asoc->a_rwnd;

		asoc->a_rwnd = asoc->rwnd;
		sack = sctp_make_sack(asoc);
		अगर (!sack) अणु
			asoc->a_rwnd = old_a_rwnd;
			जाओ nomem;
		पूर्ण

		asoc->peer.sack_needed = 0;
		asoc->peer.sack_cnt = 0;

		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(sack));

		/* Stop the SACK समयr.  */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	पूर्ण

	वापस error;
nomem:
	error = -ENOMEM;
	वापस error;
पूर्ण

/* When the T3-RTX समयr expires, it calls this function to create the
 * relevant state machine event.
 */
व्योम sctp_generate_t3_rtx_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_transport *transport =
		from_समयr(transport, t, T3_rtx_समयr);
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक error;

	/* Check whether a task is in the sock.  */

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		pr_debug("%s: sock is busy\n", __func__);

		/* Try again later.  */
		अगर (!mod_समयr(&transport->T3_rtx_समयr, jअगरfies + (HZ/20)))
			sctp_transport_hold(transport);
		जाओ out_unlock;
	पूर्ण

	/* Run through the state machine.  */
	error = sctp_करो_sm(net, SCTP_EVENT_T_TIMEOUT,
			   SCTP_ST_TIMEOUT(SCTP_EVENT_TIMEOUT_T3_RTX),
			   asoc->state,
			   asoc->ep, asoc,
			   transport, GFP_ATOMIC);

	अगर (error)
		sk->sk_err = -error;

out_unlock:
	bh_unlock_sock(sk);
	sctp_transport_put(transport);
पूर्ण

/* This is a sa पूर्णांकerface क्रम producing समयout events.  It works
 * क्रम समयouts which use the association as their parameter.
 */
अटल व्योम sctp_generate_समयout_event(काष्ठा sctp_association *asoc,
					क्रमागत sctp_event_समयout समयout_type)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक error = 0;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		pr_debug("%s: sock is busy: timer %d\n", __func__,
			 समयout_type);

		/* Try again later.  */
		अगर (!mod_समयr(&asoc->समयrs[समयout_type], jअगरfies + (HZ/20)))
			sctp_association_hold(asoc);
		जाओ out_unlock;
	पूर्ण

	/* Is this association really dead and just रुकोing around क्रम
	 * the समयr to let go of the reference?
	 */
	अगर (asoc->base.dead)
		जाओ out_unlock;

	/* Run through the state machine.  */
	error = sctp_करो_sm(net, SCTP_EVENT_T_TIMEOUT,
			   SCTP_ST_TIMEOUT(समयout_type),
			   asoc->state, asoc->ep, asoc,
			   (व्योम *)समयout_type, GFP_ATOMIC);

	अगर (error)
		sk->sk_err = -error;

out_unlock:
	bh_unlock_sock(sk);
	sctp_association_put(asoc);
पूर्ण

अटल व्योम sctp_generate_t1_cookie_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_T1_COOKIE]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_T1_COOKIE);
पूर्ण

अटल व्योम sctp_generate_t1_init_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_T1_INIT]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_T1_INIT);
पूर्ण

अटल व्योम sctp_generate_t2_shutकरोwn_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_T2_SHUTDOWN);
पूर्ण

अटल व्योम sctp_generate_t4_rto_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_T4_RTO]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_T4_RTO);
पूर्ण

अटल व्योम sctp_generate_t5_shutकरोwn_guard_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t,
			   समयrs[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD]);

	sctp_generate_समयout_event(asoc,
				    SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD);

पूर्ण /* sctp_generate_t5_shutकरोwn_guard_event() */

अटल व्योम sctp_generate_स्वतःबंद_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_AUTOCLOSE]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_AUTOCLOSE);
पूर्ण

/* Generate a heart beat event.  If the sock is busy, reschedule.   Make
 * sure that the transport is still valid.
 */
व्योम sctp_generate_heartbeat_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_transport *transport = from_समयr(transport, t, hb_समयr);
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);
	u32 elapsed, समयout;
	पूर्णांक error = 0;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		pr_debug("%s: sock is busy\n", __func__);

		/* Try again later.  */
		अगर (!mod_समयr(&transport->hb_समयr, jअगरfies + (HZ/20)))
			sctp_transport_hold(transport);
		जाओ out_unlock;
	पूर्ण

	/* Check अगर we should still send the heartbeat or reschedule */
	elapsed = jअगरfies - transport->last_समय_sent;
	समयout = sctp_transport_समयout(transport);
	अगर (elapsed < समयout) अणु
		elapsed = समयout - elapsed;
		अगर (!mod_समयr(&transport->hb_समयr, jअगरfies + elapsed))
			sctp_transport_hold(transport);
		जाओ out_unlock;
	पूर्ण

	error = sctp_करो_sm(net, SCTP_EVENT_T_TIMEOUT,
			   SCTP_ST_TIMEOUT(SCTP_EVENT_TIMEOUT_HEARTBEAT),
			   asoc->state, asoc->ep, asoc,
			   transport, GFP_ATOMIC);

	अगर (error)
		sk->sk_err = -error;

out_unlock:
	bh_unlock_sock(sk);
	sctp_transport_put(transport);
पूर्ण

/* Handle the समयout of the ICMP protocol unreachable समयr.  Trigger
 * the correct state machine transition that will बंद the association.
 */
व्योम sctp_generate_proto_unreach_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_transport *transport =
		from_समयr(transport, t, proto_unreach_समयr);
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		pr_debug("%s: sock is busy\n", __func__);

		/* Try again later.  */
		अगर (!mod_समयr(&transport->proto_unreach_समयr,
				jअगरfies + (HZ/20)))
			sctp_transport_hold(transport);
		जाओ out_unlock;
	पूर्ण

	/* Is this काष्ठाure just रुकोing around क्रम us to actually
	 * get destroyed?
	 */
	अगर (asoc->base.dead)
		जाओ out_unlock;

	sctp_करो_sm(net, SCTP_EVENT_T_OTHER,
		   SCTP_ST_OTHER(SCTP_EVENT_ICMP_PROTO_UNREACH),
		   asoc->state, asoc->ep, asoc, transport, GFP_ATOMIC);

out_unlock:
	bh_unlock_sock(sk);
	sctp_transport_put(transport);
पूर्ण

 /* Handle the समयout of the RE-CONFIG समयr. */
व्योम sctp_generate_reconf_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_transport *transport =
		from_समयr(transport, t, reconf_समयr);
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक error = 0;

	bh_lock_sock(sk);
	अगर (sock_owned_by_user(sk)) अणु
		pr_debug("%s: sock is busy\n", __func__);

		/* Try again later.  */
		अगर (!mod_समयr(&transport->reconf_समयr, jअगरfies + (HZ / 20)))
			sctp_transport_hold(transport);
		जाओ out_unlock;
	पूर्ण

	error = sctp_करो_sm(net, SCTP_EVENT_T_TIMEOUT,
			   SCTP_ST_TIMEOUT(SCTP_EVENT_TIMEOUT_RECONF),
			   asoc->state, asoc->ep, asoc,
			   transport, GFP_ATOMIC);

	अगर (error)
		sk->sk_err = -error;

out_unlock:
	bh_unlock_sock(sk);
	sctp_transport_put(transport);
पूर्ण

/* Inject a SACK Timeout event पूर्णांकo the state machine.  */
अटल व्योम sctp_generate_sack_event(काष्ठा समयr_list *t)
अणु
	काष्ठा sctp_association *asoc =
		from_समयr(asoc, t, समयrs[SCTP_EVENT_TIMEOUT_SACK]);

	sctp_generate_समयout_event(asoc, SCTP_EVENT_TIMEOUT_SACK);
पूर्ण

sctp_समयr_event_t *sctp_समयr_events[SCTP_NUM_TIMEOUT_TYPES] = अणु
	[SCTP_EVENT_TIMEOUT_NONE] =		शून्य,
	[SCTP_EVENT_TIMEOUT_T1_COOKIE] =	sctp_generate_t1_cookie_event,
	[SCTP_EVENT_TIMEOUT_T1_INIT] =		sctp_generate_t1_init_event,
	[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] =	sctp_generate_t2_shutकरोwn_event,
	[SCTP_EVENT_TIMEOUT_T3_RTX] =		शून्य,
	[SCTP_EVENT_TIMEOUT_T4_RTO] =		sctp_generate_t4_rto_event,
	[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD] =
					sctp_generate_t5_shutकरोwn_guard_event,
	[SCTP_EVENT_TIMEOUT_HEARTBEAT] =	शून्य,
	[SCTP_EVENT_TIMEOUT_RECONF] =		शून्य,
	[SCTP_EVENT_TIMEOUT_SACK] =		sctp_generate_sack_event,
	[SCTP_EVENT_TIMEOUT_AUTOCLOSE] =	sctp_generate_स्वतःबंद_event,
पूर्ण;


/* RFC 2960 8.2 Path Failure Detection
 *
 * When its peer endpoपूर्णांक is multi-homed, an endpoपूर्णांक should keep a
 * error counter क्रम each of the destination transport addresses of the
 * peer endpoपूर्णांक.
 *
 * Each समय the T3-rtx समयr expires on any address, or when a
 * HEARTBEAT sent to an idle address is not acknowledged within a RTO,
 * the error counter of that destination address will be incremented.
 * When the value in the error counter exceeds the protocol parameter
 * 'Path.Max.Retrans' of that destination address, the endpoपूर्णांक should
 * mark the destination transport address as inactive, and a
 * notअगरication SHOULD be sent to the upper layer.
 *
 */
अटल व्योम sctp_करो_8_2_transport_strike(काष्ठा sctp_cmd_seq *commands,
					 काष्ठा sctp_association *asoc,
					 काष्ठा sctp_transport *transport,
					 पूर्णांक is_hb)
अणु
	/* The check क्रम association's overall error counter exceeding the
	 * threshold is करोne in the state function.
	 */
	/* We are here due to a समयr expiration.  If the समयr was
	 * not a HEARTBEAT, then normal error tracking is करोne.
	 * If the समयr was a heartbeat, we only increment error counts
	 * when we alपढ़ोy have an outstanding HEARTBEAT that has not
	 * been acknowledged.
	 * Additionally, some tranport states inhibit error increments.
	 */
	अगर (!is_hb) अणु
		asoc->overall_error_count++;
		अगर (transport->state != SCTP_INACTIVE)
			transport->error_count++;
	 पूर्ण अन्यथा अगर (transport->hb_sent) अणु
		अगर (transport->state != SCTP_UNCONFIRMED)
			asoc->overall_error_count++;
		अगर (transport->state != SCTP_INACTIVE)
			transport->error_count++;
	पूर्ण

	/* If the transport error count is greater than the pf_retrans
	 * threshold, and less than pathmaxrtx, and अगर the current state
	 * is SCTP_ACTIVE, then mark this transport as Partially Failed,
	 * see SCTP Quick Failover Draft, section 5.1
	 */
	अगर (asoc->base.net->sctp.pf_enable &&
	    transport->state == SCTP_ACTIVE &&
	    transport->error_count < transport->pathmaxrxt &&
	    transport->error_count > transport->pf_retrans) अणु

		sctp_assoc_control_transport(asoc, transport,
					     SCTP_TRANSPORT_PF,
					     0);

		/* Update the hb समयr to resend a heartbeat every rto */
		sctp_transport_reset_hb_समयr(transport);
	पूर्ण

	अगर (transport->state != SCTP_INACTIVE &&
	    (transport->error_count > transport->pathmaxrxt)) अणु
		pr_debug("%s: association:%p transport addr:%pISpc failed\n",
			 __func__, asoc, &transport->ipaddr.sa);

		sctp_assoc_control_transport(asoc, transport,
					     SCTP_TRANSPORT_DOWN,
					     SCTP_FAILED_THRESHOLD);
	पूर्ण

	अगर (transport->error_count > transport->ps_retrans &&
	    asoc->peer.primary_path == transport &&
	    asoc->peer.active_path != transport)
		sctp_assoc_set_primary(asoc, asoc->peer.active_path);

	/* E2) For the destination address क्रम which the समयr
	 * expires, set RTO <- RTO * 2 ("back off the timer").  The
	 * maximum value discussed in rule C7 above (RTO.max) may be
	 * used to provide an upper bound to this करोubling operation.
	 *
	 * Special Case:  the first HB करोesn't trigger exponential backoff.
	 * The first unacknowledged HB triggers it.  We करो this with a flag
	 * that indicates that we have an outstanding HB.
	 */
	अगर (!is_hb || transport->hb_sent) अणु
		transport->rto = min((transport->rto * 2), transport->asoc->rto_max);
		sctp_max_rto(asoc, transport);
	पूर्ण
पूर्ण

/* Worker routine to handle INIT command failure.  */
अटल व्योम sctp_cmd_init_failed(काष्ठा sctp_cmd_seq *commands,
				 काष्ठा sctp_association *asoc,
				 अचिन्हित पूर्णांक error)
अणु
	काष्ठा sctp_ulpevent *event;

	event = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_CANT_STR_ASSOC,
						(__u16)error, 0, 0, शून्य,
						GFP_ATOMIC);

	अगर (event)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(event));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	/* SEND_FAILED sent later when cleaning up the association. */
	asoc->outqueue.error = error;
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());
पूर्ण

/* Worker routine to handle SCTP_CMD_ASSOC_FAILED.  */
अटल व्योम sctp_cmd_assoc_failed(काष्ठा sctp_cmd_seq *commands,
				  काष्ठा sctp_association *asoc,
				  क्रमागत sctp_event_type event_type,
				  जोड़ sctp_subtype subtype,
				  काष्ठा sctp_chunk *chunk,
				  अचिन्हित पूर्णांक error)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_chunk *पात;

	/* Cancel any partial delivery in progress. */
	asoc->stream.si->पात_pd(&asoc->ulpq, GFP_ATOMIC);

	अगर (event_type == SCTP_EVENT_T_CHUNK && subtype.chunk == SCTP_CID_ABORT)
		event = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_COMM_LOST,
						(__u16)error, 0, 0, chunk,
						GFP_ATOMIC);
	अन्यथा
		event = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_COMM_LOST,
						(__u16)error, 0, 0, शून्य,
						GFP_ATOMIC);
	अगर (event)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(event));

	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		पात = sctp_make_violation_max_retrans(asoc, chunk);
		अगर (पात)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(पात));
	पूर्ण

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	/* SEND_FAILED sent later when cleaning up the association. */
	asoc->outqueue.error = error;
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());
पूर्ण

/* Process an init chunk (may be real INIT/INIT-ACK or an embedded INIT
 * inside the cookie.  In reality, this is only used क्रम INIT-ACK processing
 * since all other हालs use "temporary" associations and can करो all
 * their work in statefuns directly.
 */
अटल पूर्णांक sctp_cmd_process_init(काष्ठा sctp_cmd_seq *commands,
				 काष्ठा sctp_association *asoc,
				 काष्ठा sctp_chunk *chunk,
				 काष्ठा sctp_init_chunk *peer_init,
				 gfp_t gfp)
अणु
	पूर्णांक error;

	/* We only process the init as a sideeffect in a single
	 * हाल.   This is when we process the INIT-ACK.   If we
	 * fail during INIT processing (due to दो_स्मृति problems),
	 * just वापस the error and stop processing the stack.
	 */
	अगर (!sctp_process_init(asoc, chunk, sctp_source(chunk), peer_init, gfp))
		error = -ENOMEM;
	अन्यथा
		error = 0;

	वापस error;
पूर्ण

/* Helper function to अवरोध out starting up of heartbeat समयrs.  */
अटल व्योम sctp_cmd_hb_समयrs_start(काष्ठा sctp_cmd_seq *cmds,
				     काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *t;

	/* Start a heartbeat समयr क्रम each transport on the association.
	 * hold a reference on the transport to make sure none of
	 * the needed data काष्ठाures go away.
	 */
	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list, transports)
		sctp_transport_reset_hb_समयr(t);
पूर्ण

अटल व्योम sctp_cmd_hb_समयrs_stop(काष्ठा sctp_cmd_seq *cmds,
				    काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *t;

	/* Stop all heartbeat समयrs. */

	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
			transports) अणु
		अगर (del_समयr(&t->hb_समयr))
			sctp_transport_put(t);
	पूर्ण
पूर्ण

/* Helper function to stop any pending T3-RTX समयrs */
अटल व्योम sctp_cmd_t3_rtx_समयrs_stop(काष्ठा sctp_cmd_seq *cmds,
					काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *t;

	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
			transports) अणु
		अगर (del_समयr(&t->T3_rtx_समयr))
			sctp_transport_put(t);
	पूर्ण
पूर्ण


/* Helper function to handle the reception of an HEARTBEAT ACK.  */
अटल व्योम sctp_cmd_transport_on(काष्ठा sctp_cmd_seq *cmds,
				  काष्ठा sctp_association *asoc,
				  काष्ठा sctp_transport *t,
				  काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_sender_hb_info *hbinfo;
	पूर्णांक was_unconfirmed = 0;

	/* 8.3 Upon the receipt of the HEARTBEAT ACK, the sender of the
	 * HEARTBEAT should clear the error counter of the destination
	 * transport address to which the HEARTBEAT was sent.
	 */
	t->error_count = 0;

	/*
	 * Although RFC4960 specअगरies that the overall error count must
	 * be cleared when a HEARTBEAT ACK is received, we make an
	 * exception जबतक in SHUTDOWN PENDING. If the peer keeps its
	 * winकरोw shut क्रमever, we may never be able to transmit our
	 * outstanding data and rely on the retransmission limit be reached
	 * to shutकरोwn the association.
	 */
	अगर (t->asoc->state < SCTP_STATE_SHUTDOWN_PENDING)
		t->asoc->overall_error_count = 0;

	/* Clear the hb_sent flag to संकेत that we had a good
	 * acknowledgement.
	 */
	t->hb_sent = 0;

	/* Mark the destination transport address as active अगर it is not so
	 * marked.
	 */
	अगर ((t->state == SCTP_INACTIVE) || (t->state == SCTP_UNCONFIRMED)) अणु
		was_unconfirmed = 1;
		sctp_assoc_control_transport(asoc, t, SCTP_TRANSPORT_UP,
					     SCTP_HEARTBEAT_SUCCESS);
	पूर्ण

	अगर (t->state == SCTP_PF)
		sctp_assoc_control_transport(asoc, t, SCTP_TRANSPORT_UP,
					     SCTP_HEARTBEAT_SUCCESS);

	/* HB-ACK was received क्रम a the proper HB.  Consider this
	 * क्रमward progress.
	 */
	अगर (t->dst)
		sctp_transport_dst_confirm(t);

	/* The receiver of the HEARTBEAT ACK should also perक्रमm an
	 * RTT measurement क्रम that destination transport address
	 * using the समय value carried in the HEARTBEAT ACK chunk.
	 * If the transport's rto_pending variable has been cleared,
	 * it was most likely due to a retransmit.  However, we want
	 * to re-enable it to properly update the rto.
	 */
	अगर (t->rto_pending == 0)
		t->rto_pending = 1;

	hbinfo = (काष्ठा sctp_sender_hb_info *)chunk->skb->data;
	sctp_transport_update_rto(t, (jअगरfies - hbinfo->sent_at));

	/* Update the heartbeat समयr.  */
	sctp_transport_reset_hb_समयr(t);

	अगर (was_unconfirmed && asoc->peer.transport_count == 1)
		sctp_transport_immediate_rtx(t);
पूर्ण


/* Helper function to process the process SACK command.  */
अटल पूर्णांक sctp_cmd_process_sack(काष्ठा sctp_cmd_seq *cmds,
				 काष्ठा sctp_association *asoc,
				 काष्ठा sctp_chunk *chunk)
अणु
	पूर्णांक err = 0;

	अगर (sctp_outq_sack(&asoc->outqueue, chunk)) अणु
		/* There are no more TSNs aरुकोing SACK.  */
		err = sctp_करो_sm(asoc->base.net, SCTP_EVENT_T_OTHER,
				 SCTP_ST_OTHER(SCTP_EVENT_NO_PENDING_TSN),
				 asoc->state, asoc->ep, asoc, शून्य,
				 GFP_ATOMIC);
	पूर्ण

	वापस err;
पूर्ण

/* Helper function to set the समयout value क्रम T2-SHUTDOWN समयr and to set
 * the transport क्रम a shutकरोwn chunk.
 */
अटल व्योम sctp_cmd_setup_t2(काष्ठा sctp_cmd_seq *cmds,
			      काष्ठा sctp_association *asoc,
			      काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_transport *t;

	अगर (chunk->transport)
		t = chunk->transport;
	अन्यथा अणु
		t = sctp_assoc_choose_alter_transport(asoc,
					      asoc->shutकरोwn_last_sent_to);
		chunk->transport = t;
	पूर्ण
	asoc->shutकरोwn_last_sent_to = t;
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = t->rto;
पूर्ण

/* Helper function to change the state of an association. */
अटल व्योम sctp_cmd_new_state(काष्ठा sctp_cmd_seq *cmds,
			       काष्ठा sctp_association *asoc,
			       क्रमागत sctp_state state)
अणु
	काष्ठा sock *sk = asoc->base.sk;

	asoc->state = state;

	pr_debug("%s: asoc:%p[%s]\n", __func__, asoc, sctp_state_tbl[state]);

	अगर (sctp_style(sk, TCP)) अणु
		/* Change the sk->sk_state of a TCP-style socket that has
		 * successfully completed a connect() call.
		 */
		अगर (sctp_state(asoc, ESTABLISHED) && sctp_sstate(sk, CLOSED))
			inet_sk_set_state(sk, SCTP_SS_ESTABLISHED);

		/* Set the RCV_SHUTDOWN flag when a SHUTDOWN is received. */
		अगर (sctp_state(asoc, SHUTDOWN_RECEIVED) &&
		    sctp_sstate(sk, ESTABLISHED)) अणु
			inet_sk_set_state(sk, SCTP_SS_CLOSING);
			sk->sk_shutकरोwn |= RCV_SHUTDOWN;
		पूर्ण
	पूर्ण

	अगर (sctp_state(asoc, COOKIE_WAIT)) अणु
		/* Reset init समयouts since they may have been
		 * increased due to समयr expirations.
		 */
		asoc->समयouts[SCTP_EVENT_TIMEOUT_T1_INIT] =
						asoc->rto_initial;
		asoc->समयouts[SCTP_EVENT_TIMEOUT_T1_COOKIE] =
						asoc->rto_initial;
	पूर्ण

	अगर (sctp_state(asoc, ESTABLISHED)) अणु
		kमुक्त(asoc->peer.cookie);
		asoc->peer.cookie = शून्य;
	पूर्ण

	अगर (sctp_state(asoc, ESTABLISHED) ||
	    sctp_state(asoc, CLOSED) ||
	    sctp_state(asoc, SHUTDOWN_RECEIVED)) अणु
		/* Wake up any processes रुकोing in the asoc's रुको queue in
		 * sctp_रुको_क्रम_connect() or sctp_रुको_क्रम_sndbuf().
		 */
		अगर (रुकोqueue_active(&asoc->रुको))
			wake_up_पूर्णांकerruptible(&asoc->रुको);

		/* Wake up any processes रुकोing in the sk's sleep queue of
		 * a TCP-style or UDP-style peeled-off socket in
		 * sctp_रुको_क्रम_accept() or sctp_रुको_क्रम_packet().
		 * For a UDP-style socket, the रुकोers are woken up by the
		 * notअगरications.
		 */
		अगर (!sctp_style(sk, UDP))
			sk->sk_state_change(sk);
	पूर्ण

	अगर (sctp_state(asoc, SHUTDOWN_PENDING) &&
	    !sctp_outq_is_empty(&asoc->outqueue))
		sctp_outq_uncork(&asoc->outqueue, GFP_ATOMIC);
पूर्ण

/* Helper function to delete an association. */
अटल व्योम sctp_cmd_delete_tcb(काष्ठा sctp_cmd_seq *cmds,
				काष्ठा sctp_association *asoc)
अणु
	काष्ठा sock *sk = asoc->base.sk;

	/* If it is a non-temporary association beदीर्घing to a TCP-style
	 * listening socket that is not बंदd, करो not मुक्त it so that accept()
	 * can pick it up later.
	 */
	अगर (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING) &&
	    (!asoc->temp) && (sk->sk_shutकरोwn != SHUTDOWN_MASK))
		वापस;

	sctp_association_मुक्त(asoc);
पूर्ण

/*
 * ADDIP Section 4.1 ASCONF Chunk Procedures
 * A4) Start a T-4 RTO समयr, using the RTO value of the selected
 * destination address (we use active path instead of primary path just
 * because primary path may be inactive.
 */
अटल व्योम sctp_cmd_setup_t4(काष्ठा sctp_cmd_seq *cmds,
			      काष्ठा sctp_association *asoc,
			      काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_transport *t;

	t = sctp_assoc_choose_alter_transport(asoc, chunk->transport);
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T4_RTO] = t->rto;
	chunk->transport = t;
पूर्ण

/* Process an incoming Operation Error Chunk. */
अटल व्योम sctp_cmd_process_operr(काष्ठा sctp_cmd_seq *cmds,
				   काष्ठा sctp_association *asoc,
				   काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_errhdr *err_hdr;
	काष्ठा sctp_ulpevent *ev;

	जबतक (chunk->chunk_end > chunk->skb->data) अणु
		err_hdr = (काष्ठा sctp_errhdr *)(chunk->skb->data);

		ev = sctp_ulpevent_make_remote_error(asoc, chunk, 0,
						     GFP_ATOMIC);
		अगर (!ev)
			वापस;

		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);

		चयन (err_hdr->cause) अणु
		हाल SCTP_ERROR_UNKNOWN_CHUNK:
		अणु
			काष्ठा sctp_chunkhdr *unk_chunk_hdr;

			unk_chunk_hdr = (काष्ठा sctp_chunkhdr *)
							err_hdr->variable;
			चयन (unk_chunk_hdr->type) अणु
			/* ADDIP 4.1 A9) If the peer responds to an ASCONF with
			 * an ERROR chunk reporting that it did not recognized
			 * the ASCONF chunk type, the sender of the ASCONF MUST
			 * NOT send any further ASCONF chunks and MUST stop its
			 * T-4 समयr.
			 */
			हाल SCTP_CID_ASCONF:
				अगर (asoc->peer.asconf_capable == 0)
					अवरोध;

				asoc->peer.asconf_capable = 0;
				sctp_add_cmd_sf(cmds, SCTP_CMD_TIMER_STOP,
					SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Helper function to हटाओ the association non-primary peer
 * transports.
 */
अटल व्योम sctp_cmd_del_non_primary(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *t;
	काष्ठा list_head *temp;
	काष्ठा list_head *pos;

	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		t = list_entry(pos, काष्ठा sctp_transport, transports);
		अगर (!sctp_cmp_addr_exact(&t->ipaddr,
					 &asoc->peer.primary_addr)) अणु
			sctp_assoc_rm_peer(asoc, t);
		पूर्ण
	पूर्ण
पूर्ण

/* Helper function to set sk_err on a 1-1 style socket. */
अटल व्योम sctp_cmd_set_sk_err(काष्ठा sctp_association *asoc, पूर्णांक error)
अणु
	काष्ठा sock *sk = asoc->base.sk;

	अगर (!sctp_style(sk, UDP))
		sk->sk_err = error;
पूर्ण

/* Helper function to generate an association change event */
अटल व्योम sctp_cmd_assoc_change(काष्ठा sctp_cmd_seq *commands,
				  काष्ठा sctp_association *asoc,
				  u8 state)
अणु
	काष्ठा sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_assoc_change(asoc, 0, state, 0,
					    asoc->c.sinit_num_ostreams,
					    asoc->c.sinit_max_instreams,
					    शून्य, GFP_ATOMIC);
	अगर (ev)
		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
पूर्ण

अटल व्योम sctp_cmd_peer_no_auth(काष्ठा sctp_cmd_seq *commands,
				  काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_authkey(asoc, 0, SCTP_AUTH_NO_AUTH, GFP_ATOMIC);
	अगर (ev)
		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
पूर्ण

/* Helper function to generate an adaptation indication event */
अटल व्योम sctp_cmd_adaptation_ind(काष्ठा sctp_cmd_seq *commands,
				    काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_adaptation_indication(asoc, GFP_ATOMIC);

	अगर (ev)
		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
पूर्ण


अटल व्योम sctp_cmd_t1_समयr_update(काष्ठा sctp_association *asoc,
				     क्रमागत sctp_event_समयout समयr,
				     अक्षर *name)
अणु
	काष्ठा sctp_transport *t;

	t = asoc->init_last_sent_to;
	asoc->init_err_counter++;

	अगर (t->init_sent_count > (asoc->init_cycle + 1)) अणु
		asoc->समयouts[समयr] *= 2;
		अगर (asoc->समयouts[समयr] > asoc->max_init_समयo) अणु
			asoc->समयouts[समयr] = asoc->max_init_समयo;
		पूर्ण
		asoc->init_cycle++;

		pr_debug("%s: T1[%s] timeout adjustment init_err_counter:%d"
			 " cycle:%d timeout:%ld\n", __func__, name,
			 asoc->init_err_counter, asoc->init_cycle,
			 asoc->समयouts[समयr]);
	पूर्ण

पूर्ण

/* Send the whole message, chunk by chunk, to the outqueue.
 * This way the whole message is queued up and bundling अगर
 * encouraged क्रम small fragments.
 */
अटल व्योम sctp_cmd_send_msg(काष्ठा sctp_association *asoc,
			      काष्ठा sctp_datamsg *msg, gfp_t gfp)
अणु
	काष्ठा sctp_chunk *chunk;

	list_क्रम_each_entry(chunk, &msg->chunks, frag_list)
		sctp_outq_tail(&asoc->outqueue, chunk, gfp);

	asoc->outqueue.sched->enqueue(&asoc->outqueue, msg);
पूर्ण


/* These three macros allow us to pull the debugging code out of the
 * मुख्य flow of sctp_करो_sm() to keep attention focused on the real
 * functionality there.
 */
#घोषणा debug_pre_sfn() \
	pr_debug("%s[pre-fn]: ep:%p, %s, %s, asoc:%p[%s], %s\n", __func__, \
		 ep, sctp_evttype_tbl[event_type], (*debug_fn)(subtype),   \
		 asoc, sctp_state_tbl[state], state_fn->name)

#घोषणा debug_post_sfn() \
	pr_debug("%s[post-fn]: asoc:%p, status:%s\n", __func__, asoc, \
		 sctp_status_tbl[status])

#घोषणा debug_post_sfx() \
	pr_debug("%s[post-sfx]: error:%d, asoc:%p[%s]\n", __func__, error, \
		 asoc, sctp_state_tbl[(asoc && sctp_id2assoc(ep->base.sk, \
		 sctp_assoc2id(asoc))) ? asoc->state : SCTP_STATE_CLOSED])

/*
 * This is the master state machine processing function.
 *
 * If you want to understand all of lksctp, this is a
 * good place to start.
 */
पूर्णांक sctp_करो_sm(काष्ठा net *net, क्रमागत sctp_event_type event_type,
	       जोड़ sctp_subtype subtype, क्रमागत sctp_state state,
	       काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sctp_association *asoc,
	       व्योम *event_arg, gfp_t gfp)
अणु
	प्रकार स्थिर अक्षर *(म_लिखोn_t)(जोड़ sctp_subtype);
	अटल म_लिखोn_t *table[] = अणु
		शून्य, sctp_cname, sctp_tname, sctp_oname, sctp_pname,
	पूर्ण;
	म_लिखोn_t *debug_fn  __attribute__ ((unused)) = table[event_type];
	स्थिर काष्ठा sctp_sm_table_entry *state_fn;
	काष्ठा sctp_cmd_seq commands;
	क्रमागत sctp_disposition status;
	पूर्णांक error = 0;

	/* Look up the state function, run it, and then process the
	 * side effects.  These three steps are the heart of lksctp.
	 */
	state_fn = sctp_sm_lookup_event(net, event_type, state, subtype);

	sctp_init_cmd_seq(&commands);

	debug_pre_sfn();
	status = state_fn->fn(net, ep, asoc, subtype, event_arg, &commands);
	debug_post_sfn();

	error = sctp_side_effects(event_type, subtype, state,
				  ep, &asoc, event_arg, status,
				  &commands, gfp);
	debug_post_sfx();

	वापस error;
पूर्ण

/*****************************************************************
 * This the master state function side effect processing function.
 *****************************************************************/
अटल पूर्णांक sctp_side_effects(क्रमागत sctp_event_type event_type,
			     जोड़ sctp_subtype subtype,
			     क्रमागत sctp_state state,
			     काष्ठा sctp_endpoपूर्णांक *ep,
			     काष्ठा sctp_association **asoc,
			     व्योम *event_arg,
			     क्रमागत sctp_disposition status,
			     काष्ठा sctp_cmd_seq *commands,
			     gfp_t gfp)
अणु
	पूर्णांक error;

	/* FIXME - Most of the dispositions left today would be categorized
	 * as "exceptional" dispositions.  For those dispositions, it
	 * may not be proper to run through any of the commands at all.
	 * For example, the command पूर्णांकerpreter might be run only with
	 * disposition SCTP_DISPOSITION_CONSUME.
	 */
	अगर (0 != (error = sctp_cmd_पूर्णांकerpreter(event_type, subtype, state,
					       ep, *asoc,
					       event_arg, status,
					       commands, gfp)))
		जाओ bail;

	चयन (status) अणु
	हाल SCTP_DISPOSITION_DISCARD:
		pr_debug("%s: ignored sctp protocol event - state:%d, "
			 "event_type:%d, event_id:%d\n", __func__, state,
			 event_type, subtype.chunk);
		अवरोध;

	हाल SCTP_DISPOSITION_NOMEM:
		/* We ran out of memory, so we need to discard this
		 * packet.
		 */
		/* BUG--we should now recover some memory, probably by
		 * reneging...
		 */
		error = -ENOMEM;
		अवरोध;

	हाल SCTP_DISPOSITION_DELETE_TCB:
	हाल SCTP_DISPOSITION_ABORT:
		/* This should now be a command. */
		*asoc = शून्य;
		अवरोध;

	हाल SCTP_DISPOSITION_CONSUME:
		/*
		 * We should no दीर्घer have much work to करो here as the
		 * real work has been करोne as explicit commands above.
		 */
		अवरोध;

	हाल SCTP_DISPOSITION_VIOLATION:
		net_err_ratelimited("protocol violation state %d chunkid %d\n",
				    state, subtype.chunk);
		अवरोध;

	हाल SCTP_DISPOSITION_NOT_IMPL:
		pr_warn("unimplemented feature in state %d, event_type %d, event_id %d\n",
			state, event_type, subtype.chunk);
		अवरोध;

	हाल SCTP_DISPOSITION_BUG:
		pr_err("bug in state %d, event_type %d, event_id %d\n",
		       state, event_type, subtype.chunk);
		BUG();
		अवरोध;

	शेष:
		pr_err("impossible disposition %d in state %d, event_type %d, event_id %d\n",
		       status, state, event_type, subtype.chunk);
		BUG();
		अवरोध;
	पूर्ण

bail:
	वापस error;
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* This is the side-effect पूर्णांकerpreter.  */
अटल पूर्णांक sctp_cmd_पूर्णांकerpreter(क्रमागत sctp_event_type event_type,
				जोड़ sctp_subtype subtype,
				क्रमागत sctp_state state,
				काष्ठा sctp_endpoपूर्णांक *ep,
				काष्ठा sctp_association *asoc,
				व्योम *event_arg,
				क्रमागत sctp_disposition status,
				काष्ठा sctp_cmd_seq *commands,
				gfp_t gfp)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(ep->base.sk);
	काष्ठा sctp_chunk *chunk = शून्य, *new_obj;
	काष्ठा sctp_packet *packet;
	काष्ठा sctp_sackhdr sackh;
	काष्ठा समयr_list *समयr;
	काष्ठा sctp_transport *t;
	अचिन्हित दीर्घ समयout;
	काष्ठा sctp_cmd *cmd;
	पूर्णांक local_cork = 0;
	पूर्णांक error = 0;
	पूर्णांक क्रमce;

	अगर (SCTP_EVENT_T_TIMEOUT != event_type)
		chunk = event_arg;

	/* Note:  This whole file is a huge candidate क्रम rework.
	 * For example, each command could either have its own handler, so
	 * the loop would look like:
	 *     जबतक (cmds)
	 *         cmd->handle(x, y, z)
	 * --jgrimm
	 */
	जबतक (शून्य != (cmd = sctp_next_cmd(commands))) अणु
		चयन (cmd->verb) अणु
		हाल SCTP_CMD_NOP:
			/* Do nothing. */
			अवरोध;

		हाल SCTP_CMD_NEW_ASOC:
			/* Register a new association.  */
			अगर (local_cork) अणु
				sctp_outq_uncork(&asoc->outqueue, gfp);
				local_cork = 0;
			पूर्ण

			/* Register with the endpoपूर्णांक.  */
			asoc = cmd->obj.asoc;
			BUG_ON(asoc->peer.primary_path == शून्य);
			sctp_endpoपूर्णांक_add_asoc(ep, asoc);
			अवरोध;

		हाल SCTP_CMD_PURGE_OUTQUEUE:
		       sctp_outq_tearकरोwn(&asoc->outqueue);
		       अवरोध;

		हाल SCTP_CMD_DELETE_TCB:
			अगर (local_cork) अणु
				sctp_outq_uncork(&asoc->outqueue, gfp);
				local_cork = 0;
			पूर्ण
			/* Delete the current association.  */
			sctp_cmd_delete_tcb(commands, asoc);
			asoc = शून्य;
			अवरोध;

		हाल SCTP_CMD_NEW_STATE:
			/* Enter a new state.  */
			sctp_cmd_new_state(commands, asoc, cmd->obj.state);
			अवरोध;

		हाल SCTP_CMD_REPORT_TSN:
			/* Record the arrival of a TSN.  */
			error = sctp_tsnmap_mark(&asoc->peer.tsn_map,
						 cmd->obj.u32, शून्य);
			अवरोध;

		हाल SCTP_CMD_REPORT_FWDTSN:
			asoc->stream.si->report_ftsn(&asoc->ulpq, cmd->obj.u32);
			अवरोध;

		हाल SCTP_CMD_PROCESS_FWDTSN:
			asoc->stream.si->handle_ftsn(&asoc->ulpq,
						     cmd->obj.chunk);
			अवरोध;

		हाल SCTP_CMD_GEN_SACK:
			/* Generate a Selective ACK.
			 * The argument tells us whether to just count
			 * the packet and MAYBE generate a SACK, or
			 * क्रमce a SACK out.
			 */
			क्रमce = cmd->obj.i32;
			error = sctp_gen_sack(asoc, क्रमce, commands);
			अवरोध;

		हाल SCTP_CMD_PROCESS_SACK:
			/* Process an inbound SACK.  */
			error = sctp_cmd_process_sack(commands, asoc,
						      cmd->obj.chunk);
			अवरोध;

		हाल SCTP_CMD_GEN_INIT_ACK:
			/* Generate an INIT ACK chunk.  */
			new_obj = sctp_make_init_ack(asoc, chunk, GFP_ATOMIC,
						     0);
			अगर (!new_obj) अणु
				error = -ENOMEM;
				अवरोध;
			पूर्ण

			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(new_obj));
			अवरोध;

		हाल SCTP_CMD_PEER_INIT:
			/* Process a unअगरied INIT from the peer.
			 * Note: Only used during INIT-ACK processing.  If
			 * there is an error just वापस to the outter
			 * layer which will bail.
			 */
			error = sctp_cmd_process_init(commands, asoc, chunk,
						      cmd->obj.init, gfp);
			अवरोध;

		हाल SCTP_CMD_GEN_COOKIE_ECHO:
			/* Generate a COOKIE ECHO chunk.  */
			new_obj = sctp_make_cookie_echo(asoc, chunk);
			अगर (!new_obj) अणु
				अगर (cmd->obj.chunk)
					sctp_chunk_मुक्त(cmd->obj.chunk);
				error = -ENOMEM;
				अवरोध;
			पूर्ण
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(new_obj));

			/* If there is an ERROR chunk to be sent aदीर्घ with
			 * the COOKIE_ECHO, send it, too.
			 */
			अगर (cmd->obj.chunk)
				sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
						SCTP_CHUNK(cmd->obj.chunk));

			अगर (new_obj->transport) अणु
				new_obj->transport->init_sent_count++;
				asoc->init_last_sent_to = new_obj->transport;
			पूर्ण

			/* FIXME - Eventually come up with a cleaner way to
			 * enabling COOKIE-ECHO + DATA bundling during
			 * multihoming stale cookie scenarios, the following
			 * command plays with asoc->peer.retran_path to
			 * aव्योम the problem of sending the COOKIE-ECHO and
			 * DATA in dअगरferent paths, which could result
			 * in the association being ABORTed अगर the DATA chunk
			 * is processed first by the server.  Checking the
			 * init error counter simply causes this command
			 * to be executed only during failed attempts of
			 * association establishment.
			 */
			अगर ((asoc->peer.retran_path !=
			     asoc->peer.primary_path) &&
			    (asoc->init_err_counter > 0)) अणु
				sctp_add_cmd_sf(commands,
						SCTP_CMD_FORCE_PRIM_RETRAN,
						SCTP_शून्य());
			पूर्ण

			अवरोध;

		हाल SCTP_CMD_GEN_SHUTDOWN:
			/* Generate SHUTDOWN when in SHUTDOWN_SENT state.
			 * Reset error counts.
			 */
			asoc->overall_error_count = 0;

			/* Generate a SHUTDOWN chunk.  */
			new_obj = sctp_make_shutकरोwn(asoc, chunk);
			अगर (!new_obj) अणु
				error = -ENOMEM;
				अवरोध;
			पूर्ण
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(new_obj));
			अवरोध;

		हाल SCTP_CMD_CHUNK_ULP:
			/* Send a chunk to the sockets layer.  */
			pr_debug("%s: sm_sideff: chunk_up:%p, ulpq:%p\n",
				 __func__, cmd->obj.chunk, &asoc->ulpq);

			asoc->stream.si->ulpevent_data(&asoc->ulpq,
						       cmd->obj.chunk,
						       GFP_ATOMIC);
			अवरोध;

		हाल SCTP_CMD_EVENT_ULP:
			/* Send a notअगरication to the sockets layer.  */
			pr_debug("%s: sm_sideff: event_up:%p, ulpq:%p\n",
				 __func__, cmd->obj.ulpevent, &asoc->ulpq);

			asoc->stream.si->enqueue_event(&asoc->ulpq,
						       cmd->obj.ulpevent);
			अवरोध;

		हाल SCTP_CMD_REPLY:
			/* If an caller has not alपढ़ोy corked, करो cork. */
			अगर (!asoc->outqueue.cork) अणु
				sctp_outq_cork(&asoc->outqueue);
				local_cork = 1;
			पूर्ण
			/* Send a chunk to our peer.  */
			sctp_outq_tail(&asoc->outqueue, cmd->obj.chunk, gfp);
			अवरोध;

		हाल SCTP_CMD_SEND_PKT:
			/* Send a full packet to our peer.  */
			packet = cmd->obj.packet;
			sctp_packet_transmit(packet, gfp);
			sctp_ootb_pkt_मुक्त(packet);
			अवरोध;

		हाल SCTP_CMD_T1_RETRAN:
			/* Mark a transport क्रम retransmission.  */
			sctp_retransmit(&asoc->outqueue, cmd->obj.transport,
					SCTP_RTXR_T1_RTX);
			अवरोध;

		हाल SCTP_CMD_RETRAN:
			/* Mark a transport क्रम retransmission.  */
			sctp_retransmit(&asoc->outqueue, cmd->obj.transport,
					SCTP_RTXR_T3_RTX);
			अवरोध;

		हाल SCTP_CMD_ECN_CE:
			/* Do delayed CE processing.   */
			sctp_करो_ecn_ce_work(asoc, cmd->obj.u32);
			अवरोध;

		हाल SCTP_CMD_ECN_ECNE:
			/* Do delayed ECNE processing. */
			new_obj = sctp_करो_ecn_ecne_work(asoc, cmd->obj.u32,
							chunk);
			अगर (new_obj)
				sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
						SCTP_CHUNK(new_obj));
			अवरोध;

		हाल SCTP_CMD_ECN_CWR:
			/* Do delayed CWR processing.  */
			sctp_करो_ecn_cwr_work(asoc, cmd->obj.u32);
			अवरोध;

		हाल SCTP_CMD_SETUP_T2:
			sctp_cmd_setup_t2(commands, asoc, cmd->obj.chunk);
			अवरोध;

		हाल SCTP_CMD_TIMER_START_ONCE:
			समयr = &asoc->समयrs[cmd->obj.to];

			अगर (समयr_pending(समयr))
				अवरोध;
			fallthrough;

		हाल SCTP_CMD_TIMER_START:
			समयr = &asoc->समयrs[cmd->obj.to];
			समयout = asoc->समयouts[cmd->obj.to];
			BUG_ON(!समयout);

			/*
			 * SCTP has a hard समय with समयr starts.  Because we process
			 * समयr starts as side effects, it can be hard to tell अगर we
			 * have alपढ़ोy started a समयr or not, which leads to BUG
			 * halts when we call add_समयr. So here, instead of just starting
			 * a समयr, अगर the समयr is alपढ़ोy started, and just mod
			 * the समयr with the लघुer of the two expiration बार
			 */
			अगर (!समयr_pending(समयr))
				sctp_association_hold(asoc);
			समयr_reduce(समयr, jअगरfies + समयout);
			अवरोध;

		हाल SCTP_CMD_TIMER_RESTART:
			समयr = &asoc->समयrs[cmd->obj.to];
			समयout = asoc->समयouts[cmd->obj.to];
			अगर (!mod_समयr(समयr, jअगरfies + समयout))
				sctp_association_hold(asoc);
			अवरोध;

		हाल SCTP_CMD_TIMER_STOP:
			समयr = &asoc->समयrs[cmd->obj.to];
			अगर (del_समयr(समयr))
				sctp_association_put(asoc);
			अवरोध;

		हाल SCTP_CMD_INIT_CHOOSE_TRANSPORT:
			chunk = cmd->obj.chunk;
			t = sctp_assoc_choose_alter_transport(asoc,
						asoc->init_last_sent_to);
			asoc->init_last_sent_to = t;
			chunk->transport = t;
			t->init_sent_count++;
			/* Set the new transport as primary */
			sctp_assoc_set_primary(asoc, t);
			अवरोध;

		हाल SCTP_CMD_INIT_RESTART:
			/* Do the needed accounting and updates
			 * associated with restarting an initialization
			 * समयr. Only multiply the समयout by two अगर
			 * all transports have been tried at the current
			 * समयout.
			 */
			sctp_cmd_t1_समयr_update(asoc,
						SCTP_EVENT_TIMEOUT_T1_INIT,
						"INIT");

			sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
					SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
			अवरोध;

		हाल SCTP_CMD_COOKIEECHO_RESTART:
			/* Do the needed accounting and updates
			 * associated with restarting an initialization
			 * समयr. Only multiply the समयout by two अगर
			 * all transports have been tried at the current
			 * समयout.
			 */
			sctp_cmd_t1_समयr_update(asoc,
						SCTP_EVENT_TIMEOUT_T1_COOKIE,
						"COOKIE");

			/* If we've sent any data bundled with
			 * COOKIE-ECHO we need to resend.
			 */
			list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
					transports) अणु
				sctp_retransmit_mark(&asoc->outqueue, t,
					    SCTP_RTXR_T1_RTX);
			पूर्ण

			sctp_add_cmd_sf(commands,
					SCTP_CMD_TIMER_RESTART,
					SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
			अवरोध;

		हाल SCTP_CMD_INIT_FAILED:
			sctp_cmd_init_failed(commands, asoc, cmd->obj.u16);
			अवरोध;

		हाल SCTP_CMD_ASSOC_FAILED:
			sctp_cmd_assoc_failed(commands, asoc, event_type,
					      subtype, chunk, cmd->obj.u16);
			अवरोध;

		हाल SCTP_CMD_INIT_COUNTER_INC:
			asoc->init_err_counter++;
			अवरोध;

		हाल SCTP_CMD_INIT_COUNTER_RESET:
			asoc->init_err_counter = 0;
			asoc->init_cycle = 0;
			list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
					    transports) अणु
				t->init_sent_count = 0;
			पूर्ण
			अवरोध;

		हाल SCTP_CMD_REPORT_DUP:
			sctp_tsnmap_mark_dup(&asoc->peer.tsn_map,
					     cmd->obj.u32);
			अवरोध;

		हाल SCTP_CMD_REPORT_BAD_TAG:
			pr_debug("%s: vtag mismatch!\n", __func__);
			अवरोध;

		हाल SCTP_CMD_STRIKE:
			/* Mark one strike against a transport.  */
			sctp_करो_8_2_transport_strike(commands, asoc,
						    cmd->obj.transport, 0);
			अवरोध;

		हाल SCTP_CMD_TRANSPORT_IDLE:
			t = cmd->obj.transport;
			sctp_transport_lower_cwnd(t, SCTP_LOWER_CWND_INACTIVE);
			अवरोध;

		हाल SCTP_CMD_TRANSPORT_HB_SENT:
			t = cmd->obj.transport;
			sctp_करो_8_2_transport_strike(commands, asoc,
						     t, 1);
			t->hb_sent = 1;
			अवरोध;

		हाल SCTP_CMD_TRANSPORT_ON:
			t = cmd->obj.transport;
			sctp_cmd_transport_on(commands, asoc, t, chunk);
			अवरोध;

		हाल SCTP_CMD_HB_TIMERS_START:
			sctp_cmd_hb_समयrs_start(commands, asoc);
			अवरोध;

		हाल SCTP_CMD_HB_TIMER_UPDATE:
			t = cmd->obj.transport;
			sctp_transport_reset_hb_समयr(t);
			अवरोध;

		हाल SCTP_CMD_HB_TIMERS_STOP:
			sctp_cmd_hb_समयrs_stop(commands, asoc);
			अवरोध;

		हाल SCTP_CMD_REPORT_ERROR:
			error = cmd->obj.error;
			अवरोध;

		हाल SCTP_CMD_PROCESS_CTSN:
			/* Dummy up a SACK क्रम processing. */
			sackh.cum_tsn_ack = cmd->obj.be32;
			sackh.a_rwnd = htonl(asoc->peer.rwnd +
					     asoc->outqueue.outstanding_bytes);
			sackh.num_gap_ack_blocks = 0;
			sackh.num_dup_tsns = 0;
			chunk->subh.sack_hdr = &sackh;
			sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_SACK,
					SCTP_CHUNK(chunk));
			अवरोध;

		हाल SCTP_CMD_DISCARD_PACKET:
			/* We need to discard the whole packet.
			 * Uncork the queue since there might be
			 * responses pending
			 */
			chunk->pdiscard = 1;
			अगर (asoc) अणु
				sctp_outq_uncork(&asoc->outqueue, gfp);
				local_cork = 0;
			पूर्ण
			अवरोध;

		हाल SCTP_CMD_RTO_PENDING:
			t = cmd->obj.transport;
			t->rto_pending = 1;
			अवरोध;

		हाल SCTP_CMD_PART_DELIVER:
			asoc->stream.si->start_pd(&asoc->ulpq, GFP_ATOMIC);
			अवरोध;

		हाल SCTP_CMD_RENEGE:
			asoc->stream.si->renege_events(&asoc->ulpq,
						       cmd->obj.chunk,
						       GFP_ATOMIC);
			अवरोध;

		हाल SCTP_CMD_SETUP_T4:
			sctp_cmd_setup_t4(commands, asoc, cmd->obj.chunk);
			अवरोध;

		हाल SCTP_CMD_PROCESS_OPERR:
			sctp_cmd_process_operr(commands, asoc, chunk);
			अवरोध;
		हाल SCTP_CMD_CLEAR_INIT_TAG:
			asoc->peer.i.init_tag = 0;
			अवरोध;
		हाल SCTP_CMD_DEL_NON_PRIMARY:
			sctp_cmd_del_non_primary(asoc);
			अवरोध;
		हाल SCTP_CMD_T3_RTX_TIMERS_STOP:
			sctp_cmd_t3_rtx_समयrs_stop(commands, asoc);
			अवरोध;
		हाल SCTP_CMD_FORCE_PRIM_RETRAN:
			t = asoc->peer.retran_path;
			asoc->peer.retran_path = asoc->peer.primary_path;
			sctp_outq_uncork(&asoc->outqueue, gfp);
			local_cork = 0;
			asoc->peer.retran_path = t;
			अवरोध;
		हाल SCTP_CMD_SET_SK_ERR:
			sctp_cmd_set_sk_err(asoc, cmd->obj.error);
			अवरोध;
		हाल SCTP_CMD_ASSOC_CHANGE:
			sctp_cmd_assoc_change(commands, asoc,
					      cmd->obj.u8);
			अवरोध;
		हाल SCTP_CMD_ADAPTATION_IND:
			sctp_cmd_adaptation_ind(commands, asoc);
			अवरोध;
		हाल SCTP_CMD_PEER_NO_AUTH:
			sctp_cmd_peer_no_auth(commands, asoc);
			अवरोध;

		हाल SCTP_CMD_ASSOC_SHKEY:
			error = sctp_auth_asoc_init_active_key(asoc,
						GFP_ATOMIC);
			अवरोध;
		हाल SCTP_CMD_UPDATE_INITTAG:
			asoc->peer.i.init_tag = cmd->obj.u32;
			अवरोध;
		हाल SCTP_CMD_SEND_MSG:
			अगर (!asoc->outqueue.cork) अणु
				sctp_outq_cork(&asoc->outqueue);
				local_cork = 1;
			पूर्ण
			sctp_cmd_send_msg(asoc, cmd->obj.msg, gfp);
			अवरोध;
		हाल SCTP_CMD_PURGE_ASCONF_QUEUE:
			sctp_asconf_queue_tearकरोwn(asoc);
			अवरोध;

		हाल SCTP_CMD_SET_ASOC:
			अगर (asoc && local_cork) अणु
				sctp_outq_uncork(&asoc->outqueue, gfp);
				local_cork = 0;
			पूर्ण
			asoc = cmd->obj.asoc;
			अवरोध;

		शेष:
			pr_warn("Impossible command: %u\n",
				cmd->verb);
			अवरोध;
		पूर्ण

		अगर (error) अणु
			cmd = sctp_next_cmd(commands);
			जबतक (cmd) अणु
				अगर (cmd->verb == SCTP_CMD_REPLY)
					sctp_chunk_मुक्त(cmd->obj.chunk);
				cmd = sctp_next_cmd(commands);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* If this is in response to a received chunk, रुको until
	 * we are करोne with the packet to खोलो the queue so that we करोn't
	 * send multiple packets in response to a single request.
	 */
	अगर (asoc && SCTP_EVENT_T_CHUNK == event_type && chunk) अणु
		अगर (chunk->end_of_packet || chunk->singleton)
			sctp_outq_uncork(&asoc->outqueue, gfp);
	पूर्ण अन्यथा अगर (local_cork)
		sctp_outq_uncork(&asoc->outqueue, gfp);

	अगर (sp->data_पढ़ोy_संकेतled)
		sp->data_पढ़ोy_संकेतled = 0;

	वापस error;
पूर्ण
