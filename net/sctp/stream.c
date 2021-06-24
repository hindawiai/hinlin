<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * This file contains sctp stream maniuplation primitives and helpers.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Xin Long <lucien.xin@gmail.com>
 */

#समावेश <linux/list.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/stream_sched.h>

अटल व्योम sctp_stream_shrink_out(काष्ठा sctp_stream *stream, __u16 outcnt)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_chunk *ch, *temp;
	काष्ठा sctp_outq *outq;

	asoc = container_of(stream, काष्ठा sctp_association, stream);
	outq = &asoc->outqueue;

	list_क्रम_each_entry_safe(ch, temp, &outq->out_chunk_list, list) अणु
		__u16 sid = sctp_chunk_stream_no(ch);

		अगर (sid < outcnt)
			जारी;

		sctp_sched_dequeue_common(outq, ch);
		/* No need to call dequeue_करोne here because
		 * the chunks are not scheduled by now.
		 */

		/* Mark as failed send. */
		sctp_chunk_fail(ch, (__क्रमce __u32)SCTP_ERROR_INV_STRM);
		अगर (asoc->peer.prsctp_capable &&
		    SCTP_PR_PRIO_ENABLED(ch->sinfo.sinfo_flags))
			asoc->sent_cnt_removable--;

		sctp_chunk_मुक्त(ch);
	पूर्ण
पूर्ण

/* Migrates chunks from stream queues to new stream queues अगर needed,
 * but not across associations. Also, हटाओs those chunks to streams
 * higher than the new max.
 */
अटल व्योम sctp_stream_outq_migrate(काष्ठा sctp_stream *stream,
				     काष्ठा sctp_stream *new, __u16 outcnt)
अणु
	पूर्णांक i;

	अगर (stream->outcnt > outcnt)
		sctp_stream_shrink_out(stream, outcnt);

	अगर (new) अणु
		/* Here we actually move the old ext stuff पूर्णांकo the new
		 * buffer, because we want to keep it. Then
		 * sctp_stream_update will swap ->out poपूर्णांकers.
		 */
		क्रम (i = 0; i < outcnt; i++) अणु
			kमुक्त(SCTP_SO(new, i)->ext);
			SCTP_SO(new, i)->ext = SCTP_SO(stream, i)->ext;
			SCTP_SO(stream, i)->ext = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = outcnt; i < stream->outcnt; i++) अणु
		kमुक्त(SCTP_SO(stream, i)->ext);
		SCTP_SO(stream, i)->ext = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sctp_stream_alloc_out(काष्ठा sctp_stream *stream, __u16 outcnt,
				 gfp_t gfp)
अणु
	पूर्णांक ret;

	अगर (outcnt <= stream->outcnt)
		जाओ out;

	ret = genradix_pपुनः_स्मृति(&stream->out, outcnt, gfp);
	अगर (ret)
		वापस ret;

out:
	stream->outcnt = outcnt;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_stream_alloc_in(काष्ठा sctp_stream *stream, __u16 incnt,
				gfp_t gfp)
अणु
	पूर्णांक ret;

	अगर (incnt <= stream->incnt)
		जाओ out;

	ret = genradix_pपुनः_स्मृति(&stream->in, incnt, gfp);
	अगर (ret)
		वापस ret;

out:
	stream->incnt = incnt;
	वापस 0;
पूर्ण

पूर्णांक sctp_stream_init(काष्ठा sctp_stream *stream, __u16 outcnt, __u16 incnt,
		     gfp_t gfp)
अणु
	काष्ठा sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);
	पूर्णांक i, ret = 0;

	gfp |= __GFP_NOWARN;

	/* Initial stream->out size may be very big, so मुक्त it and alloc
	 * a new one with new outcnt to save memory अगर needed.
	 */
	अगर (outcnt == stream->outcnt)
		जाओ handle_in;

	/* Filter out chunks queued on streams that won't exist anymore */
	sched->unsched_all(stream);
	sctp_stream_outq_migrate(stream, शून्य, outcnt);
	sched->sched_all(stream);

	ret = sctp_stream_alloc_out(stream, outcnt, gfp);
	अगर (ret)
		जाओ out_err;

	क्रम (i = 0; i < stream->outcnt; i++)
		SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

handle_in:
	sctp_stream_पूर्णांकerleave_init(stream);
	अगर (!incnt)
		जाओ out;

	ret = sctp_stream_alloc_in(stream, incnt, gfp);
	अगर (ret)
		जाओ in_err;

	जाओ out;

