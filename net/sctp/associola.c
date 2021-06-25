<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * This module provides the असलtraction क्रम an SCTP association.
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
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Ryan Layer	    <rmlayer@us.ibm.com>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>

#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <net/ipv6.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* Forward declarations क्रम पूर्णांकernal functions. */
अटल व्योम sctp_select_active_and_retran_path(काष्ठा sctp_association *asoc);
अटल व्योम sctp_assoc_bh_rcv(काष्ठा work_काष्ठा *work);
अटल व्योम sctp_assoc_मुक्त_asconf_acks(काष्ठा sctp_association *asoc);
अटल व्योम sctp_assoc_मुक्त_asconf_queue(काष्ठा sctp_association *asoc);

/* 1st Level Abstractions. */

/* Initialize a new association from provided memory. */
अटल काष्ठा sctp_association *sctp_association_init(
					काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sock *sk,
					क्रमागत sctp_scope scope, gfp_t gfp)
अणु
	काष्ठा sctp_sock *sp;
	काष्ठा sctp_paramhdr *p;
	पूर्णांक i;

	/* Retrieve the SCTP per socket area.  */
	sp = sctp_sk((काष्ठा sock *)sk);

	/* Discarding स्थिर is appropriate here.  */
	asoc->ep = (काष्ठा sctp_endpoपूर्णांक *)ep;
	asoc->base.sk = (काष्ठा sock *)sk;
	asoc->base.net = sock_net(sk);

	sctp_endpoपूर्णांक_hold(asoc->ep);
	sock_hold(asoc->base.sk);

	/* Initialize the common base subकाष्ठाure.  */
	asoc->base.type = SCTP_EP_TYPE_ASSOCIATION;

	/* Initialize the object handling fields.  */
	refcount_set(&asoc->base.refcnt, 1);

	/* Initialize the bind addr area.  */
	sctp_bind_addr_init(&asoc->base.bind_addr, ep->base.bind_addr.port);

	asoc->state = SCTP_STATE_CLOSED;
	asoc->cookie_lअगरe = ms_to_kसमय(sp->assocparams.sasoc_cookie_lअगरe);
	asoc->user_frag = sp->user_frag;

	/* Set the association max_retrans and RTO values from the
	 * socket values.
	 */
	asoc->max_retrans = sp->assocparams.sasoc_asocmaxrxt;
	asoc->pf_retrans  = sp->pf_retrans;
	asoc->ps_retrans  = sp->ps_retrans;
	asoc->pf_expose   = sp->pf_expose;

	asoc->rto_initial = msecs_to_jअगरfies(sp->rtoinfo.srto_initial);
	asoc->rto_max = msecs_to_jअगरfies(sp->rtoinfo.srto_max);
	asoc->rto_min = msecs_to_jअगरfies(sp->rtoinfo.srto_min);

	/* Initialize the association's heartbeat पूर्णांकerval based on the
	 * sock configured value.
	 */
	asoc->hbपूर्णांकerval = msecs_to_jअगरfies(sp->hbपूर्णांकerval);

	asoc->encap_port = sp->encap_port;

	/* Initialize path max retrans value. */
	asoc->pathmaxrxt = sp->pathmaxrxt;

	asoc->flowlabel = sp->flowlabel;
	asoc->dscp = sp->dscp;

	/* Set association शेष SACK delay */
	asoc->sackdelay = msecs_to_jअगरfies(sp->sackdelay);
	asoc->sackfreq = sp->sackfreq;

	/* Set the association शेष flags controlling
	 * Heartbeat, SACK delay, and Path MTU Discovery.
	 */
	asoc->param_flags = sp->param_flags;

	/* Initialize the maximum number of new data packets that can be sent
	 * in a burst.
	 */
	asoc->max_burst = sp->max_burst;

	asoc->subscribe = sp->subscribe;

	/* initialize association समयrs */
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T1_COOKIE] = asoc->rto_initial;
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T1_INIT] = asoc->rto_initial;
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = asoc->rto_initial;

	/* sctpimpguide Section 2.12.2
	 * If the 'T5-shutdown-guard' समयr is used, it SHOULD be set to the
	 * recommended value of 5 बार 'RTO.Max'.
	 */
	asoc->समयouts[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD]
		= 5 * asoc->rto_max;

	asoc->समयouts[SCTP_EVENT_TIMEOUT_SACK] = asoc->sackdelay;
	asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE] = sp->स्वतःबंद * HZ;

	/* Initializes the समयrs */
	क्रम (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i)
		समयr_setup(&asoc->समयrs[i], sctp_समयr_events[i], 0);

	/* Pull शेष initialization values from the sock options.
	 * Note: This assumes that the values have alपढ़ोy been
	 * validated in the sock.
	 */
	asoc->c.sinit_max_instreams = sp->iniपंचांगsg.sinit_max_instreams;
	asoc->c.sinit_num_ostreams  = sp->iniपंचांगsg.sinit_num_ostreams;
	asoc->max_init_attempts	= sp->iniपंचांगsg.sinit_max_attempts;

	asoc->max_init_समयo =
		 msecs_to_jअगरfies(sp->iniपंचांगsg.sinit_max_init_समयo);

	/* Set the local winकरोw size क्रम receive.
	 * This is also the rcvbuf space per association.
	 * RFC 6 - A SCTP receiver MUST be able to receive a minimum of
	 * 1500 bytes in one SCTP packet.
	 */
	अगर ((sk->sk_rcvbuf/2) < SCTP_DEFAULT_MINWINDOW)
		asoc->rwnd = SCTP_DEFAULT_MINWINDOW;
	अन्यथा
		asoc->rwnd = sk->sk_rcvbuf/2;

	asoc->a_rwnd = asoc->rwnd;

	/* Use my own max winकरोw until I learn something better.  */
	asoc->peer.rwnd = SCTP_DEFAULT_MAXWINDOW;

	/* Initialize the receive memory counter */
	atomic_set(&asoc->rmem_alloc, 0);

	init_रुकोqueue_head(&asoc->रुको);

	asoc->c.my_vtag = sctp_generate_tag(ep);
	asoc->c.my_port = ep->base.bind_addr.port;

	asoc->c.initial_tsn = sctp_generate_tsn(ep);

	asoc->next_tsn = asoc->c.initial_tsn;

	asoc->ctsn_ack_poपूर्णांक = asoc->next_tsn - 1;
	asoc->adv_peer_ack_poपूर्णांक = asoc->ctsn_ack_poपूर्णांक;
	asoc->highest_sacked = asoc->ctsn_ack_poपूर्णांक;
	asoc->last_cwr_tsn = asoc->ctsn_ack_poपूर्णांक;

	/* ADDIP Section 4.1 Asconf Chunk Procedures
	 *
	 * When an endpoपूर्णांक has an ASCONF संकेतed change to be sent to the
	 * remote endpoपूर्णांक it should करो the following:
	 * ...
	 * A2) a serial number should be asचिन्हित to the chunk. The serial
	 * number SHOULD be a monotonically increasing number. The serial
	 * numbers SHOULD be initialized at the start of the
	 * association to the same value as the initial TSN.
	 */
	asoc->addip_serial = asoc->c.initial_tsn;
	asoc->strreset_outseq = asoc->c.initial_tsn;

	INIT_LIST_HEAD(&asoc->addip_chunk_list);
	INIT_LIST_HEAD(&asoc->asconf_ack_list);

	/* Make an empty list of remote transport addresses.  */
	INIT_LIST_HEAD(&asoc->peer.transport_addr_list);

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * After the reception of the first data chunk in an
	 * association the endpoपूर्णांक must immediately respond with a
	 * sack to acknowledge the data chunk.  Subsequent
	 * acknowledgements should be करोne as described in Section
	 * 6.2.
	 *
	 * [We implement this by telling a new association that it
	 * alपढ़ोy received one packet.]
	 */
	asoc->peer.sack_needed = 1;
	asoc->peer.sack_generation = 1;

	/* Create an input queue.  */
	sctp_inq_init(&asoc->base.inqueue);
	sctp_inq_set_th_handler(&asoc->base.inqueue, sctp_assoc_bh_rcv);

	/* Create an output queue.  */
	sctp_outq_init(asoc, &asoc->outqueue);

	अगर (!sctp_ulpq_init(&asoc->ulpq, asoc))
		जाओ fail_init;

	अगर (sctp_stream_init(&asoc->stream, asoc->c.sinit_num_ostreams,
			     0, gfp))
		जाओ fail_init;

	/* Initialize शेष path MTU. */
	asoc->pathmtu = sp->pathmtu;
	sctp_assoc_update_frag_poपूर्णांक(asoc);

	/* Assume that peer would support both address types unless we are
	 * told otherwise.
	 */
	asoc->peer.ipv4_address = 1;
	अगर (asoc->base.sk->sk_family == PF_INET6)
		asoc->peer.ipv6_address = 1;
	INIT_LIST_HEAD(&asoc->asocs);

	asoc->शेष_stream = sp->शेष_stream;
	asoc->शेष_ppid = sp->शेष_ppid;
	asoc->शेष_flags = sp->शेष_flags;
	asoc->शेष_context = sp->शेष_context;
	asoc->शेष_समयtolive = sp->शेष_समयtolive;
	asoc->शेष_rcv_context = sp->शेष_rcv_context;

	/* AUTH related initializations */
	INIT_LIST_HEAD(&asoc->endpoपूर्णांक_shared_keys);
	अगर (sctp_auth_asoc_copy_shkeys(ep, asoc, gfp))
		जाओ stream_मुक्त;

	asoc->active_key_id = ep->active_key_id;
	asoc->strreset_enable = ep->strreset_enable;

	/* Save the hmacs and chunks list पूर्णांकo this association */
	अगर (ep->auth_hmacs_list)
		स_नकल(asoc->c.auth_hmacs, ep->auth_hmacs_list,
			ntohs(ep->auth_hmacs_list->param_hdr.length));
	अगर (ep->auth_chunk_list)
		स_नकल(asoc->c.auth_chunks, ep->auth_chunk_list,
			ntohs(ep->auth_chunk_list->param_hdr.length));

	/* Get the AUTH अक्रमom number क्रम this association */
	p = (काष्ठा sctp_paramhdr *)asoc->c.auth_अक्रमom;
	p->type = SCTP_PARAM_RANDOM;
	p->length = htons(माप(*p) + SCTP_AUTH_RANDOM_LENGTH);
	get_अक्रमom_bytes(p+1, SCTP_AUTH_RANDOM_LENGTH);

	वापस asoc;

