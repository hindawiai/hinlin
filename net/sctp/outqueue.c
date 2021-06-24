<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2003 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions implement the sctp_outq class.   The outqueue handles
 * bundling and queueing of outgoing SCTP chunks.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Perry Melange         <pmelange@null.cc.uic.edu>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Hui Huang 	    <hui.huang@nokia.com>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/list.h>   /* For काष्ठा list_head */
#समावेश <linux/socket.h>
#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>	  /* For skb_set_owner_w */

#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/stream_sched.h>
#समावेश <trace/events/sctp.h>

/* Declare पूर्णांकernal functions here.  */
अटल पूर्णांक sctp_acked(काष्ठा sctp_sackhdr *sack, __u32 tsn);
अटल व्योम sctp_check_transmitted(काष्ठा sctp_outq *q,
				   काष्ठा list_head *transmitted_queue,
				   काष्ठा sctp_transport *transport,
				   जोड़ sctp_addr *saddr,
				   काष्ठा sctp_sackhdr *sack,
				   __u32 *highest_new_tsn);

अटल व्योम sctp_mark_missing(काष्ठा sctp_outq *q,
			      काष्ठा list_head *transmitted_queue,
			      काष्ठा sctp_transport *transport,
			      __u32 highest_new_tsn,
			      पूर्णांक count_of_newacks);

अटल व्योम sctp_outq_flush(काष्ठा sctp_outq *q, पूर्णांक rtx_समयout, gfp_t gfp);

/* Add data to the front of the queue. */
अटल अंतरभूत व्योम sctp_outq_head_data(काष्ठा sctp_outq *q,
				       काष्ठा sctp_chunk *ch)
अणु
	काष्ठा sctp_stream_out_ext *oute;
	__u16 stream;

	list_add(&ch->list, &q->out_chunk_list);
	q->out_qlen += ch->skb->len;

	stream = sctp_chunk_stream_no(ch);
	oute = SCTP_SO(&q->asoc->stream, stream)->ext;
	list_add(&ch->stream_list, &oute->outq);
पूर्ण

/* Take data from the front of the queue. */
अटल अंतरभूत काष्ठा sctp_chunk *sctp_outq_dequeue_data(काष्ठा sctp_outq *q)
अणु
	वापस q->sched->dequeue(q);
पूर्ण

/* Add data chunk to the end of the queue. */
अटल अंतरभूत व्योम sctp_outq_tail_data(काष्ठा sctp_outq *q,
				       काष्ठा sctp_chunk *ch)
अणु
	काष्ठा sctp_stream_out_ext *oute;
	__u16 stream;

	list_add_tail(&ch->list, &q->out_chunk_list);
	q->out_qlen += ch->skb->len;

	stream = sctp_chunk_stream_no(ch);
	oute = SCTP_SO(&q->asoc->stream, stream)->ext;
	list_add_tail(&ch->stream_list, &oute->outq);
पूर्ण

/*
 * SFR-CACC algorithm:
 * D) If count_of_newacks is greater than or equal to 2
 * and t was not sent to the current primary then the
 * sender MUST NOT increment missing report count क्रम t.
 */
अटल अंतरभूत पूर्णांक sctp_cacc_skip_3_1_d(काष्ठा sctp_transport *primary,
				       काष्ठा sctp_transport *transport,
				       पूर्णांक count_of_newacks)
अणु
	अगर (count_of_newacks >= 2 && transport != primary)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * SFR-CACC algorithm:
 * F) If count_of_newacks is less than 2, let d be the
 * destination to which t was sent. If cacc_saw_newack
 * is 0 क्रम destination d, then the sender MUST NOT
 * increment missing report count क्रम t.
 */
अटल अंतरभूत पूर्णांक sctp_cacc_skip_3_1_f(काष्ठा sctp_transport *transport,
				       पूर्णांक count_of_newacks)
अणु
	अगर (count_of_newacks < 2 &&
			(transport && !transport->cacc.cacc_saw_newack))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * SFR-CACC algorithm:
 * 3.1) If CYCLING_CHANGEOVER is 0, the sender SHOULD
 * execute steps C, D, F.
 *
 * C has been implemented in sctp_outq_sack
 */
अटल अंतरभूत पूर्णांक sctp_cacc_skip_3_1(काष्ठा sctp_transport *primary,
				     काष्ठा sctp_transport *transport,
				     पूर्णांक count_of_newacks)
अणु
	अगर (!primary->cacc.cycling_changeover) अणु
		अगर (sctp_cacc_skip_3_1_d(primary, transport, count_of_newacks))
			वापस 1;
		अगर (sctp_cacc_skip_3_1_f(transport, count_of_newacks))
			वापस 1;
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * SFR-CACC algorithm:
 * 3.2) Else अगर CYCLING_CHANGEOVER is 1, and t is less
 * than next_tsn_at_change of the current primary, then
 * the sender MUST NOT increment missing report count
 * क्रम t.
 */
अटल अंतरभूत पूर्णांक sctp_cacc_skip_3_2(काष्ठा sctp_transport *primary, __u32 tsn)
अणु
	अगर (primary->cacc.cycling_changeover &&
	    TSN_lt(tsn, primary->cacc.next_tsn_at_change))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * SFR-CACC algorithm:
 * 3) If the missing report count क्रम TSN t is to be
 * incremented according to [RFC2960] and
 * [SCTP_STEWART-2002], and CHANGEOVER_ACTIVE is set,
 * then the sender MUST further execute steps 3.1 and
 * 3.2 to determine अगर the missing report count क्रम
 * TSN t SHOULD NOT be incremented.
 *
 * 3.3) If 3.1 and 3.2 करो not dictate that the missing
 * report count क्रम t should not be incremented, then
 * the sender SHOULD increment missing report count क्रम
 * t (according to [RFC2960] and [SCTP_STEWART_2002]).
 */
अटल अंतरभूत पूर्णांक sctp_cacc_skip(काष्ठा sctp_transport *primary,
				 काष्ठा sctp_transport *transport,
				 पूर्णांक count_of_newacks,
				 __u32 tsn)
अणु
	अगर (primary->cacc.changeover_active &&
	    (sctp_cacc_skip_3_1(primary, transport, count_of_newacks) ||
	     sctp_cacc_skip_3_2(primary, tsn)))
		वापस 1;
	वापस 0;
पूर्ण

/* Initialize an existing sctp_outq.  This करोes the boring stuff.
 * You still need to define handlers अगर you really want to DO
 * something with this काष्ठाure...
 */
व्योम sctp_outq_init(काष्ठा sctp_association *asoc, काष्ठा sctp_outq *q)
अणु
	स_रखो(q, 0, माप(काष्ठा sctp_outq));

	q->asoc = asoc;
	INIT_LIST_HEAD(&q->out_chunk_list);
	INIT_LIST_HEAD(&q->control_chunk_list);
	INIT_LIST_HEAD(&q->retransmit);
	INIT_LIST_HEAD(&q->sacked);
	INIT_LIST_HEAD(&q->abanकरोned);
	sctp_sched_set_sched(asoc, sctp_sk(asoc->base.sk)->शेष_ss);
पूर्ण

/* Free the outqueue काष्ठाure and any related pending chunks.
 */
अटल व्योम __sctp_outq_tearकरोwn(काष्ठा sctp_outq *q)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा list_head *lchunk, *temp;
	काष्ठा sctp_chunk *chunk, *पंचांगp;

	/* Throw away unacknowledged chunks. */
	list_क्रम_each_entry(transport, &q->asoc->peer.transport_addr_list,
			transports) अणु
		जबतक ((lchunk = sctp_list_dequeue(&transport->transmitted)) != शून्य) अणु
			chunk = list_entry(lchunk, काष्ठा sctp_chunk,
					   transmitted_list);
			/* Mark as part of a failed message. */
			sctp_chunk_fail(chunk, q->error);
			sctp_chunk_मुक्त(chunk);
		पूर्ण
	पूर्ण

	/* Throw away chunks that have been gap ACKed.  */
	list_क्रम_each_safe(lchunk, temp, &q->sacked) अणु
		list_del_init(lchunk);
		chunk = list_entry(lchunk, काष्ठा sctp_chunk,
				   transmitted_list);
		sctp_chunk_fail(chunk, q->error);
		sctp_chunk_मुक्त(chunk);
	पूर्ण

	/* Throw away any chunks in the retransmit queue. */
	list_क्रम_each_safe(lchunk, temp, &q->retransmit) अणु
		list_del_init(lchunk);
		chunk = list_entry(lchunk, काष्ठा sctp_chunk,
				   transmitted_list);
		sctp_chunk_fail(chunk, q->error);
		sctp_chunk_मुक्त(chunk);
	पूर्ण

	/* Throw away any chunks that are in the abanकरोned queue. */
	list_क्रम_each_safe(lchunk, temp, &q->abanकरोned) अणु
		list_del_init(lchunk);
		chunk = list_entry(lchunk, काष्ठा sctp_chunk,
				   transmitted_list);
		sctp_chunk_fail(chunk, q->error);
		sctp_chunk_मुक्त(chunk);
	पूर्ण

	/* Throw away any leftover data chunks. */
	जबतक ((chunk = sctp_outq_dequeue_data(q)) != शून्य) अणु
		sctp_sched_dequeue_करोne(q, chunk);

		/* Mark as send failure. */
		sctp_chunk_fail(chunk, q->error);
		sctp_chunk_मुक्त(chunk);
	पूर्ण

	/* Throw away any leftover control chunks. */
	list_क्रम_each_entry_safe(chunk, पंचांगp, &q->control_chunk_list, list) अणु
		list_del_init(&chunk->list);
		sctp_chunk_मुक्त(chunk);
	पूर्ण
