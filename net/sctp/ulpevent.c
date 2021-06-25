<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * These functions manipulate an sctp event.   The काष्ठा ulpevent is used
 * to carry notअगरications and data to the ULP (sockets).
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sctp/काष्ठाs.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

अटल व्योम sctp_ulpevent_receive_data(काष्ठा sctp_ulpevent *event,
				       काष्ठा sctp_association *asoc);
अटल व्योम sctp_ulpevent_release_data(काष्ठा sctp_ulpevent *event);
अटल व्योम sctp_ulpevent_release_frag_data(काष्ठा sctp_ulpevent *event);


/* Initialize an ULP event from an given skb.  */
अटल व्योम sctp_ulpevent_init(काष्ठा sctp_ulpevent *event,
			       __u16 msg_flags,
			       अचिन्हित पूर्णांक len)
अणु
	स_रखो(event, 0, माप(काष्ठा sctp_ulpevent));
	event->msg_flags = msg_flags;
	event->rmem_len = len;
पूर्ण

/* Create a new sctp_ulpevent.  */
अटल काष्ठा sctp_ulpevent *sctp_ulpevent_new(पूर्णांक size, __u16 msg_flags,
					       gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(size, gfp);
	अगर (!skb)
		जाओ fail;

	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, msg_flags, skb->truesize);

	वापस event;

fail:
	वापस शून्य;
पूर्ण

/* Is this a MSG_NOTIFICATION?  */
पूर्णांक sctp_ulpevent_is_notअगरication(स्थिर काष्ठा sctp_ulpevent *event)
अणु
	वापस MSG_NOTIFICATION == (event->msg_flags & MSG_NOTIFICATION);
पूर्ण

/* Hold the association in हाल the msg_name needs पढ़ो out of
 * the association.
 */