stream_मुक्त:
	sctp_stream_मुक्त(&asoc->stream);
fail_init:
	sock_put(asoc->base.sk);
	sctp_endpoपूर्णांक_put(asoc->ep);
	वापस शून्य;
पूर्ण

/* Allocate and initialize a new association */
काष्ठा sctp_association *sctp_association_new(स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					      स्थिर काष्ठा sock *sk,
					      क्रमागत sctp_scope scope, gfp_t gfp)
अणु
	काष्ठा sctp_association *asoc;

	asoc = kzalloc(माप(*asoc), gfp);
	अगर (!asoc)
		जाओ fail;

	अगर (!sctp_association_init(asoc, ep, sk, scope, gfp))
		जाओ fail_init;

	SCTP_DBG_OBJCNT_INC(assoc);

	pr_debug("Created asoc %p\n", asoc);

	वापस asoc;

fail_init:
	kमुक्त(asoc);
fail:
	वापस शून्य;
पूर्ण

/* Free this association अगर possible.  There may still be users, so
 * the actual deallocation may be delayed.
 */
व्योम sctp_association_मुक्त(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा sctp_transport *transport;
	काष्ठा list_head *pos, *temp;
	पूर्णांक i;

	/* Only real associations count against the endpoपूर्णांक, so
	 * करोn't bother क्रम अगर this is a temporary association.
	 */
	अगर (!list_empty(&asoc->asocs)) अणु
		list_del(&asoc->asocs);

		/* Decrement the backlog value क्रम a TCP-style listening
		 * socket.
		 */
		अगर (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
			sk_acceptq_हटाओd(sk);
	पूर्ण

	/* Mark as dead, so other users can know this काष्ठाure is
	 * going away.
	 */
	asoc->base.dead = true;

	/* Dispose of any data lying around in the outqueue. */
	sctp_outq_मुक्त(&asoc->outqueue);

	/* Dispose of any pending messages क्रम the upper layer. */
	sctp_ulpq_मुक्त(&asoc->ulpq);

	/* Dispose of any pending chunks on the inqueue. */
	sctp_inq_मुक्त(&asoc->base.inqueue);

	sctp_tsnmap_मुक्त(&asoc->peer.tsn_map);

	/* Free stream inक्रमmation. */
	sctp_stream_मुक्त(&asoc->stream);

	अगर (asoc->strreset_chunk)
		sctp_chunk_मुक्त(asoc->strreset_chunk);

	/* Clean up the bound address list. */
	sctp_bind_addr_मुक्त(&asoc->base.bind_addr);

	/* Do we need to go through all of our समयrs and
	 * delete them?   To be safe we will try to delete all, but we
	 * should be able to go through and make a guess based
	 * on our state.
	 */
	क्रम (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i) अणु
		अगर (del_समयr(&asoc->समयrs[i]))
			sctp_association_put(asoc);
	पूर्ण

	/* Free peer's cached cookie. */
	kमुक्त(asoc->peer.cookie);
	kमुक्त(asoc->peer.peer_अक्रमom);
	kमुक्त(asoc->peer.peer_chunks);
	kमुक्त(asoc->peer.peer_hmacs);

	/* Release the transport काष्ठाures. */
	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		transport = list_entry(pos, काष्ठा sctp_transport, transports);
		list_del_rcu(pos);
		sctp_unhash_transport(transport);
		sctp_transport_मुक्त(transport);
	पूर्ण

	asoc->peer.transport_count = 0;

	sctp_asconf_queue_tearकरोwn(asoc);

	/* Free pending address space being deleted */
	kमुक्त(asoc->asconf_addr_del_pending);

	/* AUTH - Free the endpoपूर्णांक shared keys */
	sctp_auth_destroy_keys(&asoc->endpoपूर्णांक_shared_keys);

	/* AUTH - Free the association shared key */
	sctp_auth_key_put(asoc->asoc_shared_key);

	sctp_association_put(asoc);
पूर्ण

/* Cleanup and मुक्त up an association. */
अटल व्योम sctp_association_destroy(काष्ठा sctp_association *asoc)
अणु
	अगर (unlikely(!asoc->base.dead)) अणु
		WARN(1, "Attempt to destroy undead association %p!\n", asoc);
		वापस;
	पूर्ण

	sctp_endpoपूर्णांक_put(asoc->ep);
	sock_put(asoc->base.sk);

	अगर (asoc->assoc_id != 0) अणु
		spin_lock_bh(&sctp_assocs_id_lock);
		idr_हटाओ(&sctp_assocs_id, asoc->assoc_id);
		spin_unlock_bh(&sctp_assocs_id_lock);
	पूर्ण

	WARN_ON(atomic_पढ़ो(&asoc->rmem_alloc));

	kमुक्त_rcu(asoc, rcu);
	SCTP_DBG_OBJCNT_DEC(assoc);
पूर्ण

/* Change the primary destination address क्रम the peer. */
व्योम sctp_assoc_set_primary(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_transport *transport)
अणु
	पूर्णांक changeover = 0;

	/* it's a changeover only अगर we alपढ़ोy have a primary path
	 * that we are changing
	 */
	अगर (asoc->peer.primary_path != शून्य &&
	    asoc->peer.primary_path != transport)
		changeover = 1 ;

	asoc->peer.primary_path = transport;
	sctp_ulpevent_notअगरy_peer_addr_change(transport,
					      SCTP_ADDR_MADE_PRIM, 0);

	/* Set a शेष msg_name क्रम events. */
	स_नकल(&asoc->peer.primary_addr, &transport->ipaddr,
	       माप(जोड़ sctp_addr));

	/* If the primary path is changing, assume that the
	 * user wants to use this new path.
	 */
	अगर ((transport->state == SCTP_ACTIVE) ||
	    (transport->state == SCTP_UNKNOWN))
		asoc->peer.active_path = transport;

	/*
	 * SFR-CACC algorithm:
	 * Upon the receipt of a request to change the primary
	 * destination address, on the data काष्ठाure क्रम the new
	 * primary destination, the sender MUST करो the following:
	 *
	 * 1) If CHANGEOVER_ACTIVE is set, then there was a चयन
	 * to this destination address earlier. The sender MUST set
	 * CYCLING_CHANGEOVER to indicate that this चयन is a
	 * द्विगुन चयन to the same destination address.
	 *
	 * Really, only bother is we have data queued or outstanding on
	 * the association.
	 */
	अगर (!asoc->outqueue.outstanding_bytes && !asoc->outqueue.out_qlen)
		वापस;

	अगर (transport->cacc.changeover_active)
		transport->cacc.cycling_changeover = changeover;

	/* 2) The sender MUST set CHANGEOVER_ACTIVE to indicate that
	 * a changeover has occurred.
	 */
	transport->cacc.changeover_active = changeover;

	/* 3) The sender MUST store the next TSN to be sent in
	 * next_tsn_at_change.
	 */
	transport->cacc.next_tsn_at_change = asoc->next_tsn;
पूर्ण

/* Remove a transport from an association.  */
व्योम sctp_assoc_rm_peer(काष्ठा sctp_association *asoc,
			काष्ठा sctp_transport *peer)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा list_head *pos;
	काष्ठा sctp_chunk *ch;

	pr_debug("%s: association:%p addr:%pISpc\n",
		 __func__, asoc, &peer->ipaddr.sa);

	/* If we are to हटाओ the current retran_path, update it
	 * to the next peer beक्रमe removing this peer from the list.
	 */
	अगर (asoc->peer.retran_path == peer)
		sctp_assoc_update_retran_path(asoc);

	/* Remove this peer from the list. */
	list_del_rcu(&peer->transports);
	/* Remove this peer from the transport hashtable */
	sctp_unhash_transport(peer);

	/* Get the first transport of asoc. */
	pos = asoc->peer.transport_addr_list.next;
	transport = list_entry(pos, काष्ठा sctp_transport, transports);

	/* Update any entries that match the peer to be deleted. */
	अगर (asoc->peer.primary_path == peer)
		sctp_assoc_set_primary(asoc, transport);
	अगर (asoc->peer.active_path == peer)
		asoc->peer.active_path = transport;
	अगर (asoc->peer.retran_path == peer)
		asoc->peer.retran_path = transport;
	अगर (asoc->peer.last_data_from == peer)
		asoc->peer.last_data_from = transport;

	अगर (asoc->strreset_chunk &&
	    asoc->strreset_chunk->transport == peer) अणु
		asoc->strreset_chunk->transport = transport;
		sctp_transport_reset_reconf_समयr(transport);
	पूर्ण

	/* If we हटाओ the transport an INIT was last sent to, set it to
	 * शून्य. Combined with the update of the retran path above, this
	 * will cause the next INIT to be sent to the next available
	 * transport, मुख्यtaining the cycle.
	 */
	अगर (asoc->init_last_sent_to == peer)
		asoc->init_last_sent_to = शून्य;

	/* If we हटाओ the transport an SHUTDOWN was last sent to, set it
	 * to शून्य. Combined with the update of the retran path above, this
	 * will cause the next SHUTDOWN to be sent to the next available
	 * transport, मुख्यtaining the cycle.
	 */
	अगर (asoc->shutकरोwn_last_sent_to == peer)
		asoc->shutकरोwn_last_sent_to = शून्य;

	/* If we हटाओ the transport an ASCONF was last sent to, set it to
	 * शून्य.
	 */
	अगर (asoc->addip_last_asconf &&
	    asoc->addip_last_asconf->transport == peer)
		asoc->addip_last_asconf->transport = शून्य;

	/* If we have something on the transmitted list, we have to
	 * save it off.  The best place is the active path.
	 */
	अगर (!list_empty(&peer->transmitted)) अणु
		काष्ठा sctp_transport *active = asoc->peer.active_path;

		/* Reset the transport of each chunk on this list */
		list_क्रम_each_entry(ch, &peer->transmitted,
					transmitted_list) अणु
			ch->transport = शून्य;
			ch->rtt_in_progress = 0;
		पूर्ण

		list_splice_tail_init(&peer->transmitted,
					&active->transmitted);

		/* Start a T3 समयr here in हाल it wasn't running so
		 * that these migrated packets have a chance to get
		 * retransmitted.
		 */
		अगर (!समयr_pending(&active->T3_rtx_समयr))
			अगर (!mod_समयr(&active->T3_rtx_समयr,
					jअगरfies + active->rto))
				sctp_transport_hold(active);
	पूर्ण

	list_क्रम_each_entry(ch, &asoc->outqueue.out_chunk_list, list)
		अगर (ch->transport == peer)
			ch->transport = शून्य;

	asoc->peer.transport_count--;

	sctp_ulpevent_notअगरy_peer_addr_change(peer, SCTP_ADDR_REMOVED, 0);
	sctp_transport_मुक्त(peer);
पूर्ण

/* Add a transport address to an association.  */
काष्ठा sctp_transport *sctp_assoc_add_peer(काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_addr *addr,
					   स्थिर gfp_t gfp,
					   स्थिर पूर्णांक peer_state)
अणु
	काष्ठा sctp_transport *peer;
	काष्ठा sctp_sock *sp;
	अचिन्हित लघु port;

	sp = sctp_sk(asoc->base.sk);

	/* AF_INET and AF_INET6 share common port field. */
	port = ntohs(addr->v4.sin_port);

	pr_debug("%s: association:%p addr:%pISpc state:%d\n", __func__,
		 asoc, &addr->sa, peer_state);

	/* Set the port अगर it has not been set yet.  */
	अगर (0 == asoc->peer.port)
		asoc->peer.port = port;

	/* Check to see अगर this is a duplicate. */
	peer = sctp_assoc_lookup_paddr(asoc, addr);
	अगर (peer) अणु
		/* An UNKNOWN state is only set on transports added by
		 * user in sctp_connectx() call.  Such transports should be
		 * considered CONFIRMED per RFC 4960, Section 5.4.
		 */
		अगर (peer->state == SCTP_UNKNOWN) अणु
			peer->state = SCTP_ACTIVE;
		पूर्ण
		वापस peer;
	पूर्ण

	peer = sctp_transport_new(asoc->base.net, addr, gfp);
	अगर (!peer)
		वापस शून्य;

	sctp_transport_set_owner(peer, asoc);

	/* Initialize the peer's heartbeat पूर्णांकerval based on the
	 * association configured value.
	 */
	peer->hbपूर्णांकerval = asoc->hbपूर्णांकerval;

	peer->encap_port = asoc->encap_port;

	/* Set the path max_retrans.  */
	peer->pathmaxrxt = asoc->pathmaxrxt;

	/* And the partial failure retrans threshold */
	peer->pf_retrans = asoc->pf_retrans;
	/* And the primary path चयनover retrans threshold */
	peer->ps_retrans = asoc->ps_retrans;

	/* Initialize the peer's SACK delay समयout based on the
	 * association configured value.
	 */
	peer->sackdelay = asoc->sackdelay;
	peer->sackfreq = asoc->sackfreq;

	अगर (addr->sa.sa_family == AF_INET6) अणु
		__be32 info = addr->v6.sin6_flowinfo;

		अगर (info) अणु
			peer->flowlabel = ntohl(info & IPV6_FLOWLABEL_MASK);
			peer->flowlabel |= SCTP_FLOWLABEL_SET_MASK;
		पूर्ण अन्यथा अणु
			peer->flowlabel = asoc->flowlabel;
		पूर्ण
	पूर्ण
	peer->dscp = asoc->dscp;

	/* Enable/disable heartbeat, SACK delay, and path MTU discovery
	 * based on association setting.
	 */
	peer->param_flags = asoc->param_flags;

	/* Initialize the pmtu of the transport. */
	sctp_transport_route(peer, शून्य, sp);

	/* If this is the first transport addr on this association,
	 * initialize the association PMTU to the peer's PMTU.
	 * If not and the current association PMTU is higher than the new
	 * peer's PMTU, reset the association PMTU to the new peer's PMTU.
	 */
	sctp_assoc_set_pmtu(asoc, asoc->pathmtu ?
				  min_t(पूर्णांक, peer->pathmtu, asoc->pathmtu) :
				  peer->pathmtu);

	peer->pmtu_pending = 0;

	/* The asoc->peer.port might not be meaningful yet, but
	 * initialize the packet काष्ठाure anyway.
	 */
	sctp_packet_init(&peer->packet, peer, asoc->base.bind_addr.port,
			 asoc->peer.port);

	/* 7.2.1 Slow-Start
	 *
	 * o The initial cwnd beक्रमe DATA transmission or after a sufficiently
	 *   दीर्घ idle period MUST be set to
	 *      min(4*MTU, max(2*MTU, 4380 bytes))
	 *
	 * o The initial value of ssthresh MAY be arbitrarily high
	 *   (क्रम example, implementations MAY use the size of the
	 *   receiver advertised winकरोw).
	 */
	peer->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));

	/* At this poपूर्णांक, we may not have the receiver's advertised winकरोw,
	 * so initialize ssthresh to the शेष value and it will be set
	 * later when we process the INIT.
	 */
	peer->ssthresh = SCTP_DEFAULT_MAXWINDOW;

	peer->partial_bytes_acked = 0;
	peer->flight_size = 0;
	peer->burst_limited = 0;

	/* Set the transport's RTO.initial value */
	peer->rto = asoc->rto_initial;
	sctp_max_rto(asoc, peer);

	/* Set the peer's active state. */
	peer->state = peer_state;

	/* Add this peer पूर्णांकo the transport hashtable */
	अगर (sctp_hash_transport(peer)) अणु
		sctp_transport_मुक्त(peer);
		वापस शून्य;
	पूर्ण

	/* Attach the remote transport to our asoc.  */
	list_add_tail_rcu(&peer->transports, &asoc->peer.transport_addr_list);
	asoc->peer.transport_count++;

	sctp_ulpevent_notअगरy_peer_addr_change(peer, SCTP_ADDR_ADDED, 0);

	/* If we करो not yet have a primary path, set one.  */
	अगर (!asoc->peer.primary_path) अणु
		sctp_assoc_set_primary(asoc, peer);
		asoc->peer.retran_path = peer;
	पूर्ण

	अगर (asoc->peer.active_path == asoc->peer.retran_path &&
	    peer->state != SCTP_UNCONFIRMED) अणु
		asoc->peer.retran_path = peer;
	पूर्ण

	वापस peer;
