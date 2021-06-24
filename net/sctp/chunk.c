<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2003, 2004
 *
 * This file is part of the SCTP kernel implementation
 *
 * This file contains the code relating the chunk असलtraction.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* This file is mostly in anticipation of future work, but initially
 * populate with fragment tracking क्रम an outbound message.
 */

/* Initialize datamsg from memory. */
अटल व्योम sctp_datamsg_init(काष्ठा sctp_datamsg *msg)
अणु
	refcount_set(&msg->refcnt, 1);
	msg->send_failed = 0;
	msg->send_error = 0;
	msg->can_delay = 1;
	msg->abanकरोned = 0;
	msg->expires_at = 0;
	INIT_LIST_HEAD(&msg->chunks);
पूर्ण

/* Allocate and initialize datamsg. */
अटल काष्ठा sctp_datamsg *sctp_datamsg_new(gfp_t gfp)
अणु
	काष्ठा sctp_datamsg *msg;
	msg = kदो_स्मृति(माप(काष्ठा sctp_datamsg), gfp);
	अगर (msg) अणु
		sctp_datamsg_init(msg);
		SCTP_DBG_OBJCNT_INC(datamsg);
	पूर्ण
	वापस msg;
पूर्ण

व्योम sctp_datamsg_मुक्त(काष्ठा sctp_datamsg *msg)
अणु
	काष्ठा sctp_chunk *chunk;

	/* This करोesn't have to be a _safe vairant because
	 * sctp_chunk_मुक्त() only drops the refs.
	 */
	list_क्रम_each_entry(chunk, &msg->chunks, frag_list)
		sctp_chunk_मुक्त(chunk);

	sctp_datamsg_put(msg);
पूर्ण