अटल अंतरभूत व्योम sctp_ulpevent_set_owner(काष्ठा sctp_ulpevent *event,
					   स्थिर काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_chunk *chunk = event->chunk;
	काष्ठा sk_buff *skb;

	/* Cast away the स्थिर, as we are just wanting to
	 * bump the reference count.
	 */
	sctp_association_hold((काष्ठा sctp_association *)asoc);
	skb = sctp_event2skb(event);
	event->asoc = (काष्ठा sctp_association *)asoc;
	atomic_add(event->rmem_len, &event->asoc->rmem_alloc);
	sctp_skb_set_owner_r(skb, asoc->base.sk);
	अगर (chunk && chunk->head_skb && !chunk->head_skb->sk)
		chunk->head_skb->sk = asoc->base.sk;
पूर्ण

/* A simple deकाष्ठाor to give up the reference to the association. */
अटल अंतरभूत व्योम sctp_ulpevent_release_owner(काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_association *asoc = event->asoc;

	atomic_sub(event->rmem_len, &asoc->rmem_alloc);
	sctp_association_put(asoc);
पूर्ण

/* Create and initialize an SCTP_ASSOC_CHANGE event.
 *
 * 5.3.1.1 SCTP_ASSOC_CHANGE
 *
 * Communication notअगरications inक्रमm the ULP that an SCTP association
 * has either begun or ended. The identअगरier क्रम a new association is
 * provided by this notअगरication.
 *
 * Note: There is no field checking here.  If a field is unused it will be
 * zero'd out.
 */
काष्ठा sctp_ulpevent  *sctp_ulpevent_make_assoc_change(
	स्थिर काष्ठा sctp_association *asoc,
	__u16 flags, __u16 state, __u16 error, __u16 outbound,
	__u16 inbound, काष्ठा sctp_chunk *chunk, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_assoc_change *sac;
	काष्ठा sk_buff *skb;

	/* If the lower layer passed in the chunk, it will be
	 * an ABORT, so we need to include it in the sac_info.
	 */
	अगर (chunk) अणु
		/* Copy the chunk data to a new skb and reserve enough
		 * head room to use as notअगरication.
		 */
		skb = skb_copy_expand(chunk->skb,
				      माप(काष्ठा sctp_assoc_change), 0, gfp);

		अगर (!skb)
			जाओ fail;

		/* Embed the event fields inside the cloned skb.  */
		event = sctp_skb2event(skb);
		sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

		/* Include the notअगरication काष्ठाure */
		sac = skb_push(skb, माप(काष्ठा sctp_assoc_change));

		/* Trim the buffer to the right length.  */
		skb_trim(skb, माप(काष्ठा sctp_assoc_change) +
			 ntohs(chunk->chunk_hdr->length) -
			 माप(काष्ठा sctp_chunkhdr));
	पूर्ण अन्यथा अणु
		event = sctp_ulpevent_new(माप(काष्ठा sctp_assoc_change),
				  MSG_NOTIFICATION, gfp);
		अगर (!event)
			जाओ fail;

		skb = sctp_event2skb(event);
		sac = skb_put(skb, माप(काष्ठा sctp_assoc_change));
	पूर्ण

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_type:
	 * It should be SCTP_ASSOC_CHANGE.
	 */
	sac->sac_type = SCTP_ASSOC_CHANGE;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_state: 32 bits (चिन्हित पूर्णांकeger)
	 * This field holds one of a number of values that communicate the
	 * event that happened to the association.
	 */
	sac->sac_state = state;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_flags: 16 bits (अचिन्हित पूर्णांकeger)
	 * Currently unused.
	 */
	sac->sac_flags = 0;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_length: माप (__u32)
	 * This field is the total length of the notअगरication data, including
	 * the notअगरication header.
	 */
	sac->sac_length = skb->len;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_error:  32 bits (चिन्हित पूर्णांकeger)
	 *
	 * If the state was reached due to a error condition (e.g.
	 * COMMUNICATION_LOST) any relevant error inक्रमmation is available in
	 * this field. This corresponds to the protocol error codes defined in
	 * [SCTP].
	 */
	sac->sac_error = error;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_outbound_streams:  16 bits (अचिन्हित पूर्णांकeger)
	 * sac_inbound_streams:  16 bits (अचिन्हित पूर्णांकeger)
	 *
	 * The maximum number of streams allowed in each direction are
	 * available in sac_outbound_streams and sac_inbound streams.
	 */
	sac->sac_outbound_streams = outbound;
	sac->sac_inbound_streams = inbound;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_assoc_id: माप (sctp_assoc_t)
	 *
	 * The association id field, holds the identअगरier क्रम the association.
	 * All notअगरications क्रम a given association have the same association
	 * identअगरier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	sac->sac_assoc_id = sctp_assoc2id(asoc);

	वापस event;

fail:
	वापस शून्य;
पूर्ण

/* Create and initialize an SCTP_PEER_ADDR_CHANGE event.
 *
 * Socket Extensions क्रम SCTP - draft-01
 * 5.3.1.2 SCTP_PEER_ADDR_CHANGE
 *
 * When a destination address on a multi-homed peer encounters a change
 * an पूर्णांकerface details event is sent.
 */
अटल काष्ठा sctp_ulpevent *sctp_ulpevent_make_peer_addr_change(
	स्थिर काष्ठा sctp_association *asoc,
	स्थिर काष्ठा sockaddr_storage *aaddr,
	पूर्णांक flags, पूर्णांक state, पूर्णांक error, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_paddr_change  *spc;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_paddr_change),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		जाओ fail;

	skb = sctp_event2skb(event);
	spc = skb_put(skb, माप(काष्ठा sctp_paddr_change));

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_type:
	 *
	 *    It should be SCTP_PEER_ADDR_CHANGE.
	 */
	spc->spc_type = SCTP_PEER_ADDR_CHANGE;

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_length: माप (__u32)
	 *
	 * This field is the total length of the notअगरication data, including
	 * the notअगरication header.
	 */
	spc->spc_length = माप(काष्ठा sctp_paddr_change);

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_flags: 16 bits (अचिन्हित पूर्णांकeger)
	 * Currently unused.
	 */
	spc->spc_flags = 0;

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_state:  32 bits (चिन्हित पूर्णांकeger)
	 *
	 * This field holds one of a number of values that communicate the
	 * event that happened to the address.
	 */
	spc->spc_state = state;

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_error:  32 bits (चिन्हित पूर्णांकeger)
	 *
	 * If the state was reached due to any error condition (e.g.
	 * ADDRESS_UNREACHABLE) any relevant error inक्रमmation is available in
	 * this field.
	 */
	spc->spc_error = error;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * spc_assoc_id: माप (sctp_assoc_t)
	 *
	 * The association id field, holds the identअगरier क्रम the association.
	 * All notअगरications क्रम a given association have the same association
	 * identअगरier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	spc->spc_assoc_id = sctp_assoc2id(asoc);

	/* Sockets API Extensions क्रम SCTP
	 * Section 5.3.1.2 SCTP_PEER_ADDR_CHANGE
	 *
	 * spc_aaddr: माप (काष्ठा sockaddr_storage)
	 *
	 * The affected address field, holds the remote peer's address that is
	 * encountering the change of state.
	 */
	स_नकल(&spc->spc_aaddr, aaddr, माप(काष्ठा sockaddr_storage));

	/* Map ipv4 address पूर्णांकo v4-mapped-on-v6 address.  */
	sctp_get_pf_specअगरic(asoc->base.sk->sk_family)->addr_to_user(
					sctp_sk(asoc->base.sk),
					(जोड़ sctp_addr *)&spc->spc_aaddr);

	वापस event;

fail:
	वापस शून्य;
पूर्ण

व्योम sctp_ulpevent_notअगरy_peer_addr_change(काष्ठा sctp_transport *transport,
					   पूर्णांक state, पूर्णांक error)
अणु
	काष्ठा sctp_association *asoc = transport->asoc;
	काष्ठा sockaddr_storage addr;
	काष्ठा sctp_ulpevent *event;

	अगर (asoc->state < SCTP_STATE_ESTABLISHED)
		वापस;

	स_रखो(&addr, 0, माप(काष्ठा sockaddr_storage));
	स_नकल(&addr, &transport->ipaddr, transport->af_specअगरic->sockaddr_len);

	event = sctp_ulpevent_make_peer_addr_change(asoc, &addr, 0, state,
						    error, GFP_ATOMIC);
	अगर (event)
		asoc->stream.si->enqueue_event(&asoc->ulpq, event);
पूर्ण

/* Create and initialize an SCTP_REMOTE_ERROR notअगरication.
 *
 * Note: This assumes that the chunk->skb->data alपढ़ोy poपूर्णांकs to the
 * operation error payload.
 *
 * Socket Extensions क्रम SCTP - draft-01
 * 5.3.1.3 SCTP_REMOTE_ERROR
 *
 * A remote peer may send an Operational Error message to its peer.
 * This message indicates a variety of error conditions on an
 * association. The entire error TLV as it appears on the wire is
 * included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP
 * specअगरication [SCTP] and any extensions क्रम a list of possible
 * error क्रमmats.
 */
काष्ठा sctp_ulpevent *
sctp_ulpevent_make_remote_error(स्थिर काष्ठा sctp_association *asoc,
				काष्ठा sctp_chunk *chunk, __u16 flags,
				gfp_t gfp)
अणु
	काष्ठा sctp_remote_error *sre;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_errhdr *ch;
	काष्ठा sk_buff *skb;
	__be16 cause;
	पूर्णांक elen;

	ch = (काष्ठा sctp_errhdr *)(chunk->skb->data);
	cause = ch->cause;
	elen = SCTP_PAD4(ntohs(ch->length)) - माप(*ch);

	/* Pull off the ERROR header.  */
	skb_pull(chunk->skb, माप(*ch));

	/* Copy the skb to a new skb with room क्रम us to prepend
	 * notअगरication with.
	 */
	skb = skb_copy_expand(chunk->skb, माप(*sre), 0, gfp);

	/* Pull off the rest of the cause TLV from the chunk.  */
	skb_pull(chunk->skb, elen);
	अगर (!skb)
		जाओ fail;

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	sre = skb_push(skb, माप(*sre));

	/* Trim the buffer to the right length.  */
	skb_trim(skb, माप(*sre) + elen);

	/* RFC6458, Section 6.1.3. SCTP_REMOTE_ERROR */
	स_रखो(sre, 0, माप(*sre));
	sre->sre_type = SCTP_REMOTE_ERROR;
	sre->sre_flags = 0;
	sre->sre_length = skb->len;
	sre->sre_error = cause;
	sctp_ulpevent_set_owner(event, asoc);
	sre->sre_assoc_id = sctp_assoc2id(asoc);

	वापस event;
fail:
	वापस शून्य;
पूर्ण

/* Create and initialize a SCTP_SEND_FAILED notअगरication.
 *
 * Socket Extensions क्रम SCTP - draft-01
 * 5.3.1.4 SCTP_SEND_FAILED
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_send_failed(
	स्थिर काष्ठा sctp_association *asoc, काष्ठा sctp_chunk *chunk,
	__u16 flags, __u32 error, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_send_failed *ssf;
	काष्ठा sk_buff *skb;

	/* Pull off any padding. */
	पूर्णांक len = ntohs(chunk->chunk_hdr->length);

	/* Make skb with more room so we can prepend notअगरication.  */
	skb = skb_copy_expand(chunk->skb,
			      माप(काष्ठा sctp_send_failed), /* headroom */
			      0,                               /* tailroom */
			      gfp);
	अगर (!skb)
		जाओ fail;

	/* Pull off the common chunk header and DATA header.  */
	skb_pull(skb, sctp_datachk_len(&asoc->stream));
	len -= sctp_datachk_len(&asoc->stream);

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	ssf = skb_push(skb, माप(काष्ठा sctp_send_failed));

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_type:
	 * It should be SCTP_SEND_FAILED.
	 */
	ssf->ssf_type = SCTP_SEND_FAILED;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_flags: 16 bits (अचिन्हित पूर्णांकeger)
	 * The flag value will take one of the following values
	 *
	 * SCTP_DATA_UNSENT - Indicates that the data was never put on
	 *                    the wire.
	 *
	 * SCTP_DATA_SENT   - Indicates that the data was put on the wire.
	 *                    Note that this करोes not necessarily mean that the
	 *                    data was (or was not) successfully delivered.
	 */
	ssf->ssf_flags = flags;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_length: माप (__u32)
	 * This field is the total length of the notअगरication data, including
	 * the notअगरication header.
	 */
	ssf->ssf_length = माप(काष्ठा sctp_send_failed) + len;
	skb_trim(skb, ssf->ssf_length);

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_error: 16 bits (अचिन्हित पूर्णांकeger)
	 * This value represents the reason why the send failed, and अगर set,
	 * will be a SCTP protocol error code as defined in [SCTP] section
	 * 3.3.10.
	 */
	ssf->ssf_error = error;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_info: माप (काष्ठा sctp_sndrcvinfo)
	 * The original send inक्रमmation associated with the undelivered
	 * message.
	 */
	स_नकल(&ssf->ssf_info, &chunk->sinfo, माप(काष्ठा sctp_sndrcvinfo));

	/* Per TSVWG discussion with Randy. Allow the application to
	 * reassemble a fragmented message.
	 */
	ssf->ssf_info.sinfo_flags = chunk->chunk_hdr->flags;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_assoc_id: माप (sctp_assoc_t)
	 * The association id field, sf_assoc_id, holds the identअगरier क्रम the
	 * association.  All notअगरications क्रम a given association have the
	 * same association identअगरier.  For TCP style socket, this field is
	 * ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	ssf->ssf_assoc_id = sctp_assoc2id(asoc);
	वापस event;

fail:
	वापस शून्य;
पूर्ण

काष्ठा sctp_ulpevent *sctp_ulpevent_make_send_failed_event(
	स्थिर काष्ठा sctp_association *asoc, काष्ठा sctp_chunk *chunk,
	__u16 flags, __u32 error, gfp_t gfp)
अणु
	काष्ठा sctp_send_failed_event *ssf;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	skb = skb_copy_expand(chunk->skb, माप(*ssf), 0, gfp);
	अगर (!skb)
		वापस शून्य;

	len = ntohs(chunk->chunk_hdr->length);
	len -= sctp_datachk_len(&asoc->stream);

	skb_pull(skb, sctp_datachk_len(&asoc->stream));
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	ssf = skb_push(skb, माप(*ssf));
	ssf->ssf_type = SCTP_SEND_FAILED_EVENT;
	ssf->ssf_flags = flags;
	ssf->ssf_length = माप(*ssf) + len;
	skb_trim(skb, ssf->ssf_length);
	ssf->ssf_error = error;

	ssf->ssfe_info.snd_sid = chunk->sinfo.sinfo_stream;
	ssf->ssfe_info.snd_ppid = chunk->sinfo.sinfo_ppid;
	ssf->ssfe_info.snd_context = chunk->sinfo.sinfo_context;
	ssf->ssfe_info.snd_assoc_id = chunk->sinfo.sinfo_assoc_id;
	ssf->ssfe_info.snd_flags = chunk->chunk_hdr->flags;

	sctp_ulpevent_set_owner(event, asoc);
	ssf->ssf_assoc_id = sctp_assoc2id(asoc);

	वापस event;
पूर्ण

/* Create and initialize a SCTP_SHUTDOWN_EVENT notअगरication.
 *
 * Socket Extensions क्रम SCTP - draft-01
 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_shutकरोwn_event(
	स्थिर काष्ठा sctp_association *asoc,
	__u16 flags, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_shutकरोwn_event *sse;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_shutकरोwn_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		जाओ fail;

	skb = sctp_event2skb(event);
	sse = skb_put(skb, माप(काष्ठा sctp_shutकरोwn_event));

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_type
	 * It should be SCTP_SHUTDOWN_EVENT
	 */
	sse->sse_type = SCTP_SHUTDOWN_EVENT;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_flags: 16 bits (अचिन्हित पूर्णांकeger)
	 * Currently unused.
	 */
	sse->sse_flags = 0;

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_length: माप (__u32)
	 * This field is the total length of the notअगरication data, including
	 * the notअगरication header.
	 */
	sse->sse_length = माप(काष्ठा sctp_shutकरोwn_event);

	/* Socket Extensions क्रम SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_assoc_id: माप (sctp_assoc_t)
	 * The association id field, holds the identअगरier क्रम the association.
	 * All notअगरications क्रम a given association have the same association
	 * identअगरier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	sse->sse_assoc_id = sctp_assoc2id(asoc);

	वापस event;

fail:
	वापस शून्य;
पूर्ण

/* Create and initialize a SCTP_ADAPTATION_INDICATION notअगरication.
 *
 * Socket Extensions क्रम SCTP
 * 5.3.1.6 SCTP_ADAPTATION_INDICATION
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_adaptation_indication(
	स्थिर काष्ठा sctp_association *asoc, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_adaptation_event *sai;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_adaptation_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		जाओ fail;

	skb = sctp_event2skb(event);
	sai = skb_put(skb, माप(काष्ठा sctp_adaptation_event));

	sai->sai_type = SCTP_ADAPTATION_INDICATION;
	sai->sai_flags = 0;
	sai->sai_length = माप(काष्ठा sctp_adaptation_event);
	sai->sai_adaptation_ind = asoc->peer.adaptation_ind;
	sctp_ulpevent_set_owner(event, asoc);
	sai->sai_assoc_id = sctp_assoc2id(asoc);

	वापस event;

fail:
	वापस शून्य;
पूर्ण

/* A message has been received.  Package this message as a notअगरication
 * to pass it to the upper layers.  Go ahead and calculate the sndrcvinfo
 * even अगर filtered out later.
 *
 * Socket Extensions क्रम SCTP
 * 5.2.2 SCTP Header Inक्रमmation Structure (SCTP_SNDRCV)
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_rcvmsg(काष्ठा sctp_association *asoc,
						काष्ठा sctp_chunk *chunk,
						gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event = शून्य;
	काष्ठा sk_buff *skb = chunk->skb;
	काष्ठा sock *sk = asoc->base.sk;
	माप_प्रकार padding, datalen;
	पूर्णांक rx_count;

	/*
	 * check to see अगर we need to make space क्रम this
	 * new skb, expand the rcvbuffer अगर needed, or drop
	 * the frame
	 */
	अगर (asoc->ep->rcvbuf_policy)
		rx_count = atomic_पढ़ो(&asoc->rmem_alloc);
	अन्यथा
		rx_count = atomic_पढ़ो(&sk->sk_rmem_alloc);

	datalen = ntohs(chunk->chunk_hdr->length);

	अगर (rx_count >= sk->sk_rcvbuf || !sk_rmem_schedule(sk, skb, datalen))
		जाओ fail;

	/* Clone the original skb, sharing the data.  */
	skb = skb_clone(chunk->skb, gfp);
	अगर (!skb)
		जाओ fail;

	/* Now that all memory allocations क्रम this chunk succeeded, we
	 * can mark it as received so the tsn_map is updated correctly.
	 */
	अगर (sctp_tsnmap_mark(&asoc->peer.tsn_map,
			     ntohl(chunk->subh.data_hdr->tsn),
			     chunk->transport))
		जाओ fail_mark;

	/* First calculate the padding, so we करोn't inadvertently
	 * pass up the wrong length to the user.
	 *
	 * RFC 2960 - Section 3.2  Chunk Field Descriptions
	 *
	 * The total length of a chunk(including Type, Length and Value fields)
	 * MUST be a multiple of 4 bytes.  If the length of the chunk is not a
	 * multiple of 4 bytes, the sender MUST pad the chunk with all zero
	 * bytes and this padding is not included in the chunk length field.
	 * The sender should never pad with more than 3 bytes.  The receiver
	 * MUST ignore the padding bytes.
	 */
	padding = SCTP_PAD4(datalen) - datalen;

	/* Fixup cloned skb with just this chunks data.  */
	skb_trim(skb, chunk->chunk_end - padding - skb->data);

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);

	/* Initialize event with flags 0  and correct length
	 * Since this is a clone of the original skb, only account क्रम
	 * the data of this chunk as other chunks will be accounted separately.
	 */
	sctp_ulpevent_init(event, 0, skb->len + माप(काष्ठा sk_buff));

	/* And hold the chunk as we need it क्रम getting the IP headers
	 * later in recvmsg
	 */
	sctp_chunk_hold(chunk);
	event->chunk = chunk;

	sctp_ulpevent_receive_data(event, asoc);

	event->stream = ntohs(chunk->subh.data_hdr->stream);
	अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) अणु
		event->flags |= SCTP_UNORDERED;
		event->cumtsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	पूर्ण
	event->tsn = ntohl(chunk->subh.data_hdr->tsn);
	event->msg_flags |= chunk->chunk_hdr->flags;

	वापस event;

fail_mark:
	kमुक्त_skb(skb);
fail:
	वापस शून्य;
पूर्ण

/* Create a partial delivery related event.
 *
 * 5.3.1.7 SCTP_PARTIAL_DELIVERY_EVENT
 *
 *   When a receiver is engaged in a partial delivery of a
 *   message this notअगरication will be used to indicate
 *   various events.
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_pdapi(
					स्थिर काष्ठा sctp_association *asoc,
					__u32 indication, __u32 sid, __u32 seq,
					__u32 flags, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_pdapi_event *pd;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_pdapi_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		जाओ fail;

	skb = sctp_event2skb(event);
	pd = skb_put(skb, माप(काष्ठा sctp_pdapi_event));

	/* pdapi_type
	 *   It should be SCTP_PARTIAL_DELIVERY_EVENT
	 *
	 * pdapi_flags: 16 bits (अचिन्हित पूर्णांकeger)
	 *   Currently unused.
	 */
	pd->pdapi_type = SCTP_PARTIAL_DELIVERY_EVENT;
	pd->pdapi_flags = flags;
	pd->pdapi_stream = sid;
	pd->pdapi_seq = seq;

	/* pdapi_length: 32 bits (अचिन्हित पूर्णांकeger)
	 *
	 * This field is the total length of the notअगरication data, including
	 * the notअगरication header.  It will generally be माप (काष्ठा
	 * sctp_pdapi_event).
	 */
	pd->pdapi_length = माप(काष्ठा sctp_pdapi_event);

	/*  pdapi_indication: 32 bits (अचिन्हित पूर्णांकeger)
	 *
	 * This field holds the indication being sent to the application.
	 */
	pd->pdapi_indication = indication;

	/*  pdapi_assoc_id: माप (sctp_assoc_t)
	 *
	 * The association id field, holds the identअगरier क्रम the association.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	pd->pdapi_assoc_id = sctp_assoc2id(asoc);

	वापस event;
fail:
	वापस शून्य;
पूर्ण

काष्ठा sctp_ulpevent *sctp_ulpevent_make_authkey(
	स्थिर काष्ठा sctp_association *asoc, __u16 key_id,
	__u32 indication, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_authkey_event *ak;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_authkey_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		जाओ fail;

	skb = sctp_event2skb(event);
	ak = skb_put(skb, माप(काष्ठा sctp_authkey_event));

	ak->auth_type = SCTP_AUTHENTICATION_EVENT;
	ak->auth_flags = 0;
	ak->auth_length = माप(काष्ठा sctp_authkey_event);

	ak->auth_keynumber = key_id;
	ak->auth_altkeynumber = 0;
	ak->auth_indication = indication;

	/*
	 * The association id field, holds the identअगरier क्रम the association.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	ak->auth_assoc_id = sctp_assoc2id(asoc);

	वापस event;
fail:
	वापस शून्य;
पूर्ण

/*
 * Socket Extensions क्रम SCTP
 * 6.3.10. SCTP_SENDER_DRY_EVENT
 */
काष्ठा sctp_ulpevent *sctp_ulpevent_make_sender_dry_event(
	स्थिर काष्ठा sctp_association *asoc, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_sender_dry_event *sdry;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_sender_dry_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		वापस शून्य;

	skb = sctp_event2skb(event);
	sdry = skb_put(skb, माप(काष्ठा sctp_sender_dry_event));

	sdry->sender_dry_type = SCTP_SENDER_DRY_EVENT;
	sdry->sender_dry_flags = 0;
	sdry->sender_dry_length = माप(काष्ठा sctp_sender_dry_event);
	sctp_ulpevent_set_owner(event, asoc);
	sdry->sender_dry_assoc_id = sctp_assoc2id(asoc);

	वापस event;
पूर्ण

काष्ठा sctp_ulpevent *sctp_ulpevent_make_stream_reset_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags, __u16 stream_num,
	__be16 *stream_list, gfp_t gfp)
अणु
	काष्ठा sctp_stream_reset_event *sreset;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;
	पूर्णांक length, i;

	length = माप(काष्ठा sctp_stream_reset_event) + 2 * stream_num;
	event = sctp_ulpevent_new(length, MSG_NOTIFICATION, gfp);
	अगर (!event)
		वापस शून्य;

	skb = sctp_event2skb(event);
	sreset = skb_put(skb, length);

	sreset->strreset_type = SCTP_STREAM_RESET_EVENT;
	sreset->strreset_flags = flags;
	sreset->strreset_length = length;
	sctp_ulpevent_set_owner(event, asoc);
	sreset->strreset_assoc_id = sctp_assoc2id(asoc);

	क्रम (i = 0; i < stream_num; i++)
		sreset->strreset_stream_list[i] = ntohs(stream_list[i]);

	वापस event;
पूर्ण

काष्ठा sctp_ulpevent *sctp_ulpevent_make_assoc_reset_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags, __u32 local_tsn,
	__u32 remote_tsn, gfp_t gfp)