in_err:
	sched->मुक्त(stream);
	genradix_मुक्त(&stream->in);
out_err:
	genradix_मुक्त(&stream->out);
	stream->outcnt = 0;
out:
	वापस ret;
पूर्ण

पूर्णांक sctp_stream_init_ext(काष्ठा sctp_stream *stream, __u16 sid)
अणु
	काष्ठा sctp_stream_out_ext *soute;
	पूर्णांक ret;

	soute = kzalloc(माप(*soute), GFP_KERNEL);
	अगर (!soute)
		वापस -ENOMEM;
	SCTP_SO(stream, sid)->ext = soute;

	ret = sctp_sched_init_sid(stream, sid, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(SCTP_SO(stream, sid)->ext);
		SCTP_SO(stream, sid)->ext = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

व्योम sctp_stream_मुक्त(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);
	पूर्णांक i;

	sched->मुक्त(stream);
	क्रम (i = 0; i < stream->outcnt; i++)
		kमुक्त(SCTP_SO(stream, i)->ext);
	genradix_मुक्त(&stream->out);
	genradix_मुक्त(&stream->in);
पूर्ण

व्योम sctp_stream_clear(काष्ठा sctp_stream *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stream->outcnt; i++) अणु
		SCTP_SO(stream, i)->mid = 0;
		SCTP_SO(stream, i)->mid_uo = 0;
	पूर्ण

	क्रम (i = 0; i < stream->incnt; i++)
		SCTP_SI(stream, i)->mid = 0;
पूर्ण

व्योम sctp_stream_update(काष्ठा sctp_stream *stream, काष्ठा sctp_stream *new)
अणु
	काष्ठा sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);

	sched->unsched_all(stream);
	sctp_stream_outq_migrate(stream, new, new->outcnt);
	sctp_stream_मुक्त(stream);

	stream->out = new->out;
	stream->in  = new->in;
	stream->outcnt = new->outcnt;
	stream->incnt  = new->incnt;

	sched->sched_all(stream);

	new->out.tree.root = शून्य;
	new->in.tree.root  = शून्य;
	new->outcnt = 0;
	new->incnt  = 0;
पूर्ण

अटल पूर्णांक sctp_send_reconf(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_chunk *chunk)
अणु
	पूर्णांक retval = 0;

	retval = sctp_primitive_RECONF(asoc->base.net, asoc, chunk);
	अगर (retval)
		sctp_chunk_मुक्त(chunk);

	वापस retval;
पूर्ण

अटल bool sctp_stream_outq_is_empty(काष्ठा sctp_stream *stream,
				      __u16 str_nums, __be16 *str_list)
अणु
	काष्ठा sctp_association *asoc;
	__u16 i;

	asoc = container_of(stream, काष्ठा sctp_association, stream);
	अगर (!asoc->outqueue.out_qlen)
		वापस true;

	अगर (!str_nums)
		वापस false;

	क्रम (i = 0; i < str_nums; i++) अणु
		__u16 sid = ntohs(str_list[i]);

		अगर (SCTP_SO(stream, sid)->ext &&
		    !list_empty(&SCTP_SO(stream, sid)->ext->outq))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक sctp_send_reset_streams(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_reset_streams *params)