पूर्ण

/* Delete a transport address from an association.  */
व्योम sctp_assoc_del_peer(काष्ठा sctp_association *asoc,
			 स्थिर जोड़ sctp_addr *addr)
अणु
	काष्ठा list_head	*pos;
	काष्ठा list_head	*temp;
	काष्ठा sctp_transport	*transport;

	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		transport = list_entry(pos, काष्ठा sctp_transport, transports);
		अगर (sctp_cmp_addr_exact(addr, &transport->ipaddr)) अणु
			/* Do book keeping क्रम removing the peer and मुक्त it. */
			sctp_assoc_rm_peer(asoc, transport);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Lookup a transport by address. */
काष्ठा sctp_transport *sctp_assoc_lookup_paddr(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_addr *address)
अणु
	काष्ठा sctp_transport *t;

	/* Cycle through all transports searching क्रम a peer address. */

	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list,
			transports) अणु
		अगर (sctp_cmp_addr_exact(address, &t->ipaddr))
			वापस t;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Remove all transports except a give one */
व्योम sctp_assoc_del_nonprimary_peers(काष्ठा sctp_association *asoc,
				     काष्ठा sctp_transport *primary)
अणु
	काष्ठा sctp_transport	*temp;
	काष्ठा sctp_transport	*t;

	list_क्रम_each_entry_safe(t, temp, &asoc->peer.transport_addr_list,
				 transports) अणु
		/* अगर the current transport is not the primary one, delete it */
		अगर (t != primary)
			sctp_assoc_rm_peer(asoc, t);
	पूर्ण
