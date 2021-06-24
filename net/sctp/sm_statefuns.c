<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2002 Intel Corp.
 * Copyright (c) 2002      Nokia Corp.
 *
 * This is part of the SCTP Linux Kernel Implementation.
 *
 * These are the state functions क्रम the state machine.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Mathew Kotowsky       <kotowsky@sctp.org>
 *    Sridhar Samudrala     <samudrala@us.ibm.com>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Hui Huang 	    <hui.huang@nokia.com>
 *    Dajiang Zhang 	    <dajiang.zhang@nokia.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Ryan Layer	    <rmlayer@us.ibm.com>
 *    Kevin Gao		    <kevin.gao@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/inet_ecn.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/काष्ठाs.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/sctp.h>

अटल काष्ठा sctp_packet *sctp_पात_pkt_new(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					स्थिर व्योम *payload, माप_प्रकार paylen);
अटल पूर्णांक sctp_eat_data(स्थिर काष्ठा sctp_association *asoc,
			 काष्ठा sctp_chunk *chunk,
			 काष्ठा sctp_cmd_seq *commands);
अटल काष्ठा sctp_packet *sctp_ootb_pkt_new(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk);
अटल व्योम sctp_send_stale_cookie_err(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर काष्ठा sctp_chunk *chunk,
				       काष्ठा sctp_cmd_seq *commands,
				       काष्ठा sctp_chunk *err_chunk);
अटल क्रमागत sctp_disposition sctp_sf_करो_5_2_6_stale(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);
अटल क्रमागत sctp_disposition sctp_sf_shut_8_4_5(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);
अटल क्रमागत sctp_disposition sctp_sf_tपात_8_4_8(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);
अटल क्रमागत sctp_disposition sctp_sf_new_encap_port(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);
अटल काष्ठा sctp_sackhdr *sctp_sm_pull_sack(काष्ठा sctp_chunk *chunk);

अटल क्रमागत sctp_disposition sctp_stop_t1_and_पात(
					काष्ठा net *net,
					काष्ठा sctp_cmd_seq *commands,
					__be16 error, पूर्णांक sk_err,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_transport *transport);

अटल क्रमागत sctp_disposition sctp_sf_पात_violation(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands,
					स्थिर __u8 *payload,
					स्थिर माप_प्रकार paylen);

अटल क्रमागत sctp_disposition sctp_sf_violation_chunklen(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);

अटल क्रमागत sctp_disposition sctp_sf_violation_paramlen(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg, व्योम *ext,
					काष्ठा sctp_cmd_seq *commands);

अटल क्रमागत sctp_disposition sctp_sf_violation_ctsn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);

अटल क्रमागत sctp_disposition sctp_sf_violation_chunk(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);

अटल क्रमागत sctp_ierror sctp_sf_authenticate(
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk);

अटल क्रमागत sctp_disposition __sctp_sf_करो_9_1_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);

/* Small helper function that checks अगर the chunk length
 * is of the appropriate length.  The 'required_length' argument
 * is set to be the size of a specअगरic chunk we are testing.
 * Return Values:  true  = Valid length
 * 		   false = Invalid length
 *
 */
अटल अंतरभूत bool sctp_chunk_length_valid(काष्ठा sctp_chunk *chunk,
					   __u16 required_length)
अणु
	__u16 chunk_length = ntohs(chunk->chunk_hdr->length);

	/* Previously alपढ़ोy marked? */
	अगर (unlikely(chunk->pdiscard))
		वापस false;
	अगर (unlikely(chunk_length < required_length))
		वापस false;

	वापस true;
पूर्ण

/* Check क्रम क्रमmat error in an ABORT chunk */
अटल अंतरभूत bool sctp_err_chunk_valid(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_errhdr *err;

	sctp_walk_errors(err, chunk->chunk_hdr);

	वापस (व्योम *)err == (व्योम *)chunk->chunk_end;
पूर्ण

/**********************************************************
 * These are the state functions क्रम handling chunk events.
 **********************************************************/

/*
 * Process the final SHUTDOWN COMPLETE.
 *
 * Section: 4 (C) (diagram), 9.2
 * Upon reception of the SHUTDOWN COMPLETE chunk the endpoपूर्णांक will verअगरy
 * that it is in SHUTDOWN-ACK-SENT state, अगर it is not the chunk should be
 * discarded. If the endpoपूर्णांक is in the SHUTDOWN-ACK-SENT state the endpoपूर्णांक
 * should stop the T2-shutकरोwn समयr and हटाओ all knowledge of the
 * association (and thus the association enters the CLOSED state).
 *
 * Verअगरication Tag: 8.5.1(C), sctpimpguide 2.41.
 * C) Rules क्रम packet carrying SHUTDOWN COMPLETE:
 * ...
 * - The receiver of a SHUTDOWN COMPLETE shall accept the packet
 *   अगर the Verअगरication Tag field of the packet matches its own tag and
 *   the T bit is not set
 *   OR
 *   it is set to its peer's tag and the T bit is set in the Chunk
 *   Flags.
 *   Otherwise, the receiver MUST silently discard the packet
 *   and take no further action.  An endpoपूर्णांक MUST ignore the
 *   SHUTDOWN COMPLETE अगर it is not in the SHUTDOWN-ACK-SENT state.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_4_C(काष्ठा net *net,
				     स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				     स्थिर काष्ठा sctp_association *asoc,
				     स्थिर जोड़ sctp_subtype type,
				     व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_ulpevent *ev;

	अगर (!sctp_vtag_verअगरy_either(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* RFC 2960 6.10 Bundling
	 *
	 * An endpoपूर्णांक MUST NOT bundle INIT, INIT ACK or
	 * SHUTDOWN COMPLETE with any other chunks.
	 */
	अगर (!chunk->singleton)
		वापस sctp_sf_violation_chunk(net, ep, asoc, type, arg, commands);

	/* Make sure that the SHUTDOWN_COMPLETE chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* RFC 2960 10.2 SCTP-to-ULP
	 *
	 * H) SHUTDOWN COMPLETE notअगरication
	 *
	 * When SCTP completes the shutकरोwn procedures (section 9.2) this
	 * notअगरication is passed to the upper layer.
	 */
	ev = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_SHUTDOWN_COMP,
					     0, 0, 0, शून्य, GFP_ATOMIC);
	अगर (ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));

	/* Upon reception of the SHUTDOWN COMPLETE chunk the endpoपूर्णांक
	 * will verअगरy that it is in SHUTDOWN-ACK-SENT state, अगर it is
	 * not the chunk should be discarded. If the endpoपूर्णांक is in
	 * the SHUTDOWN-ACK-SENT state the endpoपूर्णांक should stop the
	 * T2-shutकरोwn समयr and हटाओ all knowledge of the
	 * association (and thus the association enters the CLOSED
	 * state).
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	SCTP_INC_STATS(net, SCTP_MIB_SHUTDOWNS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);

	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());

	वापस SCTP_DISPOSITION_DELETE_TCB;
पूर्ण

/*
 * Respond to a normal INIT chunk.
 * We are the side that is being asked क्रम an association.
 *
 * Section: 5.1 Normal Establishment of an Association, B
 * B) "Z" shall respond immediately with an INIT ACK chunk.  The
 *    destination IP address of the INIT ACK MUST be set to the source
 *    IP address of the INIT to which this INIT ACK is responding.  In
 *    the response, besides filling in other parameters, "Z" must set the
 *    Verअगरication Tag field to Tag_A, and also provide its own
 *    Verअगरication Tag (Tag_Z) in the Initiate Tag field.
 *
 * Verअगरication Tag: Must be 0.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_1B_init(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg, *repl, *err_chunk;
	काष्ठा sctp_unrecognized_param *unk_param;
	काष्ठा sctp_association *new_asoc;
	काष्ठा sctp_packet *packet;
	पूर्णांक len;

	/* Update socket peer label अगर first association. */
	अगर (security_sctp_assoc_request((काष्ठा sctp_endpoपूर्णांक *)ep,
					chunk->skb))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* 6.10 Bundling
	 * An endpoपूर्णांक MUST NOT bundle INIT, INIT ACK or
	 * SHUTDOWN COMPLETE with any other chunks.
	 *
	 * IG Section 2.11.2
	 * Furthermore, we require that the receiver of an INIT chunk MUST
	 * enक्रमce these rules by silently discarding an arriving packet
	 * with an INIT chunk that is bundled with other chunks.
	 */
	अगर (!chunk->singleton)
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* If the packet is an OOTB packet which is temporarily on the
	 * control endpoपूर्णांक, respond with an ABORT.
	 */
	अगर (ep == sctp_sk(net->sctp.ctl_sock)->ep) अणु
		SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* 3.1 A packet containing an INIT chunk MUST have a zero Verअगरication
	 * Tag.
	 */
	अगर (chunk->sctp_hdr->vtag != 0)
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);

	/* Make sure that the INIT chunk has a valid length.
	 * Normally, this would cause an ABORT with a Protocol Violation
	 * error, but since we करोn't have an association, we'll
	 * just discard the packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_init_chunk)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* If the INIT is coming toward a closing socket, we'll send back
	 * and ABORT.  Essentially, this catches the race of INIT being
	 * backloged to the socket at the same समय as the user isses बंद().
	 * Since the socket and all its associations are going away, we
	 * can treat this OOTB
	 */
	अगर (sctp_sstate(ep->base.sk, CLOSING))
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);

	/* Verअगरy the INIT chunk beक्रमe processing it. */
	err_chunk = शून्य;
	अगर (!sctp_verअगरy_init(net, ep, asoc, chunk->chunk_hdr->type,
			      (काष्ठा sctp_init_chunk *)chunk->chunk_hdr, chunk,
			      &err_chunk)) अणु
		/* This chunk contains fatal error. It is to be discarded.
		 * Send an ABORT, with causes अगर there is any.
		 */
		अगर (err_chunk) अणु
			packet = sctp_पात_pkt_new(net, ep, asoc, arg,
					(__u8 *)(err_chunk->chunk_hdr) +
					माप(काष्ठा sctp_chunkhdr),
					ntohs(err_chunk->chunk_hdr->length) -
					माप(काष्ठा sctp_chunkhdr));

			sctp_chunk_मुक्त(err_chunk);

			अगर (packet) अणु
				sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
						SCTP_PACKET(packet));
				SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
				वापस SCTP_DISPOSITION_CONSUME;
			पूर्ण अन्यथा अणु
				वापस SCTP_DISPOSITION_NOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg,
						    commands);
		पूर्ण
	पूर्ण

	/* Grab the INIT header.  */
	chunk->subh.init_hdr = (काष्ठा sctp_inithdr *)chunk->skb->data;

	/* Tag the variable length parameters.  */
	chunk->param_hdr.v = skb_pull(chunk->skb, माप(काष्ठा sctp_inithdr));

	new_asoc = sctp_make_temp_asoc(ep, chunk, GFP_ATOMIC);
	अगर (!new_asoc)
		जाओ nomem;

	अगर (sctp_assoc_set_bind_addr_from_ep(new_asoc,
					     sctp_scope(sctp_source(chunk)),
					     GFP_ATOMIC) < 0)
		जाओ nomem_init;

	/* The call, sctp_process_init(), can fail on memory allocation.  */
	अगर (!sctp_process_init(new_asoc, chunk, sctp_source(chunk),
			       (काष्ठा sctp_init_chunk *)chunk->chunk_hdr,
			       GFP_ATOMIC))
		जाओ nomem_init;

	/* B) "Z" shall respond immediately with an INIT ACK chunk.  */

	/* If there are errors need to be reported क्रम unknown parameters,
	 * make sure to reserve enough room in the INIT ACK क्रम them.
	 */
	len = 0;
	अगर (err_chunk)
		len = ntohs(err_chunk->chunk_hdr->length) -
		      माप(काष्ठा sctp_chunkhdr);

	repl = sctp_make_init_ack(new_asoc, chunk, GFP_ATOMIC, len);
	अगर (!repl)
		जाओ nomem_init;

	/* If there are errors need to be reported क्रम unknown parameters,
	 * include them in the outgoing INIT ACK as "Unrecognized parameter"
	 * parameter.
	 */
	अगर (err_chunk) अणु
		/* Get the "Unrecognized parameter" parameter(s) out of the
		 * ERROR chunk generated by sctp_verअगरy_init(). Since the
		 * error cause code क्रम "unknown parameter" and the
		 * "Unrecognized parameter" type is the same, we can
		 * स्थिरruct the parameters in INIT ACK by copying the
		 * ERROR causes over.
		 */
		unk_param = (काष्ठा sctp_unrecognized_param *)
			    ((__u8 *)(err_chunk->chunk_hdr) +
			    माप(काष्ठा sctp_chunkhdr));
		/* Replace the cause code with the "Unrecognized parameter"
		 * parameter type.
		 */
		sctp_addto_chunk(repl, len, unk_param);
		sctp_chunk_मुक्त(err_chunk);
	पूर्ण

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_ASOC, SCTP_ASOC(new_asoc));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	/*
	 * Note:  After sending out INIT ACK with the State Cookie parameter,
	 * "Z" MUST NOT allocate any resources, nor keep any states क्रम the
	 * new association.  Otherwise, "Z" will be vulnerable to resource
	 * attacks.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());

	वापस SCTP_DISPOSITION_DELETE_TCB;

nomem_init:
	sctp_association_मुक्त(new_asoc);
nomem:
	अगर (err_chunk)
		sctp_chunk_मुक्त(err_chunk);
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Respond to a normal INIT ACK chunk.
 * We are the side that is initiating the association.
 *
 * Section: 5.1 Normal Establishment of an Association, C
 * C) Upon reception of the INIT ACK from "Z", "A" shall stop the T1-init
 *    समयr and leave COOKIE-WAIT state. "A" shall then send the State
 *    Cookie received in the INIT ACK chunk in a COOKIE ECHO chunk, start
 *    the T1-cookie समयr, and enter the COOKIE-ECHOED state.
 *
 *    Note: The COOKIE ECHO chunk can be bundled with any pending outbound
 *    DATA chunks, but it MUST be the first chunk in the packet and
 *    until the COOKIE ACK is वापसed the sender MUST NOT send any
 *    other packets to the peer.
 *
 * Verअगरication Tag: 3.3.3
 *   If the value of the Initiate Tag in a received INIT ACK chunk is
 *   found to be 0, the receiver MUST treat it as an error and बंद the
 *   association by transmitting an ABORT.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_1C_ack(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_init_chunk *initchunk;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *err_chunk;
	काष्ठा sctp_packet *packet;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* 6.10 Bundling
	 * An endpoपूर्णांक MUST NOT bundle INIT, INIT ACK or
	 * SHUTDOWN COMPLETE with any other chunks.
	 */
	अगर (!chunk->singleton)
		वापस sctp_sf_violation_chunk(net, ep, asoc, type, arg, commands);

	/* Make sure that the INIT-ACK chunk has a valid length */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_initack_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);
	/* Grab the INIT header.  */
	chunk->subh.init_hdr = (काष्ठा sctp_inithdr *)chunk->skb->data;

	/* Verअगरy the INIT chunk beक्रमe processing it. */
	err_chunk = शून्य;
	अगर (!sctp_verअगरy_init(net, ep, asoc, chunk->chunk_hdr->type,
			      (काष्ठा sctp_init_chunk *)chunk->chunk_hdr, chunk,
			      &err_chunk)) अणु

		क्रमागत sctp_error error = SCTP_ERROR_NO_RESOURCE;

		/* This chunk contains fatal error. It is to be discarded.
		 * Send an ABORT, with causes.  If there are no causes,
		 * then there wasn't enough memory.  Just terminate
		 * the association.
		 */
		अगर (err_chunk) अणु
			packet = sctp_पात_pkt_new(net, ep, asoc, arg,
					(__u8 *)(err_chunk->chunk_hdr) +
					माप(काष्ठा sctp_chunkhdr),
					ntohs(err_chunk->chunk_hdr->length) -
					माप(काष्ठा sctp_chunkhdr));

			sctp_chunk_मुक्त(err_chunk);

			अगर (packet) अणु
				sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
						SCTP_PACKET(packet));
				SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
				error = SCTP_ERROR_INV_PARAM;
			पूर्ण
		पूर्ण

		/* SCTP-AUTH, Section 6.3:
		 *    It should be noted that अगर the receiver wants to tear
		 *    करोwn an association in an authenticated way only, the
		 *    handling of malक्रमmed packets should not result in
		 *    tearing करोwn the association.
		 *
		 * This means that अगर we only want to पात associations
		 * in an authenticated way (i.e AUTH+ABORT), then we
		 * can't destroy this association just because the packet
		 * was malक्रमmed.
		 */
		अगर (sctp_auth_recv_cid(SCTP_CID_ABORT, asoc))
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		वापस sctp_stop_t1_and_पात(net, commands, error, ECONNREFUSED,
						asoc, chunk->transport);
	पूर्ण

	/* Tag the variable length parameters.  Note that we never
	 * convert the parameters in an INIT chunk.
	 */
	chunk->param_hdr.v = skb_pull(chunk->skb, माप(काष्ठा sctp_inithdr));

	initchunk = (काष्ठा sctp_init_chunk *)chunk->chunk_hdr;

	sctp_add_cmd_sf(commands, SCTP_CMD_PEER_INIT,
			SCTP_PEER_INIT(initchunk));

	/* Reset init error count upon receipt of INIT-ACK.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_COUNTER_RESET, SCTP_शून्य());

	/* 5.1 C) "A" shall stop the T1-init समयr and leave
	 * COOKIE-WAIT state.  "A" shall then ... start the T1-cookie
	 * समयr, and enter the COOKIE-ECHOED state.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_COOKIE_ECHOED));

	/* SCTP-AUTH: genereate the assocition shared keys so that
	 * we can potentially signe the COOKIE-ECHO.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_SHKEY, SCTP_शून्य());

	/* 5.1 C) "A" shall then send the State Cookie received in the
	 * INIT ACK chunk in a COOKIE ECHO chunk, ...
	 */
	/* If there is any errors to report, send the ERROR chunk generated
	 * क्रम unknown parameters as well.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_COOKIE_ECHO,
			SCTP_CHUNK(err_chunk));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

अटल bool sctp_auth_chunk_verअगरy(काष्ठा net *net, काष्ठा sctp_chunk *chunk,
				   स्थिर काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_chunk auth;

	अगर (!chunk->auth_chunk)
		वापस true;

	/* SCTP-AUTH:  auth_chunk poपूर्णांकer is only set when the cookie-echo
	 * is supposed to be authenticated and we have to करो delayed
	 * authentication.  We've just recreated the association using
	 * the inक्रमmation in the cookie and now it's much easier to
	 * करो the authentication.
	 */

	/* Make sure that we and the peer are AUTH capable */
	अगर (!net->sctp.auth_enable || !asoc->peer.auth_capable)
		वापस false;

	/* set-up our fake chunk so that we can process it */
	auth.skb = chunk->auth_chunk;
	auth.asoc = chunk->asoc;
	auth.sctp_hdr = chunk->sctp_hdr;
	auth.chunk_hdr = (काष्ठा sctp_chunkhdr *)
				skb_push(chunk->auth_chunk,
					 माप(काष्ठा sctp_chunkhdr));
	skb_pull(chunk->auth_chunk, माप(काष्ठा sctp_chunkhdr));
	auth.transport = chunk->transport;

	वापस sctp_sf_authenticate(asoc, &auth) == SCTP_IERROR_NO_ERROR;
पूर्ण

/*
 * Respond to a normal COOKIE ECHO chunk.
 * We are the side that is being asked क्रम an association.
 *
 * Section: 5.1 Normal Establishment of an Association, D
 * D) Upon reception of the COOKIE ECHO chunk, Endpoपूर्णांक "Z" will reply
 *    with a COOKIE ACK chunk after building a TCB and moving to
 *    the ESTABLISHED state. A COOKIE ACK chunk may be bundled with
 *    any pending DATA chunks (and/or SACK chunks), but the COOKIE ACK
 *    chunk MUST be the first chunk in the packet.
 *
 *   IMPLEMENTATION NOTE: An implementation may choose to send the
 *   Communication Up notअगरication to the SCTP user upon reception
 *   of a valid COOKIE ECHO chunk.
 *
 * Verअगरication Tag: 8.5.1 Exceptions in Verअगरication Tag Rules
 * D) Rules क्रम packet carrying a COOKIE ECHO
 *
 * - When sending a COOKIE ECHO, the endpoपूर्णांक MUST use the value of the
 *   Initial Tag received in the INIT ACK.
 *
 * - The receiver of a COOKIE ECHO follows the procedures in Section 5.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_1D_ce(काष्ठा net *net,
					 स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					 स्थिर काष्ठा sctp_association *asoc,
					 स्थिर जोड़ sctp_subtype type,
					 व्योम *arg,
					 काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_ulpevent *ev, *ai_ev = शून्य, *auth_ev = शून्य;
	काष्ठा sctp_association *new_asoc;
	काष्ठा sctp_init_chunk *peer_init;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *err_chk_p;
	काष्ठा sctp_chunk *repl;
	काष्ठा sock *sk;
	पूर्णांक error = 0;

	/* If the packet is an OOTB packet which is temporarily on the
	 * control endpoपूर्णांक, respond with an ABORT.
	 */
	अगर (ep == sctp_sk(net->sctp.ctl_sock)->ep) अणु
		SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* Make sure that the COOKIE_ECHO chunk has a valid length.
	 * In this हाल, we check that we have enough क्रम at least a
	 * chunk header.  More detailed verअगरication is करोne
	 * in sctp_unpack_cookie().
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* If the endpoपूर्णांक is not listening or अगर the number of associations
	 * on the TCP-style socket exceed the max backlog, respond with an
	 * ABORT.
	 */
	sk = ep->base.sk;
	अगर (!sctp_sstate(sk, LISTENING) ||
	    (sctp_style(sk, TCP) && sk_acceptq_is_full(sk)))
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);

	/* "Decode" the chunk.  We have no optional parameters so we
	 * are in good shape.
	 */
	chunk->subh.cookie_hdr =
		(काष्ठा sctp_चिन्हित_cookie *)chunk->skb->data;
	अगर (!pskb_pull(chunk->skb, ntohs(chunk->chunk_hdr->length) -
					 माप(काष्ठा sctp_chunkhdr)))
		जाओ nomem;

	/* 5.1 D) Upon reception of the COOKIE ECHO chunk, Endpoपूर्णांक
	 * "Z" will reply with a COOKIE ACK chunk after building a TCB
	 * and moving to the ESTABLISHED state.
	 */
	new_asoc = sctp_unpack_cookie(ep, asoc, chunk, GFP_ATOMIC, &error,
				      &err_chk_p);

	/* FIXME:
	 * If the re-build failed, what is the proper error path
	 * from here?
	 *
	 * [We should पात the association. --piggy]
	 */
	अगर (!new_asoc) अणु
		/* FIXME: Several errors are possible.  A bad cookie should
		 * be silently discarded, but think about logging it too.
		 */
		चयन (error) अणु
		हाल -SCTP_IERROR_NOMEM:
			जाओ nomem;

		हाल -SCTP_IERROR_STALE_COOKIE:
			sctp_send_stale_cookie_err(net, ep, asoc, chunk, commands,
						   err_chk_p);
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

		हाल -SCTP_IERROR_BAD_SIG:
		शेष:
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
		पूर्ण
	पूर्ण


	/* Delay state machine commands until later.
	 *
	 * Re-build the bind address क्रम the association is करोne in
	 * the sctp_unpack_cookie() alपढ़ोy.
	 */
	/* This is a bअक्रम-new association, so these are not yet side
	 * effects--it is safe to run them here.
	 */
	peer_init = &chunk->subh.cookie_hdr->c.peer_init[0];

	अगर (!sctp_process_init(new_asoc, chunk,
			       &chunk->subh.cookie_hdr->c.peer_addr,
			       peer_init, GFP_ATOMIC))
		जाओ nomem_init;

	/* SCTP-AUTH:  Now that we've populate required fields in
	 * sctp_process_init, set up the assocaition shared keys as
	 * necessary so that we can potentially authenticate the ACK
	 */
	error = sctp_auth_asoc_init_active_key(new_asoc, GFP_ATOMIC);
	अगर (error)
		जाओ nomem_init;

	अगर (!sctp_auth_chunk_verअगरy(net, chunk, new_asoc)) अणु
		sctp_association_मुक्त(new_asoc);
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	repl = sctp_make_cookie_ack(new_asoc, chunk);
	अगर (!repl)
		जाओ nomem_init;

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * D) IMPLEMENTATION NOTE: An implementation may choose to
	 * send the Communication Up notअगरication to the SCTP user
	 * upon reception of a valid COOKIE ECHO chunk.
	 */
	ev = sctp_ulpevent_make_assoc_change(new_asoc, 0, SCTP_COMM_UP, 0,
					     new_asoc->c.sinit_num_ostreams,
					     new_asoc->c.sinit_max_instreams,
					     शून्य, GFP_ATOMIC);
	अगर (!ev)
		जाओ nomem_ev;

	/* Sockets API Draft Section 5.3.1.6
	 * When a peer sends a Adaptation Layer Indication parameter , SCTP
	 * delivers this notअगरication to inक्रमm the application that of the
	 * peers requested adaptation layer.
	 */
	अगर (new_asoc->peer.adaptation_ind) अणु
		ai_ev = sctp_ulpevent_make_adaptation_indication(new_asoc,
							    GFP_ATOMIC);
		अगर (!ai_ev)
			जाओ nomem_aiev;
	पूर्ण

	अगर (!new_asoc->peer.auth_capable) अणु
		auth_ev = sctp_ulpevent_make_authkey(new_asoc, 0,
						     SCTP_AUTH_NO_AUTH,
						     GFP_ATOMIC);
		अगर (!auth_ev)
			जाओ nomem_authev;
	पूर्ण

	/* Add all the state machine commands now since we've created
	 * everything.  This way we करोn't पूर्णांकroduce memory corruptions
	 * during side-effect processing and correclty count established
	 * associations.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_ASOC, SCTP_ASOC(new_asoc));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_ESTABLISHED));
	SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
	SCTP_INC_STATS(net, SCTP_MIB_PASSIVEESTABS);
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START, SCTP_शून्य());

	अगर (new_asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* This will send the COOKIE ACK */
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	/* Queue the ASSOC_CHANGE event */
	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));

	/* Send up the Adaptation Layer Indication event */
	अगर (ai_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ai_ev));

	अगर (auth_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(auth_ev));

	वापस SCTP_DISPOSITION_CONSUME;