अणु
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u16 i, str_nums, *str_list;
	काष्ठा sctp_chunk *chunk;
	पूर्णांक retval = -EINVAL;
	__be16 *nstr_list;
	bool out, in;

	अगर (!asoc->peer.reconf_capable ||
	    !(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ)) अणु
		retval = -ENOPROTOOPT;
		जाओ out;
	पूर्ण

	अगर (asoc->strreset_outstanding) अणु
		retval = -EINPROGRESS;
		जाओ out;
	पूर्ण

	out = params->srs_flags & SCTP_STREAM_RESET_OUTGOING;
	in  = params->srs_flags & SCTP_STREAM_RESET_INCOMING;
	अगर (!out && !in)
		जाओ out;

	str_nums = params->srs_number_streams;
	str_list = params->srs_stream_list;
	अगर (str_nums) अणु
		पूर्णांक param_len = 0;

		अगर (out) अणु
			क्रम (i = 0; i < str_nums; i++)
				अगर (str_list[i] >= stream->outcnt)
					जाओ out;

			param_len = str_nums * माप(__u16) +
				    माप(काष्ठा sctp_strreset_outreq);
		पूर्ण

		अगर (in) अणु
			क्रम (i = 0; i < str_nums; i++)
				अगर (str_list[i] >= stream->incnt)
					जाओ out;

			param_len += str_nums * माप(__u16) +
				     माप(काष्ठा sctp_strreset_inreq);
		पूर्ण

		अगर (param_len > SCTP_MAX_CHUNK_LEN -
				माप(काष्ठा sctp_reconf_chunk))
			जाओ out;
	पूर्ण

	nstr_list = kसुस्मृति(str_nums, माप(__be16), GFP_KERNEL);
	अगर (!nstr_list) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < str_nums; i++)
		nstr_list[i] = htons(str_list[i]);

	अगर (out && !sctp_stream_outq_is_empty(stream, str_nums, nstr_list)) अणु
		kमुक्त(nstr_list);
		retval = -EAGAIN;
		जाओ out;
	पूर्ण

	chunk = sctp_make_strreset_req(asoc, str_nums, nstr_list, out, in);

	kमुक्त(nstr_list);

	अगर (!chunk) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (out) अणु
		अगर (str_nums)
			क्रम (i = 0; i < str_nums; i++)
				SCTP_SO(stream, str_list[i])->state =
						       SCTP_STREAM_CLOSED;
		अन्यथा
			क्रम (i = 0; i < stream->outcnt; i++)
				SCTP_SO(stream, i)->state = SCTP_STREAM_CLOSED;
	पूर्ण

	asoc->strreset_chunk = chunk;
	sctp_chunk_hold(asoc->strreset_chunk);

	retval = sctp_send_reconf(asoc, chunk);
	अगर (retval) अणु
		sctp_chunk_put(asoc->strreset_chunk);
		asoc->strreset_chunk = शून्य;
		अगर (!out)
			जाओ out;

		अगर (str_nums)
			क्रम (i = 0; i < str_nums; i++)
				SCTP_SO(stream, str_list[i])->state =
						       SCTP_STREAM_OPEN;
		अन्यथा
			क्रम (i = 0; i < stream->outcnt; i++)
				SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

		जाओ out;
	पूर्ण

	asoc->strreset_outstanding = out + in;

out:
	वापस retval;
पूर्ण