पूर्ण

/* Engage in transport control operations.
 * Mark the transport up or करोwn and send a notअगरication to the user.
 * Select and update the new active and retran paths.
 */
व्योम sctp_assoc_control_transport(काष्ठा sctp_association *asoc,
				  काष्ठा sctp_transport *transport,
				  क्रमागत sctp_transport_cmd command,
				  sctp_sn_error_t error)
अणु
	पूर्णांक spc_state = SCTP_ADDR_AVAILABLE;
	bool ulp_notअगरy = true;

	/* Record the transition on the transport.  */
	चयन (command) अणु
	हाल SCTP_TRANSPORT_UP:
		/* If we are moving from UNCONFIRMED state due
		 * to heartbeat success, report the SCTP_ADDR_CONFIRMED
		 * state to the user, otherwise report SCTP_ADDR_AVAILABLE.
		 */
		अगर (transport->state == SCTP_PF &&
		    asoc->pf_expose != SCTP_PF_EXPOSE_ENABLE)
			ulp_notअगरy = false;
		अन्यथा अगर (transport->state == SCTP_UNCONFIRMED &&
			 error == SCTP_HEARTBEAT_SUCCESS)
			spc_state = SCTP_ADDR_CONFIRMED;

		transport->state = SCTP_ACTIVE;
		अवरोध;

	हाल SCTP_TRANSPORT_DOWN:
		/* If the transport was never confirmed, करो not transition it
		 * to inactive state.  Also, release the cached route since
		 * there may be a better route next समय.
		 */
		अगर (transport->state != SCTP_UNCONFIRMED) अणु
			transport->state = SCTP_INACTIVE;
			spc_state = SCTP_ADDR_UNREACHABLE;
		पूर्ण अन्यथा अणु
			sctp_transport_dst_release(transport);
			ulp_notअगरy = false;
		पूर्ण
		अवरोध;

	हाल SCTP_TRANSPORT_PF:
		transport->state = SCTP_PF;
		अगर (asoc->pf_expose != SCTP_PF_EXPOSE_ENABLE)
			ulp_notअगरy = false;
		अन्यथा
			spc_state = SCTP_ADDR_POTENTIALLY_FAILED;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	/* Generate and send a SCTP_PEER_ADDR_CHANGE notअगरication
	 * to the user.
	 */
	अगर (ulp_notअगरy)
		sctp_ulpevent_notअगरy_peer_addr_change(transport,
						      spc_state, error);

	/* Select new active and retran paths. */
	sctp_select_active_and_retran_path(asoc);
पूर्ण

/* Hold a reference to an association. */
व्योम sctp_association_hold(काष्ठा sctp_association *asoc)
अणु
	refcount_inc(&asoc->base.refcnt);
पूर्ण

/* Release a reference to an association and cleanup
 * अगर there are no more references.
 */
व्योम sctp_association_put(काष्ठा sctp_association *asoc)
अणु
	अगर (refcount_dec_and_test(&asoc->base.refcnt))
		sctp_association_destroy(asoc);
पूर्ण

/* Allocate the next TSN, Transmission Sequence Number, क्रम the given
 * association.
 */
__u32 sctp_association_get_next_tsn(काष्ठा sctp_association *asoc)
अणु
	/* From Section 1.6 Serial Number Arithmetic:
	 * Transmission Sequence Numbers wrap around when they reach
	 * 2**32 - 1.  That is, the next TSN a DATA chunk MUST use
	 * after transmitting TSN = 2*32 - 1 is TSN = 0.
	 */
	__u32 retval = asoc->next_tsn;
	asoc->next_tsn++;
	asoc->unack_data++;

	वापस retval;
पूर्ण