nomem_authev:
	sctp_ulpevent_मुक्त(ai_ev);
nomem_aiev:
	sctp_ulpevent_मुक्त(ev);
nomem_ev:
	sctp_chunk_मुक्त(repl);
nomem_init:
	sctp_association_मुक्त(new_asoc);
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Respond to a normal COOKIE ACK chunk.
 * We are the side that is asking क्रम an association.
 *
 * RFC 2960 5.1 Normal Establishment of an Association
 *
 * E) Upon reception of the COOKIE ACK, endpoपूर्णांक "A" will move from the
 *    COOKIE-ECHOED state to the ESTABLISHED state, stopping the T1-cookie
 *    समयr. It may also notअगरy its ULP about the successful
 *    establishment of the association with a Communication Up
 *    notअगरication (see Section 10).
 *
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_1E_ca(काष्ठा net *net,
					 स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					 स्थिर काष्ठा sctp_association *asoc,
					 स्थिर जोड़ sctp_subtype type,
					 व्योम *arg,
					 काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_ulpevent *ev;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Verअगरy that the chunk length क्रम the COOKIE-ACK is OK.
	 * If we करोn't करो this, any bundled chunks may be junked.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Reset init error count upon receipt of COOKIE-ACK,
	 * to aव्योम problems with the managemement of this
	 * counter in stale cookie situations when a transition back
	 * from the COOKIE-ECHOED state to the COOKIE-WAIT
	 * state is perक्रमmed.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_COUNTER_RESET, SCTP_शून्य());

	/* Set peer label क्रम connection. */
	security_inet_conn_established(ep->base.sk, chunk->skb);

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * E) Upon reception of the COOKIE ACK, endpoपूर्णांक "A" will move
	 * from the COOKIE-ECHOED state to the ESTABLISHED state,
	 * stopping the T1-cookie समयr.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_ESTABLISHED));
	SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
	SCTP_INC_STATS(net, SCTP_MIB_ACTIVEESTABS);
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START, SCTP_शून्य());
	अगर (asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* It may also notअगरy its ULP about the successful
	 * establishment of the association with a Communication Up
	 * notअगरication (see Section 10).
	 */
	ev = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_COMM_UP,
					     0, asoc->c.sinit_num_ostreams,
					     asoc->c.sinit_max_instreams,
					     शून्य, GFP_ATOMIC);

	अगर (!ev)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));

	/* Sockets API Draft Section 5.3.1.6
	 * When a peer sends a Adaptation Layer Indication parameter , SCTP
	 * delivers this notअगरication to inक्रमm the application that of the
	 * peers requested adaptation layer.
	 */
	अगर (asoc->peer.adaptation_ind) अणु
		ev = sctp_ulpevent_make_adaptation_indication(asoc, GFP_ATOMIC);
		अगर (!ev)
			जाओ nomem;

		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));
	पूर्ण

	अगर (!asoc->peer.auth_capable) अणु
		ev = sctp_ulpevent_make_authkey(asoc, 0, SCTP_AUTH_NO_AUTH,
						GFP_ATOMIC);
		अगर (!ev)
			जाओ nomem;
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/* Generate and senकरोut a heartbeat packet.  */
अटल क्रमागत sctp_disposition sctp_sf_heartbeat(
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_transport *transport = (काष्ठा sctp_transport *) arg;
	काष्ठा sctp_chunk *reply;

	/* Send a heartbeat to our peer.  */
	reply = sctp_make_heartbeat(asoc, transport);
	अगर (!reply)
		वापस SCTP_DISPOSITION_NOMEM;

	/* Set rto_pending indicating that an RTT measurement
	 * is started with this heartbeat chunk.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_RTO_PENDING,
			SCTP_TRANSPORT(transport));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* Generate a HEARTBEAT packet on the given transport.  */
क्रमागत sctp_disposition sctp_sf_sendbeat_8_3(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_transport *transport = (काष्ठा sctp_transport *) arg;

	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		/* CMD_ASSOC_FAILED calls CMD_DELETE_TCB. */
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	/* Section 3.3.5.
	 * The Sender-specअगरic Heartbeat Info field should normally include
	 * inक्रमmation about the sender's current समय when this HEARTBEAT
	 * chunk is sent and the destination transport address to which this
	 * HEARTBEAT is sent (see Section 8.3).
	 */

	अगर (transport->param_flags & SPP_HB_ENABLE) अणु
		अगर (SCTP_DISPOSITION_NOMEM ==
				sctp_sf_heartbeat(ep, asoc, type, arg,
						  commands))
			वापस SCTP_DISPOSITION_NOMEM;

		/* Set transport error counter and association error counter
		 * when sending heartbeat.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_HB_SENT,
				SCTP_TRANSPORT(transport));
	पूर्ण
	sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_IDLE,
			SCTP_TRANSPORT(transport));
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMER_UPDATE,
			SCTP_TRANSPORT(transport));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* resend asoc strreset_chunk.  */
क्रमागत sctp_disposition sctp_sf_send_reconf(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_transport *transport = arg;

	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		/* CMD_ASSOC_FAILED calls CMD_DELETE_TCB. */
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	sctp_chunk_hold(asoc->strreset_chunk);
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
			SCTP_CHUNK(asoc->strreset_chunk));
	sctp_add_cmd_sf(commands, SCTP_CMD_STRIKE, SCTP_TRANSPORT(transport));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Process an heartbeat request.
 *
 * Section: 8.3 Path Heartbeat
 * The receiver of the HEARTBEAT should immediately respond with a
 * HEARTBEAT ACK that contains the Heartbeat Inक्रमmation field copied
 * from the received HEARTBEAT chunk.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 * When receiving an SCTP packet, the endpoपूर्णांक MUST ensure that the
 * value in the Verअगरication Tag field of the received SCTP packet
 * matches its own Tag. If the received Verअगरication Tag value करोes not
 * match the receiver's own tag value, the receiver shall silently
 * discard the packet and shall not process it any further except क्रम
 * those हालs listed in Section 8.5.1 below.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_beat_8_3(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर जोड़ sctp_subtype type,
				       व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_paramhdr *param_hdr;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *reply;
	माप_प्रकार paylen = 0;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the HEARTBEAT chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk,
				     माप(काष्ठा sctp_heartbeat_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* 8.3 The receiver of the HEARTBEAT should immediately
	 * respond with a HEARTBEAT ACK that contains the Heartbeat
	 * Inक्रमmation field copied from the received HEARTBEAT chunk.
	 */
	chunk->subh.hb_hdr = (काष्ठा sctp_heartbeathdr *)chunk->skb->data;
	param_hdr = (काष्ठा sctp_paramhdr *)chunk->subh.hb_hdr;
	paylen = ntohs(chunk->chunk_hdr->length) - माप(काष्ठा sctp_chunkhdr);

	अगर (ntohs(param_hdr->length) > paylen)
		वापस sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
						  param_hdr, commands);

	अगर (!pskb_pull(chunk->skb, paylen))
		जाओ nomem;

	reply = sctp_make_heartbeat_ack(asoc, chunk, param_hdr, paylen);
	अगर (!reply)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));
	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Process the वापसing HEARTBEAT ACK.
 *
 * Section: 8.3 Path Heartbeat
 * Upon the receipt of the HEARTBEAT ACK, the sender of the HEARTBEAT
 * should clear the error counter of the destination transport
 * address to which the HEARTBEAT was sent, and mark the destination
 * transport address as active अगर it is not so marked. The endpoपूर्णांक may
 * optionally report to the upper layer when an inactive destination
 * address is marked as active due to the reception of the latest
 * HEARTBEAT ACK. The receiver of the HEARTBEAT ACK must also
 * clear the association overall error count as well (as defined
 * in section 8.1).
 *
 * The receiver of the HEARTBEAT ACK should also perक्रमm an RTT
 * measurement क्रम that destination transport address using the समय
 * value carried in the HEARTBEAT ACK chunk.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_backbeat_8_3(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_sender_hb_info *hbinfo;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_transport *link;
	अचिन्हित दीर्घ max_पूर्णांकerval;
	जोड़ sctp_addr from_addr;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the HEARTBEAT-ACK chunk has a valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr) +
					    माप(*hbinfo)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	hbinfo = (काष्ठा sctp_sender_hb_info *)chunk->skb->data;
	/* Make sure that the length of the parameter is what we expect */
	अगर (ntohs(hbinfo->param_hdr.length) != माप(*hbinfo))
		वापस SCTP_DISPOSITION_DISCARD;

	from_addr = hbinfo->daddr;
	link = sctp_assoc_lookup_paddr(asoc, &from_addr);

	/* This should never happen, but lets log it अगर so.  */
	अगर (unlikely(!link)) अणु
		अगर (from_addr.sa.sa_family == AF_INET6) अणु
			net_warn_ratelimited("%s association %p could not find address %pI6\n",
					     __func__,
					     asoc,
					     &from_addr.v6.sin6_addr);
		पूर्ण अन्यथा अणु
			net_warn_ratelimited("%s association %p could not find address %pI4\n",
					     __func__,
					     asoc,
					     &from_addr.v4.sin_addr.s_addr);
		पूर्ण
		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* Validate the 64-bit अक्रमom nonce. */
	अगर (hbinfo->hb_nonce != link->hb_nonce)
		वापस SCTP_DISPOSITION_DISCARD;

	max_पूर्णांकerval = link->hbपूर्णांकerval + link->rto;

	/* Check अगर the बारtamp looks valid.  */
	अगर (समय_after(hbinfo->sent_at, jअगरfies) ||
	    समय_after(jअगरfies, hbinfo->sent_at + max_पूर्णांकerval)) अणु
		pr_debug("%s: HEARTBEAT ACK with invalid timestamp received "
			 "for transport:%p\n", __func__, link);

		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* 8.3 Upon the receipt of the HEARTBEAT ACK, the sender of
	 * the HEARTBEAT should clear the error counter of the
	 * destination transport address to which the HEARTBEAT was
	 * sent and mark the destination transport address as active अगर
	 * it is not so marked.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_ON, SCTP_TRANSPORT(link));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* Helper function to send out an पात क्रम the restart
 * condition.
 */
अटल पूर्णांक sctp_sf_send_restart_पात(काष्ठा net *net, जोड़ sctp_addr *ssa,
				      काष्ठा sctp_chunk *init,
				      काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_af *af = sctp_get_af_specअगरic(ssa->v4.sin_family);
	जोड़ sctp_addr_param *addrparm;
	काष्ठा sctp_errhdr *errhdr;
	अक्षर buffer[माप(*errhdr) + माप(*addrparm)];
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sctp_packet *pkt;
	पूर्णांक len;

	/* Build the error on the stack.   We are way to दो_स्मृति crazy
	 * throughout the code today.
	 */
	errhdr = (काष्ठा sctp_errhdr *)buffer;
	addrparm = (जोड़ sctp_addr_param *)errhdr->variable;

	/* Copy पूर्णांकo a parm क्रमmat. */
	len = af->to_addr_param(ssa, addrparm);
	len += माप(*errhdr);

	errhdr->cause = SCTP_ERROR_RESTART;
	errhdr->length = htons(len);

	/* Assign to the control socket. */
	ep = sctp_sk(net->sctp.ctl_sock)->ep;

	/* Association is शून्य since this may be a restart attack and we
	 * want to send back the attacker's vtag.
	 */
	pkt = sctp_पात_pkt_new(net, ep, शून्य, init, errhdr, len);

	अगर (!pkt)
		जाओ out;
	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT, SCTP_PACKET(pkt));

	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	/* Discard the rest of the inbound packet. */
	sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_शून्य());

out:
	/* Even अगर there is no memory, treat as a failure so
	 * the packet will get dropped.
	 */
	वापस 0;
पूर्ण

अटल bool list_has_sctp_addr(स्थिर काष्ठा list_head *list,
			       जोड़ sctp_addr *ipaddr)
अणु
	काष्ठा sctp_transport *addr;

	list_क्रम_each_entry(addr, list, transports) अणु
		अगर (sctp_cmp_addr_exact(ipaddr, &addr->ipaddr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
/* A restart is occurring, check to make sure no new addresses
 * are being added as we may be under a takeover attack.
 */
अटल पूर्णांक sctp_sf_check_restart_addrs(स्थिर काष्ठा sctp_association *new_asoc,
				       स्थिर काष्ठा sctp_association *asoc,
				       काष्ठा sctp_chunk *init,
				       काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा net *net = new_asoc->base.net;
	काष्ठा sctp_transport *new_addr;
	पूर्णांक ret = 1;

	/* Implementor's Guide - Section 5.2.2
	 * ...
	 * Beक्रमe responding the endpoपूर्णांक MUST check to see अगर the
	 * unexpected INIT adds new addresses to the association. If new
	 * addresses are added to the association, the endpoपूर्णांक MUST respond
	 * with an ABORT..
	 */

	/* Search through all current addresses and make sure
	 * we aren't adding any new ones.
	 */
	list_क्रम_each_entry(new_addr, &new_asoc->peer.transport_addr_list,
			    transports) अणु
		अगर (!list_has_sctp_addr(&asoc->peer.transport_addr_list,
					&new_addr->ipaddr)) अणु
			sctp_sf_send_restart_पात(net, &new_addr->ipaddr, init,
						   commands);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Return success अगर all addresses were found. */
	वापस ret;
पूर्ण

/* Populate the verअगरication/tie tags based on overlapping INIT
 * scenario.
 *
 * Note: Do not use in CLOSED or SHUTDOWN-ACK-SENT state.
 */
अटल व्योम sctp_tietags_populate(काष्ठा sctp_association *new_asoc,
				  स्थिर काष्ठा sctp_association *asoc)
अणु
	चयन (asoc->state) अणु

	/* 5.2.1 INIT received in COOKIE-WAIT or COOKIE-ECHOED State */

	हाल SCTP_STATE_COOKIE_WAIT:
		new_asoc->c.my_vtag     = asoc->c.my_vtag;
		new_asoc->c.my_ttag     = asoc->c.my_vtag;
		new_asoc->c.peer_ttag   = 0;
		अवरोध;

	हाल SCTP_STATE_COOKIE_ECHOED:
		new_asoc->c.my_vtag     = asoc->c.my_vtag;
		new_asoc->c.my_ttag     = asoc->c.my_vtag;
		new_asoc->c.peer_ttag   = asoc->c.peer_vtag;
		अवरोध;

	/* 5.2.2 Unexpected INIT in States Other than CLOSED, COOKIE-ECHOED,
	 * COOKIE-WAIT and SHUTDOWN-ACK-SENT
	 */
	शेष:
		new_asoc->c.my_ttag   = asoc->c.my_vtag;
		new_asoc->c.peer_ttag = asoc->c.peer_vtag;
		अवरोध;
	पूर्ण

	/* Other parameters क्रम the endpoपूर्णांक SHOULD be copied from the
	 * existing parameters of the association (e.g. number of
	 * outbound streams) पूर्णांकo the INIT ACK and cookie.
	 */
	new_asoc->rwnd                  = asoc->rwnd;
	new_asoc->c.sinit_num_ostreams  = asoc->c.sinit_num_ostreams;
	new_asoc->c.sinit_max_instreams = asoc->c.sinit_max_instreams;
	new_asoc->c.initial_tsn         = asoc->c.initial_tsn;
पूर्ण

/*
 * Compare vtag/tietag values to determine unexpected COOKIE-ECHO
 * handling action.
 *
 * RFC 2960 5.2.4 Handle a COOKIE ECHO when a TCB exists.
 *
 * Returns value representing action to be taken.   These action values
 * correspond to Action/Description values in RFC 2960, Table 2.
 */
अटल अक्षर sctp_tietags_compare(काष्ठा sctp_association *new_asoc,
				 स्थिर काष्ठा sctp_association *asoc)
अणु
	/* In this हाल, the peer may have restarted.  */
	अगर ((asoc->c.my_vtag != new_asoc->c.my_vtag) &&
	    (asoc->c.peer_vtag != new_asoc->c.peer_vtag) &&
	    (asoc->c.my_vtag == new_asoc->c.my_ttag) &&
	    (asoc->c.peer_vtag == new_asoc->c.peer_ttag))
		वापस 'A';

	/* Collision हाल B. */
	अगर ((asoc->c.my_vtag == new_asoc->c.my_vtag) &&
	    ((asoc->c.peer_vtag != new_asoc->c.peer_vtag) ||
	     (0 == asoc->c.peer_vtag))) अणु
		वापस 'B';
	पूर्ण

	/* Collision हाल D. */
	अगर ((asoc->c.my_vtag == new_asoc->c.my_vtag) &&
	    (asoc->c.peer_vtag == new_asoc->c.peer_vtag))
		वापस 'D';

	/* Collision हाल C. */
	अगर ((asoc->c.my_vtag != new_asoc->c.my_vtag) &&
	    (asoc->c.peer_vtag == new_asoc->c.peer_vtag) &&
	    (0 == new_asoc->c.my_ttag) &&
	    (0 == new_asoc->c.peer_ttag))
		वापस 'C';

	/* No match to any of the special हालs; discard this packet. */
	वापस 'E';
पूर्ण

/* Common helper routine क्रम both duplicate and simultaneous INIT
 * chunk handling.
 */
अटल क्रमागत sctp_disposition sctp_sf_करो_unexpected_init(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg, *repl, *err_chunk;
	काष्ठा sctp_unrecognized_param *unk_param;
	काष्ठा sctp_association *new_asoc;
	क्रमागत sctp_disposition retval;
	काष्ठा sctp_packet *packet;
	पूर्णांक len;

	/* Update socket peer label अगर first association. */
	अगर (security_sctp_assoc_request((काष्ठा sctp_endpoपूर्णांक *)ep,
					chunk->skb))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* 6.10 Bundling
	 * An endpoपूर्णांक MUST NOT bundle INIT, INIT ACK or
	 * SHUTDOWN COMPLETE with any other chunks.
	 *
	 * IG Section 2.11.2
	 * Furthermore, we require that the receiver of an INIT chunk MUST
	 * enक्रमce these rules by silently discarding an arriving packet
	 * with an INIT chunk that is bundled with other chunks.
	 */
	अगर (!chunk->singleton)
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* 3.1 A packet containing an INIT chunk MUST have a zero Verअगरication
	 * Tag.
	 */
	अगर (chunk->sctp_hdr->vtag != 0)
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);

	/* Make sure that the INIT chunk has a valid length.
	 * In this हाल, we generate a protocol violation since we have
	 * an association established.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_init_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	अगर (SCTP_INPUT_CB(chunk->skb)->encap_port != chunk->transport->encap_port)
		वापस sctp_sf_new_encap_port(net, ep, asoc, type, arg, commands);

	/* Grab the INIT header.  */
	chunk->subh.init_hdr = (काष्ठा sctp_inithdr *)chunk->skb->data;

	/* Tag the variable length parameters.  */
	chunk->param_hdr.v = skb_pull(chunk->skb, माप(काष्ठा sctp_inithdr));

	/* Verअगरy the INIT chunk beक्रमe processing it. */
	err_chunk = शून्य;
	अगर (!sctp_verअगरy_init(net, ep, asoc, chunk->chunk_hdr->type,
			      (काष्ठा sctp_init_chunk *)chunk->chunk_hdr, chunk,
			      &err_chunk)) अणु
		/* This chunk contains fatal error. It is to be discarded.
		 * Send an ABORT, with causes अगर there is any.
		 */
		अगर (err_chunk) अणु
			packet = sctp_पात_pkt_new(net, ep, asoc, arg,
					(__u8 *)(err_chunk->chunk_hdr) +
					माप(काष्ठा sctp_chunkhdr),
					ntohs(err_chunk->chunk_hdr->length) -
					माप(काष्ठा sctp_chunkhdr));

			अगर (packet) अणु
				sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
						SCTP_PACKET(packet));
				SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
				retval = SCTP_DISPOSITION_CONSUME;
			पूर्ण अन्यथा अणु
				retval = SCTP_DISPOSITION_NOMEM;
			पूर्ण
			जाओ cleanup;
		पूर्ण अन्यथा अणु
			वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg,
						    commands);
		पूर्ण
	पूर्ण

	/*
	 * Other parameters क्रम the endpoपूर्णांक SHOULD be copied from the
	 * existing parameters of the association (e.g. number of
	 * outbound streams) पूर्णांकo the INIT ACK and cookie.
	 * FIXME:  We are copying parameters from the endpoपूर्णांक not the
	 * association.
	 */
	new_asoc = sctp_make_temp_asoc(ep, chunk, GFP_ATOMIC);
	अगर (!new_asoc)
		जाओ nomem;

	अगर (sctp_assoc_set_bind_addr_from_ep(new_asoc,
				sctp_scope(sctp_source(chunk)), GFP_ATOMIC) < 0)
		जाओ nomem;

	/* In the outbound INIT ACK the endpoपूर्णांक MUST copy its current
	 * Verअगरication Tag and Peers Verअगरication tag पूर्णांकo a reserved
	 * place (local tie-tag and per tie-tag) within the state cookie.
	 */
	अगर (!sctp_process_init(new_asoc, chunk, sctp_source(chunk),
			       (काष्ठा sctp_init_chunk *)chunk->chunk_hdr,
			       GFP_ATOMIC))
		जाओ nomem;

	/* Make sure no new addresses are being added during the
	 * restart.   Do not करो this check क्रम COOKIE-WAIT state,
	 * since there are no peer addresses to check against.
	 * Upon वापस an ABORT will have been sent अगर needed.
	 */
	अगर (!sctp_state(asoc, COOKIE_WAIT)) अणु
		अगर (!sctp_sf_check_restart_addrs(new_asoc, asoc, chunk,
						 commands)) अणु
			retval = SCTP_DISPOSITION_CONSUME;
			जाओ nomem_retval;
		पूर्ण
	पूर्ण

	sctp_tietags_populate(new_asoc, asoc);

	/* B) "Z" shall respond immediately with an INIT ACK chunk.  */

	/* If there are errors need to be reported क्रम unknown parameters,
	 * make sure to reserve enough room in the INIT ACK क्रम them.
	 */
	len = 0;
	अगर (err_chunk) अणु
		len = ntohs(err_chunk->chunk_hdr->length) -
		      माप(काष्ठा sctp_chunkhdr);
	पूर्ण

	repl = sctp_make_init_ack(new_asoc, chunk, GFP_ATOMIC, len);
	अगर (!repl)
		जाओ nomem;

	/* If there are errors need to be reported क्रम unknown parameters,
	 * include them in the outgoing INIT ACK as "Unrecognized parameter"
	 * parameter.
	 */
	अगर (err_chunk) अणु
		/* Get the "Unrecognized parameter" parameter(s) out of the
		 * ERROR chunk generated by sctp_verअगरy_init(). Since the
		 * error cause code क्रम "unknown parameter" and the
		 * "Unrecognized parameter" type is the same, we can
		 * स्थिरruct the parameters in INIT ACK by copying the
		 * ERROR causes over.
		 */
		unk_param = (काष्ठा sctp_unrecognized_param *)
			    ((__u8 *)(err_chunk->chunk_hdr) +
			    माप(काष्ठा sctp_chunkhdr));
		/* Replace the cause code with the "Unrecognized parameter"
		 * parameter type.
		 */
		sctp_addto_chunk(repl, len, unk_param);
	पूर्ण

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_ASOC, SCTP_ASOC(new_asoc));
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	/*
	 * Note: After sending out INIT ACK with the State Cookie parameter,
	 * "Z" MUST NOT allocate any resources क्रम this new association.
	 * Otherwise, "Z" will be vulnerable to resource attacks.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());
	retval = SCTP_DISPOSITION_CONSUME;

	वापस retval;

nomem:
	retval = SCTP_DISPOSITION_NOMEM;
nomem_retval:
	अगर (new_asoc)
		sctp_association_मुक्त(new_asoc);
cleanup:
	अगर (err_chunk)
		sctp_chunk_मुक्त(err_chunk);
	वापस retval;
पूर्ण

/*
 * Handle simultaneous INIT.
 * This means we started an INIT and then we got an INIT request from
 * our peer.
 *
 * Section: 5.2.1 INIT received in COOKIE-WAIT or COOKIE-ECHOED State (Item B)
 * This usually indicates an initialization collision, i.e., each
 * endpoपूर्णांक is attempting, at about the same समय, to establish an
 * association with the other endpoपूर्णांक.
 *
 * Upon receipt of an INIT in the COOKIE-WAIT or COOKIE-ECHOED state, an
 * endpoपूर्णांक MUST respond with an INIT ACK using the same parameters it
 * sent in its original INIT chunk (including its Verअगरication Tag,
 * unchanged). These original parameters are combined with those from the
 * newly received INIT chunk. The endpoपूर्णांक shall also generate a State
 * Cookie with the INIT ACK. The endpoपूर्णांक uses the parameters sent in its
 * INIT to calculate the State Cookie.
 *
 * After that, the endpoपूर्णांक MUST NOT change its state, the T1-init
 * समयr shall be left running and the corresponding TCB MUST NOT be
 * destroyed. The normal procedures क्रम handling State Cookies when
 * a TCB exists will resolve the duplicate INITs to a single association.
 *
 * For an endpoपूर्णांक that is in the COOKIE-ECHOED state it MUST populate
 * its Tie-Tags with the Tag inक्रमmation of itself and its peer (see
 * section 5.2.2 क्रम a description of the Tie-Tags).
 *
 * Verअगरication Tag: Not explicit, but an INIT can not have a valid
 * verअगरication tag, so we skip the check.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_2_1_siminit(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* Call helper to करो the real work क्रम both simultaneous and
	 * duplicate INIT chunk handling.
	 */
	वापस sctp_sf_करो_unexpected_init(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Handle duplicated INIT messages.  These are usually delayed
 * restransmissions.
 *
 * Section: 5.2.2 Unexpected INIT in States Other than CLOSED,
 * COOKIE-ECHOED and COOKIE-WAIT
 *
 * Unless otherwise stated, upon reception of an unexpected INIT क्रम
 * this association, the endpoपूर्णांक shall generate an INIT ACK with a
 * State Cookie.  In the outbound INIT ACK the endpoपूर्णांक MUST copy its
 * current Verअगरication Tag and peer's Verअगरication Tag पूर्णांकo a reserved
 * place within the state cookie.  We shall refer to these locations as
 * the Peer's-Tie-Tag and the Local-Tie-Tag.  The outbound SCTP packet
 * containing this INIT ACK MUST carry a Verअगरication Tag value equal to
 * the Initiation Tag found in the unexpected INIT.  And the INIT ACK
 * MUST contain a new Initiation Tag (अक्रमomly generated see Section
 * 5.3.1).  Other parameters क्रम the endpoपूर्णांक SHOULD be copied from the
 * existing parameters of the association (e.g. number of outbound
 * streams) पूर्णांकo the INIT ACK and cookie.
 *
 * After sending out the INIT ACK, the endpoपूर्णांक shall take no further
 * actions, i.e., the existing association, including its current state,
 * and the corresponding TCB MUST NOT be changed.
 *
 * Note: Only when a TCB exists and the association is not in a COOKIE-
 * WAIT state are the Tie-Tags populated.  For a normal association INIT
 * (i.e. the endpoपूर्णांक is in a COOKIE-WAIT state), the Tie-Tags MUST be
 * set to 0 (indicating that no previous TCB existed).  The INIT ACK and
 * State Cookie are populated as specअगरied in section 5.2.1.
 *
 * Verअगरication Tag: Not specअगरied, but an INIT has no way of knowing
 * what the verअगरication tag could be, so we ignore it.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_2_2_dupinit(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* Call helper to करो the real work क्रम both simultaneous and
	 * duplicate INIT chunk handling.
	 */
	वापस sctp_sf_करो_unexpected_init(net, ep, asoc, type, arg, commands);
पूर्ण


/*
 * Unexpected INIT-ACK handler.
 *
 * Section 5.2.3
 * If an INIT ACK received by an endpoपूर्णांक in any state other than the
 * COOKIE-WAIT state, the endpoपूर्णांक should discard the INIT ACK chunk.
 * An unexpected INIT ACK usually indicates the processing of an old or
 * duplicated INIT chunk.
*/
क्रमागत sctp_disposition sctp_sf_करो_5_2_3_initack(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* Per the above section, we'll discard the chunk अगर we have an
	 * endpoपूर्णांक.  If this is an OOTB INIT-ACK, treat it as such.
	 */
	अगर (ep == sctp_sk(net->sctp.ctl_sock)->ep)
		वापस sctp_sf_ootb(net, ep, asoc, type, arg, commands);
	अन्यथा
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg, commands);
पूर्ण

अटल पूर्णांक sctp_sf_करो_assoc_update(काष्ठा sctp_association *asoc,
				   काष्ठा sctp_association *new,
				   काष्ठा sctp_cmd_seq *cmds)
अणु
	काष्ठा net *net = asoc->base.net;
	काष्ठा sctp_chunk *पात;

	अगर (!sctp_assoc_update(asoc, new))
		वापस 0;

	पात = sctp_make_पात(asoc, शून्य, माप(काष्ठा sctp_errhdr));
	अगर (पात) अणु
		sctp_init_cause(पात, SCTP_ERROR_RSRC_LOW, 0);
		sctp_add_cmd_sf(cmds, SCTP_CMD_REPLY, SCTP_CHUNK(पात));
	पूर्ण
	sctp_add_cmd_sf(cmds, SCTP_CMD_SET_SK_ERR, SCTP_ERROR(ECONNABORTED));
	sctp_add_cmd_sf(cmds, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_RSRC_LOW));
	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);

	वापस -ENOMEM;