पूर्ण

व्योम sctp_outq_tearकरोwn(काष्ठा sctp_outq *q)
अणु
	__sctp_outq_tearकरोwn(q);
	sctp_outq_init(q->asoc, q);
पूर्ण

/* Free the outqueue काष्ठाure and any related pending chunks.  */
व्योम sctp_outq_मुक्त(काष्ठा sctp_outq *q)
अणु
	/* Throw away leftover chunks. */
	__sctp_outq_tearकरोwn(q);
पूर्ण

/* Put a new chunk in an sctp_outq.  */
व्योम sctp_outq_tail(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *chunk, gfp_t gfp)
अणु
	काष्ठा net *net = q->asoc->base.net;

	pr_debug("%s: outq:%p, chunk:%p[%s]\n", __func__, q, chunk,
		 chunk && chunk->chunk_hdr ?
		 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdr->type)) :
		 "illegal chunk");

	/* If it is data, queue it up, otherwise, send it
	 * immediately.
	 */
	अगर (sctp_chunk_is_data(chunk)) अणु
		pr_debug("%s: outqueueing: outq:%p, chunk:%p[%s])\n",
			 __func__, q, chunk, chunk && chunk->chunk_hdr ?
			 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdr->type)) :
			 "illegal chunk");

		sctp_outq_tail_data(q, chunk);
		अगर (chunk->asoc->peer.prsctp_capable &&
		    SCTP_PR_PRIO_ENABLED(chunk->sinfo.sinfo_flags))
			chunk->asoc->sent_cnt_removable++;
		अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
			SCTP_INC_STATS(net, SCTP_MIB_OUTUNORDERCHUNKS);
		अन्यथा
			SCTP_INC_STATS(net, SCTP_MIB_OUTORDERCHUNKS);
	पूर्ण अन्यथा अणु
		list_add_tail(&chunk->list, &q->control_chunk_list);
		SCTP_INC_STATS(net, SCTP_MIB_OUTCTRLCHUNKS);
	पूर्ण

	अगर (!q->cork)
		sctp_outq_flush(q, 0, gfp);
पूर्ण

/* Insert a chunk पूर्णांकo the sorted list based on the TSNs.  The retransmit list
 * and the abanकरोned list are in ascending order.
 */
अटल व्योम sctp_insert_list(काष्ठा list_head *head, काष्ठा list_head *new)
अणु
	काष्ठा list_head *pos;
	काष्ठा sctp_chunk *nchunk, *lchunk;
	__u32 ntsn, ltsn;
	पूर्णांक करोne = 0;

	nchunk = list_entry(new, काष्ठा sctp_chunk, transmitted_list);
	ntsn = ntohl(nchunk->subh.data_hdr->tsn);

	list_क्रम_each(pos, head) अणु
		lchunk = list_entry(pos, काष्ठा sctp_chunk, transmitted_list);
		ltsn = ntohl(lchunk->subh.data_hdr->tsn);
		अगर (TSN_lt(ntsn, ltsn)) अणु
			list_add(new, pos->prev);
			करोne = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!करोne)
		list_add_tail(new, head);
पूर्ण

अटल पूर्णांक sctp_prsctp_prune_sent(काष्ठा sctp_association *asoc,
				  काष्ठा sctp_sndrcvinfo *sinfo,
				  काष्ठा list_head *queue, पूर्णांक msg_len)
अणु
	काष्ठा sctp_chunk *chk, *temp;

	list_क्रम_each_entry_safe(chk, temp, queue, transmitted_list) अणु
		काष्ठा sctp_stream_out *streamout;

		अगर (!chk->msg->abanकरोned &&
		    (!SCTP_PR_PRIO_ENABLED(chk->sinfo.sinfo_flags) ||
		     chk->sinfo.sinfo_समयtolive <= sinfo->sinfo_समयtolive))
			जारी;

		chk->msg->abanकरोned = 1;
		list_del_init(&chk->transmitted_list);
		sctp_insert_list(&asoc->outqueue.abanकरोned,
				 &chk->transmitted_list);

		streamout = SCTP_SO(&asoc->stream, chk->sinfo.sinfo_stream);
		asoc->sent_cnt_removable--;
		asoc->abanकरोned_sent[SCTP_PR_INDEX(PRIO)]++;
		streamout->ext->abanकरोned_sent[SCTP_PR_INDEX(PRIO)]++;

		अगर (queue != &asoc->outqueue.retransmit &&
		    !chk->tsn_gap_acked) अणु
			अगर (chk->transport)
				chk->transport->flight_size -=
						sctp_data_size(chk);
			asoc->outqueue.outstanding_bytes -= sctp_data_size(chk);
		पूर्ण

		msg_len -= chk->skb->truesize + माप(काष्ठा sctp_chunk);
		अगर (msg_len <= 0)
			अवरोध;
	पूर्ण

	वापस msg_len;
पूर्ण

अटल पूर्णांक sctp_prsctp_prune_unsent(काष्ठा sctp_association *asoc,
				    काष्ठा sctp_sndrcvinfo *sinfo, पूर्णांक msg_len)
अणु
	काष्ठा sctp_outq *q = &asoc->outqueue;
	काष्ठा sctp_chunk *chk, *temp;

	q->sched->unsched_all(&asoc->stream);

	list_क्रम_each_entry_safe(chk, temp, &q->out_chunk_list, list) अणु
		अगर (!chk->msg->abanकरोned &&
		    (!(chk->chunk_hdr->flags & SCTP_DATA_FIRST_FRAG) ||
		     !SCTP_PR_PRIO_ENABLED(chk->sinfo.sinfo_flags) ||
		     chk->sinfo.sinfo_समयtolive <= sinfo->sinfo_समयtolive))
			जारी;

		chk->msg->abanकरोned = 1;
		sctp_sched_dequeue_common(q, chk);
		asoc->sent_cnt_removable--;
		asoc->abanकरोned_unsent[SCTP_PR_INDEX(PRIO)]++;
		अगर (chk->sinfo.sinfo_stream < asoc->stream.outcnt) अणु
			काष्ठा sctp_stream_out *streamout =
				SCTP_SO(&asoc->stream, chk->sinfo.sinfo_stream);

			streamout->ext->abanकरोned_unsent[SCTP_PR_INDEX(PRIO)]++;
		पूर्ण

		msg_len -= chk->skb->truesize + माप(काष्ठा sctp_chunk);
		sctp_chunk_मुक्त(chk);
		अगर (msg_len <= 0)
			अवरोध;
	पूर्ण

	q->sched->sched_all(&asoc->stream);

	वापस msg_len;
पूर्ण

/* Abanकरोn the chunks according their priorities */
व्योम sctp_prsctp_prune(काष्ठा sctp_association *asoc,
		       काष्ठा sctp_sndrcvinfo *sinfo, पूर्णांक msg_len)
अणु
	काष्ठा sctp_transport *transport;

	अगर (!asoc->peer.prsctp_capable || !asoc->sent_cnt_removable)
		वापस;

	msg_len = sctp_prsctp_prune_sent(asoc, sinfo,
					 &asoc->outqueue.retransmit,
					 msg_len);
	अगर (msg_len <= 0)
		वापस;

	list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
			    transports) अणु
		msg_len = sctp_prsctp_prune_sent(asoc, sinfo,
						 &transport->transmitted,
						 msg_len);
		अगर (msg_len <= 0)
			वापस;
	पूर्ण

	sctp_prsctp_prune_unsent(asoc, sinfo, msg_len);
पूर्ण

/* Mark all the eligible packets on a transport क्रम retransmission.  */
व्योम sctp_retransmit_mark(काष्ठा sctp_outq *q,
			  काष्ठा sctp_transport *transport,
			  __u8 reason)