/* Compare two addresses to see अगर they match.  Wildcard addresses
 * only match themselves.
 */
पूर्णांक sctp_cmp_addr_exact(स्थिर जोड़ sctp_addr *ss1,
			स्थिर जोड़ sctp_addr *ss2)
अणु
	काष्ठा sctp_af *af;

	af = sctp_get_af_specअगरic(ss1->sa.sa_family);
	अगर (unlikely(!af))
		वापस 0;

	वापस af->cmp_addr(ss1, ss2);
पूर्ण

/* Return an ecne chunk to get prepended to a packet.
 * Note:  We are sly and वापस a shared, pपुनः_स्मृतिed chunk.  FIXME:
 * No we करोn't, but we could/should.
 */
काष्ठा sctp_chunk *sctp_get_ecne_prepend(काष्ठा sctp_association *asoc)
अणु
	अगर (!asoc->need_ecne)
		वापस शून्य;

	/* Send ECNE अगर needed.
	 * Not being able to allocate a chunk here is not deadly.
	 */
	वापस sctp_make_ecne(asoc, asoc->last_ecne_tsn);
पूर्ण

/*
 * Find which transport this TSN was sent on.
 */
काष्ठा sctp_transport *sctp_assoc_lookup_tsn(काष्ठा sctp_association *asoc,
					     __u32 tsn)
अणु
	काष्ठा sctp_transport *active;
	काष्ठा sctp_transport *match;
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_chunk *chunk;
	__be32 key = htonl(tsn);

	match = शून्य;

	/*
	 * FIXME: In general, find a more efficient data काष्ठाure क्रम
	 * searching.
	 */

	/*
	 * The general strategy is to search each transport's transmitted
	 * list.   Return which transport this TSN lives on.
	 *
	 * Let's be hopeful and check the active_path first.
	 * Another optimization would be to know अगर there is only one
	 * outbound path and not have to look क्रम the TSN at all.
	 *
	 */

	active = asoc->peer.active_path;

	list_क्रम_each_entry(chunk, &active->transmitted,
			transmitted_list) अणु

		अगर (key == chunk->subh.data_hdr->tsn) अणु
			match = active;
			जाओ out;
		पूर्ण
	पूर्ण

	/* If not found, go search all the other transports. */
	list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
			transports) अणु

		अगर (transport == active)
			जारी;
		list_क्रम_each_entry(chunk, &transport->transmitted,
				transmitted_list) अणु
			अगर (key == chunk->subh.data_hdr->tsn) अणु
				match = transport;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस match;
पूर्ण

/* Do delayed input processing.  This is scheduled by sctp_rcv(). */
अटल व्योम sctp_assoc_bh_rcv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sctp_association *asoc =
		container_of(work, काष्ठा sctp_association,
			     base.inqueue.immediate);
	काष्ठा net *net = asoc->base.net;
	जोड़ sctp_subtype subtype;
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_inq *inqueue;
	पूर्णांक first_समय = 1;	/* is this the first समय through the loop */
	पूर्णांक error = 0;
	पूर्णांक state;

	/* The association should be held so we should be safe. */
	ep = asoc->ep;

	inqueue = &asoc->base.inqueue;
	sctp_association_hold(asoc);
	जबतक (शून्य != (chunk = sctp_inq_pop(inqueue))) अणु
		state = asoc->state;
		subtype = SCTP_ST_CHUNK(chunk->chunk_hdr->type);

		/* If the first chunk in the packet is AUTH, करो special
		 * processing specअगरied in Section 6.3 of SCTP-AUTH spec
		 */
		अगर (first_समय && subtype.chunk == SCTP_CID_AUTH) अणु
			काष्ठा sctp_chunkhdr *next_hdr;

			next_hdr = sctp_inq_peek(inqueue);
			अगर (!next_hdr)
				जाओ normal;

			/* If the next chunk is COOKIE-ECHO, skip the AUTH
			 * chunk जबतक saving a poपूर्णांकer to it so we can करो
			 * Authentication later (during cookie-echo
			 * processing).
			 */
			अगर (next_hdr->type == SCTP_CID_COOKIE_ECHO) अणु
				chunk->auth_chunk = skb_clone(chunk->skb,
							      GFP_ATOMIC);
				chunk->auth = 1;
				जारी;
			पूर्ण
		पूर्ण

normal:
		/* SCTP-AUTH, Section 6.3:
		 *    The receiver has a list of chunk types which it expects
		 *    to be received only after an AUTH-chunk.  This list has
		 *    been sent to the peer during the association setup.  It
		 *    MUST silently discard these chunks अगर they are not placed
		 *    after an AUTH chunk in the packet.
		 */
		अगर (sctp_auth_recv_cid(subtype.chunk, asoc) && !chunk->auth)
			जारी;

		/* Remember where the last DATA chunk came from so we
		 * know where to send the SACK.
		 */
		अगर (sctp_chunk_is_data(chunk))
			asoc->peer.last_data_from = chunk->transport;
		अन्यथा अणु
			SCTP_INC_STATS(net, SCTP_MIB_INCTRLCHUNKS);
			asoc->stats.ictrlchunks++;
			अगर (chunk->chunk_hdr->type == SCTP_CID_SACK)
				asoc->stats.isacks++;
		पूर्ण

		अगर (chunk->transport)
			chunk->transport->last_समय_heard = kसमय_get();

		/* Run through the state machine. */
		error = sctp_करो_sm(net, SCTP_EVENT_T_CHUNK, subtype,
				   state, ep, asoc, chunk, GFP_ATOMIC);

		/* Check to see अगर the association is मुक्तd in response to
		 * the incoming chunk.  If so, get out of the जबतक loop.
		 */
		अगर (asoc->base.dead)
			अवरोध;

		/* If there is an error on chunk, discard this packet. */
		अगर (error && chunk)
			chunk->pdiscard = 1;

		अगर (first_समय)
			first_समय = 0;
	पूर्ण
	sctp_association_put(asoc);
पूर्ण

/* This routine moves an association from its old sk to a new sk.  */
व्योम sctp_assoc_migrate(काष्ठा sctp_association *assoc, काष्ठा sock *newsk)
अणु
	काष्ठा sctp_sock *newsp = sctp_sk(newsk);
	काष्ठा sock *oldsk = assoc->base.sk;

	/* Delete the association from the old endpoपूर्णांक's list of
	 * associations.
	 */
	list_del_init(&assoc->asocs);

	/* Decrement the backlog value क्रम a TCP-style socket. */
	अगर (sctp_style(oldsk, TCP))
		sk_acceptq_हटाओd(oldsk);

	/* Release references to the old endpoपूर्णांक and the sock.  */
	sctp_endpoपूर्णांक_put(assoc->ep);
	sock_put(assoc->base.sk);

	/* Get a reference to the new endpoपूर्णांक.  */
	assoc->ep = newsp->ep;
	sctp_endpoपूर्णांक_hold(assoc->ep);

	/* Get a reference to the new sock.  */
	assoc->base.sk = newsk;
	sock_hold(assoc->base.sk);

	/* Add the association to the new endpoपूर्णांक's list of associations.  */
	sctp_endpoपूर्णांक_add_asoc(newsp->ep, assoc);
पूर्ण

/* Update an association (possibly from unexpected COOKIE-ECHO processing).  */
पूर्णांक sctp_assoc_update(काष्ठा sctp_association *asoc,
		      काष्ठा sctp_association *new)