पूर्ण

/* Unexpected COOKIE-ECHO handler क्रम peer restart (Table 2, action 'A')
 *
 * Section 5.2.4
 *  A)  In this हाल, the peer may have restarted.
 */
अटल क्रमागत sctp_disposition sctp_sf_करो_dupcook_a(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_cmd_seq *commands,
					काष्ठा sctp_association *new_asoc)
अणु
	काष्ठा sctp_init_chunk *peer_init;
	क्रमागत sctp_disposition disposition;
	काष्ठा sctp_ulpevent *ev;
	काष्ठा sctp_chunk *repl;
	काष्ठा sctp_chunk *err;

	/* new_asoc is a bअक्रम-new association, so these are not yet
	 * side effects--it is safe to run them here.
	 */
	peer_init = &chunk->subh.cookie_hdr->c.peer_init[0];

	अगर (!sctp_process_init(new_asoc, chunk, sctp_source(chunk), peer_init,
			       GFP_ATOMIC))
		जाओ nomem;

	अगर (sctp_auth_asoc_init_active_key(new_asoc, GFP_ATOMIC))
		जाओ nomem;

	अगर (!sctp_auth_chunk_verअगरy(net, chunk, new_asoc))
		वापस SCTP_DISPOSITION_DISCARD;

	/* Make sure no new addresses are being added during the
	 * restart.  Though this is a pretty complicated attack
	 * since you'd have to get inside the cookie.
	 */
	अगर (!sctp_sf_check_restart_addrs(new_asoc, asoc, chunk, commands))
		वापस SCTP_DISPOSITION_CONSUME;

	/* If the endpoपूर्णांक is in the SHUTDOWN-ACK-SENT state and recognizes
	 * the peer has restarted (Action A), it MUST NOT setup a new
	 * association but instead resend the SHUTDOWN ACK and send an ERROR
	 * chunk with a "Cookie Received while Shutting Down" error cause to
	 * its peer.
	*/
	अगर (sctp_state(asoc, SHUTDOWN_ACK_SENT)) अणु
		disposition = sctp_sf_करो_9_2_reshutack(net, ep, asoc,
				SCTP_ST_CHUNK(chunk->chunk_hdr->type),
				chunk, commands);
		अगर (SCTP_DISPOSITION_NOMEM == disposition)
			जाओ nomem;

		err = sctp_make_op_error(asoc, chunk,
					 SCTP_ERROR_COOKIE_IN_SHUTDOWN,
					 शून्य, 0, 0);
		अगर (err)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err));

		वापस SCTP_DISPOSITION_CONSUME;
	पूर्ण

	/* For now, stop pending T3-rtx and SACK समयrs, fail any unsent/unacked
	 * data. Consider the optional choice of resending of this data.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_T3_RTX_TIMERS_STOP, SCTP_शून्य());
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	sctp_add_cmd_sf(commands, SCTP_CMD_PURGE_OUTQUEUE, SCTP_शून्य());

	/* Stop pending T4-rto समयr, tearकरोwn ASCONF queue, ASCONF-ACK queue
	 * and ASCONF-ACK cache.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
	sctp_add_cmd_sf(commands, SCTP_CMD_PURGE_ASCONF_QUEUE, SCTP_शून्य());

	/* Update the content of current association. */
	अगर (sctp_sf_करो_assoc_update((काष्ठा sctp_association *)asoc, new_asoc, commands))
		जाओ nomem;

	repl = sctp_make_cookie_ack(asoc, chunk);
	अगर (!repl)
		जाओ nomem;

	/* Report association restart to upper layer. */
	ev = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_RESTART, 0,
					     asoc->c.sinit_num_ostreams,
					     asoc->c.sinit_max_instreams,
					     शून्य, GFP_ATOMIC);
	अगर (!ev)
		जाओ nomem_ev;

	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));
	अगर ((sctp_state(asoc, SHUTDOWN_PENDING) ||
	     sctp_state(asoc, SHUTDOWN_SENT)) &&
	    (sctp_sstate(asoc->base.sk, CLOSING) ||
	     sock_flag(asoc->base.sk, SOCK_DEAD))) अणु
		/* If the socket has been बंदd by user, करोn't
		 * transition to ESTABLISHED. Instead trigger SHUTDOWN
		 * bundled with COOKIE_ACK.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
		वापस sctp_sf_करो_9_2_start_shutकरोwn(net, ep, asoc,
						     SCTP_ST_CHUNK(0), repl,
						     commands);
	पूर्ण अन्यथा अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
				SCTP_STATE(SCTP_STATE_ESTABLISHED));
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
	पूर्ण
	वापस SCTP_DISPOSITION_CONSUME;

nomem_ev:
	sctp_chunk_मुक्त(repl);
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/* Unexpected COOKIE-ECHO handler क्रम setup collision (Table 2, action 'B')
 *
 * Section 5.2.4
 *   B) In this हाल, both sides may be attempting to start an association
 *      at about the same समय but the peer endpoपूर्णांक started its INIT
 *      after responding to the local endpoपूर्णांक's INIT
 */
/* This हाल represents an initialization collision.  */
अटल क्रमागत sctp_disposition sctp_sf_करो_dupcook_b(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_cmd_seq *commands,
					काष्ठा sctp_association *new_asoc)
अणु
	काष्ठा sctp_init_chunk *peer_init;
	काष्ठा sctp_chunk *repl;

	/* new_asoc is a bअक्रम-new association, so these are not yet
	 * side effects--it is safe to run them here.
	 */
	peer_init = &chunk->subh.cookie_hdr->c.peer_init[0];
	अगर (!sctp_process_init(new_asoc, chunk, sctp_source(chunk), peer_init,
			       GFP_ATOMIC))
		जाओ nomem;

	अगर (sctp_auth_asoc_init_active_key(new_asoc, GFP_ATOMIC))
		जाओ nomem;

	अगर (!sctp_auth_chunk_verअगरy(net, chunk, new_asoc))
		वापस SCTP_DISPOSITION_DISCARD;

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_ESTABLISHED));
	अगर (asoc->state < SCTP_STATE_ESTABLISHED)
		SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START, SCTP_शून्य());

	/* Update the content of current association.  */
	अगर (sctp_sf_करो_assoc_update((काष्ठा sctp_association *)asoc, new_asoc, commands))
		जाओ nomem;

	repl = sctp_make_cookie_ack(asoc, chunk);
	अगर (!repl)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * D) IMPLEMENTATION NOTE: An implementation may choose to
	 * send the Communication Up notअगरication to the SCTP user
	 * upon reception of a valid COOKIE ECHO chunk.
	 *
	 * Sadly, this needs to be implemented as a side-effect, because
	 * we are not guaranteed to have set the association id of the real
	 * association and so these notअगरications need to be delayed until
	 * the association id is allocated.
	 */

	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_CHANGE, SCTP_U8(SCTP_COMM_UP));

	/* Sockets API Draft Section 5.3.1.6
	 * When a peer sends a Adaptation Layer Indication parameter , SCTP
	 * delivers this notअगरication to inक्रमm the application that of the
	 * peers requested adaptation layer.
	 *
	 * This also needs to be करोne as a side effect क्रम the same reason as
	 * above.
	 */
	अगर (asoc->peer.adaptation_ind)
		sctp_add_cmd_sf(commands, SCTP_CMD_ADAPTATION_IND, SCTP_शून्य());

	अगर (!asoc->peer.auth_capable)
		sctp_add_cmd_sf(commands, SCTP_CMD_PEER_NO_AUTH, SCTP_शून्य());

	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/* Unexpected COOKIE-ECHO handler क्रम setup collision (Table 2, action 'C')
 *
 * Section 5.2.4
 *  C) In this हाल, the local endpoपूर्णांक's cookie has arrived late.
 *     Beक्रमe it arrived, the local endpoपूर्णांक sent an INIT and received an
 *     INIT-ACK and finally sent a COOKIE ECHO with the peer's same tag
 *     but a new tag of its own.
 */
/* This हाल represents an initialization collision.  */
अटल क्रमागत sctp_disposition sctp_sf_करो_dupcook_c(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_cmd_seq *commands,
					काष्ठा sctp_association *new_asoc)
अणु
	/* The cookie should be silently discarded.
	 * The endpoपूर्णांक SHOULD NOT change states and should leave
	 * any समयrs running.
	 */
	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/* Unexpected COOKIE-ECHO handler lost chunk (Table 2, action 'D')
 *
 * Section 5.2.4
 *
 * D) When both local and remote tags match the endpoपूर्णांक should always
 *    enter the ESTABLISHED state, अगर it has not alपढ़ोy करोne so.
 */
/* This हाल represents an initialization collision.  */
अटल क्रमागत sctp_disposition sctp_sf_करो_dupcook_d(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_cmd_seq *commands,
					काष्ठा sctp_association *new_asoc)
अणु
	काष्ठा sctp_ulpevent *ev = शून्य, *ai_ev = शून्य, *auth_ev = शून्य;
	काष्ठा sctp_chunk *repl;

	/* Clarअगरication from Implementor's Guide:
	 * D) When both local and remote tags match the endpoपूर्णांक should
	 * enter the ESTABLISHED state, अगर it is in the COOKIE-ECHOED state.
	 * It should stop any cookie समयr that may be running and send
	 * a COOKIE ACK.
	 */

	अगर (!sctp_auth_chunk_verअगरy(net, chunk, asoc))
		वापस SCTP_DISPOSITION_DISCARD;

	/* Don't accidentally move back पूर्णांकo established state. */
	अगर (asoc->state < SCTP_STATE_ESTABLISHED) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
		sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
				SCTP_STATE(SCTP_STATE_ESTABLISHED));
		SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
		sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START,
				SCTP_शून्य());

		/* RFC 2960 5.1 Normal Establishment of an Association
		 *
		 * D) IMPLEMENTATION NOTE: An implementation may choose
		 * to send the Communication Up notअगरication to the
		 * SCTP user upon reception of a valid COOKIE
		 * ECHO chunk.
		 */
		ev = sctp_ulpevent_make_assoc_change(asoc, 0,
					     SCTP_COMM_UP, 0,
					     asoc->c.sinit_num_ostreams,
					     asoc->c.sinit_max_instreams,
					     शून्य, GFP_ATOMIC);
		अगर (!ev)
			जाओ nomem;

		/* Sockets API Draft Section 5.3.1.6
		 * When a peer sends a Adaptation Layer Indication parameter,
		 * SCTP delivers this notअगरication to inक्रमm the application
		 * that of the peers requested adaptation layer.
		 */
		अगर (asoc->peer.adaptation_ind) अणु
			ai_ev = sctp_ulpevent_make_adaptation_indication(asoc,
								 GFP_ATOMIC);
			अगर (!ai_ev)
				जाओ nomem;

		पूर्ण

		अगर (!asoc->peer.auth_capable) अणु
			auth_ev = sctp_ulpevent_make_authkey(asoc, 0,
							     SCTP_AUTH_NO_AUTH,
							     GFP_ATOMIC);
			अगर (!auth_ev)
				जाओ nomem;
		पूर्ण
	पूर्ण

	repl = sctp_make_cookie_ack(asoc, chunk);
	अगर (!repl)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	अगर (ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));
	अगर (ai_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
					SCTP_ULPEVENT(ai_ev));
	अगर (auth_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(auth_ev));

	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	अगर (auth_ev)
		sctp_ulpevent_मुक्त(auth_ev);
	अगर (ai_ev)
		sctp_ulpevent_मुक्त(ai_ev);
	अगर (ev)
		sctp_ulpevent_मुक्त(ev);
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Handle a duplicate COOKIE-ECHO.  This usually means a cookie-carrying
 * chunk was retransmitted and then delayed in the network.
 *
 * Section: 5.2.4 Handle a COOKIE ECHO when a TCB exists
 *
 * Verअगरication Tag: None.  Do cookie validation.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_5_2_4_dupcook(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_association *new_asoc;
	काष्ठा sctp_chunk *chunk = arg;
	क्रमागत sctp_disposition retval;
	काष्ठा sctp_chunk *err_chk_p;
	पूर्णांक error = 0;
	अक्षर action;

	/* Make sure that the chunk has a valid length from the protocol
	 * perspective.  In this हाल check to make sure we have at least
	 * enough क्रम the chunk header.  Cookie length verअगरication is
	 * करोne later.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* "Decode" the chunk.  We have no optional parameters so we
	 * are in good shape.
	 */
	chunk->subh.cookie_hdr = (काष्ठा sctp_चिन्हित_cookie *)chunk->skb->data;
	अगर (!pskb_pull(chunk->skb, ntohs(chunk->chunk_hdr->length) -
					माप(काष्ठा sctp_chunkhdr)))
		जाओ nomem;

	/* In RFC 2960 5.2.4 3, अगर both Verअगरication Tags in the State Cookie
	 * of a duplicate COOKIE ECHO match the Verअगरication Tags of the
	 * current association, consider the State Cookie valid even अगर
	 * the lअगरespan is exceeded.
	 */
	new_asoc = sctp_unpack_cookie(ep, asoc, chunk, GFP_ATOMIC, &error,
				      &err_chk_p);

	/* FIXME:
	 * If the re-build failed, what is the proper error path
	 * from here?
	 *
	 * [We should पात the association. --piggy]
	 */
	अगर (!new_asoc) अणु
		/* FIXME: Several errors are possible.  A bad cookie should
		 * be silently discarded, but think about logging it too.
		 */
		चयन (error) अणु
		हाल -SCTP_IERROR_NOMEM:
			जाओ nomem;

		हाल -SCTP_IERROR_STALE_COOKIE:
			sctp_send_stale_cookie_err(net, ep, asoc, chunk, commands,
						   err_chk_p);
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
		हाल -SCTP_IERROR_BAD_SIG:
		शेष:
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
		पूर्ण
	पूर्ण

	/* Update socket peer label अगर first association. */
	अगर (security_sctp_assoc_request((काष्ठा sctp_endpoपूर्णांक *)ep,
					chunk->skb)) अणु
		sctp_association_मुक्त(new_asoc);
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* Set temp so that it won't be added पूर्णांकo hashtable */
	new_asoc->temp = 1;

	/* Compare the tie_tag in cookie with the verअगरication tag of
	 * current association.
	 */
	action = sctp_tietags_compare(new_asoc, asoc);

	चयन (action) अणु
	हाल 'A': /* Association restart. */
		retval = sctp_sf_करो_dupcook_a(net, ep, asoc, chunk, commands,
					      new_asoc);
		अवरोध;

	हाल 'B': /* Collision हाल B. */
		retval = sctp_sf_करो_dupcook_b(net, ep, asoc, chunk, commands,
					      new_asoc);
		अवरोध;

	हाल 'C': /* Collision हाल C. */
		retval = sctp_sf_करो_dupcook_c(net, ep, asoc, chunk, commands,
					      new_asoc);
		अवरोध;

	हाल 'D': /* Collision हाल D. */
		retval = sctp_sf_करो_dupcook_d(net, ep, asoc, chunk, commands,
					      new_asoc);
		अवरोध;

	शेष: /* Discard packet क्रम all others. */
		retval = sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
		अवरोध;
	पूर्ण

	/* Delete the temporary new association. */
	sctp_add_cmd_sf(commands, SCTP_CMD_SET_ASOC, SCTP_ASOC(new_asoc));
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());

	/* Restore association poपूर्णांकer to provide SCTP command पूर्णांकerpreter
	 * with a valid context in हाल it needs to manipulate
	 * the queues */
	sctp_add_cmd_sf(commands, SCTP_CMD_SET_ASOC,
			 SCTP_ASOC((काष्ठा sctp_association *)asoc));

	वापस retval;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Process an ABORT.  (SHUTDOWN-PENDING state)
 *
 * See sctp_sf_करो_9_1_पात().
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_pending_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	अगर (!sctp_vtag_verअगरy_either(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ABORT chunk has a valid length.
	 * Since this is an ABORT chunk, we have to discard it
	 * because of the following text:
	 * RFC 2960, Section 3.3.7
	 *    If an endpoपूर्णांक receives an ABORT with a क्रमmat error or क्रम an
	 *    association that करोesn't exist, it MUST silently discard it.
	 * Because the length is "invalid", we can't really discard just
	 * as we करो not know its true length.  So, to be safe, discard the
	 * packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_पात_chunk)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* ADD-IP: Special हाल क्रम ABORT chunks
	 * F4)  One special consideration is that ABORT Chunks arriving
	 * destined to the IP address being deleted MUST be
	 * ignored (see Section 5.3.1 क्रम further details).
	 */
	अगर (SCTP_ADDR_DEL ==
		    sctp_bind_addr_state(&asoc->base.bind_addr, &chunk->dest))
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg, commands);

	अगर (!sctp_err_chunk_valid(chunk))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	वापस __sctp_sf_करो_9_1_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Process an ABORT.  (SHUTDOWN-SENT state)
 *
 * See sctp_sf_करो_9_1_पात().
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_sent_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	अगर (!sctp_vtag_verअगरy_either(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ABORT chunk has a valid length.
	 * Since this is an ABORT chunk, we have to discard it
	 * because of the following text:
	 * RFC 2960, Section 3.3.7
	 *    If an endpoपूर्णांक receives an ABORT with a क्रमmat error or क्रम an
	 *    association that करोesn't exist, it MUST silently discard it.
	 * Because the length is "invalid", we can't really discard just
	 * as we करो not know its true length.  So, to be safe, discard the
	 * packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_पात_chunk)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* ADD-IP: Special हाल क्रम ABORT chunks
	 * F4)  One special consideration is that ABORT Chunks arriving
	 * destined to the IP address being deleted MUST be
	 * ignored (see Section 5.3.1 क्रम further details).
	 */
	अगर (SCTP_ADDR_DEL ==
		    sctp_bind_addr_state(&asoc->base.bind_addr, &chunk->dest))
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg, commands);

	अगर (!sctp_err_chunk_valid(chunk))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Stop the T2-shutकरोwn समयr. */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	/* Stop the T5-shutकरोwn guard समयr.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	वापस __sctp_sf_करो_9_1_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Process an ABORT.  (SHUTDOWN-ACK-SENT state)
 *
 * See sctp_sf_करो_9_1_पात().
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_ack_sent_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* The same T2 समयr, so we should be able to use
	 * common function with the SHUTDOWN-SENT state.
	 */
	वापस sctp_sf_shutकरोwn_sent_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Handle an Error received in COOKIE_ECHOED state.
 *
 * Only handle the error type of stale COOKIE Error, the other errors will
 * be ignored.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_cookie_echoed_err(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_errhdr *err;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ERROR chunk has a valid length.
	 * The parameter walking depends on this as well.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_operr_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Process the error here */
	/* FUTURE FIXME:  When PR-SCTP related and other optional
	 * parms are emitted, this will have to change to handle multiple
	 * errors.
	 */
	sctp_walk_errors(err, chunk->chunk_hdr) अणु
		अगर (SCTP_ERROR_STALE_COOKIE == err->cause)
			वापस sctp_sf_करो_5_2_6_stale(net, ep, asoc, type,
							arg, commands);
	पूर्ण

	/* It is possible to have malक्रमmed error causes, and that
	 * will cause us to end the walk early.  However, since
	 * we are discarding the packet, there should be no adverse
	 * affects.
	 */
	वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Handle a Stale COOKIE Error
 *
 * Section: 5.2.6 Handle Stale COOKIE Error
 * If the association is in the COOKIE-ECHOED state, the endpoपूर्णांक may elect
 * one of the following three alternatives.
 * ...
 * 3) Send a new INIT chunk to the endpoपूर्णांक, adding a Cookie
 *    Preservative parameter requesting an extension to the lअगरeसमय of
 *    the State Cookie. When calculating the समय extension, an
 *    implementation SHOULD use the RTT inक्रमmation measured based on the
 *    previous COOKIE ECHO / ERROR exchange, and should add no more
 *    than 1 second beyond the measured RTT, due to दीर्घ State Cookie
 *    lअगरeबार making the endpoपूर्णांक more subject to a replay attack.
 *
 * Verअगरication Tag:  Not explicit, but safe to ignore.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