अणु
	काष्ठा sctp_assoc_reset_event *areset;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_assoc_reset_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		वापस शून्य;

	skb = sctp_event2skb(event);
	areset = skb_put(skb, माप(काष्ठा sctp_assoc_reset_event));

	areset->assocreset_type = SCTP_ASSOC_RESET_EVENT;
	areset->assocreset_flags = flags;
	areset->assocreset_length = माप(काष्ठा sctp_assoc_reset_event);
	sctp_ulpevent_set_owner(event, asoc);
	areset->assocreset_assoc_id = sctp_assoc2id(asoc);
	areset->assocreset_local_tsn = local_tsn;
	areset->assocreset_remote_tsn = remote_tsn;

	वापस event;
पूर्ण

काष्ठा sctp_ulpevent *sctp_ulpevent_make_stream_change_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags,
	__u32 strchange_instrms, __u32 strchange_outstrms, gfp_t gfp)
अणु
	काष्ठा sctp_stream_change_event *schange;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;

	event = sctp_ulpevent_new(माप(काष्ठा sctp_stream_change_event),
				  MSG_NOTIFICATION, gfp);
	अगर (!event)
		वापस शून्य;

	skb = sctp_event2skb(event);
	schange = skb_put(skb, माप(काष्ठा sctp_stream_change_event));

	schange->strchange_type = SCTP_STREAM_CHANGE_EVENT;
	schange->strchange_flags = flags;
	schange->strchange_length = माप(काष्ठा sctp_stream_change_event);
	sctp_ulpevent_set_owner(event, asoc);
	schange->strchange_assoc_id = sctp_assoc2id(asoc);
	schange->strchange_instrms = strchange_instrms;
	schange->strchange_outstrms = strchange_outstrms;

	वापस event;