अणु
	काष्ठा sctp_transport *trans;
	काष्ठा list_head *pos, *temp;

	/* Copy in new parameters of peer. */
	asoc->c = new->c;
	asoc->peer.rwnd = new->peer.rwnd;
	asoc->peer.sack_needed = new->peer.sack_needed;
	asoc->peer.auth_capable = new->peer.auth_capable;
	asoc->peer.i = new->peer.i;

	अगर (!sctp_tsnmap_init(&asoc->peer.tsn_map, SCTP_TSN_MAP_INITIAL,
			      asoc->peer.i.initial_tsn, GFP_ATOMIC))
		वापस -ENOMEM;

	/* Remove any peer addresses not present in the new association. */
	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		trans = list_entry(pos, काष्ठा sctp_transport, transports);
		अगर (!sctp_assoc_lookup_paddr(new, &trans->ipaddr)) अणु
			sctp_assoc_rm_peer(asoc, trans);
			जारी;
		पूर्ण

		अगर (asoc->state >= SCTP_STATE_ESTABLISHED)
			sctp_transport_reset(trans);
	पूर्ण

	/* If the हाल is A (association restart), use
	 * initial_tsn as next_tsn. If the हाल is B, use
	 * current next_tsn in हाल data sent to peer
	 * has been discarded and needs retransmission.
	 */
	अगर (asoc->state >= SCTP_STATE_ESTABLISHED) अणु
		asoc->next_tsn = new->next_tsn;
		asoc->ctsn_ack_poपूर्णांक = new->ctsn_ack_poपूर्णांक;
		asoc->adv_peer_ack_poपूर्णांक = new->adv_peer_ack_poपूर्णांक;

		/* Reinitialize SSN क्रम both local streams
		 * and peer's streams.
		 */
		sctp_stream_clear(&asoc->stream);

		/* Flush the ULP reassembly and ordered queue.
		 * Any data there will now be stale and will
		 * cause problems.
		 */
		sctp_ulpq_flush(&asoc->ulpq);

		/* reset the overall association error count so
		 * that the restarted association करोesn't get torn
		 * करोwn on the next retransmission समयr.
		 */
		asoc->overall_error_count = 0;

	पूर्ण अन्यथा अणु
		/* Add any peer addresses from the new association. */
		list_क्रम_each_entry(trans, &new->peer.transport_addr_list,
				    transports)
			अगर (!sctp_assoc_lookup_paddr(asoc, &trans->ipaddr) &&
			    !sctp_assoc_add_peer(asoc, &trans->ipaddr,
						 GFP_ATOMIC, trans->state))
				वापस -ENOMEM;

		asoc->ctsn_ack_poपूर्णांक = asoc->next_tsn - 1;
		asoc->adv_peer_ack_poपूर्णांक = asoc->ctsn_ack_poपूर्णांक;

		अगर (sctp_state(asoc, COOKIE_WAIT))
			sctp_stream_update(&asoc->stream, &new->stream);

		/* get a new assoc id अगर we करोn't have one yet. */
		अगर (sctp_assoc_set_id(asoc, GFP_ATOMIC))
			वापस -ENOMEM;
	पूर्ण

	/* SCTP-AUTH: Save the peer parameters from the new associations
	 * and also move the association shared keys over
	 */
	kमुक्त(asoc->peer.peer_अक्रमom);
	asoc->peer.peer_अक्रमom = new->peer.peer_अक्रमom;
	new->peer.peer_अक्रमom = शून्य;

	kमुक्त(asoc->peer.peer_chunks);
	asoc->peer.peer_chunks = new->peer.peer_chunks;
	new->peer.peer_chunks = शून्य;

	kमुक्त(asoc->peer.peer_hmacs);
	asoc->peer.peer_hmacs = new->peer.peer_hmacs;
	new->peer.peer_hmacs = शून्य;

	वापस sctp_auth_asoc_init_active_key(asoc, GFP_ATOMIC);
पूर्ण

/* Update the retran path क्रम sending a retransmitted packet.
 * See also RFC4960, 6.4. Multi-Homed SCTP Endpoपूर्णांकs:
 *
 *   When there is outbound data to send and the primary path
 *   becomes inactive (e.g., due to failures), or where the
 *   SCTP user explicitly requests to send data to an
 *   inactive destination transport address, beक्रमe reporting
 *   an error to its ULP, the SCTP endpoपूर्णांक should try to send
 *   the data to an alternate active destination transport
 *   address अगर one exists.
 *
 *   When retransmitting data that समयd out, अगर the endpoपूर्णांक
 *   is multihomed, it should consider each source-destination
 *   address pair in its retransmission selection policy.
 *   When retransmitting समयd-out data, the endpoपूर्णांक should
 *   attempt to pick the most भागergent source-destination
 *   pair from the original source-destination pair to which
 *   the packet was transmitted.
 *
 *   Note: Rules क्रम picking the most भागergent source-destination
 *   pair are an implementation decision and are not specअगरied
 *   within this करोcument.
 *
 * Our basic strategy is to round-robin transports in priorities
 * according to sctp_trans_score() e.g., अगर no such
 * transport with state SCTP_ACTIVE exists, round-robin through
 * SCTP_UNKNOWN, etc. You get the picture.
 */
अटल u8 sctp_trans_score(स्थिर काष्ठा sctp_transport *trans)
अणु
	चयन (trans->state) अणु
	हाल SCTP_ACTIVE:
		वापस 3;	/* best हाल */
	हाल SCTP_UNKNOWN:
		वापस 2;
	हाल SCTP_PF:
		वापस 1;
	शेष: /* हाल SCTP_INACTIVE */
		वापस 0;	/* worst हाल */
	पूर्ण
पूर्ण

अटल काष्ठा sctp_transport *sctp_trans_elect_tie(काष्ठा sctp_transport *trans1,
						   काष्ठा sctp_transport *trans2)
अणु
	अगर (trans1->error_count > trans2->error_count) अणु
		वापस trans2;
	पूर्ण अन्यथा अगर (trans1->error_count == trans2->error_count &&
		   kसमय_after(trans2->last_समय_heard,
			       trans1->last_समय_heard)) अणु
		वापस trans2;
	पूर्ण अन्यथा अणु
		वापस trans1;
	पूर्ण
पूर्ण

अटल काष्ठा sctp_transport *sctp_trans_elect_best(काष्ठा sctp_transport *curr,
						    काष्ठा sctp_transport *best)
अणु
	u8 score_curr, score_best;

	अगर (best == शून्य || curr == best)
		वापस curr;

	score_curr = sctp_trans_score(curr);
	score_best = sctp_trans_score(best);

	/* First, try a score-based selection अगर both transport states
	 * dअगरfer. If we're in a tie, lets try to make a more clever
	 * decision here based on error counts and last समय heard.
	 */
	अगर (score_curr > score_best)
		वापस curr;
	अन्यथा अगर (score_curr == score_best)
		वापस sctp_trans_elect_tie(best, curr);
	अन्यथा
		वापस best;
पूर्ण