अटल क्रमागत sctp_disposition sctp_sf_करो_5_2_6_stale(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	पूर्णांक attempts = asoc->init_err_counter + 1;
	काष्ठा sctp_chunk *chunk = arg, *reply;
	काष्ठा sctp_cookie_preserve_param bht;
	काष्ठा sctp_bind_addr *bp;
	काष्ठा sctp_errhdr *err;
	u32 stale;

	अगर (attempts > asoc->max_init_attempts) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
				SCTP_PERR(SCTP_ERROR_STALE_COOKIE));
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	err = (काष्ठा sctp_errhdr *)(chunk->skb->data);

	/* When calculating the समय extension, an implementation
	 * SHOULD use the RTT inक्रमmation measured based on the
	 * previous COOKIE ECHO / ERROR exchange, and should add no
	 * more than 1 second beyond the measured RTT, due to दीर्घ
	 * State Cookie lअगरeबार making the endpoपूर्णांक more subject to
	 * a replay attack.
	 * Measure of Staleness's unit is usec. (1/1000000 sec)
	 * Suggested Cookie Lअगरe-span Increment's unit is msec.
	 * (1/1000 sec)
	 * In general, अगर you use the suggested cookie lअगरe, the value
	 * found in the field of measure of staleness should be द्विगुनd
	 * to give ample समय to retransmit the new cookie and thus
	 * yield a higher probability of success on the reattempt.
	 */
	stale = ntohl(*(__be32 *)((u8 *)err + माप(*err)));
	stale = (stale * 2) / 1000;

	bht.param_hdr.type = SCTP_PARAM_COOKIE_PRESERVATIVE;
	bht.param_hdr.length = htons(माप(bht));
	bht.lअगरespan_increment = htonl(stale);

	/* Build that new INIT chunk.  */
	bp = (काष्ठा sctp_bind_addr *) &asoc->base.bind_addr;
	reply = sctp_make_init(asoc, bp, GFP_ATOMIC, माप(bht));
	अगर (!reply)
		जाओ nomem;

	sctp_addto_chunk(reply, माप(bht), &bht);

	/* Clear peer's init_tag cached in assoc as we are sending a new INIT */
	sctp_add_cmd_sf(commands, SCTP_CMD_CLEAR_INIT_TAG, SCTP_शून्य());

	/* Stop pending T3-rtx and heartbeat समयrs */
	sctp_add_cmd_sf(commands, SCTP_CMD_T3_RTX_TIMERS_STOP, SCTP_शून्य());
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_STOP, SCTP_शून्य());

	/* Delete non-primary peer ip addresses since we are transitioning
	 * back to the COOKIE-WAIT state
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_DEL_NON_PRIMARY, SCTP_शून्य());

	/* If we've sent any data bundled with COOKIE-ECHO we will need to
	 * resend
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_T1_RETRAN,
			SCTP_TRANSPORT(asoc->peer.primary_path));

	/* Cast away the स्थिर modअगरier, as we want to just
	 * rerun it through as a sideffect.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_COUNTER_INC, SCTP_शून्य());

	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_COOKIE_WAIT));
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Process an ABORT.
 *
 * Section: 9.1
 * After checking the Verअगरication Tag, the receiving endpoपूर्णांक shall
 * हटाओ the association from its record, and shall report the
 * termination to its upper layer.
 *
 * Verअगरication Tag: 8.5.1 Exceptions in Verअगरication Tag Rules
 * B) Rules क्रम packet carrying ABORT:
 *
 *  - The endpoपूर्णांक shall always fill in the Verअगरication Tag field of the
 *    outbound packet with the destination endpoपूर्णांक's tag value अगर it
 *    is known.
 *
 *  - If the ABORT is sent in response to an OOTB packet, the endpoपूर्णांक
 *    MUST follow the procedure described in Section 8.4.
 *
 *  - The receiver MUST accept the packet अगर the Verअगरication Tag
 *    matches either its own tag, OR the tag of its peer. Otherwise, the
 *    receiver MUST silently discard the packet and take no further
 *    action.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_1_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	अगर (!sctp_vtag_verअगरy_either(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ABORT chunk has a valid length.
	 * Since this is an ABORT chunk, we have to discard it
	 * because of the following text:
	 * RFC 2960, Section 3.3.7
	 *    If an endpoपूर्णांक receives an ABORT with a क्रमmat error or क्रम an
	 *    association that करोesn't exist, it MUST silently discard it.
	 * Because the length is "invalid", we can't really discard just
	 * as we करो not know its true length.  So, to be safe, discard the
	 * packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_पात_chunk)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* ADD-IP: Special हाल क्रम ABORT chunks
	 * F4)  One special consideration is that ABORT Chunks arriving
	 * destined to the IP address being deleted MUST be
	 * ignored (see Section 5.3.1 क्रम further details).
	 */
	अगर (SCTP_ADDR_DEL ==
		    sctp_bind_addr_state(&asoc->base.bind_addr, &chunk->dest))
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg, commands);

	अगर (!sctp_err_chunk_valid(chunk))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	वापस __sctp_sf_करो_9_1_पात(net, ep, asoc, type, arg, commands);
पूर्ण

अटल क्रमागत sctp_disposition __sctp_sf_करो_9_1_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	__be16 error = SCTP_ERROR_NO_ERROR;
	काष्ठा sctp_chunk *chunk = arg;
	अचिन्हित पूर्णांक len;

	/* See अगर we have an error cause code in the chunk.  */
	len = ntohs(chunk->chunk_hdr->length);
	अगर (len >= माप(काष्ठा sctp_chunkhdr) + माप(काष्ठा sctp_errhdr))
		error = ((काष्ठा sctp_errhdr *)chunk->skb->data)->cause;

	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR, SCTP_ERROR(ECONNRESET));
	/* ASSOC_FAILED will DELETE_TCB. */
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED, SCTP_PERR(error));
	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);

	वापस SCTP_DISPOSITION_ABORT;
पूर्ण

/*
 * Process an ABORT.  (COOKIE-WAIT state)
 *
 * See sctp_sf_करो_9_1_पात() above.
 */
क्रमागत sctp_disposition sctp_sf_cookie_रुको_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	__be16 error = SCTP_ERROR_NO_ERROR;
	काष्ठा sctp_chunk *chunk = arg;
	अचिन्हित पूर्णांक len;

	अगर (!sctp_vtag_verअगरy_either(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ABORT chunk has a valid length.
	 * Since this is an ABORT chunk, we have to discard it
	 * because of the following text:
	 * RFC 2960, Section 3.3.7
	 *    If an endpoपूर्णांक receives an ABORT with a क्रमmat error or क्रम an
	 *    association that करोesn't exist, it MUST silently discard it.
	 * Because the length is "invalid", we can't really discard just
	 * as we करो not know its true length.  So, to be safe, discard the
	 * packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_पात_chunk)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* See अगर we have an error cause code in the chunk.  */
	len = ntohs(chunk->chunk_hdr->length);
	अगर (len >= माप(काष्ठा sctp_chunkhdr) + माप(काष्ठा sctp_errhdr))
		error = ((काष्ठा sctp_errhdr *)chunk->skb->data)->cause;

	वापस sctp_stop_t1_and_पात(net, commands, error, ECONNREFUSED, asoc,
				      chunk->transport);
पूर्ण

/*
 * Process an incoming ICMP as an ABORT.  (COOKIE-WAIT state)
 */
क्रमागत sctp_disposition sctp_sf_cookie_रुको_icmp_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	वापस sctp_stop_t1_and_पात(net, commands, SCTP_ERROR_NO_ERROR,
				      ENOPROTOOPT, asoc,
				      (काष्ठा sctp_transport *)arg);
पूर्ण

/*
 * Process an ABORT.  (COOKIE-ECHOED state)
 */
क्रमागत sctp_disposition sctp_sf_cookie_echoed_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* There is a single T1 समयr, so we should be able to use
	 * common function with the COOKIE-WAIT state.
	 */
	वापस sctp_sf_cookie_रुको_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Stop T1 समयr and पात association with "INIT failed".
 *
 * This is common code called by several sctp_sf_*_पात() functions above.
 */
अटल क्रमागत sctp_disposition sctp_stop_t1_and_पात(
					काष्ठा net *net,
					काष्ठा sctp_cmd_seq *commands,
					__be16 error, पूर्णांक sk_err,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_transport *transport)
अणु
	pr_debug("%s: ABORT received (INIT)\n", __func__);

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));
	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR, SCTP_ERROR(sk_err));
	/* CMD_INIT_FAILED will DELETE_TCB. */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
			SCTP_PERR(error));

	वापस SCTP_DISPOSITION_ABORT;
पूर्ण

/*
 * sctp_sf_करो_9_2_shut
 *
 * Section: 9.2
 * Upon the reception of the SHUTDOWN, the peer endpoपूर्णांक shall
 *  - enter the SHUTDOWN-RECEIVED state,
 *
 *  - stop accepting new data from its SCTP user
 *
 *  - verअगरy, by checking the Cumulative TSN Ack field of the chunk,
 *    that all its outstanding DATA chunks have been received by the
 *    SHUTDOWN sender.
 *
 * Once an endpoपूर्णांक as reached the SHUTDOWN-RECEIVED state it MUST NOT
 * send a SHUTDOWN in response to a ULP request. And should discard
 * subsequent SHUTDOWN chunks.
 *
 * If there are still outstanding DATA chunks left, the SHUTDOWN
 * receiver shall जारी to follow normal data transmission
 * procedures defined in Section 6 until all outstanding DATA chunks
 * are acknowledged; however, the SHUTDOWN receiver MUST NOT accept
 * new data from its SCTP user.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	क्रमागत sctp_disposition disposition;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_shutकरोwnhdr *sdh;
	काष्ठा sctp_ulpevent *ev;
	__u32 ctsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the SHUTDOWN chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_shutकरोwn_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Convert the elaborate header.  */
	sdh = (काष्ठा sctp_shutकरोwnhdr *)chunk->skb->data;
	skb_pull(chunk->skb, माप(*sdh));
	chunk->subh.shutकरोwn_hdr = sdh;
	ctsn = ntohl(sdh->cum_tsn_ack);

	अगर (TSN_lt(ctsn, asoc->ctsn_ack_poपूर्णांक)) अणु
		pr_debug("%s: ctsn:%x, ctsn_ack_point:%x\n", __func__, ctsn,
			 asoc->ctsn_ack_poपूर्णांक);

		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* If Cumulative TSN Ack beyond the max tsn currently
	 * send, terminating the association and respond to the
	 * sender with an ABORT.
	 */
	अगर (!TSN_lt(ctsn, asoc->next_tsn))
		वापस sctp_sf_violation_ctsn(net, ep, asoc, type, arg, commands);

	/* API 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 * When a peer sends a SHUTDOWN, SCTP delivers this notअगरication to
	 * inक्रमm the application that it should cease sending data.
	 */
	ev = sctp_ulpevent_make_shutकरोwn_event(asoc, 0, GFP_ATOMIC);
	अगर (!ev) अणु
		disposition = SCTP_DISPOSITION_NOMEM;
		जाओ out;
	पूर्ण
	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));

	/* Upon the reception of the SHUTDOWN, the peer endpoपूर्णांक shall
	 *  - enter the SHUTDOWN-RECEIVED state,
	 *  - stop accepting new data from its SCTP user
	 *
	 * [This is implicit in the new state.]
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_RECEIVED));
	disposition = SCTP_DISPOSITION_CONSUME;

	अगर (sctp_outq_is_empty(&asoc->outqueue)) अणु
		disposition = sctp_sf_करो_9_2_shutकरोwn_ack(net, ep, asoc, type,
							  arg, commands);
	पूर्ण

	अगर (SCTP_DISPOSITION_NOMEM == disposition)
		जाओ out;

	/*  - verअगरy, by checking the Cumulative TSN Ack field of the
	 *    chunk, that all its outstanding DATA chunks have been
	 *    received by the SHUTDOWN sender.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_CTSN,
			SCTP_BE32(chunk->subh.shutकरोwn_hdr->cum_tsn_ack));

out:
	वापस disposition;
पूर्ण

/*
 * sctp_sf_करो_9_2_shut_ctsn
 *
 * Once an endpoपूर्णांक has reached the SHUTDOWN-RECEIVED state,
 * it MUST NOT send a SHUTDOWN in response to a ULP request.
 * The Cumulative TSN Ack of the received SHUTDOWN chunk
 * MUST be processed.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_shut_ctsn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_shutकरोwnhdr *sdh;
	__u32 ctsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the SHUTDOWN chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_shutकरोwn_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	sdh = (काष्ठा sctp_shutकरोwnhdr *)chunk->skb->data;
	ctsn = ntohl(sdh->cum_tsn_ack);

	अगर (TSN_lt(ctsn, asoc->ctsn_ack_poपूर्णांक)) अणु
		pr_debug("%s: ctsn:%x, ctsn_ack_point:%x\n", __func__, ctsn,
			 asoc->ctsn_ack_poपूर्णांक);

		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* If Cumulative TSN Ack beyond the max tsn currently
	 * send, terminating the association and respond to the
	 * sender with an ABORT.
	 */
	अगर (!TSN_lt(ctsn, asoc->next_tsn))
		वापस sctp_sf_violation_ctsn(net, ep, asoc, type, arg, commands);

	/* verअगरy, by checking the Cumulative TSN Ack field of the
	 * chunk, that all its outstanding DATA chunks have been
	 * received by the SHUTDOWN sender.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_CTSN,
			SCTP_BE32(sdh->cum_tsn_ack));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* RFC 2960 9.2
 * If an endpoपूर्णांक is in SHUTDOWN-ACK-SENT state and receives an INIT chunk
 * (e.g., अगर the SHUTDOWN COMPLETE was lost) with source and destination
 * transport addresses (either in the IP addresses or in the INIT chunk)
 * that beदीर्घ to this association, it should discard the INIT chunk and
 * retransmit the SHUTDOWN ACK chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_reshutack(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *reply;

	/* Make sure that the chunk has a valid length */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Since we are not going to really process this INIT, there
	 * is no poपूर्णांक in verअगरying chunk boundries.  Just generate
	 * the SHUTDOWN ACK.
	 */
	reply = sctp_make_shutकरोwn_ack(asoc, chunk);
	अगर (शून्य == reply)
		जाओ nomem;

	/* Set the transport क्रम the SHUTDOWN ACK chunk and the समयout क्रम
	 * the T2-SHUTDOWN समयr.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* and restart the T2-shutकरोwn समयr. */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	वापस SCTP_DISPOSITION_CONSUME;
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * sctp_sf_करो_ecn_cwr
 *
 * Section:  Appendix A: Explicit Congestion Notअगरication
 *
 * CWR:
 *
 * RFC 2481 details a specअगरic bit क्रम a sender to send in the header of
 * its next outbound TCP segment to indicate to its peer that it has
 * reduced its congestion winकरोw.  This is termed the CWR bit.  For
 * SCTP the same indication is made by including the CWR chunk.
 * This chunk contains one data element, i.e. the TSN number that
 * was sent in the ECNE chunk.  This element represents the lowest
 * TSN number in the datagram that was originally marked with the
 * CE bit.
 *
 * Verअगरication Tag: 8.5 Verअगरication Tag [Normal verअगरication]
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_ecn_cwr(काष्ठा net *net,
					 स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					 स्थिर काष्ठा sctp_association *asoc,
					 स्थिर जोड़ sctp_subtype type,
					 व्योम *arg,
					 काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_cwrhdr *cwr;
	u32 lowest_tsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_ecne_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	cwr = (काष्ठा sctp_cwrhdr *)chunk->skb->data;
	skb_pull(chunk->skb, माप(*cwr));

	lowest_tsn = ntohl(cwr->lowest_tsn);

	/* Does this CWR ack the last sent congestion notअगरication? */
	अगर (TSN_lte(asoc->last_ecne_tsn, lowest_tsn)) अणु
		/* Stop sending ECNE. */
		sctp_add_cmd_sf(commands,
				SCTP_CMD_ECN_CWR,
				SCTP_U32(lowest_tsn));
	पूर्ण
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * sctp_sf_करो_ecne
 *
 * Section:  Appendix A: Explicit Congestion Notअगरication
 *
 * ECN-Echo
 *
 * RFC 2481 details a specअगरic bit क्रम a receiver to send back in its
 * TCP acknowledgements to notअगरy the sender of the Congestion
 * Experienced (CE) bit having arrived from the network.  For SCTP this
 * same indication is made by including the ECNE chunk.  This chunk
 * contains one data element, i.e. the lowest TSN associated with the IP
 * datagram marked with the CE bit.....
 *
 * Verअगरication Tag: 8.5 Verअगरication Tag [Normal verअगरication]
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_ecne(काष्ठा net *net,
				      स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				      स्थिर काष्ठा sctp_association *asoc,
				      स्थिर जोड़ sctp_subtype type,
				      व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_ecnehdr *ecne;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_ecne_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	ecne = (काष्ठा sctp_ecnehdr *)chunk->skb->data;
	skb_pull(chunk->skb, माप(*ecne));

	/* If this is a newer ECNE than the last CWR packet we sent out */
	sctp_add_cmd_sf(commands, SCTP_CMD_ECN_ECNE,
			SCTP_U32(ntohl(ecne->lowest_tsn)));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Section: 6.2  Acknowledgement on Reception of DATA Chunks
 *
 * The SCTP endpoपूर्णांक MUST always acknowledge the reception of each valid
 * DATA chunk.
 *
 * The guidelines on delayed acknowledgement algorithm specअगरied in
 * Section 4.2 of [RFC2581] SHOULD be followed. Specअगरically, an
 * acknowledgement SHOULD be generated क्रम at least every second packet
 * (not every second DATA chunk) received, and SHOULD be generated within
 * 200 ms of the arrival of any unacknowledged DATA chunk. In some
 * situations it may be beneficial क्रम an SCTP transmitter to be more
 * conservative than the algorithms detailed in this करोcument allow.
 * However, an SCTP transmitter MUST NOT be more aggressive than the
 * following algorithms allow.
 *
 * A SCTP receiver MUST NOT generate more than one SACK क्रम every
 * incoming packet, other than to update the offered winकरोw as the
 * receiving application consumes new data.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_eat_data_6_2(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	जोड़ sctp_arg क्रमce = SCTP_NOFORCE();
	काष्ठा sctp_chunk *chunk = arg;
	पूर्णांक error;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	अगर (!sctp_chunk_length_valid(chunk, sctp_datachk_len(&asoc->stream)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	error = sctp_eat_data(asoc, chunk, commands);
	चयन (error) अणु
	हाल SCTP_IERROR_NO_ERROR:
		अवरोध;
	हाल SCTP_IERROR_HIGH_TSN:
	हाल SCTP_IERROR_BAD_STREAM:
		SCTP_INC_STATS(net, SCTP_MIB_IN_DATA_CHUNK_DISCARDS);
		जाओ discard_noक्रमce;
	हाल SCTP_IERROR_DUP_TSN:
	हाल SCTP_IERROR_IGNORE_TSN:
		SCTP_INC_STATS(net, SCTP_MIB_IN_DATA_CHUNK_DISCARDS);
		जाओ discard_क्रमce;
	हाल SCTP_IERROR_NO_DATA:
		वापस SCTP_DISPOSITION_ABORT;
	हाल SCTP_IERROR_PROTO_VIOLATION:
		वापस sctp_sf_पात_violation(net, ep, asoc, chunk, commands,
					       (u8 *)chunk->subh.data_hdr,
					       sctp_datahdr_len(&asoc->stream));
	शेष:
		BUG();
	पूर्ण

	अगर (chunk->chunk_hdr->flags & SCTP_DATA_SACK_IMM)
		क्रमce = SCTP_FORCE();

	अगर (asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE]) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));
	पूर्ण

	/* If this is the last chunk in a packet, we need to count it
	 * toward sack generation.  Note that we need to SACK every
	 * OTHER packet containing data chunks, EVEN IF WE DISCARD
	 * THEM.  We elect to NOT generate SACK's अगर the chunk fails
	 * the verअगरication tag test.
	 *
	 * RFC 2960 6.2 Acknowledgement on Reception of DATA Chunks
	 *
	 * The SCTP endpoपूर्णांक MUST always acknowledge the reception of
	 * each valid DATA chunk.
	 *
	 * The guidelines on delayed acknowledgement algorithm
	 * specअगरied in  Section 4.2 of [RFC2581] SHOULD be followed.
	 * Specअगरically, an acknowledgement SHOULD be generated क्रम at
	 * least every second packet (not every second DATA chunk)
	 * received, and SHOULD be generated within 200 ms of the
	 * arrival of any unacknowledged DATA chunk.  In some
	 * situations it may be beneficial क्रम an SCTP transmitter to
	 * be more conservative than the algorithms detailed in this
	 * करोcument allow. However, an SCTP transmitter MUST NOT be
	 * more aggressive than the following algorithms allow.
	 */
	अगर (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, क्रमce);

	वापस SCTP_DISPOSITION_CONSUME;

discard_क्रमce:
	/* RFC 2960 6.2 Acknowledgement on Reception of DATA Chunks
	 *
	 * When a packet arrives with duplicate DATA chunk(s) and with
	 * no new DATA chunk(s), the endpoपूर्णांक MUST immediately send a
	 * SACK with no delay.  If a packet arrives with duplicate
	 * DATA chunk(s) bundled with new DATA chunks, the endpoपूर्णांक
	 * MAY immediately send a SACK.  Normally receipt of duplicate
	 * DATA chunks will occur when the original SACK chunk was lost
	 * and the peer's RTO has expired.  The duplicate TSN number(s)
	 * SHOULD be reported in the SACK as duplicate.
	 */
	/* In our हाल, we split the MAY SACK advice up whether or not
	 * the last chunk is a duplicate.'
	 */
	अगर (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
	वापस SCTP_DISPOSITION_DISCARD;

discard_noक्रमce:
	अगर (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, क्रमce);

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/*
 * sctp_sf_eat_data_fast_4_4
 *
 * Section: 4 (4)
 * (4) In SHUTDOWN-SENT state the endpoपूर्णांक MUST acknowledge any received
 *    DATA chunks without delay.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_eat_data_fast_4_4(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	पूर्णांक error;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	अगर (!sctp_chunk_length_valid(chunk, sctp_datachk_len(&asoc->stream)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	error = sctp_eat_data(asoc, chunk, commands);
	चयन (error) अणु
	हाल SCTP_IERROR_NO_ERROR:
	हाल SCTP_IERROR_HIGH_TSN:
	हाल SCTP_IERROR_DUP_TSN:
	हाल SCTP_IERROR_IGNORE_TSN:
	हाल SCTP_IERROR_BAD_STREAM:
		अवरोध;
	हाल SCTP_IERROR_NO_DATA:
		वापस SCTP_DISPOSITION_ABORT;
	हाल SCTP_IERROR_PROTO_VIOLATION:
		वापस sctp_sf_पात_violation(net, ep, asoc, chunk, commands,
					       (u8 *)chunk->subh.data_hdr,
					       sctp_datahdr_len(&asoc->stream));
	शेष:
		BUG();
	पूर्ण

	/* Go a head and क्रमce a SACK, since we are shutting करोwn. */

	/* Implementor's Guide.
	 *
	 * While in SHUTDOWN-SENT state, the SHUTDOWN sender MUST immediately
	 * respond to each received packet containing one or more DATA chunk(s)
	 * with a SACK, a SHUTDOWN chunk, and restart the T2-shutकरोwn समयr
	 */
	अगर (chunk->end_of_packet) अणु
		/* We must delay the chunk creation since the cumulative
		 * TSN has not been updated yet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SHUTDOWN, SCTP_शून्य());
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Section: 6.2  Processing a Received SACK
 * D) Any समय a SACK arrives, the endpoपूर्णांक perक्रमms the following:
 *
 *     i) If Cumulative TSN Ack is less than the Cumulative TSN Ack Poपूर्णांक,
 *     then drop the SACK.   Since Cumulative TSN Ack is monotonically
 *     increasing, a SACK whose Cumulative TSN Ack is less than the
 *     Cumulative TSN Ack Poपूर्णांक indicates an out-of-order SACK.
 *
 *     ii) Set rwnd equal to the newly received a_rwnd minus the number
 *     of bytes still outstanding after processing the Cumulative TSN Ack
 *     and the Gap Ack Blocks.
 *
 *     iii) If the SACK is missing a TSN that was previously
 *     acknowledged via a Gap Ack Block (e.g., the data receiver
 *     reneged on the data), then mark the corresponding DATA chunk
 *     as available क्रम retransmit:  Mark it as missing क्रम fast
 *     retransmit as described in Section 7.2.4 and अगर no retransmit
 *     समयr is running क्रम the destination address to which the DATA
 *     chunk was originally transmitted, then T3-rtx is started क्रम
 *     that destination address.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_eat_sack_6_2(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_sackhdr *sackh;
	__u32 ctsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the SACK chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_sack_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Pull the SACK chunk from the data buffer */
	sackh = sctp_sm_pull_sack(chunk);
	/* Was this a bogus SACK? */
	अगर (!sackh)
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	chunk->subh.sack_hdr = sackh;
	ctsn = ntohl(sackh->cum_tsn_ack);

	/* If Cumulative TSN Ack beyond the max tsn currently
	 * send, terminating the association and respond to the
	 * sender with an ABORT.
	 */
	अगर (TSN_lte(asoc->next_tsn, ctsn))
		वापस sctp_sf_violation_ctsn(net, ep, asoc, type, arg, commands);

	trace_sctp_probe(ep, asoc, chunk);

	/* i) If Cumulative TSN Ack is less than the Cumulative TSN
	 *     Ack Poपूर्णांक, then drop the SACK.  Since Cumulative TSN
	 *     Ack is monotonically increasing, a SACK whose
	 *     Cumulative TSN Ack is less than the Cumulative TSN Ack
	 *     Poपूर्णांक indicates an out-of-order SACK.
	 */
	अगर (TSN_lt(ctsn, asoc->ctsn_ack_poपूर्णांक)) अणु
		pr_debug("%s: ctsn:%x, ctsn_ack_point:%x\n", __func__, ctsn,
			 asoc->ctsn_ack_poपूर्णांक);

		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* Return this SACK क्रम further processing.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_SACK, SCTP_CHUNK(chunk));

	/* Note: We करो the rest of the work on the PROCESS_SACK
	 * sideeffect.
	 */
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Generate an ABORT in response to a packet.
 *
 * Section: 8.4 Handle "Out of the blue" Packets, sctpimpguide 2.41
 *
 * 8) The receiver should respond to the sender of the OOTB packet with
 *    an ABORT.  When sending the ABORT, the receiver of the OOTB packet
 *    MUST fill in the Verअगरication Tag field of the outbound packet
 *    with the value found in the Verअगरication Tag field of the OOTB
 *    packet and set the T-bit in the Chunk Flags to indicate that the
 *    Verअगरication Tag is reflected.  After sending this ABORT, the
 *    receiver of the OOTB packet shall discard the OOTB packet and take
 *    no further action.
 *
 * Verअगरication Tag:
 *
 * The वापस value is the disposition of the chunk.
*/
अटल क्रमागत sctp_disposition sctp_sf_tपात_8_4_8(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_packet *packet = शून्य;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *पात;

	packet = sctp_ootb_pkt_new(net, asoc, chunk);
	अगर (!packet)
		वापस SCTP_DISPOSITION_NOMEM;

	/* Make an ABORT. The T bit will be set अगर the asoc
	 * is शून्य.
	 */
	पात = sctp_make_पात(asoc, chunk, 0);
	अगर (!पात) अणु
		sctp_ootb_pkt_मुक्त(packet);
		वापस SCTP_DISPOSITION_NOMEM;
	पूर्ण

	/* Reflect vtag अगर T-Bit is set */
	अगर (sctp_test_T_bit(पात))
		packet->vtag = ntohl(chunk->sctp_hdr->vtag);

	/* Set the skb to the beदीर्घing sock क्रम accounting.  */
	पात->skb->sk = ep->base.sk;

	sctp_packet_append_chunk(packet, पात);

	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT, SCTP_PACKET(packet));

	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* Handling of SCTP Packets Containing an INIT Chunk Matching an
 * Existing Associations when the UDP encap port is incorrect.
 *
 * From Section 4 at draft-tuexen-tsvwg-sctp-udp-encaps-cons-03.
 */
अटल क्रमागत sctp_disposition sctp_sf_new_encap_port(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_packet *packet = शून्य;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *पात;

	packet = sctp_ootb_pkt_new(net, asoc, chunk);
	अगर (!packet)
		वापस SCTP_DISPOSITION_NOMEM;

	पात = sctp_make_new_encap_port(asoc, chunk);
	अगर (!पात) अणु
		sctp_ootb_pkt_मुक्त(packet);
		वापस SCTP_DISPOSITION_NOMEM;
	पूर्ण

	पात->skb->sk = ep->base.sk;

	sctp_packet_append_chunk(packet, पात);

	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
			SCTP_PACKET(packet));

	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Received an ERROR chunk from peer.  Generate SCTP_REMOTE_ERROR
 * event as ULP notअगरication क्रम each cause included in the chunk.
 *
 * API 5.3.1.3 - SCTP_REMOTE_ERROR
 *
 * The वापस value is the disposition of the chunk.
*/
क्रमागत sctp_disposition sctp_sf_operr_notअगरy(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_errhdr *err;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ERROR chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_operr_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);
	sctp_walk_errors(err, chunk->chunk_hdr);
	अगर ((व्योम *)err != (व्योम *)chunk->chunk_end)
		वापस sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
						  (व्योम *)err, commands);

	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_OPERR,
			SCTP_CHUNK(chunk));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Process an inbound SHUTDOWN ACK.
 *
 * From Section 9.2:
 * Upon the receipt of the SHUTDOWN ACK, the SHUTDOWN sender shall
 * stop the T2-shutकरोwn समयr, send a SHUTDOWN COMPLETE chunk to its
 * peer, and हटाओ all record of the association.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_final(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *reply;
	काष्ठा sctp_ulpevent *ev;

	अगर (!sctp_vtag_verअगरy(chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the SHUTDOWN_ACK chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);
	/* 10.2 H) SHUTDOWN COMPLETE notअगरication
	 *
	 * When SCTP completes the shutकरोwn procedures (section 9.2) this
	 * notअगरication is passed to the upper layer.
	 */
	ev = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_SHUTDOWN_COMP,
					     0, 0, 0, शून्य, GFP_ATOMIC);
	अगर (!ev)
		जाओ nomem;

	/* ...send a SHUTDOWN COMPLETE chunk to its peer, */
	reply = sctp_make_shutकरोwn_complete(asoc, chunk);
	अगर (!reply)
		जाओ nomem_chunk;

	/* Do all the commands now (after allocation), so that we
	 * have consistent state अगर memory allocation failes
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));

	/* Upon the receipt of the SHUTDOWN ACK, the SHUTDOWN sender shall
	 * stop the T2-shutकरोwn समयr,
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));
	SCTP_INC_STATS(net, SCTP_MIB_SHUTDOWNS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	/* ...and हटाओ all record of the association. */
	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());
	वापस SCTP_DISPOSITION_DELETE_TCB;