/* Final deकाष्ठाruction of datamsg memory. */
अटल व्योम sctp_datamsg_destroy(काष्ठा sctp_datamsg *msg)
अणु
	काष्ठा sctp_association *asoc = शून्य;
	काष्ठा list_head *pos, *temp;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_ulpevent *ev;
	पूर्णांक error, sent;

	/* Release all references. */
	list_क्रम_each_safe(pos, temp, &msg->chunks) अणु
		list_del_init(pos);
		chunk = list_entry(pos, काष्ठा sctp_chunk, frag_list);

		अगर (!msg->send_failed) अणु
			sctp_chunk_put(chunk);
			जारी;
		पूर्ण

		asoc = chunk->asoc;
		error = msg->send_error ?: asoc->outqueue.error;
		sent = chunk->has_tsn ? SCTP_DATA_SENT : SCTP_DATA_UNSENT;

		अगर (sctp_ulpevent_type_enabled(asoc->subscribe,
					       SCTP_SEND_FAILED)) अणु
			ev = sctp_ulpevent_make_send_failed(asoc, chunk, sent,
							    error, GFP_ATOMIC);
			अगर (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		पूर्ण

		अगर (sctp_ulpevent_type_enabled(asoc->subscribe,
					       SCTP_SEND_FAILED_EVENT)) अणु
			ev = sctp_ulpevent_make_send_failed_event(asoc, chunk,
								  sent, error,
								  GFP_ATOMIC);
			अगर (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		पूर्ण

		sctp_chunk_put(chunk);
	पूर्ण

	SCTP_DBG_OBJCNT_DEC(datamsg);
	kमुक्त(msg);
पूर्ण

/* Hold a reference. */
अटल व्योम sctp_datamsg_hold(काष्ठा sctp_datamsg *msg)
अणु
	refcount_inc(&msg->refcnt);
पूर्ण

/* Release a reference. */
व्योम sctp_datamsg_put(काष्ठा sctp_datamsg *msg)
अणु
	अगर (refcount_dec_and_test(&msg->refcnt))
		sctp_datamsg_destroy(msg);
पूर्ण

/* Assign a chunk to this datamsg. */
अटल व्योम sctp_datamsg_assign(काष्ठा sctp_datamsg *msg, काष्ठा sctp_chunk *chunk)
अणु
	sctp_datamsg_hold(msg);
	chunk->msg = msg;
पूर्ण


/* A data chunk can have a maximum payload of (2^16 - 20).  Break
 * करोwn any such message पूर्णांकo smaller chunks.  Opportunistically, fragment
 * the chunks करोwn to the current MTU स्थिरraपूर्णांकs.  We may get refragmented
 * later अगर the PMTU changes, but it is _much better_ to fragment immediately
 * with a reasonable guess than always करोing our fragmentation on the
 * soft-पूर्णांकerrupt.
 */
काष्ठा sctp_datamsg *sctp_datamsg_from_user(काष्ठा sctp_association *asoc,
					    काष्ठा sctp_sndrcvinfo *sinfo,
					    काष्ठा iov_iter *from)
अणु
	माप_प्रकार len, first_len, max_data, reमुख्यing;
	माप_प्रकार msg_len = iov_iter_count(from);
	काष्ठा sctp_shared_key *shkey = शून्य;
	काष्ठा list_head *pos, *temp;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_datamsg *msg;
	पूर्णांक err;

	msg = sctp_datamsg_new(GFP_KERNEL);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);

	/* Note: Calculate this outside of the loop, so that all fragments
	 * have the same expiration.
	 */
	अगर (asoc->peer.prsctp_capable && sinfo->sinfo_समयtolive &&
	    (SCTP_PR_TTL_ENABLED(sinfo->sinfo_flags) ||
	     !SCTP_PR_POLICY(sinfo->sinfo_flags)))
		msg->expires_at = jअगरfies +
				  msecs_to_jअगरfies(sinfo->sinfo_समयtolive);

	/* This is the biggest possible DATA chunk that can fit पूर्णांकo
	 * the packet
	 */
	max_data = asoc->frag_poपूर्णांक;
	अगर (unlikely(!max_data)) अणु
		max_data = sctp_min_frag_poपूर्णांक(sctp_sk(asoc->base.sk),
					       sctp_datachk_len(&asoc->stream));
		pr_warn_ratelimited("%s: asoc:%p frag_point is zero, forcing max_data to default minimum (%zu)",
				    __func__, asoc, max_data);
	पूर्ण

	/* If the peer requested that we authenticate DATA chunks
	 * we need to account क्रम bundling of the AUTH chunks aदीर्घ with
	 * DATA.
	 */
	अगर (sctp_auth_send_cid(SCTP_CID_DATA, asoc)) अणु
		काष्ठा sctp_hmac *hmac_desc = sctp_auth_asoc_get_hmac(asoc);

		अगर (hmac_desc)
			max_data -= SCTP_PAD4(माप(काष्ठा sctp_auth_chunk) +
					      hmac_desc->hmac_len);

		अगर (sinfo->sinfo_tsn &&
		    sinfo->sinfo_ssn != asoc->active_key_id) अणु
			shkey = sctp_auth_get_shkey(asoc, sinfo->sinfo_ssn);
			अगर (!shkey) अणु
				err = -EINVAL;
				जाओ errout;
			पूर्ण
		पूर्ण अन्यथा अणु
			shkey = asoc->shkey;
		पूर्ण
	पूर्ण

	/* Set first_len and then account क्रम possible bundles on first frag */
	first_len = max_data;

	/* Check to see अगर we have a pending SACK and try to let it be bundled
	 * with this message.  Do this अगर we करोn't have any data queued alपढ़ोy.
	 * To check that, look at out_qlen and retransmit list.
	 * NOTE: we will not reduce to account क्रम SACK, अगर the message would
	 * not have been fragmented.
	 */
	अगर (समयr_pending(&asoc->समयrs[SCTP_EVENT_TIMEOUT_SACK]) &&
	    asoc->outqueue.out_qlen == 0 &&
	    list_empty(&asoc->outqueue.retransmit) &&
	    msg_len > max_data)
		first_len -= SCTP_PAD4(माप(काष्ठा sctp_sack_chunk));

	/* Encourage Cookie-ECHO bundling. */
	अगर (asoc->state < SCTP_STATE_COOKIE_ECHOED)
		first_len -= SCTP_ARBITRARY_COOKIE_ECHO_LEN;

	/* Account क्रम a dअगरferent sized first fragment */
	अगर (msg_len >= first_len) अणु
		msg->can_delay = 0;
		अगर (msg_len > first_len)
			SCTP_INC_STATS(asoc->base.net,
				       SCTP_MIB_FRAGUSRMSGS);
	पूर्ण अन्यथा अणु
		/* Which may be the only one... */
		first_len = msg_len;
	पूर्ण

	/* Create chunks क्रम all DATA chunks. */
	क्रम (reमुख्यing = msg_len; reमुख्यing; reमुख्यing -= len) अणु
		u8 frag = SCTP_DATA_MIDDLE_FRAG;

		अगर (reमुख्यing == msg_len) अणु
			/* First frag, which may also be the last */
			frag |= SCTP_DATA_FIRST_FRAG;
			len = first_len;
		पूर्ण अन्यथा अणु
			/* Middle frags */
			len = max_data;
		पूर्ण

		अगर (len >= reमुख्यing) अणु
			/* Last frag, which may also be the first */
			len = reमुख्यing;
			frag |= SCTP_DATA_LAST_FRAG;

			/* The application requests to set the I-bit of the
			 * last DATA chunk of a user message when providing
			 * the user message to the SCTP implementation.
			 */
			अगर ((sinfo->sinfo_flags & SCTP_खातापूर्ण) ||
			    (sinfo->sinfo_flags & SCTP_SACK_IMMEDIATELY))
				frag |= SCTP_DATA_SACK_IMM;
		पूर्ण

		chunk = asoc->stream.si->make_datafrag(asoc, sinfo, len, frag,
						       GFP_KERNEL);
		अगर (!chunk) अणु
			err = -ENOMEM;
			जाओ errout;
		पूर्ण

		err = sctp_user_addto_chunk(chunk, len, from);
		अगर (err < 0)
			जाओ errout_chunk_मुक्त;

		chunk->shkey = shkey;

		/* Put the chunk->skb back पूर्णांकo the क्रमm expected by send.  */
		__skb_pull(chunk->skb, (__u8 *)chunk->chunk_hdr -
				       chunk->skb->data);

		sctp_datamsg_assign(msg, chunk);
		list_add_tail(&chunk->frag_list, &msg->chunks);
	पूर्ण

	वापस msg;

errout_chunk_मुक्त:
	sctp_chunk_मुक्त(chunk);

errout:
	list_क्रम_each_safe(pos, temp, &msg->chunks) अणु
		list_del_init(pos);
		chunk = list_entry(pos, काष्ठा sctp_chunk, frag_list);
		sctp_chunk_मुक्त(chunk);
	पूर्ण
	sctp_datamsg_put(msg);

	वापस ERR_PTR(err);
पूर्ण

/* Check whether this message has expired. */
पूर्णांक sctp_chunk_abanकरोned(काष्ठा sctp_chunk *chunk)
अणु
	अगर (!chunk->asoc->peer.prsctp_capable)
		वापस 0;

	अगर (chunk->msg->abanकरोned)
		वापस 1;

	अगर (!chunk->has_tsn &&
	    !(chunk->chunk_hdr->flags & SCTP_DATA_FIRST_FRAG))
		वापस 0;

	अगर (SCTP_PR_TTL_ENABLED(chunk->sinfo.sinfo_flags) &&
	    समय_after(jअगरfies, chunk->msg->expires_at)) अणु
		काष्ठा sctp_stream_out *streamout =
			SCTP_SO(&chunk->asoc->stream,
				chunk->sinfo.sinfo_stream);

		अगर (chunk->sent_count) अणु
			chunk->asoc->abanकरोned_sent[SCTP_PR_INDEX(TTL)]++;
			streamout->ext->abanकरोned_sent[SCTP_PR_INDEX(TTL)]++;
		पूर्ण अन्यथा अणु
			chunk->asoc->abanकरोned_unsent[SCTP_PR_INDEX(TTL)]++;
			streamout->ext->abanकरोned_unsent[SCTP_PR_INDEX(TTL)]++;
		पूर्ण
		chunk->msg->abanकरोned = 1;
		वापस 1;
	पूर्ण अन्यथा अगर (SCTP_PR_RTX_ENABLED(chunk->sinfo.sinfo_flags) &&
		   chunk->sent_count > chunk->sinfo.sinfo_समयtolive) अणु
		काष्ठा sctp_stream_out *streamout =
			SCTP_SO(&chunk->asoc->stream,
				chunk->sinfo.sinfo_stream);

		chunk->asoc->abanकरोned_sent[SCTP_PR_INDEX(RTX)]++;
		streamout->ext->abanकरोned_sent[SCTP_PR_INDEX(RTX)]++;
		chunk->msg->abanकरोned = 1;
		वापस 1;
	पूर्ण अन्यथा अगर (!SCTP_PR_POLICY(chunk->sinfo.sinfo_flags) &&
		   chunk->msg->expires_at &&
		   समय_after(jअगरfies, chunk->msg->expires_at)) अणु
		chunk->msg->abanकरोned = 1;
		वापस 1;
	पूर्ण
	/* PRIO policy is processed by sendmsg, not here */

	वापस 0;
पूर्ण

/* This chunk (and consequently entire message) has failed in its sending. */
व्योम sctp_chunk_fail(काष्ठा sctp_chunk *chunk, पूर्णांक error)
अणु
	chunk->msg->send_failed = 1;
	chunk->msg->send_error = error;
पूर्ण