व्योम sctp_assoc_update_retran_path(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *trans = asoc->peer.retran_path;
	काष्ठा sctp_transport *trans_next = शून्य;

	/* We're करोne as we only have the one and only path. */
	अगर (asoc->peer.transport_count == 1)
		वापस;
	/* If active_path and retran_path are the same and active,
	 * then this is the only active path. Use it.
	 */
	अगर (asoc->peer.active_path == asoc->peer.retran_path &&
	    asoc->peer.active_path->state == SCTP_ACTIVE)
		वापस;

	/* Iterate from retran_path's successor back to retran_path. */
	क्रम (trans = list_next_entry(trans, transports); 1;
	     trans = list_next_entry(trans, transports)) अणु
		/* Manually skip the head element. */
		अगर (&trans->transports == &asoc->peer.transport_addr_list)
			जारी;
		अगर (trans->state == SCTP_UNCONFIRMED)
			जारी;
		trans_next = sctp_trans_elect_best(trans, trans_next);
		/* Active is good enough क्रम immediate वापस. */
		अगर (trans_next->state == SCTP_ACTIVE)
			अवरोध;
		/* We've reached the end, समय to update path. */
		अगर (trans == asoc->peer.retran_path)
			अवरोध;
	पूर्ण

	asoc->peer.retran_path = trans_next;

	pr_debug("%s: association:%p updated new path to addr:%pISpc\n",
		 __func__, asoc, &asoc->peer.retran_path->ipaddr.sa);
पूर्ण

अटल व्योम sctp_select_active_and_retran_path(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *trans, *trans_pri = शून्य, *trans_sec = शून्य;
	काष्ठा sctp_transport *trans_pf = शून्य;

	/* Look क्रम the two most recently used active transports. */
	list_क्रम_each_entry(trans, &asoc->peer.transport_addr_list,
			    transports) अणु
		/* Skip unपूर्णांकeresting transports. */
		अगर (trans->state == SCTP_INACTIVE ||
		    trans->state == SCTP_UNCONFIRMED)
			जारी;
		/* Keep track of the best PF transport from our
		 * list in हाल we करोn't find an active one.
		 */
		अगर (trans->state == SCTP_PF) अणु
			trans_pf = sctp_trans_elect_best(trans, trans_pf);
			जारी;
		पूर्ण
		/* For active transports, pick the most recent ones. */
		अगर (trans_pri == शून्य ||
		    kसमय_after(trans->last_समय_heard,
				trans_pri->last_समय_heard)) अणु
			trans_sec = trans_pri;
			trans_pri = trans;
		पूर्ण अन्यथा अगर (trans_sec == शून्य ||
			   kसमय_after(trans->last_समय_heard,
				       trans_sec->last_समय_heard)) अणु
			trans_sec = trans;
		पूर्ण
	पूर्ण

	/* RFC 2960 6.4 Multi-Homed SCTP Endpoपूर्णांकs
	 *
	 * By शेष, an endpoपूर्णांक should always transmit to the primary
	 * path, unless the SCTP user explicitly specअगरies the
	 * destination transport address (and possibly source transport
	 * address) to use. [If the primary is active but not most recent,
	 * bump the most recently used transport.]
	 */
	अगर ((asoc->peer.primary_path->state == SCTP_ACTIVE ||
	     asoc->peer.primary_path->state == SCTP_UNKNOWN) &&
	     asoc->peer.primary_path != trans_pri) अणु
		trans_sec = trans_pri;
		trans_pri = asoc->peer.primary_path;
	पूर्ण

	/* We did not find anything useful क्रम a possible retransmission
	 * path; either primary path that we found is the same as
	 * the current one, or we didn't generally find an active one.
	 */
	अगर (trans_sec == शून्य)
		trans_sec = trans_pri;

	/* If we failed to find a usable transport, just camp on the
	 * active or pick a PF अगरf it's the better choice.
	 */
	अगर (trans_pri == शून्य) अणु
		trans_pri = sctp_trans_elect_best(asoc->peer.active_path, trans_pf);
		trans_sec = trans_pri;
	पूर्ण

	/* Set the active and retran transports. */
	asoc->peer.active_path = trans_pri;
	asoc->peer.retran_path = trans_sec;
पूर्ण

काष्ठा sctp_transport *
sctp_assoc_choose_alter_transport(काष्ठा sctp_association *asoc,
				  काष्ठा sctp_transport *last_sent_to)
अणु
	/* If this is the first समय packet is sent, use the active path,
	 * अन्यथा use the retran path. If the last packet was sent over the
	 * retran path, update the retran path and use it.
	 */
	अगर (last_sent_to == शून्य) अणु
		वापस asoc->peer.active_path;
	पूर्ण अन्यथा अणु
		अगर (last_sent_to == asoc->peer.retran_path)
			sctp_assoc_update_retran_path(asoc);

		वापस asoc->peer.retran_path;
	पूर्ण
पूर्ण

व्योम sctp_assoc_update_frag_poपूर्णांक(काष्ठा sctp_association *asoc)
अणु
	पूर्णांक frag = sctp_mtu_payload(sctp_sk(asoc->base.sk), asoc->pathmtu,
				    sctp_datachk_len(&asoc->stream));

	अगर (asoc->user_frag)
		frag = min_t(पूर्णांक, frag, asoc->user_frag);

	frag = min_t(पूर्णांक, frag, SCTP_MAX_CHUNK_LEN -
				sctp_datachk_len(&asoc->stream));

	asoc->frag_poपूर्णांक = SCTP_TRUNC4(frag);
पूर्ण

व्योम sctp_assoc_set_pmtu(काष्ठा sctp_association *asoc, __u32 pmtu)
अणु
	अगर (asoc->pathmtu != pmtu) अणु
		asoc->pathmtu = pmtu;
		sctp_assoc_update_frag_poपूर्णांक(asoc);
	पूर्ण

	pr_debug("%s: asoc:%p, pmtu:%d, frag_point:%d\n", __func__, asoc,
		 asoc->pathmtu, asoc->frag_poपूर्णांक);
पूर्ण

/* Update the association's pmtu and frag_poपूर्णांक by going through all the
 * transports. This routine is called when a transport's PMTU has changed.
 */
व्योम sctp_assoc_sync_pmtu(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_transport *t;
	__u32 pmtu = 0;

	अगर (!asoc)
		वापस;

	/* Get the lowest pmtu of all the transports. */
	list_क्रम_each_entry(t, &asoc->peer.transport_addr_list, transports) अणु
		अगर (t->pmtu_pending && t->dst) अणु
			sctp_transport_update_pmtu(t,
						   atomic_पढ़ो(&t->mtu_info));
			t->pmtu_pending = 0;
		पूर्ण
		अगर (!pmtu || (t->pathmtu < pmtu))
			pmtu = t->pathmtu;
	पूर्ण

	sctp_assoc_set_pmtu(asoc, pmtu);
पूर्ण

/* Should we send a SACK to update our peer? */
अटल अंतरभूत bool sctp_peer_needs_update(काष्ठा sctp_association *asoc)
अणु
	काष्ठा net *net = asoc->base.net;

	चयन (asoc->state) अणु
	हाल SCTP_STATE_ESTABLISHED:
	हाल SCTP_STATE_SHUTDOWN_PENDING:
	हाल SCTP_STATE_SHUTDOWN_RECEIVED:
	हाल SCTP_STATE_SHUTDOWN_SENT:
		अगर ((asoc->rwnd > asoc->a_rwnd) &&
		    ((asoc->rwnd - asoc->a_rwnd) >= max_t(__u32,
			   (asoc->base.sk->sk_rcvbuf >> net->sctp.rwnd_upd_shअगरt),
			   asoc->pathmtu)))
			वापस true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

/* Increase asoc's rwnd by len and send any winकरोw update SACK अगर needed. */
व्योम sctp_assoc_rwnd_increase(काष्ठा sctp_association *asoc, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sctp_chunk *sack;
	काष्ठा समयr_list *समयr;

	अगर (asoc->rwnd_over) अणु
		अगर (asoc->rwnd_over >= len) अणु
			asoc->rwnd_over -= len;
		पूर्ण अन्यथा अणु
			asoc->rwnd += (len - asoc->rwnd_over);
			asoc->rwnd_over = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		asoc->rwnd += len;
	पूर्ण

	/* If we had winकरोw pressure, start recovering it
	 * once our rwnd had reached the accumulated pressure
	 * threshold.  The idea is to recover slowly, but up
	 * to the initial advertised winकरोw.
	 */
	अगर (asoc->rwnd_press) अणु
		पूर्णांक change = min(asoc->pathmtu, asoc->rwnd_press);
		asoc->rwnd += change;
		asoc->rwnd_press -= change;
	पूर्ण

	pr_debug("%s: asoc:%p rwnd increased by %d to (%u, %u) - %u\n",
		 __func__, asoc, len, asoc->rwnd, asoc->rwnd_over,
		 asoc->a_rwnd);

	/* Send a winकरोw update SACK अगर the rwnd has increased by at least the
	 * minimum of the association's PMTU and half of the receive buffer.
	 * The algorithm used is similar to the one described in
	 * Section 4.2.3.3 of RFC 1122.
	 */
	अगर (sctp_peer_needs_update(asoc)) अणु
		asoc->a_rwnd = asoc->rwnd;

		pr_debug("%s: sending window update SACK- asoc:%p rwnd:%u "
			 "a_rwnd:%u\n", __func__, asoc, asoc->rwnd,
			 asoc->a_rwnd);

		sack = sctp_make_sack(asoc);
		अगर (!sack)
			वापस;

		asoc->peer.sack_needed = 0;

		sctp_outq_tail(&asoc->outqueue, sack, GFP_ATOMIC);

		/* Stop the SACK समयr.  */
		समयr = &asoc->समयrs[SCTP_EVENT_TIMEOUT_SACK];
		अगर (del_समयr(समयr))
			sctp_association_put(asoc);
	पूर्ण
पूर्ण

/* Decrease asoc's rwnd by len. */
व्योम sctp_assoc_rwnd_decrease(काष्ठा sctp_association *asoc, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक rx_count;
	पूर्णांक over = 0;

	अगर (unlikely(!asoc->rwnd || asoc->rwnd_over))
		pr_debug("%s: association:%p has asoc->rwnd:%u, "
			 "asoc->rwnd_over:%u!\n", __func__, asoc,
			 asoc->rwnd, asoc->rwnd_over);

	अगर (asoc->ep->rcvbuf_policy)
		rx_count = atomic_पढ़ो(&asoc->rmem_alloc);
	अन्यथा
		rx_count = atomic_पढ़ो(&asoc->base.sk->sk_rmem_alloc);

	/* If we've reached or overflowed our receive buffer, announce
	 * a 0 rwnd अगर rwnd would still be positive.  Store the
	 * potential pressure overflow so that the winकरोw can be restored
	 * back to original value.
	 */
	अगर (rx_count >= asoc->base.sk->sk_rcvbuf)
		over = 1;

	अगर (asoc->rwnd >= len) अणु
		asoc->rwnd -= len;
		अगर (over) अणु
			asoc->rwnd_press += asoc->rwnd;
			asoc->rwnd = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		asoc->rwnd_over += len - asoc->rwnd;
		asoc->rwnd = 0;
	पूर्ण

	pr_debug("%s: asoc:%p rwnd decreased by %d to (%u, %u, %u)\n",
		 __func__, asoc, len, asoc->rwnd, asoc->rwnd_over,
		 asoc->rwnd_press);
पूर्ण

/* Build the bind address list क्रम the association based on info from the
 * local endpoपूर्णांक and the remote peer.
 */
पूर्णांक sctp_assoc_set_bind_addr_from_ep(काष्ठा sctp_association *asoc,
				     क्रमागत sctp_scope scope, gfp_t gfp)
अणु
	काष्ठा sock *sk = asoc->base.sk;
	पूर्णांक flags;

	/* Use scoping rules to determine the subset of addresses from
	 * the endpoपूर्णांक.
	 */
	flags = (PF_INET6 == sk->sk_family) ? SCTP_ADDR6_ALLOWED : 0;
	अगर (!inet_v6_ipv6only(sk))
		flags |= SCTP_ADDR4_ALLOWED;
	अगर (asoc->peer.ipv4_address)
		flags |= SCTP_ADDR4_PEERSUPP;
	अगर (asoc->peer.ipv6_address)
		flags |= SCTP_ADDR6_PEERSUPP;

	वापस sctp_bind_addr_copy(asoc->base.net,
				   &asoc->base.bind_addr,
				   &asoc->ep->base.bind_addr,
				   scope, gfp, flags);
पूर्ण

/* Build the association's bind address list from the cookie.  */
पूर्णांक sctp_assoc_set_bind_addr_from_cookie(काष्ठा sctp_association *asoc,
					 काष्ठा sctp_cookie *cookie,
					 gfp_t gfp)
अणु
	पूर्णांक var_size2 = ntohs(cookie->peer_init->chunk_hdr.length);
	पूर्णांक var_size3 = cookie->raw_addr_list_len;
	__u8 *raw = (__u8 *)cookie->peer_init + var_size2;

	वापस sctp_raw_to_bind_addrs(&asoc->base.bind_addr, raw, var_size3,
				      asoc->ep->base.bind_addr.port, gfp);
पूर्ण

/* Lookup laddr in the bind address list of an association. */
पूर्णांक sctp_assoc_lookup_laddr(काष्ठा sctp_association *asoc,
			    स्थिर जोड़ sctp_addr *laddr)
अणु
	पूर्णांक found = 0;

	अगर ((asoc->base.bind_addr.port == ntohs(laddr->v4.sin_port)) &&
	    sctp_bind_addr_match(&asoc->base.bind_addr, laddr,
				 sctp_sk(asoc->base.sk)))
		found = 1;

	वापस found;
पूर्ण

/* Set an association id क्रम a given association */
पूर्णांक sctp_assoc_set_id(काष्ठा sctp_association *asoc, gfp_t gfp)
अणु
	bool preload = gfpflags_allow_blocking(gfp);
	पूर्णांक ret;

	/* If the id is alपढ़ोy asचिन्हित, keep it. */
	अगर (asoc->assoc_id)
		वापस 0;

	अगर (preload)
		idr_preload(gfp);
	spin_lock_bh(&sctp_assocs_id_lock);
	/* 0, 1, 2 are used as SCTP_FUTURE_ASSOC, SCTP_CURRENT_ASSOC and
	 * SCTP_ALL_ASSOC, so an available id must be > SCTP_ALL_ASSOC.
	 */
	ret = idr_alloc_cyclic(&sctp_assocs_id, asoc, SCTP_ALL_ASSOC + 1, 0,
			       GFP_NOWAIT);
	spin_unlock_bh(&sctp_assocs_id_lock);
	अगर (preload)
		idr_preload_end();
	अगर (ret < 0)
		वापस ret;

	asoc->assoc_id = (sctp_assoc_t)ret;
	वापस 0;
पूर्ण

/* Free the ASCONF queue */
अटल व्योम sctp_assoc_मुक्त_asconf_queue(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_chunk *asconf;
	काष्ठा sctp_chunk *पंचांगp;

	list_क्रम_each_entry_safe(asconf, पंचांगp, &asoc->addip_chunk_list, list) अणु
		list_del_init(&asconf->list);
		sctp_chunk_मुक्त(asconf);
	पूर्ण
पूर्ण

/* Free asconf_ack cache */
अटल व्योम sctp_assoc_मुक्त_asconf_acks(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_chunk *ack;
	काष्ठा sctp_chunk *पंचांगp;

	list_क्रम_each_entry_safe(ack, पंचांगp, &asoc->asconf_ack_list,
				transmitted_list) अणु
		list_del_init(&ack->transmitted_list);
		sctp_chunk_मुक्त(ack);
	पूर्ण
पूर्ण

/* Clean up the ASCONF_ACK queue */
व्योम sctp_assoc_clean_asconf_ack_cache(स्थिर काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_chunk *ack;
	काष्ठा sctp_chunk *पंचांगp;

	/* We can हटाओ all the entries from the queue up to
	 * the "Peer-Sequence-Number".
	 */
	list_क्रम_each_entry_safe(ack, पंचांगp, &asoc->asconf_ack_list,
				transmitted_list) अणु
		अगर (ack->subh.addip_hdr->serial ==
				htonl(asoc->peer.addip_serial))
			अवरोध;

		list_del_init(&ack->transmitted_list);
		sctp_chunk_मुक्त(ack);
	पूर्ण
पूर्ण

/* Find the ASCONF_ACK whose serial number matches ASCONF */
काष्ठा sctp_chunk *sctp_assoc_lookup_asconf_ack(
					स्थिर काष्ठा sctp_association *asoc,
					__be32 serial)
अणु
	काष्ठा sctp_chunk *ack;

	/* Walk through the list of cached ASCONF-ACKs and find the
	 * ack chunk whose serial number matches that of the request.
	 */
	list_क्रम_each_entry(ack, &asoc->asconf_ack_list, transmitted_list) अणु
		अगर (sctp_chunk_pending(ack))
			जारी;
		अगर (ack->subh.addip_hdr->serial == serial) अणु
			sctp_chunk_hold(ack);
			वापस ack;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम sctp_asconf_queue_tearकरोwn(काष्ठा sctp_association *asoc)
अणु
	/* Free any cached ASCONF_ACK chunk. */
	sctp_assoc_मुक्त_asconf_acks(asoc);

	/* Free the ASCONF queue. */
	sctp_assoc_मुक्त_asconf_queue(asoc);

	/* Free any cached ASCONF chunk. */
	अगर (asoc->addip_last_asconf)
		sctp_chunk_मुक्त(asoc->addip_last_asconf);
पूर्ण