nomem_chunk:
	sctp_ulpevent_मुक्त(ev);
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * RFC 2960, 8.4 - Handle "Out of the blue" Packets, sctpimpguide 2.41.
 *
 * 5) If the packet contains a SHUTDOWN ACK chunk, the receiver should
 *    respond to the sender of the OOTB packet with a SHUTDOWN COMPLETE.
 *    When sending the SHUTDOWN COMPLETE, the receiver of the OOTB
 *    packet must fill in the Verअगरication Tag field of the outbound
 *    packet with the Verअगरication Tag received in the SHUTDOWN ACK and
 *    set the T-bit in the Chunk Flags to indicate that the Verअगरication
 *    Tag is reflected.
 *
 * 8) The receiver should respond to the sender of the OOTB packet with
 *    an ABORT.  When sending the ABORT, the receiver of the OOTB packet
 *    MUST fill in the Verअगरication Tag field of the outbound packet
 *    with the value found in the Verअगरication Tag field of the OOTB
 *    packet and set the T-bit in the Chunk Flags to indicate that the
 *    Verअगरication Tag is reflected.  After sending this ABORT, the
 *    receiver of the OOTB packet shall discard the OOTB packet and take
 *    no further action.
 */
क्रमागत sctp_disposition sctp_sf_ootb(काष्ठा net *net,
				   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				   स्थिर काष्ठा sctp_association *asoc,
				   स्थिर जोड़ sctp_subtype type,
				   व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sk_buff *skb = chunk->skb;
	काष्ठा sctp_chunkhdr *ch;
	काष्ठा sctp_errhdr *err;
	पूर्णांक ootb_cookie_ack = 0;
	पूर्णांक ootb_shut_ack = 0;
	__u8 *ch_end;

	SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);

	ch = (काष्ठा sctp_chunkhdr *)chunk->chunk_hdr;
	करो अणु
		/* Report violation अगर the chunk is less then minimal */
		अगर (ntohs(ch->length) < माप(*ch))
			वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

		/* Report violation अगर chunk len overflows */
		ch_end = ((__u8 *)ch) + SCTP_PAD4(ntohs(ch->length));
		अगर (ch_end > skb_tail_poपूर्णांकer(skb))
			वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

		/* Now that we know we at least have a chunk header,
		 * करो things that are type appropriate.
		 */
		अगर (SCTP_CID_SHUTDOWN_ACK == ch->type)
			ootb_shut_ack = 1;

		/* RFC 2960, Section 3.3.7
		 *   Moreover, under any circumstances, an endpoपूर्णांक that
		 *   receives an ABORT  MUST NOT respond to that ABORT by
		 *   sending an ABORT of its own.
		 */
		अगर (SCTP_CID_ABORT == ch->type)
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

		/* RFC 8.4, 7) If the packet contains a "Stale cookie" ERROR
		 * or a COOKIE ACK the SCTP Packet should be silently
		 * discarded.
		 */

		अगर (SCTP_CID_COOKIE_ACK == ch->type)
			ootb_cookie_ack = 1;

		अगर (SCTP_CID_ERROR == ch->type) अणु
			sctp_walk_errors(err, ch) अणु
				अगर (SCTP_ERROR_STALE_COOKIE == err->cause) अणु
					ootb_cookie_ack = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		ch = (काष्ठा sctp_chunkhdr *)ch_end;
	पूर्ण जबतक (ch_end < skb_tail_poपूर्णांकer(skb));

	अगर (ootb_shut_ack)
		वापस sctp_sf_shut_8_4_5(net, ep, asoc, type, arg, commands);
	अन्यथा अगर (ootb_cookie_ack)
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	अन्यथा
		वापस sctp_sf_tपात_8_4_8(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Handle an "Out of the blue" SHUTDOWN ACK.
 *
 * Section: 8.4 5, sctpimpguide 2.41.
 *
 * 5) If the packet contains a SHUTDOWN ACK chunk, the receiver should
 *    respond to the sender of the OOTB packet with a SHUTDOWN COMPLETE.
 *    When sending the SHUTDOWN COMPLETE, the receiver of the OOTB
 *    packet must fill in the Verअगरication Tag field of the outbound
 *    packet with the Verअगरication Tag received in the SHUTDOWN ACK and
 *    set the T-bit in the Chunk Flags to indicate that the Verअगरication
 *    Tag is reflected.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, type, arg, commands)
 *
 * Outमाला_दो
 * (क्रमागत sctp_disposition)
 *
 * The वापस value is the disposition of the chunk.
 */
अटल क्रमागत sctp_disposition sctp_sf_shut_8_4_5(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_packet *packet = शून्य;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *shut;

	packet = sctp_ootb_pkt_new(net, asoc, chunk);
	अगर (!packet)
		वापस SCTP_DISPOSITION_NOMEM;

	/* Make an SHUTDOWN_COMPLETE.
	 * The T bit will be set अगर the asoc is शून्य.
	 */
	shut = sctp_make_shutकरोwn_complete(asoc, chunk);
	अगर (!shut) अणु
		sctp_ootb_pkt_मुक्त(packet);
		वापस SCTP_DISPOSITION_NOMEM;
	पूर्ण

	/* Reflect vtag अगर T-Bit is set */
	अगर (sctp_test_T_bit(shut))
		packet->vtag = ntohl(chunk->sctp_hdr->vtag);

	/* Set the skb to the beदीर्घing sock क्रम accounting.  */
	shut->skb->sk = ep->base.sk;

	sctp_packet_append_chunk(packet, shut);

	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
			SCTP_PACKET(packet));

	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	/* If the chunk length is invalid, we करोn't want to process
	 * the reset of the packet.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* We need to discard the rest of the packet to prevent
	 * potential bomming attacks from additional bundled chunks.
	 * This is करोcumented in SCTP Threats ID.
	 */
	वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Handle SHUTDOWN ACK in COOKIE_ECHOED or COOKIE_WAIT state.
 *
 * Verअगरication Tag:  8.5.1 E) Rules क्रम packet carrying a SHUTDOWN ACK
 *   If the receiver is in COOKIE-ECHOED or COOKIE-WAIT state the
 *   procedures in section 8.4 SHOULD be followed, in other words it
 *   should be treated as an Out Of The Blue packet.
 *   [This means that we करो NOT check the Verअगरication Tag on these
 *   chunks. --piggy ]
 *
 */
क्रमागत sctp_disposition sctp_sf_करो_8_5_1_E_sa(काष्ठा net *net,
					    स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					    स्थिर काष्ठा sctp_association *asoc,
					    स्थिर जोड़ sctp_subtype type,
					    व्योम *arg,
					    काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	/* Make sure that the SHUTDOWN_ACK chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Although we करो have an association in this हाल, it corresponds
	 * to a restarted association. So the packet is treated as an OOTB
	 * packet and the state function that handles OOTB SHUTDOWN_ACK is
	 * called with a शून्य association.
	 */
	SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);

	वापस sctp_sf_shut_8_4_5(net, ep, शून्य, type, arg, commands);
पूर्ण

/* ADDIP Section 4.2 Upon reception of an ASCONF Chunk.  */
क्रमागत sctp_disposition sctp_sf_करो_asconf(काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_paramhdr *err_param = शून्य;
	काष्ठा sctp_chunk *asconf_ack = शून्य;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_addiphdr *hdr;
	__u32 serial;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* ADD-IP: Section 4.1.1
	 * This chunk MUST be sent in an authenticated way by using
	 * the mechanism defined in [I-D.ietf-tsvwg-sctp-auth]. If this chunk
	 * is received unauthenticated it MUST be silently discarded as
	 * described in [I-D.ietf-tsvwg-sctp-auth].
	 */
	अगर (!asoc->peer.asconf_capable ||
	    (!net->sctp.addip_noauth && !chunk->auth))
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg,
					     commands);

	/* Make sure that the ASCONF ADDIP chunk has a valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_addip_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	hdr = (काष्ठा sctp_addiphdr *)chunk->skb->data;
	serial = ntohl(hdr->serial);

	/* Verअगरy the ASCONF chunk beक्रमe processing it. */
	अगर (!sctp_verअगरy_asconf(asoc, chunk, true, &err_param))
		वापस sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
						  (व्योम *)err_param, commands);

	/* ADDIP 5.2 E1) Compare the value of the serial number to the value
	 * the endpoपूर्णांक stored in a new association variable
	 * 'Peer-Serial-Number'.
	 */
	अगर (serial == asoc->peer.addip_serial + 1) अणु
		/* If this is the first instance of ASCONF in the packet,
		 * we can clean our old ASCONF-ACKs.
		 */
		अगर (!chunk->has_asconf)
			sctp_assoc_clean_asconf_ack_cache(asoc);

		/* ADDIP 5.2 E4) When the Sequence Number matches the next one
		 * expected, process the ASCONF as described below and after
		 * processing the ASCONF Chunk, append an ASCONF-ACK Chunk to
		 * the response packet and cache a copy of it (in the event it
		 * later needs to be retransmitted).
		 *
		 * Essentially, करो V1-V5.
		 */
		asconf_ack = sctp_process_asconf((काष्ठा sctp_association *)
						 asoc, chunk);
		अगर (!asconf_ack)
			वापस SCTP_DISPOSITION_NOMEM;
	पूर्ण अन्यथा अगर (serial < asoc->peer.addip_serial + 1) अणु
		/* ADDIP 5.2 E2)
		 * If the value found in the Sequence Number is less than the
		 * ('Peer- Sequence-Number' + 1), simply skip to the next
		 * ASCONF, and include in the outbound response packet
		 * any previously cached ASCONF-ACK response that was
		 * sent and saved that matches the Sequence Number of the
		 * ASCONF.  Note: It is possible that no cached ASCONF-ACK
		 * Chunk exists.  This will occur when an older ASCONF
		 * arrives out of order.  In such a हाल, the receiver
		 * should skip the ASCONF Chunk and not include ASCONF-ACK
		 * Chunk क्रम that chunk.
		 */
		asconf_ack = sctp_assoc_lookup_asconf_ack(asoc, hdr->serial);
		अगर (!asconf_ack)
			वापस SCTP_DISPOSITION_DISCARD;

		/* Reset the transport so that we select the correct one
		 * this समय around.  This is to make sure that we करोn't
		 * accidentally use a stale transport that's been हटाओd.
		 */
		asconf_ack->transport = शून्य;
	पूर्ण अन्यथा अणु
		/* ADDIP 5.2 E5) Otherwise, the ASCONF Chunk is discarded since
		 * it must be either a stale packet or from an attacker.
		 */
		वापस SCTP_DISPOSITION_DISCARD;
	पूर्ण

	/* ADDIP 5.2 E6)  The destination address of the SCTP packet
	 * containing the ASCONF-ACK Chunks MUST be the source address of
	 * the SCTP packet that held the ASCONF Chunks.
	 *
	 * To करो this properly, we'll set the destination address of the chunk
	 * and at the transmit समय, will try look up the transport to use.
	 * Since ASCONFs may be bundled, the correct transport may not be
	 * created until we process the entire packet, thus this workaround.
	 */
	asconf_ack->dest = chunk->source;
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(asconf_ack));
	अगर (asoc->new_transport) अणु
		sctp_sf_heartbeat(ep, asoc, type, asoc->new_transport, commands);
		((काष्ठा sctp_association *)asoc)->new_transport = शून्य;
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