पूर्णांक sctp_send_reset_assoc(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_stream *stream = &asoc->stream;
	काष्ठा sctp_chunk *chunk = शून्य;
	पूर्णांक retval;
	__u16 i;

	अगर (!asoc->peer.reconf_capable ||
	    !(asoc->strreset_enable & SCTP_ENABLE_RESET_ASSOC_REQ))
		वापस -ENOPROTOOPT;

	अगर (asoc->strreset_outstanding)
		वापस -EINPROGRESS;

	अगर (!sctp_outq_is_empty(&asoc->outqueue))
		वापस -EAGAIN;

	chunk = sctp_make_strreset_tsnreq(asoc);
	अगर (!chunk)
		वापस -ENOMEM;

	/* Block further xmit of data until this request is completed */
	क्रम (i = 0; i < stream->outcnt; i++)
		SCTP_SO(stream, i)->state = SCTP_STREAM_CLOSED;

	asoc->strreset_chunk = chunk;
	sctp_chunk_hold(asoc->strreset_chunk);

	retval = sctp_send_reconf(asoc, chunk);
	अगर (retval) अणु
		sctp_chunk_put(asoc->strreset_chunk);
		asoc->strreset_chunk = शून्य;

		क्रम (i = 0; i < stream->outcnt; i++)
			SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

		वापस retval;
	पूर्ण

	asoc->strreset_outstanding = 1;

	वापस 0;
पूर्ण

पूर्णांक sctp_send_add_streams(काष्ठा sctp_association *asoc,
			  काष्ठा sctp_add_streams *params)
अणु
	काष्ठा sctp_stream *stream = &asoc->stream;
	काष्ठा sctp_chunk *chunk = शून्य;
	पूर्णांक retval;
	__u32 outcnt, incnt;
	__u16 out, in;

	अगर (!asoc->peer.reconf_capable ||
	    !(asoc->strreset_enable & SCTP_ENABLE_CHANGE_ASSOC_REQ)) अणु
		retval = -ENOPROTOOPT;
		जाओ out;
	पूर्ण

	अगर (asoc->strreset_outstanding) अणु
		retval = -EINPROGRESS;
		जाओ out;
	पूर्ण

	out = params->sas_outstrms;
	in  = params->sas_instrms;
	outcnt = stream->outcnt + out;
	incnt = stream->incnt + in;
	अगर (outcnt > SCTP_MAX_STREAM || incnt > SCTP_MAX_STREAM ||
	    (!out && !in)) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (out) अणु
		retval = sctp_stream_alloc_out(stream, outcnt, GFP_KERNEL);
		अगर (retval)
			जाओ out;
	पूर्ण

	chunk = sctp_make_strreset_addstrm(asoc, out, in);
	अगर (!chunk) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	asoc->strreset_chunk = chunk;
	sctp_chunk_hold(asoc->strreset_chunk);

	retval = sctp_send_reconf(asoc, chunk);
	अगर (retval) अणु
		sctp_chunk_put(asoc->strreset_chunk);
		asoc->strreset_chunk = शून्य;
		जाओ out;
	पूर्ण

	asoc->strreset_outstanding = !!out + !!in;

out:
	वापस retval;
पूर्ण

अटल काष्ठा sctp_paramhdr *sctp_chunk_lookup_strreset_param(
			काष्ठा sctp_association *asoc, __be32 resp_seq,
			__be16 type)
अणु
	काष्ठा sctp_chunk *chunk = asoc->strreset_chunk;
	काष्ठा sctp_reconf_chunk *hdr;
	जोड़ sctp_params param;

	अगर (!chunk)
		वापस शून्य;

	hdr = (काष्ठा sctp_reconf_chunk *)chunk->chunk_hdr;
	sctp_walk_params(param, hdr, params) अणु
		/* sctp_strreset_tsnreq is actually the basic काष्ठाure
		 * of all stream reconf params, so it's safe to use it
		 * to access request_seq.
		 */
		काष्ठा sctp_strreset_tsnreq *req = param.v;

		अगर ((!resp_seq || req->request_seq == resp_seq) &&
		    (!type || type == req->param_hdr.type))
			वापस param.v;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम sctp_update_strreset_result(काष्ठा sctp_association *asoc,
					__u32 result)
अणु
	asoc->strreset_result[1] = asoc->strreset_result[0];
	asoc->strreset_result[0] = result;
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_outreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	काष्ठा sctp_strreset_outreq *outreq = param.v;
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	__be16 *str_p = शून्य;
	__u32 request_seq;
	__u16 i, nums;

	request_seq = ntohl(outreq->request_seq);

	अगर (ntohl(outreq->send_reset_at_tsn) >
	    sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map)) अणु
		result = SCTP_STRRESET_IN_PROGRESS;
		जाओ err;
	पूर्ण

	अगर (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) अणु
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		जाओ err;
	पूर्ण अन्यथा अगर (TSN_lt(request_seq, asoc->strreset_inseq)) अणु
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		जाओ err;
	पूर्ण
	asoc->strreset_inseq++;

	/* Check strreset_enable after inseq inc, as sender cannot tell
	 * the peer करोesn't enable strreset after receiving response with
	 * result denied, as well as to keep consistent with bsd.
	 */
	अगर (!(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ))
		जाओ out;

	nums = (ntohs(param.p->length) - माप(*outreq)) / माप(__u16);
	str_p = outreq->list_of_streams;
	क्रम (i = 0; i < nums; i++) अणु
		अगर (ntohs(str_p[i]) >= stream->incnt) अणु
			result = SCTP_STRRESET_ERR_WRONG_SSN;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (asoc->strreset_chunk) अणु
		अगर (!sctp_chunk_lookup_strreset_param(
				asoc, outreq->response_seq,
				SCTP_PARAM_RESET_IN_REQUEST)) अणु
			/* same process with outstanding isn't 0 */
			result = SCTP_STRRESET_ERR_IN_PROGRESS;
			जाओ out;
		पूर्ण

		asoc->strreset_outstanding--;
		asoc->strreset_outseq++;

		अगर (!asoc->strreset_outstanding) अणु
			काष्ठा sctp_transport *t;

			t = asoc->strreset_chunk->transport;
			अगर (del_समयr(&t->reconf_समयr))
				sctp_transport_put(t);

			sctp_chunk_put(asoc->strreset_chunk);
			asoc->strreset_chunk = शून्य;
		पूर्ण
	पूर्ण

	अगर (nums)
		क्रम (i = 0; i < nums; i++)
			SCTP_SI(stream, ntohs(str_p[i]))->mid = 0;
	अन्यथा
		क्रम (i = 0; i < stream->incnt; i++)
			SCTP_SI(stream, i)->mid = 0;

	result = SCTP_STRRESET_PERFORMED;

	*evp = sctp_ulpevent_make_stream_reset_event(asoc,
		SCTP_STREAM_RESET_INCOMING_SSN, nums, str_p, GFP_ATOMIC);