अणु
	काष्ठा list_head *lchunk, *ltemp;
	काष्ठा sctp_chunk *chunk;

	/* Walk through the specअगरied transmitted queue.  */
	list_क्रम_each_safe(lchunk, ltemp, &transport->transmitted) अणु
		chunk = list_entry(lchunk, काष्ठा sctp_chunk,
				   transmitted_list);

		/* If the chunk is abanकरोned, move it to abanकरोned list. */
		अगर (sctp_chunk_abanकरोned(chunk)) अणु
			list_del_init(lchunk);
			sctp_insert_list(&q->abanकरोned, lchunk);

			/* If this chunk has not been previousely acked,
			 * stop considering it 'outstanding'.  Our peer
			 * will most likely never see it since it will
			 * not be retransmitted
			 */
			अगर (!chunk->tsn_gap_acked) अणु
				अगर (chunk->transport)
					chunk->transport->flight_size -=
							sctp_data_size(chunk);
				q->outstanding_bytes -= sctp_data_size(chunk);
				q->asoc->peer.rwnd += sctp_data_size(chunk);
			पूर्ण
			जारी;
		पूर्ण

		/* If we are करोing  retransmission due to a समयout or pmtu
		 * discovery, only the  chunks that are not yet acked should
		 * be added to the retransmit queue.
		 */
		अगर ((reason == SCTP_RTXR_FAST_RTX  &&
			    (chunk->fast_retransmit == SCTP_NEED_FRTX)) ||
		    (reason != SCTP_RTXR_FAST_RTX  && !chunk->tsn_gap_acked)) अणु
			/* RFC 2960 6.2.1 Processing a Received SACK
			 *
			 * C) Any समय a DATA chunk is marked क्रम
			 * retransmission (via either T3-rtx समयr expiration
			 * (Section 6.3.3) or via fast retransmit
			 * (Section 7.2.4)), add the data size of those
			 * chunks to the rwnd.
			 */
			q->asoc->peer.rwnd += sctp_data_size(chunk);
			q->outstanding_bytes -= sctp_data_size(chunk);
			अगर (chunk->transport)
				transport->flight_size -= sctp_data_size(chunk);

			/* sctpimpguide-05 Section 2.8.2
			 * M5) If a T3-rtx समयr expires, the
			 * 'TSN.Missing.Report' of all affected TSNs is set
			 * to 0.
			 */
			chunk->tsn_missing_report = 0;

			/* If a chunk that is being used क्रम RTT measurement
			 * has to be retransmitted, we cannot use this chunk
			 * anymore क्रम RTT measurements. Reset rto_pending so
			 * that a new RTT measurement is started when a new
			 * data chunk is sent.
			 */
			अगर (chunk->rtt_in_progress) अणु
				chunk->rtt_in_progress = 0;
				transport->rto_pending = 0;
			पूर्ण

			/* Move the chunk to the retransmit queue. The chunks
			 * on the retransmit queue are always kept in order.
			 */
			list_del_init(lchunk);
			sctp_insert_list(&q->retransmit, lchunk);
		पूर्ण
	पूर्ण

	pr_debug("%s: transport:%p, reason:%d, cwnd:%d, ssthresh:%d, "
		 "flight_size:%d, pba:%d\n", __func__, transport, reason,
		 transport->cwnd, transport->ssthresh, transport->flight_size,
		 transport->partial_bytes_acked);
पूर्ण

/* Mark all the eligible packets on a transport क्रम retransmission and क्रमce
 * one packet out.
 */
व्योम sctp_retransmit(काष्ठा sctp_outq *q, काष्ठा sctp_transport *transport,
		     क्रमागत sctp_retransmit_reason reason)
अणु
	काष्ठा net *net = q->asoc->base.net;

	चयन (reason) अणु
	हाल SCTP_RTXR_T3_RTX:
		SCTP_INC_STATS(net, SCTP_MIB_T3_RETRANSMITS);
		sctp_transport_lower_cwnd(transport, SCTP_LOWER_CWND_T3_RTX);
		/* Update the retran path अगर the T3-rtx समयr has expired क्रम
		 * the current retran path.
		 */
		अगर (transport == transport->asoc->peer.retran_path)
			sctp_assoc_update_retran_path(transport->asoc);
		transport->asoc->rtx_data_chunks +=
			transport->asoc->unack_data;
		अवरोध;
	हाल SCTP_RTXR_FAST_RTX:
		SCTP_INC_STATS(net, SCTP_MIB_FAST_RETRANSMITS);
		sctp_transport_lower_cwnd(transport, SCTP_LOWER_CWND_FAST_RTX);
		q->fast_rtx = 1;
		अवरोध;
	हाल SCTP_RTXR_PMTUD:
		SCTP_INC_STATS(net, SCTP_MIB_PMTUD_RETRANSMITS);
		अवरोध;
	हाल SCTP_RTXR_T1_RTX:
		SCTP_INC_STATS(net, SCTP_MIB_T1_RETRANSMITS);
		transport->asoc->init_retries++;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	sctp_retransmit_mark(q, transport, reason);

	/* PR-SCTP A5) Any समय the T3-rtx समयr expires, on any destination,
	 * the sender SHOULD try to advance the "Advanced.Peer.Ack.Point" by
	 * following the procedures outlined in C1 - C5.
	 */
	अगर (reason == SCTP_RTXR_T3_RTX)
		q->asoc->stream.si->generate_ftsn(q, q->asoc->ctsn_ack_poपूर्णांक);

	/* Flush the queues only on समयout, since fast_rtx is only
	 * triggered during sack processing and the queue
	 * will be flushed at the end.
	 */
	अगर (reason != SCTP_RTXR_FAST_RTX)
		sctp_outq_flush(q, /* rtx_समयout */ 1, GFP_ATOMIC);
पूर्ण

/*
 * Transmit DATA chunks on the retransmit queue.  Upon वापस from
 * __sctp_outq_flush_rtx() the packet 'pkt' may contain chunks which
 * need to be transmitted by the caller.
 * We assume that pkt->transport has alपढ़ोy been set.
 *
 * The वापस value is a normal kernel error वापस value.
 */
अटल पूर्णांक __sctp_outq_flush_rtx(काष्ठा sctp_outq *q, काष्ठा sctp_packet *pkt,
				 पूर्णांक rtx_समयout, पूर्णांक *start_समयr, gfp_t gfp)
अणु
	काष्ठा sctp_transport *transport = pkt->transport;
	काष्ठा sctp_chunk *chunk, *chunk1;
	काष्ठा list_head *lqueue;
	क्रमागत sctp_xmit status;
	पूर्णांक error = 0;
	पूर्णांक समयr = 0;
	पूर्णांक करोne = 0;
	पूर्णांक fast_rtx;

	lqueue = &q->retransmit;
	fast_rtx = q->fast_rtx;

	/* This loop handles समय-out retransmissions, fast retransmissions,
	 * and retransmissions due to खोलोing of whinकरोw.
	 *
	 * RFC 2960 6.3.3 Handle T3-rtx Expiration
	 *
	 * E3) Determine how many of the earliest (i.e., lowest TSN)
	 * outstanding DATA chunks क्रम the address क्रम which the
	 * T3-rtx has expired will fit पूर्णांकo a single packet, subject
	 * to the MTU स्थिरraपूर्णांक क्रम the path corresponding to the
	 * destination transport address to which the retransmission
	 * is being sent (this may be dअगरferent from the address क्रम
	 * which the समयr expires [see Section 6.4]). Call this value
	 * K. Bundle and retransmit those K DATA chunks in a single
	 * packet to the destination endpoपूर्णांक.
	 *
	 * [Just to be painfully clear, अगर we are retransmitting
	 * because a समयout just happened, we should send only ONE
	 * packet of retransmitted data.]
	 *
	 * For fast retransmissions we also send only ONE packet.  However,
	 * अगर we are just flushing the queue due to खोलो winकरोw, we'll
	 * try to send as much as possible.
	 */
	list_क्रम_each_entry_safe(chunk, chunk1, lqueue, transmitted_list) अणु
		/* If the chunk is abanकरोned, move it to abanकरोned list. */
		अगर (sctp_chunk_abanकरोned(chunk)) अणु
			list_del_init(&chunk->transmitted_list);
			sctp_insert_list(&q->abanकरोned,
					 &chunk->transmitted_list);
			जारी;
		पूर्ण

		/* Make sure that Gap Acked TSNs are not retransmitted.  A
		 * simple approach is just to move such TSNs out of the
		 * way and पूर्णांकo a 'transmitted' queue and skip to the
		 * next chunk.
		 */
		अगर (chunk->tsn_gap_acked) अणु
			list_move_tail(&chunk->transmitted_list,
				       &transport->transmitted);
			जारी;
		पूर्ण

		/* If we are करोing fast retransmit, ignore non-fast_rtransmit
		 * chunks
		 */
		अगर (fast_rtx && !chunk->fast_retransmit)
			जारी;

reकरो:
		/* Attempt to append this chunk to the packet. */
		status = sctp_packet_append_chunk(pkt, chunk);

		चयन (status) अणु
		हाल SCTP_XMIT_PMTU_FULL:
			अगर (!pkt->has_data && !pkt->has_cookie_echo) अणु
				/* If this packet did not contain DATA then
				 * retransmission did not happen, so करो it
				 * again.  We'll ignore the error here since
				 * control chunks are alपढ़ोy मुक्तd so there
				 * is nothing we can करो.
				 */
				sctp_packet_transmit(pkt, gfp);
				जाओ reकरो;
			पूर्ण

			/* Send this packet.  */
			error = sctp_packet_transmit(pkt, gfp);

			/* If we are retransmitting, we should only
			 * send a single packet.
			 * Otherwise, try appending this chunk again.
			 */
			अगर (rtx_समयout || fast_rtx)
				करोne = 1;
			अन्यथा
				जाओ reकरो;

			/* Bundle next chunk in the next round.  */
			अवरोध;

		हाल SCTP_XMIT_RWND_FULL:
			/* Send this packet. */
			error = sctp_packet_transmit(pkt, gfp);

			/* Stop sending DATA as there is no more room
			 * at the receiver.
			 */
			करोne = 1;
			अवरोध;

		हाल SCTP_XMIT_DELAY:
			/* Send this packet. */
			error = sctp_packet_transmit(pkt, gfp);

			/* Stop sending DATA because of nagle delay. */
			करोne = 1;
			अवरोध;

		शेष:
			/* The append was successful, so add this chunk to
			 * the transmitted list.
			 */
			list_move_tail(&chunk->transmitted_list,
				       &transport->transmitted);

			/* Mark the chunk as ineligible क्रम fast retransmit
			 * after it is retransmitted.
			 */
			अगर (chunk->fast_retransmit == SCTP_NEED_FRTX)
				chunk->fast_retransmit = SCTP_DONT_FRTX;

			q->asoc->stats.rtxchunks++;
			अवरोध;
		पूर्ण

		/* Set the समयr अगर there were no errors */
		अगर (!error && !समयr)
			समयr = 1;

		अगर (करोne)
			अवरोध;
	पूर्ण

	/* If we are here due to a retransmit समयout or a fast
	 * retransmit and अगर there are any chunks left in the retransmit
	 * queue that could not fit in the PMTU sized packet, they need
	 * to be marked as ineligible क्रम a subsequent fast retransmit.
	 */
	अगर (rtx_समयout || fast_rtx) अणु
		list_क्रम_each_entry(chunk1, lqueue, transmitted_list) अणु
			अगर (chunk1->fast_retransmit == SCTP_NEED_FRTX)
				chunk1->fast_retransmit = SCTP_DONT_FRTX;
		पूर्ण
	पूर्ण

	*start_समयr = समयr;

	/* Clear fast retransmit hपूर्णांक */
	अगर (fast_rtx)
		q->fast_rtx = 0;

	वापस error;
पूर्ण

/* Cork the outqueue so queued chunks are really queued. */
व्योम sctp_outq_uncork(काष्ठा sctp_outq *q, gfp_t gfp)
अणु
	अगर (q->cork)
		q->cork = 0;

	sctp_outq_flush(q, 0, gfp);
पूर्ण

अटल पूर्णांक sctp_packet_singleton(काष्ठा sctp_transport *transport,
				 काष्ठा sctp_chunk *chunk, gfp_t gfp)
अणु
	स्थिर काष्ठा sctp_association *asoc = transport->asoc;
	स्थिर __u16 sport = asoc->base.bind_addr.port;
	स्थिर __u16 dport = asoc->peer.port;
	स्थिर __u32 vtag = asoc->peer.i.init_tag;
	काष्ठा sctp_packet singleton;

	sctp_packet_init(&singleton, transport, sport, dport);
	sctp_packet_config(&singleton, vtag, 0);
	sctp_packet_append_chunk(&singleton, chunk);
	वापस sctp_packet_transmit(&singleton, gfp);
पूर्ण

/* Struct to hold the context during sctp outq flush */
काष्ठा sctp_flush_ctx अणु
	काष्ठा sctp_outq *q;
	/* Current transport being used. It's NOT the same as curr active one */
	काष्ठा sctp_transport *transport;
	/* These transports have chunks to send. */
	काष्ठा list_head transport_list;
	काष्ठा sctp_association *asoc;
	/* Packet on the current transport above */
	काष्ठा sctp_packet *packet;
	gfp_t gfp;
पूर्ण;

/* transport: current transport */
अटल व्योम sctp_outq_select_transport(काष्ठा sctp_flush_ctx *ctx,
				       काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_transport *new_transport = chunk->transport;

	अगर (!new_transport) अणु
		अगर (!sctp_chunk_is_data(chunk)) अणु
			/* If we have a prior transport poपूर्णांकer, see अगर
			 * the destination address of the chunk
			 * matches the destination address of the
			 * current transport.  If not a match, then
			 * try to look up the transport with a given
			 * destination address.  We करो this because
			 * after processing ASCONFs, we may have new
			 * transports created.
			 */
			अगर (ctx->transport && sctp_cmp_addr_exact(&chunk->dest,
							&ctx->transport->ipaddr))
				new_transport = ctx->transport;
			अन्यथा
				new_transport = sctp_assoc_lookup_paddr(ctx->asoc,
								  &chunk->dest);
		पूर्ण

		/* अगर we still करोn't have a new transport, then
		 * use the current active path.
		 */
		अगर (!new_transport)
			new_transport = ctx->asoc->peer.active_path;
	पूर्ण अन्यथा अणु
		__u8 type;

		चयन (new_transport->state) अणु
		हाल SCTP_INACTIVE:
		हाल SCTP_UNCONFIRMED:
		हाल SCTP_PF:
			/* If the chunk is Heartbeat or Heartbeat Ack,
			 * send it to chunk->transport, even अगर it's
			 * inactive.
			 *
			 * 3.3.6 Heartbeat Acknowledgement:
			 * ...
			 * A HEARTBEAT ACK is always sent to the source IP
			 * address of the IP datagram containing the
			 * HEARTBEAT chunk to which this ack is responding.
			 * ...
			 *
			 * ASCONF_ACKs also must be sent to the source.
			 */
			type = chunk->chunk_hdr->type;
			अगर (type != SCTP_CID_HEARTBEAT &&
			    type != SCTP_CID_HEARTBEAT_ACK &&
			    type != SCTP_CID_ASCONF_ACK)
				new_transport = ctx->asoc->peer.active_path;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Are we चयनing transports? Take care of transport locks. */
	अगर (new_transport != ctx->transport) अणु
		ctx->transport = new_transport;
		ctx->packet = &ctx->transport->packet;

		अगर (list_empty(&ctx->transport->send_पढ़ोy))
			list_add_tail(&ctx->transport->send_पढ़ोy,
				      &ctx->transport_list);

		sctp_packet_config(ctx->packet,
				   ctx->asoc->peer.i.init_tag,
				   ctx->asoc->peer.ecn_capable);
		/* We've चयनed transports, so apply the
		 * Burst limit to the new transport.
		 */
		sctp_transport_burst_limited(ctx->transport);
	पूर्ण
पूर्ण

अटल व्योम sctp_outq_flush_ctrl(काष्ठा sctp_flush_ctx *ctx)
अणु
	काष्ठा sctp_chunk *chunk, *पंचांगp;
	क्रमागत sctp_xmit status;
	पूर्णांक one_packet, error;

	list_क्रम_each_entry_safe(chunk, पंचांगp, &ctx->q->control_chunk_list, list) अणु
		one_packet = 0;

		/* RFC 5061, 5.3
		 * F1) This means that until such समय as the ASCONF
		 * containing the add is acknowledged, the sender MUST
		 * NOT use the new IP address as a source क्रम ANY SCTP
		 * packet except on carrying an ASCONF Chunk.
		 */
		अगर (ctx->asoc->src_out_of_asoc_ok &&
		    chunk->chunk_hdr->type != SCTP_CID_ASCONF)
			जारी;

		list_del_init(&chunk->list);

		/* Pick the right transport to use. Should always be true क्रम
		 * the first chunk as we करोn't have a transport by then.
		 */
		sctp_outq_select_transport(ctx, chunk);

		चयन (chunk->chunk_hdr->type) अणु
		/* 6.10 Bundling
		 *   ...
		 *   An endpoपूर्णांक MUST NOT bundle INIT, INIT ACK or SHUTDOWN
		 *   COMPLETE with any other chunks.  [Send them immediately.]
		 */
		हाल SCTP_CID_INIT:
		हाल SCTP_CID_INIT_ACK:
		हाल SCTP_CID_SHUTDOWN_COMPLETE:
			error = sctp_packet_singleton(ctx->transport, chunk,
						      ctx->gfp);
			अगर (error < 0) अणु
				ctx->asoc->base.sk->sk_err = -error;
				वापस;
			पूर्ण
			अवरोध;

		हाल SCTP_CID_ABORT:
			अगर (sctp_test_T_bit(chunk))
				ctx->packet->vtag = ctx->asoc->c.my_vtag;
			fallthrough;

		/* The following chunks are "response" chunks, i.e.
		 * they are generated in response to something we
		 * received.  If we are sending these, then we can
		 * send only 1 packet containing these chunks.
		 */
		हाल SCTP_CID_HEARTBEAT_ACK:
		हाल SCTP_CID_SHUTDOWN_ACK:
		हाल SCTP_CID_COOKIE_ACK:
		हाल SCTP_CID_COOKIE_ECHO:
		हाल SCTP_CID_ERROR:
		हाल SCTP_CID_ECN_CWR:
		हाल SCTP_CID_ASCONF_ACK:
			one_packet = 1;
			fallthrough;

		हाल SCTP_CID_SACK:
		हाल SCTP_CID_HEARTBEAT:
		हाल SCTP_CID_SHUTDOWN:
		हाल SCTP_CID_ECN_ECNE:
		हाल SCTP_CID_ASCONF:
		हाल SCTP_CID_FWD_TSN:
		हाल SCTP_CID_I_FWD_TSN:
		हाल SCTP_CID_RECONF:
			status = sctp_packet_transmit_chunk(ctx->packet, chunk,
							    one_packet, ctx->gfp);
			अगर (status != SCTP_XMIT_OK) अणु
				/* put the chunk back */
				list_add(&chunk->list, &ctx->q->control_chunk_list);
				अवरोध;
			पूर्ण

			ctx->asoc->stats.octrlchunks++;
			/* PR-SCTP C5) If a FORWARD TSN is sent, the
			 * sender MUST assure that at least one T3-rtx
			 * समयr is running.
			 */
			अगर (chunk->chunk_hdr->type == SCTP_CID_FWD_TSN ||
			    chunk->chunk_hdr->type == SCTP_CID_I_FWD_TSN) अणु
				sctp_transport_reset_t3_rtx(ctx->transport);
				ctx->transport->last_समय_sent = jअगरfies;
			पूर्ण

			अगर (chunk == ctx->asoc->strreset_chunk)
				sctp_transport_reset_reconf_समयr(ctx->transport);

			अवरोध;

		शेष:
			/* We built a chunk with an illegal type! */
			BUG();
		पूर्ण
	पूर्ण
पूर्ण

/* Returns false अगर new data shouldn't be sent */
अटल bool sctp_outq_flush_rtx(काष्ठा sctp_flush_ctx *ctx,
				पूर्णांक rtx_समयout)
अणु
	पूर्णांक error, start_समयr = 0;

	अगर (ctx->asoc->peer.retran_path->state == SCTP_UNCONFIRMED)
		वापस false;

	अगर (ctx->transport != ctx->asoc->peer.retran_path) अणु
		/* Switch transports & prepare the packet.  */
		ctx->transport = ctx->asoc->peer.retran_path;
		ctx->packet = &ctx->transport->packet;

		अगर (list_empty(&ctx->transport->send_पढ़ोy))
			list_add_tail(&ctx->transport->send_पढ़ोy,
				      &ctx->transport_list);

		sctp_packet_config(ctx->packet, ctx->asoc->peer.i.init_tag,
				   ctx->asoc->peer.ecn_capable);
	पूर्ण

	error = __sctp_outq_flush_rtx(ctx->q, ctx->packet, rtx_समयout,
				      &start_समयr, ctx->gfp);
	अगर (error < 0)
		ctx->asoc->base.sk->sk_err = -error;

	अगर (start_समयr) अणु
		sctp_transport_reset_t3_rtx(ctx->transport);
		ctx->transport->last_समय_sent = jअगरfies;
	पूर्ण

	/* This can happen on COOKIE-ECHO resend.  Only
	 * one chunk can get bundled with a COOKIE-ECHO.
	 */
	अगर (ctx->packet->has_cookie_echo)
		वापस false;

	/* Don't send new data अगर there is still data
	 * रुकोing to retransmit.
	 */
	अगर (!list_empty(&ctx->q->retransmit))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम sctp_outq_flush_data(काष्ठा sctp_flush_ctx *ctx,
				 पूर्णांक rtx_समयout)
अणु
	काष्ठा sctp_chunk *chunk;
	क्रमागत sctp_xmit status;

	/* Is it OK to send data chunks?  */
	चयन (ctx->asoc->state) अणु
	हाल SCTP_STATE_COOKIE_ECHOED:
		/* Only allow bundling when this packet has a COOKIE-ECHO
		 * chunk.
		 */
		अगर (!ctx->packet || !ctx->packet->has_cookie_echo)
			वापस;

		fallthrough;
	हाल SCTP_STATE_ESTABLISHED:
	हाल SCTP_STATE_SHUTDOWN_PENDING:
	हाल SCTP_STATE_SHUTDOWN_RECEIVED:
		अवरोध;

	शेष:
		/* Do nothing. */
		वापस;
	पूर्ण

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * C) When the समय comes क्रम the sender to transmit,
	 * beक्रमe sending new DATA chunks, the sender MUST
	 * first transmit any outstanding DATA chunks which
	 * are marked क्रम retransmission (limited by the
	 * current cwnd).
	 */
	अगर (!list_empty(&ctx->q->retransmit) &&
	    !sctp_outq_flush_rtx(ctx, rtx_समयout))
		वापस;

	/* Apply Max.Burst limitation to the current transport in
	 * हाल it will be used क्रम new data.  We are going to
	 * rest it beक्रमe we वापस, but we want to apply the limit
	 * to the currently queued data.
	 */
	अगर (ctx->transport)
		sctp_transport_burst_limited(ctx->transport);

	/* Finally, transmit new packets.  */
	जबतक ((chunk = sctp_outq_dequeue_data(ctx->q)) != शून्य) अणु
		__u32 sid = ntohs(chunk->subh.data_hdr->stream);
		__u8 stream_state = SCTP_SO(&ctx->asoc->stream, sid)->state;

		/* Has this chunk expired? */
		अगर (sctp_chunk_abanकरोned(chunk)) अणु
			sctp_sched_dequeue_करोne(ctx->q, chunk);
			sctp_chunk_fail(chunk, 0);
			sctp_chunk_मुक्त(chunk);
			जारी;
		पूर्ण

		अगर (stream_state == SCTP_STREAM_CLOSED) अणु
			sctp_outq_head_data(ctx->q, chunk);
			अवरोध;
		पूर्ण

		sctp_outq_select_transport(ctx, chunk);

		pr_debug("%s: outq:%p, chunk:%p[%s], tx-tsn:0x%x skb->head:%p skb->users:%d\n",
			 __func__, ctx->q, chunk, chunk && chunk->chunk_hdr ?
			 sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdr->type)) :
			 "illegal chunk", ntohl(chunk->subh.data_hdr->tsn),
			 chunk->skb ? chunk->skb->head : शून्य, chunk->skb ?
			 refcount_पढ़ो(&chunk->skb->users) : -1);

		/* Add the chunk to the packet.  */
		status = sctp_packet_transmit_chunk(ctx->packet, chunk, 0,
						    ctx->gfp);
		अगर (status != SCTP_XMIT_OK) अणु
			/* We could not append this chunk, so put
			 * the chunk back on the output queue.
			 */
			pr_debug("%s: could not transmit tsn:0x%x, status:%d\n",
				 __func__, ntohl(chunk->subh.data_hdr->tsn),
				 status);

			sctp_outq_head_data(ctx->q, chunk);
			अवरोध;
		पूर्ण

		/* The sender is in the SHUTDOWN-PENDING state,
		 * The sender MAY set the I-bit in the DATA
		 * chunk header.
		 */
		अगर (ctx->asoc->state == SCTP_STATE_SHUTDOWN_PENDING)
			chunk->chunk_hdr->flags |= SCTP_DATA_SACK_IMM;
		अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
			ctx->asoc->stats.ouodchunks++;
		अन्यथा
			ctx->asoc->stats.oodchunks++;

		/* Only now it's safe to consider this
		 * chunk as sent, sched-wise.
		 */
		sctp_sched_dequeue_करोne(ctx->q, chunk);

		list_add_tail(&chunk->transmitted_list,
			      &ctx->transport->transmitted);

		sctp_transport_reset_t3_rtx(ctx->transport);
		ctx->transport->last_समय_sent = jअगरfies;

		/* Only let one DATA chunk get bundled with a
		 * COOKIE-ECHO chunk.
		 */
		अगर (ctx->packet->has_cookie_echo)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sctp_outq_flush_transports(काष्ठा sctp_flush_ctx *ctx)