अटल क्रमागत sctp_disposition sctp_send_next_asconf(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *asconf;
	काष्ठा list_head *entry;

	अगर (list_empty(&asoc->addip_chunk_list))
		वापस SCTP_DISPOSITION_CONSUME;

	entry = asoc->addip_chunk_list.next;
	asconf = list_entry(entry, काष्ठा sctp_chunk, list);

	list_del_init(entry);
	sctp_chunk_hold(asconf);
	asoc->addip_last_asconf = asconf;

	वापस sctp_sf_करो_prm_asconf(net, ep, asoc, type, asconf, commands);
पूर्ण

/*
 * ADDIP Section 4.3 General rules क्रम address manipulation
 * When building TLV parameters क्रम the ASCONF Chunk that will add or
 * delete IP addresses the D0 to D13 rules should be applied:
 */
क्रमागत sctp_disposition sctp_sf_करो_asconf_ack(काष्ठा net *net,
					    स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					    स्थिर काष्ठा sctp_association *asoc,
					    स्थिर जोड़ sctp_subtype type,
					    व्योम *arg,
					    काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *last_asconf = asoc->addip_last_asconf;
	काष्ठा sctp_paramhdr *err_param = शून्य;
	काष्ठा sctp_chunk *asconf_ack = arg;
	काष्ठा sctp_addiphdr *addip_hdr;
	__u32 sent_serial, rcvd_serial;
	काष्ठा sctp_chunk *पात;

	अगर (!sctp_vtag_verअगरy(asconf_ack, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* ADD-IP, Section 4.1.2:
	 * This chunk MUST be sent in an authenticated way by using
	 * the mechanism defined in [I-D.ietf-tsvwg-sctp-auth]. If this chunk
	 * is received unauthenticated it MUST be silently discarded as
	 * described in [I-D.ietf-tsvwg-sctp-auth].
	 */
	अगर (!asoc->peer.asconf_capable ||
	    (!net->sctp.addip_noauth && !asconf_ack->auth))
		वापस sctp_sf_discard_chunk(net, ep, asoc, type, arg,
					     commands);

	/* Make sure that the ADDIP chunk has a valid length.  */
	अगर (!sctp_chunk_length_valid(asconf_ack,
				     माप(काष्ठा sctp_addip_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	addip_hdr = (काष्ठा sctp_addiphdr *)asconf_ack->skb->data;
	rcvd_serial = ntohl(addip_hdr->serial);

	/* Verअगरy the ASCONF-ACK chunk beक्रमe processing it. */
	अगर (!sctp_verअगरy_asconf(asoc, asconf_ack, false, &err_param))
		वापस sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
			   (व्योम *)err_param, commands);

	अगर (last_asconf) अणु
		addip_hdr = (काष्ठा sctp_addiphdr *)last_asconf->subh.addip_hdr;
		sent_serial = ntohl(addip_hdr->serial);
	पूर्ण अन्यथा अणु
		sent_serial = asoc->addip_serial - 1;
	पूर्ण

	/* D0) If an endpoपूर्णांक receives an ASCONF-ACK that is greater than or
	 * equal to the next serial number to be used but no ASCONF chunk is
	 * outstanding the endpoपूर्णांक MUST ABORT the association. Note that a
	 * sequence number is greater than अगर it is no more than 2^^31-1
	 * larger than the current sequence number (using serial arithmetic).
	 */
	अगर (ADDIP_SERIAL_gte(rcvd_serial, sent_serial + 1) &&
	    !(asoc->addip_last_asconf)) अणु
		पात = sctp_make_पात(asoc, asconf_ack,
					माप(काष्ठा sctp_errhdr));
		अगर (पात) अणु
			sctp_init_cause(पात, SCTP_ERROR_ASCONF_ACK, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(पात));
		पूर्ण
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_शून्य());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_ABORT;
	पूर्ण

	अगर ((rcvd_serial == sent_serial) && asoc->addip_last_asconf) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));

		अगर (!sctp_process_asconf_ack((काष्ठा sctp_association *)asoc,
					     asconf_ack))
			वापस sctp_send_next_asconf(net, ep,
					(काष्ठा sctp_association *)asoc,
							type, commands);

		पात = sctp_make_पात(asoc, asconf_ack,
					माप(काष्ठा sctp_errhdr));
		अगर (पात) अणु
			sctp_init_cause(पात, SCTP_ERROR_RSRC_LOW, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(पात));
		पूर्ण
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_शून्य());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_ABORT;
	पूर्ण

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/* RE-CONFIG Section 5.2 Upon reception of an RECONF Chunk. */
क्रमागत sctp_disposition sctp_sf_करो_reconf(काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_paramhdr *err_param = शून्य;
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_reconf_chunk *hdr;
	जोड़ sctp_params param;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* Make sure that the RECONF chunk has a valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, माप(*hdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	अगर (!sctp_verअगरy_reconf(asoc, chunk, &err_param))
		वापस sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
						  (व्योम *)err_param, commands);

	hdr = (काष्ठा sctp_reconf_chunk *)chunk->chunk_hdr;
	sctp_walk_params(param, hdr, params) अणु
		काष्ठा sctp_chunk *reply = शून्य;
		काष्ठा sctp_ulpevent *ev = शून्य;

		अगर (param.p->type == SCTP_PARAM_RESET_OUT_REQUEST)
			reply = sctp_process_strreset_outreq(
				(काष्ठा sctp_association *)asoc, param, &ev);
		अन्यथा अगर (param.p->type == SCTP_PARAM_RESET_IN_REQUEST)
			reply = sctp_process_strreset_inreq(
				(काष्ठा sctp_association *)asoc, param, &ev);
		अन्यथा अगर (param.p->type == SCTP_PARAM_RESET_TSN_REQUEST)
			reply = sctp_process_strreset_tsnreq(
				(काष्ठा sctp_association *)asoc, param, &ev);
		अन्यथा अगर (param.p->type == SCTP_PARAM_RESET_ADD_OUT_STREAMS)
			reply = sctp_process_strreset_addstrm_out(
				(काष्ठा sctp_association *)asoc, param, &ev);
		अन्यथा अगर (param.p->type == SCTP_PARAM_RESET_ADD_IN_STREAMS)
			reply = sctp_process_strreset_addstrm_in(
				(काष्ठा sctp_association *)asoc, param, &ev);
		अन्यथा अगर (param.p->type == SCTP_PARAM_RESET_RESPONSE)
			reply = sctp_process_strreset_resp(
				(काष्ठा sctp_association *)asoc, param, &ev);

		अगर (ev)
			sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
					SCTP_ULPEVENT(ev));

		अगर (reply)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(reply));
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * PR-SCTP Section 3.6 Receiver Side Implementation of PR-SCTP
 *
 * When a FORWARD TSN chunk arrives, the data receiver MUST first update
 * its cumulative TSN poपूर्णांक to the value carried in the FORWARD TSN
 * chunk, and then MUST further advance its cumulative TSN poपूर्णांक locally
 * अगर possible.
 * After the above processing, the data receiver MUST stop reporting any
 * missing TSNs earlier than or equal to the new cumulative TSN poपूर्णांक.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_eat_fwd_tsn(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_fwdtsn_hdr *fwdtsn_hdr;
	काष्ठा sctp_chunk *chunk = arg;
	__u16 len;
	__u32 tsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	अगर (!asoc->peer.prsctp_capable)
		वापस sctp_sf_unk_chunk(net, ep, asoc, type, arg, commands);

	/* Make sure that the FORWARD_TSN chunk has valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, sctp_ftsnchk_len(&asoc->stream)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	fwdtsn_hdr = (काष्ठा sctp_fwdtsn_hdr *)chunk->skb->data;
	chunk->subh.fwdtsn_hdr = fwdtsn_hdr;
	len = ntohs(chunk->chunk_hdr->length);
	len -= माप(काष्ठा sctp_chunkhdr);
	skb_pull(chunk->skb, len);

	tsn = ntohl(fwdtsn_hdr->new_cum_tsn);
	pr_debug("%s: TSN 0x%x\n", __func__, tsn);

	/* The TSN is too high--silently discard the chunk and count on it
	 * getting retransmitted later.
	 */
	अगर (sctp_tsnmap_check(&asoc->peer.tsn_map, tsn) < 0)
		जाओ discard_noक्रमce;

	अगर (!asoc->stream.si->validate_ftsn(chunk))
		जाओ discard_noक्रमce;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_FWDTSN, SCTP_U32(tsn));
	अगर (len > sctp_ftsnhdr_len(&asoc->stream))
		sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_FWDTSN,
				SCTP_CHUNK(chunk));

	/* Count this as receiving DATA. */
	अगर (asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE]) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));
	पूर्ण

	/* FIXME: For now send a SACK, but DATA processing may
	 * send another.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_NOFORCE());

	वापस SCTP_DISPOSITION_CONSUME;

discard_noक्रमce:
	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

क्रमागत sctp_disposition sctp_sf_eat_fwd_tsn_fast(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_fwdtsn_hdr *fwdtsn_hdr;
	काष्ठा sctp_chunk *chunk = arg;
	__u16 len;
	__u32 tsn;

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	अगर (!asoc->peer.prsctp_capable)
		वापस sctp_sf_unk_chunk(net, ep, asoc, type, arg, commands);

	/* Make sure that the FORWARD_TSN chunk has a valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, sctp_ftsnchk_len(&asoc->stream)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	fwdtsn_hdr = (काष्ठा sctp_fwdtsn_hdr *)chunk->skb->data;
	chunk->subh.fwdtsn_hdr = fwdtsn_hdr;
	len = ntohs(chunk->chunk_hdr->length);
	len -= माप(काष्ठा sctp_chunkhdr);
	skb_pull(chunk->skb, len);

	tsn = ntohl(fwdtsn_hdr->new_cum_tsn);
	pr_debug("%s: TSN 0x%x\n", __func__, tsn);

	/* The TSN is too high--silently discard the chunk and count on it
	 * getting retransmitted later.
	 */
	अगर (sctp_tsnmap_check(&asoc->peer.tsn_map, tsn) < 0)
		जाओ gen_shutकरोwn;

	अगर (!asoc->stream.si->validate_ftsn(chunk))
		जाओ gen_shutकरोwn;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_FWDTSN, SCTP_U32(tsn));
	अगर (len > sctp_ftsnhdr_len(&asoc->stream))
		sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_FWDTSN,
				SCTP_CHUNK(chunk));

	/* Go a head and क्रमce a SACK, since we are shutting करोwn. */
gen_shutकरोwn:
	/* Implementor's Guide.
	 *
	 * While in SHUTDOWN-SENT state, the SHUTDOWN sender MUST immediately
	 * respond to each received packet containing one or more DATA chunk(s)
	 * with a SACK, a SHUTDOWN chunk, and restart the T2-shutकरोwn समयr
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SHUTDOWN, SCTP_शून्य());
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * SCTP-AUTH Section 6.3 Receiving authenticated chukns
 *
 *    The receiver MUST use the HMAC algorithm indicated in the HMAC
 *    Identअगरier field.  If this algorithm was not specअगरied by the
 *    receiver in the HMAC-ALGO parameter in the INIT or INIT-ACK chunk
 *    during association setup, the AUTH chunk and all chunks after it MUST
 *    be discarded and an ERROR chunk SHOULD be sent with the error cause
 *    defined in Section 4.1.
 *
 *    If an endpoपूर्णांक with no shared key receives a Shared Key Identअगरier
 *    other than 0, it MUST silently discard all authenticated chunks.  If
 *    the endpoपूर्णांक has at least one endpoपूर्णांक pair shared key क्रम the peer,
 *    it MUST use the key specअगरied by the Shared Key Identअगरier अगर a
 *    key has been configured क्रम that Shared Key Identअगरier.  If no
 *    endpoपूर्णांक pair shared key has been configured क्रम that Shared Key
 *    Identअगरier, all authenticated chunks MUST be silently discarded.
 *
 * Verअगरication Tag:  8.5 Verअगरication Tag [Normal verअगरication]
 *
 * The वापस value is the disposition of the chunk.
 */
अटल क्रमागत sctp_ierror sctp_sf_authenticate(
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_shared_key *sh_key = शून्य;
	काष्ठा sctp_authhdr *auth_hdr;
	__u8 *save_digest, *digest;
	काष्ठा sctp_hmac *hmac;
	अचिन्हित पूर्णांक sig_len;
	__u16 key_id;

	/* Pull in the auth header, so we can करो some more verअगरication */
	auth_hdr = (काष्ठा sctp_authhdr *)chunk->skb->data;
	chunk->subh.auth_hdr = auth_hdr;
	skb_pull(chunk->skb, माप(*auth_hdr));

	/* Make sure that we support the HMAC algorithm from the auth
	 * chunk.
	 */
	अगर (!sctp_auth_asoc_verअगरy_hmac_id(asoc, auth_hdr->hmac_id))
		वापस SCTP_IERROR_AUTH_BAD_HMAC;

	/* Make sure that the provided shared key identअगरier has been
	 * configured
	 */
	key_id = ntohs(auth_hdr->shkey_id);
	अगर (key_id != asoc->active_key_id) अणु
		sh_key = sctp_auth_get_shkey(asoc, key_id);
		अगर (!sh_key)
			वापस SCTP_IERROR_AUTH_BAD_KEYID;
	पूर्ण

	/* Make sure that the length of the signature matches what
	 * we expect.
	 */
	sig_len = ntohs(chunk->chunk_hdr->length) -
		  माप(काष्ठा sctp_auth_chunk);
	hmac = sctp_auth_get_hmac(ntohs(auth_hdr->hmac_id));
	अगर (sig_len != hmac->hmac_len)
		वापस SCTP_IERROR_PROTO_VIOLATION;

	/* Now that we've करोne validation checks, we can compute and
	 * verअगरy the hmac.  The steps involved are:
	 *  1. Save the digest from the chunk.
	 *  2. Zero out the digest in the chunk.
	 *  3. Compute the new digest
	 *  4. Compare saved and new digests.
	 */
	digest = auth_hdr->hmac;
	skb_pull(chunk->skb, sig_len);

	save_digest = kmemdup(digest, sig_len, GFP_ATOMIC);
	अगर (!save_digest)
		जाओ nomem;

	स_रखो(digest, 0, sig_len);

	sctp_auth_calculate_hmac(asoc, chunk->skb,
				 (काष्ठा sctp_auth_chunk *)chunk->chunk_hdr,
				 sh_key, GFP_ATOMIC);

	/* Discard the packet अगर the digests करो not match */
	अगर (स_भेद(save_digest, digest, sig_len)) अणु
		kमुक्त(save_digest);
		वापस SCTP_IERROR_BAD_SIG;
	पूर्ण

	kमुक्त(save_digest);
	chunk->auth = 1;

	वापस SCTP_IERROR_NO_ERROR;
nomem:
	वापस SCTP_IERROR_NOMEM;
पूर्ण

क्रमागत sctp_disposition sctp_sf_eat_auth(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर जोड़ sctp_subtype type,
				       व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_authhdr *auth_hdr;
	काष्ठा sctp_chunk *err_chunk;
	क्रमागत sctp_ierror error;

	/* Make sure that the peer has AUTH capable */
	अगर (!asoc->peer.auth_capable)
		वापस sctp_sf_unk_chunk(net, ep, asoc, type, arg, commands);

	अगर (!sctp_vtag_verअगरy(chunk, asoc)) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_शून्य());
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	पूर्ण

	/* Make sure that the AUTH chunk has valid length.  */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_auth_chunk)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	auth_hdr = (काष्ठा sctp_authhdr *)chunk->skb->data;
	error = sctp_sf_authenticate(asoc, chunk);
	चयन (error) अणु
	हाल SCTP_IERROR_AUTH_BAD_HMAC:
		/* Generate the ERROR chunk and discard the rest
		 * of the packet
		 */
		err_chunk = sctp_make_op_error(asoc, chunk,
					       SCTP_ERROR_UNSUP_HMAC,
					       &auth_hdr->hmac_id,
					       माप(__u16), 0);
		अगर (err_chunk) अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err_chunk));
		पूर्ण
		fallthrough;
	हाल SCTP_IERROR_AUTH_BAD_KEYID:
	हाल SCTP_IERROR_BAD_SIG:
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	हाल SCTP_IERROR_PROTO_VIOLATION:
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	हाल SCTP_IERROR_NOMEM:
		वापस SCTP_DISPOSITION_NOMEM;

	शेष:			/* Prevent gcc warnings */
		अवरोध;
	पूर्ण

	अगर (asoc->active_key_id != ntohs(auth_hdr->shkey_id)) अणु
		काष्ठा sctp_ulpevent *ev;

		ev = sctp_ulpevent_make_authkey(asoc, ntohs(auth_hdr->shkey_id),
				    SCTP_AUTH_NEW_KEY, GFP_ATOMIC);

		अगर (!ev)
			वापस -ENOMEM;

		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Process an unknown chunk.
 *
 * Section: 3.2. Also, 2.1 in the implementor's guide.
 *
 * Chunk Types are encoded such that the highest-order two bits specअगरy
 * the action that must be taken अगर the processing endpoपूर्णांक करोes not
 * recognize the Chunk Type.
 *
 * 00 - Stop processing this SCTP packet and discard it, करो not process
 *      any further chunks within it.
 *
 * 01 - Stop processing this SCTP packet and discard it, करो not process
 *      any further chunks within it, and report the unrecognized
 *      chunk in an 'Unrecognized Chunk Type'.
 *
 * 10 - Skip this chunk and जारी processing.
 *
 * 11 - Skip this chunk and जारी processing, but report in an ERROR
 *      Chunk using the 'Unrecognized Chunk Type' cause of error.
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_unk_chunk(काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *unk_chunk = arg;
	काष्ठा sctp_chunk *err_chunk;
	काष्ठा sctp_chunkhdr *hdr;

	pr_debug("%s: processing unknown chunk id:%d\n", __func__, type.chunk);

	अगर (!sctp_vtag_verअगरy(unk_chunk, asoc))
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the chunk has a valid length.
	 * Since we करोn't know the chunk type, we use a general
	 * chunkhdr काष्ठाure to make a comparison.
	 */
	अगर (!sctp_chunk_length_valid(unk_chunk, माप(*hdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	चयन (type.chunk & SCTP_CID_ACTION_MASK) अणु
	हाल SCTP_CID_ACTION_DISCARD:
		/* Discard the packet.  */
		वापस sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	हाल SCTP_CID_ACTION_DISCARD_ERR:
		/* Generate an ERROR chunk as response. */
		hdr = unk_chunk->chunk_hdr;
		err_chunk = sctp_make_op_error(asoc, unk_chunk,
					       SCTP_ERROR_UNKNOWN_CHUNK, hdr,
					       SCTP_PAD4(ntohs(hdr->length)),
					       0);
		अगर (err_chunk) अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err_chunk));
		पूर्ण

		/* Discard the packet.  */
		sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
		वापस SCTP_DISPOSITION_CONSUME;
	हाल SCTP_CID_ACTION_SKIP:
		/* Skip the chunk.  */
		वापस SCTP_DISPOSITION_DISCARD;
	हाल SCTP_CID_ACTION_SKIP_ERR:
		/* Generate an ERROR chunk as response. */
		hdr = unk_chunk->chunk_hdr;
		err_chunk = sctp_make_op_error(asoc, unk_chunk,
					       SCTP_ERROR_UNKNOWN_CHUNK, hdr,
					       SCTP_PAD4(ntohs(hdr->length)),
					       0);
		अगर (err_chunk) अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err_chunk));
		पूर्ण
		/* Skip the chunk.  */
		वापस SCTP_DISPOSITION_CONSUME;
	शेष:
		अवरोध;
	पूर्ण

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/*
 * Discard the chunk.
 *
 * Section: 0.2, 5.2.3, 5.2.5, 5.2.6, 6.0, 8.4.6, 8.5.1c, 9.2
 * [Too numerous to mention...]
 * Verअगरication Tag: No verअगरication needed.
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_discard_chunk(काष्ठा net *net,
					    स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					    स्थिर काष्ठा sctp_association *asoc,
					    स्थिर जोड़ sctp_subtype type,
					    व्योम *arg,
					    काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	/* Make sure that the chunk has a valid length.
	 * Since we करोn't know the chunk type, we use a general
	 * chunkhdr काष्ठाure to make a comparison.
	 */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	pr_debug("%s: chunk:%d is discarded\n", __func__, type.chunk);

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/*
 * Discard the whole packet.
 *
 * Section: 8.4 2)
 *
 * 2) If the OOTB packet contains an ABORT chunk, the receiver MUST
 *    silently discard the OOTB packet and take no further action.
 *
 * Verअगरication Tag: No verअगरication necessary
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_pdiscard(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर जोड़ sctp_subtype type,
				       व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_DISCARDS);
	sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_शून्य());

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण


/*
 * The other end is violating protocol.
 *
 * Section: Not specअगरied
 * Verअगरication Tag: Not specअगरied
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (asoc, reply_msg, msg_up, समयrs, counters)
 *
 * We simply tag the chunk as a violation.  The state machine will log
 * the violation and जारी.
 */
क्रमागत sctp_disposition sctp_sf_violation(काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	/* Make sure that the chunk has a valid length. */
	अगर (!sctp_chunk_length_valid(chunk, माप(काष्ठा sctp_chunkhdr)))
		वापस sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	वापस SCTP_DISPOSITION_VIOLATION;
पूर्ण

/*
 * Common function to handle a protocol violation.
 */
अटल क्रमागत sctp_disposition sctp_sf_पात_violation(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands,
					स्थिर __u8 *payload,
					स्थिर माप_प्रकार paylen)
अणु
	काष्ठा sctp_packet *packet = शून्य;
	काष्ठा sctp_chunk *chunk =  arg;
	काष्ठा sctp_chunk *पात = शून्य;

	/* SCTP-AUTH, Section 6.3:
	 *    It should be noted that अगर the receiver wants to tear
	 *    करोwn an association in an authenticated way only, the
	 *    handling of malक्रमmed packets should not result in
	 *    tearing करोwn the association.
	 *
	 * This means that अगर we only want to पात associations
	 * in an authenticated way (i.e AUTH+ABORT), then we
	 * can't destroy this association just because the packet
	 * was malक्रमmed.
	 */
	अगर (sctp_auth_recv_cid(SCTP_CID_ABORT, asoc))
		जाओ discard;

	/* Make the पात chunk. */
	पात = sctp_make_पात_violation(asoc, chunk, payload, paylen);
	अगर (!पात)
		जाओ nomem;

	अगर (asoc) अणु
		/* Treat INIT-ACK as a special हाल during COOKIE-WAIT. */
		अगर (chunk->chunk_hdr->type == SCTP_CID_INIT_ACK &&
		    !asoc->peer.i.init_tag) अणु
			काष्ठा sctp_initack_chunk *initack;

			initack = (काष्ठा sctp_initack_chunk *)chunk->chunk_hdr;
			अगर (!sctp_chunk_length_valid(chunk, माप(*initack)))
				पात->chunk_hdr->flags |= SCTP_CHUNK_FLAG_T;
			अन्यथा अणु
				अचिन्हित पूर्णांक inittag;

				inittag = ntohl(initack->init_hdr.init_tag);
				sctp_add_cmd_sf(commands, SCTP_CMD_UPDATE_INITTAG,
						SCTP_U32(inittag));
			पूर्ण
		पूर्ण

		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(पात));
		SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

		अगर (asoc->state <= SCTP_STATE_COOKIE_ECHOED) अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
					SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
			sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
					SCTP_ERROR(ECONNREFUSED));
			sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
					SCTP_PERR(SCTP_ERROR_PROTO_VIOLATION));
		पूर्ण अन्यथा अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
					SCTP_ERROR(ECONNABORTED));
			sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
					SCTP_PERR(SCTP_ERROR_PROTO_VIOLATION));
			SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		पूर्ण
	पूर्ण अन्यथा अणु
		packet = sctp_ootb_pkt_new(net, asoc, chunk);

		अगर (!packet)
			जाओ nomem_pkt;

		अगर (sctp_test_T_bit(पात))
			packet->vtag = ntohl(chunk->sctp_hdr->vtag);

		पात->skb->sk = ep->base.sk;

		sctp_packet_append_chunk(packet, पात);

		sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
			SCTP_PACKET(packet));

		SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
	पूर्ण

	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);

discard:
	sctp_sf_pdiscard(net, ep, asoc, SCTP_ST_CHUNK(0), arg, commands);
	वापस SCTP_DISPOSITION_ABORT;

nomem_pkt:
	sctp_chunk_मुक्त(पात);
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Handle a protocol violation when the chunk length is invalid.
 * "Invalid" length is identअगरied as smaller than the minimal length a
 * given chunk can be.  For example, a SACK chunk has invalid length
 * अगर its length is set to be smaller than the size of काष्ठा sctp_sack_chunk.
 *
 * We inक्रमm the other end by sending an ABORT with a Protocol Violation
 * error code.
 *
 * Section: Not specअगरied
 * Verअगरication Tag:  Nothing to करो
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * Outमाला_दो
 * (reply_msg, msg_up, counters)
 *
 * Generate an  ABORT chunk and terminate the association.
 */
अटल क्रमागत sctp_disposition sctp_sf_violation_chunklen(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	अटल स्थिर अक्षर err_str[] = "The following chunk had invalid length:";

	वापस sctp_sf_पात_violation(net, ep, asoc, arg, commands, err_str,
				       माप(err_str));
पूर्ण

/*
 * Handle a protocol violation when the parameter length is invalid.
 * If the length is smaller than the minimum length of a given parameter,
 * or accumulated length in multi parameters exceeds the end of the chunk,
 * the length is considered as invalid.
 */
अटल क्रमागत sctp_disposition sctp_sf_violation_paramlen(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg, व्योम *ext,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_paramhdr *param = ext;
	काष्ठा sctp_chunk *पात = शून्य;
	काष्ठा sctp_chunk *chunk = arg;

	अगर (sctp_auth_recv_cid(SCTP_CID_ABORT, asoc))
		जाओ discard;

	/* Make the पात chunk. */
	पात = sctp_make_violation_paramlen(asoc, chunk, param);
	अगर (!पात)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(पात));
	SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);

	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
			SCTP_ERROR(ECONNABORTED));
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_PROTO_VIOLATION));
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);

discard:
	sctp_sf_pdiscard(net, ep, asoc, SCTP_ST_CHUNK(0), arg, commands);
	वापस SCTP_DISPOSITION_ABORT;
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/* Handle a protocol violation when the peer trying to advance the
 * cumulative tsn ack to a poपूर्णांक beyond the max tsn currently sent.
 *
 * We inक्रमm the other end by sending an ABORT with a Protocol Violation
 * error code.
 */
अटल क्रमागत sctp_disposition sctp_sf_violation_ctsn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	अटल स्थिर अक्षर err_str[] = "The cumulative tsn ack beyond the max tsn currently sent:";

	वापस sctp_sf_पात_violation(net, ep, asoc, arg, commands, err_str,
				       माप(err_str));
पूर्ण

/* Handle protocol violation of an invalid chunk bundling.  For example,
 * when we have an association and we receive bundled INIT-ACK, or
 * SHUDOWN-COMPLETE, our peer is clearly violationg the "MUST NOT bundle"
 * statement from the specs.  Additionally, there might be an attacker
 * on the path and we may not want to जारी this communication.
 */