out:
	sctp_update_strreset_result(asoc, result);
err:
	वापस sctp_make_strreset_resp(asoc, result, request_seq);
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_inreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	काष्ठा sctp_strreset_inreq *inreq = param.v;
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	काष्ठा sctp_chunk *chunk = शून्य;
	__u32 request_seq;
	__u16 i, nums;
	__be16 *str_p;

	request_seq = ntohl(inreq->request_seq);
	अगर (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) अणु
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		जाओ err;
	पूर्ण अन्यथा अगर (TSN_lt(request_seq, asoc->strreset_inseq)) अणु
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		अगर (result == SCTP_STRRESET_PERFORMED)
			वापस शून्य;
		जाओ err;
	पूर्ण
	asoc->strreset_inseq++;

	अगर (!(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ))
		जाओ out;

	अगर (asoc->strreset_outstanding) अणु
		result = SCTP_STRRESET_ERR_IN_PROGRESS;
		जाओ out;
	पूर्ण

	nums = (ntohs(param.p->length) - माप(*inreq)) / माप(__u16);
	str_p = inreq->list_of_streams;
	क्रम (i = 0; i < nums; i++) अणु
		अगर (ntohs(str_p[i]) >= stream->outcnt) अणु
			result = SCTP_STRRESET_ERR_WRONG_SSN;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!sctp_stream_outq_is_empty(stream, nums, str_p)) अणु
		result = SCTP_STRRESET_IN_PROGRESS;
		asoc->strreset_inseq--;
		जाओ err;
	पूर्ण

	chunk = sctp_make_strreset_req(asoc, nums, str_p, 1, 0);
	अगर (!chunk)
		जाओ out;

	अगर (nums)
		क्रम (i = 0; i < nums; i++)
			SCTP_SO(stream, ntohs(str_p[i]))->state =
					       SCTP_STREAM_CLOSED;
	अन्यथा
		क्रम (i = 0; i < stream->outcnt; i++)
			SCTP_SO(stream, i)->state = SCTP_STREAM_CLOSED;

	asoc->strreset_chunk = chunk;
	asoc->strreset_outstanding = 1;
	sctp_chunk_hold(asoc->strreset_chunk);

	result = SCTP_STRRESET_PERFORMED;

out:
	sctp_update_strreset_result(asoc, result);