पूर्ण

/* Return the notअगरication type, assuming this is a notअगरication
 * event.
 */
__u16 sctp_ulpevent_get_notअगरication_type(स्थिर काष्ठा sctp_ulpevent *event)
अणु
	जोड़ sctp_notअगरication *notअगरication;
	काष्ठा sk_buff *skb;

	skb = sctp_event2skb(event);
	notअगरication = (जोड़ sctp_notअगरication *) skb->data;
	वापस notअगरication->sn_header.sn_type;
पूर्ण

/* RFC6458, Section 5.3.2. SCTP Header Inक्रमmation Structure
 * (SCTP_SNDRCV, DEPRECATED)
 */
व्योम sctp_ulpevent_पढ़ो_sndrcvinfo(स्थिर काष्ठा sctp_ulpevent *event,
				   काष्ठा msghdr *msghdr)
अणु
	काष्ठा sctp_sndrcvinfo sinfo;

	अगर (sctp_ulpevent_is_notअगरication(event))
		वापस;

	स_रखो(&sinfo, 0, माप(sinfo));
	sinfo.sinfo_stream = event->stream;
	sinfo.sinfo_ssn = event->ssn;
	sinfo.sinfo_ppid = event->ppid;
	sinfo.sinfo_flags = event->flags;
	sinfo.sinfo_tsn = event->tsn;
	sinfo.sinfo_cumtsn = event->cumtsn;
	sinfo.sinfo_assoc_id = sctp_assoc2id(event->asoc);
	/* Context value that is set via SCTP_CONTEXT socket option. */
	sinfo.sinfo_context = event->asoc->शेष_rcv_context;
	/* These fields are not used जबतक receiving. */
	sinfo.sinfo_समयtolive = 0;

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_SNDRCV,
		 माप(sinfo), &sinfo);
पूर्ण

/* RFC6458, Section 5.3.5 SCTP Receive Inक्रमmation Structure
 * (SCTP_SNDRCV)
 */
व्योम sctp_ulpevent_पढ़ो_rcvinfo(स्थिर काष्ठा sctp_ulpevent *event,
				काष्ठा msghdr *msghdr)
अणु
	काष्ठा sctp_rcvinfo rinfo;

	अगर (sctp_ulpevent_is_notअगरication(event))
		वापस;

	स_रखो(&rinfo, 0, माप(काष्ठा sctp_rcvinfo));
	rinfo.rcv_sid = event->stream;
	rinfo.rcv_ssn = event->ssn;
	rinfo.rcv_ppid = event->ppid;
	rinfo.rcv_flags = event->flags;
	rinfo.rcv_tsn = event->tsn;
	rinfo.rcv_cumtsn = event->cumtsn;
	rinfo.rcv_assoc_id = sctp_assoc2id(event->asoc);
	rinfo.rcv_context = event->asoc->शेष_rcv_context;

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_RCVINFO,
		 माप(rinfo), &rinfo);
पूर्ण

/* RFC6458, Section 5.3.6. SCTP Next Receive Inक्रमmation Structure
 * (SCTP_NXTINFO)
 */
अटल व्योम __sctp_ulpevent_पढ़ो_nxtinfo(स्थिर काष्ठा sctp_ulpevent *event,
					 काष्ठा msghdr *msghdr,
					 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_nxtinfo nxtinfo;

	स_रखो(&nxtinfo, 0, माप(nxtinfo));
	nxtinfo.nxt_sid = event->stream;
	nxtinfo.nxt_ppid = event->ppid;
	nxtinfo.nxt_flags = event->flags;
	अगर (sctp_ulpevent_is_notअगरication(event))
		nxtinfo.nxt_flags |= SCTP_NOTIFICATION;
	nxtinfo.nxt_length = skb->len;
	nxtinfo.nxt_assoc_id = sctp_assoc2id(event->asoc);

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_NXTINFO,
		 माप(nxtinfo), &nxtinfo);
पूर्ण

व्योम sctp_ulpevent_पढ़ो_nxtinfo(स्थिर काष्ठा sctp_ulpevent *event,
				काष्ठा msghdr *msghdr,
				काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = sctp_skb_recv_datagram(sk, MSG_PEEK, 1, &err);
	अगर (skb != शून्य) अणु
		__sctp_ulpevent_पढ़ो_nxtinfo(sctp_skb2event(skb),
					     msghdr, skb);
		/* Just release refcount here. */
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/* Do accounting क्रम bytes received and hold a reference to the association
 * क्रम each skb.
 */
अटल व्योम sctp_ulpevent_receive_data(काष्ठा sctp_ulpevent *event,
				       काष्ठा sctp_association *asoc)
अणु
	काष्ठा sk_buff *skb, *frag;

	skb = sctp_event2skb(event);
	/* Set the owner and अक्षरge rwnd क्रम bytes received.  */
	sctp_ulpevent_set_owner(event, asoc);
	sctp_assoc_rwnd_decrease(asoc, skb_headlen(skb));

	अगर (!skb->data_len)
		वापस;

	/* Note:  Not clearing the entire event काष्ठा as this is just a
	 * fragment of the real event.  However, we still need to करो rwnd
	 * accounting.
	 * In general, the skb passed from IP can have only 1 level of
	 * fragments. But we allow multiple levels of fragments.
	 */
	skb_walk_frags(skb, frag)
		sctp_ulpevent_receive_data(sctp_skb2event(frag), asoc);
पूर्ण

/* Do accounting क्रम bytes just पढ़ो by user and release the references to
 * the association.
 */
अटल व्योम sctp_ulpevent_release_data(काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *skb, *frag;
	अचिन्हित पूर्णांक	len;

	/* Current stack काष्ठाures assume that the rcv buffer is
	 * per socket.   For UDP style sockets this is not true as
	 * multiple associations may be on a single UDP-style socket.
	 * Use the local निजी area of the skb to track the owning
	 * association.
	 */

	skb = sctp_event2skb(event);
	len = skb->len;

	अगर (!skb->data_len)
		जाओ करोne;

	/* Don't क्रमget the fragments. */
	skb_walk_frags(skb, frag) अणु
		/* NOTE:  skb_shinfos are recursive. Although IP वापसs
		 * skb's with only 1 level of fragments, SCTP reassembly can
		 * increase the levels.
		 */
		sctp_ulpevent_release_frag_data(sctp_skb2event(frag));
	पूर्ण

करोne:
	sctp_assoc_rwnd_increase(event->asoc, len);
	sctp_chunk_put(event->chunk);
	sctp_ulpevent_release_owner(event);
पूर्ण

अटल व्योम sctp_ulpevent_release_frag_data(काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *skb, *frag;

	skb = sctp_event2skb(event);

	अगर (!skb->data_len)
		जाओ करोne;

	/* Don't क्रमget the fragments. */
	skb_walk_frags(skb, frag) अणु
		/* NOTE:  skb_shinfos are recursive. Although IP वापसs
		 * skb's with only 1 level of fragments, SCTP reassembly can
		 * increase the levels.
		 */
		sctp_ulpevent_release_frag_data(sctp_skb2event(frag));
	पूर्ण

करोne:
	sctp_chunk_put(event->chunk);
	sctp_ulpevent_release_owner(event);
पूर्ण

/* Free a ulpevent that has an owner.  It includes releasing the reference
 * to the owner, updating the rwnd in हाल of a DATA event and मुक्तing the
 * skb.
 */
व्योम sctp_ulpevent_मुक्त(काष्ठा sctp_ulpevent *event)
अणु
	अगर (sctp_ulpevent_is_notअगरication(event))
		sctp_ulpevent_release_owner(event);
	अन्यथा
		sctp_ulpevent_release_data(event);

	kमुक्त_skb(sctp_event2skb(event));
पूर्ण

/* Purge the skb lists holding ulpevents. */
अचिन्हित पूर्णांक sctp_queue_purge_ulpevents(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक data_unपढ़ो = 0;

	जबतक ((skb = skb_dequeue(list)) != शून्य) अणु
		काष्ठा sctp_ulpevent *event = sctp_skb2event(skb);

		अगर (!sctp_ulpevent_is_notअगरication(event))
			data_unपढ़ो += skb->len;

		sctp_ulpevent_मुक्त(event);
	पूर्ण

	वापस data_unपढ़ो;
पूर्ण