अटल क्रमागत sctp_disposition sctp_sf_violation_chunk(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	अटल स्थिर अक्षर err_str[] = "The following chunk violates protocol:";

	अगर (!asoc)
		वापस sctp_sf_violation(net, ep, asoc, type, arg, commands);

	वापस sctp_sf_पात_violation(net, ep, asoc, arg, commands, err_str,
				       माप(err_str));
पूर्ण
/***************************************************************************
 * These are the state functions क्रम handling primitive (Section 10) events.
 ***************************************************************************/
/*
 * sctp_sf_करो_prm_asoc
 *
 * Section: 10.1 ULP-to-SCTP
 * B) Associate
 *
 * Format: ASSOCIATE(local SCTP instance name, destination transport addr,
 * outbound stream count)
 * -> association id [,destination transport addr list] [,outbound stream
 * count]
 *
 * This primitive allows the upper layer to initiate an association to a
 * specअगरic peer endpoपूर्णांक.
 *
 * The peer endpoपूर्णांक shall be specअगरied by one of the transport addresses
 * which defines the endpoपूर्णांक (see Section 1.4).  If the local SCTP
 * instance has not been initialized, the ASSOCIATE is considered an
 * error.
 * [This is not relevant क्रम the kernel implementation since we करो all
 * initialization at boot समय.  It we hadn't initialized we wouldn't
 * get anywhere near this code.]
 *
 * An association id, which is a local handle to the SCTP association,
 * will be वापसed on successful establishment of the association. If
 * SCTP is not able to खोलो an SCTP association with the peer endpoपूर्णांक,
 * an error is वापसed.
 * [In the kernel implementation, the काष्ठा sctp_association needs to
 * be created BEFORE causing this primitive to run.]
 *
 * Other association parameters may be वापसed, including the
 * complete destination transport addresses of the peer as well as the
 * outbound stream count of the local endpoपूर्णांक. One of the transport
 * address from the वापसed destination addresses will be selected by
 * the local endpoपूर्णांक as शेष primary path क्रम sending SCTP packets
 * to this peer.  The वापसed "destination transport addr list" can
 * be used by the ULP to change the शेष primary path or to क्रमce
 * sending a packet to a specअगरic transport address.  [All of this
 * stuff happens when the INIT ACK arrives.  This is a NON-BLOCKING
 * function.]
 *
 * Mandatory attributes:
 *
 * o local SCTP instance name - obtained from the INITIALIZE operation.
 *   [This is the argument asoc.]
 * o destination transport addr - specअगरied as one of the transport
 * addresses of the peer endpoपूर्णांक with which the association is to be
 * established.
 *  [This is asoc->peer.active_path.]
 * o outbound stream count - the number of outbound streams the ULP
 * would like to खोलो towards this peer endpoपूर्णांक.
 * [BUG: This is not currently implemented.]
 * Optional attributes:
 *
 * None.
 *
 * The वापस value is a disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_prm_asoc(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_association *my_asoc;
	काष्ठा sctp_chunk *repl;

	/* The comment below says that we enter COOKIE-WAIT AFTER
	 * sending the INIT, but that करोesn't actually work in our
	 * implementation...
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_COOKIE_WAIT));

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * A) "A" first sends an INIT chunk to "Z".  In the INIT, "A"
	 * must provide its Verअगरication Tag (Tag_A) in the Initiate
	 * Tag field.  Tag_A SHOULD be a अक्रमom number in the range of
	 * 1 to 4294967295 (see 5.3.1 क्रम Tag value selection). ...
	 */

	repl = sctp_make_init(asoc, &asoc->base.bind_addr, GFP_ATOMIC, 0);
	अगर (!repl)
		जाओ nomem;

	/* Choose transport क्रम INIT. */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_CHOOSE_TRANSPORT,
			SCTP_CHUNK(repl));

	/* Cast away the स्थिर modअगरier, as we want to just
	 * rerun it through as a sideffect.
	 */
	my_asoc = (काष्ठा sctp_association *)asoc;
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_ASOC, SCTP_ASOC(my_asoc));

	/* After sending the INIT, "A" starts the T1-init समयr and
	 * enters the COOKIE-WAIT state.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Process the SEND primitive.
 *
 * Section: 10.1 ULP-to-SCTP
 * E) Send
 *
 * Format: SEND(association id, buffer address, byte count [,context]
 *         [,stream id] [,lअगरe समय] [,destination transport address]
 *         [,unorder flag] [,no-bundle flag] [,payload protocol-id] )
 * -> result
 *
 * This is the मुख्य method to send user data via SCTP.
 *
 * Mandatory attributes:
 *
 *  o association id - local handle to the SCTP association
 *
 *  o buffer address - the location where the user message to be
 *    transmitted is stored;
 *
 *  o byte count - The size of the user data in number of bytes;
 *
 * Optional attributes:
 *
 *  o context - an optional 32 bit पूर्णांकeger that will be carried in the
 *    sending failure notअगरication to the ULP अगर the transportation of
 *    this User Message fails.
 *
 *  o stream id - to indicate which stream to send the data on. If not
 *    specअगरied, stream 0 will be used.
 *
 *  o lअगरe समय - specअगरies the lअगरe समय of the user data. The user data
 *    will not be sent by SCTP after the lअगरe समय expires. This
 *    parameter can be used to aव्योम efक्रमts to transmit stale
 *    user messages. SCTP notअगरies the ULP अगर the data cannot be
 *    initiated to transport (i.e. sent to the destination via SCTP's
 *    send primitive) within the lअगरe समय variable. However, the
 *    user data will be transmitted अगर SCTP has attempted to transmit a
 *    chunk beक्रमe the lअगरe समय expired.
 *
 *  o destination transport address - specअगरied as one of the destination
 *    transport addresses of the peer endpoपूर्णांक to which this packet
 *    should be sent. Whenever possible, SCTP should use this destination
 *    transport address क्रम sending the packets, instead of the current
 *    primary path.
 *
 *  o unorder flag - this flag, अगर present, indicates that the user
 *    would like the data delivered in an unordered fashion to the peer
 *    (i.e., the U flag is set to 1 on all DATA chunks carrying this
 *    message).
 *
 *  o no-bundle flag - inकाष्ठाs SCTP not to bundle this user data with
 *    other outbound DATA chunks. SCTP MAY still bundle even when
 *    this flag is present, when faced with network congestion.
 *
 *  o payload protocol-id - A 32 bit अचिन्हित पूर्णांकeger that is to be
 *    passed to the peer indicating the type of payload protocol data
 *    being transmitted. This value is passed as opaque data by SCTP.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_prm_send(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_datamsg *msg = arg;

	sctp_add_cmd_sf(commands, SCTP_CMD_SEND_MSG, SCTP_DATAMSG(msg));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Process the SHUTDOWN primitive.
 *
 * Section: 10.1:
 * C) Shutकरोwn
 *
 * Format: SHUTDOWN(association id)
 * -> result
 *
 * Gracefully बंदs an association. Any locally queued user data
 * will be delivered to the peer. The association will be terminated only
 * after the peer acknowledges all the SCTP packets sent.  A success code
 * will be वापसed on successful termination of the association. If
 * attempting to terminate the association results in a failure, an error
 * code shall be वापसed.
 *
 * Mandatory attributes:
 *
 *  o association id - local handle to the SCTP association
 *
 * Optional attributes:
 *
 * None.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_prm_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	क्रमागत sctp_disposition disposition;

	/* From 9.2 Shutकरोwn of an Association
	 * Upon receipt of the SHUTDOWN primitive from its upper
	 * layer, the endpoपूर्णांक enters SHUTDOWN-PENDING state and
	 * reमुख्यs there until all outstanding data has been
	 * acknowledged by its peer. The endpoपूर्णांक accepts no new data
	 * from its upper layer, but retransmits data to the far end
	 * अगर necessary to fill gaps.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_PENDING));

	disposition = SCTP_DISPOSITION_CONSUME;
	अगर (sctp_outq_is_empty(&asoc->outqueue)) अणु
		disposition = sctp_sf_करो_9_2_start_shutकरोwn(net, ep, asoc, type,
							    arg, commands);
	पूर्ण

	वापस disposition;
पूर्ण

/*
 * Process the ABORT primitive.
 *
 * Section: 10.1:
 * C) Abort
 *
 * Format: Abort(association id [, cause code])
 * -> result
 *
 * Ungracefully बंदs an association. Any locally queued user data
 * will be discarded and an ABORT chunk is sent to the peer.  A success code
 * will be वापसed on successful पातion of the association. If
 * attempting to पात the association results in a failure, an error
 * code shall be वापसed.
 *
 * Mandatory attributes:
 *
 *  o association id - local handle to the SCTP association
 *
 * Optional attributes:
 *
 *  o cause code - reason of the पात to be passed to the peer
 *
 * None.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_1_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* From 9.1 Abort of an Association
	 * Upon receipt of the ABORT primitive from its upper
	 * layer, the endpoपूर्णांक enters CLOSED state and
	 * discard all outstanding data has been
	 * acknowledged by its peer. The endpoपूर्णांक accepts no new data
	 * from its upper layer, but retransmits data to the far end
	 * अगर necessary to fill gaps.
	 */
	काष्ठा sctp_chunk *पात = arg;

	अगर (पात)
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(पात));

	/* Even अगर we can't send the ABORT due to low memory delete the
	 * TCB.  This is a departure from our typical NOMEM handling.
	 */

	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
			SCTP_ERROR(ECONNABORTED));
	/* Delete the established association. */
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_USER_ABORT));

	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);

	वापस SCTP_DISPOSITION_ABORT;
पूर्ण

/* We tried an illegal operation on an association which is बंदd.  */
क्रमागत sctp_disposition sctp_sf_error_बंदd(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_ERROR, SCTP_ERROR(-EINVAL));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* We tried an illegal operation on an association which is shutting
 * करोwn.
 */
क्रमागत sctp_disposition sctp_sf_error_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_ERROR,
			SCTP_ERROR(-ESHUTDOWN));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * sctp_cookie_रुको_prm_shutकरोwn
 *
 * Section: 4 Note: 2
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explicitly address this issue, but is the route through the
 * state table when someone issues a shutकरोwn जबतक in COOKIE_WAIT state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_cookie_रुको_prm_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	SCTP_INC_STATS(net, SCTP_MIB_SHUTDOWNS);

	sctp_add_cmd_sf(commands, SCTP_CMD_DELETE_TCB, SCTP_शून्य());

	वापस SCTP_DISPOSITION_DELETE_TCB;
पूर्ण

/*
 * sctp_cookie_echoed_prm_shutकरोwn
 *
 * Section: 4 Note: 2
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explcitly address this issue, but is the route through the
 * state table when someone issues a shutकरोwn जबतक in COOKIE_ECHOED state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_cookie_echoed_prm_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* There is a single T1 समयr, so we should be able to use
	 * common function with the COOKIE-WAIT state.
	 */
	वापस sctp_sf_cookie_रुको_prm_shutकरोwn(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * sctp_sf_cookie_रुको_prm_पात
 *
 * Section: 4 Note: 2
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explicitly address this issue, but is the route through the
 * state table when someone issues an पात जबतक in COOKIE_WAIT state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_cookie_रुको_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *पात = arg;

	/* Stop T1-init समयr */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));

	अगर (पात)
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(पात));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);

	/* Even अगर we can't send the ABORT due to low memory delete the
	 * TCB.  This is a departure from our typical NOMEM handling.
	 */

	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
			SCTP_ERROR(ECONNREFUSED));
	/* Delete the established association. */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
			SCTP_PERR(SCTP_ERROR_USER_ABORT));

	वापस SCTP_DISPOSITION_ABORT;
पूर्ण

/*
 * sctp_sf_cookie_echoed_prm_पात
 *
 * Section: 4 Note: 3
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explcitly address this issue, but is the route through the
 * state table when someone issues an पात जबतक in COOKIE_ECHOED state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_cookie_echoed_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* There is a single T1 समयr, so we should be able to use
	 * common function with the COOKIE-WAIT state.
	 */
	वापस sctp_sf_cookie_रुको_prm_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * sctp_sf_shutकरोwn_pending_prm_पात
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explicitly address this issue, but is the route through the
 * state table when someone issues an पात जबतक in SHUTDOWN-PENDING state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_pending_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* Stop the T5-shutकरोwn guard समयr.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	वापस sctp_sf_करो_9_1_prm_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * sctp_sf_shutकरोwn_sent_prm_पात
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explicitly address this issue, but is the route through the
 * state table when someone issues an पात जबतक in SHUTDOWN-SENT state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_sent_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* Stop the T2-shutकरोwn समयr.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	/* Stop the T5-shutकरोwn guard समयr.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	वापस sctp_sf_करो_9_1_prm_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * sctp_sf_cookie_echoed_prm_पात
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 * The RFC करोes not explcitly address this issue, but is the route through the
 * state table when someone issues an पात जबतक in COOKIE_ECHOED state.
 *
 * Outमाला_दो
 * (समयrs)
 */
क्रमागत sctp_disposition sctp_sf_shutकरोwn_ack_sent_prm_पात(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	/* The same T2 समयr, so we should be able to use
	 * common function with the SHUTDOWN-SENT state.
	 */
	वापस sctp_sf_shutकरोwn_sent_prm_पात(net, ep, asoc, type, arg, commands);
पूर्ण

/*
 * Process the REQUESTHEARTBEAT primitive
 *
 * 10.1 ULP-to-SCTP
 * J) Request Heartbeat
 *
 * Format: REQUESTHEARTBEAT(association id, destination transport address)
 *
 * -> result
 *
 * Inकाष्ठाs the local endpoपूर्णांक to perक्रमm a HeartBeat on the specअगरied
 * destination transport address of the given association. The वापसed
 * result should indicate whether the transmission of the HEARTBEAT
 * chunk to the destination address is successful.
 *
 * Mandatory attributes:
 *
 * o association id - local handle to the SCTP association
 *
 * o destination transport address - the transport address of the
 *   association on which a heartbeat should be issued.
 */
क्रमागत sctp_disposition sctp_sf_करो_prm_requestheartbeat(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	अगर (SCTP_DISPOSITION_NOMEM == sctp_sf_heartbeat(ep, asoc, type,
				      (काष्ठा sctp_transport *)arg, commands))
		वापस SCTP_DISPOSITION_NOMEM;

	/*
	 * RFC 2960 (bis), section 8.3
	 *
	 *    D) Request an on-demand HEARTBEAT on a specअगरic destination
	 *    transport address of a given association.
	 *
	 *    The endpoपूर्णांक should increment the respective error  counter of
	 *    the destination transport address each समय a HEARTBEAT is sent
	 *    to that address and not acknowledged within one RTO.
	 *
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_HB_SENT,
			SCTP_TRANSPORT(arg));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * ADDIP Section 4.1 ASCONF Chunk Procedures
 * When an endpoपूर्णांक has an ASCONF संकेतed change to be sent to the
 * remote endpoपूर्णांक it should करो A1 to A9
 */
क्रमागत sctp_disposition sctp_sf_करो_prm_asconf(काष्ठा net *net,
					    स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					    स्थिर काष्ठा sctp_association *asoc,
					    स्थिर जोड़ sctp_subtype type,
					    व्योम *arg,
					    काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T4, SCTP_CHUNK(chunk));
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(chunk));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* RE-CONFIG Section 5.1 RECONF Chunk Procedures */
क्रमागत sctp_disposition sctp_sf_करो_prm_reconf(काष्ठा net *net,
					    स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					    स्थिर काष्ठा sctp_association *asoc,
					    स्थिर जोड़ sctp_subtype type,
					    व्योम *arg,
					    काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(chunk));
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Ignore the primitive event
 *
 * The वापस value is the disposition of the primitive.
 */
क्रमागत sctp_disposition sctp_sf_ignore_primitive(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	pr_debug("%s: primitive type:%d is ignored\n", __func__,
		 type.primitive);

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/***************************************************************************
 * These are the state functions क्रम the OTHER events.
 ***************************************************************************/

/*
 * When the SCTP stack has no more user data to send or retransmit, this
 * notअगरication is given to the user. Also, at the समय when a user app
 * subscribes to this event, अगर there is no data to be sent or
 * retransmit, the stack will immediately send up this notअगरication.
 */
क्रमागत sctp_disposition sctp_sf_करो_no_pending_tsn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_ulpevent *event;

	event = sctp_ulpevent_make_sender_dry_event(asoc, GFP_ATOMIC);
	अगर (!event)
		वापस SCTP_DISPOSITION_NOMEM;

	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(event));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Start the shutकरोwn negotiation.
 *
 * From Section 9.2:
 * Once all its outstanding data has been acknowledged, the endpoपूर्णांक
 * shall send a SHUTDOWN chunk to its peer including in the Cumulative
 * TSN Ack field the last sequential TSN it has received from the peer.
 * It shall then start the T2-shutकरोwn समयr and enter the SHUTDOWN-SENT
 * state. If the समयr expires, the endpoपूर्णांक must re-send the SHUTDOWN
 * with the updated last sequential TSN received from its peer.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_start_shutकरोwn(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *reply;

	/* Once all its outstanding data has been acknowledged, the
	 * endpoपूर्णांक shall send a SHUTDOWN chunk to its peer including
	 * in the Cumulative TSN Ack field the last sequential TSN it
	 * has received from the peer.
	 */
	reply = sctp_make_shutकरोwn(asoc, arg);
	अगर (!reply)
		जाओ nomem;

	/* Set the transport क्रम the SHUTDOWN chunk and the समयout क्रम the
	 * T2-shutकरोwn समयr.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* It shall then start the T2-shutकरोwn समयr */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	/* RFC 4960 Section 9.2
	 * The sender of the SHUTDOWN MAY also start an overall guard समयr
	 * 'T5-shutdown-guard' to bound the overall समय क्रम shutकरोwn sequence.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	अगर (asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* and enter the SHUTDOWN-SENT state.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_SENT));

	/* sctp-implguide 2.10 Issues with Heartbeating and failover
	 *
	 * HEARTBEAT ... is disजारीd after sending either SHUTDOWN
	 * or SHUTDOWN-ACK.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_STOP, SCTP_शून्य());

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Generate a SHUTDOWN ACK now that everything is SACK'd.
 *
 * From Section 9.2:
 *
 * If it has no more outstanding DATA chunks, the SHUTDOWN receiver
 * shall send a SHUTDOWN ACK and start a T2-shutकरोwn समयr of its own,
 * entering the SHUTDOWN-ACK-SENT state. If the समयr expires, the
 * endpoपूर्णांक must re-send the SHUTDOWN ACK.
 *
 * The वापस value is the disposition.
 */
क्रमागत sctp_disposition sctp_sf_करो_9_2_shutकरोwn_ack(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = arg;
	काष्ठा sctp_chunk *reply;

	/* There are 2 ways of getting here:
	 *    1) called in response to a SHUTDOWN chunk
	 *    2) called when SCTP_EVENT_NO_PENDING_TSN event is issued.
	 *
	 * For the हाल (2), the arg parameter is set to शून्य.  We need
	 * to check that we have a chunk beक्रमe accessing it's fields.
	 */
	अगर (chunk) अणु
		अगर (!sctp_vtag_verअगरy(chunk, asoc))
			वापस sctp_sf_pdiscard(net, ep, asoc, type, arg,
						commands);

		/* Make sure that the SHUTDOWN chunk has a valid length. */
		अगर (!sctp_chunk_length_valid(
				chunk, माप(काष्ठा sctp_shutकरोwn_chunk)))
			वापस sctp_sf_violation_chunklen(net, ep, asoc, type,
							  arg, commands);
	पूर्ण

	/* If it has no more outstanding DATA chunks, the SHUTDOWN receiver
	 * shall send a SHUTDOWN ACK ...
	 */
	reply = sctp_make_shutकरोwn_ack(asoc, chunk);
	अगर (!reply)
		जाओ nomem;

	/* Set the transport क्रम the SHUTDOWN ACK chunk and the समयout क्रम
	 * the T2-shutकरोwn समयr.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* and start/restart a T2-shutकरोwn समयr of its own, */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	अगर (asoc->समयouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* Enter the SHUTDOWN-ACK-SENT state.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_ACK_SENT));

	/* sctp-implguide 2.10 Issues with Heartbeating and failover
	 *
	 * HEARTBEAT ... is disजारीd after sending either SHUTDOWN
	 * or SHUTDOWN-ACK.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_STOP, SCTP_शून्य());

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * Ignore the event defined as other
 *
 * The वापस value is the disposition of the event.
 */
क्रमागत sctp_disposition sctp_sf_ignore_other(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	pr_debug("%s: the event other type:%d is ignored\n",
		 __func__, type.other);

	वापस SCTP_DISPOSITION_DISCARD;
पूर्ण

/************************************************************
 * These are the state functions क्रम handling समयout events.
 ************************************************************/

/*
 * RTX Timeout
 *
 * Section: 6.3.3 Handle T3-rtx Expiration
 *
 * Whenever the retransmission समयr T3-rtx expires क्रम a destination
 * address, करो the following:
 * [See below]
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_करो_6_3_3_rtx(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_transport *transport = arg;

	SCTP_INC_STATS(net, SCTP_MIB_T3_RTX_EXPIREDS);

	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		अगर (asoc->peer.zero_winकरोw_announced &&
		    asoc->state == SCTP_STATE_SHUTDOWN_PENDING) अणु
			/*
			 * We are here likely because the receiver had its rwnd
			 * बंदd क्रम a जबतक and we have not been able to
			 * transmit the locally queued data within the maximum
			 * retransmission attempts limit.  Start the T5
			 * shutकरोwn guard समयr to give the receiver one last
			 * chance and some additional समय to recover beक्रमe
			 * पातing.
			 */
			sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START_ONCE,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));
		पूर्ण अन्यथा अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
					SCTP_ERROR(ETIMEDOUT));
			/* CMD_ASSOC_FAILED calls CMD_DELETE_TCB. */
			sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
					SCTP_PERR(SCTP_ERROR_NO_ERROR));
			SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
			SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
			वापस SCTP_DISPOSITION_DELETE_TCB;
		पूर्ण
	पूर्ण

	/* E1) For the destination address क्रम which the समयr
	 * expires, adjust its ssthresh with rules defined in Section
	 * 7.2.3 and set the cwnd <- MTU.
	 */

	/* E2) For the destination address क्रम which the समयr
	 * expires, set RTO <- RTO * 2 ("back off the timer").  The
	 * maximum value discussed in rule C7 above (RTO.max) may be
	 * used to provide an upper bound to this करोubling operation.
	 */

	/* E3) Determine how many of the earliest (i.e., lowest TSN)
	 * outstanding DATA chunks क्रम the address क्रम which the
	 * T3-rtx has expired will fit पूर्णांकo a single packet, subject
	 * to the MTU स्थिरraपूर्णांक क्रम the path corresponding to the
	 * destination transport address to which the retransmission
	 * is being sent (this may be dअगरferent from the address क्रम
	 * which the समयr expires [see Section 6.4]).  Call this
	 * value K. Bundle and retransmit those K DATA chunks in a
	 * single packet to the destination endpoपूर्णांक.
	 *
	 * Note: Any DATA chunks that were sent to the address क्रम
	 * which the T3-rtx समयr expired but did not fit in one MTU
	 * (rule E3 above), should be marked क्रम retransmission and
	 * sent as soon as cwnd allows (normally when a SACK arrives).
	 */

	/* Do some failure management (Section 8.2). */
	sctp_add_cmd_sf(commands, SCTP_CMD_STRIKE, SCTP_TRANSPORT(transport));

	/* NB: Rules E4 and F1 are implicit in R1.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_RETRAN, SCTP_TRANSPORT(transport));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * Generate delayed SACK on समयout
 *
 * Section: 6.2  Acknowledgement on Reception of DATA Chunks
 *
 * The guidelines on delayed acknowledgement algorithm specअगरied in
 * Section 4.2 of [RFC2581] SHOULD be followed.  Specअगरically, an
 * acknowledgement SHOULD be generated क्रम at least every second packet
 * (not every second DATA chunk) received, and SHOULD be generated
 * within 200 ms of the arrival of any unacknowledged DATA chunk.  In
 * some situations it may be beneficial क्रम an SCTP transmitter to be
 * more conservative than the algorithms detailed in this करोcument
 * allow. However, an SCTP transmitter MUST NOT be more aggressive than
 * the following algorithms allow.
 */
क्रमागत sctp_disposition sctp_sf_करो_6_2_sack(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  स्थिर जोड़ sctp_subtype type,
					  व्योम *arg,
					  काष्ठा sctp_cmd_seq *commands)
अणु
	SCTP_INC_STATS(net, SCTP_MIB_DELAY_SACK_EXPIREDS);
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * sctp_sf_t1_init_समयr_expire
 *
 * Section: 4 Note: 2
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 *  RFC 2960 Section 4 Notes
 *  2) If the T1-init समयr expires, the endpoपूर्णांक MUST retransmit INIT
 *     and re-start the T1-init समयr without changing state.  This MUST
 *     be repeated up to 'Max.Init.Retransmits' बार.  After that, the
 *     endpoपूर्णांक MUST पात the initialization process and report the
 *     error to SCTP user.
 *
 * Outमाला_दो
 * (समयrs, events)
 *
 */
क्रमागत sctp_disposition sctp_sf_t1_init_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	पूर्णांक attempts = asoc->init_err_counter + 1;
	काष्ठा sctp_chunk *repl = शून्य;
	काष्ठा sctp_bind_addr *bp;

	pr_debug("%s: timer T1 expired (INIT)\n", __func__);

	SCTP_INC_STATS(net, SCTP_MIB_T1_INIT_EXPIREDS);

	अगर (attempts <= asoc->max_init_attempts) अणु
		bp = (काष्ठा sctp_bind_addr *) &asoc->base.bind_addr;
		repl = sctp_make_init(asoc, bp, GFP_ATOMIC, 0);
		अगर (!repl)
			वापस SCTP_DISPOSITION_NOMEM;

		/* Choose transport क्रम INIT. */
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_CHOOSE_TRANSPORT,
				SCTP_CHUNK(repl));

		/* Issue a sideeffect to करो the needed accounting. */
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));

		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
	पूर्ण अन्यथा अणु
		pr_debug("%s: giving up on INIT, attempts:%d "
			 "max_init_attempts:%d\n", __func__, attempts,
			 asoc->max_init_attempts);

		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/*
 * sctp_sf_t1_cookie_समयr_expire
 *
 * Section: 4 Note: 2
 * Verअगरication Tag:
 * Inमाला_दो
 * (endpoपूर्णांक, asoc)
 *
 *  RFC 2960 Section 4 Notes
 *  3) If the T1-cookie समयr expires, the endpoपूर्णांक MUST retransmit
 *     COOKIE ECHO and re-start the T1-cookie समयr without changing
 *     state.  This MUST be repeated up to 'Max.Init.Retransmits' बार.
 *     After that, the endpoपूर्णांक MUST पात the initialization process and
 *     report the error to SCTP user.
 *
 * Outमाला_दो
 * (समयrs, events)
 *
 */
क्रमागत sctp_disposition sctp_sf_t1_cookie_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	पूर्णांक attempts = asoc->init_err_counter + 1;
	काष्ठा sctp_chunk *repl = शून्य;

	pr_debug("%s: timer T1 expired (COOKIE-ECHO)\n", __func__);

	SCTP_INC_STATS(net, SCTP_MIB_T1_COOKIE_EXPIREDS);

	अगर (attempts <= asoc->max_init_attempts) अणु
		repl = sctp_make_cookie_echo(asoc, शून्य);
		अगर (!repl)
			वापस SCTP_DISPOSITION_NOMEM;

		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_CHOOSE_TRANSPORT,
				SCTP_CHUNK(repl));
		/* Issue a sideeffect to करो the needed accounting. */
		sctp_add_cmd_sf(commands, SCTP_CMD_COOKIEECHO_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));

		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
	पूर्ण अन्यथा अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* RFC2960 9.2 If the समयr expires, the endpoपूर्णांक must re-send the SHUTDOWN
 * with the updated last sequential TSN received from its peer.
 *
 * An endpoपूर्णांक should limit the number of retransmissions of the
 * SHUTDOWN chunk to the protocol parameter 'Association.Max.Retrans'.
 * If this threshold is exceeded the endpoपूर्णांक should destroy the TCB and
 * MUST report the peer endpoपूर्णांक unreachable to the upper layer (and
 * thus the association enters the CLOSED state).  The reception of any
 * packet from its peer (i.e. as the peer sends all of its queued DATA
 * chunks) should clear the endpoपूर्णांक's retransmission count and restart
 * the T2-Shutकरोwn समयr,  giving its peer ample opportunity to transmit
 * all of its queued DATA chunks that have not yet been sent.
 */
क्रमागत sctp_disposition sctp_sf_t2_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *reply = शून्य;

	pr_debug("%s: timer T2 expired\n", __func__);

	SCTP_INC_STATS(net, SCTP_MIB_T2_SHUTDOWN_EXPIREDS);

	((काष्ठा sctp_association *)asoc)->shutकरोwn_retries++;

	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		/* Note:  CMD_ASSOC_FAILED calls CMD_DELETE_TCB. */
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_DELETE_TCB;
	पूर्ण

	चयन (asoc->state) अणु
	हाल SCTP_STATE_SHUTDOWN_SENT:
		reply = sctp_make_shutकरोwn(asoc, शून्य);
		अवरोध;

	हाल SCTP_STATE_SHUTDOWN_ACK_SENT:
		reply = sctp_make_shutकरोwn_ack(asoc, शून्य);
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण

	अगर (!reply)
		जाओ nomem;

	/* Do some failure management (Section 8.2).
	 * If we हटाओ the transport an SHUTDOWN was last sent to, करोn't
	 * करो failure management.
	 */
	अगर (asoc->shutकरोwn_last_sent_to)
		sctp_add_cmd_sf(commands, SCTP_CMD_STRIKE,
				SCTP_TRANSPORT(asoc->shutकरोwn_last_sent_to));

	/* Set the transport क्रम the SHUTDOWN/ACK chunk and the समयout क्रम
	 * the T2-shutकरोwn समयr.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* Restart the T2-shutकरोwn समयr.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));
	वापस SCTP_DISPOSITION_CONSUME;

nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/*
 * ADDIP Section 4.1 ASCONF CHunk Procedures
 * If the T4 RTO समयr expires the endpoपूर्णांक should करो B1 to B5
 */
क्रमागत sctp_disposition sctp_sf_t4_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *chunk = asoc->addip_last_asconf;
	काष्ठा sctp_transport *transport = chunk->transport;

	SCTP_INC_STATS(net, SCTP_MIB_T4_RTO_EXPIREDS);

	/* ADDIP 4.1 B1) Increment the error counters and perक्रमm path failure
	 * detection on the appropriate destination address as defined in
	 * RFC2960 [5] section 8.1 and 8.2.
	 */
	अगर (transport)
		sctp_add_cmd_sf(commands, SCTP_CMD_STRIKE,
				SCTP_TRANSPORT(transport));

	/* Reconfig T4 समयr and transport. */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T4, SCTP_CHUNK(chunk));

	/* ADDIP 4.1 B2) Increment the association error counters and perक्रमm
	 * endpoपूर्णांक failure detection on the association as defined in
	 * RFC2960 [5] section 8.1 and 8.2.
	 * association error counter is incremented in SCTP_CMD_STRIKE.
	 */
	अगर (asoc->overall_error_count >= asoc->max_retrans) अणु
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_DISPOSITION_ABORT;
	पूर्ण

	/* ADDIP 4.1 B3) Back-off the destination address RTO value to which
	 * the ASCONF chunk was sent by करोubling the RTO समयr value.
	 * This is करोne in SCTP_CMD_STRIKE.
	 */

	/* ADDIP 4.1 B4) Re-transmit the ASCONF Chunk last sent and अगर possible
	 * choose an alternate destination address (please refer to RFC2960
	 * [5] section 6.4.1). An endpoपूर्णांक MUST NOT add new parameters to this
	 * chunk, it MUST be the same (including its serial number) as the last
	 * ASCONF sent.
	 */
	sctp_chunk_hold(asoc->addip_last_asconf);
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
			SCTP_CHUNK(asoc->addip_last_asconf));

	/* ADDIP 4.1 B5) Restart the T-4 RTO समयr. Note that अगर a dअगरferent
	 * destination is selected, then the RTO used will be that of the new
	 * destination address.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/* sctpimpguide-05 Section 2.12.2
 * The sender of the SHUTDOWN MAY also start an overall guard समयr
 * 'T5-shutdown-guard' to bound the overall समय क्रम shutकरोwn sequence.
 * At the expiration of this समयr the sender SHOULD पात the association
 * by sending an ABORT chunk.
 */
क्रमागत sctp_disposition sctp_sf_t5_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_chunk *reply = शून्य;

	pr_debug("%s: timer T5 expired\n", __func__);

	SCTP_INC_STATS(net, SCTP_MIB_T5_SHUTDOWN_GUARD_EXPIREDS);

	reply = sctp_make_पात(asoc, शून्य, 0);
	अगर (!reply)
		जाओ nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));
	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
			SCTP_ERROR(ETIMEDOUT));
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_NO_ERROR));

	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);

	वापस SCTP_DISPOSITION_DELETE_TCB;
nomem:
	वापस SCTP_DISPOSITION_NOMEM;
पूर्ण

/* Handle expiration of AUTOCLOSE समयr.  When the स्वतःबंद समयr expires,
 * the association is स्वतःmatically बंदd by starting the shutकरोwn process.
 * The work that needs to be करोne is same as when SHUTDOWN is initiated by
 * the user.  So this routine looks same as sctp_sf_करो_9_2_prm_shutकरोwn().
 */
क्रमागत sctp_disposition sctp_sf_स्वतःबंद_समयr_expire(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands)
अणु
	क्रमागत sctp_disposition disposition;

	SCTP_INC_STATS(net, SCTP_MIB_AUTOCLOSE_EXPIREDS);

	/* From 9.2 Shutकरोwn of an Association
	 * Upon receipt of the SHUTDOWN primitive from its upper
	 * layer, the endpoपूर्णांक enters SHUTDOWN-PENDING state and
	 * reमुख्यs there until all outstanding data has been
	 * acknowledged by its peer. The endpoपूर्णांक accepts no new data
	 * from its upper layer, but retransmits data to the far end
	 * अगर necessary to fill gaps.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_PENDING));

	disposition = SCTP_DISPOSITION_CONSUME;
	अगर (sctp_outq_is_empty(&asoc->outqueue)) अणु
		disposition = sctp_sf_करो_9_2_start_shutकरोwn(net, ep, asoc, type,
							    शून्य, commands);
	पूर्ण

	वापस disposition;
पूर्ण

/*****************************************************************************
 * These are sa state functions which could apply to all types of events.
 ****************************************************************************/

/*
 * This table entry is not implemented.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_not_impl(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर जोड़ sctp_subtype type,
				       व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	वापस SCTP_DISPOSITION_NOT_IMPL;
पूर्ण

/*
 * This table entry represents a bug.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_bug(काष्ठा net *net,
				  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				  स्थिर काष्ठा sctp_association *asoc,
				  स्थिर जोड़ sctp_subtype type,
				  व्योम *arg, काष्ठा sctp_cmd_seq *commands)
अणु
	वापस SCTP_DISPOSITION_BUG;
पूर्ण

/*
 * This table entry represents the firing of a समयr in the wrong state.
 * Since समयr deletion cannot be guaranteed a समयr 'may' end up firing
 * when the association is in the wrong state.   This event should
 * be ignored, so as to prevent any rearming of the समयr.
 *
 * Inमाला_दो
 * (endpoपूर्णांक, asoc, chunk)
 *
 * The वापस value is the disposition of the chunk.
 */
क्रमागत sctp_disposition sctp_sf_समयr_ignore(काष्ठा net *net,
					   स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					   स्थिर काष्ठा sctp_association *asoc,
					   स्थिर जोड़ sctp_subtype type,
					   व्योम *arg,
					   काष्ठा sctp_cmd_seq *commands)
अणु
	pr_debug("%s: timer %d ignored\n", __func__, type.chunk);

	वापस SCTP_DISPOSITION_CONSUME;
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* Pull the SACK chunk based on the SACK header. */
अटल काष्ठा sctp_sackhdr *sctp_sm_pull_sack(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_sackhdr *sack;
	__u16 num_dup_tsns;
	अचिन्हित पूर्णांक len;
	__u16 num_blocks;

	/* Protect ourselves from पढ़ोing too far पूर्णांकo
	 * the skb from a bogus sender.
	 */
	sack = (काष्ठा sctp_sackhdr *) chunk->skb->data;

	num_blocks = ntohs(sack->num_gap_ack_blocks);
	num_dup_tsns = ntohs(sack->num_dup_tsns);
	len = माप(काष्ठा sctp_sackhdr);
	len += (num_blocks + num_dup_tsns) * माप(__u32);
	अगर (len > chunk->skb->len)
		वापस शून्य;

	skb_pull(chunk->skb, len);

	वापस sack;
पूर्ण

/* Create an ABORT packet to be sent as a response, with the specअगरied
 * error causes.
 */
अटल काष्ठा sctp_packet *sctp_पात_pkt_new(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					स्थिर व्योम *payload, माप_प्रकार paylen)
अणु
	काष्ठा sctp_packet *packet;
	काष्ठा sctp_chunk *पात;

	packet = sctp_ootb_pkt_new(net, asoc, chunk);

	अगर (packet) अणु
		/* Make an ABORT.
		 * The T bit will be set अगर the asoc is शून्य.
		 */
		पात = sctp_make_पात(asoc, chunk, paylen);
		अगर (!पात) अणु
			sctp_ootb_pkt_मुक्त(packet);
			वापस शून्य;
		पूर्ण

		/* Reflect vtag अगर T-Bit is set */
		अगर (sctp_test_T_bit(पात))
			packet->vtag = ntohl(chunk->sctp_hdr->vtag);

		/* Add specअगरied error causes, i.e., payload, to the
		 * end of the chunk.
		 */
		sctp_addto_chunk(पात, paylen, payload);

		/* Set the skb to the beदीर्घing sock क्रम accounting.  */
		पात->skb->sk = ep->base.sk;

		sctp_packet_append_chunk(packet, पात);

	पूर्ण

	वापस packet;
पूर्ण

/* Allocate a packet क्रम responding in the OOTB conditions.  */
अटल काष्ठा sctp_packet *sctp_ootb_pkt_new(
					काष्ठा net *net,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_packet *packet;
	__u16 sport, dport;
	__u32 vtag;

	/* Get the source and destination port from the inbound packet.  */
	sport = ntohs(chunk->sctp_hdr->dest);
	dport = ntohs(chunk->sctp_hdr->source);

	/* The V-tag is going to be the same as the inbound packet अगर no
	 * association exists, otherwise, use the peer's vtag.
	 */
	अगर (asoc) अणु
		/* Special हाल the INIT-ACK as there is no peer's vtag
		 * yet.
		 */
		चयन (chunk->chunk_hdr->type) अणु
		हाल SCTP_CID_INIT_ACK:
		अणु
			काष्ठा sctp_initack_chunk *initack;

			initack = (काष्ठा sctp_initack_chunk *)chunk->chunk_hdr;
			vtag = ntohl(initack->init_hdr.init_tag);
			अवरोध;
		पूर्ण
		शेष:
			vtag = asoc->peer.i.init_tag;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Special हाल the INIT and stale COOKIE_ECHO as there is no
		 * vtag yet.
		 */
		चयन (chunk->chunk_hdr->type) अणु
		हाल SCTP_CID_INIT:
		अणु
			काष्ठा sctp_init_chunk *init;

			init = (काष्ठा sctp_init_chunk *)chunk->chunk_hdr;
			vtag = ntohl(init->init_hdr.init_tag);
			अवरोध;
		पूर्ण
		शेष:
			vtag = ntohl(chunk->sctp_hdr->vtag);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Make a transport क्रम the bucket, Eliza... */
	transport = sctp_transport_new(net, sctp_source(chunk), GFP_ATOMIC);
	अगर (!transport)
		जाओ nomem;

	transport->encap_port = SCTP_INPUT_CB(chunk->skb)->encap_port;

	/* Cache a route क्रम the transport with the chunk's destination as
	 * the source address.
	 */
	sctp_transport_route(transport, (जोड़ sctp_addr *)&chunk->dest,
			     sctp_sk(net->sctp.ctl_sock));

	packet = &transport->packet;
	sctp_packet_init(packet, transport, sport, dport);
	sctp_packet_config(packet, vtag, 0);

	वापस packet;

nomem:
	वापस शून्य;
पूर्ण

/* Free the packet allocated earlier क्रम responding in the OOTB condition.  */
व्योम sctp_ootb_pkt_मुक्त(काष्ठा sctp_packet *packet)
अणु
	sctp_transport_मुक्त(packet->transport);
पूर्ण

/* Send a stale cookie error when a invalid COOKIE ECHO chunk is found  */
अटल व्योम sctp_send_stale_cookie_err(काष्ठा net *net,
				       स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				       स्थिर काष्ठा sctp_association *asoc,
				       स्थिर काष्ठा sctp_chunk *chunk,
				       काष्ठा sctp_cmd_seq *commands,
				       काष्ठा sctp_chunk *err_chunk)
अणु
	काष्ठा sctp_packet *packet;

	अगर (err_chunk) अणु
		packet = sctp_ootb_pkt_new(net, asoc, chunk);
		अगर (packet) अणु
			काष्ठा sctp_चिन्हित_cookie *cookie;

			/* Override the OOTB vtag from the cookie. */
			cookie = chunk->subh.cookie_hdr;
			packet->vtag = cookie->c.peer_vtag;

			/* Set the skb to the beदीर्घing sock क्रम accounting. */
			err_chunk->skb->sk = ep->base.sk;
			sctp_packet_append_chunk(packet, err_chunk);
			sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
					SCTP_PACKET(packet));
			SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
		पूर्ण अन्यथा
			sctp_chunk_मुक्त (err_chunk);
	पूर्ण
पूर्ण


/* Process a data chunk */
अटल पूर्णांक sctp_eat_data(स्थिर काष्ठा sctp_association *asoc,
			 काष्ठा sctp_chunk *chunk,
			 काष्ठा sctp_cmd_seq *commands)
अणु
	काष्ठा sctp_tsnmap *map = (काष्ठा sctp_tsnmap *)&asoc->peer.tsn_map;
	काष्ठा sock *sk = asoc->base.sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा sctp_datahdr *data_hdr;
	काष्ठा sctp_chunk *err;
	क्रमागत sctp_verb deliver;
	माप_प्रकार datalen;
	__u32 tsn;
	पूर्णांक पंचांगp;

	data_hdr = (काष्ठा sctp_datahdr *)chunk->skb->data;
	chunk->subh.data_hdr = data_hdr;
	skb_pull(chunk->skb, sctp_datahdr_len(&asoc->stream));

	tsn = ntohl(data_hdr->tsn);
	pr_debug("%s: TSN 0x%x\n", __func__, tsn);

	/* ASSERT:  Now skb->data is really the user data.  */

	/* Process ECN based congestion.
	 *
	 * Since the chunk काष्ठाure is reused क्रम all chunks within
	 * a packet, we use ecn_ce_करोne to track अगर we've alपढ़ोy
	 * करोne CE processing क्रम this packet.
	 *
	 * We need to करो ECN processing even अगर we plan to discard the
	 * chunk later.
	 */

	अगर (asoc->peer.ecn_capable && !chunk->ecn_ce_करोne) अणु
		काष्ठा sctp_af *af = SCTP_INPUT_CB(chunk->skb)->af;
		chunk->ecn_ce_करोne = 1;

		अगर (af->is_ce(sctp_gso_headskb(chunk->skb))) अणु
			/* Do real work as sideffect. */
			sctp_add_cmd_sf(commands, SCTP_CMD_ECN_CE,
					SCTP_U32(tsn));
		पूर्ण
	पूर्ण

	पंचांगp = sctp_tsnmap_check(&asoc->peer.tsn_map, tsn);
	अगर (पंचांगp < 0) अणु
		/* The TSN is too high--silently discard the chunk and
		 * count on it getting retransmitted later.
		 */
		अगर (chunk->asoc)
			chunk->asoc->stats.outofseqtsns++;
		वापस SCTP_IERROR_HIGH_TSN;
	पूर्ण अन्यथा अगर (पंचांगp > 0) अणु
		/* This is a duplicate.  Record it.  */
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_DUP, SCTP_U32(tsn));
		वापस SCTP_IERROR_DUP_TSN;
	पूर्ण

	/* This is a new TSN.  */

	/* Discard अगर there is no room in the receive winकरोw.
	 * Actually, allow a little bit of overflow (up to a MTU).
	 */
	datalen = ntohs(chunk->chunk_hdr->length);
	datalen -= sctp_datachk_len(&asoc->stream);

	deliver = SCTP_CMD_CHUNK_ULP;

	/* Think about partial delivery. */
	अगर ((datalen >= asoc->rwnd) && (!asoc->ulpq.pd_mode)) अणु

		/* Even अगर we करोn't accept this chunk there is
		 * memory pressure.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_PART_DELIVER, SCTP_शून्य());
	पूर्ण

	/* Spill over rwnd a little bit.  Note: While allowed, this spill over
	 * seems a bit troublesome in that frag_poपूर्णांक varies based on
	 * PMTU.  In हालs, such as loopback, this might be a rather
	 * large spill over.
	 */
	अगर ((!chunk->data_accepted) && (!asoc->rwnd || asoc->rwnd_over ||
	    (datalen > asoc->rwnd + asoc->frag_poपूर्णांक))) अणु

		/* If this is the next TSN, consider reneging to make
		 * room.   Note: Playing nice with a confused sender.  A
		 * malicious sender can still eat up all our buffer
		 * space and in the future we may want to detect and
		 * करो more drastic reneging.
		 */
		अगर (sctp_tsnmap_has_gap(map) &&
		    (sctp_tsnmap_get_ctsn(map) + 1) == tsn) अणु
			pr_debug("%s: reneging for tsn:%u\n", __func__, tsn);
			deliver = SCTP_CMD_RENEGE;
		पूर्ण अन्यथा अणु
			pr_debug("%s: discard tsn:%u len:%zu, rwnd:%d\n",
				 __func__, tsn, datalen, asoc->rwnd);

			वापस SCTP_IERROR_IGNORE_TSN;
		पूर्ण
	पूर्ण

	/*
	 * Also try to renege to limit our memory usage in the event that
	 * we are under memory pressure
	 * If we can't renege, don't worry about it, the sk_rmem_schedule
	 * in sctp_ulpevent_make_rcvmsg will drop the frame अगर we grow our
	 * memory usage too much
	 */
	अगर (sk_under_memory_pressure(sk)) अणु
		अगर (sctp_tsnmap_has_gap(map) &&
		    (sctp_tsnmap_get_ctsn(map) + 1) == tsn) अणु
			pr_debug("%s: under pressure, reneging for tsn:%u\n",
				 __func__, tsn);
			deliver = SCTP_CMD_RENEGE;
		पूर्ण अन्यथा अणु
			sk_mem_reclaim(sk);
		पूर्ण
	पूर्ण

	/*
	 * Section 3.3.10.9 No User Data (9)
	 *
	 * Cause of error
	 * ---------------
	 * No User Data:  This error cause is वापसed to the originator of a
	 * DATA chunk अगर a received DATA chunk has no user data.
	 */
	अगर (unlikely(0 == datalen)) अणु
		err = sctp_make_पात_no_data(asoc, chunk, tsn);
		अगर (err) अणु
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err));
		पूर्ण
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET, SCTP_शून्य());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_DATA));
		SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
		वापस SCTP_IERROR_NO_DATA;
	पूर्ण

	chunk->data_accepted = 1;

	/* Note: Some chunks may get overcounted (अगर we drop) or overcounted
	 * अगर we renege and the chunk arrives again.
	 */
	अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) अणु
		SCTP_INC_STATS(net, SCTP_MIB_INUNORDERCHUNKS);
		अगर (chunk->asoc)
			chunk->asoc->stats.iuodchunks++;
	पूर्ण अन्यथा अणु
		SCTP_INC_STATS(net, SCTP_MIB_INORDERCHUNKS);
		अगर (chunk->asoc)
			chunk->asoc->stats.iodchunks++;
	पूर्ण

	/* RFC 2960 6.5 Stream Identअगरier and Stream Sequence Number
	 *
	 * If an endpoपूर्णांक receive a DATA chunk with an invalid stream
	 * identअगरier, it shall acknowledge the reception of the DATA chunk
	 * following the normal procedure, immediately send an ERROR chunk
	 * with cause set to "Invalid Stream Identifier" (See Section 3.3.10)
	 * and discard the DATA chunk.
	 */
	अगर (ntohs(data_hdr->stream) >= asoc->stream.incnt) अणु
		/* Mark tsn as received even though we drop it */
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_TSN, SCTP_U32(tsn));

		err = sctp_make_op_error(asoc, chunk, SCTP_ERROR_INV_STRM,
					 &data_hdr->stream,
					 माप(data_hdr->stream),
					 माप(u16));
		अगर (err)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err));
		वापस SCTP_IERROR_BAD_STREAM;
	पूर्ण

	/* Check to see अगर the SSN is possible क्रम this TSN.
	 * The biggest gap we can record is 4K wide.  Since SSNs wrap
	 * at an अचिन्हित लघु, there is no way that an SSN can
	 * wrap and क्रम a valid TSN.  We can simply check अगर the current
	 * SSN is smaller then the next expected one.  If it is, it wrapped
	 * and is invalid.
	 */
	अगर (!asoc->stream.si->validate_data(chunk))
		वापस SCTP_IERROR_PROTO_VIOLATION;

	/* Send the data up to the user.  Note:  Schedule  the
	 * SCTP_CMD_CHUNK_ULP cmd beक्रमe the SCTP_CMD_GEN_SACK, as the SACK
	 * chunk needs the updated rwnd.
	 */
	sctp_add_cmd_sf(commands, deliver, SCTP_CHUNK(chunk));

	वापस SCTP_IERROR_NO_ERROR;
पूर्ण