err:
	अगर (!chunk)
		chunk =  sctp_make_strreset_resp(asoc, result, request_seq);

	वापस chunk;
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_tsnreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	__u32 init_tsn = 0, next_tsn = 0, max_tsn_seen;
	काष्ठा sctp_strreset_tsnreq *tsnreq = param.v;
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	__u32 request_seq;
	__u16 i;

	request_seq = ntohl(tsnreq->request_seq);
	अगर (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) अणु
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		जाओ err;
	पूर्ण अन्यथा अगर (TSN_lt(request_seq, asoc->strreset_inseq)) अणु
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		अगर (result == SCTP_STRRESET_PERFORMED) अणु
			next_tsn = asoc->ctsn_ack_poपूर्णांक + 1;
			init_tsn =
				sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map) + 1;
		पूर्ण
		जाओ err;
	पूर्ण

	अगर (!sctp_outq_is_empty(&asoc->outqueue)) अणु
		result = SCTP_STRRESET_IN_PROGRESS;
		जाओ err;
	पूर्ण

	asoc->strreset_inseq++;

	अगर (!(asoc->strreset_enable & SCTP_ENABLE_RESET_ASSOC_REQ))
		जाओ out;

	अगर (asoc->strreset_outstanding) अणु
		result = SCTP_STRRESET_ERR_IN_PROGRESS;
		जाओ out;
	पूर्ण

	/* G4: The same processing as though a FWD-TSN chunk (as defined in
	 *     [RFC3758]) with all streams affected and a new cumulative TSN
	 *     ACK of the Receiver's Next TSN minus 1 were received MUST be
	 *     perक्रमmed.
	 */
	max_tsn_seen = sctp_tsnmap_get_max_tsn_seen(&asoc->peer.tsn_map);
	asoc->stream.si->report_ftsn(&asoc->ulpq, max_tsn_seen);

	/* G1: Compute an appropriate value क्रम the Receiver's Next TSN -- the
	 *     TSN that the peer should use to send the next DATA chunk.  The
	 *     value SHOULD be the smallest TSN not acknowledged by the
	 *     receiver of the request plus 2^31.
	 */
	init_tsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map) + (1 << 31);
	sctp_tsnmap_init(&asoc->peer.tsn_map, SCTP_TSN_MAP_INITIAL,
			 init_tsn, GFP_ATOMIC);

	/* G3: The same processing as though a SACK chunk with no gap report
	 *     and a cumulative TSN ACK of the Sender's Next TSN minus 1 were
	 *     received MUST be perक्रमmed.
	 */
	sctp_outq_मुक्त(&asoc->outqueue);

	/* G2: Compute an appropriate value क्रम the local endpoपूर्णांक's next TSN,
	 *     i.e., the next TSN asचिन्हित by the receiver of the SSN/TSN reset
	 *     chunk.  The value SHOULD be the highest TSN sent by the receiver
	 *     of the request plus 1.
	 */
	next_tsn = asoc->next_tsn;
	asoc->ctsn_ack_poपूर्णांक = next_tsn - 1;
	asoc->adv_peer_ack_poपूर्णांक = asoc->ctsn_ack_poपूर्णांक;

	/* G5:  The next expected and outgoing SSNs MUST be reset to 0 क्रम all
	 *      incoming and outgoing streams.
	 */
	क्रम (i = 0; i < stream->outcnt; i++) अणु
		SCTP_SO(stream, i)->mid = 0;
		SCTP_SO(stream, i)->mid_uo = 0;
	पूर्ण
	क्रम (i = 0; i < stream->incnt; i++)
		SCTP_SI(stream, i)->mid = 0;

	result = SCTP_STRRESET_PERFORMED;

	*evp = sctp_ulpevent_make_assoc_reset_event(asoc, 0, init_tsn,
						    next_tsn, GFP_ATOMIC);

out:
	sctp_update_strreset_result(asoc, result);