अणु
	काष्ठा sock *sk = ctx->asoc->base.sk;
	काष्ठा list_head *ltransport;
	काष्ठा sctp_packet *packet;
	काष्ठा sctp_transport *t;
	पूर्णांक error = 0;

	जबतक ((ltransport = sctp_list_dequeue(&ctx->transport_list)) != शून्य) अणु
		t = list_entry(ltransport, काष्ठा sctp_transport, send_पढ़ोy);
		packet = &t->packet;
		अगर (!sctp_packet_empty(packet)) अणु
			rcu_पढ़ो_lock();
			अगर (t->dst && __sk_dst_get(sk) != t->dst) अणु
				dst_hold(t->dst);
				sk_setup_caps(sk, t->dst);
			पूर्ण
			rcu_पढ़ो_unlock();
			error = sctp_packet_transmit(packet, ctx->gfp);
			अगर (error < 0)
				ctx->q->asoc->base.sk->sk_err = -error;
		पूर्ण

		/* Clear the burst limited state, अगर any */
		sctp_transport_burst_reset(t);
	पूर्ण
पूर्ण

/* Try to flush an outqueue.
 *
 * Description: Send everything in q which we legally can, subject to
 * congestion limitations.
 * * Note: This function can be called from multiple contexts so appropriate
 * locking concerns must be made.  Today we use the sock lock to protect
 * this function.
 */

अटल व्योम sctp_outq_flush(काष्ठा sctp_outq *q, पूर्णांक rtx_समयout, gfp_t gfp)
अणु
	काष्ठा sctp_flush_ctx ctx = अणु
		.q = q,
		.transport = शून्य,
		.transport_list = LIST_HEAD_INIT(ctx.transport_list),
		.asoc = q->asoc,
		.packet = शून्य,
		.gfp = gfp,
	पूर्ण;

	/* 6.10 Bundling
	 *   ...
	 *   When bundling control chunks with DATA chunks, an
	 *   endpoपूर्णांक MUST place control chunks first in the outbound
	 *   SCTP packet.  The transmitter MUST transmit DATA chunks
	 *   within a SCTP packet in increasing order of TSN.
	 *   ...
	 */

	sctp_outq_flush_ctrl(&ctx);

	अगर (q->asoc->src_out_of_asoc_ok)
		जाओ sctp_flush_out;

	sctp_outq_flush_data(&ctx, rtx_समयout);

sctp_flush_out:

	sctp_outq_flush_transports(&ctx);
पूर्ण

/* Update unack_data based on the incoming SACK chunk */
अटल व्योम sctp_sack_update_unack_data(काष्ठा sctp_association *assoc,
					काष्ठा sctp_sackhdr *sack)
अणु
	जोड़ sctp_sack_variable *frags;
	__u16 unack_data;
	पूर्णांक i;

	unack_data = assoc->next_tsn - assoc->ctsn_ack_poपूर्णांक - 1;

	frags = sack->variable;
	क्रम (i = 0; i < ntohs(sack->num_gap_ack_blocks); i++) अणु
		unack_data -= ((ntohs(frags[i].gab.end) -
				ntohs(frags[i].gab.start) + 1));
	पूर्ण

	assoc->unack_data = unack_data;
पूर्ण

/* This is where we REALLY process a SACK.
 *
 * Process the SACK against the outqueue.  Mostly, this just मुक्तs
 * things off the transmitted queue.
 */
पूर्णांक sctp_outq_sack(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_association *asoc = q->asoc;
	काष्ठा sctp_sackhdr *sack = chunk->subh.sack_hdr;
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_chunk *tchunk = शून्य;
	काष्ठा list_head *lchunk, *transport_list, *temp;
	जोड़ sctp_sack_variable *frags = sack->variable;
	__u32 sack_ctsn, ctsn, tsn;
	__u32 highest_tsn, highest_new_tsn;
	__u32 sack_a_rwnd;
	अचिन्हित पूर्णांक outstanding;
	काष्ठा sctp_transport *primary = asoc->peer.primary_path;
	पूर्णांक count_of_newacks = 0;
	पूर्णांक gap_ack_blocks;
	u8 accum_moved = 0;

	/* Grab the association's destination address list. */
	transport_list = &asoc->peer.transport_addr_list;

	/* SCTP path tracepoपूर्णांक क्रम congestion control debugging. */
	अगर (trace_sctp_probe_path_enabled()) अणु
		list_क्रम_each_entry(transport, transport_list, transports)
			trace_sctp_probe_path(transport, asoc);
	पूर्ण

	sack_ctsn = ntohl(sack->cum_tsn_ack);
	gap_ack_blocks = ntohs(sack->num_gap_ack_blocks);
	asoc->stats.gapcnt += gap_ack_blocks;
	/*
	 * SFR-CACC algorithm:
	 * On receipt of a SACK the sender SHOULD execute the
	 * following statements.
	 *
	 * 1) If the cumulative ack in the SACK passes next tsn_at_change
	 * on the current primary, the CHANGEOVER_ACTIVE flag SHOULD be
	 * cleared. The CYCLING_CHANGEOVER flag SHOULD also be cleared क्रम
	 * all destinations.
	 * 2) If the SACK contains gap acks and the flag CHANGEOVER_ACTIVE
	 * is set the receiver of the SACK MUST take the following actions:
	 *
	 * A) Initialize the cacc_saw_newack to 0 क्रम all destination
	 * addresses.
	 *
	 * Only bother अगर changeover_active is set. Otherwise, this is
	 * totally suboptimal to करो on every SACK.
	 */
	अगर (primary->cacc.changeover_active) अणु
		u8 clear_cycling = 0;

		अगर (TSN_lte(primary->cacc.next_tsn_at_change, sack_ctsn)) अणु
			primary->cacc.changeover_active = 0;
			clear_cycling = 1;
		पूर्ण

		अगर (clear_cycling || gap_ack_blocks) अणु
			list_क्रम_each_entry(transport, transport_list,
					transports) अणु
				अगर (clear_cycling)
					transport->cacc.cycling_changeover = 0;
				अगर (gap_ack_blocks)
					transport->cacc.cacc_saw_newack = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Get the highest TSN in the sack. */
	highest_tsn = sack_ctsn;
	अगर (gap_ack_blocks)
		highest_tsn += ntohs(frags[gap_ack_blocks - 1].gab.end);

	अगर (TSN_lt(asoc->highest_sacked, highest_tsn))
		asoc->highest_sacked = highest_tsn;

	highest_new_tsn = sack_ctsn;

	/* Run through the retransmit queue.  Credit bytes received
	 * and मुक्त those chunks that we can.
	 */
	sctp_check_transmitted(q, &q->retransmit, शून्य, शून्य, sack, &highest_new_tsn);

	/* Run through the transmitted queue.
	 * Credit bytes received and मुक्त those chunks which we can.
	 *
	 * This is a MASSIVE candidate क्रम optimization.
	 */
	list_क्रम_each_entry(transport, transport_list, transports) अणु
		sctp_check_transmitted(q, &transport->transmitted,
				       transport, &chunk->source, sack,
				       &highest_new_tsn);
		/*
		 * SFR-CACC algorithm:
		 * C) Let count_of_newacks be the number of
		 * destinations क्रम which cacc_saw_newack is set.
		 */
		अगर (transport->cacc.cacc_saw_newack)
			count_of_newacks++;
	पूर्ण

	/* Move the Cumulative TSN Ack Poपूर्णांक अगर appropriate.  */
	अगर (TSN_lt(asoc->ctsn_ack_poपूर्णांक, sack_ctsn)) अणु
		asoc->ctsn_ack_poपूर्णांक = sack_ctsn;
		accum_moved = 1;
	पूर्ण

	अगर (gap_ack_blocks) अणु

		अगर (asoc->fast_recovery && accum_moved)
			highest_new_tsn = highest_tsn;

		list_क्रम_each_entry(transport, transport_list, transports)
			sctp_mark_missing(q, &transport->transmitted, transport,
					  highest_new_tsn, count_of_newacks);
	पूर्ण

	/* Update unack_data field in the assoc. */
	sctp_sack_update_unack_data(asoc, sack);

	ctsn = asoc->ctsn_ack_poपूर्णांक;

	/* Throw away stuff rotting on the sack queue.  */
	list_क्रम_each_safe(lchunk, temp, &q->sacked) अणु
		tchunk = list_entry(lchunk, काष्ठा sctp_chunk,
				    transmitted_list);
		tsn = ntohl(tchunk->subh.data_hdr->tsn);
		अगर (TSN_lte(tsn, ctsn)) अणु
			list_del_init(&tchunk->transmitted_list);
			अगर (asoc->peer.prsctp_capable &&
			    SCTP_PR_PRIO_ENABLED(chunk->sinfo.sinfo_flags))
				asoc->sent_cnt_removable--;
			sctp_chunk_मुक्त(tchunk);
		पूर्ण
	पूर्ण

	/* ii) Set rwnd equal to the newly received a_rwnd minus the
	 *     number of bytes still outstanding after processing the
	 *     Cumulative TSN Ack and the Gap Ack Blocks.
	 */

	sack_a_rwnd = ntohl(sack->a_rwnd);
	asoc->peer.zero_winकरोw_announced = !sack_a_rwnd;
	outstanding = q->outstanding_bytes;

	अगर (outstanding < sack_a_rwnd)
		sack_a_rwnd -= outstanding;
	अन्यथा
		sack_a_rwnd = 0;

	asoc->peer.rwnd = sack_a_rwnd;

	asoc->stream.si->generate_ftsn(q, sack_ctsn);

	pr_debug("%s: sack cumulative tsn ack:0x%x\n", __func__, sack_ctsn);
	pr_debug("%s: cumulative tsn ack of assoc:%p is 0x%x, "
		 "advertised peer ack point:0x%x\n", __func__, asoc, ctsn,
		 asoc->adv_peer_ack_poपूर्णांक);

	वापस sctp_outq_is_empty(q);
पूर्ण

/* Is the outqueue empty?
 * The queue is empty when we have not pending data, no in-flight data
 * and nothing pending retransmissions.
 */
पूर्णांक sctp_outq_is_empty(स्थिर काष्ठा sctp_outq *q)
अणु
	वापस q->out_qlen == 0 && q->outstanding_bytes == 0 &&
	       list_empty(&q->retransmit);
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* Go through a transport's transmitted list or the association's retransmit
 * list and move chunks that are acked by the Cumulative TSN Ack to q->sacked.
 * The retransmit list will not have an associated transport.
 *
 * I added coherent debug inक्रमmation output.	--xguo
 *
 * Instead of prपूर्णांकing 'sacked' or 'kept' क्रम each TSN on the
 * transmitted_queue, we prपूर्णांक a range: SACKED: TSN1-TSN2, TSN3, TSN4-TSN5.
 * KEPT TSN6-TSN7, etc.
 */
अटल व्योम sctp_check_transmitted(काष्ठा sctp_outq *q,
				   काष्ठा list_head *transmitted_queue,
				   काष्ठा sctp_transport *transport,
				   जोड़ sctp_addr *saddr,
				   काष्ठा sctp_sackhdr *sack,
				   __u32 *highest_new_tsn_in_sack)
अणु
	काष्ठा list_head *lchunk;
	काष्ठा sctp_chunk *tchunk;
	काष्ठा list_head tlist;
	__u32 tsn;
	__u32 sack_ctsn;
	__u32 rtt;
	__u8 restart_समयr = 0;
	पूर्णांक bytes_acked = 0;
	पूर्णांक migrate_bytes = 0;
	bool क्रमward_progress = false;

	sack_ctsn = ntohl(sack->cum_tsn_ack);

	INIT_LIST_HEAD(&tlist);

	/* The जबतक loop will skip empty transmitted queues. */
	जबतक (शून्य != (lchunk = sctp_list_dequeue(transmitted_queue))) अणु
		tchunk = list_entry(lchunk, काष्ठा sctp_chunk,
				    transmitted_list);

		अगर (sctp_chunk_abanकरोned(tchunk)) अणु
			/* Move the chunk to abanकरोned list. */
			sctp_insert_list(&q->abanकरोned, lchunk);

			/* If this chunk has not been acked, stop
			 * considering it as 'outstanding'.
			 */
			अगर (transmitted_queue != &q->retransmit &&
			    !tchunk->tsn_gap_acked) अणु
				अगर (tchunk->transport)
					tchunk->transport->flight_size -=
							sctp_data_size(tchunk);
				q->outstanding_bytes -= sctp_data_size(tchunk);
			पूर्ण
			जारी;
		पूर्ण

		tsn = ntohl(tchunk->subh.data_hdr->tsn);
		अगर (sctp_acked(sack, tsn)) अणु
			/* If this queue is the retransmit queue, the
			 * retransmit समयr has alपढ़ोy reclaimed
			 * the outstanding bytes क्रम this chunk, so only
			 * count bytes associated with a transport.
			 */
			अगर (transport && !tchunk->tsn_gap_acked) अणु
				/* If this chunk is being used क्रम RTT
				 * measurement, calculate the RTT and update
				 * the RTO using this value.
				 *
				 * 6.3.1 C5) Karn's algorithm: RTT measurements
				 * MUST NOT be made using packets that were
				 * retransmitted (and thus क्रम which it is
				 * ambiguous whether the reply was क्रम the
				 * first instance of the packet or a later
				 * instance).
				 */
				अगर (!sctp_chunk_retransmitted(tchunk) &&
				    tchunk->rtt_in_progress) अणु
					tchunk->rtt_in_progress = 0;
					rtt = jअगरfies - tchunk->sent_at;
					sctp_transport_update_rto(transport,
								  rtt);
				पूर्ण

				अगर (TSN_lte(tsn, sack_ctsn)) अणु
					/*
					 * SFR-CACC algorithm:
					 * 2) If the SACK contains gap acks
					 * and the flag CHANGEOVER_ACTIVE is
					 * set the receiver of the SACK MUST
					 * take the following action:
					 *
					 * B) For each TSN t being acked that
					 * has not been acked in any SACK so
					 * far, set cacc_saw_newack to 1 क्रम
					 * the destination that the TSN was
					 * sent to.
					 */
					अगर (sack->num_gap_ack_blocks &&
					    q->asoc->peer.primary_path->cacc.
					    changeover_active)
						transport->cacc.cacc_saw_newack
							= 1;
				पूर्ण
			पूर्ण

			/* If the chunk hasn't been marked as ACKED,
			 * mark it and account bytes_acked अगर the
			 * chunk had a valid transport (it will not
			 * have a transport अगर ASCONF had deleted it
			 * जबतक DATA was outstanding).
			 */
			अगर (!tchunk->tsn_gap_acked) अणु
				tchunk->tsn_gap_acked = 1;
				अगर (TSN_lt(*highest_new_tsn_in_sack, tsn))
					*highest_new_tsn_in_sack = tsn;
				bytes_acked += sctp_data_size(tchunk);
				अगर (!tchunk->transport)
					migrate_bytes += sctp_data_size(tchunk);
				क्रमward_progress = true;
			पूर्ण

			अगर (TSN_lte(tsn, sack_ctsn)) अणु
				/* RFC 2960  6.3.2 Retransmission Timer Rules
				 *
				 * R3) Whenever a SACK is received
				 * that acknowledges the DATA chunk
				 * with the earliest outstanding TSN
				 * क्रम that address, restart T3-rtx
				 * समयr क्रम that address with its
				 * current RTO.
				 */
				restart_समयr = 1;
				क्रमward_progress = true;

				list_add_tail(&tchunk->transmitted_list,
					      &q->sacked);
			पूर्ण अन्यथा अणु
				/* RFC2960 7.2.4, sctpimpguide-05 2.8.2
				 * M2) Each समय a SACK arrives reporting
				 * 'Stray DATA chunk(s)' record the highest TSN
				 * reported as newly acknowledged, call this
				 * value 'HighestTSNinSack'. A newly
				 * acknowledged DATA chunk is one not
				 * previously acknowledged in a SACK.
				 *
				 * When the SCTP sender of data receives a SACK
				 * chunk that acknowledges, क्रम the first समय,
				 * the receipt of a DATA chunk, all the still
				 * unacknowledged DATA chunks whose TSN is
				 * older than that newly acknowledged DATA
				 * chunk, are qualअगरied as 'Stray DATA chunks'.
				 */
				list_add_tail(lchunk, &tlist);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tchunk->tsn_gap_acked) अणु
				pr_debug("%s: receiver reneged on data TSN:0x%x\n",
					 __func__, tsn);

				tchunk->tsn_gap_acked = 0;

				अगर (tchunk->transport)
					bytes_acked -= sctp_data_size(tchunk);

				/* RFC 2960 6.3.2 Retransmission Timer Rules
				 *
				 * R4) Whenever a SACK is received missing a
				 * TSN that was previously acknowledged via a
				 * Gap Ack Block, start T3-rtx क्रम the
				 * destination address to which the DATA
				 * chunk was originally
				 * transmitted अगर it is not alपढ़ोy running.
				 */
				restart_समयr = 1;
			पूर्ण

			list_add_tail(lchunk, &tlist);
		पूर्ण
	पूर्ण

	अगर (transport) अणु
		अगर (bytes_acked) अणु
			काष्ठा sctp_association *asoc = transport->asoc;

			/* We may have counted DATA that was migrated
			 * to this transport due to DEL-IP operation.
			 * Subtract those bytes, since the were never
			 * send on this transport and shouldn't be
			 * credited to this transport.
			 */
			bytes_acked -= migrate_bytes;

			/* 8.2. When an outstanding TSN is acknowledged,
			 * the endpoपूर्णांक shall clear the error counter of
			 * the destination transport address to which the
			 * DATA chunk was last sent.
			 * The association's overall error counter is
			 * also cleared.
			 */
			transport->error_count = 0;
			transport->asoc->overall_error_count = 0;
			क्रमward_progress = true;

			/*
			 * While in SHUTDOWN PENDING, we may have started
			 * the T5 shutकरोwn guard समयr after reaching the
			 * retransmission limit. Stop that समयr as soon
			 * as the receiver acknowledged any data.
			 */
			अगर (asoc->state == SCTP_STATE_SHUTDOWN_PENDING &&
			    del_समयr(&asoc->समयrs
				[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD]))
					sctp_association_put(asoc);

			/* Mark the destination transport address as
			 * active अगर it is not so marked.
			 */
			अगर ((transport->state == SCTP_INACTIVE ||
			     transport->state == SCTP_UNCONFIRMED) &&
			    sctp_cmp_addr_exact(&transport->ipaddr, saddr)) अणु
				sctp_assoc_control_transport(
					transport->asoc,
					transport,
					SCTP_TRANSPORT_UP,
					SCTP_RECEIVED_SACK);
			पूर्ण

			sctp_transport_उठाओ_cwnd(transport, sack_ctsn,
						  bytes_acked);

			transport->flight_size -= bytes_acked;
			अगर (transport->flight_size == 0)
				transport->partial_bytes_acked = 0;
			q->outstanding_bytes -= bytes_acked + migrate_bytes;
		पूर्ण अन्यथा अणु
			/* RFC 2960 6.1, sctpimpguide-06 2.15.2
			 * When a sender is करोing zero winकरोw probing, it
			 * should not समयout the association अगर it जारीs
			 * to receive new packets from the receiver. The
			 * reason is that the receiver MAY keep its winकरोw
			 * बंदd क्रम an indefinite समय.
			 * A sender is करोing zero winकरोw probing when the
			 * receiver's advertised winकरोw is zero, and there is
			 * only one data chunk in flight to the receiver.
			 *
			 * Allow the association to समयout जबतक in SHUTDOWN
			 * PENDING or SHUTDOWN RECEIVED in हाल the receiver
			 * stays in zero winकरोw mode क्रमever.
			 */
			अगर (!q->asoc->peer.rwnd &&
			    !list_empty(&tlist) &&
			    (sack_ctsn+2 == q->asoc->next_tsn) &&
			    q->asoc->state < SCTP_STATE_SHUTDOWN_PENDING) अणु
				pr_debug("%s: sack received for zero window "
					 "probe:%u\n", __func__, sack_ctsn);

				q->asoc->overall_error_count = 0;
				transport->error_count = 0;
			पूर्ण
		पूर्ण

		/* RFC 2960 6.3.2 Retransmission Timer Rules
		 *
		 * R2) Whenever all outstanding data sent to an address have
		 * been acknowledged, turn off the T3-rtx समयr of that
		 * address.
		 */
		अगर (!transport->flight_size) अणु
			अगर (del_समयr(&transport->T3_rtx_समयr))
				sctp_transport_put(transport);
		पूर्ण अन्यथा अगर (restart_समयr) अणु
			अगर (!mod_समयr(&transport->T3_rtx_समयr,
				       jअगरfies + transport->rto))
				sctp_transport_hold(transport);
		पूर्ण

		अगर (क्रमward_progress) अणु
			अगर (transport->dst)
				sctp_transport_dst_confirm(transport);
		पूर्ण
	पूर्ण

	list_splice(&tlist, transmitted_queue);
पूर्ण

/* Mark chunks as missing and consequently may get retransmitted. */
अटल व्योम sctp_mark_missing(काष्ठा sctp_outq *q,
			      काष्ठा list_head *transmitted_queue,
			      काष्ठा sctp_transport *transport,
			      __u32 highest_new_tsn_in_sack,
			      पूर्णांक count_of_newacks)
अणु
	काष्ठा sctp_chunk *chunk;
	__u32 tsn;
	अक्षर करो_fast_retransmit = 0;
	काष्ठा sctp_association *asoc = q->asoc;
	काष्ठा sctp_transport *primary = asoc->peer.primary_path;

	list_क्रम_each_entry(chunk, transmitted_queue, transmitted_list) अणु

		tsn = ntohl(chunk->subh.data_hdr->tsn);

		/* RFC 2960 7.2.4, sctpimpguide-05 2.8.2 M3) Examine all
		 * 'Unacknowledged TSN's', अगर the TSN number of an
		 * 'Unacknowledged TSN' is smaller than the 'HighestTSNinSack'
		 * value, increment the 'TSN.Missing.Report' count on that
		 * chunk अगर it has NOT been fast retransmitted or marked क्रम
		 * fast retransmit alपढ़ोy.
		 */
		अगर (chunk->fast_retransmit == SCTP_CAN_FRTX &&
		    !chunk->tsn_gap_acked &&
		    TSN_lt(tsn, highest_new_tsn_in_sack)) अणु

			/* SFR-CACC may require us to skip marking
			 * this chunk as missing.
			 */
			अगर (!transport || !sctp_cacc_skip(primary,
						chunk->transport,
						count_of_newacks, tsn)) अणु
				chunk->tsn_missing_report++;

				pr_debug("%s: tsn:0x%x missing counter:%d\n",
					 __func__, tsn, chunk->tsn_missing_report);
			पूर्ण
		पूर्ण
		/*
		 * M4) If any DATA chunk is found to have a
		 * 'TSN.Missing.Report'
		 * value larger than or equal to 3, mark that chunk क्रम
		 * retransmission and start the fast retransmit procedure.
		 */

		अगर (chunk->tsn_missing_report >= 3) अणु
			chunk->fast_retransmit = SCTP_NEED_FRTX;
			करो_fast_retransmit = 1;
		पूर्ण
	पूर्ण

	अगर (transport) अणु
		अगर (करो_fast_retransmit)
			sctp_retransmit(q, transport, SCTP_RTXR_FAST_RTX);

		pr_debug("%s: transport:%p, cwnd:%d, ssthresh:%d, "
			 "flight_size:%d, pba:%d\n",  __func__, transport,
			 transport->cwnd, transport->ssthresh,
			 transport->flight_size, transport->partial_bytes_acked);
	पूर्ण
पूर्ण

/* Is the given TSN acked by this packet?  */
अटल पूर्णांक sctp_acked(काष्ठा sctp_sackhdr *sack, __u32 tsn)
अणु
	__u32 ctsn = ntohl(sack->cum_tsn_ack);
	जोड़ sctp_sack_variable *frags;
	__u16 tsn_offset, blocks;
	पूर्णांक i;

	अगर (TSN_lte(tsn, ctsn))
		जाओ pass;

	/* 3.3.4 Selective Acknowledgment (SACK) (3):
	 *
	 * Gap Ack Blocks:
	 *  These fields contain the Gap Ack Blocks. They are repeated
	 *  क्रम each Gap Ack Block up to the number of Gap Ack Blocks
	 *  defined in the Number of Gap Ack Blocks field. All DATA
	 *  chunks with TSNs greater than or equal to (Cumulative TSN
	 *  Ack + Gap Ack Block Start) and less than or equal to
	 *  (Cumulative TSN Ack + Gap Ack Block End) of each Gap Ack
	 *  Block are assumed to have been received correctly.
	 */

	frags = sack->variable;
	blocks = ntohs(sack->num_gap_ack_blocks);
	tsn_offset = tsn - ctsn;
	क्रम (i = 0; i < blocks; ++i) अणु
		अगर (tsn_offset >= ntohs(frags[i].gab.start) &&
		    tsn_offset <= ntohs(frags[i].gab.end))
			जाओ pass;
	पूर्ण

	वापस 0;
pass:
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक sctp_get_skip_pos(काष्ठा sctp_fwdtsn_skip *skiplist,
				    पूर्णांक nskips, __be16 stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nskips; i++) अणु
		अगर (skiplist[i].stream == stream)
			वापस i;
	पूर्ण
	वापस i;
पूर्ण

/* Create and add a fwdtsn chunk to the outq's control queue अगर needed. */
व्योम sctp_generate_fwdtsn(काष्ठा sctp_outq *q, __u32 ctsn)
अणु
	काष्ठा sctp_association *asoc = q->asoc;
	काष्ठा sctp_chunk *ftsn_chunk = शून्य;
	काष्ठा sctp_fwdtsn_skip ftsn_skip_arr[10];
	पूर्णांक nskips = 0;
	पूर्णांक skip_pos = 0;
	__u32 tsn;
	काष्ठा sctp_chunk *chunk;
	काष्ठा list_head *lchunk, *temp;

	अगर (!asoc->peer.prsctp_capable)
		वापस;

	/* PR-SCTP C1) Let SackCumAck be the Cumulative TSN ACK carried in the
	 * received SACK.
	 *
	 * If (Advanced.Peer.Ack.Poपूर्णांक < SackCumAck), then update
	 * Advanced.Peer.Ack.Poपूर्णांक to be equal to SackCumAck.
	 */
	अगर (TSN_lt(asoc->adv_peer_ack_poपूर्णांक, ctsn))
		asoc->adv_peer_ack_poपूर्णांक = ctsn;

	/* PR-SCTP C2) Try to further advance the "Advanced.Peer.Ack.Point"
	 * locally, that is, to move "Advanced.Peer.Ack.Point" up as दीर्घ as
	 * the chunk next in the out-queue space is marked as "abandoned" as
	 * shown in the following example:
	 *
	 * Assuming that a SACK arrived with the Cumulative TSN ACK 102
	 * and the Advanced.Peer.Ack.Poपूर्णांक is updated to this value:
	 *
	 *   out-queue at the end of  ==>   out-queue after Adv.Ack.Poपूर्णांक
	 *   normal SACK processing           local advancement
	 *                ...                           ...
	 *   Adv.Ack.Pt-> 102 acked                     102 acked
	 *                103 abanकरोned                 103 abanकरोned
	 *                104 abanकरोned     Adv.Ack.P-> 104 abanकरोned
	 *                105                           105
	 *                106 acked                     106 acked
	 *                ...                           ...
	 *
	 * In this example, the data sender successfully advanced the
	 * "Advanced.Peer.Ack.Point" from 102 to 104 locally.
	 */
	list_क्रम_each_safe(lchunk, temp, &q->abanकरोned) अणु
		chunk = list_entry(lchunk, काष्ठा sctp_chunk,
					transmitted_list);
		tsn = ntohl(chunk->subh.data_hdr->tsn);

		/* Remove any chunks in the abanकरोned queue that are acked by
		 * the ctsn.
		 */
		अगर (TSN_lte(tsn, ctsn)) अणु
			list_del_init(lchunk);
			sctp_chunk_मुक्त(chunk);
		पूर्ण अन्यथा अणु
			अगर (TSN_lte(tsn, asoc->adv_peer_ack_poपूर्णांक+1)) अणु
				asoc->adv_peer_ack_poपूर्णांक = tsn;
				अगर (chunk->chunk_hdr->flags &
					 SCTP_DATA_UNORDERED)
					जारी;
				skip_pos = sctp_get_skip_pos(&ftsn_skip_arr[0],
						nskips,
						chunk->subh.data_hdr->stream);
				ftsn_skip_arr[skip_pos].stream =
					chunk->subh.data_hdr->stream;
				ftsn_skip_arr[skip_pos].ssn =
					 chunk->subh.data_hdr->ssn;
				अगर (skip_pos == nskips)
					nskips++;
				अगर (nskips == 10)
					अवरोध;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	/* PR-SCTP C3) If, after step C1 and C2, the "Advanced.Peer.Ack.Point"
	 * is greater than the Cumulative TSN ACK carried in the received
	 * SACK, the data sender MUST send the data receiver a FORWARD TSN
	 * chunk containing the latest value of the
	 * "Advanced.Peer.Ack.Point".
	 *
	 * C4) For each "abandoned" TSN the sender of the FORWARD TSN SHOULD
	 * list each stream and sequence number in the क्रमwarded TSN. This
	 * inक्रमmation will enable the receiver to easily find any
	 * stअक्रमed TSN's रुकोing on stream reorder queues. Each stream
	 * SHOULD only be reported once; this means that अगर multiple
	 * abanकरोned messages occur in the same stream then only the
	 * highest abanकरोned stream sequence number is reported. If the
	 * total size of the FORWARD TSN करोes NOT fit in a single MTU then
	 * the sender of the FORWARD TSN SHOULD lower the
	 * Advanced.Peer.Ack.Poपूर्णांक to the last TSN that will fit in a
	 * single MTU.
	 */
	अगर (asoc->adv_peer_ack_poपूर्णांक > ctsn)
		ftsn_chunk = sctp_make_fwdtsn(asoc, asoc->adv_peer_ack_poपूर्णांक,
					      nskips, &ftsn_skip_arr[0]);

	अगर (ftsn_chunk) अणु
		list_add_tail(&ftsn_chunk->list, &q->control_chunk_list);
		SCTP_INC_STATS(asoc->base.net, SCTP_MIB_OUTCTRLCHUNKS);
	पूर्ण
पूर्ण