err:
	वापस sctp_make_strreset_tsnresp(asoc, result, request_seq,
					  next_tsn, init_tsn);
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_addstrm_out(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	काष्ठा sctp_strreset_addstrm *addstrm = param.v;
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	__u32 request_seq, incnt;
	__u16 in, i;

	request_seq = ntohl(addstrm->request_seq);
	अगर (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) अणु
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		जाओ err;
	पूर्ण अन्यथा अगर (TSN_lt(request_seq, asoc->strreset_inseq)) अणु
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		जाओ err;
	पूर्ण
	asoc->strreset_inseq++;

	अगर (!(asoc->strreset_enable & SCTP_ENABLE_CHANGE_ASSOC_REQ))
		जाओ out;

	in = ntohs(addstrm->number_of_streams);
	incnt = stream->incnt + in;
	अगर (!in || incnt > SCTP_MAX_STREAM)
		जाओ out;

	अगर (sctp_stream_alloc_in(stream, incnt, GFP_ATOMIC))
		जाओ out;

	अगर (asoc->strreset_chunk) अणु
		अगर (!sctp_chunk_lookup_strreset_param(
			asoc, 0, SCTP_PARAM_RESET_ADD_IN_STREAMS)) अणु
			/* same process with outstanding isn't 0 */
			result = SCTP_STRRESET_ERR_IN_PROGRESS;
			जाओ out;
		पूर्ण

		asoc->strreset_outstanding--;
		asoc->strreset_outseq++;

		अगर (!asoc->strreset_outstanding) अणु
			काष्ठा sctp_transport *t;

			t = asoc->strreset_chunk->transport;
			अगर (del_समयr(&t->reconf_समयr))
				sctp_transport_put(t);

			sctp_chunk_put(asoc->strreset_chunk);
			asoc->strreset_chunk = शून्य;
		पूर्ण
	पूर्ण

	stream->incnt = incnt;

	result = SCTP_STRRESET_PERFORMED;

	*evp = sctp_ulpevent_make_stream_change_event(asoc,
		0, ntohs(addstrm->number_of_streams), 0, GFP_ATOMIC);

out:
	sctp_update_strreset_result(asoc, result);
err:
	वापस sctp_make_strreset_resp(asoc, result, request_seq);
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_addstrm_in(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	काष्ठा sctp_strreset_addstrm *addstrm = param.v;
	काष्ठा sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	काष्ठा sctp_chunk *chunk = शून्य;
	__u32 request_seq, outcnt;
	__u16 out, i;
	पूर्णांक ret;

	request_seq = ntohl(addstrm->request_seq);
	अगर (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) अणु
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		जाओ err;
	पूर्ण अन्यथा अगर (TSN_lt(request_seq, asoc->strreset_inseq)) अणु
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		अगर (result == SCTP_STRRESET_PERFORMED)
			वापस शून्य;
		जाओ err;
	पूर्ण
	asoc->strreset_inseq++;

	अगर (!(asoc->strreset_enable & SCTP_ENABLE_CHANGE_ASSOC_REQ))
		जाओ out;

	अगर (asoc->strreset_outstanding) अणु
		result = SCTP_STRRESET_ERR_IN_PROGRESS;
		जाओ out;
	पूर्ण

	out = ntohs(addstrm->number_of_streams);
	outcnt = stream->outcnt + out;
	अगर (!out || outcnt > SCTP_MAX_STREAM)
		जाओ out;

	ret = sctp_stream_alloc_out(stream, outcnt, GFP_ATOMIC);
	अगर (ret)
		जाओ out;

	chunk = sctp_make_strreset_addstrm(asoc, out, 0);
	अगर (!chunk)
		जाओ out;

	asoc->strreset_chunk = chunk;
	asoc->strreset_outstanding = 1;
	sctp_chunk_hold(asoc->strreset_chunk);

	stream->outcnt = outcnt;

	result = SCTP_STRRESET_PERFORMED;

out:
	sctp_update_strreset_result(asoc, result);
err:
	अगर (!chunk)
		chunk = sctp_make_strreset_resp(asoc, result, request_seq);

	वापस chunk;
पूर्ण

काष्ठा sctp_chunk *sctp_process_strreset_resp(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp)
अणु
	काष्ठा sctp_stream *stream = &asoc->stream;
	काष्ठा sctp_strreset_resp *resp = param.v;
	काष्ठा sctp_transport *t;
	__u16 i, nums, flags = 0;
	काष्ठा sctp_paramhdr *req;
	__u32 result;

	req = sctp_chunk_lookup_strreset_param(asoc, resp->response_seq, 0);
	अगर (!req)
		वापस शून्य;

	result = ntohl(resp->result);
	अगर (result != SCTP_STRRESET_PERFORMED) अणु
		/* अगर in progress, करो nothing but retransmit */
		अगर (result == SCTP_STRRESET_IN_PROGRESS)
			वापस शून्य;
		अन्यथा अगर (result == SCTP_STRRESET_DENIED)
			flags = SCTP_STREAM_RESET_DENIED;
		अन्यथा
			flags = SCTP_STREAM_RESET_FAILED;
	पूर्ण

	अगर (req->type == SCTP_PARAM_RESET_OUT_REQUEST) अणु
		काष्ठा sctp_strreset_outreq *outreq;
		__be16 *str_p;

		outreq = (काष्ठा sctp_strreset_outreq *)req;
		str_p = outreq->list_of_streams;
		nums = (ntohs(outreq->param_hdr.length) - माप(*outreq)) /
		       माप(__u16);

		अगर (result == SCTP_STRRESET_PERFORMED) अणु
			काष्ठा sctp_stream_out *sout;
			अगर (nums) अणु
				क्रम (i = 0; i < nums; i++) अणु
					sout = SCTP_SO(stream, ntohs(str_p[i]));
					sout->mid = 0;
					sout->mid_uo = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < stream->outcnt; i++) अणु
					sout = SCTP_SO(stream, i);
					sout->mid = 0;
					sout->mid_uo = 0;
				पूर्ण
			पूर्ण
		पूर्ण

		flags |= SCTP_STREAM_RESET_OUTGOING_SSN;

		क्रम (i = 0; i < stream->outcnt; i++)
			SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

		*evp = sctp_ulpevent_make_stream_reset_event(asoc, flags,
			nums, str_p, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (req->type == SCTP_PARAM_RESET_IN_REQUEST) अणु
		काष्ठा sctp_strreset_inreq *inreq;
		__be16 *str_p;

		/* अगर the result is perक्रमmed, it's impossible क्रम inreq */
		अगर (result == SCTP_STRRESET_PERFORMED)
			वापस शून्य;

		inreq = (काष्ठा sctp_strreset_inreq *)req;
		str_p = inreq->list_of_streams;
		nums = (ntohs(inreq->param_hdr.length) - माप(*inreq)) /
		       माप(__u16);

		flags |= SCTP_STREAM_RESET_INCOMING_SSN;

		*evp = sctp_ulpevent_make_stream_reset_event(asoc, flags,
			nums, str_p, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (req->type == SCTP_PARAM_RESET_TSN_REQUEST) अणु
		काष्ठा sctp_strreset_resptsn *resptsn;
		__u32 stsn, rtsn;

		/* check क्रम resptsn, as sctp_verअगरy_reconf didn't करो it*/
		अगर (ntohs(param.p->length) != माप(*resptsn))
			वापस शून्य;

		resptsn = (काष्ठा sctp_strreset_resptsn *)resp;
		stsn = ntohl(resptsn->senders_next_tsn);
		rtsn = ntohl(resptsn->receivers_next_tsn);

		अगर (result == SCTP_STRRESET_PERFORMED) अणु
			__u32 mtsn = sctp_tsnmap_get_max_tsn_seen(
						&asoc->peer.tsn_map);
			LIST_HEAD(temp);

			asoc->stream.si->report_ftsn(&asoc->ulpq, mtsn);

			sctp_tsnmap_init(&asoc->peer.tsn_map,
					 SCTP_TSN_MAP_INITIAL,
					 stsn, GFP_ATOMIC);

			/* Clean up sacked and abanकरोned queues only. As the
			 * out_chunk_list may not be empty, splice it to temp,
			 * then get it back after sctp_outq_मुक्त is करोne.
			 */
			list_splice_init(&asoc->outqueue.out_chunk_list, &temp);
			sctp_outq_मुक्त(&asoc->outqueue);
			list_splice_init(&temp, &asoc->outqueue.out_chunk_list);

			asoc->next_tsn = rtsn;
			asoc->ctsn_ack_poपूर्णांक = asoc->next_tsn - 1;
			asoc->adv_peer_ack_poपूर्णांक = asoc->ctsn_ack_poपूर्णांक;

			क्रम (i = 0; i < stream->outcnt; i++) अणु
				SCTP_SO(stream, i)->mid = 0;
				SCTP_SO(stream, i)->mid_uo = 0;
			पूर्ण
			क्रम (i = 0; i < stream->incnt; i++)
				SCTP_SI(stream, i)->mid = 0;
		पूर्ण

		क्रम (i = 0; i < stream->outcnt; i++)
			SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

		*evp = sctp_ulpevent_make_assoc_reset_event(asoc, flags,
			stsn, rtsn, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (req->type == SCTP_PARAM_RESET_ADD_OUT_STREAMS) अणु
		काष्ठा sctp_strreset_addstrm *addstrm;
		__u16 number;

		addstrm = (काष्ठा sctp_strreset_addstrm *)req;
		nums = ntohs(addstrm->number_of_streams);
		number = stream->outcnt - nums;

		अगर (result == SCTP_STRRESET_PERFORMED) अणु
			क्रम (i = number; i < stream->outcnt; i++)
				SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;
		पूर्ण अन्यथा अणु
			sctp_stream_shrink_out(stream, number);
			stream->outcnt = number;
		पूर्ण

		*evp = sctp_ulpevent_make_stream_change_event(asoc, flags,
			0, nums, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (req->type == SCTP_PARAM_RESET_ADD_IN_STREAMS) अणु
		काष्ठा sctp_strreset_addstrm *addstrm;

		/* अगर the result is perक्रमmed, it's impossible क्रम addstrm in
		 * request.
		 */
		अगर (result == SCTP_STRRESET_PERFORMED)
			वापस शून्य;

		addstrm = (काष्ठा sctp_strreset_addstrm *)req;
		nums = ntohs(addstrm->number_of_streams);

		*evp = sctp_ulpevent_make_stream_change_event(asoc, flags,
			nums, 0, GFP_ATOMIC);
	पूर्ण

	asoc->strreset_outstanding--;
	asoc->strreset_outseq++;

	/* हटाओ everything क्रम this reconf request */
	अगर (!asoc->strreset_outstanding) अणु
		t = asoc->strreset_chunk->transport;
		अगर (del_समयr(&t->reconf_समयr))
			sctp_transport_put(t);

		sctp_chunk_put(asoc->strreset_chunk);
		asoc->strreset_chunk = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण
